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

ROOT = MOD = LIB = BGFORGE = TRA = None


def set_root(root):
    global ROOT, MOD, LIB, BGFORGE, TRA
    ROOT = root.resolve()
    MOD = ROOT / "AutoDescription"
    LIB = MOD / "lib"
    BGFORGE = LIB / "bgforge"
    TRA = MOD / "tra"


def in_engine(path):
    """Fichier du moteur : lib/ hors de lib/bgforge/ (bibliothèque tierce)."""
    return LIB in path.parents and BGFORGE not in path.parents


def engine_place(place):
    """Chemin relatif d'une définition du moteur (lib/ hors de lib/bgforge/)."""
    return place.startswith(relative(LIB) + "/") and not place.startswith(relative(BGFORGE) + "/")

NEW_TRA = "description.tra"
# Fichiers .tra en UTF-8 convertis en Windows-1252 par HANDLE_CHARSETS sur les jeux classiques ;
# setup.tra est lu tel quel.
CONVERTED_TRA = (NEW_TRA,)
NEW_TRA_RANGES = ((1_000_000, 9_999_999), (20_000_000, 39_999_999))
DEFINITION = re.compile(r"DEFINE_(PATCH|ACTION)_(MACRO|FUNCTION)\s+[~\"]?([A-Za-z0-9_#-]+)")


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
    if name in CONVERTED_TRA:
        try:
            text = raw.decode("utf-8")
        except UnicodeDecodeError:
            report.add("ERREUR", f"{where} : contenu non UTF-8 (HANDLE_CHARSETS le convertirait à tort "
                       "sur les jeux classiques)")
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
    old = ids.get(("french", "setup.tra"), set())
    new = ids.get(("french", NEW_TRA), set())
    sources = [path for path in weidu_files() if BGFORGE not in path.parents]
    references = 0
    for path in sources:
        # lib/ n'utilise que description.tra, le tp2 que setup.tra.
        own, name = (new, NEW_TRA) if in_engine(path) else (old, "setup.tra")
        _, code = strip_weidu(read_text(path))
        for match in re.finditer(r"@(-?\d+)\b", code):
            references += 1
            identifier = int(match.group(1))
            if identifier not in own:
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : @{identifier} absent de {name}")
    # Les identifiants calculés (10000000 + parameter2, strref = 13269382…) échappent à ce contrôle.
    print(f"  {references} références littérales examinées (hors commentaires et chaînes)")


NEW_ENTRY = re.compile(r"^@(\d+)\s*=\s*~([^~]*)~([^\n]*)", re.M)
# Fichiers du nouveau moteur où les globales en majuscules sont fixées.
NEW_STARTUP_FILES = ("always.tpa", "startup.tpa", "catalog.tpa")
# Variables de mise en forme de l'ancien moteur (CRLF, AD_COLON, AD_SEMICOLON et PERCENT dans le
# moteur), interdites dans description.tra.
OLD_GLOBALS = {"crlf", "colon", "semicolon", "outer_percent", "meter", "meters"}


def check_new_tra_rules(report):
    report.section(f"Règles propres à {NEW_TRA} et aux références de lib/")
    texts = {}
    for language in ("french", "english"):
        new = (TRA / language / NEW_TRA).read_bytes().decode("utf-8", errors="replace").replace("\r\n", "\n")
        entries = [(int(i), t, rest, line_of(new, m.start())) for m in NEW_ENTRY.finditer(new)
                   for i, t, rest in [m.groups()]]
        order = [i for i, _, _, _ in entries]
        if order != sorted(order):
            report.add("ERREUR", f"{relative(TRA / language / NEW_TRA)} : identifiants non triés")
        texts[language] = ({i: t for i, t, _, _ in entries}, order)
        for identifier, text, rest, line in entries:
            # Le gabarit lirait une variable que le moteur ne définit pas (une fonction voit celles de son appelant).
            for variable in sorted(set(re.findall(r"%([A-Za-z_][A-Za-z0-9_]*)%", text)) & OLD_GLOBALS):
                report.add("ERREUR", f"{relative(TRA / language / NEW_TRA)}:{line} : @{identifier} utilise la "
                           f"variable {variable} de l'ancien moteur")
        print(f"  {relative(TRA / language / NEW_TRA)} : {len(entries)} entrées")
    if texts.get("french", (None, []))[1] != texts.get("english", (None, []))[1]:
        report.add("ERREUR", f"{NEW_TRA} : identifiants dans un ordre différent en français et en anglais")

    french = texts.get("french", ({}, []))[0]
    for path in sorted(p for p in weidu_files() if in_engine(p)):
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
        # Majuscules = globale fixée au démarrage, jamais modifiée pendant le traitement ; les
        # variables de WeiDU qu'un COPY change sont rétablies (cache des sous-sorts).
        if path.name not in NEW_STARTUP_FILES:
            for match in re.finditer(r"\b(?:OUTER_)?(?:SET|SPRINT|TEXT_SPRINT)[ \t]+([A-Z][A-Z0-9_]*)\b", code):
                if match.group(1) in WEIDU_VARIABLES:
                    continue
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
    report.section("Macros et fonctions définies plusieurs fois (lib/, lib/bgforge/)")
    # WeiDU garde silencieusement la dernière définition (ordre d'inclusion).
    definitions = collect_definitions(weidu_files())
    for (context, kind, name), places in sorted(definitions.items()):
        if len(places) > 1:
            third_party_only = all(p.startswith(relative(BGFORGE) + "/") for p in places)
            # Un doublon interne aux bibliothèques tierces ne concerne le mod que s'il les appelle.
            level = "AVERTISSEMENT" if third_party_only else "ERREUR"
            report.add(level, f"{context}_{kind} {name} : " + ", ".join(places))
    return definitions


