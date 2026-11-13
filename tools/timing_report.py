"""Résume les chronométrages d'une installation d'AutoDescription (feuille de route, §3.1 cible 3).

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

WeiDU écrit à la fin de son journal (SETUP-AUTODESCRIPTION.DEBUG) une table « Mod Timings » :
une ligne par libellé de PATCH_TIME, durée cumulée sur toute l'exécution (tous composants), plus
ses propres postes internes (function overhead, process_patch2, TOTAL…). Les durées sont
**inclusives** : un libellé contient le temps des libellés imbriqués ; les lignes ne
s'additionnent donc pas entre elles. Résolution de l'horloge ≈ 16 ms par mesure : seules les
sommes sur de nombreux appels sont significatives. Ce sont des durées CPU : l'attente (disque,
antivirus…) n'y figure pas. Quand le journal est dans un dossier de tools/run_install.py, la durée
réelle est lue dans console-times.txt et options.txt, et la boucle est découpée par tranches de
ressources (ordre du dump de régression).

Usage : python tools/timing_report.py SETUP-AUTODESCRIPTION.DEBUG [--top N]
"""

import argparse
import re
import sys
from pathlib import Path

LINE = re.compile(r"^(.+?)\s+(\d+\.\d{3})\s*$")
STEP = re.compile(r"^step:([a-z_]+)(?::item=(\d))?(?::subspell=(\d))?$")
RESOURCE = re.compile(r"\.(ITM|SPL)$", re.I)
# Étiquettes ACTION_TIME du composant (AutoDescription.tp2, lib/always.tpa, lib/install.tpp).
COMPONENT_STEPS = ("charsets", "bgforge", "engine", "startup", "catalog", "init", "loop", "close_js", "close_log")


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

    total = timings.get("TOTAL", 0.0)
    print(f"\n== Composant (temps CPU ; % du TOTAL de WeiDU, {total:.3f} s) ==")
    component = [(timings[f"step:{name}"], name) for name in COMPONENT_STEPS if f"step:{name}" in timings]
    for seconds, name in component:
        print(f"  {seconds:9.3f} s  {100 * seconds / total if total else 0:5.1f} %  {name}")
    if "step:loop" in timings:
        outside = timings["step:loop"] - loop["ITM"] - loop["SPL"]
        print(f"  {outside:9.3f} s  {100 * outside / total if total else 0:5.1f} %  "
              "loop hors des PATCH_TIME par ressource (lecture, écriture des fichiers)")
    if not component:
        print("  aucune étiquette de composant")

    print("\n== Étapes (durées inclusives ; % du temps de la boucle du même composant) ==")
    # Une exécution d'un seul composant : ses étapes sans contexte lui reviennent.
    single = "1" if loop["ITM"] and not loop["SPL"] else "0" if loop["SPL"] and not loop["ITM"] else None
    steps = []
    for label, seconds in timings.items():
        match = STEP.match(label)
        if not match or match.group(1) in COMPONENT_STEPS:
            continue
        name, item, subspell = match.groups()
        # Étapes propres à un composant : equipped/charged/combat (objets), spell_description (sorts).
        if item is None:
            item = single or ("0" if name == "spell_description" else "1")
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

    run = Path(args.debug_log).resolve().parent
    if (run / "console-times.txt").is_file():
        wall_report(run, resources, total)
    return 0


def read_options(run):
    options = {}
    path = run / "options.txt"
    if path.is_file():
        for line in path.read_text(encoding="utf-8").splitlines():
            name, _, value = line.partition(" = ")
            options[name] = value.removesuffix(" s")
    return options


def wall_report(run, resources, total):
    """Durée réelle (console horodatée par tools/run_install.py) face au temps CPU."""
    stamps = []
    for line in (run / "console-times.txt").read_text(encoding="utf-8").splitlines():
        seconds, _, text = line.partition("\t")
        stamps.append((float(seconds), text))
    end = stamps[-1][0]
    options = read_options(run)
    print("\n== Durée réelle et temps CPU du processus WeiDU ==")
    print(f"  {end:9.1f} s  durée réelle")
    if "cpu_user" in options:
        user, kernel = float(options["cpu_user"]), float(options["cpu_kernel"])
        print(f"  {user:9.1f} s  CPU utilisateur\n  {kernel:9.1f} s  CPU noyau (appels système : fichiers…)")
        print(f"  {end - user - kernel:9.1f} s  attente (durée réelle − CPU utilisateur − CPU noyau)")
    print(f"  {total:9.1f} s  TOTAL de WeiDU (CPU)")

    def first(pattern, after=0.0):
        return next((t for t, text in stamps if t >= after and re.search(pattern, text)), None)

    progress = [(int(m.group(1)), t) for t, text in stamps
                if (m := re.match(r"(\d+) (?:items|spells) processed$", text))]
    marks = [("lancement", 0.0), ("Installing", first(r"^Installing \[")),
             ("1re tranche de 100", progress[0][1] if progress else None),
             ("dernière tranche de 100", progress[-1][1] if progress else None),
             ("synthèse des opcodes", first(r"^Nouveau moteur : .* opcodes")),
             ("synthèse des événements", first(r"^Nouveau moteur : .* ressources")),
             ("bilan", first(r"^Reussis")), ("SUCCESSFULLY", first(r"SUCCESSFULLY INSTALLED")),
             ("fin du processus", end)]
    marks = [(name, t) for name, t in marks if t is not None]
    print("\n== Jalons de la console (durée réelle écoulée entre deux jalons) ==")
    for (name, t), (_, before) in zip(marks[1:], marks):
        print(f"  {t - before:9.1f} s  → {name} (à {t:.1f} s)")

    dump = next(run.glob("*-dump.txt"), None)
    if not progress or dump is None:
        return
    # Ordre de traitement : une ligne du dump par ressource parcourue.
    order = [line.split("\t", 1)[0].upper() for line in dump.read_text(encoding="utf-8", errors="replace").splitlines() if line.strip()]
    cpu = {label.rsplit(".", 1)[0].upper(): seconds for label, seconds in resources.items()}
    print("\n== Boucle par tranches de 1 000 ressources (durée réelle des jalons, CPU utilisateur des PATCH_TIME) ==")
    print("  ressources       réelle      CPU   réelle − CPU (noyau + attente)")
    previous_count, previous_time = 0, progress[0][1] - 0.0
    rows = []
    for count, t in progress:
        rows.append((previous_count, count, t - previous_time if previous_count else None,
                     sum(cpu.get(name, 0.0) for name in order[previous_count:count])))
        previous_count, previous_time = count, t
    for start in range(0, len(rows), 10):
        group = [row for row in rows[start:start + 10] if row[2] is not None]
        if not group:
            continue
        wall = sum(row[2] for row in group)
        work = sum(row[3] for row in group)
        print(f"  {group[0][0]:5d}-{group[-1][1]:<5d}  {wall:8.1f} {work:8.1f}  {wall - work:8.1f}")


if __name__ == "__main__":
    sys.exit(main())
