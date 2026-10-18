"""Contrôles statiques d'AutoDescription, sans jeu (feuille de route, §3.1 cible 5).

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

Usage : python tools/static_checks.py [--root DOSSIER] [--weidu CHEMIN | --no-parse]
Code de retour : 0 aucune erreur, 1 au moins une erreur (les avertissements et informations
ne changent pas le code de retour).
"""

import argparse
import collections
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = MOD = LIB = BGFORGE = SFO = TRA = OPCODES = None


def set_root(root):
    global ROOT, MOD, LIB, BGFORGE, SFO, TRA, OPCODES
    ROOT = root.resolve()
    MOD = ROOT / "AutoDescription"
    LIB = MOD / "lib"
    BGFORGE = LIB / "bgforge"
    SFO = MOD / "sfo"
    TRA = MOD / "tra"
    OPCODES = LIB / "itm" / "opcodes.tpp"

# Fichiers .tra convertis par HANDLE_CHARSETS : ils doivent être en Windows-1252 dans la copie
# de travail. Les autres (setup.tra, noconvert_array du tp2) sont lus tels quels.
CONVERTED_TRA = ("description.tra",)
VARIANTS = ("self", "target", "self_probability", "target_probability")
DEFINITION = re.compile(r"DEFINE_(PATCH|ACTION)_(MACRO|FUNCTION)\s+[~\"]?([A-Za-z0-9_#-]+)")
OPCODE_VARIANT = re.compile(r"^opcode_(self|target)(_probability)?_(\d+)$")


class Report:
    def __init__(self):
        self.counts = collections.Counter()

    def section(self, title):
        print(f"\n== {title} ==")

    def add(self, level, message):
        self.counts[level] += 1
        print(f"  [{level}] {message}")


def read_text(path):
    # Les sources mélangent UTF-8 et Windows-1252 : latin-1 lit tous les octets sans perte et
    # suffit pour analyser la syntaxe, qui est en ASCII.
    return path.read_bytes().decode("latin-1")


def strip_weidu(text):
    """Renvoie (texte sans commentaires, texte sans commentaires ni chaînes).

    Les positions sont conservées (remplacement par des espaces) pour pouvoir calculer les
    numéros de ligne.
    """
    no_comments = []
    code_only = []
    i = 0
    n = len(text)
    while i < n:
        if text.startswith("//", i):
            end = text.find("\n", i)
            end = n if end < 0 else end
            blank = re.sub(r"[^\n]", " ", text[i:end])
            no_comments.append(blank)
            code_only.append(blank)
            i = end
        elif text.startswith("/*", i):
            end = text.find("*/", i + 2)
            end = n if end < 0 else end + 2
            blank = re.sub(r"[^\n]", " ", text[i:end])
            no_comments.append(blank)
            code_only.append(blank)
            i = end
        elif text.startswith("~~~~~", i) or text[i] in "~\"":
            delimiter = "~~~~~" if text.startswith("~~~~~", i) else text[i]
            end = text.find(delimiter, i + len(delimiter))
            end = n if end < 0 else end + len(delimiter)
            no_comments.append(text[i:end])
            code_only.append(re.sub(r"[^\n]", " ", text[i:end]))
            i = end
        else:
            no_comments.append(text[i])
            code_only.append(text[i])
            i += 1
    return "".join(no_comments), "".join(code_only)


def line_of(text, position):
    return text.count("\n", 0, position) + 1


def relative(path):
    return path.relative_to(ROOT).as_posix()


def weidu_files():
    files = [MOD / "AutoDescription.tp2"]
    for pattern in ("*.tpa", "*.tpp"):
        files += sorted(MOD.rglob(pattern))
    return files


# ---------------------------------------------------------------------------------------------
# Traductions


def parse_tra(path):
    """Renvoie la liste [(identifiant, ligne)] des entrées d'un fichier .tra."""
    text, _ = strip_weidu(read_text(path))
    entries = []
    for match in re.finditer(r"@(-?\d+)\s*=\s*(?:~~~~~.*?~~~~~|~[^~]*~|\"[^\"]*\")", text, re.S):
        entries.append((int(match.group(1)), line_of(text, match.start())))
    return entries


