"""Compare deux dumps de régression d'AutoDescription (option ``regression_dump``).

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

Format d'un dump : une ligne par ressource, ``RESREF<TAB>statut<TAB>texte``, où le texte est
échappé (``\\\\``, ``\\r``, ``\\n``, ``\\t``). Statuts : ``ok``, ``failed`` (texte = message
d'erreur WeiDU), ``ignored:<motif>``.

Usage : python tools/compare_dumps.py REFERENCE NOUVEAU [--show N] [--context N]
Code de retour : 0 dumps identiques, 1 différences, 2 dump invalide.
"""

import argparse
import difflib
import sys

UNESCAPES = {"\\": "\\", "r": "\r", "n": "\n", "t": "\t"}


class DumpError(Exception):
    pass


def unescape(text, where):
    result = []
    i = 0
    while i < len(text):
        char = text[i]
        if char == "\\":
            if i + 1 >= len(text) or text[i + 1] not in UNESCAPES:
                raise DumpError(f"{where} : séquence d'échappement invalide")
            result.append(UNESCAPES[text[i + 1]])
            i += 2
        else:
            result.append(char)
            i += 1
    return "".join(result)


def read_dump(path):
    """Renvoie {RESREF en majuscules: (resref, statut, texte)} et la liste des doublons."""
    entries = {}
    duplicates = []
    # surrogateescape : les dumps des jeux classiques sont en Windows-1252, ceux des EE en
    # UTF-8 ; la comparaison doit rester exacte octet à octet quel que soit l'encodage.
    with open(path, "r", encoding="utf-8", errors="surrogateescape", newline="") as handle:
        content = handle.read()
    # APPEND_OUTER ajoute des sauts de ligne en tête et en fin de fichier : seules les lignes
    # non vides sont des entrées.
    # Les CR/LF du texte sont échappés : tout saut de ligne brut (CRLF sous Windows, LF
    # ailleurs) sépare deux entrées.
    for number, line in enumerate(content.split("\n"), 1):
        line = line.removesuffix("\r")
        if line == "":
            continue
        where = f"{path}:{number}"
        fields = line.split("\t", 2)
        if len(fields) != 3 or fields[0] == "":
            raise DumpError(f"{where} : ligne mal formée")
        resref, status, text = fields
        key = resref.upper()
        if key in entries:
            duplicates.append(key)
        entries[key] = (resref, status, unescape(text, where))
    return entries, duplicates


def printable(text):
    raw = text.encode("utf-8", errors="surrogateescape")
    try:
        return raw.decode("utf-8")
    except UnicodeDecodeError:
        return raw.decode("cp1252", errors="replace")


def show_text_diff(reference, new, context):
    diff = difflib.unified_diff(
        printable(reference).splitlines(),
        printable(new).splitlines(),
        "référence",
        "nouveau",
        n=context,
        lineterm="",
    )
    for line in diff:
        print("    " + line)


def main():
    parser = argparse.ArgumentParser(description="Compare deux dumps de régression d'AutoDescription.")
    parser.add_argument("reference")
    parser.add_argument("new")
    parser.add_argument("--show", type=int, default=20, help="nombre de différences détaillées (défaut : 20, -1 : toutes)")
    parser.add_argument("--context", type=int, default=2, help="lignes de contexte des différences de texte")
    args = parser.parse_args()
    # Sous Windows, une sortie redirigée utilise sinon l'encodage local (cp1252).
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")

    try:
        reference, reference_duplicates = read_dump(args.reference)
        new, new_duplicates = read_dump(args.new)
    except (OSError, DumpError) as error:
        print(f"ERREUR : {error}", file=sys.stderr)
        return 2

    if reference_duplicates or new_duplicates:
        # Une ressource traitée deux fois rend la comparaison ambiguë : on refuse de conclure.
        for path, duplicates in ((args.reference, reference_duplicates), (args.new, new_duplicates)):
            if duplicates:
                print(f"ERREUR : {path} : ressources en double : {', '.join(sorted(set(duplicates)))}", file=sys.stderr)
        return 2

    only_reference = sorted(set(reference) - set(new))
    only_new = sorted(set(new) - set(reference))
    status_changed = []
    text_changed = []
    for key in sorted(set(reference) & set(new)):
        _, reference_status, reference_text = reference[key]
        _, new_status, new_text = new[key]
        if reference_status != new_status:
            status_changed.append(key)
        elif reference_text != new_text:
            text_changed.append(key)

    identical = len(set(reference) & set(new)) - len(status_changed) - len(text_changed)
    print(f"Référence : {len(reference)} ressources ; nouveau : {len(new)} ressources")
    print(f"Identiques : {identical}")
    print(f"Texte modifié : {len(text_changed)}")
    print(f"Statut modifié : {len(status_changed)}")
    print(f"Absentes du nouveau : {len(only_reference)}")
    print(f"Absentes de la référence : {len(only_new)}")

    remaining = args.show
    for title, keys in (
        ("Absentes du nouveau", only_reference),
        ("Absentes de la référence", only_new),
        ("Statut modifié", status_changed),
        ("Texte modifié", text_changed),
    ):
        if not keys or remaining == 0:
            continue
        print(f"\n== {title} ==")
        for key in keys:
            if remaining == 0:
                print("  …")
                break
            remaining -= 1
            if key not in new:
                print(f"  {reference[key][0]} ({reference[key][1]})")
            elif key not in reference:
                print(f"  {new[key][0]} ({new[key][1]})")
            elif title == "Statut modifié":
                print(f"  {key} : {reference[key][1]} -> {new[key][1]}")
            else:
                print(f"  {key} ({new[key][1]})")
                show_text_diff(reference[key][2], new[key][2], args.context)

    return 0 if identical == len(reference) == len(new) else 1


if __name__ == "__main__":
    sys.exit(main())
