# OneCore SPS vocoder (David / Zira / Mark) — MSTTSEngine_OneCore.dll 10.3.21207 (x64)

Scope: everything after the acoustic parameter streams exist (F0 / LSF / gain per 5 ms frame), up to the PCM
handed to SAPI. Parameter generation (trees, durations, MLPG, DelayMode streaming) is in other notes.

**Status: the whole default chain is verified bit-exact** against the live engine with a call-site-hooking probe
(`harness/vocprobe.c`) and reference models (`tools/vocoder_model.py` float path, `tools/vocoder_model_int.py`
fixed-point path): LsfSharpen, excitation (including the CRT `rand()` stream), LSP→LPC, the all-pole synthesis, the
soft clipper, and for David also the final WAV (volume stage + silence zeroing). Test sentences: 3-sentence text
for David, 2-sentence text for OneCore Zira, all chunks and utterance resets included; 0 mismatching samples.

## 0. Which path each voice uses (verified at runtime)

| voice | APM header u32 @file 0x24 | vocoder path | excitation vtbl | synth vtbl | LSF order | streams present |
|---|---|---|---|---|---|---|
| David (OneCore) | 0 | **float** | `CExcitationGeneratorImpl<float>` 0x180177ae8 | `CLsfSynthesizerImpl<float,float>` 0x180177a68 | 24 | F0 1, LSF 24, gain 1 (no MBE, no power) |
| Zira (OneCore) | 1 | **fixed point (int)** | `CExcitationGeneratorImpl<int>` 0x180177aa8 | `CLsfSynthesizerImpl<short,int>` 0x180177a90 | 24 | same, int32 matrices |
| Mark (OneCore) | 1 | fixed point | same as Zira | same as Zira | 24 | same |
| Eva (neural) | 0 | float + `CITFTEExcitationGeneratorImpl<float>` if NN voice data flag (+0x9d4) set | 0x180177b18 | | | NN streams |

- fs = 16000, frame shift = 80 samples (5 ms) for all three (vocoder +8 / +0xc; they come from the engine setting
  struct at CTTSEngine+0xa0: +0x40 fs, +0x48 shift, +0x58 int flag, +0x68 SilenceNoiseSuppress; the APM header block
  at file 0x18 has fs@0x28=16000, bits@0x2c=16, 0x50=80 @0x30 — matching; the header->setting copy itself was not
  traced, the *mapping* file 0x24 → int path is inferred from David=0 / Zira=Mark=1 and the observed paths).
- ITFTE (`CITFTEExcitationGeneratorImpl`, "improved time-frequency trajectory excitation") is only chosen in
  `FUN_180052f70` when the NN setting (`FUN_1800901b8(engine+0x200)+0x9d4`) is non-zero → Eva only. David/Zira/Mark
  never use it (verified via vtable RVAs above). MBE (5-band voicing stream) is not present for David/Zira/Mark
  (`MultiBandExcitation.Enabled`, engine+0x9c0, default off); the MBE code path is documented below anyway.
- Matrices everywhere are `struct {u32 rows; u32 cols; T *data;}` (T = float or int32); views via `FUN_180077f3c`.

## 1. Object graph and call flow

```
CWaveGenerator (vtbls 0x180172ff0 @0, 0x180173060 @8, 0x180173040 @0x10, 0x180173030 @0x28), size 0x220
  +0x80 CTTSEngine*, +0x88 output/site object, +0x90 = engine+0xa0 (voice settings, see FUN_180056c00)
  +0x98 CRateChanger / CRateChangerSonic (VoiceSetting.WaveScale == "Sonic")
  +0xa0 CWaveSmoother (240-sample linear ramp, FUN_18011287c(this+0xa0, 0xf0, ...))
  +0x150 CSpsVocoder* (size 0x110, ctor FUN_18010d3f0, init FUN_180052f70)
  +0x200 NUS/SPS junction joiner (created by FUN_180104c08 when a NUS inventory is used)
  +0x218 "voice has NUS domain data" (selects SpsVolumeAdjustment, see §6)

Init   FUN_180104910 (slot0) -> FUN_1801046e4: rate changer, CSpsVocoder, FUN_180052f70(vocoder, sharpenSettings=
       settings+0xf8, engine, settings+0x58 (int flag), +0x40 (fs), +0x48 (shift), +0x68 (SilenceNoiseSuppress))
Begin utterance FUN_180057df0 (vtbl@8 slot6) -> FUN_180110450(vocoder, utt, wavegen+0x20c):
       clears chunk counters, vocoder+0xf4 = utt+0xb8 (spectrum warp offset), DRC/biquad enables from the
       utterance's domain (+0xa4 DrcEnable, +0xa8 BiquadFilterEnable), FUN_18010ee30 ...
Process FUN_180032150 (vtbl@8 slot7):
   SPS units  -> FUN_1800321f0:  per chunk of phones
        vocoder+0x38==0 ? FUN_18010ca5c (float prepare) : FUN_18010c148 (int prepare)
        loop:   vocoder+0x38==0 ? FUN_180009b14 (float synth block) : FUN_180074968 (int synth block)
                then FUN_18004e460 (rate/volume/effects/output) per block
   NUS units  -> FUN_180032828 (unit concatenation, not covered here)
   end of utterance -> FUN_18011024c(vocoder): excitation slot1 reset (srand(0x406)), synth slot1 reset (history=0)
```

