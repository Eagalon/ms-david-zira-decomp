import pefile,uuid,sys
pe=pefile.PE(r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll',fast_load=True)
d=open(r'C:\Windows\Speech_OneCore\Engines\TTS\en-US\MSTTSLocEnUS.dat','rb').read()
for a in sys.argv[1:]:
  b=pe.get_data(int(a,16)-0x180000000,16); p=d.find(b); r=[]
  while p>=0 and len(r)<4: r.append(hex(p)); p=d.find(b,p+1)
  print(a,uuid.UUID(bytes_le=b),r)
