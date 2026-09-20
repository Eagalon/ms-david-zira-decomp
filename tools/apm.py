"""APM (HTS acoustic model) container parser for MSTTSEngine_OneCore voices.
See notes/backend.md section 1."""
import struct, sys
import apmstr
def u32s(d, o, n): return struct.unpack_from('<%dI' % n, d, o)
class APM:
    def __init__(self, path):
        self.d = d = open(path, 'rb').read()
        assert d[:4] == b'APM '
        self.guid = d[4:0x14]; self.payload = u32s(d, 0x14, 1)[0]
        h = 0x18; self.h = h
        (self.version, self.checksum) = u32s(d, h, 2)
        self.lang, self.hflagA = struct.unpack_from('<HH', d, h + 8)
        (self.hflagB, self.unk10, ) = u32s(d, h + 0xc, 1)[0], 0
        (self.rate, self.bits, self.shift) = u32s(d, h + 0x10, 3)
        (self.qoff, self.qsize, self.moff, self.msize, self.soff, self.ssize, self.hoff, self.hsize) = u32s(d, h + 0x1c, 8)
        self.S = apmstr.strings(d[self.soff:self.soff + self.ssize])
        self.parse_questions(); self.parse_models()
    def s(self, o): return self.S.get(o, '#%x' % o)
    def parse_questions(self):
        d = self.d; p = self.qoff
        self.qnamed, nf = u32s(d, p, 2); p += 8
        self.features = [self.s(x) for x in u32s(d, p, nf)]; p += 4 * nf
        nq = u32s(d, p, 1)[0]; p += 4; self.questions = []
        for i in range(nq):
            name = None
            if self.qnamed: name = self.s(u32s(d, p, 1)[0]); p += 4
            fi, op, nv = u32s(d, p, 3); p += 12
            vals = u32s(d, p, nv); p += 4 * nv
            self.questions.append((name, fi, op, vals))
        assert p == self.qoff + self.qsize, (hex(p), hex(self.qoff + self.qsize))
    def parse_models(self):
        d = self.d; b = self.moff; n = u32s(d, b, 1)[0]; self.models = []
        for i in range(n):
            o, sz = u32s(d, b + 4 + 8 * i, 2); m = b + o
            self.models.append(self.parse_model_header(m, sz))
    def parse_model_header(self, m, sz):
        d = self.d; p = m; M = {'off': m, 'size': sz}
        (M['type'], name, M['f10'], M['nstream_or_msd'], M['nstate'], n) = u32s(d, p, 6); p += 24
        M['name'] = self.s(name)
        M['streamdim'] = u32s(d, p, n); p += 4 * n
        M['streamid'] = u32s(d, p, n); p += 4 * n
        M['treeoff'], M['treesize'], M['pooloff'], M['poolsize'] = u32s(d, p, 4); p += 16
        nw = u32s(d, p, 1)[0]; p += 4; wins = []
        for i in range(nw):
            w = u32s(d, p, 1)[0]; p += 4
            wins.append(struct.unpack_from('<%df' % w, d, p)); p += 4 * w
        M['windows'] = wins
        M['tail'] = u32s(d, p, 10); p += 40
        blob = u32s(d, p, 1)[0]; p += 4
        M['blobsize'] = blob; M['bloboff'] = p; p += blob
        M['hdrsize'] = p - m
        return M
if __name__ == '__main__':
    a = APM(sys.argv[1])
    print(f'ver={a.version} lang={a.lang:#x} flagA={a.hflagA} flagB={a.hflagB} rate={a.rate} bits={a.bits} shift={a.shift}')
    print(f'questions@{a.qoff:#x}+{a.qsize:#x} models@{a.moff:#x}+{a.msize:#x} strings@{a.soff:#x}+{a.ssize:#x} huff@{a.hoff:#x}+{a.hsize:#x}')
    print(f'{len(a.features)} features, {len(a.questions)} questions (named={a.qnamed})')
    for M in a.models:
        print({k: v for k, v in M.items()})

# ---------------------------------------------------------------- trees
OPS = {0: '==', 1: 'in', 2: '>', 3: '>=', 4: '<', 5: '<='}   # feature OP question-value (FUN_180013ab0)
def q_eval(q, fv):
    name, fi, op, vals = q
    if op == 1: return fv in vals
    v = vals[0]
    return {0: fv == v, 2: fv > v, 3: fv >= v, 4: fv < v, 5: fv <= v}[op]

def parse_trees(a, M):
    """Tree region of model M. Returns dict id -> list(per state) of subtree dicts."""
    d = a.d; t = M['off'] + M['treeoff']
    ntrees, nsub = u32s(d, t, 2); p = t + 8; trees = {}
    for k in range(ntrees):
        tid = u32s(d, p, 1)[0]; pairs = u32s(d, p + 4, 2 * nsub); p += 4 + 8 * nsub
        subs = []
        for s in range(nsub):
            so, ss = pairs[2 * s], pairs[2 * s + 1]
            subs.append(parse_subtree(d, t + so, ss, M))
        trees[tid] = subs
    trailer = u32s(d, p, 1)[0]; p += 4
    assert p <= t + M['treesize']
    return trees, trailer, p - t

