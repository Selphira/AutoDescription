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

ROOT = MOD = LIB = NEW_LIB = BGFORGE = SFO = TRA = OPCODES = None


def set_root(root):
    global ROOT, MOD, LIB, NEW_LIB, BGFORGE, SFO, TRA, OPCODES
    ROOT = root.resolve()
    MOD = ROOT / "AutoDescription"
    LIB = MOD / "lib"
    NEW_LIB = MOD / "new-lib"
    BGFORGE = LIB / "bgforge"
    SFO = MOD / "sfo"
    TRA = MOD / "tra"
    OPCODES = LIB / "itm" / "opcodes.tpp"

# Fichiers .tra de l'ancien moteur convertis par HANDLE_CHARSETS : en Windows-1252 dans le dépôt.
# Le nouveau fichier est en UTF-8 (converti en sens inverse) ; setup.tra est lu tel quel.
CONVERTED_TRA = ("description.tra",)
NEW_TRA = "description_new.tra"
NEW_TRA_RANGES = ((1_000_000, 9_999_999), (20_000_000, 39_999_999))
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


def parse_tra(text):
    """Renvoie la liste [(identifiant, ligne, texte)] des entrées d'un contenu .tra."""
    code, _ = strip_weidu(text)
    entries = []
    for match in re.finditer(r"@(-?\d+)\s*=\s*(~~~~~.*?~~~~~|~[^~]*~|\"[^\"]*\")", code, re.S):
        delimiter = 5 if match.group(2).startswith("~~~~~") else 1
        entries.append((int(match.group(1)), line_of(code, match.start()), match.group(2)[delimiter:-delimiter]))
    return entries


def in_new_ranges(identifier):
    return any(low <= identifier <= high for low, high in NEW_TRA_RANGES)


def git_index_content(path):
    """Contenu indexé par Git (ce qu'une extraction propre ou la CI produirait), ou None."""
    try:
        result = subprocess.run(["git", "show", f":{relative(path)}"], cwd=ROOT, capture_output=True)
    except OSError:
        return None
    return result.stdout if result.returncode == 0 else None


def check_tra_encoding(report, where, name, raw):
    if raw.startswith(b"\xef\xbb\xbf"):
        report.add("ERREUR", f"{where} : commence par un BOM UTF-8 (WeiDU refuse le fichier)")
    if name in CONVERTED_TRA and any(b > 0x7F for b in raw):
        try:
            raw.decode("utf-8")
            report.add("ERREUR", f"{where} : contenu UTF-8 au lieu de Windows-1252 "
                       "(HANDLE_CHARSETS le convertirait une seconde fois sur EE)")
        except UnicodeDecodeError:
            pass
    if name == NEW_TRA:
        try:
            text = raw.decode("utf-8")
        except UnicodeDecodeError:
            report.add("ERREUR", f"{where} : contenu non UTF-8 (le nouveau fichier doit être en UTF-8)")
            return
        # iconv -c supprime sans message les caractères absents de Windows-1252 (jeux classiques).
        for identifier, line, string in parse_tra(text):
            missing = sorted({char for char in string if char.encode("cp1252", errors="ignore") == b""})
            if missing:
                report.add("ERREUR", f"{where}:{line} : @{identifier} contient des caractères absents de "
                           f"Windows-1252 : {' '.join(missing)}")


