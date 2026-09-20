# OneCore HTS backend: parameter generation (David / Zira / Mark)

Engine: `MSTTSEngine_OneCore.dll` 10.3.21207 (x64). All addresses are VAs (image base 0x180000000).
Status legend: **[V]** verified in decomp and/or disassembly; **[G]** guess or inference; **[?]** open question.
Tools: `tools/fn.py` (decomp by VA), `tools/dis64.py` (capstone x64), `tools/cst.py` (dump f32/f64/u32 constants),
`tools/rtti64.py` (RTTI class to vtable map).

---------------------------------------------------------------------------------------------------
## 0. Summary

* **Frame shift:** 80 samples at 16 kHz, which is 5 ms. The model header struct holds {sr=16000, bits=16, shift=80}.
  `FUN_1800afd38` reads it and it is stored in `CDurationPredictor+0xa4/+0xa0` [V].
* **Two HTS acoustic-space flavours**, selected by a model-header flag (`FUN_1800331b0`, stored at `utt+0x2c0`):
  * flag 0 is **David**: `CTTSAcousticSpaceImpl<float>` (vtbl 0x180173770). Gaussians use the float canonical form
    (`+0x18` = mean*precision, `+0x20` = precision). The standard HTS MLPG runs with 3 windows, and the LDL solver works in double.
  * flag 1 is **Zira/Mark** (and it is required by `LSPDecomposing.DelayMode=1`): `CTTSAcousticSpaceImpl<int>`
    (vtbl 0x180173740). The models are quantised and the MLPG is integer / fixed point with 2 windows (static + delta).
    LSF and gain then get a [1 2 1]/4 time smoothing.
* **Predictor order** (list built by `FUN_18004bce4`, run by `FUN_1800653c4`): Duration, UV, NuSps, F0,
  LSF, Gain, [MBE], [Power], [LSF9]. The DNN (NN/PostNN/TrajectoryRefinementor/Sew/Rew/Energy) entries are Eva only.
* **No GV.** No global-variance step exists anywhere in the generation call graph (`FUN_180068544`) [V].
* **F0 chain (David):** MLPG over voiced frames only, then a voiced-segment-aware FIR smoothing with the model's
  "customized generation setting" window (15 taps, per the parent), then `(f0-Mean)*EnhanceRate+Mean`,
  then (Zira only) the question-intonation ramp, then `exp()` in double, then pitch factor and pitch-range scaling
  in Hz, clamped to [3, 8000].
* **Durations:** per state, `round(mean + rho*var + carry)` in float with error carry (min 1). Here
  `rho = (T - sum mean)/sum var`, and T interpolates toward the phone-level duration model with weight
  `PhoneDuration.Weight` (default 0.9). The result is then capped by `MaxFramesPerPhone` (default 40) and
  rescaled by the rate factor.

---------------------------------------------------------------------------------------------------
## 1. Objects and call graph

### 1.1 CAcousticProsodyTagger (0x9f0 bytes, ctor `FUN_180070b60`, vtbl 0x18016ea58)
* `+0x9b0`: engine (`CTTSEngine`). `+0xa0` = engine+0xa0 = `CTTSEngineConfig*` (the INI voice settings, §6).
* `+0x30`: stage-event callback. It is called with `(mask, 0=before / 1=after, utt)` around each predictor, around
  the model lookup (mask 0x4000004) and around the final export (0x4000800). **This is a good hook point** [V].
* `+0x38`: `CTTSFeatureExtractionEngine` (vtbl 0x1801714b8; slot 3 `0x18005bfc0` extracts per-phone feature values).
* `+0x40`: `CHTSModelSetManager` loaded from `<voice>.APM`.
* `+0x48`: `CHTSTransformModelSetManager` from `<voice>.ATM`, only if that file exists; then `+0x9cc=1`.
  **No .ATM file ships for en-US, so transforms are unused** [V].
