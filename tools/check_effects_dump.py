"""Vérifie le journal des effets lus par le nouveau moteur (option AD_EFFECTS_DUMP).

Outil de développement : il relit lui-même les fichiers .itm/.spl (formats ITM V1 et SPL V1,
IESDP), produit les lignes attendues et les compare à celles du journal
AutoDescription/log/*-effects.txt écrit par new-lib/.

Usage : python tools/check_effects_dump.py JOURNAL DOSSIER [DOSSIER ...]
Les dossiers contiennent les fichiers du jeu (par exemple extraits des BIFF avec
weidu --biff-get, puis le dossier override) ; en cas de doublon, le dernier dossier l'emporte.
Code de retour : 0 si tout concorde, 1 sinon.
"""

import argparse
import struct
import sys
from pathlib import Path

# Bloc d'effet de 0x30 octets : entiers sur 1 ou 2 octets non signés, sur 4 octets signés,
# comme les lit WeiDU (READ_BYTE, READ_SHORT, READ_LONG).
EFFECT = struct.Struct("<HBBiiBBiBB8siiiii")
FORMATS = {
    # extension : (signature, taille d'en-tête étendu, décalage du nombre d'effets d'un en-tête,
    #              décalage de l'index, nom du bloc global)
    "ITM": (b"ITM V1  ", 0x38, 0x1E, 0x20, "equipped"),
    "SPL": (b"SPL V1  ", 0x28, 0x1E, 0x20, "casting"),
}


def short(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def long(data, offset):
    return struct.unpack_from("<i", data, offset)[0]


def read_effects(data, kind):
    """Renvoie (nombre d'en-têtes, [champs de chaque effet], erreur de lecture)."""
    signature, header_size, count_at, index_at, global_block = FORMATS[kind]
    if data[:8] != signature:
        return 0, [], "unsupported_format"
    if len(data) < 0x72:
        return 0, [], "invalid_file"
    table = long(data, 0x6A)
    headers_offset = long(data, 0x64)
    header_count = short(data, 0x68)
    effects = []

    def load_block(block, header, index, count):
        for position in range(count):
            offset = table + (index + position) * 0x30
            if offset < 0 or offset + 0x30 > len(data):
                return "invalid_effect"
            values = list(EFFECT.unpack_from(data, offset))
            values[10] = values[10].split(b"\0", 1)[0]
            effects.append([block, str(header), str(position)] + [
                value.decode("latin-1") if isinstance(value, bytes) else str(value) for value in values])
        return ""

    error = load_block(global_block, -1, short(data, 0x6E), short(data, 0x70))
    for header in range(header_count):
        if error:
            break
        offset = headers_offset + header * header_size
        if offset < 0 or offset + header_size > len(data):
            error = "invalid_header"
            break
        error = load_block("ability", header, short(data, offset + index_at), short(data, offset + count_at))
    return header_count, effects, error


def index_files(directories):
    files = {}
    for directory in directories:
        for path in Path(directory).iterdir():
            if path.suffix.upper() in (".ITM", ".SPL"):
                files[path.name.upper()] = path
    return files


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("dump", type=Path)
    parser.add_argument("directories", nargs="+", type=Path)
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    kind = "SPL" if "-spells-" in args.dump.name else "ITM"
    files = index_files(args.directories)

    # Lu en latin-1 : le journal contient les octets bruts des noms de ressources.
    lines = [line.rstrip("\r\n") for line in args.dump.read_text(encoding="latin-1").splitlines() if line.strip()]
    actual = {}
    for line in lines:
        fields = line.split("\t")
        actual.setdefault(fields[0].upper(), []).append(fields)

    problems = 0
    effects_checked = 0
    for resref, rows in sorted(actual.items()):
        path = files.get(f"{resref}.{kind}")
        if path is None:
            print(f"{resref} : fichier introuvable")
            problems += 1
            continue
        header_count, effects, error = read_effects(path.read_bytes(), kind)
        expected = [[rows[0][0], "resource", str(header_count), str(len(effects)), error]]
        expected += [[rows[0][0], "fx", str(i)] + effect for i, effect in enumerate(effects)]
        effects_checked += len(effects)
        if rows != expected:
            problems += 1
            print(f"{resref} : différence")
            for got, want in zip(rows + [[]] * len(expected), expected + [[]] * len(rows)):
                if got != want:
                    print(f"    journal : {got}\n    attendu : {want}")
                    break
    print(f"{len(actual)} ressources, {effects_checked} effets comparés, {problems} différences")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
