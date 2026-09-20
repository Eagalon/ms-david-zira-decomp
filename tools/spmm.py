#!/usr/bin/env python3
"""spmm.py - dump the sPMM pattern-machine rules (resource 00a2359e/4d4d5073, CRuleSentAndPuncDetector)."""
import sys, struct
sys.path.insert(0, 'D:/llm-experiments/misk/zira/tools')
from locdat import Dat
sys.stdout.reconfigure(encoding='utf-8', errors='backslashreplace')
OPS = {1: '==', 2: '<', 3: '<=', 4: '>', 5: '>=', 6: 'eq', 7: 'startswith', 8: 'endswith', 9: 'contains', 10: 'in', 11: 'ieq'}
d = Dat(); c, sz = d.res('00a2359e'); b = d.d[c:c + sz]
u = lambda o: struct.unpack_from('<i', b, o)[0]
def s(o):
    n = struct.unpack_from('<H', b, o)[0]; return b[o + 2:o + 2 + 2 * n].decode('utf-16le')
nf, ne, fto, eo = u(4), u(8), u(12), u(16)
print('features', nf, 'types', [u(fto + 4 * i) for i in range(nf)])
for e in range(ne):
    o = eo + 16 * e
    print('ENTRY %r (a=%d) rules=%d' % (s(u(o + 4)), u(o), u(o + 8)))
    for r in range(u(o + 8)):
        ro = u(o + 12) + 16 * r
        kind, val, nc, co = u(ro), u(ro + 4), u(ro + 8), u(ro + 12)
        conds = []
        for k in range(nc):
            q = co + 16 * k
            f, op, x, v = u(q), u(q + 4), u(q + 8), u(q + 12)
            conds.append('F%d %s %s' % (f, OPS.get(op, op), repr(s(v)) if op >= 6 else v) + ('' if x == 0 else ' x=%d' % x))
        print('   -> %s  if %s' % (val if kind == 0 else repr(s(val)), ' AND '.join(conds) or 'TRUE'))
