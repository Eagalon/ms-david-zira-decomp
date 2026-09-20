# OneCore HTS acoustic backend: David / Zira / Mark (MSTTSEngine_OneCore.dll 10.3.21207, x64)

This is the master map. Details and evidence are in three companion notes, each written by a parallel mapping
pass and cross-checked here:
* `backend_paramgen.md`: predictors, durations, MLPG, UV, F0 chain, INI voice settings (item 2)
* `backend_vocoder.md`: vocoder chain. **Verified bit-exact against the engine** for David (float) and
  OneCore Zira (int) through `harness/vocprobe.c` plus `tools/vocoder_model{,_int}.py` (item 3)
* `backend_io.md`: handler pipeline, the frontend→backend boundary, NUS/DNN, and the hooking plan
  (`harness/ziraprobe.c`) (items 4-6)

All addresses are VAs (base 0x180000000; RVA = VA - 0x180000000). [V] = verified at runtime or against data;
[S] = read from decompile/disasm; [G] = guess. The decompile has no symbols. Class names come from RTTI
(`tools/rtti64.py <dll> [filter]` maps RTTI names to vtables to method VAs).

## 0. Big picture (one sentence at a time)

```
CTextProcessor → CLinguisticProsodyTagger → CTTSUnitGenerator      (frontend; handler Process = vtbl slot 3)
  → CAcousticProsodyTagger::Process 0x1800a39f0 → FUN_1800a3324      (BACKEND ENTRY)
       FUN_1800a2bd4: CTTSFeatureExtractionEngine slot3 0x18005bfc0 → per-phone typed feature matrix
                      FUN_18000246c → FUN_180003540/FUN_180013ab0: decision-tree lookup per stream/state
       FUN_1800653c4: predictors in order Duration, UV, NuSps, F0, LSF, Gain  (MLPG per stream)
       FUN_1800a25f4 (float) / FUN_1800a2488 (int): export F0[Hz], LSF[24], log-gain per 5 ms frame
  → CStreamHandlersAdapter: CUnitLatticeGenerator / CUnitSelector / CWaveGenerator stepped per phone
       (plain text: every segment is domain "general", so no NUS clip is ever fetched)
       CWaveGenerator → CSpsVocoder: prepare (edge copy, LsfSharpen, LSF repair) → excitation
       (pulse + noise, CRT rand) → LSF→LPC → all-pole synthesis with gain → soft clip → int16
       → silence zeroing → volume (SpsVolumeAdjustment) → [DRC/biquad only for NUS domains]
  → CTTSEngineSite::Write: 16 kHz mono 16-bit PCM
```
Two numeric flavours, chosen by APM header u32 at file offset 0x24 (flag B below; stored at utt+0x2c0):
* **David = float**: float pools, 3-window MLPG in double LDL, float vocoder.
* **Zira and Mark = int**: quantized pools, fixed-point 2-window MLPG plus [1 2 1]/4 smoothing, fixed-point
  vocoder (Q13/Q14/Q30). DelayMode=1 streams the generation in chunks; the output does not depend on chunking.

Reference audio: `render.ps1 "Microsoft David Desktop"` IS OneCore David [V, byte-identical]. **"Microsoft Zira
Desktop" is the legacy desktop engine plus M1033ZIR.APM, so it is NOT OneCore Zira.** Render OneCore Zira/Mark with
`harness\ziraprobe.exe "text" out.wav HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_ZiraM`
(or `_MarkM`). Output is deterministic (srand(0x406) at load and after every utterance).

## 1. Voice data file formats (APM, BEP)

All verified against the installed en-US files with `tools/apm.py` / `tools/bep.py`. Run
`python tools/apm.py <APM>` for the header and model table, and
`python -c "import apm; apm.verify('<APM>')"` to parse every tree of every model and bounds-check
every leaf. It passes on David, Zira, Mark and Eva.

### 1.1 Common container header (0x18 bytes), FUN_1800982b4