def check_tra(report):
    report.section("Fichiers .tra : encodage, doublons")
    ids = {}
    for language in ("french", "english"):
        for path in sorted((TRA / language).glob("*.tra")):
            raw = path.read_bytes()
            if raw.startswith(b"\xef\xbb\xbf"):
                report.add("ERREUR", f"{relative(path)} : commence par un BOM UTF-8 (WeiDU refuse le fichier)")
            if path.name in CONVERTED_TRA and any(b > 0x7F for b in raw):
                try:
                    raw.decode("utf-8")
                    report.add("ERREUR", f"{relative(path)} : contenu UTF-8 au lieu de Windows-1252 "
                               "(copie produite sans .gitattributes, ex. git archive ?)")
                except UnicodeDecodeError:
                    pass
            entries = parse_tra(path)
            counter = collections.Counter(identifier for identifier, _ in entries)
            for identifier, count in sorted(counter.items()):
                if count > 1:
                    lines = ", ".join(str(line) for i, line in entries if i == identifier)
                    report.add("ERREUR", f"{relative(path)} : @{identifier} défini {count} fois (lignes {lines})")
            ids[(language, path.name)] = set(counter)
            print(f"  {relative(path)} : {len(counter)} identifiants")

    report.section("Fichiers .tra : français / anglais")
    for name in sorted({name for _, name in ids}):
        french = ids.get(("french", name), set())
        english = ids.get(("english", name), set())
        only_english = sorted(english - french)
        only_french = sorted(french - english)
        if only_english:
            report.add("AVERTISSEMENT", f"{name} : {len(only_english)} identifiants seulement en anglais : "
                       + " ".join(f"@{i}" for i in only_english))
        if only_french:
            # Repli de l'anglais sur le français : décision du mainteneur (TRA-002).
            report.add("INFO", f"{name} : {len(only_french)} identifiants seulement en français (repli) : "
                       + " ".join(f"@{i}" for i in only_french))
    return ids


def check_tra_references(report, ids):
    report.section("Références @n littérales absentes des .tra français")
    french = ids.get(("french", "description.tra"), set()) | ids.get(("french", "setup.tra"), set())
    sources = [path for path in weidu_files() if BGFORGE not in path.parents and SFO not in path.parents]
    references = 0
    for path in sources:
        _, code = strip_weidu(read_text(path))
        for match in re.finditer(r"@(-?\d+)\b", code):
            references += 1
            identifier = int(match.group(1))
            if identifier not in french:
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : @{identifier} absent")
    # Les identifiants calculés (10000000 + parameter2, strref = 13269382…) échappent à ce contrôle.
    print(f"  {references} références littérales examinées (hors commentaires et chaînes)")


# ---------------------------------------------------------------------------------------------
# Définitions de macros et de fonctions


def collect_definitions(paths):
    definitions = collections.defaultdict(list)
    for path in paths:
        text, _ = strip_weidu(read_text(path))
        for match in DEFINITION.finditer(text):
            key = (match.group(1), match.group(2), match.group(3))
            definitions[key].append(f"{relative(path)}:{line_of(text, match.start())}")
    return definitions


def check_duplicate_definitions(report):
    report.section("Macros et fonctions définies plusieurs fois (lib/, lib/bgforge/, sfo/)")
    # WeiDU garde silencieusement la dernière définition (ordre d'inclusion).
    definitions = collect_definitions(weidu_files())
    for (context, kind, name), places in sorted(definitions.items()):
        if len(places) > 1:
            third_party_only = all(p.startswith(("AutoDescription/lib/bgforge/", "AutoDescription/sfo/")) for p in places)
            # Un doublon interne aux bibliothèques tierces ne concerne le mod que s'il les appelle.
            level = "AVERTISSEMENT" if third_party_only else "ERREUR"
            report.add(level, f"{context}_{kind} {name} : " + ", ".join(places))
    return definitions


def check_opcode_variants(report, definitions):
    report.section("Variantes des macros de description d'opcode")
    variants = collections.defaultdict(set)
    for (context, kind, name), places in definitions.items():
        match = OPCODE_VARIANT.match(name)
        if context == "PATCH" and kind == "MACRO" and match and not any("lib/bgforge/" in p or "sfo/" in p for p in places):
            variant = match.group(1) + (match.group(2) or "")
            variants[int(match.group(3))].add(variant)
    missing = collections.defaultdict(list)
    for opcode, present in sorted(variants.items()):
        for variant in VARIANTS:
            if variant not in present:
                missing[variant].append(opcode)
    # Certaines absences sont sans doute légitimes (effet toujours sur soi…) mais rien ne les
    # documente : une combinaison non prévue fait échouer get_effect_description (RISK-005).
    for variant in VARIANTS:
        if missing[variant]:
            report.add("AVERTISSEMENT", f"opcode_{variant}_N absente pour {len(missing[variant])} opcodes : "
                       + " ".join(str(o) for o in missing[variant]))
    print(f"  {len(variants)} opcodes ont au moins une variante")
    return variants