def check_tra(report):
    report.section("Fichiers .tra : encodage, doublons, plages")
    ids = {}
    for language in ("french", "english"):
        for path in sorted((TRA / language).glob("*.tra")):
            raw = path.read_bytes()
            check_tra_encoding(report, relative(path), path.name, raw)
            indexed = git_index_content(path)
            if indexed is not None and indexed.replace(b"\r\n", b"\n") != raw.replace(b"\r\n", b"\n"):
                check_tra_encoding(report, f"{relative(path)} (version indexée par Git)", path.name, indexed)
            entries = parse_tra(raw.decode("latin-1"))
            counter = collections.Counter(identifier for identifier, _, _ in entries)
            for identifier, count in sorted(counter.items()):
                if count > 1:
                    lines = ", ".join(str(line) for i, line, _ in entries if i == identifier)
                    report.add("ERREUR", f"{relative(path)} : @{identifier} défini {count} fois (lignes {lines})")
            # Plages disjointes : les deux fichiers sont chargés ensemble par LANGUAGE (§3.12).
            for identifier in sorted(counter):
                if (path.name == NEW_TRA) != in_new_ranges(identifier):
                    expected = "dans les" if path.name == NEW_TRA else "hors des"
                    report.add("ERREUR", f"{relative(path)} : @{identifier} doit être {expected} plages "
                               "du nouveau moteur (1 000 000-9 999 999, 20 000 000-39 999 999)")
            ids[(language, path.name)] = set(counter)
            print(f"  {relative(path)} : {len(counter)} identifiants")
    french_new = ids.get(("french", NEW_TRA), set())
    english_new = ids.get(("english", NEW_TRA), set())
    if french_new != english_new:
        # Pour le nouveau fichier, le repli sur le français n'est pas admis (contrôle bloquant).
        report.add("ERREUR", f"{NEW_TRA} : identifiants différents en français et en anglais : "
                   + " ".join(f"@{i}" for i in sorted(french_new ^ english_new)))

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
    old = ids.get(("french", "description.tra"), set()) | ids.get(("french", "setup.tra"), set())
    new = ids.get(("french", NEW_TRA), set())
    sources = [path for path in weidu_files() if BGFORGE not in path.parents and SFO not in path.parents]
    references = 0
    for path in sources:
        # Chaque moteur n'utilise que son fichier de chaînes.
        own, name = (new, NEW_TRA) if NEW_LIB in path.parents else (old, "description.tra/setup.tra")
        _, code = strip_weidu(read_text(path))
        for match in re.finditer(r"@(-?\d+)\b", code):
            references += 1
            identifier = int(match.group(1))
            if identifier not in own:
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : @{identifier} absent de {name}")
    # Les identifiants calculés (10000000 + parameter2, strref = 13269382…) échappent à ce contrôle.
    print(f"  {references} références littérales examinées (hors commentaires et chaînes)")


NEW_ENTRY = re.compile(r"^@(\d+)\s*=\s*~([^~]*)~([^\n]*)", re.M)
COPY_MARKER = re.compile(r"//\s*reprise de @(\d+)")
# Fichiers du nouveau moteur où les globales en majuscules sont fixées.
NEW_STARTUP_FILES = ("always.tpa", "startup.tpa", "catalog.tpa")
# Variables de mise en forme de l'ancien moteur et leur équivalent dans le nouveau, pour les
# chaînes reprises ; l'ancien nom est interdit dans description_new.tra.
OLD_TO_NEW_VARIABLES = {"crlf": "CRLF", "colon": "AD_COLON", "semicolon": "AD_SEMICOLON", "outer_percent": "PERCENT"}
OLD_GLOBALS = set(OLD_TO_NEW_VARIABLES) | {"meter", "meters"}


