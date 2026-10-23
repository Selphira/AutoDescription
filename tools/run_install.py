"""Installe AutoDescription sur l'installation de test et range les journaux de l'exécution.

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

Le mod du dépôt est copié dans <jeu>/AutoDescription (lib, new-lib, tra, sfo, 2da, tp2,
settings-default.ini, gabarits des journaux). Les options demandées sont imposées dans la copie
du tp2, après la lecture de settings.ini (qui prime sur settings-default.ini et n'est jamais
modifié). --only restreint la boucle des objets et des sorts aux ressources voulues, dans la copie
seulement (jamais dans le dépôt). Les composants 15 et 10 sont d'abord désinstallés : une
réinstallation garderait la langue enregistrée dans WeiDU.log (V27).

Usage :
  python tools/run_install.py --game DOSSIER --component 15 --mode 2 --label essai
      [--language 0|1] [--only RESREF ...] [--only-file LISTE] [--dump]
      [--set NOM=VALEUR ...] [--out DOSSIER]
Le dossier du jeu peut aussi être donné par la variable d'environnement AD_TEST_GAME, le dossier
des exécutions par AD_TEST_RUNS (défaut : <temp>/autodescription-runs). Code de retour : 0 si
l'installation a réussi, 1 sinon.
"""

import argparse
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

REPOSITORY = Path(__file__).resolve().parent.parent
MOD = REPOSITORY / "AutoDescription"
MOD_DIRECTORIES = ("lib", "new-lib", "tra", "sfo", "2da")
LOG_PATTERNS = ("*.log", "*-diff.html", "*-dump.txt", "*-compare.txt", "*-effects.txt", "*-opcodes.txt",
                "*-recursion.txt", "*-events.txt", "*.md")
LOOPS = {"lib/itm.tpp": "itm", "lib/spl.tpp": "spl"}
# Ligne du tp2 qui suit la lecture de settings.ini : les options imposées sont insérées avant.
SETTINGS_END = "\tACTION_IF description_engine < 0 OR description_engine > 3 BEGIN"


def copy_mod(target):
    for name in MOD_DIRECTORIES:
        shutil.rmtree(target / name, ignore_errors=True)
        if (MOD / name).is_dir():
            shutil.copytree(MOD / name, target / name)
    for name in ("AutoDescription.tp2", "settings-default.ini"):
        shutil.copy2(MOD / name, target / name)
    (target / "log").mkdir(exist_ok=True)
    for name in ("template.html", "template_ee.html"):
        shutil.copy2(MOD / "log" / name, target / "log" / name)


def impose_options(tp2, options):
    text = tp2.read_bytes().decode("utf-8")
    newline = "\r\n" if "\r\n" in text else "\n"
    if text.count(SETTINGS_END) != 1:
        raise SystemExit(f"ERREUR : {tp2} : fin de la lecture des options introuvable")
    lines = "".join(f"\tOUTER_SET {name} = {value}{newline}" for name, value in options.items())
    tp2.write_bytes(text.replace(SETTINGS_END, lines + SETTINGS_END).encode("utf-8"))


def restrict_loops(target, resources):
    pattern = "\\(" + "\\|".join(re.escape(resource) for resource in resources) + "\\)"
    for relative, extension in LOOPS.items():
        path = target / relative
        text = path.read_bytes().decode("utf-8")
        loop = f"COPY_EXISTING_REGEXP GLOB ~^.+\\.{extension}$~ ~override~"
        if text.count(loop) != 1:
            raise SystemExit(f"ERREUR : {path} : boucle complète introuvable")
        path.write_bytes(text.replace(loop, f"COPY_EXISTING_REGEXP GLOB ~^{pattern}\\.{extension}$~ ~override~").encode("utf-8"))