CSpsVocoder fields (size 0x110): +8 fs, +0xc shift, +0x10 int16 output buffer (vector), +0x30 junction joiner (NULL
for pure SPS David), +0x38 int flag, +0x3c SilenceNoiseSuppress, +0x40 CFormantSharpenSetting*, +0x48 excitation,
+0x50 synthesizer, +0x58 DRC, +0x60 CBiquadsFilterSetting container, +0x68 CCombFilter (echo, `EchoSetting.*`),
+0x70 per-utterance echo (utt+0xb0), +0x78 use +0x70, +0x7c NUS-trajectory mix mode, +0xa8 NN streaming,
+0xb0 current chunk descriptor, +0xb8 output descriptor, +0xc0 engine, +0xd0/+0xd4/+0xd8 chunk counters,
+0xe4 DelayMode/streaming flag (David 0, Zira/Mark 1), +0xe8 "last chunk" flag, +0xf0 Vocoder.PowerEnabled,
+0xf4 spectrum warp offset, +0xf8..+0x108 LSPDecomposing.{LsfBaseModelStep=4, LsfOverlappedStep=3,
LsfOverlappedModelRange=7, F0ForwardModelRange=5, F0BackwardModelRange=4} (defaults from ctor; used by NN/Eva),
+0x10c ITFTE flag.

