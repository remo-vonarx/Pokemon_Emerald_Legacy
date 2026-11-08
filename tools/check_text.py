#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Usage: python3 tools/check_text.py [--widths] [--quiet] [path ...]

Checks the text in data/ and src/ for what breaks at run time:
 - a string run without a closing $, or text behind a $
 - {...} codes that are not closed or that charmap.txt does not know
 - characters that charmap.txt does not know
 - a code from battle text in field text, and the other way round
 - more lines in a text box than it can show before the next \\p or \\l
 - lines wider than their box, in pixels from the glyph widths in src/fonts.c,
   with every name that is inserted at run time at its longest

Exit status 1 when something is found. Run it after every text edit.
"""

import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# The longest text each code can stand for, as pixel widths in FONT_NORMAL.
LETTER = 6
INSERTED = {
	'PLAYER': 7 * LETTER,
	'RIVAL': 5 * LETTER,      # BRIX, MAIKE
	'KUN': 0,
	'VERSION': 7 * LETTER,    # SMARAGD
	'AQUA': 4 * LETTER,
	'MAGMA': 5 * LETTER,
	'ARCHIE': 6 * LETTER,     # ADRIAN
	'MAXIE': 4 * LETTER,      # MARC
	'KYOGRE': 6 * LETTER,
	'GROUDON': 7 * LETTER,
	'STR_VAR_1': 10 * LETTER,
	'STR_VAR_2': 10 * LETTER,
	'STR_VAR_3': 10 * LETTER,
}
NAME_WITH_PREFIX = 10 * LETTER + 46  # " (Gegner)" behind a nickname
TRAINER = 12 * LETTER + 3 + 10 * LETTER  # class, space, name

# Field codes the text printer treats as plain, without width.
NO_WIDTH = ('COLOR', 'HIGHLIGHT', 'SHADOW', 'COLOR_HIGHLIGHT_SHADOW', 'PALETTE', 'FONT', 'RESET_FONT',
	'PAUSE', 'PAUSE_UNTIL_PRESS', 'WAIT_SE', 'PLAY_BGM', 'ESCAPE', 'SHIFT_DOWN', 'FILL_WINDOW', 'PLAY_SE',
	'CLEAR', 'MIN_LETTER_SPACING', 'JPN', 'ENG', 'PAUSE_MUSIC', 'RESUME_MUSIC', 'NAME_END', 'SHIFT_RIGHT',
	'SKIP', 'CLEAR_TO', 'FONT_SMALL', 'FONT_NORMAL', 'FONT_SHORT', 'FONT_NARROW', 'FONT_SMALL_NARROW')

# (path pattern, font table, box width in px, lines per page)
BOXES = [
	(r'data/maps/.*\.inc$', 'Normal', 216, 2),
	(r'data/scripts/.*\.inc$', 'Normal', 216, 2),
	(r'data/text/.*\.inc$', 'Normal', 216, 2),
	(r'src/battle_message\.c$', 'Normal', 216, 2),
	(r'src/data/text/match_call_messages\.h$', 'Normal', 216, 2),
]

# Texts that sit in their own, bigger window and may have more lines per page.
BIG_WINDOWS = re.compile(r'(Board|Desc|Rules|Info|Sign|Poster|Note|Letter|Diary|Plaque|Notice|Braille|Paper|Book|Scroll|Memo|Report|Results)(?=[A-Z0-9_]|$)')


def load_charmap():
	chars, tokens = {}, {}
	for line in open(ROOT / 'charmap.txt', encoding='utf-8'):
		line = line.rstrip('\n')
		m = re.match(r"^'((?:\\.|[^\\])+?)'\s*=\s*([0-9A-Fa-f ]+)", line)
		if m:
			ch = "'" if m[1] == "\\'" else m[1]
			chars[ch] = bytes.fromhex(m[2])
			continue
		m = re.match(r'^(\w+)\s*=\s*([0-9A-Fa-f ]+)', line.split('@')[0])
		if m:
			tokens[m[1]] = bytes.fromhex(m[2])
	return chars, tokens


def load_widths(font):
	src = (ROOT / 'src/fonts.c').read_text(encoding='utf-8')
	m = re.search(r'gFont%sLatinGlyphWidths\[\]\s*=\s*\{(.*?)\}' % font, src, re.S)
	return [int(x) for x in re.findall(r'\b\d+\b', m[1])]


CHARS, TOKENS = load_charmap()
WIDTHS = {}
BATTLE = {t for t, b in TOKENS.items() if t.startswith('B_') and b[0] == 0xFD}


def parse_inc(path):
	"""(label, text, first line) for every run of .string lines; a run ends at its $ or at a label"""
	res = []
	label = run = None
	for n, line in enumerate(open(path, encoding='utf-8', errors='replace'), 1):
		st = line.strip()
		m = re.match(r'^([A-Za-z_]\w*)::?\s*(?:@.*)?$', st)
		if m:
			if run:
				run[3] = False
				res.append(run)
				run = None
			label = m[1]
			continue
		m = re.search(r'\.string\s+"((?:[^"\\]|\\.)*)"', line)
		if m and not st.startswith('@'):
			if run is None:
				run = [label, '', n, True]
			run[1] += m[1]
			if m[1].endswith('$'):
				res.append(run)
				run = None
		elif run and st and not st.startswith('@'):
			run[3] = False
			res.append(run)
			run = None
	if run:
		run[3] = False
		res.append(run)
	return res


C_STR = re.compile(r'(?<![A-Za-z0-9_])__?\(\s*((?:"(?:[^"\\\n]|\\.)*"\s*)+)\)')
C_PIECE = re.compile(r'"((?:[^"\\\n]|\\.)*)"')


def blank_comments(src):
	out = re.sub(r'//[^\n]*', lambda m: ' ' * len(m[0]), src)
	return re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m[0]), out, flags=re.S)


def parse_c(path):
	src = blank_comments(open(path, encoding='utf-8', errors='replace').read())
	for m in C_STR.finditer(src):
		label = re.findall(r'(\w+)\s*(?:\[[^\]]*\]\s*)*=\s*$', src[max(0, m.start() - 80):m.start()])
		yield (label[0] if label else None), ''.join(C_PIECE.findall(m[1])), src.count('\n', 0, m.start()) + 1


def scan(text):
	"""yields ('code', name, args), ('char', c) or ('break', 'n'|'l'|'p'), and reports bad spelling"""
	i, n = 0, len(text)
	while i < n:
		c = text[i]
		if c == '{':
			j = text.find('}', i)
			if j < 0:
				yield ('bad', 'unclosed {')
				return
			parts = text[i + 1:j].split()
			if not parts:
				yield ('bad', 'empty {}')
			else:
				yield ('code', parts[0], parts[1:])
			i = j + 1
		elif c == '}':
			yield ('bad', 'stray }')
			i += 1
		elif c == '\\':
			d = text[i + 1:i + 2]
			if d in ('n', 'l', 'p'):
				yield ('break', d)
			elif d not in ('\\', '"', "'"):
				yield ('bad', 'unknown escape \\' + d)
			else:
				yield ('char', d)
			i += 2
		else:
			yield ('char', c)
			i += 1


def code_width(name, widths):
	if name in INSERTED:
		return INSERTED[name]
	if name in NO_WIDTH or name.startswith(('F9_',)):
		return 0
	if re.search(r'_WITH_PREFIX|MON\d_NAME|ATK_PARTNER_NAME', name):
		return NAME_WITH_PREFIX if 'PREFIX' in name else 10 * LETTER
	if name in ('B_TRAINER1_CLASS', 'B_TRAINER2_CLASS'):
		return 12 * LETTER
	if name.startswith('B_') and 'NAME' in name:
		return 10 * LETTER
	if name.startswith('B_') and ('MOVE' in name or 'ABILITY' in name or 'ITEM' in name):
		return 13 * LETTER
	if name.startswith('B_BUFF'):
		return 10 * LETTER
	return 0


def check(text, path, label, line, box, problems, widths_on, is_inc):
	where = f'{path}:{line}' + (f' {label}' if label else '')
	if is_inc and '$' in text[:-1]:
		problems.append(('format', where, 'text behind a $: ' + text[:60]))
	lines = [[0, '']]
	page_lines = 1
	too_many = False
	font, limit, max_lines = box or (None, None, None)
	widths = None
	if font:
		widths = WIDTHS.setdefault(font, load_widths(font))
	for tok in scan(text):
		if tok[0] == 'bad':
			problems.append(('code', where, tok[1] + ': ' + text[:60]))
		elif tok[0] == 'code':
			name = tok[1]
			if re.fullmatch(r'(0x)?[0-9A-Fa-f]{2}', name) and name not in TOKENS:
				continue
			if name not in TOKENS:
				problems.append(('code', where, 'unknown code {%s}' % name))
				continue
			if name == 'CLEAR_TO':
				lines[-1][0] = max(lines[-1][0], int(tok[2][0], 0)) if tok[2] else lines[-1][0]
				continue
			if name in BATTLE and not (path.endswith('battle_message.c') or 'battle' in path):
				if name not in ('B_BUFF1',):
					problems.append(('code', where, 'battle code {%s} outside battle text' % name))
			if path.endswith('battle_message.c') and name not in BATTLE and TOKENS[name][:1] == b'\xfd':
				problems.append(('code', where, 'field code {%s} in battle text' % name))
			lines[-1][0] += code_width(name, widths)
			lines[-1][1] += '{' + name + '}'
		elif tok[0] == 'char':
			c = tok[1]
			if c == '$':
				continue
			if c not in CHARS:
				problems.append(('char', where, 'unknown character %r' % c))
				continue
			b = CHARS[c]
			if widths and len(b) == 1:
				lines[-1][0] += widths[b[0]]
			lines[-1][1] += c
		else:
			d = tok[1]
			if d == 'p':
				page_lines = 1
			elif d == 'n':
				page_lines += 1
				if max_lines and page_lines > max_lines:
					too_many = True
			lines.append([0, ''])
	if too_many and not (label and BIG_WINDOWS.search(label)):
		problems.append(('lines', where, 'more than %d lines before the next \\p or \\l: %s' % (max_lines, text[:60])))
	if widths_on and limit:
		for w, t in lines:
			if w > limit:
				problems.append(('width', where, '%d px, box %d: %s' % (w, limit, t)))


def files(args):
	if args:
		out = []
		for a in args:
			p = Path(a)
			out += sorted(p.rglob('*')) if p.is_dir() else [p]
		return [p.resolve() for p in out if p.suffix in ('.inc', '.c', '.h')]
	out = sorted((ROOT / 'data').rglob('*.inc')) + sorted((ROOT / 'src').rglob('*.c')) + sorted((ROOT / 'src').rglob('*.h'))
	return [p for p in out if '.json' not in p.name]


def main():
	ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
	ap.add_argument('--widths', action='store_true', help='also report lines wider than their box')
	ap.add_argument('--quiet', action='store_true', help='only print the totals')
	ap.add_argument('paths', nargs='*')
	args = ap.parse_args()
	problems = []
	for p in files(args.paths):
		rel = p.relative_to(ROOT).as_posix()
		box = next((b[1:] for b in BOXES if re.search(b[0], rel)), None)
		if p.suffix == '.inc':
			for label, text, line, closed in parse_inc(p):
				if not closed:
					problems.append(('format', f'{rel}:{line} {label or ""}', 'string run without a closing $: ' + text[:60]))
				check(text, rel, label, line, box, problems, args.widths, True)
		else:
			for label, text, line in parse_c(p):
				check(text, rel, label, line, box, problems, args.widths, False)
	counts = {}
	for kind, where, what in problems:
		counts[kind] = counts.get(kind, 0) + 1
		if not args.quiet:
			print(f'{where}: {what}')
	print('checked: ' + (', '.join(f'{v} {k}' for k, v in sorted(counts.items())) or 'no problems'))
	return 1 if problems else 0


if __name__ == '__main__':
	sys.exit(main())
