# OneCore engine: backend input, NUS/DNN use, and the x64 hooking plan

Scope: items 4, 5 and 6 of the backend map for `MSTTSEngine_OneCore.dll` 10.3.21207 (x64, image base 0x180000000,
md5 d7d84e2b439e4edc0f691efd2085f4fc, the same bytes as the System32 copy). All VAs assume that base.
Status tags: **[V]** means verified at runtime with `harness/ziraprobe.exe`. **[S]** means read from the decompile or
disassembly. **[G]** means a guess.

Tools added for this part:
- `tools/xref.py ADDR`: lists decompiled functions that reference an address.
- `tools/feat_table.py`: dumps the engine's feature tables (leaf features, path tokens).
- `tools/dis64.py VA [n]` / `dis64.py -p VA...`: x64 disassembly and a prologue report for inline hooks.
- `harness/ziraprobe.c` + `build_probe.bat`: an x64 SAPI5 probe that patches vtables and logs the pipeline and the feature matrix.

---

## 0. Which voice is actually rendered (important for reference WAVs)

| SAPI5 token (`HKLM\SOFTWARE\Microsoft\Speech\Voices\Tokens`) | CLSID | Engine DLL | Data |
|---|---|---|---|
| `TTS_MS_EN-US_DAVID_11.0` "Microsoft David Desktop" | {179F3D56-1B0B-42B2-A962-59B7EF59FE1B} | **OneCore** `System32\speech_onecore\engines\tts\MSTTSEngine_OneCore.dll` | `Speech_OneCore\...\M1033David` |
| `TTS_MS_EN-US_ZIRA_11.0` "Microsoft Zira Desktop" | {C64501F6-E6E6-451f-A150-25D0839BC510} | **legacy desktop** `System32\speech\engines\tts\MSTTSEngine.dll` | `Speech\Engines\TTS\en-US\M1033ZIR.APM` (6.18 MB, a different model) |

OneCore tokens are under `HKLM\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_{DavidM,ZiraM,MarkM}`.
They all use the same CLSID and carry the values `VoicePath` (for example `...\en-US\M1033David`, with no extension) and
`LangDataPath` (`...\MSTTSLocenUS.dat`).

- **[V]** `render.ps1 "Microsoft David Desktop"` runs the OneCore engine. Its output is byte-identical (md5
  6005C892...) to the probe driving the OneCore token `MSTTS_V110_enUS_DavidM`, and repeated runs are identical, so
  output is deterministic.
- **[V]** `render.ps1 "Microsoft Zira Desktop"` does **not** run OneCore Zira. It runs the older desktop engine and
  voice. `ref/zira_t1*.wav` is therefore not a OneCore Zira reference (assuming it came from render.ps1).
- **[V]** SAPI5 accepts the OneCore token path directly: `ISpObjectToken::SetId(NULL, L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices\\Tokens\\MSTTS_V110_enUS_ZiraM", FALSE)`
  followed by `ISpVoice::SetVoice`. This works for ZiraM, MarkM and DavidM:
  `ziraprobe.exe "text" out.wav HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_ZiraM`.
  System.Speech (render.ps1) cannot select these tokens. Use the probe, or a C renderer, for OneCore Zira and Mark references.
- Eva (`M1033Eva.*`) has no token, so SetVoice on `..._EvaM` fails with 0x8004503a.

---

## 1. Pipeline: handler chain and the frontend/backend boundary (item 4)

### 1.1 Construction [S]
`CTTSEngine` (vtable 0x18016f190, 28 slots, object 0x708 bytes, created in `FUN_18008a790`). Its Initialize is
slot 0 `0x1800955a0` → `FUN_1800930dc`. That calls `FUN_1800936c0` (the text processor), then `FUN_180058fac` and
`FUN_180060820`, which build the rest. Handlers go into the vector at engine+0x1a8 (or engine+0x1c8 when
`Pipeline.ParallelProcess`) through `FUN_1800511d0`. Each handler is enabled by a bit in the dword at engine+0x100.

