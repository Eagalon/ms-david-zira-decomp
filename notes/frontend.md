# Microsoft David / Zira (OneCore, en-US): text frontend map

Binaries: `bin\MSTTSEngine_OneCore.dll` (x64, v10.3.21207.0, image base 0x180000000) and `bin\MSTTSLoc_OneCore.dll` (base 0x180000000; addresses in it are written `loc!`).
Data: `C:\Windows\Speech_OneCore\Engines\TTS\en-US\MSTTSLocEnUS.dat` (9,804,832 bytes) plus `enUS.*.dat` domain files.
Decompiles are in `decomp\*\_all.c`. The tools are in `tools\`:
- `fn.py [loc] ADDR | -l LINE | -w ADDR`: decompile by address, by line, or find the function that contains an address.
- `xref.py`: callers of a function, with their strings.
- `rtti.py [loc] CLASS`: vftable of a class.
- `vtof.py`, `vtsum.py`: which vftable holds a function; vtable slot summaries.
- `calls.py`
- `guidrefs.py`: every GetResource call site, checked against the .dat.
- `locdat.py`: container TOC plus resource parsers and the lexicon decoder.
- `fe_tables.py`: the sentsep, suffix, quote, parallel-structure and polyphony-CRF tables.

Harness: `harness\ziratap.c`, built with `build_ziratap.bat` into `ziratap.exe`.
**guess** marks anything not verified by parsing the real files or by running the code.

## 0. Read this first

1. **Zira Desktop runs on a different engine.** The SAPI5 token "Microsoft Zira Desktop" loads the old `System32\speech\engines\tts\MSTTSEngine.dll` (v11.0) with `C:\Windows\Speech\Engines\TTS\en-US\M1033ZIR.*` and a *different* `MSTTSLocEnUS.dat` (9,258,072 bytes). So `ref\zira_*.wav` and `render.ps1 "Microsoft Zira Desktop"` do **not** exercise the engine mapped here. "Microsoft David Desktop" does use `MSTTSEngine_OneCore.dll` with the Speech_OneCore data. For OneCore Zira references use `ziratap.exe zira @text out.wav` (for David it is bit-identical to render.ps1). Two forks confirmed this independently from the registry.
2. **The frontend is mostly rules and lexicon for these voices.** No CRF or RNN prosody model ships for David or Zira. The prosody models are looked up as `<VoicePath>.BRK/.BR2/.BR3/.EMP/.EMC/.TON/.ACL`, and only Eva has them. The CRF sentence separator and sentence-type detector, the RNN POS tagger, RNN LTS and RNN polyphony are also absent from the en-US data, so every one of these falls back.
   The trained models that do run:
   - the lexicon (Huffman-coded)
   - the CART LTS
   - the classic POS tagger
   - 13 homograph CRFs
   - the TN/NE transducer network (HFST/pmatch-style) and the FST matcher
3. **Output is deterministic.** Repeated renders and repeated Speak calls in one process give identical PCM. rand() is used only in the vocoder (srand(0x406) at init). The frontend runs sequentially on the Speak thread.

## Pipeline at a glance (per sentence; CTTSEngine::Speak 0x180028288)

SAPI Speak 0x18008b210 → frag conversion 0x18008b6e0/0x18008bb98 → CTTSEngine::Speak loop: new CTTSUtterance (0x760 bytes) per sentence. The handlers run in order via vt+0x18, with an observer callback at engine+0x578 before and after each one:

| id | handler | Process | role |
|---|---|---|---|
| 0x40000 | CTextProcessor | 0x1800b5110 → 0x18005c794 | sentence split (rule-based CSentSepImpl, SENTSEP lists), CSentenceAnalyzer::Analyze 0x180065980: frag walk + NE/whitespace word breaking 0x1800c51cc, locale TA hook, POS 0x18006603c, TN 0x180018ed4 (CTextNormalizer::Normalize 0x1800c3e50, transducer "TRANSDUCER_en-US"), CPronouncer::Pronounce 0x1800479e0 (lexicon → OOV/compound/CEnMorph → CART LTS → CPolyphony rules → homograph CRFs), then sent/punc detector, quote pairing, parallel structures |
| 0x80000 | CLinguisticProsodyTagger | 0x180060010 | Break → Emphasis → BoundaryTone → PitchAccent predictors (rules + model runner; no models for David/Zira), then locale post step (loc handler vt+0x70) |
| 0x100000 | CTTSUnitGenerator | 0x180034b00 | **boundary adapter**: applies SAPI rate/pitch/volume, builds per-phone unit lists, emits SAPI events |
| 0x4000000 | CAcousticProsodyTagger | 0x1800a39f0 → 0x180032dc8 | **backend starts here** (durations/F0 via the voice model, fed by CTTSFeatureExtractionEngine) |
| 0x800000/0x1000000/0x2000000 | lattice / selector / wave generator | | backend |

**The frontend→backend boundary** is the CTTSUtterance/CTTSSentence tree after handler 0x80000, or after 0x100000 once rate/pitch and the unit lists are applied: sentence → (intonation) phrase → prosodic word → word → syllable → phone. There is no label string or fixed-length vector. The voice model lists feature names such as `Phone.PrevPhone.PhoneIdentity`, and the CTTSFeatureExtractionEngine (vt+0x18 = 0x18005bfc0 → 0x180005248 per feature) evaluates each one against the tree. See §4 of the prosody section for layouts and the getter tables. A backend port should take this tree, or a dump of the feature values, as its input.

---

# 1. MSTTSLocEnUS.dat: container and resources

Parser: `tools/locdat.py` (subcommands `toc`, `lex`, `lexdump`, `phones`, `sentsep`, `chartable`, `lts`, `poly`, `misc`, `--file` for the domain files). Everything below was checked against the real file (9,804,832 bytes, 2026-03 build) unless marked **guess**.
Addresses are VAs in MSTTSEngine_OneCore.dll (base 0x180000000). New helper tools: `tools/fn.py` (decompile by address or line), `tools/xref.py` (callers + strings), `tools/rtti.py` (vftable from RTTI), `tools/vtof.py` (which vftable holds a function) and `tools/guidrefs.py` (every GetResource(type,id) call site, checked against the .dat).

## 1.1 Container format (verified)

A chunk is `GUID type; GUID id; u64 size; u8 data[size]`, and the next chunk starts at `(data+size+7)&~7`. The header is 0x28 bytes.

```
0x000 ROOT      099f9814-92ab-4e98-a8b3-82867d871cc5  (id 0)  size = file-0x28
  0x028 HEADER  3e13f66a-63c0-43ee-8957-a4a0f8a111c3
    0x050 33c56624-a468-4c7f-a706-d506127b2312  data {u32 ver=1, u32 0, u32 LCID=0x409, u32 0}
  0x088 RESLIST e5f704bc-f648-41d1-86f2-b0fe5c0fbfff  -> flat list of 23 resources (depth 2)
