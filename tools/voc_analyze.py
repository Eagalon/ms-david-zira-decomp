"""Analyse a 16 kHz WAV into OneCore vocoder parameters and resynthesize it with the ported vocoder.

Experiment: how much of Anna survives David's vocoder?  Per 80-sample (5 ms) frame we estimate
  * 24th order LPC -> line spectral frequencies, normalized 0..0.5 (what zb_vocoder expects),
  * F0 by normalized autocorrelation (<=3 Hz means unvoiced),
  * a log gain, calibrated by running the vocoder and matching its per-frame level to the original.

usage: python voc_analyze.py in.wav out.wav [--voice PATH] [--iters 3] [--no-sharpen] [--keep-params F]
"""
import argparse
import os
import struct
import subprocess
import sys
import wave

import numpy as np

SHIFT = 80
ORDER = 24
BWEXP = 0.995
HERE = os.path.dirname(os.path.abspath(__file__))
EXE = os.path.join(HERE, "..", "build", "x64", "zb_vocode_test.exe")
VOICE = "C:/Windows/Speech_OneCore/Engines/TTS/en-US/M1033David"


def read_wav(path):
    with wave.open(path, "rb") as w:
        assert w.getnchannels() == 1 and w.getsampwidth() == 2, "want 16-bit mono"
        rate = w.getframerate()
        x = np.frombuffer(w.readframes(w.getnframes()), dtype="<i2").astype(np.float64)
    return x, rate


def levinson(r, p):
    """autocorrelation -> a[0..p] with A(z) = 1 + a1 z^-1 + ... (y[n] = -sum a_k y[n-k])"""
    a = np.zeros(p + 1)
    a[0] = 1.0
    e = r[0]
    if e <= 0:
        return a, 1.0
    for i in range(1, p + 1):
        acc = r[i] + np.dot(a[1:i], r[i - 1:0:-1]) if i > 1 else r[i]
        k = -acc / e
        a[1:i + 1] = a[1:i + 1] + k * a[i - 1::-1][:i]
        e *= 1.0 - k * k
        if e <= 0:
            return a, max(e, 1e-12)
    return a, e


def lpc_to_lsf(a):
    """-> two sorted arrays of normalized frequencies (0..0.5): roots of the sum / difference polys"""
    p = len(a) - 1
    ar = a[::-1]
    P = np.concatenate([a, [0.0]]) + np.concatenate([[0.0], ar])   # root at z = -1
    Q = np.concatenate([a, [0.0]]) - np.concatenate([[0.0], ar])   # root at z = +1
    P = np.polydiv(P, np.array([1.0, 1.0]))[0]
    Q = np.polydiv(Q, np.array([1.0, -1.0]))[0]
    fp = np.sort(np.angle(np.roots(P)))
    fq = np.sort(np.angle(np.roots(Q)))
    fp = fp[fp > 1e-9] / (2 * np.pi)
    fq = fq[fq > 1e-9] / (2 * np.pi)
    return fp, fq


def lsp2lpc(c):
    """port of lsp2lpc() in zb_vocoder.c, so we can check our LSF ordering round-trips"""
    p = len(c)
    n = p // 2
    P = np.zeros(p + 10)
    Q = np.zeros(p + 10)
    P[0] = Q[0] = 1.0
    P[1] = -2.0 * c[0]
    Q[1] = -2.0 * c[1]
    for i in range(1, n):
        d, e = -2.0 * c[2 * i], -2.0 * c[2 * i + 1]
        P2, Q2 = P.copy(), Q.copy()
        P2[i + 1] = d * P[i] + 2 * P[i - 1]
        Q2[i + 1] = e * Q[i] + 2 * Q[i - 1]
        for j in range(i, 1, -1):
            P2[j] = d * P[j - 1] + P[j] + P[j - 2]
            Q2[j] = e * Q[j - 1] + Q[j] + Q[j - 2]
        P2[1] = d * P[0] + P[1]
        Q2[1] = e * Q[0] + Q[1]
        P, Q = P2, Q2
    a = np.zeros(p)
    for j in range(1, n + 1):
        sp = P[j] + P[j - 1]
        dq = Q[j] - Q[j - 1]
        a[j - 1] = (dq + sp) * 0.5
        a[p - j] = (sp - dq) * 0.5
    return a