| off | type | meaning |
|---|---|---|
| 0x00 | char[4] | magic `"APM "` (checked by FUN_1800b3790) |
| 0x04 | GUID | must equal engine GUID at DAT_1801887f0 (`76 85 70 6b 03 42 9b 4a 9b 1d ff f8 52 a4 ad d0`) |
| 0x14 | u32 | payload size = file size - 0x18 |

### 1.2 APM header (0x40 bytes at file+0x18), stored as voicedata+0x38. Checked by FUN_1800b3918

| hdr off | file off | David | Zira | Mark | meaning |
|---|---|---|---|---|---|
| 0x00 | 0x18 | 3 | 3 | 3 | version |
| 0x04 | 0x1c | 0x28ab0801 | 0x2bc7064f | .. | checksum / build id (not checked by the loader) |
| 0x08 | 0x20 | u16 0x409 | 0x409 | 0x409 | LCID (must be nonzero) |
| 0x0a | 0x22 | u16 0 | 1 | 0 | flag A (unknown, set only on Zira) |
| 0x0c | 0x24 | 0 | 1 | 1 | **flag B = "typed/quantized model format"**: 0 means all trees use CHTSOffsetLeafNode and float pools; 1 means type-specific leaf classes and quantized LSF/F0/MBE pools (FUN_180014b80) |
| 0x10 | 0x28 | 16000 | 16000 | 16000 | sample rate (8000 or 16000 accepted) |
| 0x14 | 0x2c | 16 | 16 | 16 | bits per sample (8 or 16 accepted) |
| 0x18 | 0x30 | 80 | 80 | 80 | frame shift in samples (5 ms). Guess from the value; not checked in the loader |
| 0x1c/0x20 | 0x34 | 0x58 / 0x59e4 | .. | .. | question-set region (offset, size) |
| 0x24/0x28 | 0x3c | 0x5a3c / 0x77b3e0 | .. | .. | model region |
| 0x2c/0x30 | 0x44 | .. | .. | .. | string table (XOR-obfuscated UTF-16) |
| 0x34/0x38 | 0x4c | 0/0 | 0/0 | 0/0 | optional Huffman table. When present, trees and pool entries are CLwHuffDecoder-compressed (FUN_180015e70, FUN_1800b44e8). **No shipped en-US voice uses it** |

Loader chain: CHTSVoiceData slot 6 = FUN_1800b3650 → FUN_1800b380c (header) → FUN_1800b3918
(validate) → FUN_180039f60 (strings + questions) → FUN_1800b34d8 (models).

### 1.3 String table (FUN_180039f60)
UTF-16LE strings. Every nonzero code unit is XORed with key[j], where key = 8 u16 at
DAT_1801807d8 = `3412 7856 bc9a f0de 5634 debc 9a78 12f0`. j advances (mod 8) **only on
nonzero units**; a 0 unit stays 0 and does not advance j. Strings are referenced by byte offset.
Decoder: `tools/apmstr.py`. Contents: feature names, question names (David/Eva only; Zira/Mark
questions are unnamed), and model names ("Linear Spectrum Pair", "Log Fundamental Frequency",
"Multi-Band Excitation", "Duration", "Phone Duration").