def check_new_tra_rules(report):
    report.section(f"Règles propres à {NEW_TRA} et aux références de new-lib/")
    texts = {}
    for language in ("french", "english"):
        new = (TRA / language / NEW_TRA).read_bytes().decode("utf-8", errors="replace").replace("\r\n", "\n")
        old_path = TRA / language / "description.tra"
        old = {int(i): t for i, t, _ in NEW_ENTRY.findall(old_path.read_bytes().decode("cp1252", errors="replace").replace("\r\n", "\n"))}
        entries = [(int(i), t, rest, line_of(new, m.start())) for m in NEW_ENTRY.finditer(new)
                   for i, t, rest in [m.groups()]]
        order = [i for i, _, _, _ in entries]
        if order != sorted(order):
            report.add("ERREUR", f"{relative(TRA / language / NEW_TRA)} : identifiants non triés")
        texts[language] = ({i: t for i, t, _, _ in entries}, order)
        copies = 0
        for identifier, text, rest, line in entries:
            marker = COPY_MARKER.search(rest)
            if marker:
                copies += 1
                source = int(marker.group(1))
                # Recopie à l'identique, au renommage près des variables de l'ancien moteur ; une
                # reformulation est un changement distinct, à signaler.
                expected = old.get(source)
                for old_name, new_name in OLD_TO_NEW_VARIABLES.items():
                    expected = expected.replace(f"%{old_name}%", f"%{new_name}%") if expected is not None else None
                if expected != text:
                    report.add("ERREUR", f"{relative(TRA / language / NEW_TRA)}:{line} : @{identifier} diffère de "
                               f"@{source} de description.tra (« reprise de »)")
            # Le gabarit lirait la variable de l'ancien moteur (une fonction voit celles de son appelant).
            for variable in sorted(set(re.findall(r"%([A-Za-z_][A-Za-z0-9_]*)%", text)) & OLD_GLOBALS):
                report.add("ERREUR", f"{relative(TRA / language / NEW_TRA)}:{line} : @{identifier} utilise la "
                           f"variable {variable} de l'ancien moteur")
        print(f"  {relative(TRA / language / NEW_TRA)} : {len(entries)} entrées, dont {copies} reprises")
    if texts.get("french", (None, []))[1] != texts.get("english", (None, []))[1]:
        report.add("ERREUR", f"{NEW_TRA} : identifiants dans un ordre différent en français et en anglais")

    french = texts.get("french", ({}, []))[0]
    for path in sorted(p for p in weidu_files() if NEW_LIB in p.parents):
        raw = read_text(path)
        _, code = strip_weidu(raw)
        lines = raw.split("\n")
        for match in re.finditer(r"@(\d+)\b", code):
            identifier = int(match.group(1))
            line = line_of(code, match.start())
            comment = lines[line - 1].partition("//")[2]
            # Règle du dépôt : chaque référence est suivie de son texte français en commentaire.
            if not comment.strip():
                report.add("ERREUR", f"{relative(path)}:{line} : @{identifier} sans commentaire du texte français")
                continue
            quoted = re.match(r"\s*~(.*)~\s*$", comment.rstrip("\r"))
            expected = french.get(identifier, "").encode("utf-8").decode("latin-1")
            if quoted and identifier in french and quoted.group(1) != expected:
                report.add("ERREUR", f"{relative(path)}:{line} : commentaire de @{identifier} différent du texte "
                           "français")
        # Majuscules = globale fixée au démarrage, jamais modifiée pendant le traitement.
        if path.name not in NEW_STARTUP_FILES:
            for match in re.finditer(r"\b(?:OUTER_)?(?:SET|SPRINT|TEXT_SPRINT)[ \t]+([A-Z][A-Z0-9_]*)\b", code):
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : affectation de la globale "
                           f"{match.group(1)} hors des fichiers de démarrage")


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


def parse_sort_opcodes():
    text, _ = strip_weidu(read_text(OPCODES))
    block = re.search(r"ACTION_DEFINE_ASSOCIATIVE_ARRAY\s+~sort_opcodes~\s+BEGIN(.*?)\bEND\b", text, re.S)
    if not block:
        return None
    return {int(key): int(value) for key, value in re.findall(r"(-?\d+)\s*=>\s*(-?\d+)", block.group(1))}


def parse_opcode_table(name):
    text, _ = strip_weidu(read_text(OPCODES))
    block = re.search(r"ACTION_DEFINE_ASSOCIATIVE_ARRAY\s+~" + name + r"~\s+BEGIN(.*?)\bEND\b", text, re.S)
    return {int(key) for key in re.findall(r"(-?\d+)\s*=>", block.group(1))} if block else set()


