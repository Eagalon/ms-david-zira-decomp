"""Dump per-class GetFeature tables {int propId; int ?; u64 ?; fnptr} (24 B) of MSTTSEngine_OneCore."""
import struct, pefile, sys
pe = pefile.PE(r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll', fast_load=True)
img = pe.get_memory_mapped_image(); base = pe.OPTIONAL_HEADER.ImageBase
names = {}
t = 0x18016f280 - base
while t < 0x18016fc10 - base:
    p, fid, typ, lvl = struct.unpack_from('<QIII', img, t)
    if p == 0 or not (base <= p < base + len(img)): break
    r = p - base; e = r
    while img[e:e+2] != b'\0\0': e += 2
    names.setdefault(fid, img[r:e].decode('utf-16le')); t += 24
T = {'phone': (0x180170240, 0x180170400), 'syll': (0x180170400, None), 'word': (0x1801706d0, 0x180170c40),
     'phrase': (0x180178ca0, None), 'ip': (0x180178e20, None), 'sent': (0x180178bb0, 0x180178c40), 'pw': (0x180178ed0, None)}
for k, (a, end) in T.items():
    print('==', k, hex(a)); t = a - base
    while True:
        pid, x, y, fn = struct.unpack_from('<iiQQ', img, t)
        if end and t + base >= end: break
        if not (base <= fn < base + len(img)): break
        print(f'  {pid:#04x} {names.get(pid,"?"):32s} {x:#x} {y:#x} {fn:#x}'); t += 24