```

The loader lives in an engine class that holds the resource manager (engine object +0x368 = `IResMgr*`).
- `FUN_180134f80(this, path)`: CreateFileW, then `FUN_18005d5f8`, which calls CreateFileMapping and MapViewOfFileEx (FILE_MAP_COPY, i.e. read-only). The whole file stays mapped. Resources are **pointers into the mapping, not copies**.
- `FUN_180135170`: checks the ROOT, HEADER and 33c56624 GUIDs (33c56624 must have size 0x10) and calls vt+0x50 (the header or LCID check).
- `FUN_1801350c0`: walks the RESLIST and pushes each `{type,id,size,ptr}` into the index (`FUN_180134d9c`). `FUN_180062cc0` parses one chunk header.
- `FUN_180135170` also sees the GUID globals at 0x18018bce8 (ROOT), 0x18018bd18 (HEADER), 0x18018bd08 (33c56624) and 0x18018bcf8 (RESLIST).

**Resource-manager interface.** The data path comes from `%s%s\MSTTSLoc%s.dat` / `%sLocaleHandler\MSTTSLoc%s.dat` (FUN at line 120286).
- vt+0x00 `Get(type,id,&ptr,&size,&fileObj)`: fileObj carries the data path at +8. It is used for the cache keys.
- vt+0x08 `Get(type,id,&ptr,&size)`.
- vt+0x10 returns the locale name string. It is the `%s` in the cache keys.
- vt+0x18 returns the "update" name.
- vt+0x20 `IsUpdate(type,id,&flag)`: selects the `UPDATE_*` cache key.
- HRESULTs: 0x8004801A = resource not present (every consumer treats it as "feature off / fall back"). 0x80048018 = wrong version id; the consumer then retries older id GUIDs, e.g. the word breaker tries 4 ids.

**Cache keys (confirmed).** Loaded models live in a **process-global, ref-counted cache** under the critical section 0x1801c0dc0. The lookup is `FUN_1800264ac` and the insert is `FUN_180026564`.
- Keys: `LEX@<datapath>` (FUN_1800c0ec0), `LangDataFstNE@<datapath>` (FUN_1800c426c), `SENTSEP_<loc>`, `UPDATE_SENTSEP_<loc>`, `WORDBREAKER_<loc>`, `UPDATE_WORDBREAKER_<loc>`, `TRANSDUCER_<loc>`, `LTS_<loc>`, `LTS_<loc>_<i>`, `RNNLTS_<loc>`, `COMPOUNDPRON_<loc>`, `RNN_DECODER_<loc>`, `TRANSDUCER_POSCONVERTER_<loc>`, `POS_TAGGER[@..]`, `TRANSDUCERALPHABETMAP[_<loc>]`, `address word breaker_<loc>`.
- The key only decides whether two engine instances share the read-only object. It has no effect on output.

## 1.2 Resource table (en-US)

"Off" is the data offset of the payload. The consumer is the function that calls GetResource. For the functions that use the data, see the per-resource notes.

| # | off | size | type GUID | id GUID | what | consumer (loader) |
|---|---|---|---|---|---|---|
| 1 | 0xd8 | 0xeb6 | 00a2359e | 4d4d5073 ("sPMM") | pattern-machine rules for rule-based sentence/punctuation detection (strings like "how's", "prep conj adv") | FUN_1800b7d70 -> `CRuleSentAndPuncDetector` (FUN_1800b7ca8); also FUN_180059d90 (layout: `+0x10` = offset of the second part) |
| 2 | 0xfb8 | 0x9e72 | 0cb71848 | 827032e3 | POS tagger rules (`CPosTagger`) | FUN_1800c1f48 -> FUN_1800458cc |
| 3 | 0xae58 | 0xdcb0 | 19a6569a | ea8d0701 | transducer network: compound-word pronunciation (`COMPOUNDPRON_%ls`) | FUN_1800ccd00 / FUN_1800cce14 (CWordPronouncer) |
| 4 | 0x18b30 | 0x960 | 29a5584b | 153f1b64 | **phone set** | FUN_18005df80 (phone-converter setup) |
| 5 | 0x194b8 | 0x55cc | 388b0327 | ea8d0701 | transducer network: phone converter ("OverallToplevel", "Native", "es-MX"; mixlingual) | FUN_18005df80 -> FUN_180068268 |
| 6 | 0x1eab0 | 0x414 | 5554ba64 | 09397c04 | noun/adjective suffix lists | FUN_1800b80dc (sentence/punc detector init FUN_18005d950) |
| 7 | 0x1eef0 | 0x7aff | 629aa5c4 | 9756c4e5 | word-breaker data (`CWordBreakerInfo`) | FUN_1800c4780 (CWhiteSpaceBreaker) -> FUN_1800cbe0c; also FUN_180076454 |
| 8 | 0x26a18 | 0x2238e | 6f4ac239 | c5693920 | foreign-language LTS set (one entry: es-MX 0x080a) | FUN_1800cd1d4 (CWordPronouncer) |
| 9 | 0x48dd0 | 0x24c | 78f6770d | 7ab40d39 | syllabification: legal onset clusters (`CSyllableSeg`) | FUN_1800c3060 (CPronouncer) |
| 10 | 0x49048 | 0x345b04 | 7bd71f46 | f9a99c02 | **main lexicon** | FUN_1800c1040 -> FUN_1800c0ec0 -> CTTSLexiconWrapper -> FUN_1800c1110 -> FUN_1800491b0/180049260 |
| 11 | 0x38eb78 | 0x333044 | 7d5841ab | ea8d0701 | transducer network: **text normalization** (TN grammar) | FUN_1800c3c90 (`CTextNormalizer` vt+8) and FUN_1800c4420 (`CNEDetector`) |
| 12 | 0x6c1be8 | 0x4ac | 9abda282 | fedc5fe9 | NUS domain table (46 x 26 B), used by the backend/NUS | FUN_180077090 (from FUN_180055a20 "EnabledNE", "NuuListRefine") |
| 13 | 0x6c20c0 | 0x74 | 9d9e8526 | 0 | 7 x 16 B phone-class groups (M/N/NG, W/Y, L/R ...). **No reference found** in either DLL (unused?) | none |
| 14 | 0x6c2160 | 0xf32fc | ac4aefcf | d18325ec | **letter-to-sound CART** (`CLTSLexiconCART`) | FUN_1800c9890 -> FUN_1800c9c34 (`LTS_%s`) -> FUN_18015fcb8 -> FUN_180160684 |
| 15 | 0x7b5488 | 0x28 | b54490e3 | e4c81da4 | quote-pair table | FUN_1800b83f4 |
| 16 | 0x7b54d8 | 0xd3931 | bfc4309d | d2343132 | NE FST (`CFstMatcher`, BingNlPlatform::Fst), key LangDataFstNE | FUN_1800c4420 -> FUN_1800c426c -> FUN_1800c415c |
| 17 | 0x888e38 | 0x48314 | d49f77b9 | 3e135d7f | 13 polyphony (homograph) CRF models | FUN_18002b96c (`CCRFPolyphonyTaggerList`, from CPolyphonyHandler FUN_180064400) |
| 18 | 0x8d1178 | 0xc0 | d8951565 | 52a33b0b | parallel-structure detector config (0x2c-byte recs: and/or/nor) | FUN_1800b8f08 (`CParallelStructDetector`) |
| 19 | 0x8d1260 | 0xb322 | e67ab014 | 1df28780 | sentence-separator word lists | FUN_18007b43c -> FUN_180047748 |
| 20 | 0x8dc5b0 | 0x332b0 | e849e61b | 4a3c699e | `CPolyphony` rule/context-pronunciation data | FUN_1800c3060 -> FUN_1800c2524 (object 0x1950 B); FUN_180026a50 |
| 21 | 0x90f888 | 0x46a24 | efdc81f5 | 18be7e07 | "Language Identifier" model (header `u16 LCID=0x409, u16 n=3, ...`) **guess: mixlingual LID** | FUN_1800360f0 -> FUN_1800e0a70 |
| 22 | 0x9562d8 | 0x38f0 | f6e4f50a | 80b9a5a3 | **char table** (symbol names) | FUN_1800360f0 -> FUN_180045a6c (falls back to id 0x180189180 on version mismatch) |
| 23 | 0x959bf0 | 0x30 | f81fd1d1 | ed1348b2 | POS-id list (u32 n=22, u16 ids) hung on the lexicon object | FUN_1800c19dc |

**Requested but absent in en-US.** The consumer silently falls back when these are missing (from `tools/guidrefs.py`):
- 9b4ece4f / 0d5c0d43: CRF sentence separator (`CCRFSentSepHandler` FUN_1800c073c). Falls back to the rule lists (#19).
- 3292d97f / 0d5c0d43 and 1801861b0 / 180188900: CRF sentence-type detector (FUN_1800b7d70).
- 3235b923 (FUN_1800c1f48, alternate tagger) and 180186210 / 1801891a8: RNN/CRF POS tagger variant. Falls back to `CPosTagger` rules.
- 46ee52ba / 3b273052: RNN LTS. Absent in the main .dat, **present in enUS.Name.dat**.
- 7758aa3c (FUN_18011b598), b15e4e27, 6de01f86, 03110205, cea1be6f (acronym CRF; present in enUS.Address.dat).
- The CPronouncer's CSyllableSeg type 180186190 **is** present (#9).

**Loc DLL.** MSTTSLoc_OneCore.dll has no embedded models (.rdata is 166 KB and has no RES blobs).
- Its own GetResource calls use 8 GUIDs: cdc85643, 99cc36f3, b85c9da5 (types) and 9e4e57a5, 1bdfa8dc, b1fe7ab5, 62a5796d (ids). They are in FUN_1800155a8 (CBoundaryPronChange), FUN_18002ae34, FUN_18002c54c (CVocabTrie/CTemplateTrie) and FUN_18002d63c.
- **None of these GUIDs occurs in any en-US file** (.dat, domain .dat, APM, BEP, NUS). So for en-US those Loc features are off.
- The voice APM files are the acoustic format ("APM " magic) and contain no text-model strings.
- Where the en-US break/tone/accent models come from is for fork C (possibly rules or defaults when absent).

## 1.3 Main lexicon (7bd71f46): format and lookup (verified, decodes real words)

The lexicon is created as CTTSLexiconWrapper (vtable 0x18016d678, cache key `LEX@path`). The inner lexicon object is 0xe8 bytes (vtable 0x180173550). `FUN_1800492f0` validates the header and `FUN_180049550` sets up the pointers.

Header, as offsets from the resource start:
```
+00 GUID b3884aee-29dc-4038-8c6c-6aab8ba3724c (format; checked vs 0x180180fe0)   +10..1f 0
+20 LCID 0x409      +24 total size (must equal resource size)
+28 185418 (nEntries)   +2c/+30 202398  +34 209324  +38 676   (counts, meaning not needed for lookup)
+3c hash table offset 0x3b24   +40 nSlots 278128   +44 bits/slot 25
+48/+4c codec0 (word chars, 1360 syms)     +50/+54 codec1 (phone ids, 45 syms)
+58/+5c codec2 (3 syms: 0x6000,0xFFFF,0xFFFE) +60/+64 codec3 (attr-set ids 0..24)
+68/+6c codec4 (chars of attribute names)   +70/+74 u32 attrset_start[24]
+78/+7c 63 attr-def records x 10 B {u16 id, u16 isValue, u16 parent, u16 nameBitOff, u16 0}
+80/+84 u16 attr-id lists (0-terminated)    +88/+8c u32 bitstream for codec4
+90/+94 MAIN BITSTREAM (u32 words, 2.5 MB)  +98 total bits of attribute names (2227)
```

**Huffman codec (CLwHuffCodec / CLwHuffDecoder).** Setup is `FUN_18007a214` and the header check is `FUN_180144198`. Decoding is inline in FUN_180035180 and FUN_180035c24, and FUN_180044304 does single-symbol decodes.
- Table layout: `u32 nSym, u32 nNodes (=2n-1), u32 root (=2n-2); u16 sym[nSym]; u32 node[nNodes]`. Each node is `{u16 child0, u16 child1}`.
- Decoding starts at `root`. Read one bit from the u32 word stream **LSB-first** (`word[p>>5] >> (p&31) & 1`). Bit 0 takes child0 and bit 1 takes child1.
- A node whose child0 is 0xFFFF is a leaf. Its symbol is `sym[node]`, i.e. the leaves are nodes 0..n-1.
- Strings are 0-terminated.

**Lookup** (`FUN_180034f50`): copy the word (at most 128 chars) and lowercase it (CharLowerW; LCMapString for tr/az). Then `FUN_180035180` runs:
- Hash: `h=c0; for each next char c (prev p): h += (c << (p&31)) + (p << (c&31)); slot = (h*0xFFFF mod 2^32) % nSlots`.
- Read the 25-bit slot, packed **MSB-first** in bytes. The all-ones value (0x1FFFFFF) means the word is not present.
- The slot value is a bit offset into the main bitstream. The entry starts with its own key, which is Huffman-coded with codec0 and 0-terminated.
- The key is compared with CompareStringW(LCID, NORM_IGNORECASE). On a mismatch, probe linearly to slot+1 (wrapping).
- On a match, the returned position is the bit just after the key.

**Entry decode** (`FUN_180044304`) is a sequence of records. Each record starts with a 4-bit header `h`: type = `h&7`, and `h&8` marks the last record.
- type 1: new pronunciation, a 0-terminated codec1 string of phone ids (up to 0x181). Created via FUN_1800c81a8 / FUN_18005bd50.
- type 2: one codec2 symbol, stored at pron+0x50. It is always 0x6000 in the samples. **Meaning unknown; guess: pron flags/source**.
- type 3: 0-terminated codec3 list of attribute-set indices k (1-based). `attrset_start[k-1]` indexes the u16 id list, and each id names an attribute (FUN_180035ab0 / FUN_1800639a0, cached per set).
- The attribute names (decoded from codec4) form a POS/feature tree: `POS > NOM/VER/ADJ/DET/NUM/AUX/PRO/ADV/CON/ADP/INT/PAR/SYM/OTH/unknown`, with `*_TYPE` children (noun, verb, verbing, verbpastp, adj, det, whdet, num, vaux, pron, whpron, adv, whadv, conj, prep, interjection, particle, symbol, listitem, possend, contr), plus F_GENDER, F_CASE and F_NUMBER. The 24 attribute sets are e.g. {NOM noun}, {VER verbpastp}, {ADJ adj}.
- Phone ids map through the phone set (#4). Syllable boundaries are `-` (id 2). Stress comes **after the vowel** as `1` (primary) or `2` (secondary) (ids 5/6).

Real output (`locdat.py lex ...`):
```
hello   /h eh - l ow 1/            [INT interjection],[NOM noun]
read    /r iy 1 d/ [VER verb],[NOM noun]      /r eh 1 d/ [VER verb],[VER verbpastp]
record  /r eh 1 - k ax r d/ [NOM noun]        /r ih - k ao 1 r d/ [VER verb]
the     /dh ax 1/ [DET det]                   /dh ih 1/ [DET det]
live    /l ih 1 v/ [VER verb],[NOM noun]      /l ay 1 v/ [ADJ adj]
Microsoft /m ay 1 - k r ax - s ao 2 f t/ [NOM noun];   zira /z iy 1 - r ax/
```

**Phone set (#4, verified).** Layout: `u32 recSize=0x34, u32 n=46`, then records `{u16 id; wchar name[23]; u32 flags}`.
- Ids: 1 `&`, 2 `-`, 3 `-SIL-`, 4 `-SP-`, 5 `1`, 6 `2`.
- 7-13: AA AE AH AO AW AX AY. 14-23: B CH D DH EH ER EY F G H. 24: IH. 26-47: IY JH K L M N NG OW OY P R S SH T TH UH UW V W Y Z ZH. (There is no id 25.)
- Flags 0x0000000d = vowel. Consonant flags encode manner and place bits (e.g. B 0x82a, M 0x90e). **Guess**: bit 0x2 = consonant, 0x8 = voiced, 0x4 = sonorant.

Other lexicons, not in this file:
- The domain .dat files each carry a small 7bd71f46 lexicon in the same format (e.g. Name.dat 0x4ee0 B).
- `Lexicon.hot.lxa` (FUN_18005b1fc near L158049) is an optional hot-fix lexicon.
- There are also CPLSLexiconCache (SSML PLS), CSAPIUserAppLexicon (SAPI user/app lexicon) and CTTSCustomLexicon. These are runtime, not data.

## 1.4 Letter-to-sound (verified layout)

**Which LTS en-US uses.** `FUN_1800c9890` first asks for the RNN LTS (type 0x1801861d0 = 46ee52ba, vt+0x00 call). For the main en-US .dat the answer is 0x8004801A, so it falls back to **CART LTS ac4aefcf** (`FUN_1800c9c34`, key `LTS_en-US`). The RNN LTS (`CRNNDecoder`, FUN_1800c9d14 -> FUN_1801601c0 -> FUN_180114a6c) is used only by the **Name domain** (enUS.Name.dat).

**CART LTS layout** (`FUN_180160684`: parts A,B = FUN_180160854, C = FUN_180044ad8, D = FUN_180160738, E = FUN_1800448f8). The parse lands exactly on the resource end:
```
A letters  : u32 secSize, u32 n=29, u32 off[n] (wchar units), u32 poolBytes, wchar pool
             -> '@' ' - a..z'
B outputs  : same layout, n=260 -> '@','','','','aa','aa1','aa1 l',... (multi-phone strings with stress digits)
C matrices : u32 n=44,m=1, u32[n*m]; u32 n=297,m=9, u32[n*m]  (bitsets; guess: phone/letter class questions)
D          : u32 secSize, u32 n=874, u16[n] (values 512..; guess: question -> feature mapping)
E trees    : for each letter 1..28: u32 secSize, u32 nNodes, u32 node[nNodes], u32 nLeafBytes, u8 leaf[],
             u32 nQBytes, u8 q[]  (pad to 4). e.g. 'a' 20001 nodes, 'e' 20001, 'c' 741.
```
The node, leaf and question bit encodings are **not decoded yet** (next step: the CLTSLexiconCART predict function, reached via the object created in FUN_1800c8e88).

**Foreign LTS (#8, es-MX).** Layout: `u8 n=1; u16 {lcid 0x080a, 0x080a}[n]; u32 ltsOff[n]; u32 listOff[n]`. The CART at +0xe uses the same format as above (33 letters). At 0x6ca there is a phone-string list ("a j-", "a1- jj", ...), loaded with FUN_180098c58. Key `LTS_<loc>_<i>`. Use: Spanish words and names, together with the #5 phone converter.

## 1.5 Other resources (layouts)

**Sentence separator lists (#19, verified).** `u32 n=12; u32 count[12]; u32 strOff[sum] (bytes, relative to the pool); wchar pool`. The loader FUN_180047748 builds pointer arrays into the object:

| list | count | object field | examples |
|---|---|---|---|
| 0 | 2381 | +0x68 | abbreviations "Aa." "Adj." |
| 1 | 61 | +0x78 | Bible books "Chron." |
| 2 | 6 | +0x48 | coordinating conjunctions and/but/either/neither/nor/or |
| 3 | 42 | +0x98 | ambiguous month/day abbreviations "Apr." "Is." "Jr." |
| 4 | 173 | +0x28 | sentence-initial capitalised words "About" "According" |
| 5 | 0 | +0x38 | (empty) |
| 6 | 10 | +0x58 | digit words zero..nine |
| 7 | 7 | +0x88 | numeric prefixes "fig." "no." "sect." |
| 8 | 4 | +0xb8 | "c" "r" "sm" "tm" (symbols such as (c)) |
| 9 | 280 | +0xd8 | emoticons |
| 10 | 90 | +0xa8 | titles "Adm." "Capt." |
| 11 | 4 | +0xc8 | suffixes ed/ing/n't/s |

**Char table (#22).** Layout: `u32 n=363; {u32 codepoint, u32 flags, u32 name1Off, u32 name2Off}[n]; wchar pool`. Examples: U+0021 "exclamation point", U+0022 "double quotes", U+0028 "opening parenthesis".

**Quote pairs (#15).** Layout: `u32 LCID, u32 n=4, {u16 open, u16 close, u32 typographic}`: `"` `"`, `'` `'`, U+2018/U+2019, U+201C/U+201D.

**Suffixes (#6).** Layout: `u32 LCID, u32 recSize=20, u32 n=27, wchar[10] recs` for noun suffixes (ance ancy ... ee), then `u32 n=15` more recs for adjective suffixes (able less like some stic cal ese est ful ile ing ish ive ous ed).

**Syllabification (#9).** Layout: `u32 n=73; {u16 p1,p2,p3,0}[n]`. These are the legal onset clusters in phone ids (S K L, S K R, S K W, S K Y, S P ...). **Guess**: maximum-onset syllabification for LTS output (lexicon prons already carry `-`).

**POS tagger (#2).** The data is two tables of 12-byte records `{u8 kind, u8 table(1|2), u16 a, u32 b, u32 strOff}`, each ended by a 12-byte zero sentinel (0x1801809a8). They are followed by a string pool at +0x4dac.
- Table 1: 219 "lexical" rules. Table 2: 1436 "contextual" rules.
- **Guess**: a transformation-based (Brill) tagger. The kind byte is the rule template, a/b are from/to POS ids, and strOff is the word or suffix.

**Polyphony CRF (#17, verified header).** Layout: `u32 namePoolOff (0x48268), u32 modelsBase (0x74), u32 n=13, u32 modelOff[n], u32 nameOff[n]`.
- Words: ADDRESS CLOSE COMPLEX CONFLICT CONTRACT LEAD LIVE OBJECT PRESENT READ SUBJECT UPS USE.
- Each model starts with a 16-byte GUID, then `u32, u32 size, u32 LCID, "CRF\0", u32 100, ...`, e.g. nLabels=2 and nTemplates=12 for ADDRESS.
- It contains CRF++-style feature templates such as `U00:Token.PrevToken.PrevToken.PrevToken.CaseInsensitiveText`, and label pronunciations such as `AE%1%-%D%R%EH%S` / `AX%-%D%R%EH%1%S`.
- The CRF model internals (the CCRFModelManager / CCRFDecoderCore format) are **not mapped** here.

**Transducer networks (#3, #5, #11).** All three share id ea8d0701 (format id) and start with magic GUID 8c339078-fb86-40eb-84de-7fb7add37406, checked at 0x18018bdc8 in FUN_18013f810. Reader: FUN_18013fa64 -> FUN_1800302b8 (sequential u16/u32 header fields at obj+0x38..+0xd2), wrapped by FUN_180066224 / FUN_180135b48 ("TransducerNetwork", pmatch-style alphabet and delimiters).
- Header after the magic: `u32,u32, u16 nSym, u16, u32 x8 ...`. Values: TN 7d5841ab = (1,1, 4172 syms, 0, 6879, 39215, 31506, 32825, 1, 11, 11, ...). Phone converter 388b0327 = (0,0,3,0,3,161,238,407,...).
- Field meanings (states/arcs/...) are a **guess**; the TN internals are fork B's.

**NE FST (#16).** BingNlPlatform `CFstMatcher` format. The header contains an ASCII build stamp "June 07, 2013 05:50:19 GMT Copyright (c) 2013". It is used by CNEDetector.

**Word breaker (#7).** Layout: `u32 n=89; u32 tbl[n] (0..88); ...` The rest (a trie or rules) is **not mapped**. The version-id chain lives at 0x180189558 / 548 / 568 / 278.

**Domain files** (`enUS.<domain>.dat`, the INI [Domain] list) use the same container. `locdat.py --file` works on them:
- Address: 00a2359e, 7bd71f46 (lexicon), cea1be6f (acronym CRF list), e849e61b.
- CompanyName, Computer: lexicon only.
- Media, Message: 00a2359e, lexicon, e849e61b (Message holds the emoji pronunciations such as "k ih 1 s - s m ay 1 - l iy 2").
- Name: 00a2359e, **46ee52ba RNN LTS (1.48 MB)**, lexicon, e849e61b.

## 1.6 Open items
- Decode the CART node/leaf/question bits and the CRF model body. The Huffman lexicon is fully decodable now.
- efdc81f5 (language identifier) internals.
- The meaning of 9d9e8526, which has no reference.

---

## 2a. Text processing: SPVTEXTFRAG to pronounced words (CTextProcessor)

Source is static analysis of `MSTTSEngine_OneCore.dll` (md5 d7d84e2b…, same as the copy in System32) and
`MSTTSLoc_OneCore.dll` (md5 5d124efa…). Addresses are VAs (image base 0x180000000 in both DLLs).
**guess** marks anything I did not verify. "Absent" means that the (type, id) GUID pair the code asks for does not
occur anywhere in `MSTTSLocEnUS.dat` or in the en-US voice/domain files. The resource manager then returns
0x8004801A (not found) and the component is skipped. I checked this by byte search, not at runtime.

Helper tools written for this section (all in `zira\tools`):
- `fn.py [loc] ADDR | -l LINE | -w ADDR` prints a decompiled function, or the function that contains a line or address.
- `xref.py [loc] FUN`: direct callers, plus the strings and vftables used in each caller.
- `rtti.py [loc] CLASS [n]` gives the vftable address and slots, found from the MSVC x64 RTTI.
- `vtof.py [loc] FUN`: which class vftable slot holds a function. The class guess is only right when the COL sits directly in front of the vftable.
- `calls.py ADDR…`: a one-screen outline (calls, vtable calls, strings) of each function.
- `guidrefs.py` lists every `(&typeGUID,&idGUID)` resource request in the engine and says whether each is present in the .dat.
- `fe_tables.py` dumps the small frontend tables: SENTSEP lists, suffix tables, quote pairs, the parallel-structure list and the polyphony CRF bank.

### Object graph (per engine instance)

```
CTextProcessor (0x58 B, ctor 1800b4888, vftables 180175d00 / 180175d38)
  +0x10 CTTSEngine*            +0x18 CSentenceEnumerator (0x88 B, ctor 1800b5cbc, vt 180175d58)
  +0x20 CSentenceAnalyzer (0x598 B, ctor 1800ba0dc via 1800798d0, vt 1801760a8)
  +0x28 CSentAndPuncDetector (vt 180175fb8)   +0x30 suffix tables (5554ba64)
  +0x38 quote-pair matcher (b54490e3)           +0x40 CParallelStructDetector (d8951565)
  +0x48 "enumerator initialised" flag           +0x50 event sink (vt+0 called with 0x40004,0/1)