def old_duration_kinds():
    """Colonne DURATION attendue d'après les listes de l'ancien moteur (la première qui contient l'opcode)."""
    kinds = {}
    for opcode in parse_opcode_table("opcodes_cant_be_permanent_after_death"):
        kinds[opcode] = "NOT_AFTER_DEATH"
    for opcode in parse_opcode_table("opcodes_cant_be_permanent"):
        kinds[opcode] = "NOT_PERMANENT"
    for opcode in OLD_HIDDEN_DURATION:
        kinds[opcode] = "HIDDEN"
    for opcode in parse_opcode_table("opcodes_ignore_duration"):
        kinds[opcode] = "IGNORED"
    return kinds


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
# Catalogue des opcodes du nouveau moteur

CATALOG_STATUSES = ("DESCRIBED", "IGNORED", "TODO")
CATALOG_DICE = ("LEVEL", "DICE", "DICE_IF_P2_1_EE")
CATALOG_DURATIONS = ("SHOWN", "IGNORED", "HIDDEN", "NOT_PERMANENT", "NOT_AFTER_DEATH")
# Opcodes dont add_duration n'écrit jamais la durée, sans être dans opcodes_ignore_duration.
OLD_HIDDEN_DURATION = (177, 183, 283)
NEW_OPCODE_MACRO = re.compile(r"^ad_op_(\d+)_")
# Macros appelées par le rendu pour chaque opcode DESCRIBED (new-lib/item_render.tpp).
NEW_OPCODE_ROLES = ("support", "lines")
# Rang par défaut de l'ancien moteur pour un opcode absent de sort_opcodes (set_opcode_sort).
OLD_DEFAULT_SORT = 400


def check_catalog(report, definitions):
    report.section("Catalogue des opcodes (2da/opcodes.2da)")
    path = MOD / "2da" / "opcodes.2da"
    lines = read_text(path).replace("\r\n", "\n").split("\n")
    if lines[:2] != ["2DA V1.0", "*"] or lines[2].split() != ["BG2", "EE", "STATUS", "DICE", "SORT", "DURATION", "NAME"]:
        report.add("ERREUR", f"{relative(path)} : en-tête attendu « 2DA V1.0 », « * », « BG2 EE STATUS DICE SORT DURATION NAME »")
        return
    old_sort = parse_sort_opcodes() or {}
    old_duration = old_duration_kinds()
    rows = {}
    previous = -1
    for number, line in enumerate(lines[3:], start=4):
        fields = line.split()
        if not fields:
            continue
        where = f"{relative(path)}:{number}"
        if len(fields) != 8 or not fields[0].isdigit():
            report.add("ERREUR", f"{where} : ligne mal formée (opcode BG2 EE STATUS DICE SORT DURATION NAME)")
            continue
        opcode = int(fields[0])
        if opcode <= previous:
            report.add("ERREUR", f"{where} : opcode {opcode} en double ou hors ordre")
        previous = max(previous, opcode)
        if fields[1] not in ("0", "1") or fields[2] not in ("0", "1"):
            report.add("ERREUR", f"{where} : BG2 et EE valent 0 ou 1")
        if fields[3] not in CATALOG_STATUSES:
            report.add("ERREUR", f"{where} : statut {fields[3]} inconnu ({', '.join(CATALOG_STATUSES)})")
        if fields[4] not in CATALOG_DICE:
            report.add("ERREUR", f"{where} : DICE {fields[4]} inconnu ({', '.join(CATALOG_DICE)})")
        # Même ordre d'affichage que l'ancien moteur, tant que la comparaison des moteurs sert de référence.
        if not re.fullmatch(r"-?\d+", fields[5]):
            report.add("ERREUR", f"{where} : SORT {fields[5]} n'est pas un entier")
        elif int(fields[5]) != old_sort.get(opcode, OLD_DEFAULT_SORT):
            report.add("ERREUR", f"{where} : SORT {fields[5]} au lieu de {old_sort.get(opcode, OLD_DEFAULT_SORT)} "
                       "(sort_opcodes de l'ancien moteur)")
        # Mêmes durées affichées que l'ancien moteur, tant que la comparaison des moteurs sert de référence.
        if fields[6] not in CATALOG_DURATIONS:
            report.add("ERREUR", f"{where} : DURATION {fields[6]} inconnu ({', '.join(CATALOG_DURATIONS)})")
        elif fields[6] != old_duration.get(opcode, "SHOWN"):
            report.add("ERREUR", f"{where} : DURATION {fields[6]} au lieu de {old_duration.get(opcode, 'SHOWN')} "
                       "(listes de durée de l'ancien moteur)")
        rows[opcode] = fields[3]

    # Registre : le statut DESCRIBED doit correspondre au code réellement présent dans new-lib/.
    implemented = collections.defaultdict(list)
    for (_, _, name), places in definitions.items():
        match = NEW_OPCODE_MACRO.match(name)
        if match and any(p.startswith(relative(NEW_LIB) + "/") for p in places):
            implemented[int(match.group(1))].append(name)
    for opcode in sorted(set(implemented) | {o for o, s in rows.items() if s == "DESCRIBED"}):
        if rows.get(opcode) != "DESCRIBED":
            report.add("ERREUR", f"opcode {opcode} : {', '.join(implemented[opcode])} défini mais statut "
                       f"{rows.get(opcode, 'absent du catalogue')} au lieu de DESCRIBED")
        else:
            for role in NEW_OPCODE_ROLES:
                if f"ad_op_{opcode}_{role}" not in implemented[opcode]:
                    report.add("ERREUR", f"opcode {opcode} : statut DESCRIBED sans macro ad_op_{opcode}_{role} dans new-lib/")

    # Point de départ repris de l'ancien moteur ; les écarts sont des décisions à documenter.
    ignored_old = set(parse_ignored_opcodes() or {})
    ignored_new = {o for o, s in rows.items() if s == "IGNORED"}
    if ignored_old != ignored_new:
        report.add("INFO", "IGNORED diffère de ignored_opcodes de l'ancien moteur : "
                   f"seulement dans le catalogue {sorted(ignored_new - ignored_old)}, "
                   f"seulement dans l'ancien {sorted(ignored_old - ignored_new)}")
    counts = collections.Counter(rows.values())
    print(f"  {len(rows)} opcodes : " + ", ".join(f"{counts[s]} {s}" for s in CATALOG_STATUSES))


