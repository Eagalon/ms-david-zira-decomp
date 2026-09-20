#!/usr/bin/env python3
"""mkn_from_dump.py DUMP OUT: N-queries (category, text) from the engine's "TN hr= cat= in=" hook lines."""
import re, sys
TNL = re.compile(r'^TN hr=\S+ cat="((?:[^"\\]|\\.)*)" in="((?:[^"\\]|\\.)*)"')


def unesc(s):
    return re.sub(r'\\x([0-9a-f]{2})', lambda m: chr(int(m.group(1), 16)), s)


seen = set()
out = []
for l in open(sys.argv[1], encoding='utf-8'):
    m = TNL.match(l)
    if m:
        k = (unesc(m.group(1)), unesc(m.group(2)))
        if k not in seen and '\t' not in k[1] and '\n' not in k[1]:
            seen.add(k)
            out.append('N\t%s\t%s\n' % k)
open(sys.argv[2], 'w', encoding='utf-8').write(''.join(out))
print(len(out))
