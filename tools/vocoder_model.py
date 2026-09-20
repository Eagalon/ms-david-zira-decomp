"""Reference model of the OneCore SPS vocoder (float path: CExcitationGeneratorImpl<float> +
CLsfSynthesizerImpl<float,float>) as used by Microsoft David (OneCore, MSTTSEngine_OneCore.dll 10.3.21207).
Verifies against harness/vocprobe.exe dumps (vocdump.bin):  python vocoder_model.py [vocdump.bin]

Everything here is transcribed from the disassembly (see notes/backend_vocoder.md); numpy float32 is used
where the engine uses SSE single precision, Python float where it uses double.
"""
import sys, struct, math
import numpy as np
import pefile

DLL = r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll'
f32 = np.float32


def dll_tables():
    pe = pefile.PE(DLL, fast_load=True)
    b = pe.OPTIONAL_HEADER.ImageBase
    img = pe.get_memory_mapped_image()
    bands = np.array(struct.unpack_from('<205d', img, 0x18017d3c0 - b)).reshape(5, 41)   # 5 x 41-tap FIRs
    w16k = struct.unpack_from('<5d', img, 0x1801927f8 - b)                                # default band voicing @16k
    w8k = struct.unpack_from('<5d', img, 0x1801927d0 - b)
    return bands, w16k, w8k


class CRand:
    """MSVC/UCRT rand(): per-thread LCG."""
    def __init__(self, seed=0x406): self.s = seed
    def srand(self, seed): self.s = seed
    def rand(self):
        self.s = (self.s * 214013 + 2531011) & 0xffffffff
        return (self.s >> 16) & 0x7fff


def band_filters(bands, w):
    """FUN_18003c060: voiced = sum w_b h_b, unvoiced = sum (1-w_b) h_b (double accum, stored float)."""
    hv = np.zeros(41, np.float32); hu = np.zeros(41, np.float32)
    for k in range(41):
        dv = 0.0; du = 0.0
        for b_ in range(5):
            dv = dv + w[b_] * bands[b_][k]
            du = du + (1.0 - w[b_]) * bands[b_][k]
        hv[k] = f32(dv); hu[k] = f32(du)
    return hv, hu


def fir_valid(h, x):
    """FUN_18000b1f0: out[n] = sum_k h[k]*x[n-k] for n >= taps-1, first taps entries zero; products in
    float, accumulated sequentially in DOUBLE, stored float (Ghidra hides the cvtps2pd)."""
    T = len(h); out = np.zeros(len(x), np.float32)
    for n in range(T - 1, len(x)):
        acc = 0.0
        for k in range(T):
            acc = acc + float(f32(x[n - k] * h[k]))
        out[n] = f32(acc)
    return out