| # | engine slot | enable bit | factory | class (handler vtbl) | GetID | log name |
|---|---|---|---|---|---|---|
| 1 | +0x1f0 | 0x40000 | FUN_1800b4888 | CTextProcessor (0x180175d00) | 0x40000 | |
| 2 | +0x1f8 | 0x80000 | FUN_18009b65c | CLinguisticProsodyTagger (0x180171328) | | "Linguistic Prosody Tagger" |
| 3 | +0x218 | 0x100000 | FUN_18009cc18 | CTTSUnitGenerator (0x1801757a8) | | "Unit Generator" |
| 4 | +0x200 | 0x4000000 | FUN_1800594ec | CAcousticProsodyTagger (0x18016ea58) | 0x4000000 (0x4000001 when anchor) | "Acoustic Prosody Tagger" |
| (4b) | +0x208/+0x210/+0x228 | EnableLongUnitAnchor | FUN_1800594ec / FUN_1800a3ffc / FUN_1800f2264 | anchor tagger, CLongUnitLatticeGenerator | | "...For Long Unit Selection" (not used by David/Zira/Mark) |
| 5 | +0x1e8 | Pipeline.EnableStreaming | FUN_180149864 | **CStreamHandlersAdapter** (0x180178ac0) holding the next three as stream handlers | | |
| 5a | +0x230 | 0x800000 | FUN_1800f5734 | CUnitLatticeGenerator (stream vtbl 0x1801771f8) | | "Unit Lattice Generator" |
| 5b | +0x238 | 0x1000000 | FUN_1800ff760 | CUnitSelector (stream vtbl 0x1801776c8) | | "Unit Selector" |
| 5c | +0x240 | 0x2000000 | FUN_18007a000 | CWaveGenerator (stream vtbl 0x180173060) | 0x2000000 | "Wave Generator" |

**[V] Runtime order for David, Zira and Mark, once per sentence** (the same `CTTSUtterance` object is reused):
`CTextProcessor → CLinguisticProsodyTagger → CTTSUnitGenerator → CAcousticProsodyTagger → CStreamHandlersAdapter{UnitLattice, UnitSelector, WaveGenerator}`.
Then `CTextProcessor` returns S_FALSE (hr=1) when no text is left. The adapter's list order (verified) is
lattice (+0x1771f8), selector (+0x1776c8), wave (+0x173060).

Handler interface (`ITTSHandler`, primary vtable, 7 slots) [S]:
0 `Init(engine)`, 1 `GetID(int*)`, 2 ?, **3 `Process(ITTSUtterance*, ?, ?)`**, 4 ?, 5 `Release/delete`, 6 dtor.
Streaming interface (`ITtsStreamHandler`, at object+8 in most classes, 10 slots) [S/V]:
**6 `Begin(utt)`** (+0x30), **7 `Step()`** (+0x38), **8 `HasMore(int *more)`** (+0x40), **9 `End()`** (+0x48).
`CStreamHandlersAdapter::Process` (0x1800488d0) calls Begin on every handler, then steps them in lockstep while
`HasMore==1`, then calls End. **[V]** For "Hello world." (11 phones including two sil) each of the three stream
handlers got 11 `Step` calls: one step per phone/segment (probably).

The generic `Process` for stream-only handlers (0x180149b30) runs the same Begin/HasMore/Step/End loop on a single handler.

### 1.2 The boundary
- **Frontend** = handlers 1 to 3. `CTextProcessor::Process` 0x1800b5110 does normalization, word breaking, POS,
  pronunciation and syllabification [G on the split]. `CLinguisticProsodyTagger::Process` 0x180060010 does
  breaks/accents/boundary tones (CProsody*Predictor, CProsodyModelRunner) [G]. `CTTSUnitGenerator::Process`
  0x180034b00 builds the segment/unit lists in the utterance.
- **Acoustic backend entry = `CAcousticProsodyTagger::Process` 0x1800a39f0** (handler slot 3, vtbl 0x18016ea58+0x18).
  Its signature is `HRESULT (this, ITTSUtterance *utt, ?, ?)`. It checks the utterance with `FUN_18005c534`
  (dynamic_cast to CTTSUtterance). The core is `FUN_1800a3324(this, utt, domainName, ...)`, which does:
  1. `FUN_180032dc8`: select the model set (`CHTSModelSetManagerAdapter`, `FUN_1800aff30` by domain name utt+0x70,
     falling back to "general"). `FUN_1800a2bd4` computes the **context feature matrix** (below) and looks up trees
     (`FUN_18000246c`). Per-phone model pointers go into the acoustic space.
  2. `FUN_1800653c4`: runs the acoustic predictors in lockstep (stream slots 6/8/7/9 on each predictor in the vector
     at this+0xa8/+0xb0), filling the per-frame acoustic space.
