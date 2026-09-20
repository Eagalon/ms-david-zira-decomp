"""Dump the OneCore engine's linguistic feature tables (leaf feature names -> id/type/level) and path-token table.
usage: python feat_table.py [dll]"""
import sys, struct, pefile
dll = sys.argv[1] if len(sys.argv) > 1 else r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll'
pe = pefile.PE(dll, fast_load=True); img = pe.get_memory_mapped_image(); base = pe.OPTIONAL_HEADER.ImageBase
def ws(va):
    r = va - base
    if not (0 <= r < len(img)): return None
    e = r
    while img[e:e + 2] != b'\0\0' and e - r < 200: e += 2
    try: s = img[r:e].decode('utf-16le')
    except Exception: return None
    return s if s and s.isprintable() and s.isascii() else None
LEVEL = {1: 'Phone', 2: 'HalfPhone', 4: 'Syllable', 8: 'Word', 0x10: 'ProsodicWord', 0x40: 'Phrase', 0x80: 'IntonationPhrase', 0x200: 'Sentence'}
def ent(t):
    p, fid, typ, lvl = struct.unpack_from('<QIII', img, t)
    return ws(p), fid, typ, lvl
anchor = img.find('BwPosInYesNoQuestion'.encode('utf-16le'))
t = img.find(struct.pack('<Q', base + anchor))
while ent(t - 24)[0]: t -= 24
print(f'# leaf feature table @ {base + t:#x}: {{wchar* name; u32 id; u32 type(0 int,1 ?,2 string); u32 levelmask}}')
while ent(t)[0]:
    n, fid, typ, lvl = ent(t)
    lv = '|'.join(v for k, v in LEVEL.items() if lvl & k)
    print(f'{base + t:#x} {fid:#04x} type={typ} level={lvl:#x}({lv}) {n}')
    t += 24
print('\n# path token table @ 0x18016fee0: {wchar* name; u32 level; i32 dir; u32 ?; u32 allowed-after mask}')
t = 0x18016fee0 - base
while t < 0x180170240 - base:
    p, a, b, c, d = struct.unpack_from('<QiiII', img, t)
    print(f'{ws(p)} level={a:#x} dir={b} {c} {d:#x}'); t += 24