# ---------------------------------------------------------------------------------------------
# Catalogue des opcodes du nouveau moteur

CATALOG_STATUSES = ("DESCRIBED", "IGNORED", "TODO")
CATALOG_DICE = ("LEVEL", "DICE", "DICE_IF_P2_1_EE")
CATALOG_DURATIONS = ("SHOWN", "IGNORED", "HIDDEN", "NOT_PERMANENT", "NOT_AFTER_DEATH")
NEW_OPCODE_MACRO = re.compile(r"^ad_op_(\d+)_")
# Macros appelées par le rendu pour chaque opcode DESCRIBED (lib/item_render.tpp).
NEW_OPCODE_ROLES = ("support", "lines")


def check_catalog(report, definitions):
    report.section("Catalogue des opcodes (2da/opcodes.2da)")
    path = MOD / "2da" / "opcodes.2da"
    lines = read_text(path).replace("\r\n", "\n").split("\n")
    if lines[:2] != ["2DA V1.0", "*"] or lines[2].split() != ["BG2", "EE", "STATUS", "DICE", "SORT", "DURATION", "NAME"]:
        report.add("ERREUR", f"{relative(path)} : en-tête attendu « 2DA V1.0 », « * », « BG2 EE STATUS DICE SORT DURATION NAME »")
        return
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
        if not re.fullmatch(r"-?\d+", fields[5]):
            report.add("ERREUR", f"{where} : SORT {fields[5]} n'est pas un entier")
        if fields[6] not in CATALOG_DURATIONS:
            report.add("ERREUR", f"{where} : DURATION {fields[6]} inconnu ({', '.join(CATALOG_DURATIONS)})")
        rows[opcode] = fields[3]

    # Registre : le statut DESCRIBED doit correspondre au code réellement présent dans lib/.
    implemented = collections.defaultdict(list)
    for (_, _, name), places in definitions.items():
        match = NEW_OPCODE_MACRO.match(name)
        if match and any(engine_place(p) for p in places):
            implemented[int(match.group(1))].append(name)
    for opcode in sorted(set(implemented) | {o for o, s in rows.items() if s == "DESCRIBED"}):
        if rows.get(opcode) != "DESCRIBED":
            report.add("ERREUR", f"opcode {opcode} : {', '.join(implemented[opcode])} défini mais statut "
                       f"{rows.get(opcode, 'absent du catalogue')} au lieu de DESCRIBED")
        else:
            for role in NEW_OPCODE_ROLES:
                if f"ad_op_{opcode}_{role}" not in implemented[opcode]:
                    report.add("ERREUR", f"opcode {opcode} : statut DESCRIBED sans macro ad_op_{opcode}_{role} dans lib/")

    counts = collections.Counter(rows.values())
    print(f"  {len(rows)} opcodes : " + ", ".join(f"{counts[s]} {s}" for s in CATALOG_STATUSES))


