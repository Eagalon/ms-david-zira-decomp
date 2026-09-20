#!/usr/bin/env python3
"""fe_tables.py [path-to-MSTTSLocEnUS.dat] [--full]
Dump the small text-frontend tables of the OneCore en-US language data (verified against the
installed MSTTSLocEnUS.dat, 9,804,832 bytes):
  SENTSEP  e67ab014/1df28780  12 word lists used by the rule sentence separator (CSentSepImpl)
  SUFFIX   5554ba64/09397c04  4 suffix tables (noun/adj/verb/apostrophe), 10-wchar slots
  QUOTES   b54490e3/e4c81da4  paired quote table (open, close, flag)
  PARALLEL d8951565/52a33b0b  parallel-structure conjunction list
  POLYCRF  d49f77b9/3e135d7f  CRF homograph model bank (13 models): label prons + feature templates
Container: nested chunks {GUID type, GUID id, u64 size, payload}, 8-byte aligned (see notes/frontend.md)."""
import struct, sys, uuid, re
sys.stdout.reconfigure(encoding='utf-8', errors='replace')
path = next((a for a in sys.argv[1:] if not a.startswith('--')),
            r'C:\Windows\Speech_OneCore\Engines\TTS\en-US\MSTTSLocEnUS.dat')
full = '--full' in sys.argv
d = open(path, 'rb').read()

def chunks():
    out = {}
    def walk(o, end, dep):
        while o + 0x28 <= end:
            t, i = str(uuid.UUID(bytes_le=d[o:o+16])), str(uuid.UUID(bytes_le=d[o+16:o+32]))
            sz = struct.unpack_from('<Q', d, o + 32)[0]
            out.setdefault(t, []).append((i, o + 0x28, sz))
            if dep == 0 or (dep == 1 and o in (0x28, 0x88)): walk(o + 0x28, o + 0x28 + sz, dep + 1)
            o = (o + 0x28 + sz + 7) & ~7
    walk(0, len(d), 0)
    return out
C = chunks()
def get(t): return C[t][0][1], C[t][0][2]
def wstr(p):
    e = p
    while d[e:e+2] != b'\0\0': e += 2
    return d[p:e].decode('utf-16le')

# SENTSEP: u32 nLists(=12), u32 count[n], u32 off[sum] (relative to string pool), UTF-16 strings
o, sz = get('e67ab014-65f6-4e5e-9c1e-2e3a06e9b212')
n = struct.unpack_from('<I', d, o)[0]; cnt = struct.unpack_from('<%dI' % n, d, o + 4)
offs = struct.unpack_from('<%dI' % sum(cnt), d, o + 4 + 4 * n); pool = o + 4 + 4 * n + 4 * sum(cnt)
# field of CSentSepImpl data object each list is stored in (FUN_180047748)
fld = [0x68, 0x78, 0x48, 0x98, 0x28, 0x38, 0x58, 0x88, 0xb8, 0xd8, 0xa8, 0xc8]
print('== SENTSEP (%d lists)' % n); k = 0
for i, c in enumerate(cnt):
    items = [wstr(pool + offs[k + j]) for j in range(c)]; k += c
    print('  list%-2d obj+0x%02x n=%-5d %s' % (i, fld[i], c, items if full else items[:10] + (['...'] if c > 10 else [])))

# SUFFIX: u32 lcid, u32 slotBytes(=0x14), then 4x {u32 n, n*slot}
o, sz = get('5554ba64-7557-436d-9d6f-d5d1d7afb2d3')
lcid, slot = struct.unpack_from('<II', d, o); p = o + 8
print('== SUFFIX lcid=%x slot=%d' % (lcid, slot))
for t in range(4):
    n = struct.unpack_from('<I', d, p)[0]; p += 4
    print('  table%d n=%d %s' % (t, n, [d[p+i*slot:p+(i+1)*slot].decode('utf-16le').rstrip('\0') for i in range(n)])); p += slot * n

# QUOTES: u32 lcid, u32 n, n*{u16 open, u16 close, u32 flag}
o, sz = get('b54490e3-050b-4f66-9c01-76bf4e35a648')
lcid, n = struct.unpack_from('<II', d, o)
print('== QUOTES', [(chr(a), chr(b), f) for a, b, f in struct.iter_unpack('<HHI', d[o+8:o+8+8*n])])

# PARALLEL: words as 0x20-wchar slots (layout partly guessed)
o, sz = get('d8951565-f16d-46c6-a2c8-c2107f9eaea1')
print('== PARALLEL', [w.decode('utf-16le') for w in re.findall(rb'(?:[\x20-\x7e]\x00){2,}', d[o:o+sz])])

# POLYCRF bank: u32 total, u32 hdrLen(0x74), u32 n, u32 0, u32 endOff[n] (relative), ...
o, sz = get('d49f77b9-8982-4860-9d5d-55919cf4f54e')
tot, hl, n = struct.unpack_from('<III', d, o)
ends = sorted(x for x in struct.unpack_from('<%dI' % n, d, o + 16) if x) + [tot]
starts = [hl] + ends[:-1]
print('== POLYCRF %d models' % len(ends))
for s, e in zip(starts, ends):
    ws = [m.group().decode('utf-16le') for m in re.finditer(rb'(?:[\x20-\x7e]\x00){2,}', d[o+s:o+e])]
    print('  @%05x-%05x labels=%s ntemplates=%d' % (s, e, [w for w in ws if '%' in w][:4],
          len([w for w in ws if re.match(r'[UB]\d\d:', w)])))
