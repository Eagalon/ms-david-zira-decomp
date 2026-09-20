"""Map MSVC x64 RTTI class names -> vtable VAs -> method VAs for a PE64 DLL.
usage: python rtti64.py <dll> [filter-substring]"""
import sys, struct, pefile, re
dll = sys.argv[1]; flt = sys.argv[2] if len(sys.argv) > 2 else ''
pe = pefile.PE(dll, fast_load=True)
base = pe.OPTIONAL_HEADER.ImageBase
img = pe.get_memory_mapped_image()
secs = [(s.VirtualAddress, s.VirtualAddress + max(s.Misc_VirtualSize, s.SizeOfRawData), s.Name.rstrip(b'\0')) for s in pe.sections]
def sec_of(rva):
    for a, b, n in secs:
        if a <= rva < b: return n
def u32(r): return struct.unpack_from('<I', img, r)[0]
def u64(r): return struct.unpack_from('<Q', img, r)[0]
# type descriptors: ".?AV" strings; TD = string_rva - 0x10
tds = {}
for m in re.finditer(rb'\.\?A[VU][^\0]{1,200}\0', img):
    tds[m.start() - 0x10] = m.group()[:-1].decode('latin1')
# COLs: signature 1, pTypeDescriptor rva at +0xC, pSelf at +0x14
cols = {}
for a, b, n in secs:
    if n not in (b'.rdata',): continue
    for r in range(a, b - 0x18, 4):
        if u32(r) == 1:
            td = u32(r + 0xC)
            if td in tds and u32(r + 0x14) == r:
                cols[r] = td
# vtables: qword pointing to COL, followed by function pointers
colva = {base + r: r for r in cols}
out = []
for a, b, n in secs:
    if n != b'.rdata': continue
    for r in range(a, b - 8, 8):
        v = u64(r)
        if v in colva:
            name = tds[cols[colva[v]]]
            off = struct.unpack_from('<I', img, colva[v] + 4)[0]
            meths = []
            q = r + 8
            while True:
                f = u64(q)
                if not (base <= f < base + len(img)) or sec_of(f - base) != b'.text': break
                meths.append(f); q += 8
                if q in [x - base for x in []]: break
                if u64(q) in colva: break
            out.append((name, r + 8 + base, off, meths))
def demangle(n):
    s = n[4:].rstrip('@').split('@')
    return '::'.join(reversed([x for x in s if x]))
for name, vt, off, meths in sorted(out, key=lambda x: demangle(x[0])):
    dn = demangle(name)
    if flt and flt.lower() not in dn.lower(): continue
    print(f'{dn}  vtbl={vt:#x} off={off:#x} n={len(meths)}')
    print('   ' + ' '.join(f'{i}:{m:#x}' for i, m in enumerate(meths)))