def setup(game, arguments, console):
    executable = game / "setup-autodescription.exe"
    with open(console, "ab") as output:
        result = subprocess.run([str(executable), "--noautoupdate", "--no-exit-pause"] + arguments,
                                cwd=game, stdin=subprocess.DEVNULL, stdout=output, stderr=subprocess.STDOUT)
    return result.returncode


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--game", type=Path, default=os.environ.get("AD_TEST_GAME"))
    parser.add_argument("--component", type=int, choices=(10, 15), required=True)
    parser.add_argument("--mode", type=int, choices=(0, 1, 2, 3), required=True, help="description_engine")
    parser.add_argument("--label", required=True)
    parser.add_argument("--language", type=int, choices=(0, 1), default=0, help="0 français, 1 anglais")
    parser.add_argument("--only", nargs="+", default=[], help="ressources traitées (sans extension)")
    parser.add_argument("--only-file", type=Path, help="fichier d'une ressource par ligne (# : commentaire)")
    parser.add_argument("--dump", action="store_true", help="regression_dump = 1")
    parser.add_argument("--set", nargs="+", default=[], metavar="NOM=VALEUR", help="options imposées")
    parser.add_argument("--out", type=Path,
                        default=Path(os.environ.get("AD_TEST_RUNS", Path(tempfile.gettempdir()) / "autodescription-runs")))
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    if args.game is None or not (args.game / "setup-autodescription.exe").is_file():
        raise SystemExit("ERREUR : dossier du jeu absent ou sans setup-autodescription.exe (--game ou AD_TEST_GAME)")

    options = {"description_engine": args.mode, "regression_dump": int(args.dump)}
    for pair in args.set:
        name, _, value = pair.partition("=")
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", name) or not re.fullmatch(r"-?\d+", value):
            raise SystemExit(f"ERREUR : option invalide : {pair}")
        options[name] = value
    resources = list(args.only)
    if args.only_file:
        for line in args.only_file.read_text(encoding="utf-8").splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                resources.append(line)

    target = args.game / "AutoDescription"
    copy_mod(target)
    impose_options(target / "AutoDescription.tp2", options)
    if resources:
        restrict_loops(target, resources)

    run = args.out / args.label
    shutil.rmtree(run, ignore_errors=True)
    run.mkdir(parents=True)
    console = run / "console.txt"
    language = ["--language", str(args.language)]
    setup(args.game, language + ["--force-uninstall", "15", "--force-uninstall", "10"], run / "uninstall.txt")
    for pattern in LOG_PATTERNS:
        for path in (target / "log").glob(pattern):
            path.unlink()
    for path in (args.game / "docs" / "data").glob("*-all-*.js"):
        path.unlink()
    start = time.monotonic()
    code = setup(args.game, language + ["--force-install", str(args.component)], console)
    duration = time.monotonic() - start

    for pattern in LOG_PATTERNS:
        for path in (target / "log").glob(pattern):
            shutil.copy2(path, run / path.name)
    shutil.copy2(args.game / "SETUP-AUTODESCRIPTION.DEBUG", run / "SETUP-AUTODESCRIPTION.DEBUG")
    (run / "options.txt").write_text(
        "".join(f"{name} = {value}\n" for name, value in options.items())
        + f"component = {args.component}\nlanguage = {args.language}\nonly = {' '.join(resources)}\n"
        + f"duration = {duration:.0f} s\nexit = {code}\n", encoding="utf-8")

    text = console.read_bytes().decode("utf-8", errors="replace")
    print(f"== {args.label} : composant {args.component}, mode {args.mode}, langue {args.language}, "
          f"{len(resources) or 'toutes les'} ressources, {duration:.0f} s, code {code}")
    for line in text.splitlines():
        if re.match(r"\s*(Reussis|Echoues|Identiques|Differents|Non couverts|Nouveau moteur :)|ERROR|FATAL", line):
            print("  " + line.strip())
    print(f"  journaux : {run}")
    return 0 if code == 0 and "SUCCESSFULLY INSTALLED" in text else 1


if __name__ == "__main__":
    sys.exit(main())