def frame_lsf(x, T, order):
    """LPC + LSF per frame; returns lsf[T, order] and the residual energy per sample"""
    win_len = 400
    win = np.hanning(win_len + 2)[1:-1]
    lag = np.exp(-0.5 * (2 * np.pi * 60.0 / 16000.0 * np.arange(order + 1)) ** 2)  # 60 Hz lag window
    lsf = np.zeros((T, order), dtype=np.float32)
    err = np.zeros(T)
    prev = None
    flip = [None]
    for t in range(T):
        c = t * SHIFT + SHIFT // 2
        s, e = c - win_len // 2, c + win_len // 2
        seg = np.zeros(win_len)
        a0, b0 = max(s, 0), min(e, len(x))
        if b0 > a0:
            seg[a0 - s:b0 - s] = x[a0:b0]
        seg = seg * win
        r = np.correlate(seg, seg, "full")[win_len - 1:win_len - 1 + order + 1]
        if r[0] < 1e-6:
            lsf[t] = prev if prev is not None else np.arange(1, order + 1) / (2.0 * (order + 1))
            err[t] = 0.0
            continue
        r = r * lag
        r[0] *= 1.0001                      # ridge, keeps the fit stable
        a, e2 = levinson(r, order)
        a = a * (BWEXP ** np.arange(order + 1))     # bandwidth expansion, keeps sharp poles from ringing
        fp, fq = lpc_to_lsf(a)
        if len(fp) != order // 2 or len(fq) != order // 2:
            lsf[t] = prev if prev is not None else np.arange(1, order + 1) / (2.0 * (order + 1))
            err[t] = e2 / win_len
            continue
        if flip[0] is None:                 # which set goes to the even slots? decide once, by round-trip
            best, bestv = None, None
            for cand in (0, 1):
                v = np.empty(order)
                v[0::2], v[1::2] = (fp, fq) if cand == 0 else (fq, fp)
                d = np.abs(lsp2lpc(np.cos(2 * np.pi * v)) - a[1:]).max()
                if bestv is None or d < bestv:
                    best, bestv = cand, d
            flip[0] = best
            print("LSF interleave: %s set first (round-trip error %.2e)" % ("P" if best == 0 else "Q", bestv))
        v = np.empty(order)
        v[0::2], v[1::2] = (fp, fq) if flip[0] == 0 else (fq, fp)
        lsf[t] = v
        prev = lsf[t]
        err[t] = e2 / win_len
    return lsf, err


def frame_f0(x, T, fmin=60.0, fmax=400.0, rate=16000):
    """normalized autocorrelation pitch, one value per frame (0 = unvoiced)"""
    win_len = 512
    lo, hi = int(rate / fmax), int(rate / fmin)
    f0 = np.zeros(T, dtype=np.float32)
    rms = np.zeros(T)
    for t in range(T):
        c = t * SHIFT + SHIFT // 2
        s = c - win_len // 2
        seg = np.zeros(win_len)
        a0, b0 = max(s, 0), min(s + win_len, len(x))
        if b0 > a0:
            seg[a0 - s:b0 - s] = x[a0:b0]
        rms[t] = np.sqrt(np.mean(seg ** 2))
        if rms[t] < 20.0:
            continue
        seg = seg - seg.mean()
        ac = np.correlate(seg, seg, "full")[win_len - 1:]
        e0 = ac[0]
        if e0 <= 0:
            continue
        # normalize by the energy of the shifted window so long lags are not penalized
        norm = np.array([np.sqrt(np.dot(seg[k:], seg[k:]) * e0) + 1e-9 for k in range(lo, hi + 1)])
        nac = ac[lo:hi + 1] / norm
        k = int(np.argmax(nac))
        if nac[k] > 0.40:
            f0[t] = rate / float(lo + k)
    # median smoothing of the voiced track, and drop single-frame islands
    v = f0 > 0
    for t in range(1, T - 1):
        if v[t] and not v[t - 1] and not v[t + 1]:
            f0[t] = 0.0
    sm = f0.copy()
    for t in range(T):
        a0, b0 = max(0, t - 2), min(T, t + 3)
        w = f0[a0:b0]
        w = w[w > 0]
        if f0[t] > 0 and len(w):
            sm[t] = np.median(w)
    return sm, rms