* `+0x50/+0x58`: DNN manager (`.NNM`+`.TDAT`), Eva only. `+0x60`: HEQ table (`.HEQ`), Eva only.
* `+0x68`: {samplerate, bits, frameshift}. `+0x16c` = sr and `+0x168` = shift are copied into the duration predictor.
* `+0x840`: `CNusTrajectoryRefiner`, active only when the utterance contains NUS units (`utt+0x128`).
* Stream-presence flags: `+0x9bc` stream 6 (phone duration) present, `+0x9c0` MBE (only if INI
  `MultiBandExcitation.Enabled=true`, and none of the three INIs sets it), `+0x9c4` stream 8 (power), `+0x9c8` stream 9
  (second LSF), `+0x9b8` `LSPDecomposing.DelayMode`, `+0x9d0` gain predictor enabled (default 1).
* Initialize: `FUN_18004ef80` (loads APM/ATM/NNM/HEQ, reads stream dims, wires predictors).
* Process: `FUN_1800a39f0`, then `FUN_1800a3324`, then:
  1. `FUN_180032dc8`: builds the CHTSModelSetManagerAdapter and calls `FUN_1800a2bd4`, which does feature
     extraction and the **decision-tree model lookup** for every stream (§2).
  2. `FUN_1800653c4`: the predictor scheduler. It calls slot 6 (Init) on each list entry, then loops calling
     slot 8 (state) and slot 7 (Run, when state==1), and finally slot 9. It then runs the final export
     `FUN_1800a25f4` (float) / `FUN_1800a2488` (int) (§5).

Predictor sub-objects (offset inside the tagger / stream id / event mask) [V: ctor `FUN_180070b60` + `FUN_18004bce4`]:

| tagger off | class | stream id (`+0x10`) | mask (`+0x14`) | runs for David |
|---|---|---|---|---|
| 0x0c8 | CDurationPredictor | 3 (+6 phone dur) | 0x4000008 | yes |
| 0x188 | CUVPredictor | 2 | 0x4000010 | yes |
| 0x4a8 | CNuSpsPredictor | 0 | 0x4000020 | yes (no-op without NUS) [G] |
| 0x200 | CF0Predictor | 2 | 0x4000040 | yes |
| 0x290 | CLsfPredictor | 1 | 0x4000080 | yes |
| 0x3a0 | CGainPredictor | 5 | 0x4000100 | yes |
| 0x430 | CMbePredictor | 7 | 0x4000200 | only if MBE enabled (no) |
| 0x528 | CPowerPredictor | 8 | 0x4000400 | only if the APM has stream 8 |
| 0x318 | CLsfPredictor #2 | 9 | 0x4001000 | only if the APM has stream 9 |
| 0x5a0/0x690/0x7c8/0x848/0x8c0/0x938 | NN, PostNN, TrajRefinementor, Sew, Rew, Energy | 12/-/-/13/14/15 | | Eva/DNN only |

The list is built in exactly the order shown in the table (`FUN_18004bce4`) [V].
Predictor vtable layouts. The primary vtbl has slot 1 = main for the non-stream predictors (Duration: `FUN_1800692d0`),
slot 4 = int-space run, slot 5 = float-space run. The interface at +0x40 dispatches slot 7:
`FUN_1800a4610` (Duration) / `FUN_1800773a0` (stream predictors: RTTI cast of the acoustic space to <float> or <int>,
then primary slot 5 or 4).

| predictor | float run (slot 5) | int run (slot 4) |
|---|---|---|
| UV | `FUN_18003b890` | `FUN_1800a51b0` |
| F0 | `FUN_1800a6304` (thunk 0x1800a6ab0) | `FUN_1800a615c` (thunk 0x1800a6aa0) |
| LSF | `FUN_1800a6d04` (thunk 0x1800a6ef0) | `FUN_1800a6b10` (thunk 0x1800a6ee0) |
| Gain | `FUN_180059550` | (none) |
| MBE | `FUN_1800a7620` | `FUN_1800a7560` |

