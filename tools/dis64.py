"""x64 disassembler helper for MSTTSEngine_OneCore.dll (capstone CS_MODE_64).
usage: python dis64.py <VA> [count]          disassemble count (default 20) instructions at VA
       python dis64.py -p <VA> [<VA>...]      prologue report: first instructions covering >=14 bytes,
                                              flags RIP-relative / branch instructions inside the stolen bytes"""
import sys, pefile, capstone
DLL = r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll'
pe = pefile.PE(DLL, fast_load=True); img = pe.get_memory_mapped_image(); base = pe.OPTIONAL_HEADER.ImageBase
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64); md.detail = True
def insns(va, n):
    r = va - base
    return list(md.disasm(img[r:r + 16 * n], va))[:n]
a = sys.argv[1:]
if a and a[0] == '-p':
    for v in a[1:]:
        va = int(v, 16); out = []; tot = 0; bad = []
        for i in insns(va, 12):
            out.append(f'{i.bytes.hex()} {i.mnemonic} {i.op_str}')
            if 'rip' in i.op_str or i.group(capstone.CS_GRP_JUMP) or i.group(capstone.CS_GRP_CALL) or i.group(capstone.CS_GRP_RET):
                bad.append(i.mnemonic)
            tot += i.size
            if tot >= 14: break
        print(f'{va:#x}: steal {tot} B {"OK" if not bad else "RELOCATE:" + ",".join(bad)} | ' + ' ; '.join(out))
else:
    va = int(a[0], 16); n = int(a[1]) if len(a) > 1 else 20
    for i in insns(va, n): print(f'{i.address:#x}: {i.bytes.hex():<24} {i.mnemonic} {i.op_str}')