def write_params(path, f0, gain, lsf):
    T, p = lsf.shape
    with open(path, "wb") as f:
        f.write(b"ZVOC" + struct.pack("<ii", T, p))
        for t in range(T):
            f.write(struct.pack("<ff", float(f0[t]), float(gain[t])))
            f.write(np.asarray(lsf[t], dtype="<f4").tobytes())


def smooth_energy(r, k=2):
    """rms over a +-k frame window, so pulse placement inside a frame does not drive the gain"""
    e = r ** 2
    out = np.zeros_like(e)
    for t in range(len(e)):
        a0, b0 = max(0, t - k), min(len(e), t + k + 1)
        out[t] = e[a0:b0].mean()
    return np.sqrt(out)


def frame_rms(x, T):
    out = np.zeros(T)
    for t in range(T):
        seg = x[t * SHIFT:(t + 1) * SHIFT]
        if len(seg):
            out[t] = np.sqrt(np.mean(seg ** 2))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("dst")
    ap.add_argument("--voice", default=VOICE)
    ap.add_argument("--iters", type=int, default=3)
    ap.add_argument("--no-sharpen", action="store_true")
    ap.add_argument("--keep-params")
    ap.add_argument("--exe", default=EXE)
    ap.add_argument("--headroom", type=float, default=10.0, help="dB below the original, to stay off the soft clipper")
    args = ap.parse_args()

    x, rate = read_wav(args.src)
    assert rate == 16000, "the vocoder runs at 16 kHz"
    T = len(x) // SHIFT
    print("%d frames (%.2f s)" % (T, len(x) / rate))

    lsf, err = frame_lsf(x, T, ORDER)
    f0, _ = frame_f0(x, T, rate=rate)
    target = frame_rms(x, T)
    voiced = int((f0 > 0).sum())
    print("voiced %d/%d frames, median F0 %.1f Hz" % (voiced, T, np.median(f0[f0 > 0]) if voiced else 0))

    params = args.keep_params or os.path.join(os.path.dirname(os.path.abspath(args.dst)), "_voc_params.bin")
    target = target * (10.0 ** (-args.headroom / 20.0))
    silent = target <= 1.0
    gain = np.log(np.maximum(np.sqrt(err), 1e-3))    # first pass: the LPC residual level, then calibrate
    for it in range(args.iters):
        g = gain.copy()
        g[np.abs(g) < 1e-6] = 1e-6                   # gain exactly 0 makes the engine output silence
        g[silent] = 0.0
        write_params(params, f0, g, lsf.copy())
        cmd = [args.exe, args.voice, params, args.dst]
        if args.no_sharpen:
            cmd.append("--no-sharpen")
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode:
            sys.exit("vocoder failed: %s%s" % (r.stdout, r.stderr))
        y, _ = read_wav(args.dst)
        got = frame_rms(y, T)
        st, sg = smooth_energy(target), smooth_energy(got)
        ratio = np.where((sg > 1e-6) & (st > 1.0), st / np.maximum(sg, 1e-6), 1.0)
        gain = gain + np.clip(np.log(np.maximum(ratio, 1e-6)), -3.0, 3.0)
        for t in range(1, len(gain)):                # slew limit: no more than ~9 dB per 5 ms
            gain[t] = np.clip(gain[t], gain[t - 1] - 1.05, gain[t - 1] + 1.05)
        db = 20 * np.log10(np.maximum(st[~silent], 1e-6) / np.maximum(sg[~silent], 1e-6))
        print("pass %d: level error mean %.2f dB, |err| median %.2f dB, max %.1f dB"
              % (it + 1, db.mean(), np.median(np.abs(db)), np.abs(db).max()))
    # final render with the converged gains
    g = gain.copy()
    g[np.abs(g) < 1e-6] = 1e-6
    g[silent] = 0.0
    write_params(params, f0, g, lsf.copy())
    cmd = [args.exe, args.voice, params, args.dst] + (["--no-sharpen"] if args.no_sharpen else [])
    subprocess.run(cmd, check=True)
    y, _ = read_wav(args.dst)
    n = min(len(x), len(y))
    num = float(np.dot(x[:n], x[:n]))
    den = float(np.dot(x[:n] - y[:n], x[:n] - y[:n])) + 1e-9
    print("wrote %s  (waveform SNR %.1f dB - not meaningful for a vocoder, listen instead)"
          % (args.dst, 10 * np.log10(num / den)))


if __name__ == "__main__":
    main()