def check_opcode_includes(report):
    """Fichiers de new-lib/opcodes/ : code commun d'abord, puis un fichier par opcode dans l'ordre numérique."""
    report.section("Inclusions des fichiers d'opcode (new-lib/always.tpa)")
    path = NEW_LIB / "always.tpa"
    code, _ = strip_weidu(read_text(path))
    included = re.findall(r"INCLUDE\s+~%MOD_FOLDER%/new-lib/opcodes/([^~]+)~", code)
    numbers = [int(name[:-4]) for name in included if re.fullmatch(r"\d+\.tpp", name)]
    first_number = next((i for i, name in enumerate(included) if re.fullmatch(r"\d+\.tpp", name)), len(included))
    for name in included[first_number:]:
        if not re.fullmatch(r"\d+\.tpp", name):
            report.add("ERREUR", f"{relative(path)} : {name} (code commun) inclus après un fichier d'opcode")
    if numbers != sorted(set(numbers)):
        report.add("ERREUR", f"{relative(path)} : fichiers d'opcode hors de l'ordre numérique ou en double")
    present = sorted(q.name for q in (NEW_LIB / "opcodes").glob("*.tpp"))
    for name in sorted(set(present) - set(included)):
        report.add("ERREUR", f"{relative(NEW_LIB)}/opcodes/{name} : non inclus par always.tpa")
    for name in sorted(set(included) - set(present)):
        report.add("ERREUR", f"{relative(path)} : inclut new-lib/opcodes/{name}, absent")
    print(f"  {len(included)} fichiers inclus, dont {len(numbers)} fichiers d'opcode")


# ---------------------------------------------------------------------------------------------
# Séparation des moteurs lib/ et new-lib/ (§7.1, condition 1)