### 1.4 Question-set region (FUN_180037c30 + FUN_1800397c0/FUN_180039960)
```
u32 named            (1 = each question has a name string offset; David/Eva 1, Zira/Mark 0)
u32 nFeatures        (David 44, Zira 41, Mark 42)
u32 featureName[nFeatures]   string offsets; a leading '$' is stripped and flagged
u32 nQuestions       (David 811, Zira 791, Mark 768)
repeat nQuestions:
   [u32 nameOffset]  only if named
   u32 featureIndex
   u32 op            0 '==', 1 'in set', 2 '>', 3 '>=', 4 '<', 5 '<='   (feature OP value)
   u32 nValues
   u32 values[nValues]  ints (phone ids, POS ids, counts); for string-typed features
                        (feature def +0xc4 == 2) they are string offsets (FUN_18003c7b0)
```
Only ops 0, 1 and 5 occur in the shipped files. Each feature name is a dotted path through the
utterance tree ("Phone.Syllable.Word.Phrase.IntonationPhrase.Sentence.SentenceType"). It is
parsed by FUN_180037e34 against the token table at PTR_u_Phone_18016fee0 into a
CTTSFeatureQuestion (0x100 bytes). Feature sets: David and Eva have 3 extra features
(`Sentence.SentenceType`, `Word.FwPosInYesNoQuestion`, `Word.BwPosInYesNoQuestion`). Zira and Mark
have no sentence-type/question features; question intonation for Zira comes from the INI
`[QuestionIntonation]` post-rule instead (see §2).
Question evaluation: FUN_180013ab0 (tree walk), FUN_180014290 / FUN_1800139d0 (typed compare),
FUN_180014220 (string compare result).

### 1.5 Model region (FUN_1800b34d8)
`u32 nModels; nModels × {u32 offset (from region start), u32 size}`. Each model is
a CHTSAcousticModel (0x60 bytes), loaded by FUN_1800157b0. Its header is a
CHTSAcousticModelHeader (0x80 bytes), loaded by FUN_180035680:
```
u32 type        1 LSF(+gain), 2 logF0 (MSD), 3 state duration, 6 phone duration, 7 MBE
                (5 = gain sub-model split off LSF at runtime by FUN_1800032e8)
u32 nameOffset  string table
u32 f10         0
u32 msdFlag     2 for logF0 and MBE, else 1 (2 means a leaf holds 3 pool offsets)
u32 nStates     5 for LSF/F0/MBE, 1 for the duration models
u32 nStreams    N
u32 streamDim[N]   David LSF (75); David F0 (1,1,1); Zira F0 (3); MBE (15); Dur (5); PDur (1)
u32 streamId[N]    David F0 (2,3,4); LSF (1); MBE (5)
u32 treeOff, treeSize, poolOff, poolSize      (relative to model start)
u32 nWindows; nWindows × {u32 width; f32 coef[width]}  CHMMDynamicWindowSet (FUN_18014beac):
       LSF/F0/MBE: [1.0], [-0.5 0 0.5], [1 -2 1]; none for the duration models
u32 nMix(+0x4c)=1, staticDim(+0x50) (25 LSF, 1 F0, 5 MBE/Dur, 1 PDur), +0x54, +0x58, +0x5c, +0x60,
    quantFlag(+0x64: 1 = quantized pool), meanBits(+0x68), precBits(+0x6c), +0x70
       David all models: (1,dim,1,1,1,0,0,32,32,0)
       Zira LSF (1,25,0,1,1,0,1,8,8,0); F0 (1,1,1,1,1,0,1,16,8,0); MBE (1,5,0,1,1,0,1,16,8,0)
u32 blobSize; blob       only in F0: type u32 = 1 → "customized generation setting"
       (FUN_1800b1bb4, printed by FUN_180149620): u32 windowLength=15, 15 f32 weights (0.0666, one
       0.0676), f32 EnhanceRate = 1.0, f32 Mean (David 4.531, Zira 5.175) = mean logF0
```
Per-voice models: David = LSF, LF0, Dur, PDur (**no MBE**). Zira and Mark = LSF, LF0, MBE, Dur,
PDur. Eva = Dur and PDur only (the rest of Eva is DNN).

