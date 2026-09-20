#!/usr/bin/env python3
"""cmp.py DUMP PORT_OUT [-v N] : compare build/zf1_t_pron.exe output with the engine dump, word by word.
Fields: pron list (+current), i278, i368.  Words whose final pronunciation came from fork C's polyphony
steps (i278 13 = CPolyphony, 22 = CRF homograph) are reported separately (not counted as errors)."""
import sys, os, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dumpparse import parse_dump, prons_ids

def fmt(lst):
    if lst is None or not lst: return '-'
    return ','.join(('*' if cur else '') + '.'.join('%x' % x for x in ids) for ids, cur in lst)

def hx(s): return ''.join('%04x' % ord(c) for c in s) if s else ''

verbose = 30
if '-v' in sys.argv: verbose = int(sys.argv[sys.argv.index('-v') + 1])
exp = []
for no, text, sents in parse_dump(sys.argv[1]):
    for s in sents:
        for w in s:
            exp.append((no, w))
got = [l.split() for l in open(sys.argv[2])]
if len(got) != len(exp):
    print('word count mismatch', len(got), len(exp))
bad = collections.Counter(); ok = 0; skipped = 0; shown = 0
for (no, w), g in zip(exp, got):
    i278 = int(w['i278'])
    e = (fmt(prons_ids(w.get('prons'))), w['i278'], w['i368'])
    p = (g[2] if len(g) > 2 else '?', g[3] if len(g) > 3 else '?', g[4] if len(g) > 4 else '?')
    if len(g) == 4:  # empty text
        p = (g[1], g[2], g[3])
    if i278 in (13, 22):
        skipped += 1
        continue
    if e == p:
        ok += 1
        continue
    key = 'i278=%s' % w['i278']
    bad[key] += 1
    if shown < verbose:
        shown += 1
        print('L%d %-16s exp %s | got %s' % (no, w.get('text'), ' '.join(e), ' '.join(p)))
print('mismatch by engine source:', dict(bad))
print('WORDS OK %d / %d  (skipped fork-C words: %d)' % (ok, ok + sum(bad.values()), skipped))
