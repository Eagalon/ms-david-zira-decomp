#!/usr/bin/env python3
"""rd.py [loc] KIND VA [n] : read data from the engine (default) or loc DLL image.
KIND: ws (UTF-16 string), wsp (pointer to UTF-16 string), q (u64 x n), d (u32 x n), h (u16 x n), f (float), dbl (double),
      hex (n bytes)"""
import sys, struct, pefile
a = sys.argv[1:]
mod = 'MSTTSEngine_OneCore'
if a and a[0] == 'loc':
    mod = 'MSTTSLoc_OneCore'; a = a[1:]
pe = pefile.PE(r'D:/llm-experiments/misk/zira/bin/%s.dll' % mod, fast_load=True)
img = pe.get_memory_mapped_image(); B = pe.OPTIONAL_HEADER.ImageBase
kind, va = a[0], int(a[1], 16); n = int(a[2]) if len(a) > 2 else 1
r = va - B


def ws(r, lim=400):
    if not (0 <= r < len(img)): return '<bad %x>' % (r + B)
    e = r
    while e < len(img) - 1 and img[e:e + 2] != b'\0\0' and e - r < 2 * lim: e += 2
    return img[r:e].decode('utf-16le', errors='replace')


sys.stdout.reconfigure(encoding='utf-8', errors='replace')
if kind == 'ws': print(repr(ws(r)))
elif kind == 'wsp':
    for i in range(n):
        p = struct.unpack_from('<Q', img, r + 8 * i)[0]
        print(hex(p), repr(ws(p - B)) if p else None)
elif kind == 'q': print([hex(x) for x in struct.unpack_from('<%dQ' % n, img, r)])
elif kind == 'd': print([hex(x) for x in struct.unpack_from('<%dI' % n, img, r)])
elif kind == 'h': print([hex(x) for x in struct.unpack_from('<%dH' % n, img, r)])
elif kind == 'f': print(struct.unpack_from('<%df' % n, img, r))
elif kind == 'dbl': print(struct.unpack_from('<%dd' % n, img, r))
elif kind == 'hex': print(img[r:r + n].hex())