- **Backend output = `CTTSAcousticSpaceImpl<float>` inside the utterance**, at utt+0x2c8, or at utt+0x4d0 when
  utt+0x2c0 != 0. utt+0x2c0 is copied from the model header dword +0xc (`FUN_1800331b0`).
  **[V]** utt+0x2c0 is 0 for David and 1 for Zira and Mark (these two have `[LSPDecomposing] DelayMode=1`; the link is [G]).
  `CWaveGenerator` (stream Begin 0x180057df0) reads that space. The frame-parameter details belong to the param-gen/vocoder notes.
- **[V] Predictors run by David, Zira and Mark** (vector at CAcousticProsodyTagger+0xa8, element vtables):
  0x180173188 CDurationPredictor, 0x180173240 CUVPredictor, 0x180173200 CNuSpsPredictor, 0x180171710 CF0Predictor,
  0x180171620 CLsfPredictor, 0x180171788 CGainPredictor. There are **no** MBE, Energy, Power, NN or PostNN predictors
  for these voices.

### 1.3 The utterance object (CTTSUtterance, vtbl 0x18016d020) [S unless marked]
| off | meaning |
|---|---|
| +0x70 | domain-name string object; +0x78 = its `wchar_t*`. **[V]** "none" before the adapter, "general" after |
| +0x98 | ptr → ptr → +0x10 int* (model-set / style index, default 1) [S] |
| +0xd0/+0xd8 | condition variable / SRW lock used by the streaming stages |
| +0xe0 | current `CTTSSentence*` (all list getters go through it) |
| +0xe8 / +0xf8 | **segment list** {head,tail,...,count}. Nodes are {next, prev, CTTSSegment*}. seg+0xb8 is the domain-name object and seg+0xc0 its `wchar_t*`. **[V]** one segment per phone, all "general" for plain text |
| +0x148 | hash map phone → model list [S] |
| +0x250 | passed to the output object in CWaveGenerator::Begin |
| +0x2c0 | acoustic-space selector (see above); +0x2c8 space A (0x208 bytes), +0x4d0 space B |
| +0x348 (+0x208) | phone-list pointer cached in the chosen space |
| +0x708 / +0x720 | unit/candidate lists used by the lattice and wave generator [S] |
| +0x750 | refcount (slot 1) |
| +0x754 | anchor flag checked by CAcousticProsodyTagger::Process |

`CTTSSentence` (vtbl 0x18016fde8, 27 slots) list heads [S]: phones +0xb0 (slot 8), syllables +0xe0 (slot 7),
words +0x110 (slot 5), prosodic words +0x188 (slot 6), phrases +0x1b8 (slot 9), intonation phrases +0x1e8 (slot 10) [G for the last].
The utterance wrappers are 0x1800331d8 (phones, sentence vt+0x40), 0x18014a2c4 (syllables, +0x38), 0x180034e44
(words, +0x28), 0x18014a1a4 (prosodic words, +0x30), 0x18014a170 (phrases, +0x48). A list is {head node*, ?, count}.
The first node's element is at node+0x10. The node classes are the `CTTSUtteranceNodeBase<Parent,Self,Child>`
templates (Sentence→IntonationPhrase→Phrase→Word→Syllable→Phone→HalfPhone, plus ProsodicWord, Segment, Unit and NusUnit).

