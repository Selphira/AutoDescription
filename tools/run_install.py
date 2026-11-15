"""Installe AutoDescription sur l'installation de test et range les journaux de l'exécution.

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

Le mod du dépôt est copié dans <jeu>/AutoDescription (lib, tra, 2da, tp2,
settings-default.ini, gabarits des journaux). Les options demandées sont imposées dans la copie
du tp2, après la lecture de settings.ini (qui prime sur settings-default.ini et n'est jamais
modifié). --only restreint la boucle des objets et des sorts aux ressources voulues, dans la copie
seulement (jamais dans le dépôt). Les composants 15 et 10 sont d'abord désinstallés : une
réinstallation garderait la langue enregistrée dans WeiDU.log (V27).

Usage :
  python tools/run_install.py --game DOSSIER --component 15 --label essai
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
MOD_DIRECTORIES = ("lib", "tra", "2da")
LOG_PATTERNS = ("*.log", "*-diff.html", "*-dump.txt", "*-compare.txt", "*-effects.txt", "*-opcodes.txt",
                "*-recursion.txt", "*-events.txt", "*-cache.txt", "*.md", "*.part")
# Fichier des boucles complètes sur les objets et les sorts.
LOOPS = "lib/install.tpp"
# Ligne du tp2 qui suit la lecture de settings.ini : les options imposées sont insérées avant.
SETTINGS_END = "\tOUTER_SPRINT CACHE_FOLDER"


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
    # re.escape protège aussi « # » (L#NSSEE), que l'expression régulière de WeiDU ne reconnaît plus.
    pattern = "\\(" + "\\|".join(re.sub(r"([.*+?^$\[\]\\])", r"\\\1", resource) for resource in resources) + "\\)"
    path = target / LOOPS
    text = path.read_bytes().decode("utf-8")
    for extension in ("itm", "spl"):
        loop = f"COPY_EXISTING_REGEXP GLOB ~^.+\\.{extension}$~ ~override~"
        if text.count(loop) != 1:
            raise SystemExit(f"ERREUR : {path} : boucle complète des .{extension} introuvable")
        text = text.replace(loop, f"COPY_EXISTING_REGEXP GLOB ~^{pattern}\\.{extension}$~ ~override~")
    path.write_bytes(text.encode("utf-8"))


def process_cpu_times(process):
    """Temps CPU utilisateur et noyau (s) d'un processus terminé, None hors Windows.

    Les durées de WeiDU (PATCH_TIME, ACTION_TIME, TOTAL du .DEBUG) sont du temps CPU : l'écart avec
    la durée réelle est du temps d'attente (disque, antivirus…)."""
    if os.name != "nt":
        return None
    import ctypes
    from ctypes import wintypes
    times = [wintypes.FILETIME() for _ in range(4)]
    handle = wintypes.HANDLE(int(process._handle))
    if not ctypes.windll.kernel32.GetProcessTimes(handle, *[ctypes.byref(t) for t in times]):
        return None
    seconds = [((t.dwHighDateTime << 32) + t.dwLowDateTime) / 1e7 for t in times[2:]]
    return seconds[1], seconds[0]


def process_counters(process):
    """Compteurs d'entrées-sorties et de mémoire d'un processus terminé (Windows), pour savoir d'où
    vient le temps CPU noyau : appels de lecture/écriture, ou défauts de page."""
    if os.name != "nt":
        return {}
    import ctypes
    from ctypes import wintypes

    class IoCounters(ctypes.Structure):
        _fields_ = [(name, ctypes.c_ulonglong) for name in
                    ("reads", "writes", "others", "read_bytes", "write_bytes", "other_bytes")]

    class MemoryCounters(ctypes.Structure):
        _fields_ = [("cb", wintypes.DWORD), ("page_faults", wintypes.DWORD)] + [
            (name, ctypes.c_size_t) for name in ("peak_working_set", "working_set", "peak_paged", "paged",
                                                  "peak_nonpaged", "nonpaged", "pagefile", "peak_pagefile")]

    handle = wintypes.HANDLE(int(process._handle))
    counters = {}
    io = IoCounters()
    if ctypes.windll.kernel32.GetProcessIoCounters(handle, ctypes.byref(io)):
        counters.update(io_reads=io.reads, io_writes=io.writes, io_others=io.others,
                        io_read_mb=io.read_bytes >> 20, io_write_mb=io.write_bytes >> 20)
    memory = MemoryCounters()
    memory.cb = ctypes.sizeof(memory)
    if ctypes.windll.psapi.GetProcessMemoryInfo(handle, ctypes.byref(memory), memory.cb):
        counters.update(page_faults=memory.page_faults, peak_working_set_mb=memory.peak_working_set >> 20)
    return counters


