import pefile,struct,sys,subprocess
pe=pefile.PE('D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll',fast_load=True);img=pe.get_memory_mapped_image()
rva=int(sys.argv[1],16)-0x180000000; n=int(sys.argv[2]) if len(sys.argv)>2 else 20
for i in range(n):
    v=struct.unpack_from('<Q',img,rva+8*i)[0]
    if not (0x180001000<=v<0x18016c000): break
    out=subprocess.run(['python','D:/llm-experiments/misk/zira/tools/fn.py',hex(v)[2:]],capture_output=True,text=True).stdout
    print('+%03x %x %d lines  %s'%(8*i,v,out.count('\n'),out.split('\n')[2][:100] if out.count('\n')>2 else ''))