CALL = re.compile(r"\b(?:LPF|LAF|LPM|LAM|LAUNCH_(?:PATCH|ACTION)_(?:FUNCTION|MACRO))\s+[~\"]?([A-Za-z0-9_#-]+)")
INCLUDE_PATH = re.compile(r"\b(?:PATCH_)?(?:RE)?INCLUDE\s+(~[^~]*~|\"[^\"]*\")")
ASSIGNMENT = re.compile(
    r"\b(?:OUTER_SET|OUTER_SPRINT|OUTER_TEXT_SPRINT|LOCAL_SET|LOCAL_SPRINT|SET|SPRINT|TEXT_SPRINT"
    r"|(?:ACTION_|PATCH_)?DEFINE_(?:ASSOCIATIVE_)?ARRAY|ACTION_READLN|PATCH_READLN)"
    r"[ \t]+[~\"]?([A-Za-z_][A-Za-z0-9_]*)")
# READ_<type> décalage variable ; les READ_2DA_* ont une autre arité (non relevés).
READ_ASSIGNMENT = re.compile(r"\bREAD_(?!2DA)[A-Z0-9_]+[ \t]+(?:\([^()\n]*\)|\S+)[ \t]+([A-Za-z_][A-Za-z0-9_]*)")
# Paramètres et valeurs renvoyées, dans les définitions comme dans les appels.
PARAMETERS = re.compile(r"\b(?:INT_VAR|STR_VAR|RET_ARRAY|RET)\b(.*?)(?=\b(?:BEGIN|END|INT_VAR|STR_VAR|RET_ARRAY|RET)\b)", re.S)
NAMED = re.compile(r"(?<![A-Za-z0-9_$#-])([A-Za-z_][A-Za-z0-9_]*)\s*=(?![=>])")
PHP_EACH = re.compile(r"\bPHP_EACH\s+\S+\s+AS\s+([A-Za-z_][A-Za-z0-9_]*)\s*=>\s*([A-Za-z_][A-Za-z0-9_]*)")
IDENTIFIER = re.compile(r"(?<![A-Za-z0-9_$#-])([A-Za-z_][A-Za-z0-9_]*)(?![A-Za-z0-9_#-])")
STRING_VARIABLE = re.compile(r"%([A-Za-z_][A-Za-z0-9_]*)%")
NON_VARIABLES = {"EVAL", "BEGIN", "END"}
# Seuls les points d'entrée de la boucle commune appellent le nouveau moteur (initialisation des
# journaux, boucles des objets et des sorts).
ENGINE_CALLERS = ("AutoDescription/lib/log.tpp", "AutoDescription/lib/itm.tpp", "AutoDescription/lib/spl.tpp")
# Options de settings-default.ini réservées au nouveau moteur.
NEW_OPTION_PREFIX = "AD_"


def assigned_variables(code):
    """Noms de variables affectés ou déclarés (paramètres, RET) dans un code sans commentaires ni chaînes."""
    names = set(ASSIGNMENT.findall(code)) | set(READ_ASSIGNMENT.findall(code))
    for segment in PARAMETERS.findall(code):
        # « nom = expression » ou liste de noms seuls : les expressions ne sont pas des noms affectés.
        names |= set(NAMED.findall(segment))
        first = NAMED.search(segment)
        names |= set(IDENTIFIER.findall(segment[:first.start()] if first else segment))
    for key, value in PHP_EACH.findall(code):
        names |= {key, value}
    return names - NON_VARIABLES