class Excitation:
    """CExcitationGeneratorImpl<float> (vtbl 0x180177ae8)."""
    def __init__(self, fs=16000, rnd=None):
        bands, w16, w8 = dll_tables()
        self.fs = fs
        self.rnd = rnd or CRand()
        self.hv, self.hu = band_filters(bands, w16 if fs == 16000 else w8)
        # FUN_18006b550: 1024-sample Gaussian noise (Box-Muller, srand(0x406))
        self.rnd.srand(0x406)
        noise = np.zeros(1024, np.float32)
        for i in range(1024):
            r1 = self.rnd.rand(); r2 = self.rnd.rand()
            s = math.sin(float(f32(f32(r2 + 1) * f32(1 / 32768.0))) * 6.283185307179586)
            l = math.log(float(f32(f32(r1 + 1) * f32(1 / 32768.0))))
            noise[i] = f32(s * math.sqrt(l * -2.0))
        self.noise = noise
        e = f32(0.0)
        for v in noise: e = f32(e + f32(v * v))
        a = f32(f32(1024.0) / e)
        self.g40 = f32(math.sqrt(float(f32(a / f32(40.0)))))
        self.g80 = f32(math.sqrt(float(f32(a / f32(80.0)))))
        self.noise_uv = fir_valid(self.hu, noise)       # +0x1050: noise filtered by unvoiced-band FIR
        self.reset()

    def reset(self):
        """slot 1 (0x1801100b0): srand(0x406), last pulse=0, prevF0=0, FIR history invalid."""
        self.rnd.srand(0x406)
        self.last = 0; self.prevf0 = f32(0.0)
        self.hist = None

    def pulses(self, f0, n, shift):
        """FUN_18002ce50: int pulse train; F0 in Hz, <=3.0 means unvoiced."""
        p = np.zeros(n, np.int32)
        s = 0
        for i in range(len(f0)):
            if s >= n: break
            f = f32(f0[i])
            if f <= f32(3.0):
                f = f32(0.0)
            else:
                if self.prevf0 <= f32(3.0):
                    p[s] = 1; self.last = s
                T = int(f32(f32(self.fs) / f))          # cvttss2si
                if T:
                    m = s
                    while m < s + shift:
                        k = ((m - self.last) & 0xffffffff) // T
                        if k >= 1:
                            step = T; base = self.last
                            for _ in range(k):
                                pos = step + base
                                if pos < 0: p[0] = 1
                                elif pos < n: p[pos] = 1
                                step += T; self.last = m; base = m
                        m += 1
            self.prevf0 = f
            s += shift
        self.last -= n
        return p

    def voiced_fir(self, p, n):
        """FUN_1800090e0: overlap-add of the voiced FIR at every pulse, with 41-sample pulse history."""
        h = self.hv; T = 41; out = np.zeros(n, np.float32)
        if self.hist is not None:
            for i in range(T):
                if self.hist[i]:
                    for k in range(T):
                        if i + k >= T and i + k - T < n:
                            out[i + k - T] = f32(h[k] + out[i + k - T])
        for m in range(n):
            if p[m]:
                for k in range(T):
                    if m + k < n: out[m + k] = f32(h[k] + out[m + k])
        if n < T:
            self.hist = np.concatenate([self.hist[n:] if self.hist is not None else np.zeros(T - n, np.int32), p])
        else:
            self.hist = p[n - T:].copy()
        return out

    def run(self, f0, n, shift):
        """FUN_18000ac88 (no MBE stream): pulses -> voiced FIR, then per-frame noise (FUN_18000adc0)."""
        p = self.pulses(f0, n, shift)
        out = self.voiced_fir(p, n)
        g = self.g40 if shift == 40 else self.g80
        for i in range(len(f0)):
            if (i + 1) * shift > n: break
            r = self.rnd.rand()
            off = shift + r % (1024 - 2 * shift)
            seg = slice(i * shift, (i + 1) * shift)
            if f32(f0[i]) > f32(3.0):
                out[seg] = (self.noise_uv[off:off + shift] * g + out[seg]).astype(np.float32)
            else:
                out[seg] = (g * self.noise[off:off + shift]).astype(np.float32)
        return out


def lsp2lpc(c, p):
    """FUN_180014640: cosines c[p] (float) -> a[p] (float), A(z)=1+sum a[k] z^-(k+1). Double arithmetic."""
    n = p // 2
    P = [1.0, float(f32(c[0] * f32(-2.0)))]
    Q = [1.0, float(f32(c[1] * f32(-2.0)))]
    for i in range(1, n):
        d = float(f32(c[2 * i] * f32(-2.0))); e = float(f32(c[2 * i + 1] * f32(-2.0)))
        P2 = [0.0] * (i + 2); Q2 = [0.0] * (i + 2)
        P2[0] = 1.0; Q2[0] = 1.0
        P2[i + 1] = d * P[i] + (P[i - 1] + P[i - 1])     # 2*P[i-1] computed first (addsd x,x)
        Q2[i + 1] = e * Q[i] + (Q[i - 1] + Q[i - 1])
        for j in range(i, 1, -1):
            P2[j] = d * P[j - 1] + P[j] + P[j - 2]
            Q2[j] = e * Q[j - 1] + Q[j] + Q[j - 2]
        P2[1] = d * P[0] + P[1]
        Q2[1] = e * Q[0] + Q[1]
        P, Q = P2, Q2
    a = np.zeros(p, np.float32)
    j = 1
    while j + 1 <= n - 1 + 1 and j <= n - 1:     # pairs (j, j+1) while j+1 <= n  (loop cond: j <= n-1)
        for jj in (j, j + 1):
            sp = P[jj] + P[jj - 1]; dq = Q[jj] - Q[jj - 1]
            a[jj - 1] = f32((dq + sp) * 0.5)
            a[p - jj] = f32((sp - dq) * 0.5)
        j += 2
    if j <= n:                                     # odd tail, different association
        dq = Q[j] - Q[j - 1]
        a[j - 1] = f32(((dq + P[j]) + P[j - 1]) * 0.5)
        a[p - j] = f32(((P[j] + P[j - 1]) - dq) * 0.5)
    return a


