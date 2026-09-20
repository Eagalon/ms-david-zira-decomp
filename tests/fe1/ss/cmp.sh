#!/bin/sh
# cmp.sh LINES.txt : run engine (harness direct mode) and port on the same lines, report differing lines
H=../../../harness/zftap1_ss.exe; P=../../../build/zf1_t_ss.exe
b=$(basename "$1" .txt)
$H david "$1" "$b.eng" direct >/dev/null && $P "$1" "$b.port" || exit 1
grep -E '^(L|SD) ' "$b.eng" > "$b.eng.f"; grep -E '^(L|SD) ' "$b.port" > "$b.port.f"
python - "$b.eng.f" "$b.port.f" <<'PY'
import sys
def rd(f):
    d={};cur=None
    for l in open(f,encoding='utf-8',errors='replace'):
        l=l.rstrip('\n')
        if l.startswith('L '): cur=l; d[cur]=[]
        else: d[cur].append(l)
    return d
E,P=rd(sys.argv[1]),rd(sys.argv[2]); bad=0
for k in E:
    if E[k]!=P.get(k):
        bad+=1
        if bad<=20: print(k[:150]); print('  E',E[k][:6]); print('  P',P.get(k,[])[:6])
print('identical %d/%d lines, %d calls'%(len(E)-bad,len(E),sum(len(v) for v in E.values())))
PY