### 1.2 Acoustic space (`utt+0x2c8`, or `utt+0x4d0` when `utt+0x2c0`!=0) [V offsets from use]
| off | content |
|---|---|
| +0x08 | state-duration matrix, uint32 [nPhones][nStates] (struct {rows,cols,data*}) |
| +0x10 | voiced flag per frame, int32 [T] |
| +0x80 | phone list (CTTSPhone nodes; `+0x84` = u16 phone id) |
| +0x88 | vector of per-stream model sequences. Each entry has `+0x20` = stream id and `+0x48` = per-phone CHMMModel* |
| +0xa8 | sentence/settings object |
| +0xb0 / +0xb4 | nPhones / nStates (5) |
| +0xb8 | T = total frames |
| +0xc0 | F0 trajectory [T][1]: logF0, and Hz after export; 0 = unvoiced |
| +0xc8 | LSF trajectory [T][order] (stream 1) |
| +0xd0 | LSF trajectory of stream 9 |
| +0xd8 | gain trajectory [T][1] (stream 5) |
| +0x174 | NUS mode flag (whole utterance comes from NUS) |
| +0x188/+0x1a8/+0x1c8 | int-space per-phone quantised model refs (duration/LSF, F0, MBE) [G on the exact meaning] |

---------------------------------------------------------------------------------------------------
## 2. Model lookup (context features, then trees, then per-state Gaussians)

* `FUN_1800a2bd4`: `FUN_1800afb28` gets the question/feature definitions from the model set (0x100-byte records;
  `+0x10` = feature name). Then feature-extractor vtbl+0x18 (`0x18005bfc0`) fills, for each feature, an
  array of per-phone 16-byte values: `{int type; int pad; union{int i; wchar* s}}`. type 0/1 = int, 2 = string,
  and -1 = special (evaluated by `FUN_1800139d0`/`FUN_180014290`). **This per-phone typed feature vector is the backend
  input**; there are no HTS full-context label strings [V].
