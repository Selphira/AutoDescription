"""Forme des sorts du jeu (en-têtes, niveaux requis, effets) pour choisir les panels d'essai.

Outil de développement : il n'est pas utilisé pendant l'installation du mod.

Il relit les fichiers .spl (format SPL V1, IESDP) de dossiers extraits du jeu (weidu --biff-get,
puis override ; en cas de doublon, le dernier dossier l'emporte). Avec --dump (dump de l'ancien
moteur, option regression_dump), il ne garde que les sorts décrits et classe aussi chaque sort
d'après son texte : sections par niveau (« À partir du niveau », « Au niveau », « Entre le
niveau ») et progressions (« par niveau »), dans la section « PARAMÈTRES » seulement.

Formes :
  no_header       aucun en-tête étendu
  single          un en-tête au niveau requis 1
  single_high     un en-tête au-dessus du niveau 1
  multi           plusieurs en-têtes, triés, sans doublon, le premier au niveau 1
  multi_anomaly   plusieurs en-têtes avec un doublon de niveau, un ordre décroissant ou un premier
                  en-tête au-dessus de 1 (refusés, décision D18)
Marques : casting (effets de lancement), sections, progression (d'après --dump).

Usage : python tools/spell_stats.py DOSSIER [DOSSIER ...] [--dump DUMP] [--tsv FICHIER]
        [--panel N] [--seed S]
--panel N : jusqu'à N sorts par combinaison forme + marques, tirés au hasard (graine --seed),
plus les sorts les plus coûteux en effets ; une ressource par ligne, à passer à
tools/run_install.py --only-file.
"""

import argparse
import collections
import random
import re
import struct
import sys
from pathlib import Path

from compare_dumps import read_dump

SECTION = re.compile(r"(^|\n)(À partir du niveau|Au niveau|Entre le niveau|From level|At level|Between level)")
PROGRESSION = re.compile(r"par niveau|per level", re.I)
# Titre de la section des effets (@100003 de description.tra) : les marques ne lisent que la suite,
# le texte d'origine du sort parlant souvent lui aussi de niveaux.
STATISTICS = re.compile(r"PARAMÈTRES|STATISTICS")


def short(data, offset):
    return struct.unpack_from("<H", data, offset)[0]


def long(data, offset):
    return struct.unpack_from("<i", data, offset)[0]


def read_spell(data):
    """Renvoie le dictionnaire des champs d'un sort, ou None si le fichier n'est pas lisible."""
    if data[:8] != b"SPL V1  " or len(data) < 0x72:
        return None
    headers_offset, count = long(data, 0x64), short(data, 0x68)
    levels, effects = [], []
    for header in range(count):
        offset = headers_offset + header * 0x28
        if offset < 0 or offset + 0x28 > len(data):
            return None
        levels.append(short(data, offset + 0x10))
        effects.append(short(data, offset + 0x1E))
    return {"type": short(data, 0x1C), "level": long(data, 0x34), "casting": short(data, 0x70),
            "levels": levels, "effects": effects}


def form(spell):
    levels = spell["levels"]
    if not levels:
        return "no_header"
    if len(levels) == 1:
        return "single" if levels[0] <= 1 else "single_high"
    ordered = all(a < b for a, b in zip(levels, levels[1:]))
    return "multi" if ordered and levels[0] <= 1 else "multi_anomaly"


def marks(spell, text):
    result = []
    if spell["casting"]:
        result.append("casting")
    titles = list(STATISTICS.finditer(text or ""))
    technical = text[titles[-1].end():] if titles else ""
    if SECTION.search(technical):
        result.append("sections")
    if PROGRESSION.search(technical):
        result.append("progression")
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("directories", nargs="+", type=Path)
    parser.add_argument("--dump", type=Path)
    parser.add_argument("--tsv", type=Path)
    parser.add_argument("--panel", type=int, default=0)
    parser.add_argument("--seed", type=int, default=1)
    args = parser.parse_args()
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

    files = {}
    for directory in args.directories:
        for path in directory.iterdir():
            if path.suffix.upper() == ".SPL":
                files[path.stem.upper()] = path
    texts = None
    if args.dump:
        dump, _ = read_dump(args.dump)
        texts = {key: text for key, (_, status, text) in dump.items() if status == "ok"}

    rows = []
    unreadable = 0
    for resref in sorted(files):
        if texts is not None and resref not in texts:
            continue
        spell = read_spell(files[resref].read_bytes())
        if spell is None:
            unreadable += 1
            continue
        text = texts.get(resref) if texts is not None else None
        rows.append((resref, form(spell), marks(spell, text), spell))

    print(f"{len(rows)} sorts" + (f" décrits par l'ancien moteur" if texts is not None else "")
          + (f" ; {unreadable} illisibles" if unreadable else ""))
    if texts is not None:
        missing = sorted(set(texts) - {row[0] for row in rows})
        if missing:
            print(f"  absents des dossiers : {len(missing)} ({' '.join(missing[:10])})")
    combos = collections.Counter((row[1], " ".join(row[2])) for row in rows)
    for (shape, flags), count in sorted(combos.items()):
        print(f"  {count:5}  {shape}{' + ' + flags if flags else ''}")
    multi = [row for row in rows if len(row[3]["levels"]) > 1]
    if multi:
        sizes = collections.Counter(len(row[3]["levels"]) for row in multi)
        print("  en-têtes des sorts à plusieurs en-têtes :", " ".join(f"{k}:{v}" for k, v in sorted(sizes.items())))

    if args.tsv:
        with open(args.tsv, "w", encoding="utf-8", newline="\n") as handle:
            handle.write("resref\tform\tmarks\ttype\tlevel\tcasting\theaders\tlevels\teffects\n")
            for resref, shape, flags, spell in rows:
                handle.write(f"{resref}\t{shape}\t{','.join(flags)}\t{spell['type']}\t{spell['level']}\t{spell['casting']}\t"
                             f"{len(spell['levels'])}\t{','.join(map(str, spell['levels']))}\t{','.join(map(str, spell['effects']))}\n")

    if args.panel:
        generator = random.Random(args.seed)
        by_combo = collections.defaultdict(list)
        for row in rows:
            by_combo[(row[1], " ".join(row[2]))].append(row[0])
        panel = []
        for combo in sorted(by_combo):
            members = sorted(by_combo[combo])
            panel += sorted(generator.sample(members, min(args.panel, len(members))))
        heaviest = sorted(rows, key=lambda row: -(row[3]["casting"] + sum(row[3]["effects"])))[:args.panel]
        panel += [row[0] for row in heaviest if row[0] not in panel]
        print(f"\n# Panel : {len(panel)} sorts ({args.panel} par combinaison, graine {args.seed}, plus les plus lourds)")
        for resref in panel:
            print(resref)
    return 0


if __name__ == "__main__":
    sys.exit(main())