def parse_subtree(d, b, size, M):
    """nodes: {off: ('q', qidx, no_off, yes_off) | ('leaf', payload tuple)}; offsets relative to b."""
    cnt = u32s(d, b, 1)[0]; nodes = {}; queue = [4]; i = 0
    nleafpay = 3 if M['nstream_or_msd'] == 2 else len(M['streamdim'])
    while i < len(queue):
        o = queue[i]; i += 1
        if d[b + o] == 0:
            q = struct.unpack_from('<H', d, b + o + 2)[0]; no, yes = u32s(d, b + o + 4, 2)
            nodes[o] = ('q', q, no, yes); queue += [no, yes]
        elif d[b + o] == 1:
            nodes[o] = ('leaf', u32s(d, b + o + 4, nleafpay))
        else: raise ValueError('bad node tag')
    assert len(nodes) == cnt, (len(nodes), cnt)
    return nodes

def lookup(a, subtree, fvec):
    """fvec: list of int feature values indexed like a.features. Returns leaf payload (pool offsets)."""
    o = 4
    while True:
        n = subtree[o]
        if n[0] == 'leaf': return n[1]
        o = n[3] if q_eval(a.questions[n[1]], fvec[a.questions[n[1]][1]]) else n[2]

def verify(path):
    a = APM(path)
    for M in a.models:
        trees, trailer, used = parse_trees(a, M)
        nleaf = sum(1 for tr in trees.values() for st in tr for n in st.values() if n[0] == 'leaf')
        nnode = sum(len(st) for tr in trees.values() for st in tr)
        maxq = max(n[1] for tr in trees.values() for st in tr for n in st.values() if n[0] == 'q')
        pool = M['off'] + M['pooloff']; npool = u32s(a.d, pool, 1)[0]
        offs = [x for tr in trees.values() for st in tr for n in st.values() if n[0] == 'leaf' for x in n[1]]
        print(f"  {M['name']:28s} trees={len(trees)} ids={min(trees)}..{max(trees) if len(trees)>1 else ''} nodes={nnode} leaves={nleaf} "
              f"trailer={trailer} maxq={maxq}/{len(a.questions)} pool n={npool} leafoff {min(offs)}..{max(offs)} < {M['poolsize']}")
        assert maxq < len(a.questions) and max(offs) < M['poolsize']
    return a

# ---------------------------------------------------------------- pools
def pool_float(a, M, off, dim):
    """Float pool (hdr flagB==0, e.g. David; and all Duration/Phone Duration models):
    entry = [f32 mixture weight] [dim f32 mean*precision] [dim f32 precision]  (FUN_180003e94).
    Returns (w, mean, var)."""
    b = M['off'] + M['pooloff'] + off
    w = struct.unpack_from('<f', a.d, b)[0]
    mp = struct.unpack_from('<%df' % dim, a.d, b + 4); p = struct.unpack_from('<%df' % dim, a.d, b + 4 + 4 * dim)
    return w, [x / y for x, y in zip(mp, p)], [1 / y for y in p]

def pool_lsf_q(a, M, off, P=25, nwin=2, mode=1):
    """Quantized LSF entry (Zira/Mark), exactly as FUN_1800451a0 / FUN_1800ae1cc(mode 1) read it.
    Returns integer means (Q15 normalized-freq for LSF, gain raw i16) and integer 'precisions' (2*u).
    Entry = 156 bytes: mean area 3P+3=78 bytes (u8 deltas + i16 gain per window), precision bytes at +78 (+3 pad)."""
    d = a.d; b = M['off'] + M['pooloff'] + off; T = P * nwin; half = 78  # mean area is always (3P+3) bytes
    means = []; precs = []; acc = 0
    for i in range(T):
        u = d[b + half + i] ** 2
        if i < P:
            u = (u >> 2) if mode == 2 else u
            u = max(u, 1)
        else:
            u <<= 8
        if (i + 1) % P == 0:
            m = struct.unpack_from('<h', d, b + i + i // P)[0]
            if m < 0 and i + 1 == P: m = 0
        elif i < P:
            acc += d[b + i]; m = (8 if P < 41 else 4) * acc
        else:
            m = struct.unpack_from('<b', d, b + i + 1)[0] * (4 if P < 41 else 2)   # engine reads i+1; int path uses nwin=2 so the 3rd window is never read
        if i >= P and 2 * P == T: m *= 2
        means.append(m); precs.append(2 * u)
    return means, precs

def pool_msd_q(a, M, off, dim, P, mode, weight=True):
    """Quantized F0 (weight=True: [f32 w][dim i16][dim u8][pad]) / MBE ([dim i16][dim u8][pad]) entry,
    per FUN_1800ae1cc with mode != 1: mean = i16, precision as in pool_lsf_q."""
    d = a.d; b = M['off'] + M['pooloff'] + off; w = None
    if weight: w = struct.unpack_from('<f', d, b)[0]; b += 4
    means = list(struct.unpack_from('<%dh' % dim, d, b)); precs = []
    for i in range(dim):
        u = d[b + 2 * dim + i] ** 2
        if i < P: u = max((u >> 2) if mode == 2 else u, 1)
        else: u <<= 8
        precs.append(2 * u)
    if 2 * P == dim: means = means[:P] + [m * 2 for m in means[P:]]
    return w, means, precs