def parse_ignored_opcodes():
    text, _ = strip_weidu(read_text(OPCODES))
    block = re.search(r"ACTION_DEFINE_ASSOCIATIVE_ARRAY\s+~ignored_opcodes~\s+BEGIN(.*?)\bEND\b", text, re.S)
    if not block:
        return None
    return {int(key): int(value) for key, value in re.findall(r"(-?\d+)\s*=>\s*(-?\d+)", block.group(1))}


def check_ignored_described(report, variants):
    report.section("Opcodes ignorés mais décrits")
    ignored = parse_ignored_opcodes()
    if ignored is None:
        report.add("ERREUR", f"{relative(OPCODES)} : table ignored_opcodes introuvable")
        return
    # Un opcode ignoré n'est jamais décrit : ses macros de description sont du code mort.
    for opcode in sorted(set(ignored) & set(variants)):
        report.add("AVERTISSEMENT", f"opcode {opcode} : dans ignored_opcodes (valeur {ignored[opcode]}) "
                   f"et décrit par {', '.join(sorted('opcode_' + v + '_' + str(opcode) for v in variants[opcode]))}")
    print(f"  {len(ignored)} entrées dans ignored_opcodes")


# ---------------------------------------------------------------------------------------------
# Analyse syntaxique WeiDU


def check_parse(report, weidu):
    report.section("Analyse syntaxique WeiDU")
    files = [(path, "TP2" if path.suffix == ".tp2" else "TPA") for path in weidu_files()]
    files.append((MOD / "settings-default.ini", "TPP"))
    with tempfile.TemporaryDirectory() as directory:
        # WeiDU écrit ses journaux dans le dossier courant : jamais dans le dépôt.
        executable = Path(directory) / "weidu.exe"
        shutil.copy(weidu, executable)
        for path, kind in files:
            kinds = (kind, "TPP") if kind == "TPA" else (kind,)
            for attempt in kinds:
                # Certains fichiers BGforge ne contiennent que des instructions de patch : TPP.
                result = subprocess.run(
                    [str(executable), "--noautoupdate", "--nogame", "--parse-check", attempt, str(path)],
                    cwd=directory, capture_output=True, text=True, errors="replace",
                )
                # L'échec s'écrit « was NOT successfully parsed » : tester aussi le code de retour.
                if result.returncode == 0 and "was successfully parsed" in result.stdout + result.stderr:
                    break
            else:
                last = (result.stdout + result.stderr).strip().splitlines()[-1:]
                report.add("ERREUR", f"{relative(path)} : analyse échouée ({' '.join(last)})")
    print(f"  {len(files)} fichiers analysés")


def main():
    parser = argparse.ArgumentParser(description="Contrôles statiques d'AutoDescription.")
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parent.parent,
                        help="dossier contenant AutoDescription/ (défaut : le dépôt)")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--weidu", type=Path,
                       help="exécutable WeiDU (défaut : setup-AutoDescription.exe à la racine)")
    group.add_argument("--no-parse", action="store_true", help="ne pas lancer l'analyse syntaxique WeiDU")
    args = parser.parse_args()
    set_root(args.root)
    weidu = args.weidu or ROOT / "setup-AutoDescription.exe"
    # Sous Windows, une sortie redirigée utilise sinon l'encodage local (cp1252).
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    report = Report()
    ids = check_tra(report)
    check_tra_references(report, ids)
    definitions = check_duplicate_definitions(report)
    variants = check_opcode_variants(report, definitions)
    check_ignored_described(report, variants)
    if not args.no_parse:
        if weidu.is_file():
            check_parse(report, weidu)
        else:
            report.add("ERREUR", f"WeiDU introuvable : {weidu} (utiliser --weidu ou --no-parse)")

    print(f"\nBilan : {report.counts['ERREUR']} erreurs, {report.counts['AVERTISSEMENT']} avertissements, "
          f"{report.counts['INFO']} informations")
    return 1 if report.counts["ERREUR"] else 0


if __name__ == "__main__":
    sys.exit(main())