def check_opcode_includes(report):
    """Fichiers de lib/opcodes/ : code commun d'abord, puis un fichier par opcode dans l'ordre numérique."""
    report.section("Inclusions des fichiers d'opcode (lib/always.tpa)")
    path = LIB / "always.tpa"
    code, _ = strip_weidu(read_text(path))
    included = re.findall(r"INCLUDE\s+~%MOD_FOLDER%/lib/opcodes/([^~]+)~", code)
    numbers = [int(name[:-4]) for name in included if re.fullmatch(r"\d+\.tpp", name)]
    first_number = next((i for i, name in enumerate(included) if re.fullmatch(r"\d+\.tpp", name)), len(included))
    for name in included[first_number:]:
        if not re.fullmatch(r"\d+\.tpp", name):
            report.add("ERREUR", f"{relative(path)} : {name} (code commun) inclus après un fichier d'opcode")
    if numbers != sorted(set(numbers)):
        report.add("ERREUR", f"{relative(path)} : fichiers d'opcode hors de l'ordre numérique ou en double")
    present = sorted(q.name for q in (LIB / "opcodes").glob("*.tpp"))
    for name in sorted(set(present) - set(included)):
        report.add("ERREUR", f"{relative(LIB)}/opcodes/{name} : non inclus par always.tpa")
    for name in sorted(set(included) - set(present)):
        report.add("ERREUR", f"{relative(path)} : inclut lib/opcodes/{name}, absent")
    print(f"  {len(included)} fichiers inclus, dont {len(numbers)} fichiers d'opcode")


# ---------------------------------------------------------------------------------------------
# Conventions de lib/

INCLUDE_PATH = re.compile(r"\b(?:PATCH_)?(?:RE)?INCLUDE\s+(~[^~]*~|\"[^\"]*\")")
WEIDU_VARIABLES = {"SOURCE_FILE", "SOURCE_RES", "SOURCE_SIZE", "SOURCE_EXT", "SOURCE_DIRECTORY", "SOURCE_FILESPEC",
                   "DEST_FILE", "DEST_RES", "DEST_EXT", "DEST_DIRECTORY", "DEST_FILESPEC"}


def check_new_lib_conventions(report, definitions):
    report.section("Conventions de lib/ (préfixe ad_, inclusions)")
    new_files = sorted(p for p in weidu_files() if in_engine(p))
    if not new_files:
        report.add("ERREUR", f"{relative(LIB)} : aucun fichier")
        return
    names = 0
    for (context, kind, name), places in definitions.items():
        if any(engine_place(p) for p in places):
            names += 1
            if not name.startswith("ad_"):
                report.add("ERREUR", f"{context}_{kind} {name} ({', '.join(places)}) : nom sans préfixe ad_")
    for path in new_files:
        no_comments, code = strip_weidu(read_text(path))
        for match in INCLUDE_PATH.finditer(no_comments):
            if "/lib/" not in match.group(1):
                report.add("ERREUR", f"{relative(path)}:{line_of(code, match.start())} : inclusion hors de lib/ "
                           f"{match.group(1)}")
    print(f"  {len(new_files)} fichiers dans lib/, {names} fonctions ou macros")


# Élément écrit par nom : SET/SPRINT ~t_%k%~, READ_* offset ~t_%k%~ (clé : variable ou nombre).
WRITTEN_BY_NAME = re.compile(
    r"\b(?:SET|SPRINT|TEXT_SPRINT|READ_(?:BYTE|SHORT|LONG|ASCII|SBYTE|SSHORT|SLONG)\s+(?:\([^()]*\)|[A-Za-z0-9_]+))"
    r"\s+~([A-Za-z_][A-Za-z0-9_]*?)_(?:%[A-Za-z0-9_]+%|[0-9]+)~")
ARRAY_WALK = re.compile(r"\b(PHP_EACH|SORT_ARRAY_INDICES|CLEAR_ARRAY|GET_OFFSET_ARRAY2?)\s+[~\"]?([A-Za-z_][A-Za-z0-9_]*)[~\"]?(?=\s)")
ARRAY_RETURN = re.compile(r"\bRET_ARRAY\b(.*?)\b(?:BEGIN|END)\b", re.S)
JOINED_ARRAY = re.compile(r"\barray_name\s*=\s*[~\"]([A-Za-z_][A-Za-z0-9_]*)[~\"]")


