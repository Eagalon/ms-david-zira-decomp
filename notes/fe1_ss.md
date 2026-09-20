# zf1 sentence separation (fork D): CSentSepImpl + CSentenceEnumerator piece loop

Engine: MSTTSEngine_OneCore.dll 10.3.21207.0 (x64). Port: `src/zf1_ss.c`, `src/zf1_ss.h`, generated table
`src/zf1_ss_tab.h` (by `tools/gen_zf1_chartab.py`), test driver `src/zf1_t_ss.c`, harness
`harness/zftap1_ss.c` (+ `build_zftap1_ss.bat`), tests in `tests/fe1/ss/`. Clean-room: transliterated from the
Ghidra decompilation (`decomp/MSTTSEngine_OneCore/_all.c`) and checked at runtime; no Microsoft source used.

## 1. Which separator runs for en-US

`CSentenceEnumerator::Init` (0x180028fa0): the locale handler (vt+0xb0) returns E_NOTIMPL, the CRF separator
(`CCRFSentSepHandler`, model 9b4ece4f/0d5c0d43) is absent (0x8004801A), so the engine makes a **CSentSepImpl**
(0x1800293d4, vtable 0x18016d758) and loads the shared model "SENTSEP_en-US" (0x18007b43c -> parser 0x180047748,
resource e67ab014/1df28780, object **CSentSepInfo**). CSentSepImpl members: +0x08 model (CSentSepInfo),
+0x18 the CCharTable (f6e4f50a/80b9a5a3), +0x20 result length (vt+0x10), +0x24 hard-end flag (vt+0x18);
vt+0x20 clears both.

CSentSepInfo word lists (vtable slot -> field -> list index in the file):

| vt | field | file list | contents | used by |
|---|---|---|---|---|
| 0x00 | +0x28 | 4 | 173 sentence-initial capitalised words (About, According ...) | "capitalised word after '.'" test (0x180161624) |
| 0x08 | +0x38 | 5 | empty | 0x1801616b0 (always "not found" for en-US) |
| 0x10 | +0x48 | 2 | conjunctions and/but/either/neither/nor/or | state -2 sub 0x19 (skip a conjunction after ':' + blank) |
| 0x18 | +0x58 | 6 | digit words zero..nine | 0x1801617e4 |
| 0x20 | +0x68 | 0 | 2381 abbreviations | 0x180161120 abbreviation test, tokenizer 0x14 state |
| 0x28 | +0x78 | 1 | Bible books | tokenizer 0x32 state (type 6) |
| 0x30 | +0x98 | 3 | ambiguous abbreviations (Apr. Is. Jr. ...) | state -2 sub 0x28 |
| 0x38 | +0x88 | 7 | numeric prefixes fig. no. sect. | 0x180161740 |
| 0x40 | +0xa8 | 10 | titles Adm. Capt. ... | tokenizer 0x14/0x32 states (type 5 / 7) |
| 0x48 | +0xb8 | 8 | c r sm tm | (not used by the separator) |
| 0x50 | +0xc8 | 11 | ed ing n't s | suffix list for "(s)" after an emoticon/word match (0x18003f9e4) |
| 0x58 | +0xd8 | 9 | 280 emoticons | tokenizer prefix match (0x18003f9e4) |
| 0x60 | - | - | returns 0 | tokenizer (cVar19 = 0 -> "letter case switch" mode off) |
| 0x68 | +0x24 | - | LangID 0x409 | many `(lang & 0x3ff) == 7/10/0x15/...` rules: all off for English |

All lookups are binary searches over the lists as stored (u16 code-unit order): exact (0x180061864, the entry must
end where the key ends) or longest-prefix (0x18003f9e4, the match must be followed by a char that is not
alphanumeric and not '_', minimum length argument, optional "(suffix)" continuation from list 11).

## 2. vt+8 = FUN_18005d050 (zf1_ss_run)

1. Skip leading chars that are blank-like (0x180072d30: class "space" or 0x01-0x1f, 0x7f-0x9f, U+202F, U+205F,
   U+2060, U+2420, U+2422-2424) or line breaks (0x180079ea4: LF VT CR U+008D), at most 500. 500 skipped -> length 500,
   not hard.
2. Run the state machine on the rest (state object ~0x320 bytes, init 0x180073fa0, run 0x180073970). The result
   length is +0x2ec (set by the finish step 0x1800686e0 = start of the token where the machine stopped, minus
   trailing blanks/line breaks), plus the skipped prefix.
