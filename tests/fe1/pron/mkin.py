#!/usr/bin/env python3
"""mkin.py DUMP OUT : engine zf1 dump -> input file for build/zf1_t_pron.exe (one word per line, hex fields).
Line: W <type> <textHex> <pos> <s1b0Hex> <s188Hex> <action> <fspos> <presetI278> <presetPronsHex|-> <lineNo>
Words that already had a pronunciation before CPronouncer (type != 0, or <pron sym> i278 == 20) carry their
dump prons as preset.  'S' separates sentences."""
import sys, re
import os; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dumpparse import parse_dump, prons_ids

def hx(s): return ''.join('%04x' % ord(c) for c in s) if s else '-'

out = []
for no, text, sents in parse_dump(sys.argv[1]):
    for s in sents:
        out.append('S %d' % no)
        for w in s:
            ty = int(w['i88']); i278 = int(w['i278'])
            preset = '-'
            if ty != 0 or i278 == 20:
                lst = prons_ids(w.get('prons'))
                if lst is not None:
                    preset = ','.join(('*' if cur else '') + '.'.join('%x' % x for x in ids) for ids, cur in lst) or '='
            fs = w.get('fs', '0,409,0,0,ffff').split(',')
            out.append('W %d %s %s %s %s %s %s %d %s %d' % (ty, hx(w.get('text', '')), w['pos'], hx(w.get('s1b0', '')),
                       hx(w.get('s188', '')), fs[0], fs[4], i278 if (i278 == 20 or preset != "-") else 0, preset, no))
open(sys.argv[2], 'w').write('\n'.join(out) + '\n')
