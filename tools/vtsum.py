#!/usr/bin/env python3
"""vtsum.py [loc] CLASS [offset_hex] [n] -> one-line summary of each vtable slot body"""
import sys, subprocess, re
args=sys.argv[1:]; loc=[]
if args[0]=='loc': loc=['loc']; args=args[1:]
cls=args[0]; want=args[1] if len(args)>1 else '0'; n=args[2] if len(args)>2 else '80'
out=subprocess.run([sys.executable,'D:/llm-experiments/misk/zira/tools/rtti.py',*loc,cls,n],capture_output=True,text=True).stdout
cur=None; slots=[]
for l in out.splitlines():
    m=re.match(r'.* vftable @ (\w+) \(offset (\w+)\)',l)
    if m: cur=m.group(2); continue
    m=re.match(r'\s+\+(\w+)\s+(\w+)',l)
    if m and cur==want: slots.append((m.group(1),m.group(2)))
for off,a in slots:
    b=subprocess.run([sys.executable,'D:/llm-experiments/misk/zira/tools/fn.py',*loc,a],capture_output=True,text=True).stdout
    lines=[x.strip() for x in b.splitlines()[1:] if x.strip() and not x.strip().startswith('/*') and x.strip() not in '{}']
    body=' '.join(lines)
    body=re.sub(r'\s+',' ',body)
    print('+%s %s: %s'%(off,a,body[:260]))
