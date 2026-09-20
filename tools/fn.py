#!/usr/bin/env python3
"""fn.py [loc] addr...   print decompiled function(s) by address (or containing address)
   fn.py [loc] -l LINE  print the function containing that line of _all.c
   fn.py [loc] -w ADDR  name of function containing ADDR"""
import sys, re, bisect
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
args = sys.argv[1:]
mod = 'MSTTSEngine_OneCore'
if args and args[0] == 'loc': mod = 'MSTTSLoc_OneCore'; args = args[1:]
src = open(r'D:/llm-experiments/misk/zira/decomp/%s/_all.c' % mod, encoding='utf-8', errors='replace').read()
lines = src.split('\n')
starts = []  # (lineno, addr, name)
for i, l in enumerate(lines):
    m = re.match(r'// (\S+) @ ([0-9a-f]{9,})$', l)
    if m: starts.append((i, int(m.group(2), 16), m.group(1)))
byaddr = sorted((a, i, n) for i, a, n in starts)
def body(k):
    i = starts[k][0]; j = starts[k+1][0] if k+1 < len(starts) else len(lines)
    return '\n'.join(lines[i:j])
mode = None
for a in args:
    if a in ('-l', '-w'): mode = a; continue
    if mode == '-l':
        ln = int(a) - 1; k = bisect.bisect_right([s[0] for s in starts], ln) - 1
        print(body(k)); continue
    x = int(a, 16)
    k = bisect.bisect_right([b[0] for b in byaddr], x) - 1
    a0, i0, n0 = byaddr[k]
    if mode == '-w': print('%x in %s @ %x' % (x, n0, a0)); continue
    kk = [s[0] for s in starts].index(i0); print(body(kk))
