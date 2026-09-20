import re,struct,pefile,uuid,bisect,sys
pe=pefile.PE(r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll',fast_load=True)
img=pe.get_memory_mapped_image();b=pe.OPTIONAL_HEADER.ImageBase
d=open(r'C:\Windows\Speech_OneCore\Engines\TTS\en-US\MSTTSLocEnUS.dat','rb').read()
present={}
def walk(o,end,dep):
    while o+0x28<=end:
        sz=struct.unpack_from("<Q",d,o+32)[0]; c=o+0x28
        if dep==0 or (dep==1 and o in (0x28,0x88)): walk(c,c+sz,dep+1)
        elif dep==2: present[d[o:o+16]]=(c,sz)
        o=(c+sz+7)&~7
walk(0,len(d),0)
lines=open(r'D:/llm-experiments/misk/zira/decomp/MSTTSEngine_OneCore/_all.c',encoding='utf-8',errors='replace').read().split('\n')
starts=[(i,m.group(1)) for i,l in enumerate(lines) for m in [re.match(r'// (\S+) @ ([0-9a-f]{9,})$',l)] if m]
sl=[s[0] for s in starts]
seen=set()
for i,l in enumerate(lines):
    for m in re.finditer(r'&DAT_(18[0-9a-f]{7}),&DAT_(18[0-9a-f]{7})',l):
        t,idg=int(m.group(1),16),int(m.group(2),16)
        tb=img[t-b:t-b+16]; ib=img[idg-b:idg-b+16]
        f=starts[bisect.bisect_right(sl,i)-1][1]
        k=(t,idg,f)
        if k in seen: continue
        seen.add(k)
        p=present.get(tb)
        print('%s %s %s L%d %s'%(str(uuid.UUID(bytes_le=tb))[:8],str(uuid.UUID(bytes_le=ib))[:8],f,i+1,'IN .dat @%x size %x'%p if p else '-'))