3. Length 0 -> 1 (if the text is not empty). Length > 500: if nothing was skipped, cut after the last word that ends
   before index 500 (scan back from 499 over non-blanks, then over blanks; UCRT iswspace or line break), or 500 if
   no blank; if a prefix was skipped the length becomes the prefix length (engine quirk). Not hard in both cases.
4. Otherwise hard end = state+0x310 (a sentence-final token was accepted) || state+0x314 (a line break was read).

The CSentenceEnumerator piece loop (0x1800624e0, `zf1_ss_next`) calls it on the rest of each text fragment
(actions 0 speak, 4 spell, 9) and keeps adding pieces until the hard flag is set, a fragment of > 499 chars is
met, the sentence would exceed 500 chars (then the piece is left for the next sentence), or an SSML sentence /
paragraph fragment (action 6/7) follows. Say-as "address" and "name" fragments are taken whole (0x1800b682c).
Non-text fragments (silence, bookmark, pronounce ...) are simply included in the current sentence.

## 3. Tokenizer (FUN_18003dbc0, next-token wrapper FUN_18003da24)

The state keeps three tokens: current +0x98, previous +0xb8, the one before +0xd8 (record: base ptr, type +8,
start +0xc, len +0x10, flags +0x14, end flag +0x18); +0xf8 = current type, +0xfc = previous type.
Character classes come from the engine's own tables (`zf1_ss_tab.h`): a 256-entry Latin-1 ctype table
(1 upper, 2 lower, 4 digit, 8 space, 0x10 punct, 0x20 control, 0x40 letter, 0x80 vowel), a 64K class table for
chars >= 0x100 (0x100000 upper, 0x200000 lower, 0x400000 digit, 0x800000 space, 0x10000000 letter), a Latin-1
base-letter table, plus UCRT iswdigit/iswspace bitsets (probed with `tools/ucrt_ctype_probe.c`).