### 1.4 What the backend "sees": the named-feature matrix [S+V]
The acoustic model set does not store HTS label strings. It stores **named path features**, which are XOR-encrypted
UTF-16 strings in the APM string block (header dword file+0x44 = offset, +0x48 = size). They are decrypted by
`FUN_180039f60`: each non-zero u16 is XORed with the u16 key `DAT_1801807d8[k]`, where k counts non-zero chars mod 8.
The key is u16[8] = 3412 7856 bc9a f0de 5634 de bc 9a78 12f0 (bytes `123456789abcdef03456bcde789af012`). Zero chars
pass through and do not advance k. (The parent's `apmstr.py` may already cover this.)

The strings are, in order: (a) the model's base feature list, (b) the question strings, (c) the stream names
"Linear Spectrum Pair", "Log Fundamental Frequency", "Duration", "Phone Duration".
David's base list has **44 features** (Zira 41, Mark 42 **[V]**; the exact names for those two are in their string blocks):

```
00 Phone.BwPosInSyllable                 01 Phone.FwPosInSyllable
02 Phone.NextPhone.NextPhone.PhoneIdentity 03 Phone.NextPhone.PhoneIdentity
04 Phone.PrevPhone.PhoneIdentity         05 Phone.PrevPhone.PrevPhone.PhoneIdentity
06 Phone.Syllable.BreakIndex             07 Phone.Syllable.BwPosInPhrase
08 Phone.Syllable.BwPosInWord            09 Phone.Syllable.FwPosInPhrase
10 Phone.Syllable.FwPosInWord            11 Phone.Syllable.NextSyllable.Accent
12 ...NextSyllable.BreakIndex            13 ...NextSyllable.PhoneNumber
14 ...NextSyllable.Stress                15 Phone.Syllable.PhoneNumber
16 ...PrevSyllable.Accent                17 ...PrevSyllable.BreakIndex
18 ...PrevSyllable.PhoneNumber           19 ...PrevSyllable.Stress
20 Phone.Syllable.Stress                 21 Phone.Syllable.Word.BwPosInPhrase
22 ...Word.BwPosInYesNoQuestion          23 ...Word.FwPosInPhrase
24 ...Word.NextWord.POS                  25 ...Word.NextWord.SyllableNumber
26 ...Word.Phrase.BwPosInSentence        27 ...Word.Phrase.FwPosInSentence
28 ...Phrase.IntonationPhrase.Sentence.PhraseNumber
29 ...Sentence.SentenceType              30 ...Sentence.SyllableNumber
31 ...Sentence.WordNumber                32 ...Word.Phrase.SyllableNumber
33 ...Word.Phrase.WordNumber             34 ...Word.POS
35 ...Word.PrevWord.POS                  36 ...Word.PrevWord.SyllableNumber
37 ...Word.SyllableNumber                38 Phone.PhoneIdentity
39 ...Word.FwPosInYesNoQuestion          40 ...Phrase.NextPhrase.SyllableNumber
41 ...Phrase.NextPhrase.WordNumber       42 ...Phrase.PrevPhrase.SyllableNumber
43 ...Phrase.PrevPhrase.WordNumber
```
Questions are strings over these features: `F<=N` (integers), `F==v` (enums/POS, including `==null`), and
`F_Class` for PhoneIdentity (a phone or a phone class, for example `Phone.PhoneIdentity_Vowel`, `_Voiced-Stop`, `_sil`).
The PhoneIdentity classes seen are aa ae ah ao aw ay b ch d dh eh er ey f g hh ih iy jh k l m n ng ow oy p r s sh t
th uh uw v w y z zh sil, plus articulatory classes (Vowel, Front, Nasal, Liquid, Fricative, ...). The class
membership table has to come from the language data or the APM (parent/frontend).

**Path grammar** (`FUN_180037e34` parses the spec, `feat_table.py` dumps the tables):
- Path tokens (table 0x18016fee0, 24-byte entries {name, level, dir, ?, allowed-after mask}):
  Phone/PrevPhone/NextPhone/FirstPhone/LastPhone (level 1), ...Syllable (4), ...Word and ...Token (8),
  ...ProsodicWord (0x10), ...Phrase (0x40), ...IntonationPhrase (0x80), Sentence (0x200).
- Leaf features (table 0x18016f280, 24-byte entries {wchar* name, u32 id, u32 type, u32 levelmask}). There are
  about 100. The ones used here: PhoneIdentity 0x00, PhoneNumber 0x01, SyllableNumber 0x02, WordNumber 0x03,
  PhraseNumber 0x05, FwPosInSyllable 0x07, BwPosInSyllable 0x08, Fw/BwPosInWord 0x09/0x0a, Fw/BwPosInPhrase
  0x0d/0x0e, Fw/BwPosInSentence 0x11/0x12, Stress 0x15 (type 1), Accent 0x16 (type 1), BreakIndex 0x2a, POS 0x17,
  SentenceType 0x2e (type 1), Fw/BwPosInYesNoQuestion 0x2f/0x30. Type 0 is an int, 1 an enum, 2 a string.

**Feature matrix = backend input as the trees consume it** [V]:
`CTTSFeatureExtractionEngine` (vtbl 0x1801714b8) slot 3 = `0x18005bfc0 (this, CTTSUtterance *utt, FeatureMeta *metas /*0x100 B each*/, FeatureValues *out /*0x20 B each*/, int n)`.
It is called from `FUN_1800a2bd4` with n = 44 for David. `out[i] = {Value *data; size_t count; size_t cap; int grow}`
holds one Value per phone. A Value is 16 bytes: `{i32 kind; i32 pad; union{i32 v; wchar_t *s}}`. kind 0 is an
integer, 1 an enum, 2 a string, and kind -1 with v -1 is null (the context does not exist). Example, David, "Hello world." (11 phones):

```
f38 PhoneIdentity : 3 23 18 29 33 44 19 36 29 16 3      (sil hh eh l ow w er r l d sil)
f00 BwPosInSyll   : null 2 1 2 1 5 4 3 2 1 null
f29 SentenceType  : enum 0 ... ("Is it raining?" -> enum 1)
f24 NextWord.POS  : 38 3 3 3 3 null ...                 (POS ids are ints)
```
Phone ids observed [V]: sil=3, d=16, eh=18, er=19, ey=20, hh=23, ih=24, l=29, n=31, ng=32, ow=33, r=36, t=39, w=44, z=46.
This matches an alphabetical ARPAbet list with d at 16 [G]: aa=7? ... zh=47. The full phone-id and POS-id tables
are still TODO. Get them from `CTTSPhoneConverter` / the language data, or by probing more words.
`CTTSUnitGenerator::Process` also calls the extractor twice with n=1 (Fw/BwPosInWord style values), and that
drives unit generation.

**Implication for the port:** the frontend must produce an utterance tree with, per phone, a phone id; per syllable
Stress, Accent and BreakIndex; per word POS and yes/no-question positions; per sentence SentenceType; and the
phrase/intonation-phrase structure. The backend then only needs this 44-column int matrix, one row per phone
(including the sil at each end). A harness can dump exactly this matrix at `0x18005bfc0`, which makes it the natural
cut point and golden-file format between the frontend and backend ports.

---

## 2. NUS clips and the DNN path (item 5)

- **[V] For plain text, David, Zira and Mark are pure SPS (HMM).** The lattice and selector stream handlers do run
  (Begin, 11 Steps, End), but every segment's domain is "general". `CWaveGenerator::Begin` (0x180057df0) only
  looks up NUS domain data (`FUN_18006dd4c(nusData, name)`) for segments whose domain is not "general". This held
  for "Hello world.", "Press Ctrl+Alt+Delete then Tab.", single letters ("a", "x"), key names ("Tab", "Enter",
  "Backspace"), and SSML `<say-as interpret-as="keyboard|characters">`.
- **Domain assignment** is done by `CNusUnitDetectorManager` (vtbl 0x180176ca0, slot 3 `0x18005eae0`) [S]. It sets
  utt domain "none" to "general" and runs domain detectors (`NusRuntime.AllowDomainDetection`,
  `NusRuntime.OverwritingDomainName`, "hotfix"). It switches "general" to **"keyboard"** only when
  `FUN_180034d98(utt)` is true: exactly one word whose word+0x90 → int == 4 (every other word must be skipped by
  word vt+0x270). Word type 4 is probably a keyboard/character token produced for a specific API (for example
  Narrator key echo) [G]. None of the tested SAPI inputs triggered it.
- Domains from settings: `Segments.Domain%d` engine settings (`FUN_18007316c`) and the INI
  `[Domain]` entries (David: keyboard → `NUSData\M1033David.keyboard.{NU2,RAD,UNT,WIH,WVE}`; Zira/Mark:
  phoneNumber (only a RateAdjustment), tbtdirection → `TBT.NUS`, speechux → `SpeechUX.NUS`, keyboard). The engine
  loads these at init ("%s Successfully Load %s domain data"). They only matter when an app tags segments with that
  domain (turn-by-turn navigation or speech UX prompts) [G]. `NuspsConvarFp` and `DrcEnable`/`BiquadFilterEnable`
  for those domains are per-domain post-processing (the vocoder notes cover the DRC/biquad code).
- **CNuSpsPredictor runs for plain text** [V], as one of the six predictors. It has no NUS target in the general
  domain, so presumably it passes through [G]. Check it bit-exactly in the param-gen notes.
- **DNN path** (CDNNVoiceData, CTTSMLPDataLoader, CMLP*, CNNPredictor, CPostNNPredictor, CITFTE excitation) is not
  instantiated for David, Zira or Mark [V: the predictor list above]. The data files that feed it (`.NNM`, `.BR2`,
  `.TON`, `.HEQ`, `.ACL`, `.TDAT`) exist only for Eva, whose INI has `[NN]` and `LSPDecomposing` model-range keys.
  A port of David, Zira and Mark can ignore it.
- Long-unit (anchor) lattice: off unless `Pipeline.EnableLongUnitAnchor` (only the Eva-style `[LatticeGeneration]`/`[Pipeline]`
  settings) [S]. It was not observed for the three voices [V].

---

## 3. Hooking plan for a 64-bit harness (item 6)

### 3.1 Loading
- The simplest route, verified: SAPI5 in-process. `LoadLibraryW(System32\speech_onecore\engines\tts\MSTTSEngine_OneCore.dll)`
  first, so the module is already mapped when COM loads the same path. Patch it, then
  `SpVoice` + `SpObjectToken::SetId(<OneCore or Desktop token path>)` + `SpStream::BindToFile` (16 kHz/16-bit/mono) + `Speak`.
  The probe does exactly this (`harness/ziraprobe.c`). Hooking does not change the output (md5 matches render.ps1).
- Without SAPI (later): the DLL exports only `DllGetClassObject` / `DllCanUnloadNow` / `DllRegisterServer` /
  `DllUnregisterServer`. `DllGetClassObject(CLSID {179F3D56-1B0B-42B2-A962-59B7EF59FE1B})` → `IClassFactory` →
  object implementing `ISpTTSEngine` + `ISpObjectWithToken`. `SetObjectToken` reads the token values
  `VoicePath` and `LangDataPath` ("[Initialization] VoicePath = %s", `%s%s\MSTTSLoc%s.dat`) and the `Attributes`
  subkey. You would have to supply your own `ISpObjectToken`, a `ISpTTSEngineSite` (Write/GetActions/GetRate/...)
  and a `SPVTEXTFRAG` list. Not needed while SAPI5 works.
- The DLL is `/guard:cf` (DllCharacteristics 0x4160). Its indirect calls go through `_guard_dispatch_icall`. Targets
  inside a non-CFG harness EXE and `VirtualAlloc(PAGE_EXECUTE_READWRITE)` trampolines are accepted (verified for
  EXE functions). Keep the harness EXE non-CFG.

### 3.2 Vtable patches (preferred; no code patching; RVA = VA - 0x180000000)
| what | vtable VA | slot | fn | args |
|---|---|---|---|---|
| handler Process: text processor | 0x180175d00 | 3 | 0x1800b5110 | (this, utt, ?, ?) |
| handler Process: linguistic prosody | 0x180171328 | 3 | 0x180060010 | same |
| handler Process: unit generator | 0x1801757a8 | 3 | 0x180034b00 | same |
| **backend entry**: acoustic prosody tagger | 0x18016ea58 | 3 | 0x1800a39f0 | same |
| stream adapter Process (segments ready, before wave) | 0x180178ac0 | 3 | 0x1800488d0 | (this, utt) |
| **feature matrix** CTTSFeatureExtractionEngine | 0x1801714b8 | 3 | 0x18005bfc0 | (this, utt, metas, out, int n) = 5 args |
| lattice stream Begin/Step/HasMore/End | 0x1801771f8 | 6/7/8/9 | 0x18005b360/0x18001e000/... | (this, utt) / (this) / (this,int*) / (this) |
| selector stream | 0x1801776c8 | 6..9 | slot 7 = 0x1800180c0 | |
| **wave generator** stream | 0x180173060 | 6 Begin 0x180057df0, 7 Step 0x180032150, 8 HasMore, 9 End 0x18005f5b0 | | |
| predictors (acoustic tagger vector) | Dur 0x1801730f8, F0 0x18016ec88, Lsf 0x18016ed20, UV 0x18016eb28, NuSps 0x18016eb80, Gain 0x18016edb8 (stream vtbls at +0x40 of each object) | 6..9 | | per-predictor Begin/Step/End, for per-frame dumps |
| audio out | `CTTSEngineSite<ISpTTSEngineSiteEx>` 0x180175390 (or `<ISpTTSEngineSite>` 0x180175330) | 3 Write (0x1800623e0 → real site vt+0x30) | | (this, const void *pcm, ULONG bytes, ULONG *written) [G on the exact args] |

A vtable wrapper must preserve the argument count. All the slots above take 4 or fewer register args, except the
feature extractor (5). Declare wrappers with the same arity. In the x64 ABI a 4-arg passthrough wrapper is safe
only if the callee takes no stack arguments.

### 3.3 Inline hooks for non-virtual workers (the `dis64.py -p` report)
None of these prologues contain RIP-relative operands or branches in the first 14 or more bytes, so a
**14-byte `jmp [rip+0]; dq target` absolute jump** can be written over them. Copy the stolen bytes into the
trampoline and append another absolute jump back:

| fn | role | stolen bytes (whole insns ≥14 B) |
|---|---|---|
| 0x1800a3324 | CAcousticProsodyTagger core `(this, utt, domain, ?)` | 15: `mov rax,rsp; mov [rax+8],rbx; mov [rax+18h],rbp; push rsi; push rdi; push r14` |
| 0x1800a2bd4 | feature extraction + tree lookup `(this, utt, space, modelsetAdapter, transformAdapter)` | 15 (`mov rax,rsp; mov [rax+20h],r9; ...`) |
| 0x18000246c | tree lookup worker (10 args) | 15 |
| 0x1800653c4 | predictor lockstep loop `(this, utt)` | 14 |
| 0x180057df0 | CWaveGenerator::Begin (stream-this) | 15 |
| 0x1800321f0 / 0x180032828 | wave step workers (per segment) | 18 / 18 |
| 0x180110450 | vocoder/param-manager init with utterance `(vocoder, utt, intFlag)` | 15 |
| 0x18011024c | vocoder flush at end | 18 |
| 0x18004bb98 | engine output write `(output, pcm, bytes)` → site Write | 16 |
| 0x180148850 | output ring-buffer read | 15 |

Avoid tail-jump thunks such as 0x1800f5820 (`sub rcx,8; jmp`). Patch the vtable slot instead.

### 3.4 Suggested logs (as in anna's annatap, tagged records `u32 tag, u32 len, payload`)
1. T_FEATS at 0x18005bfc0 exit: n, count, then an n×count int32 matrix (-1 = null) plus the kinds. This is the
   **frontend→backend golden file**.
2. T_DUR/T_PARAM: per-predictor Step dumps. Use the acoustic-space layout from the param-gen notes, or hook the
   Gain/Lsf/F0 predictor stream slot 7 and read the space after each step.
3. T_EXC/T_FRAME: `CExcitationGeneratorImpl<float>` vtbl 0x180177ae8 (slot 1 0x1801100b0, slot 4 0x18010ebf0) and
   `CLsfSynthesizerImpl<float,float>` vtbl 0x180177a68 slot 1 0x180110220 (see the vocoder notes for signatures).
4. T_PCM: `CTTSEngineSite` Write slot 3, or simply the WAV file. The engine output format is 16 kHz mono 16-bit
   ([V] via SAPI; the WAV matches render.ps1).

### 3.5 Probe usage
```
harness\build_probe.bat
ziraprobe.exe "text" out.wav [token-path]      (default token = David Desktop = OneCore David)
```
It prints the handler order, the predictor vtables, utt+0x2c0, segment domains before and after the adapter,
stream Begin/End with step counts, and the full feature matrix.
