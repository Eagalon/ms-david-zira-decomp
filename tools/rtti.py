#!/usr/bin/env python3
"""rtti.py [loc] CLASS [n]  -> vftable address(es) (x64 MSVC RTTI) and first n slots"""
import sys, struct, pefile
args = sys.argv[1:]
mod = 'MSTTSEngine_OneCore'
if args and args[0] == 'loc': mod = 'MSTTSLoc_OneCore'; args = args[1:]
pe = pefile.PE(r'D:/llm-experiments/misk/zira/bin/%s.dll' % mod, fast_load=True)
img = pe.get_memory_mapped_image(); base = pe.OPTIONAL_HEADER.ImageBase
cls = args[0]; n = int(args[1]) if len(args) > 1 else 40
name = ('.?AV%s@@' % cls).encode() if not cls.startswith('.?') else cls.encode()
td = img.find(b'\0' + name + b'\0')
if td < 0: sys.exit('no typedesc')
td_rva = td + 1 - 0x10
res = []
for s in pe.sections:
    if not s.Name.startswith(b'.rdata'): continue
    a, e = s.VirtualAddress, s.VirtualAddress + s.Misc_VirtualSize
    for p in range(a, e - 24, 4):
        sig, off, cd, t = struct.unpack_from('<IIII', img, p)
        if sig == 1 and t == td_rva:
            col = p
            # find vftable: qword pointing at col
            key = struct.pack('<Q', base + col)
            q = img.find(key, a, e)
            while q >= 0:
                res.append((off, q + 8)); q = img.find(key, q + 1, e)
for off, vt in res:
    print('%s vftable @ %x (offset %x)' % (cls, base + vt, off))
    for i in range(n):
        v = struct.unpack_from('<Q', img, vt + 8 * i)[0]
        if not (base + 0x1000 <= v < base + 0x16c000): break
        print('  +%03x  %x' % (8 * i, v))