### 1.6 Tree region (FUN_180014b80, FUN_1800153e0)
```
u32 nTrees, u32 nSub (= nStates)
repeat nTrees: u32 treeId; nSub × {u32 off, u32 size}   (offsets relative to tree region)
u32 trailer = nTrees*nSub
```
treeId is the **centre phone id** for LSF and MBE (ids 3..47; David 41 trees, Zira 42, Mark 41).
It is 0x7fffffff (one shared tree) for F0 and durations. Selection is in FUN_180003540:
the model keeps min/max id (+0x50/+0x54) and a map (+0x30) from id-min to tree index.
Sub-tree blob: `u32 nodeCount`, then nodes addressed by byte offset from blob start, root at 4:
* internal: `u8 0, u8 pad, u16 questionIndex, u32 noOff, u32 yesOff` (12 bytes)
* leaf: `u8 1, 3 pad, u32 poolOffset[k]` where k = 3 if msdFlag == 2, else nStreams.
  In David's F0 the 3 offsets point to 3 separate stream entries. In Zira/Mark F0/MBE all 3
  are equal (one entry holds all windows).
The walk takes `yes` when the question is true (FUN_180013ab0: result 0 goes to node+4, 1 to node+8).
At load time the nodes are converted to 12-byte runtime nodes with relative child indices.
Negative indices are leaves.