def softclip(y):
    """FUN_18006b4b0"""
    x = abs(float(y))
    if x > 31000.0:
        v = f32(32767.0 - math.exp((x - 31000.0) * -1.0 * 0.0005000000237487257) * 1767.0)
        if not (y > 0.0): v = f32(v * f32(-1.0))
        return int(v)
    return int(y)


class Synth:
    """CLsfSynthesizerImpl<float,float>::Synthesize = FUN_18006b620 (no spectrum warp, no power normalisation)."""
    def __init__(self, order):
        self.hist = np.zeros(order, np.float32)

    def run(self, lsf, gain, exc, shift):
        p = lsf.shape[1]; nfr = lsf.shape[0]
        out = np.zeros(nfr * shift, np.int16)
        B = np.zeros(p + shift, np.float32)
        B[:p] = self.hist
        for u in range(nfr):
            gv = f32(gain[u])
            g = f32(math.exp(float(gv))) if gv != 0.0 else f32(0.0)
            c = np.array([f32(math.cos(float(x) * math.pi + float(x) * math.pi)) for x in lsf[u]], np.float32)
            a = lsp2lpc(c, p)
            tries = 0
            while True:
                tries += 1
                bad = False
                for n in range(shift):
                    acc = f32(g * exc[u * shift + n])
                    for k in range(p):
                        acc = f32(acc - f32(B[n + p - 1 - k] * a[k]))
                    B[n + p] = acc
                    if tries < 5 and (acc > f32(31000.0) or acc < f32(-31000.0)):
                        bad = True; break
                    out[u * shift + n] = softclip(acc)
                if not bad: break
                fac = f32(0.99); m = f32(0.99)
                for k in range(p):
                    a[k] = f32(fac * a[k]); fac = f32(fac * m)
            B[:p] = B[shift:shift + p].copy()
        self.hist = B[:p].copy()
        return out


MINGAP = [f32(0.28) * f32(0.5), f32(0.7) * f32(0.5), f32(1.2) * f32(0.5), f32(1.8) * f32(0.5)]  # DAT_1801c0308 (runtime init)


def sharpen_pass(x, d, step, low, high):
    """FUN_180012750: one multi-interval formant-sharpening pass with interval d (float32 throughout)."""
    p = len(x); acc = np.zeros(p, np.float32); half = f32(0.5)
    for i in range(d, p - d):
        f = x[i]
        if f <= low:
            w = f32(f32(f32(f - f32(0.0)) * step) / f32(low - f32(0.0)))
        else:
            w = step
            if high <= f:
                w = f32(step - f32(f32(f32(f - high) * step) / f32(half - high)))
        fl = f32(f - x[i - d]); fr = f32(x[i + d] - f)
        c = f32(0.0)
        if fl != 0.0:
            den = f32(f32(f32(fr * fr) / fl) + fl)
            if den != 0.0: c = f32(f32(w * fr) / den)
        delta = f32(f32(fl - fr) * c)
        acc[i] = f32(delta + acc[i])
        for j in range(1, d):
            if fl != 0.0:
                acc[i - j] = f32(f32(f32(f32(f - x[i - j]) * delta) / fl) + acc[i - j])
            else:
                acc[i - j] = f32(acc[i - j] + f32(0.0))
            t = f32(0.0)
            if fr != 0.0: t = f32(f32(f32(x[i + j] - f) * delta) / fr)
            acc[i + j] = f32(t + acc[i + j])
    out = np.zeros(p, np.float32)
    out[0] = x[0]; out[p - 1] = x[p - 1]
    for k in range(1, p - 1):
        den = min(k, p - 1 - k, 2 * d - 1)
        out[k] = f32(f32(acc[k] / f32(den)) + x[k])
    return out