| type | token |
|---|---|
| 1 | run of blanks (not line breaks) |
| 2 | run of U+E800/U+E801 |
| 3 | word: letters/digits with inner '.', '-', apostrophes, "(s)"; surrogate pair; URL/emoticon matches (flags 0x41) |
| 4 | number-like word (digits then '.'/','/':'/'-' groups; flag 2 = has digits) |
| 5 | abbreviation (list 0 / title list match after a '.'), 6 Bible book, 7 title (+"A.B." shapes) |
| 8 | "..." (exactly three dots), 9 other dot runs / spaced ". . .", 0xc single/double dot |
| 0xa / 0xb | opening / closing bracket or quote mark ( ( [ { U+2018 U+201C U+300C ... ) flags 0x10/0x20 |
| 0xc | sentence punctuation ! ? U+2026 U+203C U+061F ... and 1-2 dots |
| 0xd | quote: ' " U+2018-201F U+0091-0094 U+00AB U+00BB ... |
| 0xe | , / : ; |
| 0xf | other symbol, or NUL; 0x10 line break (CRLF/LFCR = 2); 0x11 end of text; 0x12 emoticon shape (":-)", ";)", "8)"); 0x13 CJK full stop (U+3002, U+FF01, U+FF1F, U+FF61, U+0589, U+0964) |
| 0x1a | inverted ? ! ; 0x1b # % & * @ \ | § ° ...; 0x1c bullets; 0x1d math; 0x1e currency; 0x1f other apostrophe; 0x20 dashes |

Token-level flags: 0x40/0x41 = matched emoticon/URL prefix list, 4 = contains an apostrophe, 8 = "A.B." all caps.
Counters kept by FUN_18003da24: +0x2fc words, +0x300 word chars, +0x304 other chars, +0x308/+0x30c ';' handling,
+0x314 line break seen.

## 4. State machine (states are the return values; -7 = stop)

- -1 (0x1801623e0) sentence start: skip blanks, open brackets (pushed on the bracket stack at +0x100, max 50),
  count opening quotes (+0x298 counters: double quotes, single quotes, guillemets); number/list-item openers
  "1." / "(a)" / "iv." are tried with a saved snapshot (0x180162738 / restore 0x180161e84).
- -2 (0x180064630) inside a sentence: words (3..7) reset +0x310; '.'/'!'/'?' (0xc) -> +0x310 = 1 and state -3;
  numbers -> -3; abbreviations (type 5/7/6) go through sub-states 0x1e/0x28/0x3c/0x50 which look at the next token
  (lower-case word, digit, numeric prefix "No." + number, ambiguous abbreviation + capitalised starter word ...) to
  decide whether the abbreviation ends the sentence (+0x310 = 1, stop) or not (continue); ':' + blank + conjunction
  handling (0x14/0x19); initials "J. R." (sub 0xf); closing brackets pop the stack.
- -3 (0x180161a1c) after sentence punctuation: one blank then anything other than more punctuation ends the sentence
  (-7) unless a double quote is still open (-4) or a bracket is open (-5); several blanks end it immediately.
- -4 (0x180161ff8) inside quotes after punctuation, -5 (0x18016225c) inside brackets, -6 (0x180161e00) after a CJK
  full stop.
- finish (0x1800686e0): the sentence ends at the start of the current token (+0x2e8), trailing blanks removed
  (+0x2ec).

## 5. Porting notes

- The state object is emulated as a word array addressed by the engine's byte offsets, so every function is a
  line-by-line transliteration (goto structure kept). The only language-dependent branches kept are the English
  ones (LangID & 0x3ff == 9); branches for 7 (German), 10 (Spanish), 0xc, 0x12 (Korean), 0x15, 4 ... are removed
  where they are statically dead for 0x409 and noted in comments.
- The tokenizer may read `text[len]` (the character after the piece) in two places ('.' between alphanumerics,
  "No." check); the enumerator passes fragment text in place, so callers must keep `text[len]` readable and equal to
  the engine's (0 for a 0-terminated fragment copy).
- `_wcsnicmp` / `tolower` / `toupper` are the UCRT "C" locale versions (ASCII-only folding); iswdigit/iswspace are
  the UCRT Unicode tables (probed).

## 6. Verification (harness/zftap1_ss.exe; tests/fe1/ss)

- direct mode (`zftap1_ss.exe david lines.txt out direct`: the real CSentSepImpl instance is called on every line,
  repeatedly over the rest of the line like the enumerator does; `cmp.sh`):
  corpus 375/375 lines (396 calls); `edge.txt` 125/125 (245 calls, incl. 480..1200-char lines);
  `gen_stress.py` seeds 1-6: 18000/18000 lines (217,916 calls); `gen_fuzz.py` character fuzz seeds 11-13:
  59,996/59,996 lines (139,070 calls) + 800 long concatenations (27,682 calls).
- Speak mode (every CSentSepImpl call made by the engine's own enumerator during ISpVoice::Speak, logged with the
  real following character; `replay.py DUMP` re-runs them through `zf1_t_ss.exe ... replay`): corpus 449/449,
  stress1 16,077/16,077, fuzz1 37,840/37,840, long fuzz 19,473/19,473, edge 236/236, XML 3,587/3,587,
  stress3 (1000 lines) 5,462/5,462 calls identical.
- Enumerator (`zf1_ss_next` vs the sentence start/end fragment positions returned by the engine's
  CSentenceEnumerator::Next, hooked at vtable 0x175d58 slot 3, `enumtest.py DUMP`): corpus 378/378 Speak calls
  (783 sentences), edge 125/125 (360), random XML with silence/bookmark/spell/pron/context address,name,date
  fragments 573/573 (4,047), stress3 1000/1000 (6,462), char fuzz 991/991 (2,889; the 9 other lines are
  rejected by SAPI's XML parser and never reach the engine).

Total: all calls identical, 0 known mismatches.

How to rerun: `harness\build_zftap1_ss.bat`; `src\cl64.bat /nologo /O2 /W3 /Fo..\build\ss\
/Fe:..\build\zf1_t_ss.exe zf1_t_ss.c zf1_ss.c zf1_dat.c zf1_util.c`; in tests\fe1\ss: `./cmp.sh LINES.txt`
(direct), `zftap1_ss.exe david LINES.txt D.dump` then `python replay.py D.dump` and `python enumtest.py D.dump`.
Generators: `gen_stress.py N SEED OUT`, `gen_fuzz.py N SEED OUT`, `gen_xml.py SRC OUT SEED`.

## 7. Integration notes for the coordinator

- Per Speak: build the engine fragment list (as 0x18008b6e0 does: U+200B removal, whitespace trimming of say-as
  fragments, SAPI action -> node action), then call `zf1_ss_next` repeatedly; a sentence = fragments from start
  to end position (the end fragment is also the next sentence's start fragment, continuing at end.pos).
- `text[len]` must be the character that really follows in the engine's buffer: for a fragment pointing into the
  SAPI text this is the next source character (not 0); for a U+200B-stripped copy it is 0; for a trimmed say-as
  fragment it is the first trimmed-off character (`enumtest.py` reproduces this and matches 100%).
- The separator is stateless across calls (read-only model), so one `zf1_ss` can serve every engine instance.
