"""Compare deux exécutions d'AutoDescription rangées par tools/run_install.py.

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

Pour chaque type de ressource (objets, sorts) présent dans la nouvelle exécution :
- couverture (…-compare.txt, modes 2 et 3) : comptes par statut, identiques perdus et gagnés,
  nouveaux « différents », raisons de non-couverture les plus fréquentes ;
- textes (…-dump.txt, option --dump) : comparés sur les ressources communes aux deux
  exécutions, ce qui permet de comparer un panel à une référence complète ; le texte d'un dump
  est celui de l'ancien moteur en modes 0 et 2, celui du nouveau en modes 1 et 3 (une ressource
  non couverte y est « ignored:not_covered ») ;
- autres journaux : identiques ou non, seulement si les deux exécutions portent sur les mêmes
  ressources.
Les ressources synthétiques (préfixes ADT, ADS) sont comptées à part (décision D10).

Usage : python tools/compare_runs.py REFERENCE NOUVELLE [--show N] [--context N]
REFERENCE et NOUVELLE sont des dossiers d'exécution (ou leurs noms, cherchés dans AD_TEST_RUNS).
Code de retour : 0 sans régression, 1 si un identique est perdu, un « différent » apparaît, ou
un texte ou un statut change, 2 si une exécution est illisible.
"""

import argparse
import collections
import os
import sys
import tempfile
from pathlib import Path

from compare_dumps import DumpError, read_dump, show_text_diff

SYNTHETIC = ("ADT", "ADS")
KINDS = {"items": "objets", "spells": "sorts"}
OTHER_LOGS = ("diff.html", "events.txt", "file-errors.md", "not-implemented.md", "opcodes.txt", "recursion.txt",
              "error.log", "warning.log")


def run_folder(name):
    path = Path(name)
    if not path.is_dir():
        path = Path(os.environ.get("AD_TEST_RUNS", Path(tempfile.gettempdir()) / "autodescription-runs")) / name
    if not path.is_dir():
        raise SystemExit(f"ERREUR : exécution introuvable : {name}")
    return path


def find(run, kind, suffix):
    matches = sorted(run.glob(f"*-{kind}-{suffix}"))
    return matches[0] if matches else None


def read_compare(path):
    rows = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        fields = line.split("\t")
        if len(fields) >= 2 and fields[0]:
            rows[fields[0].upper()] = (fields[1], fields[2] if len(fields) > 2 else "")
    return rows


def options(run):
    path = run / "options.txt"
    values = {}
    if path.is_file():
        for line in path.read_text(encoding="utf-8").splitlines():
            name, _, value = line.partition(" = ")
            values[name] = value
    return values


def synthetic(key):
    return key.startswith(SYNTHETIC)


def short_reason(reason):
    return ":".join(reason.split(":")[:3])


def listing(keys, show):
    keys = sorted(keys)
    text = " ".join(keys[:show]) if show >= 0 else " ".join(keys)
    return text + (" …" if 0 <= show < len(keys) else "")


def compare_coverage(reference, new, show):
    regressions = 0
    counts = collections.Counter(status for key, (status, _) in new.items() if not synthetic(key))
    counts_synthetic = collections.Counter(status for key, (status, _) in new.items() if synthetic(key))
    print(f"  couverture : {dict(sorted(counts.items()))}" + (f" ; synthétiques {dict(sorted(counts_synthetic.items()))}" if counts_synthetic else ""))
    if reference is not None:
        common = set(reference) & set(new)
        lost = [k for k in common if reference[k][0] == "identical" and new[k][0] != "identical"]
        different = [k for k in common if new[k][0] == "different" and reference[k][0] != "different"]
        gained = [k for k in common if new[k][0] == "identical" and reference[k][0] != "identical"]
        print(f"  identiques perdus : {len(lost)} ; nouveaux différents : {len(different)} ; identiques gagnés : {len(gained)}")
        for title, keys in (("perdus", lost), ("différents", different), ("gagnés", gained)):
            if keys:
                print(f"    {title} : {listing(keys, show)}")
        regressions += len(lost) + len(different)
    reasons = collections.Counter(short_reason(reason) for key, (status, reason) in new.items()
                                  if status == "not_covered" and not synthetic(key))
    if reasons:
        print("  raisons de non-couverture :")
        for reason, count in reasons.most_common(10):
            print(f"    {count:5}  {reason}")
    return regressions


def compare_texts(reference_path, new_path, show, context):
    reference, _ = read_dump(reference_path)
    new, _ = read_dump(new_path)
    common = sorted(set(reference) & set(new))
    same = text = 0
    status = collections.Counter()
    changed = []
    for key in common:
        _, reference_status, reference_text = reference[key]
        _, new_status, new_text = new[key]
        if reference_status != new_status:
            status[f"{reference_status} -> {new_status}"] += 1
        elif reference_text != new_text:
            text += 1
            changed.append(key)
        else:
            same += 1
    only_new = len(set(new) - set(reference))
    print(f"  textes ({len(common)} ressources communes) : {same} identiques, {text} modifiés"
          + (f" ; {only_new} absentes de la référence" if only_new else ""))
    for transition, count in sorted(status.items()):
        print(f"    statut {transition} : {count}")
    for key in changed[:show] if show >= 0 else changed:
        print(f"    {key}")
        show_text_diff(reference[key][2], new[key][2], context)
    # Une ressource que le nouveau moteur ne couvre pas encore n'est pas une régression.
    lost = sum(count for transition, count in status.items() if not transition.endswith("ignored:not_covered"))
    return text + lost


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("reference")
    parser.add_argument("new")
    parser.add_argument("--show", type=int, default=10, help="ressources détaillées par liste (-1 : toutes)")
    parser.add_argument("--context", type=int, default=1, help="lignes de contexte des différences de texte")
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    reference_run, new_run = run_folder(args.reference), run_folder(args.new)
    same_resources = options(reference_run).get("only") == options(new_run).get("only")
    regressions = 0
    found = False
    try:
        for kind, label in KINDS.items():
            new_compare, new_dump = find(new_run, kind, "compare.txt"), find(new_run, kind, "dump.txt")
            if new_compare is None and new_dump is None:
                continue
            found = True
            print(f"== {label} : {reference_run.name} -> {new_run.name}")
            reference_compare, reference_dump = find(reference_run, kind, "compare.txt"), find(reference_run, kind, "dump.txt")
            if new_compare is not None:
                regressions += compare_coverage(read_compare(reference_compare) if reference_compare else None,
                                                read_compare(new_compare), args.show)
            if new_dump is not None and reference_dump is not None:
                regressions += compare_texts(reference_dump, new_dump, args.show, args.context)
            if same_resources:
                differing = []
                for suffix in OTHER_LOGS:
                    a, b = find(reference_run, kind, suffix), find(new_run, kind, suffix)
                    if a is not None and b is not None and a.read_bytes() != b.read_bytes():
                        differing.append(suffix)
                print(f"  autres journaux : {'différents : ' + ', '.join(differing) if differing else 'identiques'}")
    except (OSError, DumpError) as error:
        print(f"ERREUR : {error}", file=sys.stderr)
        return 2
    if not found:
        print("ERREUR : aucun journal de comparaison ni dump dans la nouvelle exécution", file=sys.stderr)
        return 2
    print("Bilan :", "aucune régression" if regressions == 0 else f"{regressions} régressions")
    return 1 if regressions else 0


if __name__ == "__main__":
    sys.exit(main())