Chunk descriptor (0x98 bytes, `vocoder+0xb0`, built in prepare): +0 #phones, +4 #frames, +8 head trim, +0xc tail
trim, +0x18 Mat* durations (#phones x 5 states, frames per state), +0x28 F0, +0x30 LSF, +0x38 gain, +0x40 MBE,
+0x48 power, +0x50/+0x58/+0x60 ITFTE/NN streams, +0x68 frames done, +0x6c samples done, +0x70 current phone,
+0x78 float excitation buffer. The acoustic space (`CTTSAcousticSpaceImpl<float|int>` at utt+0x2c8, or +0x2c8+0x208
when utt+0x2c0 != 0) holds the full-utterance streams at qword index [1]=durations, [3]=per-frame flag array
(LsfSharpen skips frames whose flag != 0; all frames were 0 in tests; guess: NUS-copied frames),
[0x18]=F0, [0x19]=LSF, [0x1b]=gain, [0x1c]=MBE, [0x1d]=power, [0x1e..0x20]=NN/ITFTE.

## 2. Parameter conditioning in "prepare" (FUN_18010ca5c float / FUN_18010c148 int)

In this order, on the chunk's LSF matrix:
1. **Edge replication** `FUN_1800a1ec4` (int: `FUN_1800a1db0`)(LSF, gain, head, tail): head=10 if this is the first
   chunk of the utterance, tail=10 if it is the last. LSF rows 0..9 := row 10; rows N-10..N-1 := row N-11. If
   N <= head+tail, LSF *and gain* are zero-filled (utterance silent).
2. **LsfSharpen** `FUN_180012408` (int: `FUN_18003adb0`) — see §3.
3. **LSF repair** `FUN_18006bfec` (int `FUN_18006cc7c`) per frame: if not strictly increasing → bubble sort
   (`FUN_18006c12c`); then if any value <0 or >0.5 (int: Q15 >16384) → copy previous frame, or for frame 0
   `FUN_18006c18c` (linear re-spacing via `FUN_1800a186c`).
Frame-level UV decision / F0 zeroing happens earlier (param gen): the vocoder treats F0 <= 3.0 as unvoiced.

## 3. LsfSharpen (formant sharpening in the LSF domain) — verified bit-exact (float and int)

Settings object `CFormantSharpenSetting` (0x28 B, reader `FUN_1800542f0`, ctor defaults in `FUN_180056c00`):
+8 FrequencyDependent (0), +0xc MultipleInterval (0), +0x10 Intervals (2, valid 1..5), +0x14 Iterations (1, <=10),
+0x18 Step (0.4 single / 0.3 multi if "null"; must be in (0,1)), +0x1c TopStep (0.7), +0x20 LowFrequency,
+0x24 HighFrequency. **Built-in defaults table** at 0x18016d790 ({wchar* key, wchar* default}, 0x89 entries,
`FUN_18002a43c`) supplies LowFrequency="0.075f", HighFrequency="0.4f" when the INI has none — so David/Zira
effectively run with Low=0.075, High=0.4 (verified at runtime). Effective values: David/Zira: multi, Intervals=2,
Iterations=3, Step=0.22; Mark: Step=0.25.

Branches: FrequencyDependent → `FUN_18010bf6c` (TopStep; unused by these voices); single-interval →
`FUN_180012b60` (unused); **MultipleInterval** (all three voices):

```
x = lsf row (p=24, normalized frequency in [0,0.5]; int path: Q15, 0.5 = 16384)
d = Intervals
repeat Iterations times:                       # FUN_180012750 (int FUN_18003b084)
    if d == 0: d = 1
    acc[0..p-1] = 0
    for i in d .. p-d-1:
        f = x[i]
        w = f <= Low ? f*Step/Low : (f >= High ? Step - (f-High)*Step/(0.5-High) : Step)
        fl = f - x[i-d];  fr = x[i+d] - f
        c = (fl != 0 && (den = fr*fr/fl + fl) != 0) ? w*fr/den : 0
        delta = (fl - fr) * c                  # int: ((fl-fr)*c)/32768
        acc[i] += delta
        for j in 1..d-1:
            acc[i-j] += fl ? (f - x[i-j])*delta/fl : 0
            acc[i+j] += fr ? (x[i+j] - f)*delta/fr : 0
    for k in 1..p-2: x[k] += acc[k] / min(k, p-1-k, 2d-1)     # x[0], x[p-1] unchanged
    d -= 1
for d in Intervals-1 .. 1:                      # minimum spacing
    g = MINGAP[d-1] / p     # float: {0.14,0.35,0.6,0.9} (DAT_1801c0308 = DAT_180185a00*0.5, runtime init FUN_180001420)
                            # int:   {4587,11468,19660,29491}/p (DAT_1801c0320 = (int)(tab*16384), FUN_1800013e0)
    for i in 0..p-d-1: if x[i+d]-x[i] < g: a=(g-gap)*0.5 (int: /2); x[i+d]+=a; x[i]-=a
```
Float: every operation in float32 exactly as written (w computed as ((f-0)*Step)/(Low-0) etc.). Int: Step/Low/High
converted as `(short)(int)(v*32768.0f)`; all divisions are C truncating divisions.

## 4. Excitation

### 4.1 Init (`FUN_18010ebf0` float / `FUN_18010eaa0` int; excitation object 0x1068 B)
- Band table `DAT_18017d3c0`: 5 × 41-tap linear-phase FIRs (double) splitting 0..fs/2 into 5 bands; default band
  voicing strengths `DAT_1801927f8` (16 kHz) = {1.0, 0.9, 0.5, 0.4, 0.3} (8 kHz: `DAT_1801927d0` = {1,1,1,0.9,0.5});
  a voice-supplied table at exc+0x1038 overrides (none for these voices).
- `FUN_18003c060`: hv[k] = (float)Σ_b w_b·h_b[k], hu[k] = (float)Σ_b (1−w_b)·h_b[k] (double accumulation).
  hv → voiced FIR (exc+0x1040, `CFIRFilter<float>`; int path: taps `(int)(short)(int)(8192.0f*hv)` Q13).
- `FUN_18006b550` noise table (1024 floats at exc+0x28): **`srand(0x406)`**, then for each i:
  `r1=rand(); r2=rand(); n=(float)( sin((double)((float)(r2+1)*2^-15)*2π) * sqrt(log((double)((float)(r1+1)*2^-15))*-2) )`
  (UCRT `rand` LCG: s=s*214013+2531011, (s>>16)&0x7fff; UCRT sin/log/sqrt).
- E = Σ n² (float); a = 1024/E; `FUN_18010dea0`: g40 = (float)sqrt(a/40), g80 = (float)sqrt(a/80)
  (David observed 0.165253788 / 0.116852067). Int (`FUN_18010b7e0`): i1=(int)(a*16384*16384);
  g = (short)(int)sqrt((double)(i1/40 or i1/80)) → 2707 / 1914.
- +0x1048 = raw noise, +0x1050 = noise filtered by hu with `FUN_18000b1f0` ("valid" FIR: out[n]=Σ_k hu[k]x[n−k]
  for n>=40, first 41 outputs 0; **products in float, accumulated in double**, stored float). Int path: raw →
  `(short)(int)(8192*x)` (Q13), filtered → `(short)(int)(16384*x)` (Q14).
- Then slot1 reset (`0x1801100b0`): FIR history invalid, **`srand(0x406)`** again, last-pulse=0, prevF0=0. The same
  reset runs at the end of every utterance (`FUN_18011024c`), so each sentence's noise sequence restarts from seed
  0x406 (verified across 3 sentences). NB: `rand` state is per thread; the engine's synthesis runs on one thread.

### 4.2 Per block (float `FUN_18000ac88` / int `FUN_18010e0d4`), no MBE stream
1. Pulse train `FUN_18002ce50` (int `FUN_18004b864`), int array of 0/1 marks, state (last pulse position relative to
   block start at +0x102c, prevF0 at +0x1060):
   ```
   for frame i (start s=i*shift): f=F0[i]
     if f <= 3.0: f = 0 (unvoiced)
     else:
       if prevF0 <= 3.0: mark[s]=1; last=s          # voicing onset: pulse at frame start
       T = (int)(fs/f)   (float div, cvttss2si; int path: fs / F0 unsigned int division, F0 in Hz as int)
       for m in s..s+shift-1:
         k = (u32)(m-last) / T
         if k>=1: pos=last+T; mark[pos]; last=m; then for further k: pos=m+2T, m+3T... (quirk, only if T shrank)
     prevF0 = f
   last -= nsamples
   ```
2. Optional pulse filter object at exc+0x18 (NULL for these voices).
3. Voiced FIR `FUN_1800090e0` (int `FUN_180041890`): out = 0; first the 41-sample pulse history from the previous
   block contributes its tails, then every mark at m adds hv[0..40] to out[m..m+40] (float adds `h+out`), history :=
   last 41 marks. (Pulse amplitude 1; int: Q13 taps.)
4. Noise mix `FUN_18000adc0` (int `FUN_180060d58`), per frame i: `r=rand(); off = shift + r % (1024 − 2·shift)`;
   - voiced (F0>3): out[k] = noise_uv[off+k]*g + out[k]; int: out = (g·filt_q14)/16384 + 2·out (Q14 result)
   - unvoiced: out[k] = g*noise[off+k] (overwrites pulse tails); int: out = (g·raw_q13)/8192
   (g = g80 for shift 80, g40 for shift 40; any other shift is an error.)
   Float excitation ≈ unit pulses + noise with ~1/shift power per sample; int excitation is Q14.

### 4.3 MBE variant (float `FUN_1800097dc`, int `FUN_18010df8c`/`FUN_18000b3dc`) — not used by David/Zira/Mark
Per frame the 5 MBE values v_b (int path: v/32768) replace the default band strengths: voiced FIR taps =
Σ v_b h_b (`FUN_18010e630` → `FUN_18010de54` + overlap-add); unvoiced frames: noise[k + r%(1024−shift)]*g; voiced
frames: 120-sample slice of raw noise at `r % (1024−shift−40)` filtered with Σ(1−v_b)h_b ("valid" part, last 80
samples) × g added.

## 5. LSF → LPC and all-pole synthesis — verified bit-exact

### Float (`FUN_18006b620`, called from `FUN_180009b14` at 0x18000a42f)
Args: (synth, Mat* LSF, Mat* gain, float* exc, int16* out, nsamples, shift, itfte, warp α, float* warpvec,
Mat* power, Mat* F0, fs). Per frame u:
- g = gain[u] != 0 ? (float)exp((double)gain[u]) : 0 (`FUN_18006b3fc`; gain stream = natural-log amplitude).
- c[k] = (float)cos(2·((double)lsf[k]·π)); a[] = `FUN_180014640`(c, p): double arithmetic,
  K = −2.0f, P = [1, K·c0], Q = [1, K·c1]; for i=1..p/2−1 with d=K·c[2i], e=K·c[2i+1] (float products):
  `P'[i+1] = d·P[i] + (P[i−1]+P[i−1])` (note association), `P'[j] = (d·P[j−1] + P[j]) + P[j−2]` for j=i..2,
  `P'[1] = d·P[0] + P[1]`, same for Q with e; then for j=1..p/2 (pairs loop):
  `a[j−1] = (float)(((Q[j]−Q[j−1]) + (P[j]+P[j−1]))·0.5)`, `a[p−j] = (float)(((P[j]+P[j−1]) − (Q[j]−Q[j−1]))·0.5)`
  (odd p/2 tail uses `((dq + P[j]) + P[j−1])`). A(z) = 1 + Σ a[k] z^−(k+1).
- y[n] = g·e[n]; for k=0..p−1: y −= y[n−1−k]·a[k] (float32, sequential, no FMA). History (p samples) persists
  across blocks and chunks; reset to 0 at utterance end.
- Stability: if |y| > 31000 on attempt < 5 → `FUN_18010df58` a[k] *= 0.99^(k+1) (float running power) and the
  whole frame is recomputed (max 4 expansions).
- out = `FUN_18006b4b0`(y): |y| <= 31000 → (int)y (truncation); else
  `32767 − 1767·exp(−(|y|−31000)·0.0005000000237)` with sign, truncated. Output is **int16 directly**.
- Not active for these voices: spectrum warp (param 9/10: α = clamp((SpectrumAdjustment−100)/100 + utt warp,
  −1, 1)·0.25, warp vector (−α)^(k+1); only if VoiceSetting.SpectrumAdjustment != 100 or utt+0xb8 != 0), and power
  normalisation (Vocoder.PowerEnabled, 10-iteration gain correction to exp(power) mean-abs).

### Int (`FUN_18006c250`, called from `FUN_180074968` at 0x180074f15) — Zira/Mark
- g = G != 0 ? exp_tab[min((G+128)/256, 1330)] : 0; G = int log-gain (Q15 of ln); exp_tab = `DAT_1801876d0`
  (1331 int16 ≈ trunc(exp(i/128))).
- c[k] = cos_tab[min(lsf/8, 2047)], cos_tab = `DAT_1801866d0` (2048 int16 ≈ round(32767·cos(2πi/4096))).
- a = `FUN_18003b460`: int64 Q30 polynomials; P=[2^30, −65536·c0], Q=[2^30, −65536·c1]; iteration i=1..n−1 takes
  pair index idx = i even ? 2i : (n even ? 2(n−i) : 2(n−i)−2) (permuted order!), d=−2c[idx], e=−2c[idx+1];
  `P'[i+1] = ((d·P[i])>>15) + 2P[i−1]`, `P'[j] = ((d·P[j−1])>>15) + P[j−2] + P[j]`, `P'[1] = ((d·P[0])>>15)+P[1]`;
  a[j−1] = trunc((ΔQ + P[j]+P[j−1]) / 32768), a[p−j] = trunc((P[j]+P[j−1] − ΔQ)/32768).
- acc = (int64)e[n]·g·4 − Σ y[n−1−k]·a[k]; y = clamp(acc>>16, −32768, 32767) (history is int16);
  retry as float path with a[k] = (int)((float)a[k]·0.99^(k+1)) (`FUN_18010bc78`); out = soft clip of (float)y
  (`FUN_18006b428`, same constants).

## 6. After synthesis (per block, `FUN_180009b14`/`FUN_180074968`, then `FUN_18004e460`)
1. **Silence zeroing** (in the synth block): for each silence phone (`FUN_18001d540`), with 5 states:
   SilenceNoiseSuppress (vocoder+0x3c) = 0 (all three voices): zero states [s0..s1] where s0 = 0 if the previous
   phone is missing/silence else 2, s1 = 4 if the next phone is missing/silence else 2 (i.e. an internal pause keeps
   its first/last two states of synthesized noise-floor, sentence-initial/final silence is zeroed from/to the
   edge); SilenceNoiseSuppress=1: states 0..4. Verified on the WAV (zero runs start on frame boundaries).
   (prev/next = `FUN_18005488c`/`FUN_180035600`, identification as prev/next is a guess consistent with data.)
2. NUS junction smoothing `FUN_18000a744` (int `FUN_18010b8ac`) only when vocoder+0x30 (joiner) exists and the
   neighbour is a NUS unit (NULL for normal David text).
3. **Rate** `FUN_18004dd00`: SAPI rate is realised in the durations (verified: `<rate absspeed=5>` gives fewer
   frames, WAV length == synth length). The Sonic changer (`CRateChangerSonic` 0x180179238, embedded Sonic:
   create `FUN_180086110`, setSpeed `FUN_180086420`, write `FUN_180086440`, flush `FUN_180086200`, read
   `FUN_180086320`) is only engaged for units with flag +0xe0 (NUS) or +0x4c set; speed =
   3^(clamp(r,−20,20)/10)·(1 + (f(MSTTS.SpeakRate)−1)·NormalFactor/100)·scale, with
   `FUN_18004e41c(r)` = r<1 ? 1+r/C : 1+r·C' (constants 0x180181060/0x180193e44), NormalFactor =
   `VoiceSetting.MSTTS_SpeakRate_NormalFactor`. `VoiceSetting.MixRateScale` != 0 → the samples flushed out of Sonic
   are passed through CWaveSmoother (240-sample linear ramp `FUN_1800665c8`). (Details of NUS rate: partly guess.)
4. **Voice volume** `FUN_18001fedc` + `FUN_18002c420`: v = SpsVolumeAdjustment (settings+0xc) if the unit is SPS
   and the voice has NUS domain data (wavegen+0x218), else VolumeAdjustment (+8); per-domain settings override;
   plus SSML/utterance volume offset (utt+0xc0 → +0x10, −100). If v != 100: s = (short)(int)clamp((float)s·v/100,
   −31000, 31000). **David: SpsVolumeAdjustment=180 → ×1.8f, verified 100% on the WAV.** Zira/Mark: 100 (no-op).
5. **SAPI volume** in `FUN_18006d71c`: x = ((siteVolume·phoneVolume)/100)/100; if != 1: gain =
   `FUN_1801487ec`(x) = x >= 0.1 ? 10^(−25·(1−x)/20) : (x/0.1)·G(0.1) (DAT_1801c0d08, runtime); applied with the
   same truncating ±31000 clip. Verified: `<volume level=50>` → ×0.23713738.
6. **Sound effects** `FUN_18005e9bc(vocoder, pcm, n)`: DRC (if enabled) → biquad chain (if enabled) → echo comb
   (if +0xac). DRC/biquads are enabled per utterance only from the *domain* settings (`DrcEnable<i>`,
   `BiquadFilterEnable<i>` in `[Domain]`): Zira tbtdirection (DRC+biquads), Mark tbtdirection (DRC only). Normal
   text: all off.
7. `FUN_18004ba04` writes 16-bit mono PCM at 16 kHz to the SAPI site (engine format; SAPI resamples if the client
   asks for another format).

### 6.1 DRC (`CDrcSoundEffectTransferFunction`, init `FUN_180159eec`, apply `FUN_18015a4fc`)
Defaults (0xc0 B object, `FUN_180159e1c`): Attack 0.15, Decay 0.2, FirstIn −70, FirstOut −42, SecondIn −4.2,
SecondOut −1, Curve 9, Gain 1 dB; overridden by `[DrcSetting]` (Zira GainDB=10, SecondIn −8; Mark GainDB=3).
coef = t > 1/fs ? 1 − exp(−1/(fs·t)) : 1 (`FUN_18015a0e0`). Envelope starts at 10^−4.5; per sample:
x = |s|/32768, env += (x−env)·(x>env ? attack : decay) (`FUN_180159dd4`); gain = exp(quadratic spline in
ln(env)) built from the knee points in ln units (dB·ln10/20 = ·0.1151293) with knee radius Curve (`FUN_18015a194`,
`FUN_180159d60`); s = (short)(int)clamp(gain·s, −32768, 32767).
### 6.2 Biquads (`FUN_180058ad0` reader, `FUN_180066954` design, `FUN_18015a9e0` run)
Entries `BiquadFilterSetting.{LowPassFilter,HighPassFilter}<i>=f0` (Q=√0.5), `BandPassFilter<i>=f0,bw`,
`EqualizerFilter<i>=f0,bw,gainDB`. A=10^(gain/40), w0=2π·f0/fs, α = sin(w0)·bw/(2f0) (BP/EQ) or sin(w0)/(2Q)
(LP/HP); RBJ-cookbook coefficients (EQ `FUN_18015a7a0`, BP `FUN_18015a720`, HP `FUN_18015a840`, LP `FUN_18015a8d0`)
normalised by a0 (`FUN_18015aad4`). Processing in double on x·65536 (Q16) direct form I, y rounded half away from
zero, clamped to int32, >>16, clamped to ±31000. Zira tbtdirection: EQ (300 Hz, bw 500, +3 dB), (2500, 4000, +8),
(3000, 1000, +3).

## 7. Other DSP classes (not in the default SPS chain)
CCodecLspSmoother (`FUN_180079ed0`, `WaveGeneration.LspSmooth`), CFrameShifter (`FUN_1800f4ef0`),
CWaveBlockControl, CUncompressedWaveInventory / COpusSILK* belong to the NUS (recorded-unit) concatenation path
(`FUN_180032828` → `FUN_180106660`); CCombFilter = echo effect (`EchoSetting.*`, `EchoPreset.*`, `FUN_180153ce8`,
`FUN_180154a28`), used only if enabled per utterance. CITFTE = Eva.

## 8. INI keys (vocoder side)
- LsfSharpen.* → §3. UVDecision.FrameLevel (settings+0x5c) / VoicedWeightThreshold (+0x80): param gen side; the
  vocoder only sees F0 (0 = unvoiced).
- SpsVolumeAdjustment/VolumeAdjustment → §6.4 (clamped 1..1000). WaveScale=Sonic → Sonic rate changer (§6.3).
- MSTTS_SpeakRate_NormalFactor, MixRateScale → §6.3. SpectrumAdjustment → warp (off at default 100).
- LSPDecomposing.DelayMode (engine+0x9b8, read in `FUN_18004ef80`) → streaming parameter generation; vocoder gets
  smaller chunks (vocoder+0xe4=1 for Zira/Mark) but its state is continuous, so output is chunk-invariant (the int
  model reproduced Zira's multi-chunk sentences exactly).
- DrcSetting.*, BiquadFilterSetting.*, `[Domain] DrcEnable/BiquadFilterEnable` → §6.1/6.2.

## 9. Probe / hook points used (call-site redirection, `harness/vocprobe.c`)
rel32 CALL sites redirected through a trampoline page allocated within ±2 GB of the DLL (no prologue patching):
0x1800327a6 float prepare, 0x18003279c int prepare, 0x18010d2b0 float LsfSharpen, 0x18010c99c int LsfSharpen,
0x18000a060 float excitation, 0x18000a07e float MBE excitation, 0x180074ce6 int excitation,
0x18000a42f float synth, 0x180074f15 int synth, 0x1800321e1 end-of-utterance reset. Other useful sites:
0x18000a2fc junction, 0x18010d15d edge replication (float), 0x18010d2cd LSF repair (float).
Usage: `vocprobe.exe "text" out.wav [token]` (default token = "Microsoft David Desktop" registry entry, which points
at the OneCore engine + M1033David; OneCore Zira/Mark: `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_ZiraM` / `..._MarkM`),
then `python tools/vocoder_model.py vocdump.bin` (float) or `python tools/vocoder_model_int.py vocdump.bin [step]`.

**Warning:** the SAPI token "Microsoft Zira Desktop" is the *desktop* engine (C:\Windows\System32\Speech\Engines\TTS\
MSTTSEngine.dll 11.0 with C:\Windows\Speech\Engines\TTS\en-US\M1033ZIR.*), not OneCore Zira, so `render.ps1`
renders of "Microsoft Zira Desktop" (ref/zira_t1*.wav) are not references for the OneCore Zira port.
"Microsoft David Desktop" on this machine is registered with the OneCore CLSID {179F3D56-…} and OneCore data.