### 1.7 Pools (offsets are relative to the pool start; pool starts with `u32 nEntries`)
* **Float pools** (David all models; all voices' Dur/PDur). Read by FUN_180003e94 into
  CHMMStream/CHMMGaussMixture: per stream, per mixture (nMix=1):
  `f32 weight; f32 A[dim]; f32 B[dim]` where **B = precision (1/var), A = mean·precision**
  (canonical/information form). Verified: A/B of David LSF gives monotone LSFs 0.016..0.474 in
  normalized frequency (cycles/sample, 0..0.5); the 25th value ≈ 7.9 (log gain). F0 static
  A/B ≈ 4.26..4.82 (ln Hz, median 4.49 = 89 Hz). For MSD F0, `weight` = voiced probability.
  Duration: A/B = mean in frames (likely; paramgen confirms).
* **Quantized LSF** (Zira/Mark, 156-byte entries = 2·(75+3)). Decoded to *integers* by
  FUN_1800451a0 / FUN_1800ae1cc (mode 1), P=25 static dims, T=75:
  mean area 78 bytes, then precision bytes at +78. The int path (paramgen §4.1) uses only 2 windows
  (static + delta), so the decoder is called with T = 2P = 50 and the delta-delta bytes/i16 at
  51..77 are **never read**. For i<P-1: mean = 8·cumsum(u8[0..i]) (Q15 LSF, ×4 if P≥41).
  For i = P-1 or 2P-1: mean = i16 at byte i + i/P (gain; a negative first gain clamps to 0).
  For other delta i: mean = 4·i8 at byte i+1. Because 2P == T, delta means are then doubled.
  Precision u = p[i]²; if i<P: max(u (>>2 when mode 2), 1); else u<<8. Stored as 2u.
  Precision base +78 comes from the 156 = 78+78 layout; guess that the record's +0x18 size field = 78.
  `tools/apm.py: pool_lsf_q`.
* **Quantized F0** (16 bytes): `f32 voicedWeight; i16 mean[3]; u8 prec[3]; pad[3]`.
* **Quantized MBE** (48 bytes): `i16 mean[15] (5 static Q15 band voicing strengths, then
  deltas and delta-deltas); u8 prec[15]; pad[3]`. Decoded by FUN_1800ae1cc (i16 means,
  precision rule as above). `pool_msd_q`. The integer→float scale for F0 is **not yet pinned**
  (medians: Zira 24227, Mark 22826 vs David 4.49 ln Hz). See §2.

### 1.8 BEP ("BEPT") = CParameterManager data (loader FUN_180113dc0 = CParameterManager slot 6)
Header 0x24: `"BEPT"`, GUID (DAT_18018bac0), u32 version 3, u32 checksum, u64 payload size
(FUN_180098458). Then `u32 N; N × {u32 id<32, i32 off, i32 size}` and a data blob. The sizes
must sum to the blob length. All three voices have the same ids:
2: (-3,3,2) i32×3; 3: 500; 4: 100; 5: 12; 6: 500; 11: 10.0f; 18: 24 (LSF order); 31: 1;
7, 8, 9, 12, 13, 14, 15, 16, 17, 30: 37 floats each. Guess: per-phone(-class) statistics
(7/12/13 are about 4..60, the others small variance-like values with a repeated default for unseen
entries). Probably unit-selection/target-cost or post-processing parameters. Parser:
`tools/bep.py`. Semantics: see §2/§3 if the forks identified getters.

### 1.9 Other files
CHTSTransformModel/Header (FUN_1800b2890, 0xe0-byte header) = APM-like adaptation models
loaded only through INI `[ExtendAcousticModel] Number/APMn/Domainn/Emotionn` (FUN_1800b0080).
None of the en-US OneCore voices have this section, so it is unused.

### 1.10 Integer ids recovered from David's question names (check against the frontend phone table)
Phone ids (Phone.PhoneIdentity_x with a single value): 3 sil, 7 aa, 8 ae, 9 ah, 10 ao, 11 aw,
12 (only in class "RVowel"; probably ax or axr), 13 ay, 14 b, 15 ch, 16 d, 17 dh, 18 eh, 19 er,
20 ey, 21 f, 22 g, 23 hh, 24 ih, 25 (unnamed), 26 iy, 27 jh, 28 k, 29 l, 30 m, 31 n, 32 ng, 33 ow,
34 oy, 35 p, 36 r, 37 s, 38 sh, 39 t, 40 th, 41 uh, 42 uw, 43 v, 44 w, 45 y, 46 z, 47 zh.
LSF and MBE tree ids 3..47 are these ids. POS ids: noun 3, verb 6, verbpastp 8, adj 11, det 14,
num 18, vaux 21, pron 24, whpron 25, adv 28, whadv 29, conj 32, prep 35, interjection 38,
particle 41, contr 49.

## 2. Parameter generation (summary; full detail in backend_paramgen.md)

* **Input to the lookup**: per phone, one 16-byte typed value per APM feature: `{int type; pad; union{int; wchar*}}`,
  type 0/1 int, 2 string, -1 = take the type from the feature definition. There are no HTS label strings. [V]
* **Streams looked up** (FUN_18000246c): float path FUN_180002de8: 3 state duration, 6 phone duration (if
  present), 2 lf0, 1 LSF (split by FUN_1800032e8/FUN_180006e9c into type 1 = LSF dims 0..23 and type 5 = gain dim 24).
  Int path FUN_180002628 does the same plus FUN_1800a14d0 (MBE). **David's APM has exactly models 1, 2, 3, 6** (no 7/8/9);
  windows are the standard [1], [-.5 0 .5], [1 -2 1]. Zira/Mark also carry a type-7 MBE model, but **no MBE predictor or
  MBE excitation runs for them** (confirmed at runtime by both the io and vocoder passes). The MBE model is dead data for plain text.
* **Durations** FUN_1800692d0 [V+disasm]: S=Σμ_s, V=Σσ²_s, T = S + W·(max(PhoneDur,5) − S) with W =
  PhoneDuration.Weight/100 = 0.9; ρ=(T−S)/V; d_s = trunc_f32(μ_s + ρσ²_s + carry + 0.5), min 1, float error carry;
  rescale to round(T) if the leftover carry > 1 (visible only in disasm); cap at MaxFramesPerPhone (40).
* **Rate** FUN_18006cda8: 3^(rate/10) products × SpeakRate/NormalFactor × RateAdjustment. It applies to durations when
  MixRateScale=1 (David). SAPI `<rate>` changes durations for all three voices [V by vocoder pass].
* **MLPG** FUN_18000ca70 (float): per dimension, float products summed in double, LDLᵀ in double, pivot |D|≤1e-6 → 1.0,
  back substitution on float-rounded values. Windows are zeroed at utterance edges and U/V boundaries. **No GV,
  no parameter postfilter.** Int path: FUN_1800451a0 (decode) → FUN_180008a6c → FUN_18000c0f0 (FUN_180076b04/
  FUN_1800aef84/FUN_1800af178 integer band solver) → FUN_1800af4b4 smoothing (open: exact integer scales).
* **UV** FUN_18003b890/FUN_18004d258 (UVDecision FrameLevel=yes): threshold 0.5 on the state voiced weight. A state is
  fully voiced if its own weight passes or both neighbours pass; otherwise round(d·w) frames at the side of a voiced
  neighbour. Quirk: the first state's weight is treated as 0.
* **F0** (FUN_1800a6304 / FUN_1800a5394): MLPG on voiced frames, then the APM F0 blob smoothing (15-tap moving average
  within voiced runs, renormalised; FUN_180016010), then (f0−Mean)·EnhanceRate+Mean (FUN_18003ff28, float), then
  **Zira only** [QuestionIntonation] ramp FUN_1800a65a8 (+0.005 logF0/frame, cap 5.35, 11-tap smoothing), then exp()
  in double, then pitch factor / PitchRangeScale about the mean, clamped to [3, 8000] Hz (FUN_18001b100, FUN_1800a2810).
* **Export** FUN_1800a25f4/FUN_1800a2488: LSF ordering fix; a frame outside [0, 0.5] is replaced by the previous frame.
* EmotionRecipe entry = {name, RateAdjustment, PitchAdjustment, PitchRangeScale, VolumeAdjustment} (% values);
  selected by `<mstts:emotion><mstts:category name=...>` in the engine's **own** SSML parser (FUN_18005a348).
  **Unreachable in practice**: SAPI 5 (SPF_IS_XML and SSML) and the WinRT SpeechSynthesizer both drop the mstts:
  namespace before the engine sees it, so emotion markup gives byte-identical audio to plain text (measured on
  David).  The four consumers are: rate `FUN_18004e254` (`R% += emotion.Rate - 100`, then log3 to rate steps),
  pitch `FUN_18001b100` (`P = Config.PitchAdjustment + emotion.Pitch - 100`, F0 *= P/100), range
  `FUN_18001b100`/`FUN_1800a2810` (`S = Config.PitchRangeScale + emotion.Range - 100` about the utterance F0
  mean), volume `FUN_18001fedc` (`V = (Sps)VolumeAdjustment + emotion.Volume - 100`).  Ported as `ZbStyle`
  (src/zb.h), reachable from the library as `zira_tts_set_emotion` and from both CLIs as `--emotion`; not
  verifiable against the engine (see zb.h). SilenceLength: 8 keys (ms) give pause durations per boundary type
  (the assignment site is still open). ShortPause consumer is still open.

## 3. Vocoder (summary; full detail in backend_vocoder.md, verified bit-exact)

* Frame = 80 samples. The vocoder input per frame is F0 in Hz (≤3 means unvoiced), 24 LSF (normalized 0..0.5), and log gain.
* Prepare FUN_18010ca5c (float) / FUN_18010c148 (int): copy the first and last 10 LSF frames from their neighbour,
  then **LsfSharpen** FUN_180012408 / FUN_18003adb0 (MultipleInterval, Intervals=2, Iterations=3, Step=0.22 for David
  and Zira, 0.25 for Mark; Low/High 0.075/0.4 from the built-in defaults at 0x18016d790), then a minimum-spacing pass,
  then LSF repair.
* Excitation (float FUN_18000ac88, int FUN_18010e0d4): pulse train at int(fs/F0) through a 41-tap voiced FIR
  (5-band table 0x18017d3c0, band weights {1,.9,.5,.4,.3}). Noise comes from a 1024-sample Box-Muller table at
  offset 80+rand()%864, scaled g=sqrt(1024/E/80). In voiced frames it goes through the unvoiced-band FIR and is added;
  in unvoiced frames it replaces the pulses. `rand()` is the CRT's, seeded srand(0x406). The MBE-driven variant
  (FUN_1800097dc / FUN_18010df8c / FUN_18000b3dc) and ITFTE (Eva) are not used by David/Zira/Mark.
* LSF→LPC FUN_180014640 (float/double) or FUN_18003b460 (int Q30, permuted LSP pairs). All-pole synthesis
  FUN_18006b620 / FUN_18006c250 with gain exp(g) (int: exp table 0x1801876d0, cos table 0x1801866d0).
  If any sample exceeds ±31000, set a[k]*=0.99^(k+1) and redo the frame (≤4×). Soft clip above 31000:
  32767−1767·exp(−0.0005·excess). Write int16.
* Then silence zeroing (sentence-edge silences fully, inter-word pauses only state 2), then SpsVolumeAdjustment
  (David 180 → ×1.8 truncated and clipped ±31000; Zira/Mark 100), then SAPI volume (−25 dB range curve).
  DRC / biquad EQ ([DrcSetting], [BiquadFilterSetting]) only for domains with DrcEnable/BiquadFilterEnable
  (Zira/Mark tbtdirection NUS). WaveScale=Sonic: the CRateChangerSonic (0x180153540..) time-stretcher is used only
  for NUS/flagged units.

## 4. Backend input (summary; detail in backend_io.md §1)

* Boundary: `CAcousticProsodyTagger::Process` (vtbl 0x18016ea58 slot 3 = 0x1800a39f0) receives the CTTSUtterance tree
  (Sentence → IntonationPhrase → Phrase → Word → Syllable → Phone) built by the frontend. The backend only reads it
  through **CTTSFeatureExtractionEngine slot 3 (0x18005bfc0)**. That call evaluates each APM feature path (the §1.4
  names, parsed against the token table 0x18016fee0; leaf features in 0x18016f280, dump with `tools/feat_table.py`)
  into a phones × features matrix of ints/strings. **That matrix is the contract**: the frontend port must reproduce
  it, and the backend port consumes it. `ziraprobe` dumps it (golden file). Phone and POS ids are in §1.10.
* The segment/pause structure and SilenceLength durations also come from the utterance (see paramgen §3).

## 5. NUS clips and the DNN path

* Plain text on David/Zira/Mark is **pure HMM/SPS**. The lattice and selector handlers run, but every segment is domain
  "general", so no CNUSVoiceData / COpusSILKDecoder data is read [V]. "keyboard" (NUSData\M1033David.keyboard.*) is
  selected only when FUN_180034d98 sees a single word of type 4. No tested input triggered it (letters, key names,
  say-as). tbtdirection/speechux (Zira/Mark .NUS) presumably need an app-set domain [G]. When a NUS unit is used, the
  domain's DRC/biquad, NuspsConvarFp, NusRate and Sonic rate change apply.
* DNN (CDNNAcousticModel, CMLP*, CNNPredictor, ITFTE excitation) = Eva only (M1033Eva.NNM/TDAT/BR2). Eva has no
  registry token, so it cannot be selected through SAPI.

## 6. Hooking plan (summary; detail in backend_io.md §3 and backend_vocoder.md §9)

* Load: `LoadLibraryW(...\MSTTSEngine_OneCore.dll)` in an x64 non-CFG harness EXE, patch it, then drive SAPI5
  in-process (SpVoice + token SetId + SpStream to 16 kHz WAV). Hooks don't change the output [V].
* Prefer **vtable-slot patches** (no code patching): backend entry 0x18016ea58[3], feature matrix 0x1801714b8[3]
  (5 args), predictors (Dur 0x1801730f8, F0 0x18016ec88, Lsf 0x18016ed20, UV 0x18016eb28, NuSps 0x18016eb80,
  Gain 0x18016edb8; stream slots 6..9), wave generator 0x180173060[6..9], site Write
  `CTTSEngineSite` 0x180175390[3]. The predictor-stage callback at tagger+0x30 fires before and after each stage.
* Non-virtual workers: a 14-byte `jmp [rip]` absolute hook is safe on 0x1800a3324, 0x1800a2bd4, 0x18000246c, 0x1800653c4,
  0x180057df0, 0x1800321f0, 0x180032828, 0x180110450, 0x18004bb98 (stolen-byte lengths in backend_io §3.3).
  Alternative used by vocprobe: redirect rel32 CALL sites through a stub within ±2 GB (float/int prepare
  0x1800327a6/0x18003279c, sharpen 0x18010d2b0/0x18010c99c, excitation 0x18000a060/0x180074ce6, synth
  0x18000a42f/0x180074f15, utterance-end reset 0x1800321e1).
* Suggested annatap-style tagged log: T_FEATS (matrix), T_DUR (per-state frames), T_PARAM (per frame F0/LSF/gain
  after export), T_EXC, T_PCM.

## 7. INI keys (where each one lands)

| key | effect | where |
|---|---|---|
| LsfSharpen MultipleInterval/Intervals/Iterations/Step (+Low/HighFrequency) | LSF-domain formant sharpening before synthesis | vocoder §3 |
| UVDecision FrameLevel | frame-level voicing from state weights (thr 0.5) | paramgen §5.1 |
| PhoneDuration Weight=90 | W=0.9 interpolation of total state duration toward the phone-duration model | paramgen §3 |
| SpsVolumeAdjustment | output ×value/100, clip ±31000 (David 180) | vocoder §6 |
| WaveScale=Sonic | Sonic time-stretch for NUS/flagged units | vocoder §6.3 |
| MSTTS_SpeakRate_NormalFactor, MixRateScale | rate normalisation; MixRateScale=1 makes rate act on HMM durations | paramgen §3 (rate) |
| EmotionRecipe | per-emotion rate/pitch/range/volume % | paramgen §6; ported in `src/zb.h` (ZbStyle) + zb_dur/zb_wave/zb_synth |
| QuestionIntonation LogF0RisingRate/LogF0MaxValue | Zira: logF0 ramp at question end | paramgen §5.2 |
| SilenceLength | pause lengths (ms) per boundary type | paramgen §6 (site open) |
| ShortPause Enable | open | - |
| LSPDecomposing DelayMode=1 | chunked (streamed) generation; forces the int acoustic space | paramgen §0, vocoder §8 |
| DrcSetting, BiquadFilterSetting, Domain* | NUS-domain post effects only | vocoder §6.1/6.2 |

## 8. Open items

1. The integer→real scale of the quantized F0 (i16, medians 24227 Zira / 22826 Mark) and the full integer MLPG
   solver (FUN_18000c0f0, FUN_180076b04, FUN_1800aef84, FUN_1800af178). Paramgen found ×7 on stream 2 and ×10 on the
   last LSF dim. For the int path the vocoder side is already verified, so parameters dumped at export are a
   usable golden target.
2. BEP id semantics (CParameterManager getters). Id 18 = 24 = LSF order is certain; the 37-float tables are a guess
   (per-phone/NUS target-cost statistics).
3. Pause-duration assignment (SilenceLength) and the ShortPause consumer.
4. Full phone-id table (ids 4-6, 12, 25 are unnamed in the questions) and the POS table from the frontend data.
5. What triggers the keyboard NUS domain.

## 9. Tools

* `tools/apm.py`: APM parser (`APM(path)`, `parse_trees`, `lookup(a, subtree, fvec)`, `pool_float`, `pool_lsf_q`,
  `pool_msd_q`, `verify`). `tools/apmstr.py`: string-table decoder. `tools/bep.py`: BEP parser.
* `tools/rtti64.py`, `tools/dis64.py`, `tools/feat_table.py`, `tools/cst.py`, `tools/xref.py`, `tools/fn.py`
  (note: fn.py/xref.py/dis64.py were rewritten by concurrent agents; check the docstrings).
* `harness/ziraprobe.c` (pipeline/feature dump, any token), `harness/vocprobe.c` plus `tools/vocoder_model.py`,
  `tools/vocoder_model_int.py` (bit-exact vocoder models).