def lsf_sharpen(row, intervals, iters, step, low, high):
    """FUN_180012408, MultipleInterval=yes, FrequencyDependent=no branch."""
    x = row.astype(np.float32).copy(); p = len(x)
    d = intervals
    for it in range(iters):
        if d == 0: d = 1
        t = sharpen_pass(x, d, step, low, high)
        x[1:p - 1] = t[1:p - 1]
        d -= 1
    dd = intervals
    while dd - 1 > 0:
        d = dd - 1
        g = f32(MINGAP[dd - 2] / f32(p))
        for i in range(p - d):
            gap = f32(x[i + d] - x[i])
            if gap < g:
                adj = f32(f32(g - gap) * f32(0.5))
                x[i + d] = f32(x[i + d] + adj); x[i] = f32(x[i] - adj)
        dd = d
    return x


def read_dump(path):
    d = open(path, 'rb').read(); o = 0; recs = []
    while o < len(d):
        tag = d[o:o + 4].decode(); n = struct.unpack_from('<I', d, o + 4)[0]
        recs.append((tag, d[o + 8:o + 8 + n])); o += 8 + n
    return recs


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else r'D:/llm-experiments/misk/zira/harness/vocdump.bin'
    recs = read_dump(path)
    exc = None; syn = None
    for tag, b in recs:
        if tag == 'EXC0':
            rows, cols, n, sh = struct.unpack_from('<4I', b)
            f0 = np.frombuffer(b, np.float32, rows * cols, 16).reshape(rows, cols)[:, 0]
            ref = np.frombuffer(b, np.float32, n, 16 + rows * cols * 4)
            if exc is None: exc = Excitation(16000)
            got = exc.run(f0, n, sh)
            bad = np.nonzero(got.view(np.uint32) != ref.view(np.uint32))[0]
            print(f'EXC0 frames={rows} n={n}: {len(bad)} mismatching samples' + (f' first@{bad[0]} got {got[bad[0]]!r} ref {ref[bad[0]]!r}' if len(bad) else ''))
        elif tag == 'SYN0':
            rows, order, grows, gcols, n, sh, itf = struct.unpack_from('<7I', b)
            o = 40
            lsf = np.frombuffer(b, np.float32, rows * order, o).reshape(rows, order); o += rows * order * 4
            g = np.frombuffer(b, np.float32, grows * gcols, o).reshape(grows, gcols)[:, 0]; o += grows * gcols * 4
            e = np.frombuffer(b, np.float32, n, o); o += n * 4
            ref = np.frombuffer(b, np.int16, n, o)
            if syn is None: syn = Synth(order)
            got = syn.run(lsf, g, e, sh)
            bad = np.nonzero(got != ref[:len(got)])[0]
            print(f'SYN0 frames={rows} order={order} n={n}: {len(bad)} mismatching samples' + (f' first@{bad[0]} got {got[bad[0]]} ref {ref[bad[0]]}' if len(bad) else ''))
        elif tag == 'RSET':
            print('RSET (utterance end: excitation/synth reset)')
            if exc is not None: exc.reset()
            if syn is not None: syn.hist[:] = 0
        elif tag == 'SHRP':
            rows, order = struct.unpack_from('<2I', b)
            bef = np.frombuffer(b, np.float32, rows * order, 8).reshape(rows, order)
            aft = np.frombuffer(b, np.float32, rows * order, 8 + rows * order * 4).reshape(rows, order)
            nb = 0; nsk = 0
            for r in range(rows):
                if np.array_equal(bef[r], aft[r]): nsk += 1; continue
                got = lsf_sharpen(bef[r], 2, 3, f32(0.22), f32(0.075), f32(0.4))
                if not np.array_equal(got.view(np.uint32), aft[r].view(np.uint32)): nb += 1
            print(f'SHRP frames={rows} order={order}: {nb} mismatching frames, {nsk} frames left unchanged')


if __name__ == '__main__':
    main()
