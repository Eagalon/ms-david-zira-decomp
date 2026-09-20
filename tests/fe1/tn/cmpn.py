import sys
def blocks(fn):
    out=[];cur=None
    for l in open(fn,encoding='utf-8'):
        l=l.rstrip('\n')
        if l.startswith('Q '): cur=[l,[]]; out.append(cur)
        elif cur: cur[1].append(l)
    return out
a=blocks(sys.argv[1]); b=blocks(sys.argv[2])
nshow=int(sys.argv[3]) if len(sys.argv)>3 else 25
bad=0
for x,y in zip(a,b):
    if x!=y:
        bad+=1
        if bad<=nshow: print(x[0]); print('   E',x[1]); print('   C',y[1])
print('mismatch',bad,'of',len(a),len(b))
