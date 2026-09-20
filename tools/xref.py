#!/usr/bin/env python3
"""xref.py [loc] FUNADDR...  -> callers of function (by name FUN_xxx in text) + L"" strings in each caller"""
import sys, re, bisect
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
args = sys.argv[1:]
mod = 'MSTTSEngine_OneCore'
if args and args[0] == 'loc': mod = 'MSTTSLoc_OneCore'; args = args[1:]
lines = open(r'D:/llm-experiments/misk/zira/decomp/%s/_all.c' % mod, encoding='utf-8', errors='replace').read().split('\n')
starts = [(i, m.group(1), m.group(2)) for i, l in enumerate(lines) for m in [re.match(r'// (\S+) @ ([0-9a-f]{9,})$', l)] if m]
sl = [s[0] for s in starts]
def fnof(i): return starts[bisect.bisect_right(sl, i) - 1]
for a in args:
    pat = re.compile(r'\b\w*_%s\b' % a.lower())
    seen = set()
    for i, l in enumerate(lines):
        if pat.search(l) and not l.startswith('//'):
            s = fnof(i)
            if s[2] == a.lower() or s in seen: continue
            seen.add(s)
            k = sl.index(s[0]); e = sl[k+1] if k+1 < len(sl) else len(lines)
            strs = sorted(set(re.findall(r'L"([^"]{3,60})"', '\n'.join(lines[s[0]:e]))))[:8]
            vt = sorted(set(re.findall(r'(\w+)::vftable', '\n'.join(lines[s[0]:e]))))[:6]
            print('%s <- %s @%s L%d %s %s' % (a, s[1], s[2], i+1, strs, vt))