def check_arrays_written_by_name(report):
    """G11 : un tableau dont des éléments sont écrits par nom n'est jamais parcouru.

    PHP_EACH, SORT_ARRAY_INDICES, CLEAR_ARRAY et RET_ARRAY ne voient pas ces éléments : un parcours
    perdrait silencieusement des clés. ad_join (array_name) parcourt son tableau par PHP_EACH.
    """
    report.section("Tableaux écrits par nom, jamais parcourus")
    files = [p for p in weidu_files() if in_engine(p)]
    written = collections.defaultdict(set)
    walked = []
    for path in files:
        no_comments, _ = strip_weidu(read_text(path))
        for match in WRITTEN_BY_NAME.finditer(no_comments):
            written[match.group(1)].add(f"{relative(path)}:{line_of(no_comments, match.start())}")
        for match in ARRAY_WALK.finditer(no_comments):
            walked.append((match.group(2), match.group(1), path, match.start(), no_comments))
        for match in ARRAY_RETURN.finditer(no_comments):
            for name in re.findall(r"[A-Za-z_][A-Za-z0-9_]*", match.group(1)):
                walked.append((name, "RET_ARRAY", path, match.start(), no_comments))
        for match in JOINED_ARRAY.finditer(no_comments):
            walked.append((match.group(1), "ad_join", path, match.start(), no_comments))
    for name, command, path, position, text in walked:
        if name in written:
            first = sorted(written[name])[0]
            report.add("ERREUR", f"{relative(path)}:{line_of(text, position)} : {command} sur {name}, "
                       f"dont des éléments sont écrits par nom ({first})")
    print(f"  {len(written)} tableaux écrits par nom, {len(walked)} parcours examinés")


# Variables de contexte d'une description (type de l'objet, sort ou objet, opcode rendu, texte,
# contexte d'une sous-ressource) et fichiers de lib/ dont les macros peuvent les écrire. Une macro
# partage la portée de son appelant : écrite ailleurs, la variable change pour tout ce qui suit
# (exemple : l'opcode 181 qui rangeait le type interdit dans item_type). Les fonctions ont leur
# propre portée : elles ne sont pas contrôlées.
CONTEXT_OWNERS = {
    "item_type": ("item_render.tpp",),
    "resource_is_spell": (),
    "support_spell": (),
    "support_header_only": (),
    "kind": (),
    "render_opcode": ("application.tpp", "item_charged.tpp", "item_render.tpp", "recursion.tpp",
                      "spell_header.tpp", "spell_levels.tpp"),
    "description": ("application.tpp", "item_charged.tpp", "item_combat.tpp", "item_render.tpp", "lines.tpp",
                    "spell_header.tpp", "spell_levels.tpp"),
    "ctx_": ("recursion.tpp", "spell_levels.tpp"),
}
CONTEXT_NAME = r"(?:" + "|".join(sorted(n for n in CONTEXT_OWNERS if n != "ctx_")) + r"|ctx_[a-z0-9_]+)"
CONTEXT_ASSIGNMENT = re.compile(
    r"(?:\b(?:SET|SPRINT|TEXT_SPRINT|AS|READ_(?:BYTE|SHORT|LONG|ASCII|SBYTE|SSHORT|SLONG)\s+(?:\([^()]*\)|[A-Za-z0-9_]+))|=>)"
    r"\s+(" + CONTEXT_NAME + r")\b(?!\s*\()")
CALL_RETURN = re.compile(r"\bRET\b(.*?)\bEND\b", re.S)
RETURNED_CONTEXT = re.compile(r"\b(" + CONTEXT_NAME + r")\s*=")


def check_context_variables(report):
    """Variables de contexte écrites dans une macro hors de leurs fichiers propriétaires.

    Jamais dans lib/opcodes/ : une macro d'opcode range ses valeurs dans ses propres variables.
    """
    report.section("Variables de contexte écrites hors de leurs fichiers")
    checked = 0
    for path in (p for p in weidu_files() if in_engine(p)):
        no_comments, _ = strip_weidu(read_text(path))
        starts = [(m.start(), m.group(2)) for m in DEFINITION.finditer(no_comments)]
        writes = [(m.start(), m.group(1)) for m in CONTEXT_ASSIGNMENT.finditer(no_comments)]
        for match in CALL_RETURN.finditer(no_comments):
            writes += [(match.start(1) + m.start(), m.group(1)) for m in RETURNED_CONTEXT.finditer(match.group(1))]
        in_opcodes = path.parent.name == "opcodes"
        for position, name in sorted(writes):
            enclosing = [kind for start, kind in starts if start < position]
            if enclosing and enclosing[-1] == "FUNCTION":
                continue
            checked += 1
            owners = CONTEXT_OWNERS["ctx_" if name.startswith("ctx_") else name]
            if in_opcodes or path.name not in owners:
                report.add("ERREUR", f"{relative(path)}:{line_of(no_comments, position)} : {name} écrite par une macro "
                           f"hors de ses fichiers ({', '.join(owners) or 'aucune macro'})")
    print(f"  {checked} écritures de variables de contexte examinées")


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
    check_catalog(report, definitions)
    check_opcode_includes(report)
    check_new_lib_conventions(report, definitions)
    check_arrays_written_by_name(report)
    check_context_variables(report)
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