CTextProcessor::Init (vt+0 = 18005d950) -> 180054a5c (makes analyzer + enumerator), 1800b7d70, 1800b80dc, 1800b83f4, 1800b8f08
```

CSentenceAnalyzer, the object that does the real work (`this` = A). The offsets are byte offsets:

| off | object | created in | en-US |
|---|---|---|---|
| 0x10 | u16 LangID (0x409) | 1800360f0 | |
| 0x20 | current CTTSSentence* | Analyze | |
| 0x28.. | 500-wchar sentence text buffer (filled by the locale TA vt+0x20) | c51cc | |
| 0x420 | word list (linked list of CTTSWord*; node = {next, ?, word}) | | |
| 0x488 | the list passed to the locale TA hooks (A+0x488) | | |
| 0x4b8 | word breaker = **CWhiteSpaceBreaker** (vt 180176410). The ENU locale TA returns E_NOTIMPL for its own breaker (loc 1800151f0) | 1800360f0 | active |
| 0x4c0 | **CPOSTaggerImpl** (vt 180176280) wrapping CPosTagger | 1800c1c68/1800c1f48 | active |
| 0x4c8 | **CPronouncer** (vt 180176298) | 1800c280c + vt+8 1800c3060 | active |
| 0x4d0 | **CNEDetector** (vt 18016f0c8) | vt+0x10 1800c4420 | active |
| 0x4d8 | person-name NER from the file `NERLessEdited.<lang>.mrr` (1800bc1e0/18002b424/18007924c) | | absent (no .mrr file on disk) |
| 0x4e0 | **CTextNormalizer** (vt 1801763b0) | vt+0x10 1800c3c90 | active |
| 0x4e8 | int TNScope: 1 = FullContext, 0 = LimitedContext | 180056808 | 1 |
| 0x4ec | int TNEnhancedSayAsSupport | 180056808 | 1 |
| 0x4f0/0x4f2 | wchar decimal and thousand separators ('.' ',') | 180056808 | |
| 0x4f8 | **CAcronymHandler** (vt 1801763a0). Its CCRFAcronymTaggerList needs cea1be6f/0fbd602c | 18006838c | handler active; the CRF acronym model is absent from the main .dat but present in enUS.Address.dat |
| 0x500 | CCharTable (f6e4f50a/80b9a5a3; fallback id a28a86cd) | 180045a6c | active |
| 0x538 | resource manager (engine+0x368) | | |
| 0x540 | voice data manager (engine+0x580). Provides `VOICE_LEX` | 1800bca58 | voice-dependent |
| 0x548 | "Language Identifier" (efdc81f5/18be7e07, chunk 0x90f860, parsed by 1800e0a70) | 1800360f0 | loaded. It is for mixed-language text (**guess**) |
| 0x550 | CTTSNgramTrieBreaker (03110205/d29ffcb7) | 1800bc9c0 | absent, so deleted |
| 0x558 | CTTSEngine* | | |
| 0x568 | CEnMorph morph lexicon, supplied by the locale TA vt+0x10 (loc 1800194f0) | | active |
| 0x570 | VOICE_LEX lexicon (priority 0x8000) | 1800bca58 | voice-dependent |
| 0x578 | `Lexicon.hot.lxa` hot-fix lexicon read from the data dir (priority 0x1000) | 1800bcc94 | no such file on disk, so inactive |
| 0x580 | CTTSContainerLexicon (lexicon list; vt 180176258, lookup = 1800c1350) | 1800c12b0 | |
| 0x588 | CSAPIUserAppLexicon (SAPI user and app lexicons) | 1800360f0 tail, 18015251c | active when the engine site gives a lexicon |
| 0x590 | Locale text analyzer from the Loc DLL = **CLocaleTextAnalyzerENU** (vt loc 18007b7e8, ctor loc 180019460). It is obtained through the locale handler (engine+0x350) vt+0x80 | | active |

The main lexicon is registered in 1800360f0 by `FUN_1800c1040(resmgr, L"LEX", 0x1000, &A+0x560)`. Its resource is 7bd71f46/f9a99c02 (the 3.4 MB chunk at 0x49020). The lexicon file format belongs to fork A.
The flags passed to Init decide what is created: 4 = POS tagger, 0x12 = char table, 2 = pronouncer, 8 = acronym, NE and TN.
FUN_180054a5c passes 0xFFFFFFFF, so everything is created. The one exception is 2 (pronouncer only), used when the domain is "general" and engine+0x4a4 is set.

The locale handler comes from `GetLocaleHandler` (loc 1800141f0). For LCID 0x409 it calls loc 1800199e0, which builds **CTTSLocaleHandlerENU** (0x68 B, vt loc 18007b8a0). The engine uses these slots:
- +0x80 creates the CLocaleTextAnalyzerENU.
- +0xb0 is the sentence-separator override. It returns E_NOTIMPL (loc 180010ac0), so the engine uses its own separator.
- +0x30 is loc 1800176c0 and +0x48 is loc 180017730. Both act on the utterance (fork C / D territory).

CLocaleTextAnalyzerENU (0xb8 B) Init (loc 180019660) builds **CCompoundWordBreakerEnUS** at +0xb0 (init loc 18003e890 with 0x409). Its vtable slots used by the engine:

| slot | loc fn | role |
|---|---|---|
| +0x00 | 180019660 | Init |
| +0x08 | 1800151f0 | GetWordBreaker, returns E_NOTIMPL (engine falls back to CWhiteSpaceBreaker) |
| +0x10 | 1800194f0 | GetMorphLexicon, creates **CEnMorph** (loc 18005c5c4/18005c964; tables loc 1800a8630 and 1800a7430) |
| +0x20 | 18000be20 | copies the sentence text into A+0x28 (max 0x1f5 chars) **guess** |
| +0x28 | 18000a1d0 | OOV splitter. Handles `sp:email`/`sp:webUrl`/`sp:filePath` with CEmailWordBreaker, `sp:mixedAcronymWord`, and runs the compound breaker (CCompoundWordBreakerEnUS) on other OOV words. Called from CPronouncer 180047eac (`vt+0x28(word, buf, 0x180)`) |
| +0x50 | 180018630 -> 180028730 | post-word-break hook. Handles tokens that are exactly `*` (asterisk emphasis/markers) **guess** |
| +0x58 / +0x60 / +0x88 | 1800157a0 | no-op hooks (return 0) |
| +0x68 | 1800185f0 | "is not all lowercase a-z" test |
| +0x78 | 180010910 | "should not split": 2 fixed strings, the sp:datetime-type categories (loc 181488 table), or the token contains '.' |
| +0x80 | 180019980 | checks two word lists (loc 180081480/180081478) |
| +0x98 | 180017a40 | per-language lexicon lookup through table +0x80 and CEnMorph (+0x98 vt+0xf0) **guess** |

### Per-speak / per-sentence flow

`CTextProcessor::Process` = **1800b5110**. It traces "CTextProcessor::Process" and calls **18005c794** in a loop until it gets a sentence that is not empty.

**18005c794** (one sentence):
1. On the first call it initialises the enumerator from the fragment list: `enum->vt+0x10(frags)` (frags come from engine vt+0x60).
   With skip (SPVES_SKIP) it moves with `enum->vt+0x20` (next) or `enum->vt+0x18` (prev) until the skip count is used up.
2. **180063378** gets the next sentence. `enum->vt+0x18` returns a new CTTSSentence (S_FALSE = end). The analyzer then runs `analyzer->vt+0x10` = **180065980 Analyze**.
   Sentences that come out with no words are skipped. At the end it calls 18005c1a0 (attach the sentence to the utterance) and sets sentence+0x2d8 = engine vt+0x50.
3. After analysis, still inside 18005c794, the following run in order:
   - `sentence->vt+0xb0`
   - **CSentAndPuncDetector 1800b7358**: sentence type and punctuation, via CRuleSentAndPuncDetector (+0x18) and 1800b72c4 / 1800c0dd8.
   - Optional "message" domain handling.
   - **18001bf24**: suffix tables, POS guessing for unknown words from their suffix (**guess**).
   - **1800b8608**: quote/bracket pairing.
   - **1800b90a8**: parallel-structure detection (CParallelStruct objects).
   - `sentence->vt+0xa0(fragInfo, engine+0x4a8)`.

**180065980 CSentenceAnalyzer::Analyze(sentence, flag, out)**, in order:

| # | call | stage |
|---|---|---|
| 1 | vt+0x20 = 1800be620 | reset (A+0x20, A+0x418, word list) |
| 2 | **1800c51cc** | walks the fragments of this sentence: tokenisation, NE detection, TN category tagging, word breaking (below) |
| 3 | LTA vt+0x50 (ENU loc 180028730) | locale hook after word breaking |
| 4 | A+0x550 CTTSNgramTrieBreaker 18013267c, then 18002bf08 for each word | n-gram re-breaking and say-as category canonicalisation (`sp:cardinal`→cardinal, `number:digit`, `telephone`→phonenumber, `net:email`→url …). Skipped for en-US because the object is null |
| 5 | **18006603c** | **POS tagging**: A+0x4c0 vt+0 = CPOSTaggerImpl 1800569d0(wordlist, pronouncer, engine+0x4a0==3) |
| 6 | LTA vt+0x58 | no-op for ENU |
| 7 | **180018ed4** | **second-pass TN**: 180079408 (acronyms through A+0x4f8 1800c3940; 180065c34 / 180063dc4), then for every word that has a pending say-as category (word vt+0xc0 != 0): `CTextNormalizer::Normalize` (A+0x4e0 vt+0x18 = 1800c3e50)(text, category, &outList), then 18004b06c replaces the token with the normalized words |
| 8 | LTA vt+0x60 | no-op for ENU |
| 9 | 1800bb3e0 → 180060c48 | per-word check against the lang-data object at engine+0x1f0 (domain/lexicon attribute? **guess**) |
| 10 | **A+0x4c8 vt+0x48 = CPronouncer 1800479e0**, then 1800bc5e0 | **pronunciation** (lexicon, LTS, polyphony, syllabification, below). 1800bc5e0 handles words that still carry an SPVA_Pronounce phone string (1800c6f58) |
| 11 | LTA vt+0x88 | no-op for ENU |
| 12 | 1800bb318 if langdata+0x34c | extra-language (mixlingual) re-pass for each extra language in engine+0x8 list |
| 13 | **1800bd64c** | commit the word list into the CTTSSentence (sentence vt+0x28/+0x80/+0x88, word vt+0x68/+0x210/+0x220) |

### Sentence separation (CSentenceEnumerator)

- The enumerator is set up in CSentenceEnumerator vt+8 = **180028fa0**. It logs "Sentence Breaker".
  The locale handler vt+0xb0 returns E_NOTIMPL. The engine then tries **CCRFSentSepHandler** (1800c073c). That needs the CRF model 9b4ece4f/0d5c0d43 "CRF sentence separator", which is **absent**. The fallback is **CSentSepImpl** (vt 18016d758, made by 1800293d4) with the shared model "SENTSEP_en-US" (loaded by 18007b43c, parsed by 180047748) from resource **e67ab014/1df28780** (chunk 0x8d1238, 0xb322 B).
  Format, verified by `fe_tables.py`: `u32 nLists=12; u32 count[12]; u32 strOff[Σcount]; UTF-16Z pool`. The 12 lists are:
  - 0: 2381 abbreviations "Aa."…
  - 1: Bible books
  - 2: conjunctions
  - 3: ambiguous month/day abbreviations
  - 4: 173 capitalised sentence starters
  - 5: empty
  - 6: number words
  - 7: fig./no./sect.
  - 8: c r sm tm
  - 9: 280 emoticons
  - 10: 90 titles
  - 11: clitic suffixes ed/ing/n't/s
  The first-choice id is resolved through resmgr vt+0x20. "UPDATE_SENTSEP_%s" is used when the update flag is set.
- Fragment walk (enumerator Next 1800b6900/Prev 1800b6980 → **1800624e0**). It builds sentences across fragments of type 0 (Speak), 4 (SpellOut) and 9 (mask 0x211). A sentence is capped at 500 wchar, and fragment types 6/7 force a break.
  For each text piece it calls 1800b610c. That uses enumerator+0x80 (the CRF handler, null for en-US), otherwise enumerator+0x60 = CSentSepImpl vt+8 = **18005d050**(text, len):
  - skip leading whitespace/punct (limit 500);
  - run a hand-written state machine, init 180073fa0 and run **180073970**. States: −1 1801623e0, −2 180064630, −3 180161a1c, −4 180161ff8, −5 18016225c, −6 180161e00, −7 finish 1800686e0;
  - the result is the sentence length. If it is over 500, cut after the last whitespace before char 499;
  - `+0x24` = "hard end" flag, set from the state-machine fields local_58/54.
- CCRFSentTypeDetector (3292d97f/0d5c0d43 "CRF sentence type detector") is **absent**.
  **CRuleSentAndPuncDetector** (1800b7ca8) uses resource **00a2359e/4d4d5073** (chunk 0xb0, 0xeb6 B, id text "sPMM"), which is also loaded by 180059d90. It fills TP+0x28 (**guess**: question/exclamation/statement typing plus punctuation rules).

### Fragment → tokens (1800c51cc)

It walks the engine's own fragment copies (SPVTEXTFRAG-like, owned by fork D). The fields used are: `+0` action, `+0x20` say-as/context ptr (`{category, before, after}`), `+0x68` text, `+0x70` src offset, `+0x74` length and `+0x80` next.
Dispatch on the action:
- 0 / 9 → 1800c4f10 (text). Before that, 1800c769c handles `<context id="name">` (a name lookup through engine+0x580).
- 1 silence → 1800c7838
- 2 pronounce → 1800c6f58
- 3 bookmark → 1800c6d3c
- 4 spell → 1800c7cf0(−1)
- 6/7 → 1800c6e6c
- other → 18006e874 (raw token)
- In spell mode with A+0x508, action 0 → 1800c7cf0(3).

**1800c4f10** (plain text):
- If there is no NE detector or no TN, it just word-breaks and appends: `A+0x4b8 vt+8(text, len, CTTSWordSink, 1)`, then 180071b70.
- If TNEnhancedSayAsSupport is on and the fragment has a say-as, it goes to **1800c5db4**. That has its own handlers for date (1800c5900), time (1800c6510) and cardinal (1800c573c), and otherwise feeds 1800c5620.
- Say-as category: 1800c6aec resolves the context. `TN vt+0x20` (1800c3c50 → network vt+0x38) checks that the category is supported.
- **TNScope=FullContext** (en-US INI) → **1800c6888** on the whole fragment. **LimitedContext** → 18003f5c4, which only sends a ±4-token window around tokens flagged by 18003f810 (digits, symbols, '.', mask 0x300000005f00219 over 0x26..) through 1800c6888.
- `ml:address` is always sent to 1800c6888.

**1800c6888**:
- Optional NER spans from A+0x4d8 (absent).
- Then a loop of **CNEDetector::FindNext** (A+0x4d0 vt+0x18 = **180061910**) over the remaining text:
  - It parses the text with the TN transducer network (180138e18), then refines the result with the **CFstMatcher** from bfc4309d.
  - It returns 0 = entity found, with prefix length and entity length, or 1 = no entity.
  - For each hit: 180070830 handles the text before the entity, and **1800709a8** turns the entity into one token (a CWordBreakingInfo that carries the entity text and its category). Normalization of that token is **deferred** to Analyze step 7.
- **180070830 / 1800c55a8 / 1800c4db8** handle the non-entity text:
  - First they try the active domain's word breaker: `engine+0x580` domain map → domain handler vt+0x40 → breaker vt+8. The domain name comes from 0x180180958, which is "general".
  - Otherwise they use the default CWhiteSpaceBreaker.

### Text normalization (TN)

- **CTextNormalizer** is built by `CTextNormalizer::Init` (vt+0x10 = 1800c3c90), then vt+8 = 1800c3d80. It uses resource **7d5841ab/ea8d0701** (the 3.3 MB chunk at 0x38eb50), shared under the name **"TRANSDUCER_en-US"**, and builds the network object with 180066224 → 180135b48.
  The blob is a compiled HFST-pmatch-style transducer network: "pmatch alphabet", `OverallToplevel`, and rule names such as `function_ignoreSpace`, `sp:cardinal`, `ml:date_mdy`, `sp:datetime`. The same blob feeds CNEDetector (1800c4420).
  The CFstMatcher / BingNlPlatform::Fst reader belongs to the NE refinement blob bfc4309d. That blob's header string is "June 07, 2013 … Copyright (c) 2013 by Microsoft Corp.".
- `Normalize` = **1800c3e50**(text, category, outList):
  1. 180138e18 parses the text into a lattice (the network method at vt+0x50 does the matching).
  2. `network vt+0x10(lattice, 0, 2, category, &path, &len)` picks the best parse for that category. If that path does not cover the whole input, it uses `"sp:default"` instead.
  3. The chosen path is loaded into a **CTextNormMultiResult** (ATL object, 1800b6d6c): vt+0xe8 LangID, vt+0xc0 path, vt+0xb8(1), vt+0x20 result → vt+0x18 BSTR.
  4. The output string is split on ' ' and each word goes through 1800c3b54 into the output list.
     HRESULT 0x80041004 means "no rewrite", so the original text is kept.
- **JScript**: the transducer runtime can generate a JScript program ("function ScriptNode_%d()", "Token_%d_%d.StrIn/RuleName", `$.Parsed`, generator 180140260). It runs that program through `CoCreateInstance(CLSID_JScript f414c260-…, IActiveScript/IActiveScriptParse64)` (1801403f8), for semantic-tag grammars.
  I rendered "On 12/25/2013 at 3:45 pm, Dr. Smith paid $1,234.56 for 3 items. Call 425-555-1234." with David. **jscript.dll was not loaded**, so the en-US grammar does not seem to use scripts. I only checked that one input. A port must still confirm this with a load-module check over a wide corpus.
- The INI [TN] section is read by 180056808 from the lang INI (resmgr vt+0xd0) or the voice INI (vt+0xb0), through 1800bcd88. The values it reads are TNScope, TNEnhancedSayAsSupport and the decimal/thousand separators.
  TNBoundaryType (BOUNDARY_AT_PUNCTUATION …) is only referenced in the Loc DLL (**guess**: it is used by the locale TA).
  SayAsMapping and `SayAsMapping.` are resolved in 18004b020 and 1800518c0 and belong to fork D.
- The `HKLM\SOFTWARE\Microsoft\Speech_OneCore\TextNormalizers` key is read at 180027bd8 (lines 30824 and 120948) and 18002708c (line 185652). This looks like an optional external TN override (**guess**). Fork D should confirm.

### Word breaking

**CWhiteSpaceBreaker** (vt 180176410):
- Init at vt+0 = 1800c4780. The shared name is "WORDBREAKER_en-US" or "UPDATE_WORDBREAKER_en-US". The type is 629aa5c4. The ids are tried in order 964f993a, 86405bc7, c4235fef, then **9756c4e5**, which is the only one present (chunk 0x1eec8, 0x7aff B).
- 1800cbe0c parses the blob into a **CWordBreakerInfo** (char-class and bsearch tables).
- Break is vt+8 = **180043cd0**. It calls 180076454 (char classification with the resource tables), then 18007a588 / 180043ee8 / 180044194, and writes the tokens to a CTTSWordSink.

Other breakers:
- The Loc DLL has no en-US breaker (TA vt+8 returns E_NOTIMPL).
- CCompoundWordBreakerEnUS is only used for OOV pronunciation (TA vt+0x28).
- CTTSNgramTrieBreaker is absent.
- CAddressCRFWordBreaker ("address word breaker_%s", "CRF model Address word breaker", 1800e1ab0 → b15e4e27/47a7f580) is only reachable through the **address domain** handler. Its GUID is not found in any en-US file (**guess**: it lives inside enUS.Address.dat under a different id).

### Domains / named entities

- **Domain handlers** are built by 180099628 from the name: "acronym" → CAcronymDomainHandler, "message" → CSmsDomainHandler, "name" → CNameDomainHandler, "address" → CAddressDomainHandler, "media" → CMediaDomainHandler, anything else → CDomainHandler.
  They come from the lang INI [Domain] Number/Domain%d/FileName%d, read by 180016f24 and 18009944c. The data files are `enUS.<Domain>.dat` and use the same GUID container as the main .dat.
  enUS.Name.dat contains an **RNN LTS** (46ee52ba), and enUS.Address.dat contains the **acronym CRF** (cea1be6f).
  A handler is active only when the fragment's context or say-as maps to that domain, directly or through [SayAsMapping] (e.g. place_name→address). A handler can supply a lexicon (container-lexicon step 3), a word breaker (1800c4db8) and prosody settings.
- The **CNEDetector** is described above. It is rule/FST-based. `managedNER.dll` (loaded at line 236369) is not present on disk, so it is inactive (**guess**, not traced).

### POS tagging

- **CPOSTaggerImpl::Tag** = **1800569d0**. For each word that has text (vt+0x80):
  1. If the word has no pronunciation yet (vt+0x68 == 0 && vt+0x258 == 0), look it up in the lexicon with FUN_1800484b4 (A+0x580 container lexicon, `vt+0x250` stores the result).
  2. If the lookup fails (0x80048017) and the flag is set, use 1800c2294 (LTS or morph fallback **guess**), else mark the word (vt+0x40, 1).
  3. Build a candidate node (0x58 B, 1800c2398; `next` at +0x50) from the word's lexicon POS set.
  4. Run the tagger on the chain: `CPosTagger` (vt 180179390) **vt+0 = 180062190** → 1800621e8 (for each node with ≠3 candidates, 18015f30c; for type-2 nodes, 18003d1e0), then 18002ef70 (only if +0x40), then 18005bc60.
  5. 18002ef70 is a 1000-line n-gram decoder that uses `"S-T-A-R-T"` boundary symbols (**guess**: trigram HMM Viterbi).
  6. Write the tags back with `word vt+0xe8(pos, posTable)`.
- Model: **0cb71848/827032e3** (chunk 0xf90, 0x9e72 B), loaded by 1800458cc. CRNNPOSTagger (3235b923/b8852744) is **absent**, so the classic CPosTagger is used.
  The POS table f81fd1d1/ed1348b2 (0x30 B, 18003777c) is attached to the lexicon (1800c19dc).
- `TRANSDUCER_POSCONVERTER_%s` (line 236624) is not traced (**guess**: it is for mixlingual or locale POS mapping).

### Pronunciation (CPronouncer, vt 180176298)

CPronouncer (0x98 B) Init vt+8 = **1800c3060** builds:
- +0x50 **CWordPronouncer** (vt 180176368). Init 1800c99dc creates:
  - +0x28 the main LTS (1800c9890):
    - It first asks for RNN LTS 46ee52ba/3b273052 ("RNNLTS_%s", **absent**).
    - It then falls back to **CART LTS ac4aefcf/d18325ec** (chunk 0x6c2138, 0xf32fc B). This is shared as "LTS_en-US" and is a **CLTSLexiconCART** (1800c8e88; data init 18015fcb8, ctor 1800c9c34).
  - +0x30 COMPOUNDPRON (1800ccd00 → 1800cce14 "COMPOUNDPRON_%ls" → 1800ccf10) from **19a6569a/ea8d0701** (chunk 0xae30, 0xdcb0 B).
  - +0x40 extra-language LTS (1800cd1d4, "LTS_%s_%i") from **6f4ac239/c5693920** (chunk 0x269f0).
    Header: u8 n=1, then u16 lang 0x080A (es-MX), then u32 offset pairs. It holds a Spanish LTS for mixlingual words (**guess** on its use).
- +0x58 **CPolyphony** (0x1950 B, ctor 1800c2524) from **e849e61b/4a3c699e** (chunk 0x8dc588, 0x332b0 B). This is a rule-based context homograph table. Examples of the strings:
  - "." between nums → "p oy 1 n t"
  - "Charles"… + "I" → "dh ax 1 - f er 1 r s t"
  - symbol/num contexts for "dash", "comma", "colon"
  It is run by 1800c9e30 over the word list (+0x68).
- +0x60 **CPolyphonyHandler** (vt 1801764f8). Init 180064400 loads:
  - the **CCRFPolyphonyTaggerList** (18002b96c) from **d49f77b9/3e135d7f** (chunk 0x888e10). That bank holds **13 CRF models**: address, close, complex, conflict, contract, lead, live, object, present, read, subject, UPS/ups, use.
    The labels are `%`-separated UPS phone strings and the features are CRF++-style templates (`U00:Token.PrevToken…CaseInsensitiveText`, 12 or 24 per model). See `fe_tables.py`.
  - CRNNPolyphonyTagger (6de01f86, 18006e444) is **absent**.
  - It runs 1800caca8 (**CRF** per ambiguous word, through 1800cec7c) and then 180060158 (applies the chosen pronunciation; honours the domain "none"/"general").
- +0x68 **CSyllableSeg** from **78f6770d/7ab40d39** (chunk 0x48da8, 0x24c B). It is initialised with vt+8, and **guess**: it syllabifies LTS output.

**CPronouncer::Pronounce(wordList)** = **1800479e0**:
1. For each word, 180047abc: skip words that are already pronounced. Look the word up with FUN_1800484b4 (container lexicon), apply morphology / 18005d888 / 18004863c, and pick the lexicon entry that matches the POS (vt+0x88). Otherwise use 1800c28cc (LTS path).
2. For each word, 180047eac: for OOV or special words, call `LTA vt+0x28` (email/compound splitter). Domain "name" goes to 1800c33dc. Then 1800c2e80 / 18008ec9c (spell-out / acronym letter pronunciations for all-caps, 18008f7e4), then 1800c2d6c (LTS with 0x180-char buffer), and set the result with vt+0x88.
3. CPolyphony (1800c9e30).
4. CPolyphonyHandler (1800caca8, 180060158).
5. For each word, 180017d1c (per-domain post-processing through engine map 18006f208, "general").
6. 1800563dc → 180056450 for each word that is not punctuation (vt+0x270 == 0). **guess**: this is the final syllabification / stress normalisation.

**Container lexicon lookup** = CTTSContainerLexicon vt+0 = **1800c1350**(word, lang, 0, domain, &out, flag):
1. Try the lexicons in +0x48 with the current domain, unless the domain is "none" or "general".
2. Try the same lexicons with domain `"none"`.
3. Try the lexicon of the active domain handler (engine+0x40 map → vt+0x18 → vt+8).
4. If `flag` is set, try the priority list at +0x10 with 180053898. This list holds LEX 0x1000, hot-fix 0x1000, VOICE_LEX 0x8000 and the morph lexicon. **guess**: a higher value wins.

"Not found" is 0x80048017.

### CRF runtime (shared by the sentsep, acronym and polyphony taggers, and the Loc-DLL prosody taggers)

- Model init is CCRFTagger `FUN_1800e3650(tagger, blob, size, extra, L"name")`. Each CRF blob starts with `"TD\0\0" + GUID 0d5c0d43-bd7b-40d7-9a9c-266b31969fdd + u32 size + u32 LCID 0x409 + "CRF\0" + u32 0x64 …`.
- Feature extraction: 1800e35a0 → 1800e43f0 → 1800e4474 builds the per-token feature-id lists from the templates. It uses 180038d5c for each template; ids that were already computed are listed in `param_1[8]` and skipped.
- The decoder object is CCRFDecoderCore (vt 180176c00). I did not trace the decoding algorithm. **guess**: it is standard linear-chain Viterbi (argmax), and on ties the first (lowest) label wins. That has to be verified before a bit-exact port.

### Resource map for the text half (en-US; "Absent" = GUID pair not in any en-US file)

| type/id | chunk @ size | consumer | status |
|---|---|---|---|
| 00a2359e/4d4d5073 | 0xb0 / 0xeb6 | CRuleSentAndPuncDetector 1800b7ca8, 180059d90 | used |
| e67ab014/1df28780 | 0x8d1238 / 0xb322 | SENTSEP lists, CSentSepImpl (180047748) | used |
| 9b4ece4f/0d5c0d43 | – | CCRFSentSepTagger (1800c073c) | absent |
| 3292d97f/0d5c0d43 | – | CCRFSentTypeDetector (1800b7d70) | absent |
| 5554ba64/09397c04 | 0x1ea88 / 0x414 | suffix tables, TP+0x30 (1800b80dc) | used |
| b54490e3/e4c81da4 | 0x7b5460 / 0x28 | quote pairs, TP+0x38 (1800b83f4) | used |
| d8951565/52a33b0b | 0x8d1150 / 0xc0 | parallel structure (1800b8f08) | used |
| 629aa5c4/9756c4e5 | 0x1eec8 / 0x7aff | CWhiteSpaceBreaker tables | used |
| 7d5841ab/ea8d0701 | 0x38eb50 / 0x333044 | TN and NE transducer network | used |
| bfc4309d/d2343132 | 0x7b54b0 / 0xd3931 | CFstMatcher for NE (1800c426c) | used |
| 0cb71848/827032e3 | 0xf90 / 0x9e72 | CPosTagger model | used |
| 3235b923/b8852744 | – | RNN POS | absent |
| f81fd1d1/ed1348b2 | 0x959bc8 / 0x30 | POS table | used |
| f6e4f50a/80b9a5a3 | 0x9562b0 / 0x38f0 | CCharTable | used |
| efdc81f5/18be7e07 | 0x90f860 / 0x46a24 | "Language Identifier" | loaded |
| 7bd71f46/f9a99c02 | 0x49020 / 0x345b04 | main lexicon "LEX" | used |
| ac4aefcf/d18325ec | 0x6c2138 / 0xf32fc | CART LTS | used |
| 46ee52ba/3b273052 | – (only in enUS.Name.dat) | RNN LTS | absent for the default domain |
| 19a6569a/ea8d0701 | 0xae30 / 0xdcb0 | COMPOUNDPRON | used |
| 6f4ac239/c5693920 | 0x269f0 / 0x2238e | extra-language LTS (es-MX) | loaded |
| e849e61b/4a3c699e | 0x8dc588 / 0x332b0 | CPolyphony rules | used |
| d49f77b9/3e135d7f | 0x888e10 / 0x48314 | CRF polyphony bank (13) | used |
| 6de01f86/ed89822b | – | RNN polyphony | absent |
| 78f6770d/7ab40d39 | 0x48da8 / 0x24c | CSyllableSeg | used |
| cea1be6f/0fbd602c | – (enUS.Address.dat only) | CRF acronym | absent in the main .dat |
| 03110205/d29ffcb7 | – | n-gram trie breaker | absent |

### Hook points for a text-stage harness (x64, RVA = VA − 0x180000000)

- **180065980** Analyze(sentence). On return, walk A+0x420 and the sentence (vt+0x28), or hook 1800bd64c (commit) to dump the words.
- **1800c3e50** TN Normalize(text, category, out). Log input and output: this gives TN ground truth for each token.
- **180061910** NE FindNext. Log the returned offset, length and category.
- **180043cd0** word breaker output.
- **1800569d0** POS: dump `word vt+0xe8` args, or hook `vt+0xe8` itself.
- **1800479e0** Pronounce. Compare word pronunciations before and after the lexicon, LTS (1800c28cc / 1800c2d6c), CPolyphony (1800c9e30) and CRF polyphony (1800caca8) steps.
- **18005d050** sentence length for each call.

Word accessors, all vt offsets on CTTSWord (layout owned by fork C):
- +0x80 text
- +0xc0 say-as category
- +0xe0 domain
- +0xe8 set POS
- +0x88 set pronunciation (buf, len, flag)
- +0x90 pronunciation
- +0x68 has-pron flag
- +0x270 is-punctuation
- +0x38 LangID
- +0x250 attach lexicon entry

---

# Handler pipeline, linguistic prosody, utterance structures and the frontend→backend boundary

(fork C; all addresses are VAs in MSTTSEngine_OneCore.dll (base 0x180000000) unless prefixed `loc!` =
MSTTSLoc_OneCore.dll. Everything is static analysis of the Ghidra `_all.c` plus RTTI/vtable dumps with
`tools\rtti.py`/`tools\vtsum.py`; nothing here has been confirmed at runtime yet. **guess** marks inferences.)

## 0. Which engine and data the reference voices really use (important)

Registry (`HKLM\SOFTWARE\Microsoft\Speech\Voices\Tokens`, i.e. what System.Speech / render.ps1 sees):

| token | CLSID → DLL | VoicePath | LangDataPath |
|---|---|---|---|
| TTS_MS_EN-US_DAVID_11.0 ("Microsoft David Desktop") | {179F3D56-…} → `System32\speech_onecore\engines\tts\MSTTSEngine_OneCore.dll` | `Speech_OneCore\Engines\TTS\en-US\M1033David` | `Speech_OneCore\…\MSTTSLocEnUS.dat` (9.8 MB) |
| TTS_MS_EN-US_ZIRA_11.0 ("Microsoft Zira Desktop") | {C64501F6-…} → `System32\speech\engines\tts\MSTTSEngine.dll` (**the non-OneCore desktop engine**) | `C:\Windows\Speech\Engines\TTS\en-US\M1033ZIR` (APM 6.18 MB, INI, Keyboard.NUS) | `C:\Windows\Speech\Engines\TTS\en-US\MSTTSLocEnUS.dat` (9.26 MB, older build) |

The OneCore tokens (`Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_{David,Zira,Mark}M`) all use MSTTSEngine_OneCore.dll with the
`Speech_OneCore` data. **So "Zira Desktop" renders come from a different engine DLL (bin\MSTTSEngine.dll) and different
data files than OneCore Zira.** This document maps MSTTSEngine_OneCore.dll; I have not checked whether MSTTSEngine.dll matches it
function for function (its class set is probably close; **guess**). A Zira port has to be checked against MSTTSEngine.dll plus
`C:\Windows\Speech\...\M1033ZIR.*`, or the references have to be rendered through the OneCore token.

## 1. The handler chain (CTTSEngine)

CTTSEngine (vftable 0x18016f190) holds an array of `ITTSHandler*` at **engine+0x1a8** (ptr, count at +0x1b0, cap at +0x1b8). A second
array at +0x1c8 is used when `Pipeline.ParallelProcess=yes`, and the handlers after the acoustic tagger then run on another
thread (fork D's area). The build is driven by a handler-mask dword at **engine+0x100** (bit → handler). Where the mask comes from is
not resolved: it is not written anywhere visible in the decompile, so it is **guess**: passed in by the COM wrapper/config.
The value `0x40000` alone means "text only" (used for Normalize/GetPronunciation-type calls, `FUN_1800930dc`).

| order | bit in +0x100 | slot | class (ctor/dtor) | init call | Process (vt+0x18) |
|---|---|---|---|---|---|
| 1 | 0x40000 | +0x1f0 | CTextProcessor (0x1800b4888) | `FUN_1800936c0` | `FUN_1800b5110` "CTextProcessor::Process" |
| 2 | 0x80000 | +0x1f8 | CLinguisticProsodyTagger (0x18009b65c/0x18005d200) | `FUN_180058fac` | `FUN_180060010` |
| 3 | 0x100000 | +0x218 | CTTSUnitGenerator (0x18009cc18) | `FUN_180058fac` | `FUN_180034b00` "CTTSUnitGenerator::Process" |
| 4 | 0x4000000 | +0x200 | CAcousticProsodyTagger (0x1800594ec; +0x9e8=0) | `FUN_180058fac` | `FUN_1800a39f0` → `FUN_1800a3324` |
| 4b | 0x4000000 and `Pipeline.EnableLongUnitAnchor` | +0x208 | CAcousticProsodyTagger (+0x9e8=1, "…For Long Unit Selection") | same | same |
| 5 | (EnableLongUnitAnchor) | +0x228, +0x210 | CLongUnitLatticeGenerator (0x1800f2264), CAcousticProsodyTaggerAnchor (0x1800a3ffc) | `FUN_180060820` | |
| 6 | `Pipeline.EnableStreaming` (default 1) | +0x1e8 | streaming/output handler (0x180149864) | `FUN_180060820` | |
| 7 | 0x800000 | +0x230 | CUnitLatticeGenerator (0x1800f5734) | `FUN_180060820` | |
| 8 | 0x1000000 | +0x238 | CUnitSelector (0x1800ff760) | `FUN_180060820` | |
| 9 | 0x2000000 | +0x240 | CWaveGenerator (0x18007a000) | `FUN_180060820` | |

Every handler goes through `vt[0](handler, engine)` = Init, then `FUN_1800511d0(list, &handler)` = append, then `FUN_18007a4c8(hr, "name")`,
which writes a trace line "%s Successfully Initialize %S." with the ANSI names at 0x180185570… ("Linguistic Prosody Tagger", "Unit
Generator", "Acoustic Prosody Tagger", "Unit Lattice Generator", "Unit Selector", "Wave Generator").
The locale handler is created before this: `FUN_18005df80` loads `MSTTSLoc_OneCore.dll!GetLocaleHandler(LANGID)` into
**engine+0x350**. The data/resource manager is at engine+0x368, CTTSLookUpPath (voice search path) at engine+0x370, the voice base
path string (`…\M1033David`) at engine+0x3b8 (engine vt+0xa8 returns it), the settings object at engine+0x4a8/+0x4e0, and domain
handlers at engine+0x580.

### Per-Speak / per-sentence driver
`CTTSEngine vt+0x20 = FUN_180095aa0` → **`FUN_180028288` = Speak**:
1. It logs the fragments and walks the SPVTEXTFRAG list (voice/domain changes; fork D).
2. `FUN_180094904` picks the handler array (engine+0x1a8) and the output sink (engine+0x250). A domain voice (`[Domain]` in the
   voice INI) can supply its own engine copy (`FUN_18007196c`).
3. For each handler it calls `vt+0x10` (per-Speak begin).
4. **Loop, once per sentence/utterance.** `FUN_180079ce4` allocates a fresh **CTTSUtterance** (0x760 bytes, ctor `FUN_180149c78`,
   init `FUN_18014a0d8`, which creates the CTTSSentence at utt+0xe0). It copies the SAPI state into the utterance (+0x70 domain
   string, +0xa8/+0xb0 pointers, +0xb8 float, +0xc0/+0xc8), then calls `FUN_18006ff8c(engine, utt)` (domain/NUS selection) and
   optionally `FUN_18009552c`. Then:
   ```
   for i in handlers:  id = h->vt+8(&id)
                       if (cb = engine+0x578) { r = cb->vt0(cb, id, 0 /*before*/, utt); if r==1 skip }
                       hr = h->vt+0x18(h, utt)            // Process
                       if (cb) cb->vt0(cb, id, 1 /*after*/, utt)
   ```
   After that it handles metadata/bookmark events through CTTSMetaDataHandler casts (utt+0xa0 flags; fork D), frees the utterance
   (`vt[0]`), and repeats `while hr == S_OK`. CTextProcessor returns S_FALSE when the text runs out.
5. For each handler it calls `vt+0x20` (end), then logs "[TTS] WaveTime".

**engine+0x578 is a built-in per-handler pre/post callback** (setter `FUN_18008ae80`, which returns the old value). It is the
cleanest hook point for a harness: install an object whose vt[0](this, handlerId, phase, utt) dumps the utterance after handler 2
(LinguisticProsodyTagger) and after handler 3 (UnitGenerator). CLinguisticProsodyTagger has the same kind of callback at +0x30 for each
sub-predictor. CAcousticProsodyTagger has one at `this[6]`, called with code 0x4000004 just before feature extraction.

## 2. CLinguisticProsodyTagger

Vftables 0x180171328 (ITTSHandler) and 0x180171400. Its object embeds four predictors:

| member | class (vftable) | id | runs |
|---|---|---|---|
| +0x68 | CProsodyBreakPredictor (0x180173608) | 1 | 1st |
| +0xb8 | CProsodyEmphasisPredictor (0x1801713b0) | 2 | 2nd |
| +0xe8 | CProsodyBoundaryTonePredictor (0x180171e38) | 3 | 3rd |
| +0x118 | CProsodyPitchAccentPredictor (0x1801712d8) | 4 | 4th |

- Init `FUN_18009b770`: `predictor->vt+0x10(engine, id)` (= `FUN_18009c460`; for Break it is `FUN_18009a4b0`, which also reads
  setting 0x1801862b0) for each predictor, then `FUN_18009c0dc` builds the run list at +0x48/+0x50.
- `FUN_18009c460` creates a **CProsodyModelRunner** (vftable 0x180171198) at predictor+0x18. It asks the locale handler for its
  model table (`loc vt+0x18`) and calls `runner->vt+0x38 = FUN_180055380(engine, table, n, id)`.
- **Process `FUN_180060010`**:
  - If `loc->vt+0x90()` returns nonzero (ENU returns this+0x24 = "Prosody/EnableDomainTwoPassPrediction" from the language settings)
    and the utterance domain is in engine+0x518, it first runs `FUN_18009bb70` (a two-pass prediction on a sub-utterance for say-as
    domains).
  - `FUN_1800755b4` then calls each predictor's `vt+8 = FUN_18009c5c0`, which is `vt+0x28` (pre, rules), `vt+0x30` (model runner),
    `vt+0x38` (post), and `vt+0x40` if +0x20 is set.
  - After the predictors: `loc->vt+0x20` (only if this+0x40), then `loc->vt+0x70`. Finally sentence(+0x28 list obj)+0x60 = 1.
- Break predictor slots: pre `FUN_18009a400` = rule chain `FUN_18009afd0` (SSML `<break>` → BI), `FUN_180059964` (punctuation →
  BI/pause class, SSML `<emphasis>` → word accent), `FUN_18009ad24` (reads `SilenceLength.PuncIntermPhraseBoundary`),
  `FUN_18009aa04`, `FUN_18009a8b0`, `FUN_18009b3e4`, `FUN_18009a808`. Model runner `FUN_18009a350`. Post `FUN_18009a280` = every
  domain handler at engine+0x580 `->vt+0x70(utt)`.
- The emphasis, boundary-tone and pitch-accent predictors have no rules of their own. Their `vt+0x28` checks that there are words.
  Boundary tone's `vt+0x28` (thunk → `FUN_1800508d4`) finds list items and sets tones 0x3ea/0x3eb/0x3ec through word vt+0x158.
  Pitch accent's `vt+0x30 = FUN_18009c870` calls `vt+0x110` on each word, then the runner.

### Model table from the Loc DLL (ENU: `loc!CTTSLocaleHandlerENU` vftable 0x18007b8a0, `vt+0x18 = loc!0x180019630` → table
`loc!0x1800a14c0`, 11 entries of 32 bytes: {int predictorId; pad; wchar* name; factory(); arg})

| id | name | factory | class | loads |
|---|---|---|---|---|
| 1 | BRK | loc!0x18005ee40 | CProsodyBreakCARTPredictor (CProsodyWordCART) | `<VoicePath>.BRK` |
| 1 | BR2 | loc!0x18005d920 | CIntermediatePhrasePredictor : CCRFBreakTagger | `<VoicePath>.BR2` |
| 1 | BR3 | loc!0x18005e5c0 | CIntonationPhrasePredictor : CCRFBreakTagger | `<VoicePath>.BR3` |
| 1 | TOBI, BI | loc!0x18005ef40 | CProsodyRNNPredictor | `<VoicePath>.TOBI` / `.BI` |
| 2 | EMP | loc!0x18005fd80 | CProsodyEmphasisCARTPredictor | `<VoicePath>.EMP` |
| 2 | EMC | loc!0x18005fe50 | CCRFEmphasisPredictor | `<VoicePath>.EMC` |
| 3 | TON | loc!0x180060480 | CCRFBoundaryTonePredictorEnglish (CCRFBoundaryToneTaggerImpl) | `<VoicePath>.TON` |
| 3 | TI | loc!0x18005ef40 | CProsodyRNNPredictor | `<VoicePath>.TI` |
| 4 | ACL | loc!0x18006b860 | CCRFPitchAccentLocTagger | `<VoicePath>.ACL` |

The runner (`FUN_180055380`) builds the key `ProsodyModelSetting.<name>` and asks the engine settings (engine+0x4e0 vt+0x18) whether it
is enabled. The engine default table (0x18016d790, 137 entries of {name, type, default string, default int}) gives
`ProsodyModelSetting.{BRK,BR0,BR2,BR3,B23,CBD,medianame,EMP,EMC,TON,ACT,ACL} = "VoiceFont"` (`FUN_180051c38`: "no" = off, a CLSID or
"VoiceFont" = on). TOBI/BI/TI are not in the table.

Each model then calls `factory()`, then `vt+0x40(engine, name, arg)`, and looks up a file named `<VoicePath>.<name>`
(`CTTSLookUpPath vt+0x30 = FUN_1800169a0`, which formats "%s.%s" and searches the voice lookup paths, `FUN_180029b90`). A missing
file returns 0x80070002 → 0x8004801a, and the runner skips that model (CART models stay attached but inactive, +0xc=0).
- **M1033David and M1033Zira (OneCore) ship only .APM/.BEP/.INI (+ NUS for Zira): no .BRK/.BR2/.BR3/.EMP/.EMC/.TON/.ACL/.TOBI/.BI/.TI.**
  Eva ships .ACL, .TON and .BR2. So **for David and Zira no statistical prosody model runs**. Breaks, boundary tones and accents come
  only from the rule code above (punctuation, SSML break/emphasis, list items, domain handlers) plus the ENU locale post-step. This is a
  static conclusion. Verify at runtime: the runner's sequence handler at predictor+0x18 → +0x28 should hold count 0 (+0x10).
- The CRF/RNN decoders (loc CCRFDecoderCore, CCRFLattice, CRNNDecoder, CRNNFeaturizer, CProsodyRNNTagger*) are therefore **not needed for
  David/Zira** and I did not map them in detail. The text-side CRFs (sentence separator, word breaker, acronym, polyphony) are engine-side
  (fork B).
- Relevant voice INI keys: `BreakPrediction.PhraseBased` (default "false"), `BreakPrediction.EntityFolding` ("false"),
  `BreakPrediction.MaxWordNumPerInterPhrase` (loc, CCRFBreakTagger only), and `SilenceLength.*`. SilenceLength defaults in ms:
  WordBoundary 0, PuncIntermPhrase 10000(sic), IntermPhrase 100, NonPuncIntonationPhrase 70, ParalStructIP 120, ParalStructListIP 350,
  IntonationPhrase 500, SentenceBoundary 750, SpeakSessionStart 100, SpeakSessionEnd 750. The David INI overrides IntonationPhrase=400
  and Sentence=750. The OneCore Zira INI overrides IP=250 and Sentence=500. `MSTTS.NoPause=1` zeroes classes 3..6. The loader is
  `FUN_180051980`; the class-index order is table 0x180170f00: 0 Word, 1 IntermPhrase, 2 PuncIntermPhrase, 3 NonPuncIP, 4 ParalStructIP,
  5 ParalStructListIP, 6 IP, 7 Sentence.

### ENU locale handler (loc!0x18007b8a0, object 0x68 bytes, created by `loc!FUN_1800199e0` for LANGID 0x409)
Init `loc!0x1800197e0`:
- base init `loc!0x18000fa30` (engine at +8, engine vt+0xd0 = language-settings reader at +0x10, CBoundaryPronChange, reads
  "Prosody/EnableAccentModelForEmphasis" → +0x20 and "Prosody/EnableDomainTwoPassPrediction" → +0x24)
- +0x38 = CCustomFeatureDataEnglish, +0x40 = CCustomFeatureExtractorEnglish ("WordAccentPattern", "WordPositionInPhrase" custom
  features for the backend feature extractor)
- +0x28 = CTTSSequenceHandler containing +0x30 = CListItemBoundaryToneTaggerEnglish

Known slots:

| slot | address | what it does |
|---|---|---|
| +0x10 | | returns a name table |
| +0x18 | | prosody model table (above) |
| +0x20 | | returns 1 |
| +0x30 | 0x1800176c0 | |
| +0x48 | 0x180017730 | runs the list-item tagger sequence |
| +0x50 | 0x1800107f0 | |
| +0x70 | 0x180014e90 | post-prosody step (boundary pron change via this+0x18) |
| +0x78 | 0x180014f10 | BoundaryPron FeatureLevel/AtomChangeType/ConnectChangeType settings |
| +0x80 | | creates CLocaleTextAnalyzerENU |
| +0x88 | | returns this+0x20 |
| +0x90 | | returns this+0x24 |
| +0x98 | | creates CLocaleBackEnd |
| +0xa0 | | returns +0x38 |
| +0xa8 | | LANGID |
| +0xb0 | 0x180010ac0 | E_NOTIMPL, so the engine uses its own CCRFSentSepHandler |
| +0xc8 | | CCompoundWordBreaker |
| +0xe8 / +0xf0 / +0xf8 | | word-breaker helpers |
| +0x100 / +0x108 | | small string tables ("eLearning") |

**guess**: the rest are text-analysis hooks for fork B.

## 3. Utterance data structures

All tree nodes derive from `CTTSUtteranceNodeBase<Child,Self,Parent>`. The layout is common to every level:
```
+0x00 vftable (main)          +0x08 parent*            +0x10 firstChild*        +0x18 lastChild*
+0x20 owning sentence list*   +0x28 link* in that list: link = {next link*, prev link*, item* at +0x10}
     next sibling at same level = (*(node+0x28)) ? *(*(node+0x28))+0x10 : 0      (FUN_180045a04 / FUN_18004e7bc iterate)
