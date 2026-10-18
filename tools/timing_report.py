"""Résume les chronométrages d'une installation d'AutoDescription (feuille de route, §3.1 cible 3).

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

WeiDU écrit à la fin de son journal (SETUP-AUTODESCRIPTION.DEBUG) une table « Mod Timings » :
une ligne par libellé de PATCH_TIME, durée cumulée sur toute l'exécution (tous composants), plus
ses propres postes internes (function overhead, process_patch2, TOTAL…). Les durées sont
**inclusives** : un libellé contient le temps des libellés imbriqués ; les lignes ne
s'additionnent donc pas entre elles. Résolution de l'horloge ≈ 16 ms par mesure : seules les
sommes sur de nombreux appels sont significatives.

Usage : python tools/timing_report.py SETUP-AUTODESCRIPTION.DEBUG [--top N]
"""

import argparse
import re
import sys

LINE = re.compile(r"^(.+?)\s+(\d+\.\d{3})\s*$")
STEP = re.compile(r"^step:([a-z_]+)(?::item=(\d))?(?::subspell=(\d))?$")
RESOURCE = re.compile(r"\.(ITM|SPL)$", re.I)


def read_timings(path):
    with open(path, "rb") as handle:
        lines = handle.read().decode("latin-1").splitlines()
    try:
        start = max(i for i, line in enumerate(lines) if line.strip() == "Mod Timings")
    except ValueError:
        raise SystemExit(f"ERREUR : table « Mod Timings » absente de {path}")
    timings = {}
    for line in lines[start + 1:]:
        match = LINE.match(line)
        if match:
            timings[match.group(1).strip()] = float(match.group(2))
    return timings


def context(item, subspell):
    parts = []
    if item is not None:
        parts.append("objets" if item == "1" else "sorts")
    if subspell == "1":
        parts.append("dans un sous-sort")
    return ", ".join(parts)


def main():
    parser = argparse.ArgumentParser(description="Résume les chronométrages d'AutoDescription.")
    parser.add_argument("debug_log")
    parser.add_argument("--top", type=int, default=15, help="nombre de ressources les plus lentes affichées")
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    timings = read_timings(args.debug_log)
    resources = {label: seconds for label, seconds in timings.items() if RESOURCE.search(label)}
    loop = {kind: sum(s for label, s in resources.items() if label.upper().endswith("." + kind)) for kind in ("ITM", "SPL")}
    counts = {kind: sum(1 for label in resources if label.upper().endswith("." + kind)) for kind in ("ITM", "SPL")}

    print("== Boucle principale (somme des PATCH_TIME par ressource) ==")
    for kind, name in (("ITM", "objets"), ("SPL", "sorts")):
        print(f"  {name:<8} {loop[kind]:9.3f} s  ({counts[kind]} ressources)")

    print("\n== Étapes (durées inclusives ; % du temps de la boucle du même composant) ==")
    steps = []
    for label, seconds in timings.items():
        match = STEP.match(label)
        if not match:
            continue
        name, item, subspell = match.groups()
        # Étapes propres à un composant : equipped/charged/combat (objets), spell_description (sorts).
        if item is None:
            item = "0" if name == "spell_description" else "1"
        steps.append((seconds, name, item, subspell))
    for seconds, name, item, subspell in sorted(steps, reverse=True):
        base = loop["ITM" if item == "1" else "SPL"]
        share = f"{100 * seconds / base:5.1f} %" if base else "    —"
        print(f"  {seconds:9.3f} s  {share}  {name:<24} {context(item, subspell)}")
    if not steps:
        print("  aucune ligne step:* (version du mod sans chronométrage par étape ?)")

    print(f"\n== {args.top} ressources les plus lentes ==")
    for label, seconds in sorted(resources.items(), key=lambda item: -item[1])[:args.top]:
        print(f"  {seconds:9.3f} s  {label}")

    print("\n== Postes internes de WeiDU (les plus coûteux) ==")
    internal = {label: s for label, s in timings.items() if label not in resources and not STEP.match(label)}
    for label, seconds in sorted(internal.items(), key=lambda item: -item[1])[:8]:
        print(f"  {seconds:9.3f} s  {label}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