def ini_keys():
    """(options de l'ancien moteur, options du nouveau moteur)."""
    text = read_text(MOD / "settings-default.ini")
    keys = set(re.findall(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=", text, re.M))
    new = {key for key in keys if key.startswith(NEW_OPTION_PREFIX)}
    return keys - new, new


def check_engine_separation(report, definitions):
    report.section("Séparation des moteurs lib/ et new-lib/")
    new_files = sorted(p for p in weidu_files() if NEW_LIB in p.parents)
    if not new_files:
        report.add("ERREUR", f"{relative(NEW_LIB)} : aucun fichier")
        return
    old_files = [p for p in weidu_files() if NEW_LIB not in p.parents and BGFORGE not in p.parents]

    def owner(places):
        return {("new" if p.startswith(relative(NEW_LIB) + "/") else
                 "bgforge" if p.startswith(relative(BGFORGE) + "/") else "old") for p in places}

    new_names, old_names = set(), set()
    for (context, kind, name), places in definitions.items():
        owners = owner(places)
        if "new" in owners:
            new_names.add(name)
            if not name.startswith("ad_"):
                report.add("ERREUR", f"{context}_{kind} {name} ({', '.join(places)}) : nom sans préfixe ad_")
            if owners != {"new"}:
                report.add("ERREUR", f"{context}_{kind} {name} défini dans new-lib/ et ailleurs : {', '.join(places)}")
        if "old" in owners:
            old_names.add(name)

    # Variables de l'ancien code (lib/, sfo/, tp2, options) : une fonction voit les variables de
    # son appelant (V7) ; si new-lib/ lit un de ces noms sans l'avoir affecté lui-même, il dépend
    # de l'ancien moteur. Les constantes BGforge sont partagées en lecture seule.
    bgforge_variables = set()
    for path in weidu_files():
        if BGFORGE in path.parents:
            bgforge_variables |= assigned_variables(strip_weidu(read_text(path))[1])
    old_variables, new_options = ini_keys()
    for path in old_files:
        old_variables |= assigned_variables(strip_weidu(read_text(path))[1])
    old_variables -= bgforge_variables

    new_variables, new_globals = set(new_options), set(new_options)
    parsed = {}
    for path in new_files:
        no_comments, code = strip_weidu(read_text(path))
        parsed[path] = (no_comments, code)
        new_variables |= assigned_variables(code)
        new_globals |= set(re.findall(r"\bOUTER_(?:SET|SPRINT|TEXT_SPRINT)\s+([A-Za-z_][A-Za-z0-9_]*)", code))

    for path, (no_comments, code) in parsed.items():
        for match in CALL.finditer(no_comments):
            if match.group(1) in old_names and match.group(1) not in new_names:
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : appel de {match.group(1)}, "
                           "défini dans lib/ ou sfo/")
        for match in INCLUDE_PATH.finditer(no_comments):
            if "/new-lib/" not in match.group(1):
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : inclusion hors de new-lib/ "
                           f"{match.group(1)}")
        reported = set()
        uses = [(m.start(), m.group(1)) for m in IDENTIFIER.finditer(code)]
        uses += [(m.start(), m.group(1)) for m in STRING_VARIABLE.finditer(no_comments)]
        for position, name in sorted(uses):
            if name in old_variables and name not in new_variables and name not in reported:
                reported.add(name)
                report.add("ERREUR", f"{relative(path)}:{line_of(code, position)} : lit la variable {name} "
                           "de l'ancien code sans l'affecter")

    for path in old_files:
        no_comments, code = strip_weidu(read_text(path))
        for match in CALL.finditer(no_comments):
            if match.group(1) in new_names and relative(path) not in ENGINE_CALLERS:
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : appel de {match.group(1)} "
                           f"(new-lib/) hors de la boucle commune ({', '.join(ENGINE_CALLERS)})")
        if path.suffix != ".tp2":
            for match in INCLUDE_PATH.finditer(no_comments):
                if "/new-lib/" in match.group(1):
                    report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : inclusion de new-lib/")
        uses = {m.group(1) for m in IDENTIFIER.finditer(code)} | set(STRING_VARIABLE.findall(no_comments))
        for name in sorted(uses & new_globals):
            report.add("ERREUR", f"{relative(path)} : lit la variable globale {name} de new-lib/")
    print(f"  {len(new_files)} fichiers dans new-lib/, {len(new_names)} fonctions ou macros, "
          f"{len(old_variables)} noms de variables de l'ancien code relevés")


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
    check_new_tra_rules(report)
    definitions = check_duplicate_definitions(report)
    variants = check_opcode_variants(report, definitions)
    check_ignored_described(report, variants)
    check_catalog(report, definitions)
    check_opcode_includes(report)
    check_engine_separation(report, definitions)
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
