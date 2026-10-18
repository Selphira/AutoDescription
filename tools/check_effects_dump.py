"""Vérifie le journal des effets lus par le nouveau moteur (option AD_EFFECTS_DUMP).

Outil de développement : il relit lui-même les fichiers .itm/.spl (formats ITM V1 et SPL V1,
IESDP), produit les lignes attendues et les compare à celles du journal
AutoDescription/log/*-effects.txt écrit par new-lib/.

Les valeurs normalisées sont recalculées ici, indépendamment de new-lib/normalize.tpp, à partir
des règles de l'IESDP (format des effets) et de la colonne DICE de 2da/opcodes.2da.

Usage : python tools/check_effects_dump.py [--classic] JOURNAL DOSSIER [DOSSIER ...]
Les dossiers contiennent les fichiers du jeu (par exemple extraits des BIFF avec
weidu --biff-get, puis le dossier override) ; en cas de doublon, le dernier dossier l'emporte.
--classic : journal produit sur un jeu classique (BG2, BGT) plutôt que sur un EE.
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


CATALOG = Path(__file__).resolve().parent.parent / "AutoDescription" / "2da" / "opcodes.2da"
TIMINGS = {
    # timing : (genre, délai en ticks, durée en ticks) en fonction de la durée brute d
    0: ("limited", lambda d: 0, lambda d: d * 15),
    1: ("permanent", lambda d: 0, lambda d: 0),
    3: ("delayed_limited", lambda d: d * 15, lambda d: d * 15),
    4: ("delayed_permanent", lambda d: d * 15, lambda d: 0),
    5: ("delayed_while_equipped", lambda d: d * 15, lambda d: 0),
    6: ("game_time_limited", lambda d: 0, lambda d: 0),
    7: ("game_time_permanent", lambda d: 0, lambda d: 0),
    8: ("game_time_while_equipped", lambda d: 0, lambda d: 0),
    9: ("permanent_after_death", lambda d: 0, lambda d: 0),
    10: ("limited", lambda d: 0, lambda d: d),
    4096: ("absolute", lambda d: 0, lambda d: 0),
}


def read_dice_usage():
    usage = {}
    for line in CATALOG.read_text(encoding="ascii").splitlines()[3:]:
        fields = line.split()
        if fields:
            usage[int(fields[0])] = fields[4]
    return usage


def normalize(block, values, dice_usage, is_ee):
    """Valeurs normalisées d'un effet (mêmes colonnes que AD_FX_FIELDS après les champs bruts)."""
    (opcode, _, _, _, parameter2, timing, _, duration, probability1, probability2, resource,
     dice_count, dice_sides, save_type, _, _) = values
    if timing == 2:
        kind, delay, length = ("while_equipped" if block == "equipped" else "until_reload"), 0, 0
    elif timing in TIMINGS:
        kind, delay_of, length_of = TIMINGS[timing]
        delay, length = delay_of(duration), length_of(duration)
    else:
        kind, delay, length = "unknown", 0, 0
    # Tirage x dans 0-99 : l'effet a lieu si probabilité 2 <= x <= probabilité 1.
    high = min(probability1, 99)
    chance = high - probability2 + 1 if probability2 <= high else 0
    usage = dice_usage.get(opcode, "LEVEL")
    level = usage == "LEVEL" or (usage == "DICE_IF_P2_1_EE" and not (is_ee and parameter2 == 1))
    # Minuscules ASCII seulement (les noms de ressources du jeu sont en ASCII).
    lower = "".join(c.lower() if c.isascii() else c for c in resource)
    return [kind, delay, length, probability2, high, chance, save_type & 0b11111, save_type & ~0b11111,
            dice_sides if level else 0, dice_count if level else 0, lower]


def short(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def long(data, offset):
    return struct.unpack_from("<i", data, offset)[0]


def read_effects(data, kind, dice_usage, is_ee):
    """Renvoie (nombre d'en-têtes, [champs bruts et normalisés de chaque effet], erreur de lecture)."""
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
            values[10] = values[10].split(b"\0", 1)[0].decode("latin-1")
            effects.append([block, str(header), str(position)]
                           + [str(value) for value in values + normalize(block, values, dice_usage, is_ee)])
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
    parser.add_argument("--classic", action="store_true", help="journal produit sur un jeu classique")
    args = parser.parse_args()
    dice_usage = read_dice_usage()
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
        header_count, effects, error = read_effects(path.read_bytes(), kind, dice_usage, not args.classic)
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