* `FUN_18000246c` (lookup driver). It calls acoustic-space slot 4 (is-int). For float it goes to `FUN_180002de8`, which looks up
  stream 3 (state dur), stream 6 (phone dur, if present), stream 2 (lf0), then `FUN_1800032e8` (stream 1, split by
  `FUN_180006e9c` into type 1 = dims [0,order) LSF and type 5 = dim `order` **gain**), then 7/8/9 if enabled.
  For int it goes to `FUN_180002628`: streams 3/6, then `FUN_1800021ac`, `FUN_180001ec4`, and `FUN_1800a14d0` (MBE).
  After lookup: `space+0xb4 = nStates` (from the duration stream's state count).
* `FUN_180003540` (per stream, per phone) [V]:
  * It finds the CHTSAcousticModel whose header stream type == stream (model array `mgr+0x80`, 0x60 bytes each).
  * Per-central-phone tree set: if `model+0x50/+0x54` (min/max phone id) are both 0x7fffffff there is one shared set.
    Otherwise `idx = table(+0x30)[phoneId-min]` gives entry `+0x10 + idx*0x28` = {u32 phoneId, ?, ?, u32 nStates, Tree** trees}.
  * For each state s it calls `tree[s]->vtbl[1]` = **`FUN_180013ab0` traverse**, then `FUN_180003e94` builds the CHMMState from the leaf.
    Duration streams (3/6) with `hdr+0x38->+0xc` set use `FUN_1800b1218` instead [G: phone-level leaf].
* **Tree traverse `FUN_180013ab0`** [V]. A node is 12 bytes: `u16 question; i32 no; i32 yes` (at +4/+8).
  A child > 0 is a relative jump (`node += child`, in nodes); a child <= 0 is a leaf `-child`. The question table
  (`tree[3]`) has 0x40-byte entries: `+0x18` feature index, `+0x20` feature def (its `+0xc4` type must match),
  `+0x28` op, `+0x30` values array (16-byte items, value at +8), `+0x38` count.
  Ops: 0 `==`, 1 in-set (any equal; strings compared with `_wcsicmp`), 2 `q < f`, 3 `q <= f`, 4 `f < q`, 5 `f <= q`,
  where q = question value and f = feature value. With a string feature and op != 1, `FUN_180014220` compares.
  An optional trace (param_4) records (nodeIndex, answer).
* Leaf classes (`CHTSDecisionTreeImpl<...>`, vtbls 0x180175b20 F0, 0x180170dd0 LSF, 0x180170e20 MBE, 0x180170e70
  Offset (ATM transforms), 0x180175bc0 PhoneDuration, 0x180175b70 StateDuration). Pool/leaf decoding is file-format
  territory (see the parent's APM notes).
* Multi-sub-stream states (for example lf0 static/Δ/ΔΔ stored as separate MSD streams) are **concatenated** into one
  vector by `FUN_180008790`, then `FUN_180007044`, then `FUN_18000766c` (mean*prec and prec copied in order; the MSD weight
  `+0xc` comes from the first) [V].
* CHTSTransformModel (`.ATM`): chosen per domain name via `FUN_18006f18c` and applied in `FUN_1800a08d8`, then `FUN_1800b214c`.
  It walks per-state trees with **Offset leaves** and applies them to the looked-up Gaussians (`FUN_1800b22ec`).
  [G] This is a bias / mean-offset adaptation, not a full MLLR matrix. It is irrelevant for the shipped en-US voices (no ATM).

---------------------------------------------------------------------------------------------------
## 3. Durations: `CDurationPredictor` main `FUN_1800692d0` [V, disasm-checked]

Gaussian accessors: `mean_i = FUN_18004caac(m,i) = (+0x18)[i] / (+0x20)[i]` (float division), and
`FUN_1800075cc` gives `S = Σ mean_i` and `V = Σ 1/prec_i` (float, sequential).

Per phone p (nStates n = 5):
```
if (preset row p all zero):                       # else: keep the preset durations (pauses etc.)
    S, V = FUN_1800075cc(stateDurModel)
    T = S
    if phone-duration model (stream 6) present:   # pred+0xac
        P = max(mean_phone, (float)n)
        T = (P - S) * W + S                       # W = PhoneDuration.Weight/100 clamped [0,1]; default 0.9
    [HEQ: Eva only, blend with DurationHeqAdjustment/100]
    rho = (V > 0) ? (T - S) / V : 0
    carry = 0 (reset per phone) ; sum = 0
    for i in 0..n-1:
        m = mean_i
        x = (m == 0.0) ? 0.0 + m : rho / prec_i + m     # float ops, this order
        d = (int)trunc_f32((x + carry) + 0.5f) ; if d < 1: d = 1   (cvttss2si; <=1 gives 1)
        carry += x - (float)d ; dur[i] = d ; sum += d
    if |(double)carry| > 1.0:  FUN_1800a47ac(&sum, target=(int)(T+0.5f), dur, n)   # missed by Ghidra
    limit = 160 if (feature-flag && word-type==4)
            80  if FUN_18004d844(phone)             [G: pause/silence-like phone]
            else Config.MaxFramesPerPhone (default 40)
    if sum > limit: FUN_1800a47ac(&sum, limit, dur, n)
FUN_18006cda8(...)                                # rate (below)
```
`FUN_1800a47ac(rescale)` [V]:
```
tgt = max(n, target); s = tgt/(float)sum; carry = 0
for i: y = (float)dur[i]*s; v = (double)(y+carry)+0.5; d = v>1.0 ? (int64)v : 1; carry += y - d
while sum != tgt: k = first index of maximum dur;  dur[k] = (sum+1 < tgt+dur[k]) ? tgt-sum+dur[k] : 1
```
(`FUN_1800a4710` is used instead when `FUN_18001d540(phone)` holds [G: spell-out phones].)

A second pass (after all phones) handles word groups with an explicit target duration in ms (`word+0x78..+0x14`,
converted by `FUN_1800a436c = (sr/1000*ms)/shift`). This is SSML-driven; it is a no-op for plain text [G]. Then `space+0xb8 = T_total`.

### Rate `FUN_18006cda8` [V, powf arguments from disasm 0x18006d131..]
```
siteRate  = ISpTTSEngineSite rate clamped [-10,10]         (FUN_18004e72c -> rateobj+0x18)
absRate   = double rateobj+0x20, default 1.0; set from engine-site "rate ex" clamp[0.18, 1+NF*5/100] (FUN_18006d3b0)
            [G: WinRT SpeechSynthesizerOptions.SpeakingRate]
xmlRate   = phone+0x78 -> +4 (SAPI XML <rate>), clamped [-20,20]
if absRate == 1.0: f = 3^(siteRate/10) * 3^(xmlRate/10)   (powf(3, x/10.0 as float))
else:              f = (float)absRate * 3^(xmlRate/10)
SR = property "MSTTS.SpeakRate" + emotionRate(param_8)
f *= (SR > 0) ? 1 + ((g(SR)-1)*NF)/100 : g(SR),  g(x)= x<1 ? 1+x/120 : 1+min(x,100)*0.05,
     NF = VoiceSetting.MSTTS_SpeakRate_NormalFactor (David 81, Zira 63, Mark 57)
R = Config.RateAdjustment (default 100; a domain config can override) [* domain NUS rate/100] ; if param_6 != 100: R = R*param_6/100
if R != 100 and !FUN_18001d540(phone): f = R*f/100
if VoiceSetting.MixRateScale != 0 and (new=(uint)(sum/f)) > n: rescale durations to `new`
```
The whole block is skipped when all inputs are neutral. **MixRateScale=1 (David)** means the rate is applied to the
HMM durations. Zira and Mark have no MixRateScale, so the duration is not rescaled here.
[G] Their rate change then happens on the waveform (`CRateChangerSonic`, WaveScale=Sonic; see `FUN_18004dd00` in the wave path).
Domain `RateAdjustment` (for example phoneNumber 80) is applied at the end for word type 4 when `R/100*f > 1.5` [V structure, G semantics].

---------------------------------------------------------------------------------------------------
## 4. Trajectory generation (MLPG)

Driver: `FUN_1800aed9c(space+0x88, stream, durs, voicedMask|0, windows, out, settings, nusOK, streamSel, nusMode, hook)`
calls `FUN_180068544` [V].
* It counts the frames to generate (voiced frames only when a mask is given), allocates a compact matrix, and runs
  `FUN_180007f00`, which builds the per-frame Gaussian list:
  * frame t of state s points at the state's Gaussian.
  * **Boundary/MSD rule:** for window j and each tap k with coef != 0: if t+k lies outside [0,T), or (with a mask) frame t+k
    is unvoiced, then that window's slice (dims j*D .. j*D+D-1) of `mean*prec` and `prec` is zeroed in a copy-on-write clone
    (`FUN_1800082a0`; `FUN_18000897c` float / `FUN_1800088e0` int).
* An optional NUS override (`FUN_1800ae84c`) replaces frame Gaussians with NUS-unit ones (needs NUS units; not for plain text).
* `FUN_18000ca70` = MLPG, **independently per dimension d** [V]:
  * `FUN_18000cbd8` builds the band `WUW` (width = window width, double) and `WUM` (double).
    * **Fast path `FUN_18000d6a0`**: taken when there are exactly 3 windows, w0=[1.0], and Δ and Δ² are both 3-tap with Δ centre 0.0
      (the standard HTS windows). Products of window coefficients are formed **in float** (for example `d[+1]*d[+1]`) and multiplied by
      the float precision in float. Each term is then converted to double and accumulated in double, in this order for row t:
      `WUW[t][0] = P_s[t] + d1²·P_Δ[t-1] + d-1²·P_Δ[t+1] + a1²·P_Δ²[t-1] + a0²·P_Δ²[t] + a-1²·P_Δ²[t+1]`,
      `WUW[t][1] = a0a1·P_Δ²[t] + a-1a0·P_Δ²[t+1]`, `WUW[t][2] = d-1d1·P_Δ[t+1] + a-1a1·P_Δ²[t+1]`,
      `WUM[t] = b_s[t] + d1·b_Δ[t-1] + d-1·b_Δ[t+1] + a1·b_Δ²[t-1] + a0·b_Δ²[t] + a-1·b_Δ²[t+1]`
      (b = mean*prec; d = Δ window, a = Δ² window; a1 = coefficient at +1). Rows 0, T-2 and T-1 are special-cased.
      Replicate FUN_18000d6a0 literally for bit exactness.
    * Generic path: HTS calc_WUW_and_WUM with `WUW[t][k] += ((double)w[-i+k] * (double)P) * (double)w[-i]` and
      `WUM[t] += (double)b * (double)w[-i]`.
  * `FUN_18000cf70`: in-place LDL^T (HTS "Cholesky"), in double. Pivot guard: `if |D[t]| <= 1e-6 then D[t] = 1.0`
    (DAT_18017f890). Width-3 specialisation:
    `D[t] -= L[t-2][2]*L[t-2][2]*D[t-2]; D[t] -= L[t-1][1]*L[t-1][1]*D[t-1]; L[t][1] -= L[t-1][1]*L[t-1][2]*D[t-1]; guard; L[t][1]/=D[t]; L[t][2]/=D[t]`.
  * `FUN_180012e30`: forward substitution `g[t] = r[t] - L[t-1][1]g[t-1] - L[t-2][2]g[t-2]` (double), then `g[t] /= D[t]`.
    Back substitution **uses the float-rounded outputs**:
    `c[T-1]=(float)g[T-1]; c[t]=(float)((g[t] - (double)c[t+1]*L[t][1]) - (double)c[t+2]*L[t][2])` [V].
* **There is no GV and no postfilter at the parameter level** (the LsfSharpen postfilter lives in the vocoder, not here).

### 4.1 Int-space (Zira/Mark) variant [V structure, details G]
`FUN_1800ad874` / `FUN_1800ada04` / `FUN_1800adbdc`:
* `FUN_1800451a0` decodes the quantised model refs into integer means/precisions.
* `FUN_180008a6c` builds the frame list.
* `FUN_18000c0f0` solves. The fast path is `FUN_18007af3c`: 2 windows, Δ=[-0.5? (DAT_180194090),0,0.5]. It uses the integer band
  solver `FUN_180076b04`, then `FUN_1800aef84`, then `FUN_1800af178`. Otherwise the double LDL uses off-diagonals scaled by 2^28 (DAT_18017da40)
  and stored as int32.
* Post-steps: stream 1/5 fast path `FUN_1800af4b4` smooths along time as `y[t] = (x[t-1] + 2x[t] + x[t+1]) >> 2`
  for t in 1..T-2, using the original x[t-1] (saved before overwrite; non-recursive [1 2 1]/4). Stream 7 is clamped to <= 0x8000 (Q15). Stream 2 is multiplied by 7.
  The last LSF-stream dim is multiplied by 10. Stream 2 also holds the mean over runs of >= 2 unvoiced frames [G]. The scales need parent verification.

---------------------------------------------------------------------------------------------------
## 5. Stream-specific processing

### 5.1 UV decision (`FUN_18003b890`) [V + disasm]
* `FUN_18003b968`: the per-state voiced weight `w[k]` is the max over the stream-2 state's space entries of `+0xc` (MSD weight),
  with k = phone*nStates + state.
* Threshold `thr = Config.VoicedWeightThreshold` (default 0.5; `FUN_18004d440`).
* **FrameLevel=yes** (David, Zira, Mark) uses `FUN_18004d258`. For global state k with duration d:
  `cur = w[k]`, `prev = w[k-1]`, `next = w[k+1]` (0 beyond the end). **Quirk:** for k=0, cur=0, and for k=1, prev=0
  (w[0] is never read).
  ```
  if cur > thr or (prev > thr and next > thr): all d frames voiced
  else: n = (int64)((float)d*cur + 0.5f)
        frame j voiced iff (prev>thr and j<n) or (next>thr and d-j<=n)
  ```
* FrameLevel=no uses `FUN_1800a4ea8`: the state is voiced iff w>thr. For "voiced phones" (`FUN_180076f5c`) there is gap filling
  (`FUN_1800a5014`); then it expands to frames (`FUN_18014b9ec`).
* Output: `space+0x10` int[T].

### 5.2 F0 float path `FUN_1800a6304` [V]
1. `FUN_1800a57b0`: MLPG on stream 2 with the voiced mask. Out: `space+0xc0` (logF0; unvoiced = 0).
2. `pred+0x88` / `pred+0x80`: optional debug dumpers (`FUN_1800a5964`, which prints `"%f"` per frame). They are useful hooks, not math.
3. If `pred+0x70` (the stream-2 "customized generation setting", from `FUN_1800afab8(...,2)` `.+0x28`) is set and the utterance is
   not NUS, `FUN_1800a5394` runs:
   * `FUN_180016010(f0, win, 0, T, isInt)`: centred FIR over each frame t with f0[t]!=0. It extends backward up to N/2 and forward up to
     N-N/2-1 frames but **stops at the first unvoiced (0) frame or at the utterance edge**.
     `out[t] = (Σall w / Σused w) * Σused w_k f0[t+k]` (float; the Q15 variant uses int64 >>15). Input is a snapshot copy.
   * `FUN_18003ff28`: `f0 = (f0 - Mean)*EnhanceRate + Mean` for f0 != 0 (Mean=`+0x24`, rate=`+0x20`). Float ops must be kept
     even when rate==1.0.
4. `FUN_1800616a8`: LogF0 HEQ (only if a HEQ table exists; Eva).
5. If `Config.QuestionIntonation` is enabled (Zira: rate 0.005, max 5.35), `FUN_1800a5f78` runs:
   * `FUN_1800a5cbc` finds the question sentence (the word's sentence type at `+0x228` is 3 or 5) and the first voiced frame s at/after
     the start of its last word's syllable [G on the exact unit]. e = the last voiced frame of the utterance.
   * `FUN_1800a65a8`: `if f0[s] + (e-s)*rate > max: f0[s] = max-(e-s)*rate`; then for voiced t in [s,e]: `f0[t] = (t-s)*rate + f0[s]`.
     This **replaces** the contour with a linear ramp.
   * Then `FUN_180016010` with an 11-tap boxcar (1/11 = 0.0909091f; Q15 0x453a2e8c for int) over frames [max(s-20,0), min(s+20,T)).
6. Int path `FUN_1800a615c` is the same, with `FUN_1800a571c` / `FUN_1800a585c` / `FUN_1800a5254` / `FUN_1800a5590` / `FUN_1800a5e14`.

### 5.3 LSF (`FUN_1800a6d04`), stream 1 (and 9)
MLPG with no mask; out `space+0xc8` (or `+0xd0`), [T][order]. `order = streamDim-1` (the last dim is gain), <= 40.

### 5.4 Gain (`FUN_180059550`), stream 5
MLPG (1 dim) into `space+0xd8`, then GainHeq (Eva).

### 5.5 Final export (after all predictors) `FUN_1800a25f4` (float) / `FUN_1800a2488` (int) [V]
1. `FUN_180069b34`: for each F0 != 0, `f0 = (float)exp((double)f0)`, giving Hz.
2. `FUN_18006bfec`: LSF sanity per frame. If not non-decreasing, fix with `FUN_18006c12c`. If any value is outside [0, 0.5],
   copy the previous frame (frame 0: `FUN_18006c18c`). LSFs are in cycles/sample, 0..0.5.
3. `FUN_180065380`: NUS trajectory refiner (only with NUS units).
4. **Pitch** `FUN_18001b100`, per phone over its frames:
   ```
   k  = gP(MSTTS.Pitch) * powf(2, clamp(xmlPitch,-10,10)/24.0) * (float)absPitch      # absPitch = engine+0x278 (double, default 1)
        gP(x) = x<1 ? 1+x/200 : 1+min(x,100)*0.01
   P  = Config.PitchAdjustment (+Sps/SpsWithNus variants when NUS mixes) + emotion.PitchAdjustment - 100
   if P != 100: k = P*k/100
   FUN_18007afa8: for f0>3: f0 = clamp(f0*k, 3, 8000)     (skipped when everything is neutral)
   ```
   The per-word contour hook is `FUN_1800a11f4` (word+0x28 -> +0x48) [G: SSML contour].
5. Pitch range: `S = Config.PitchRangeScale (+Sps variants) + emotion.PitchRangeScale - 100`, times a phone-level float (`+0x78+0xc`, default 1).
   If not identity, `FUN_1800a2810` computes `mean = Σf0/n` over f0>3 and then `f0 = clamp((f0-mean)*S/100*r + mean, 3, 8000)`.

---------------------------------------------------------------------------------------------------
## 6. CTTSEngineConfig (INI "VoiceSetting" etc.): ctor `FUN_180017a48`, loader `FUN_180056c00` [V]
| off | key | default | clamp |
|---|---|---|---|
| +0x08 | VoiceSetting.VolumeAdjustment | 100 | 1..1000 |
| +0x0c | VoiceSetting.SpsVolumeAdjustment (David 180) | 100 | 1..1000 (used by the vocoder) |
| +0x10 / +0x14 / +0x18 | PitchAdjustment / SpsPitchAdjustment / SpsWithNusPitchAdjustment | 100 | |
| +0x1c / +0x20 | RateAdjustment / SpsRateAdjustment | 100 | |
| +0x24 | SpectrumAdjustment | 100 | <=200 |
| +0x28 / +0x2c / +0x30 | LogF0Heq / DurationHeq / GainHeq adjustment | 100 | |
| +0x34 / +0x38 / +0x3c | PitchRangeScale / Sps.. / SpsWithNus.. | 100 | |
| +0x5c | UVDecision.FrameLevel yes/no | 0 | |
| +0x64 | ShortPause.Enable | 0 | consumer not traced [?] |
| +0x68 | SilenceNoiseSuppress.Enable | | |
| +0x70/+0x74/+0x78 | QuestionIntonation enabled / LogF0RisingRate [-1,1] / LogF0MaxValue [0,10] | off | |
| +0x7c | PhoneDuration.Weight/100 | 0.9 | [0,1] |
| +0x80 | UVDecision.VoicedWeightThreshold | 0.5 | [0,1] |
| +0x84 | MultiBandExcitation.Offset | 0 | |
| +0x88 | PhoneDuration.MaxFramesPerPhone | 40 | |
| +0xf8 | CFormantSharpenSetting (LsfSharpen.*; defaults Intervals 2, MultipleInterval 1, 0.4, 0.7): vocoder | | |
| +0x100 | CTTSEmotionSetting | | |

* **EmotionRecipe** (`FUN_180016da0`): 0x14-byte entries `{id, Rate +4, Pitch +8, PitchRangeScale +0xc, Volume +0x10}`.
  Only active when the input requests an emotion; plain text uses the neutral values (100) [G].
* **SilenceLength** (CTTSProsodySetting `FUN_180051980`): 8 keys (WordBoundary, IntermPhraseBoundary, PuncIntermPhrase,
  NonPuncIntonationPhrase, ParalStructIntonationPhrase, ParalStructListIntonationPhrase, IntonationPhraseBoundary,
  SentenceBoundary), plus SpeakSessionStart/End (min 5) and RatioNameEntities. `MSTTS.NoPause=1` zeroes entries 3..6.
  They are consumed on the frontend/pause-insertion side. Pause phones arrive with **preset state durations**, which the duration
  predictor keeps unchanged (the `row != 0` branch) [G: the exact ms-to-frames conversion site was not traced; likely
  `FUN_1800a436c`-style `(sr/1000*ms)/80`].
* **SpellOut.UnvoicedPhoneRate** is stored at engine+300 (used for spell-out durations) [G].

---------------------------------------------------------------------------------------------------
## 7. Hook points for a harness (parameter generation)
| what | VA | when / args (Win64: rcx, rdx, r8, r9) |
|---|---|---|
| tagger Process | 0x1800a3324 | (tagger, utt); on return all trajectories are final |
| stage events | `*(tagger+0x30)` vtbl[0] | (obj, mask, 0/1, utt); marks each predictor's before/after |
| feature extraction | 0x18005bfc0 | extractor vtbl[3](ext, utt, featDefs, out, n): **the backend input** |
| tree traverse | 0x180013ab0 | (tree, featVec, &leaf, trace); log the leaf index per stream/state |
| duration main | 0x1800692d0 | (durPred, space); after return read space+0x08 |
| rate | 0x18006cda8 | per phone |
| MLPG per dim | 0x18000ca70 | (windows, frames, ?, T, D, ?, out) |
| export | 0x1800a25f4 | on entry: logF0/LSF/gain/voicing final; on exit: F0 in Hz after pitch |
Space pointer: `utt + (utt[0x2c0] ? 0x4d0 : 0x2c8)`.

## 8. Open items
* Exact per-stream window coefficients and dims for David come from the APM (parent). Also check whether David has streams 6, 8, 9.
* The int-space decode scales (`FUN_1800451a0`) and the integer band solver `FUN_180076b04`/`FUN_1800aef84`/`FUN_1800af178`.
* The ShortPause consumer; the pause duration assignment site; the exact question-intonation anchor (last syllable vs last word).