def setup(game, arguments, console):
    """Lance WeiDU ; la console est recopiée telle quelle et horodatée (durée réelle depuis le
    lancement) dans <console>-times.txt. Renvoie le code de retour et les temps CPU."""
    executable = game / "setup-autodescription.exe"
    start = time.monotonic()
    timed = console.with_name(console.stem + "-times.txt")
    with open(console, "ab") as output, open(timed, "a", encoding="utf-8") as stamps:
        process = subprocess.Popen([str(executable), "--noautoupdate", "--no-exit-pause"] + arguments,
                                   cwd=game, stdin=subprocess.DEVNULL, stdout=subprocess.PIPE,
                                   stderr=subprocess.STDOUT)
        for line in process.stdout:
            output.write(line)
            stamps.write(f"{time.monotonic() - start:9.2f}\t{line.decode('utf-8', errors='replace').rstrip()}\n")
        process.wait()
        stamps.write(f"{time.monotonic() - start:9.2f}\t(fin du processus)\n")
        cpu = process_cpu_times(process)
        counters = process_counters(process)
    return process.returncode, cpu, counters


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--game", type=Path, default=os.environ.get("AD_TEST_GAME"))
    parser.add_argument("--component", type=int, choices=(10, 15), required=True)
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

    options = {"regression_dump": int(args.dump)}
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
    start = time.monotonic()
    setup(args.game, language + ["--force-uninstall", "15", "--force-uninstall", "10"], run / "uninstall.txt")
    uninstall = time.monotonic() - start
    for pattern in LOG_PATTERNS:
        for path in (target / "log").glob(pattern):
            path.unlink()
    for pattern in ("*-all-*.js", "*-all-*.js.*.part"):
        for path in (args.game / "docs" / "data").glob(pattern):
            path.unlink()
    start = time.monotonic()
    code, cpu, counters = setup(args.game, language + ["--force-install", str(args.component)], console)
    duration = time.monotonic() - start
    cpu_lines = f"cpu_user = {cpu[0]:.1f} s\ncpu_kernel = {cpu[1]:.1f} s\n" if cpu else ""
    cpu_lines += "".join(f"{name} = {value}\n" for name, value in counters.items())

    for pattern in LOG_PATTERNS:
        for path in (target / "log").glob(pattern):
            shutil.copy2(path, run / path.name)
    for path in (args.game / "docs" / "data").glob("*-all-*.js"):
        shutil.copy2(path, run / path.name)
    shutil.copy2(args.game / "SETUP-AUTODESCRIPTION.DEBUG", run / "SETUP-AUTODESCRIPTION.DEBUG")
    (run / "options.txt").write_text(
        "".join(f"{name} = {value}\n" for name, value in options.items())
        + f"component = {args.component}\nlanguage = {args.language}\nonly = {' '.join(resources)}\n"
        + f"duration = {duration:.0f} s\n{cpu_lines}uninstall = {uninstall:.0f} s\nexit = {code}\n", encoding="utf-8")

    text = console.read_bytes().decode("utf-8", errors="replace")
    print(f"== {args.label} : composant {args.component}, langue {args.language}, "
          f"{len(resources) or 'toutes les'} ressources, {duration:.0f} s, code {code}")
    for line in text.splitlines():
        if re.match(r"\s*(Reussis|Echoues|Ignores|Non couverts|Nouveau moteur :)|ERROR|FATAL", line):
            print("  " + line.strip())
    print(f"  journaux : {run}")
    return 0 if code == 0 and "SUCCESSFULLY INSTALLED" in text else 1


if __name__ == "__main__":
    sys.exit(main())
