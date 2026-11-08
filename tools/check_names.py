#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Usage: python3 tools/check_names.py [--category NAME]

Looks for English names left in the German text in data/ and src/:
script strings, C strings (also when split over several literals) and
the region map names in src/data/region_map/region_map_sections.json.
The names come from tools/german_names.py, one table per category:
SPECIES, MOVES, ABILITIES, ITEMS, PLACES, PEOPLE.
Exit status 1 when something is found.
"""

import argparse
import bisect
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import german_names as names

ROOT = Path(__file__).resolve().parent.parent
TABLES = ('SPECIES', 'MOVES', 'ABILITIES', 'ITEMS', 'PLACES', 'PEOPLE')
INC_STRING = re.compile(r'\.string\s+"((?:[^"\\]|\\.)*)"')
C_STRING = re.compile(r'_\(\s*((?:"(?:[^"\\\n]|\\.)*"\s*)+)\)')
PIECE = re.compile(r'"((?:[^"\\\n]|\\.)*)"')
JSON_NAME = re.compile(r'"name"\s*:\s*"((?:[^"\\]|\\.)*)"')
JSON_FILES = ('src/data/region_map/region_map_sections.json',)
SKIP_FILES = ('src/debug.c',)
# The German ROM uses these words itself: as part of a string, and as a whole string.
ROM_WORDS = ('SURF-Strecke',)
ROM_STRINGS = ('TRANSFORM',)  # Ditto's Pokédex category


def targets():
	found = {}
	for table in TABLES:
		for en, de in getattr(names, table).items():
			plain = en.replace('é', 'E')
			if len(en) >= 3 and plain.upper() == plain and en != de:
				found.setdefault(en, (table, de))
	return found


def strings(rel, source):
	"""Each string of a file as (line number, text)."""
	if rel.endswith(('.inc', '.s')):
		for number, line in enumerate(source.splitlines(), 1):
			for m in INC_STRING.finditer(line):
				yield number, m[1]
		return
	starts = [0] + [i + 1 for i, c in enumerate(source) if c == '\n']
	if rel.endswith('.json'):
		for m in JSON_NAME.finditer(source):
			yield bisect.bisect_right(starts, m.start()), m[1]
		return
	for m in C_STRING.finditer(source):
		yield bisect.bisect_right(starts, m.start()), ''.join(PIECE.findall(m[1]))


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument('--category', choices=TABLES)
	args = ap.parse_args()
	want = targets()
	if args.category:
		want = {k: v for k, v in want.items() if v[0] == args.category}
	german = set()
	for table in TABLES:
		german.update(getattr(names, table).values())
	words = re.compile(r"(?<![A-ZÄÖÜa-zäöü.-])(" + '|'.join(sorted(map(re.escape, want), key=len, reverse=True)) + r")(?![A-ZÄÖÜa-zäöü])")
	hits = 0
	files = [p for d in ('data', 'src') for p in (ROOT / d).rglob('*') if p.suffix in ('.inc', '.c', '.h', '.s')]
	files += [ROOT / f for f in JSON_FILES if (ROOT / f).exists()]
	for path in sorted(files):
		rel = str(path.relative_to(ROOT))
		if rel in SKIP_FILES or 'bard_music' in rel:
			continue
		for number, raw in strings(rel, path.read_text(encoding='utf-8', errors='replace')):
			text = re.sub(r'\{[^}]*\}', ' ', raw)
			if text in german or text in ROM_STRINGS:
				continue
			for w in ROM_WORDS:
				text = text.replace(w, ' ')
			for w in words.finditer(text):
				table, de = want[w[1]]
				print(f'{rel}:{number} {table} {w[1]} -> {de}: {text[:60]}')
				hits += 1
	print(f'checked: {hits} found' if hits else 'checked: no English names')
	return 1 if hits else 0


if __name__ == '__main__':
	sys.exit(main())
