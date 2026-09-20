#!/usr/bin/env python3
"""vtof.py [loc] FUNADDR... -> which class vftable slot(s) hold this function"""
import sys, struct, pefile
args = sys.argv[1:]
mod = 'MSTTSEngine_OneCore'
if args and args[0] == 'loc': mod = 'MSTTSLoc_OneCore'; args = args[1:]
pe = pefile.PE(r'D:/llm-experiments/misk/zira/bin/%s.dll' % mod, fast_load=True)
img = pe.get_memory_mapped_image(); base = pe.OPTIONAL_HEADER.ImageBase
text = [(s.VirtualAddress, s.VirtualAddress + s.Misc_VirtualSize) for s in pe.sections if s.Name.startswith(b'.text')][0]
rd = [(s.VirtualAddress, s.VirtualAddress + s.Misc_VirtualSize) for s in pe.sections if s.Name.startswith(b'.rdata')][0]
def istext(v): return text[0] <= v - base < text[1]
def colname(v):
    r = v - base
    if not (rd[0] <= r < rd[1]): return None
    sig, off, cd, td = struct.unpack_from('<IIII', img, r)
    if sig != 1: return None
    n = img[td + 0x10: td + 0x10 + 200].split(b'\0')[0].decode(errors='replace')
    return n[4:-2] if n.startswith('.?AV') else n
for a in args:
    key = struct.pack('<Q', int(a, 16)); p = img.find(key, rd[0], rd[1])
    while p >= 0:
        q = p
        while istext(struct.unpack_from('<Q', img, q - 8)[0]): q -= 8
        cn = colname(struct.unpack_from('<Q', img, q - 8)[0])
        print('%s: %s vftable@%x slot +0x%x' % (a, cn, base + q, p - q))
        p = img.find(key, p + 1, rd[1])