+0x30 (Phone/Syllable) or +0x38 (Word) = CTTSFeatureNodeBase vftable: +8 Navigate(location), +0x20 GetCustomFeature,
      +0x28 GetFeature(propId,&FeatureValue)
```
`FeatureValue` = 16 bytes `{int type (0 = int, 1 = enum, 2 = wstring, -1 = undefined); int pad; union {int i; wchar_t* s;}}`.
Hierarchy: HalfPhone < Phone < Syllable < Word < Phrase < IntonationPhrase. CTTSProsodicWord is a parallel grouping of words
(word+0x2c0 → prosodic word).

**CTTSUtterance** (0x760 bytes, vftables 0x18016d020 / 0x18016d008):

| offset | contents |
|---|---|
| +0x38 | CPropertyBag |
| +0x70 | CTTSString, domain name ("general") |
| +0x98 | ? |
| +0xa0 | event/metadata flags |
| +0xa8 … +0xc8 | SAPI state copied in by Speak |
| +0xd0 / +0xd8 | condition variable / SRW lock (acoustic streaming) |
| +0xe0 | **CTTSSentence\*** |
| +0x148 | map phone → units |
| +0x250 | CTTSEventManager (vftable at +0x250) |
| +0x2c0 | acoustic-space selector |
| +0x2c8 | CTTSAcousticSpace #0 (`FUN_18014b870`) |
| +0x348 / +0x550 | phone list cached for each space |
| +0x4d0 | CTTSAcousticSpace #1 (`FUN_18014b730`) |
| +0x754 | flag used by the anchor tagger |

`FUN_18005c534` = dynamic_cast to CTTSUtterance.

**CTTSSentence** (0x2e0 bytes, ctor 0x1800b53a0, vftable 0x18016fde8). Each list is 0x30 bytes {head link*, tail, count(+0x10), …,
grow=10}.

| getter (vt) | list | meaning |
|---|---|---|
| +0x40 | +0xb0 | **phones** (`FUN_1800331d8`, level 1) |
| +0x38 | +0xe0 | **syllables** (`FUN_18014a2c4`, level 4) |
| +0x28 | +0x110 | **words/tokens** (`FUN_180034e44`, level 8) |
| +0x30 | +0x188 | **prosodic words** (`FUN_18014a1a4`, level 0x10) |
| +0x48 | +0x1b8 | **phrases** (`FUN_18014a170`, level 0x40) |
| +0x50 | +0x1e8 | intonation phrases (**guess**, `FUN_18014a1d8`) |
| +0x58, +0x60, +0x68 | +0x218, +0x248, +0x278 | unknown; +0x278 = segments (**guess**; `FUN_18014a13c` uses +0x60) |

Scalar fields: +0x80/+0x88 text span (ptr, len), +0x90/+0x98 a second span, +0xa0/+0xa4 ints (vt+0x70/+0x78),
+0xa8 **SentenceType** (vt+0x90, enum), +0xac **SentenceEmotion** (vt+0xc0).

**CTTSWord** (0x370 bytes, ctor 0x18001ba9c, dtor 0x18001e8d4, vftable 0x18016d098 (main), +0x38 feature iface 0x18016d378; feature
table 0x1801706d0, getter `FUN_18004c7e0`).

| offset | field |
|---|---|
| +0x10 | parent phrase |
| +0x80 | u16 (vt+0x30/0x38) |
| +0x84 | int word type (vt+0x40/0x48?) |
| +0x88 | int |
| +0x90 | ptr to SAPI frag state (rate/pitch/vol, used by UnitGenerator) |
| +0x98 | Text |
| +0xb8 | RegularText |
| +0xd8 | CaseInsensitiveText |
| +0xf8 | PreviousCharacters |
| +0x118 | NextCharacters |
| +0x138 | u16 **POS** (after conversion) |
| +0x13a | u16 **POSTaggerPOS** (raw tagger output) |
| +0x160 | **Pronunciation** string (vt+0x98) |
| +0x180 | int |
| +0x190 | NamedEntityType wstring (vt+0xc0) |
| +0x1a8 | ptr |
| +0x1b0 | string |
| +0x1d0 | AcousticDomain string |
| +0x228 | int (vt+0x128/0x130, e.g. punctuation class set by the rules) |
| +0x22c, +0x234 | ints |
| +0x238 | **ToBIFinalBoundaryTone** (set vt+0x158, get vt+0x160, lock vt+0x168 → +0x23c) |
| +0x240 | int |
| +0x244 | **BreakIndex** (set vt+0x1a8, get vt+0x1b0, lock vt+0x1c8 → +0x24c; ctor default 2) |
| +0x248 | int |
| +0x250 | **pause class** (index into SilenceLength table; set vt+0x1e8) |
| +0x254 | **accent/emphasis flag**, exposed as feature "Emphasis" (0x4c); a syllable's "Accent" = stressed and word+0x254==1 (set vt+0x1f8, get vt+0x200, lock vt+0x1d8 → +0x258) |
| +0x270, +0x274, +0x278, +0x27c | ints |
| +0x2c0 | prosodic word |
| +0x328 | inner object (vt 0..0x28 forward) |
| +0x360 | ptr |
| +0x368 | int |
| +0x36c | int |

Word type (vt+0x68): 0 = word, 1 = punctuation (vt+0x108 = punctuation class 1..7), 3 = break/silence token (data at vt+0x110: +8 SSML
strength −1..−6, +0x10 tone flag, +0x18 valid), 4 = spelled/other word **guess**. "Lock" flags mark values that SSML fixed; later
predictors do not overwrite them.

**CTTSSyllable** (0xc8+ bytes, ctor 0x18001aefc, feature table 0x180170400):
- +0x80 CTTSString, +0xa0 CTTSString
- +0xc0 **ToBIAccent** (enum)
- Stress = max over its phones of `FUN_1800195b4(phone)` (`FUN_180019540`)
- BreakIndex = the word's BI on the last syllable, otherwise 1
- Tone at 0x1801521d0

**CTTSPhone** (0xe0 bytes, created in `FUN_18001c4ac` from the pronunciation string, feature table 0x180170240):
- +0x84 u16 **PhoneIdentity** (phone id in the language phone set; the table is in the .dat, fork A)
- +0x88 CTTSString **PhoneName**
- ToneLevel `FUN_180150b30`
- per-phone stress read by `FUN_1800195b4`

**CTTSPhrase** (feature table 0x180178ca0): ToBIFinalBoundaryTone = last word's +0x238.
**CTTSIntonationPhrase** (feature table 0x180178e20): +0x78 ToBIFinalBoundaryTone.
**Sentence** feature table 0x180178bb0: SentenceType, SentenceEmotion, counts.
**Prosodic word / token** feature table 0x180178ed0: CharacterNumber …

Enum values that are known:
- BI 1..5. SSML x-weak→1, weak→2, medium→3 (pause 1), strong→4 (pause 3), x-strong→5 (pause 7); sentence end→5 (pause 7).
  **guess**: 2 = plain word boundary, 3 = intermediate phrase, 4 = intonation phrase.
- Boundary-tone codes seen: 0x3ea/0x3eb/0x3ec (1002/1003/1004). ToBI names are not in the binary, so the numbers are the interface.
- The POS strings `TTS_MAIN_POS_*` (0x18018cbc8…) are debug-dump labels (fork B).

## 4. THE BOUNDARY: frontend output → acoustic backend

**Boundary = the CTTSUtterance as it enters handler 3/4.** More precisely:
- **Frontend output** = the utterance after `CLinguisticProsodyTagger::Process` (handler id 2 in the engine+0x578 callback).
- `CTTSUnitGenerator::Process` (`FUN_180034b00`) is the adapter. It walks the words (`FUN_18005f190`: applies the SAPI rate/pitch/volume
  from word+0x90 and the INI VoiceSetting factors), creates the unit list per word (`FUN_18001f4c0`), fills utt+0x250/+0x2c8, and calls
  `FUN_18009db84` (per-phone unit sequence, depends on the voice phone mapping).
- `CAcousticProsodyTagger::Process` (`FUN_1800a39f0` → `FUN_1800a3324` → `FUN_180032dc8`) is the first backend stage.

The backend does **not** receive a label string or a fixed numeric vector. It pulls features on demand:
- `FUN_180032dc8` wraps the voice model (CHTSModelSetManagerAdapter, param_1[8]; optionally CHTSTransformModelSetManagerAdapter) and
  calls `FUN_1800a2bd4`.
- `FUN_1800afb28(model, …)` returns the model's list of **CTTSFeatureMeta** (0x100 bytes each), parsed from feature-name strings in
  the voice data. The grammar is `Location(.Location)*.Property` with optional functions, e.g. `Phone.PrevPhone.PhoneIdentity`,
  `Word.LastSyllable.LastPhone.PhoneName`, `Phrase.LastWord.IsFollowedByPunc`.
- `CTTSFeatureExtractionEngine` (vftable 0x1801714b8) `vt+0x18 = FUN_18005bfc0(fe, utt, metas, out, n)` → `FUN_180005248` per feature:
  - Pick the node list for the meta's level: phone/syll/word/pw/phrase/sentence as above.
  - Navigate each node through `node->vt+8(locationStep)`.
  - Read `node->vt+0x28(propId, &FeatureValue)`, falling back to `vt+0x20` custom features such as CCustomFeatureExtractorEnglish.
  - Apply up to 2 post-functions (meta+0x70 …) and append the 16-byte value to `out[i]` (a 0x20-byte growable array per feature).
- Features are then turned into decision-tree answers / NN inputs (backend; `FUN_1800a3430` when param_1[0x13b]).

Name tables:

| table | address | layout |
|---|---|---|
| Properties | 0x18016f280 … 0x18016fc10 | 24-byte entries {wchar* name; int id; int valueType (0 int/1 enum/2 string); int levelMask} |
| Locations | 0x18016fee0 … 0x180170240 | {name; level; offset −1/0/+1; …} (Phone, PrevPhone, NextPhone, First/Last…, Syllable…, Word…, Token…, ProsodicWord…, Phrase…, IntonationPhrase…, Sentence) |
| Functions | 0x180179050 / 0x180179190 | GreaterThan, SmallerThan, EndWith, IsInList, IsNumber, GetCharacter, InRange, Length, StartWithCapital, StartWith, GetNValue, ReplaceInvalidCharacter, IsContainList, AllCharactersInRange, LimitedNValue |

Level bits: 1 phone, 2 half-phone/dummy, 4 syllable, 8 word, 0x10 prosodic word, 0x20 foot, 0x40 phrase, 0x80 intonation phrase,
0x100 chunk, 0x200 sentence (from TTS_FEATURE_LEVEL_* order plus the masks).

Property ids: see the table dump. The ones that matter for HTS-style questions are PhoneIdentity 0, PhoneNumber 1, SyllableNumber 2,
WordNumber 3, PWNumber 4, PhraseNumber 5, IPNumber 6, Fw/BwPos* 7‥0x14, Stress 0x15, Accent 0x16, POS 0x17, POSTaggerPOS 0x18,
ToBIFinalBoundaryTone 0x19, Tone 0x29, BreakIndex 0x2a, PhoneName 0x2b, ToneLevel 0x2c, SentenceType 0x2e, IsFollowedByPunc 0x31,
Emphasis 0x4c, ToBIAccent 0x4f, IsAccented 0x50. The getter for every (level, property) is in the per-class tables listed in §3, so a
port can reproduce `GetFeature` exactly.

**Proposed dump format for the harness and for the backend port** (one record per phone, walking sentence+0xb0):
- the phone's id/name/stress
- its syllable (stress, ToBIAccent, accent), word (text, POS, POSTaggerPOS, BI, tone, emphasis, pause class, type), phrase and IP
  (boundary tone)
- sentence type/emotion
- positions/counts
- the SAPI word state (+0x90)

Better still, dump the exact `FeatureValue` arrays that `FUN_18005bfc0` writes (hook it: args utt, metas, out, n), plus the feature
names from each meta (+0x28 string), so the backend can be tested alone.

## 5. Hooks (64-bit harness)

| what | how |
|---|---|
| per-handler before/after | set engine+0x578 (via `FUN_18008ae80` or a direct write): `vt0(this, id, phase, utt)` |
| per-prosody-predictor | CLinguisticProsodyTagger+0x30, same signature |
| final linguistic features | hook `FUN_18005bfc0` (or CTTSFeatureExtractionEngine vt+0x18) |
| which prosody models loaded | after init, predictor+0x18 → runner+0x28 (CTTSSequenceHandler) → +0x10 count; the runner's list at +0x8/+0x10 holds {name, model*} pairs |
| sentence text/type | CTTSSentence +0x80/+0x88, +0xa8 |

## 6. Open items
- Where the engine+0x100 handler mask is set (**guess**: engine config/COM wrapper); for David the pipeline should be the handlers
  1-4, 7-9 plus streaming.
- The full word vtable semantics (many small int fields not yet named); the IP/segment list identity at sentence+0x1e8/+0x218/+0x248/+0x278.
- Rule details inside `FUN_180073c04` (punctuation → break inside the sentence), `FUN_18009ad24`, `FUN_18009aa04`, `FUN_18009a8b0`,
  `FUN_18009b3e4`, `FUN_18009a808`, and the ENU post-step `loc!FUN_18004003c`. These **are** the prosody of David/Zira and must be
  ported.
- Whether MSTTSEngine.dll (desktop Zira) matches the OneCore engine.

---

## 4. SAPI integration (fork D)

All addresses are VAs in `MSTTSEngine_OneCore.dll` 10.3.21207.0 (image base 0x180000000,
MD5 D7D84E2B439E4EDC0F691EFD2085F4FC, identical to `C:\Windows\System32\Speech_OneCore\Engines\TTS\`).
**guess** marks things I inferred but did not run.

### 4.0 Which engine does which voice token load? (important for the reference renders)

| token (registry) | display name | CLSID -> InprocServer32 | VoicePath / LangDataPath |
|---|---|---|---|
| `Speech\Voices\Tokens\TTS_MS_EN-US_DAVID_11.0` | Microsoft David Desktop | {179F3D56-1B0B-42B2-A962-59B7EF59FE1B} -> **System32\speech_onecore\engines\tts\MSTTSEngine_OneCore.dll** | `Speech_OneCore\...\M1033David`, `Speech_OneCore\...\MSTTSLocEnUS.dat` |
| `Speech\Voices\Tokens\TTS_MS_EN-US_ZIRA_11.0` | Microsoft Zira Desktop | {C64501F6-E6E6-451f-A150-25D0839BC510} -> **System32\speech\engines\tts\MSTTSEngine.dll** (v11.0.58.18, the OLD desktop engine) | `C:\Windows\Speech\Engines\TTS\en-US\M1033ZIR` (+ its own MSTTSLocEnUS.dat, 9 258 072 bytes, different from OneCore's 9 804 832) |
| `Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_{David,Zira,Mark}M` | Microsoft David/Zira/Mark | {179F3D56...} (OneCore) | `Speech_OneCore\...\M1033{David,Zira,Mark}`, `...\MSTTSLocenUS.dat` |

**Consequence:** `render.ps1 "Microsoft David Desktop"` exercises exactly the OneCore engine we mapped
(verified: bit-identical PCM to the harness below). `render.ps1 "Microsoft Zira Desktop"` does **not**:
it runs MSTTSEngine.dll 11.0 + `M1033ZIR.*` data. OneCore Zira via `ziratap zira` gives different
audio (370 764 vs 382 606 bytes for the same text). So `ref\zira_t1*.wav` are renders of the old desktop
engine, not the OneCore Zira. For OneCore Zira references use `harness\ziratap.exe zira ...` (SAPI5
with the Speech_OneCore token). The copies in `bin\` are byte-identical to the installed DLLs
(MSTTSEngine.dll 1 045 888 B v11.0.58.18; MSTTSEngine_OneCore.dll 1 953 792 B v10.3.21207.0;
MSTTSLoc.dll 557 056 B v11.0.58.18; MSTTSLoc_OneCore.dll 757 760 B v10.3.21207.0).

### 4.1 COM object

`CComObject<CTTSEngineCom>` (ctor 0x1800865fc; interface map at 0x1801795e0). Object layout (obj = IUnknown ptr):

| obj off | interface (IID) | vtable | methods |
|---|---|---|---|
| +0x00 | IMSTTSEngine {2d0fa0db-aea2-4ae2-9f8a-7afc7794e56b} (private) | 0x180175240 | QI 0x1800889e0, AddRef, Release, ... |
| +0x08 | ISpTTSEngine | 0x180175210 | **Speak 0x18008b210**, GetOutputFormat 0x18008aae0 |
| +0x10 | ISpObjectWithToken | 0x1801751e0 | SetObjectToken 0x180027040, GetObjectToken 0x18008aa90 |
| +0x18 | ISpEnginePronunciation | 0x1801751b0 | Normalize 0x18006b540, GetPronunciations 0x18008ab30 |
| +0x20 | {a9efb1bc-6b6f-46cd-a8ec-87a909f845a5} (private pronunciation API) | 0x180175188 | 0x18008abe0 |
| +0x28 | ISpProperties | 0x180175148 | SetPropertyNum 0x18008af70, GetPropertyNum 0x18008ac90, SetPropertyString 0x18008b020, GetPropertyString 0x18008ad50 |
| +0x30 | (non-COM helper) | 0x180175138 | 0x18008ae80 = **SetStageObserver(obs)**: swaps `CTTSEngine+0x578` |
| +0x70 | `CTTSEngine*` (0x708 bytes, ctor 0x1800728a8, vtable 0x18016f190) | | created in 0x18008a790 |
| +0x78 | `CTTSEngineSite<ISpTTSEngineSiteEx>` wrapper | | |
| +0x80 | `CTTSEngineSite<ISpTTSEngineSite>` wrapper (0x50 B: [0]=engine, [3]=SAPI site) | vtable 0x180175330 | |
| +0x88 | ISpObjectToken* | | |
| +0x98 | CRITICAL_SECTION serialising Speak | | |

`Speak` 0x18008b210 takes the object's critical section (one Speak at a time per voice instance),
calls lazy re-init 0x18008a884 (re-inits the engine when flag obj+0x148 is set), then
`0x1800637d0(siteWrapper, flags, fmtId, pwfx, frags, site)`:
* `fmtId == SPDFID_Text` -> returns S_OK immediately (no text-format output).
* requires `SPDFID_WaveFormatEx`; stores the SAPI site in wrapper[3];
* `0x18008b6e0` converts the SPVTEXTFRAG list to the internal fragment list (4.2);
* `0x18008df50` syncs the `<lexicon>` list collected from ParseUnknownTag frags (load via engine vt+0x10, unload vt+0x18);
* engine vt+0x20 (0x180095aa0 -> **CTTSEngine::Speak 0x180028288**).

`GetOutputFormat` 0x18008aae0 -> 0x1800642d0 (engine native format; trace shows 16 kHz 16-bit mono for David/Zira).

### 4.2 Token -> paths, Loc DLL

`SetObjectToken` 0x180027040 -> 0x180027cb4:
* token string `LangDataPath` (e.g. `...\en-US\MSTTSLocenUS.dat`), optional `LangUpdateDataDirectory`
  (servicing override: if present, the file name is re-rooted there, 0x18008a1f8/0x18005b1fc);
* `VoicePath` (e.g. `...\en-US\M1033David`, no extension), optional `VoiceUpdateDataDirectory`;
* `Attributes\Language` hex ("409") -> LangID;
* then 0x180027120(obj, langid, LangDataPath, VoicePath, 0, 0) = full init (engine ctor via 0x18008a790).
  On failure with an update directory it retries (token value `Reinitialize`).
* Voice INI = `VoicePath + ".INI"` (M1033David.INI), language INI `MSTTSLocEnUS.INI` next to the .dat
  (**guess** on exact composition; path strings `%s%s../%s/MSTTSLoc%s%s`, `%s%sMSTTSLoc%s%s` at 0x1800918b8).
* Loc DLL: 0x180077df8 builds `<engine dir>\MSTTSLoc_OneCore<suffix>.DLL` (suffix from 0x18014954c(langid)),
  falls back to `<engine dir>\MSTTSLoc_OneCore.DLL`; 0x180099a44 = `LoadLibraryW` + `GetProcAddress("GetLocaleHandler")`
  + `GetLocaleHandler(langid, &CTTSEngine+0x350)`. In the Loc DLL `GetLocaleHandler` 0x1800141f0 switches on
  LangID; 0x409 -> 0x1800199e0 (en-US locale handler). Locale handler vt+0xb0 is queried per component
  (e.g. sentence separator, 0x180028fa0) and returns E_NOTIMPL when the generic engine component is used.
* Trace at init (captured by ziratap): Loc Data, 6 domain .dat files (address/name/message/computer/media/companyname),
  Lexicon, POS Table, POS Tagger, Char Table, Pronouncer, Acronym Tagger, TN, NE Detector, Morph Lexicon, Word Breaker,
  Sentence Breaker, Linguistic Prosody Tagger, Unit Generator, Acoustic Prosody Tagger (David: "Window Length = 15,
  EnhanceRate = 1.0, Mean = 4.531177"), Unit Lattice Generator, Unit Selector, Wave Generator.

### 4.3 SPVTEXTFRAG -> internal fragment list

x64 SPVTEXTFRAG: +0 pNext, +8 SPVSTATE (eAction +8, LangID +0xC, EmphAdj +0x10, RateAdj +0x14, Volume +0x18,
MiddleAdj +0x1C, RangeAdj +0x20, SilenceMSecs +0x24, pPhoneIds +0x28, ePartOfSpeech +0x30, pCategory +0x38,
pBefore +0x40, pAfter +0x48), pTextStart +0x50, ulTextLen +0x58, ulTextSrcOffset +0x5C.

`0x18008b6e0` walks the list. For eAction Speak(0)/SpellOut(4)/ParseUnknownTag(6) the text is first copied
with every U+200B (zero-width space) removed (0x18008c26c). ParseUnknownTag frags are only examined for
`<lexicon uri="..." type="..."/>` (0x18008c6a8, strings at 0x180184ea8..) and are otherwise dropped. Every other
frag becomes a 0x88-byte node, state converted by **0x18008bb98**:

| node off | meaning |
|---|---|
| +0x00 | action: 0 speak, 1 silence, 2 pronounce, 3 bookmark, 4 spell-out, 5 section, 8 other (SSML path also uses 6 start-sentence, 7 start-paragraph; names from trace 0x18007677c "TA_*") |
| +0x04 | LangID (u16; set from engine LangID, not from the frag) |
| +0x08 | emphasis: SAPI EmphAdj != 0 -> 1 (= EW_STRONG). Values 2 moderate, 3 none, 4 reduced, -1..-7 = EB_* break strengths (SSML path; trace 0x18007957c) |
| +0x0C | silence ms (action 1: SilenceMSecs) |
| +0x20 | say-as struct {InterpretAs, Format, Detail}; from SAPI only InterpretAs = copy of Context.pCategory (pBefore/pAfter ignored) |
| +0x28 | prosody struct (0x50 B) only if MiddleAdj!=0 or RateAdj!=0 or Volume!=100: float +0x08 = MiddleAdj, float +0x28 = RateAdj, float +0x3C = Volume. **RangeAdj is ignored.** (sub-records {SsmlAttribute, Number, NumberPercent, Unit} dumped by 0x1801496bc as Pitch/Rate/Volume) |
| +0x30 | pronounce: phone list converted from pPhoneIds (0x18008b8f8) |
| +0x38 | POS (u16, 0xFFFF = none): ePartOfSpeech mapped via engine phone/POS converter vt+0x18 |
| +0x68/+0x74/+0x70 | text ptr / length / source offset (after 0x18008d958 trims leading/trailing whitespace of each frag and adjusts the offset) |
| +0x78 | owned text copy; +0x80 next |

The internal list is dumped by 0x180028da4 ("<Fragments>", "[TTS] InputText", "[LangID", "[Duration", "[SayAs:",
"[Prosody"). SSML-only customs are parsed elsewhere (0x18005a348: `mstts:SpeakRate`, `mstts:spectrum`,
`mstts:echosetting`, ...; "MSPromptMapping" 0x18004dc20, "SayAsMapping." 0x1800518c0) - not reachable from SAPI5 XML.

### 4.4 CTTSEngine::Speak (0x180028288) - per-sentence driver

1. dumps fragments; logs `VoiceLookUpPath[i]`;
2. voice switching / domain selection per fragment (0x1800945d0, 0x1800944b8, 0x180094804, action 8 frags);
3. 0x180094224 prepares the output (site, format); optional fragment rewriting 0x1800ddc1c (engine[0xd1]) and
   0x180094d78 (engine[0xcd]); 0x180066f30; 0x18007186c;
4. 0x180094904 creates the handler list (`pTVar13`, array of ITTSHandler*) and the sentence enumerator
   (`pvVar12+0x10`); every handler gets `Begin` (vt+0x10);
5. loop: enumerator vt+0x10(&flags) (flags&1 = done) -> new utterance (0x180079ce4, ITTSUtterance/CTTSUtterance),
   0x18006ff8c (domain flag utt+0x754), then **for each handler**:
   `id = h->vt[1]()`; `obs = engine+0x578`; `if (obs && obs->vt[0](obs,id,0,utt)==1) skip`;
   `h->vt[3](h, utt)` (= Process); `obs->vt[0](obs,id,1,utt)`;
   CTTSMetaDataHandler handlers handle bookmark/metadata flags; if `engine[0xd5]` (parallel/streaming) 0x180094a2c runs
   extra handlers (engine+0x1c8 list) on threads (CreateThread, WaitForMultipleObjects);
6. handlers `End` (vt+0x20); trace `[TTS] WaveTime = %u` ms.

Observed handler ids and order per sentence (ziratap, David and Zira identical):
`0x40000 CTextProcessor` -> `0x80000 CLinguisticProsodyTagger` -> `0x100000 CTTSUnitGenerator` (contains a
nested `0x100004` sub-stage) -> `0x4000000 CAcousticProsodyTagger` -> `0x3800000` (unit lattice + selector +
wave generator composite, **guess** from the bit pattern). The text processor runs once more at the end and
returns "no more sentences". The "Hello world. ... AM. Is it raining?" test gave 3 utterances
("Dr." and "AM." did not split).

### 4.5 Rate / volume / pitch

* SAPI global rate (`ISpTTSEngineSite::GetRate`) and per-frag RateAdj end up as the integer property
  `MSTTS.SpeakRate`; used in 0x18004dd00 (wave generator) and 0x18006cda8 (duration scaling):
  `r = clamp(rate,-100,100)`; `f(r) = r>0 ? 1 + r*0.05 : 1 + r/120` (0x18004e41c; constants 0.05 @0x180193e44,
  120 @0x180181060); for r>0 the factor is softened by `VoiceSetting.MSTTS_SpeakRate_NormalFactor` (INI
  `[VoiceSetting] MSTTS_SpeakRate_NormalFactor = 63` for Zira): `factor = 1 + (f-1)*NF/100`.
  **guess:** the SAPI -10..10 rate is scaled by 10 before this (not traced).
* `ISpTTSEngineSiteEx` (Windows.Media) path: action flag 0x10 -> double speaking rate via SiteEx vt+0x28,
  clamped with NormalFactor (0x18006d3b0). Not reachable from SAPI5.
* Per-voice `[Domain] RateAdjustmentN`, `[EmotionRecipe]` (Rate/Pitch/PitchRangeScale/VolumeAdjustment) are read
  in 0x180017xxx ("%s.%s%d" keys) - SSML `mstts:express-as` style; not reachable from SAPI5 XML.
* Where pitch (`MSTTS.Pitch`) and volume are applied: acoustic prosody tagger / wave generator (backend,
  lines ~77227, 133325 in _all.c) - see notes/backend.md.

### 4.6 ISpTTSEngineSite use and events

Wrapper vtable 0x180175330 maps the engine's internal site calls to SAPI:
`[0] AddEvents, [1] GetEventInterest, [2] GetActions (0x180051340), [3] Write, [4] GetRate, [5]/[6] SiteEx-only (QI),
[7] GetVolume, [8] GetSkipInfo (returns "skip requested" flag), [9] CompleteSkip, [10] SiteEx QI +0x58`.

Events are built per utterance by the `CSAPIEventHandler` embedded in `CTTSUnitGenerator` (ctor 0x18009c9b8,
object +0xC0), from `CTTSUnitGenerator::Process` 0x180034b00 -> 0x18009db84:
* 0x180033f34: SPEI_PHONEME (6) and SPEI_VISEME (8) per phone, using the phone-converter table
  (entries of 13 u16: internal phone id, up to 7 viseme bytes, SAPI phone-id string). Language-specific
  "silence" id used as default next-phone: 7 for 0x409 (SAPI en-US "_").
  `VoiceSetting.TtsPhonemeEvents` (0x18009dd50) switches to native phone ids.
* 0x18003358c: SPEI_WORD_BOUNDARY (5) per word: lParam = word+0x270 (source char offset), wParam = word+0x274 (length).
* 0x18009dbe4: SPEI_SENTENCE_BOUNDARY (7): lParam = utt vt+0x40 (offset), wParam = utt vt+0x50 (length).
* Audio offsets are filled when the wave is written (events attached to units, **guess** on the exact function).

Observed (ziratap, David, 16 kHz):
```
EVENT id=7 off=0     wParam=12        lParam=0     sentence "Hello world." (pos 0, len 12)
EVENT id=6 off=0     wParam=6553626   lParam=7     PHONEME '_' dur 100 ms, next=26 (h)
EVENT id=8 off=0     wParam=6553612   lParam=0     VISEME 0 dur 100 ms, next=12
EVENT id=5 off=3200  wParam=5         lParam=0     word "Hello"
EVENT id=6 off=3200  wParam=4587541   lParam=26    h 70 ms, next 21 (eh) ... l(31) ow(35); w(46) er(22) r(38) l(31) d(19)
```
PHONEME: lParam = SAPI en-US phone id, wParam = duration_ms<<16 | next phone id. VISEME: lParam = viseme,
wParam = duration_ms<<16 | next viseme. lParam high word (SPVFEATURE stress/emph) was 0 in all observed events.

## 5. Nondeterminism, threading, state

* **Empirically deterministic.** Same text rendered twice in separate processes -> identical files (David
  Desktop = OneCore, and old-engine Zira Desktop). Same SpeechSynthesizer: text A, then A+B, then A again ->
  PCM of A identical all three times. ziratap (David) output is bit-identical to render.ps1. Two ziratap Zira
  runs identical.
* `rand()` only in the backend (vocoder/excitation noise: 0x18000adc0, 0x18000b3dc, 0x180060d58, 0x18010db2c);
  `srand(0x406)` in 0x18006b550 (fills a 1024-entry Gaussian table via Box-Muller at init) and 0x1801100b0.
  UCRT rand state is per thread; the table is built at init, so later rand() draws depend on how many were
  consumed on that thread before -> the backend port must replicate rand (MS LCG 214013/2531011) and the
  call order. Observed determinism across Speak calls suggests the per-sentence consumption re-seeds or the
  draws are made on a fresh thread; **verify in the backend mapping.** No rand in the text frontend.
* Time: `GetSystemTime` at 0x180056064 / 0x18009f0e0 = cache aging (LexiconCache.DropTime-style eviction,
  threadpool timers 0x1800bd934) - affects memory only (**guess**: never output). `QueryPerformanceCounter`
  only in CRT security-cookie init (0x18007c73c).
* Threads: `Pipeline.ParallelProcess` / `Pipeline.EnableStreaming` (0x180072xxx, 0x180078333) enable the
  threaded handler path 0x180094a2c; `Pipeline.LatticeGeneratorThreadNumber`, `Pipeline.UnitSelectorThreadNumber`
  and `NN.PredictorThreadNumber` spawn workers via `_beginthreadex` 0x18011a03c (CSpTaskQueue). None of these keys are
  in the David/Zira INIs (defaults apply). Frontend stages run on the SAPI speak thread, sequentially per sentence.
* Shared state: models are cached process-wide by name (e.g. "SENTSEP_en-US") under the critical section at
  0x1801c0dc0 (0x18007b43c); lexicon cache (CPLSLexiconCache) holds `<lexicon>`-loaded PLS lexicons across Speak
  calls; user/app lexicon (CSAPIUserAppLexicon) via SAPI. No per-sentence state was observed to leak into
  later audio (test above).

## 6. Hooking plan (64-bit) - implemented in `harness\ziratap.c`

* Load path: plain SAPI5 in a 64-bit process: `SpObjectToken::SetId(HKLM\...\Speech_OneCore\Voices\Tokens\MSTTS_V110_enUS_DavidM)`
  -> `ISpVoice::SetVoice` -> output `ISpStream` over `CreateStreamOnHGlobal` (16 kHz/16/mono). `LoadLibraryW` the
  System32 engine DLL first so hooks are in place before SAPI instantiates it.
* Hook 1 (free trace): the logger `0x180029190 Log(level, fmt, ...)` begins with a 15-byte register-spill
  prologue; overwrite with `jmp [rip]` to a variadic replacement that `_vsnwprintf`s the line. The original only
  formats and `EventWrite`s to ETW provider {9502132b-fbe0-4f27-9165-6dc8232a2b67}
  (Microsoft-Windows-Speech-TTS-OneCore; levels 0..4 -> event ids 16/8/4/2/1, keyword 4). The gate at
  0x1801c0aa0 is only the ETW REGHANDLE (always set), so all strings are always formatted. ETW capture without
  hooks needs admin (`logman ... -ets` returned Access denied).
* Hook 2 (per-stage): patch ISpTTSEngine vtable 0x180175210 slot 3 (Speak). In the wrapper,
  `engine = *(this+0x68)`, set `*(engine+0x578) = &observer` (same effect as helper 0x18008ae80). The engine calls
  `observer->vt[0](observer, handlerId, phase, utt)` before/after every handler: this is the per-stage capture point;
  `utt` is the CTTSUtterance* (layouts: section on data structures). Returning 1 in phase 0 skips a stage (e.g.
  stop after 0x80000 to capture only the frontend output).
* Other hook points: handler Process entries CTextProcessor 0x1800b5110, CLinguisticProsodyTagger 0x180060010,
  CTTSUnitGenerator 0x180034b00, CAcousticProsodyTagger 0x1800a3324/0x1800a39f0; fragment conversion 0x18008bb98;
  event build 0x18009db84.
* Verified run: `ziratap.exe david "@det.txt" out.wav` -> init trace, fragment dump, STAGE lines, SAPI events;
  out.wav bit-identical to `render.ps1 "Microsoft David Desktop"`. Build: `harness\build_ziratap.bat` (VS BuildTools x64).
  Note: sapiddk.h does not compile as C, so SPVTEXTFRAG is re-declared in ziratap.c.
