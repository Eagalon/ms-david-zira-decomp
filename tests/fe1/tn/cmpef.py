import sys
blocks=[];cur=None
for l in open(sys.argv[1],encoding='utf-8'):
    l=l.rstrip('\n')
    if l.startswith('Q '): cur=[l,[]]; blocks.append(cur)
    else: cur[1].append(l)
diff=0
for i in range(0,len(blocks),2):
    e,f=blocks[i],blocks[i+1]
    if e[1]!=f[1]:
        diff+=1; print(e[0]); print('  E',e[1]); print('  F',f[1])
print('diffs',diff,'of',len(blocks)//2)
