# zf1: OneCore en-US text frontend, first half (text -> sentences -> words with pronunciations)

Portable C99 port of the part of `MSTTSEngine_OneCore.dll` (10.3.21207.0) that runs inside
`CTextProcessor::Process` (handler 0x40000): SAPI fragments -> sentence separation -> fragment walk / word
breaking -> named entities + text normalization -> POS -> pronunciation -> punctuation / quotes / parallel
structures.  David and OneCore Zira share this code and data (`MSTTSLocEnUS.dat`); verified: the harness dumps
of the whole corpus are identical for both voices (except an uninitialised field of the empty last utterance).

Component notes written by the sub-agents: `fe1_pron.md` (lexicon, LTS, morphology, CPronouncer),
`fe1_tn.md` (transducer network, NE, TN), `fe1_pos.md` (POS tagger, CRF homographs, CPolyphony),
`fe1_ss.md` (sentence separator), `fe1_post.md` (sentence type, rules, quotes, parallel structures).

## 1. Stage boundary (what "bit-exact" is measured on)

The engine calls an observer at `CTTSEngine+0x578` before and after every handler
(`vt[0](obs, handlerId, phase, utt)`, see frontend.md §1).  **zf1 output = the CTTSUtterance as it is at
`handlerId == 0x40000, phase == 1`** (end of CTextProcessor::Process for one sentence, before
CLinguisticProsodyTagger 0x80000).  At that point the sentence (`utt+0xe0`) has its word list (`+0x110`) and
also syllable/phone lists (`+0xe0`/`+0xb0`, built by sentence vt+0xa0 = FUN_18001a644) — those belong to zf2;
zf1 delivers the words, including the SIL words that FUN_18001a644 inserts in its first pass.

`harness/zftap1.exe david|zira corpus.txt dump.txt [full] [log] [hooks]` (build: `harness/build_zftap1.bat`)
installs that observer, speaks every corpus line with `ISpVoice::Speak(SPF_DEFAULT)` (so a line starting with
'<' is SAPI XML) and returns 1 for every later handler (the backend is skipped: 375 lines in < 1 s).
Per line it writes:

```
L <lineno>\t<text>
F act= emph= rate= vol= pitch=m/r sil= pos= cat= before= after= ph= off= len= "text"   SAPI SPVTEXTFRAGs
S off=<+0xa0> len=<+0xa4> type=<+0xa8> emo=<+0xac> lists=<phones,sylls,words>
W text="" u80= pos=<+0x138> tpos=<+0x13a> i84 i88(type) i180 i210(silence ms) i214 i228 ... i36c
  sXXX="" (every CTTSString member != Text, by offset) prons=[*current|other...] (phone-id strings)
  fs=<action>,<lang>,<emph>,<silence>,<pos hex> [pro=pitch,rate,volume] [sayas=""] fso=<src off>,<len>
  grp=<+0x2e8 object id> ap=<+0x2b0 word index> ne=<+0x1a8 segment: 1 first word, 2 other>
```
With `hooks` it also logs `TN` (CTextNormalizer vt+0x18 Normalize in/out) and `WB` (CWhiteSpaceBreaker vt+8
input/tokens) lines.  zf_word (src/zf.h) mirrors every dumped field; `src/zf1_main.exe` writes the same format
and `tests/fe1/compare.py ENGINE PORT [-f fields] [-x fields]` compares them line by line.

## 2. Pipeline (engine functions -> C)

| engine | what | C |
|---|---|---|
| sapi.dll | SAPI XML -> SPVTEXTFRAG | zf1_frag.c `sapi_xml_parse` (same behaviour as the Anna port; XML only when the text starts with '<', like SPF_DEFAULT) |
| 18008b6e0 / 18008bb98 / 18008c26c / 18008d958 | fragment nodes: U+200B removed (actions 0/4/6), action 6 dropped, SAPI POS converted (noun 3, verb 8, modifier 11, function 32, interjection 38), prosody struct only if pitch/rate/volume differ from 0/0/100, ASCII-blank trim of say-as fragments | zf1_frag.c `build_nodes` |
| 1800624e0 (CSentenceEnumerator) | sentence spans over the nodes of one Speak call; text actions 0/4/9 go through CSentSepImpl unless the say-as is "address"/"name"; 500-char cap | zf1_ana.c `zf1_enum_next` + zf1_ss (fork D) |
| 180062254 + loc!18000be20 | sentence buffer (<= 500 chars) + ENU normalisation (fullwidth ASCII, NBSP/U+2002.. -> ' ') | zf1_ana.c `build_sbuf`, `lta_normalize` |
| 1800c51cc | fragment walk: text / silence / pronounce / bookmark / spell; trailing-blank trim of a text piece only when the piece equals the buffer tail | zf1_ana.c `walk` |
| 180043cd0 (CWhiteSpaceBreaker) | tokens (see §3) | zf1_wb.c |
| 180071b70 / 180062900 / 1800c4ab4 / 18006e874 | tokens -> words; plain tokens with a digit become "sp:default" entities; quote normalisation in Text; CaseInsensitiveText = towupper ("C" locale: ASCII only) | zf1_ana.c `sink_to_words` |
| 1800c7914 | <spell>: char table (f6e4f50a) pron -> type-4 word, name -> words, else main-lexicon entry of the char, else the char itself | zf1_ana.c `spell_piece` |
| 1800c7838 / 1800c6d3c | <silence> (type 3, silence ms), bookmarks (attached to the next word: +0x2f0/+0x2f8) | zf1_ana.c |
| loc!180028730 | ENU hook: "*word*" emphasis | zf1_ana.c `lta_stars` |
| 18006603c | POS tagging | zf1_pos (fork C) |
| 180018ed4 | acronyms + TN expansion | zf1_pron (fork A) / zf1_tn (fork B) |
| 1800bb3e0 | punctuation rules (type 1, i180) | zf1_post (fork E) |
| 1800479e0 | CPronouncer | zf1_pron (fork A) + zf1_pos (fork C: polyphony) |
| 1800bd64c | commit: sentence src span = first..last type 0/1 word | zf1_ana.c `commit` |
| 180063378 | +0x2bc on the first word with a pronunciation when the sentence starts the Speak call, +0x2b8 on the last one when it ends it | zf1_engine.c |
| 18005c794 tail | sentence type, suffix step, quotes, parallel structures | zf1_post (fork E) |
| 18001a644 (1st pass) | SIL word (100 ms, BI 5, pause class 7) before the first word with a pronunciation; SIL words after words with +0x214 | zf1_modules.c `zf1_sentence_finish` |

## 3. Word breaking (CWhiteSpaceBreaker) — 100% (676 engine calls on the corpus + 41 stress lines)

Resource 629aa5c4 id 9756c4e5 (the 4th id the engine tries): three sorted u32 character tables (skip, split,
trim) and two CVocabTrie blobs.  Algorithm (FUN_180043cd0 -> 180076454 / 180043ee8 / 180044194):
1. at each position, longest match in trie 0 (abbreviations such as "st.", emoji sequences): accepted when
   the match does not cover the whole remaining text (the engine calls with flag 1) and the character after
   the match or its last character is a skip/split character; else a match in trie 1 (emoticons, "I ll", ...)
   that covers the whole remaining text;
2. otherwise a skip character is dropped, a split character is a token of its own, and anything else runs to
   the next skip/split character; that chunk loses one leading and one trailing trim character (' - U+2010
   U+2018 U+2019 U+2032 U+FF07) as separate tokens, except the English possessive "...s'" / "...S'".
CVocabTrie: threshold-coded node references into a {char, flags} table; flags: 1 terminal, 2 last sibling,
0x200 continue with next group, 4 value follows, 0x10 has children, 0x1c0 child addressing (0 relative,
0x40 inline, 0x80 via table T7, 0x100 24-bit offset), 0x1d0 child-reference encodings.  `tools/vocabtrie.py`
dumps both vocabularies (5511 / 3097 entries).

## 4. Integration details found while wiring (coordinator)

- SAPI (SPF_DEFAULT) treats text as XML when the first non-blank character is '<'; plain text loses its leading
  blanks (ASCII + U+200B), not its trailing ones.  An end tag that closes nothing, or an unterminated '<...' tag,
  makes sapi.dll reject the whole Speak (no fragments); a mismatched end tag just closes the innermost element.
- The engine copies fragment text only when it contains U+200B; otherwise the node points into the SAPI text, so
  the character after a fragment (read by the sentence-separator tokenizer) is the next source character.  The
  C nodes keep that character at text[len].
- Entity token POS: FindNext's POS attribute; digit tokens turned into "sp:default" entities get the POS table
  default 50 (vt+0x38).
- +0x2bc / +0x2b8 go to the first / last word that has a (non-empty) pronunciation, only when the sentence starts
  at the first text fragment's start (or at the list head) / ends at the end of the last text fragment
  (FUN_180063378, enumerator +0x40/+0x48/+0x50).
- <silence> and a trailing bookmark create type-3 words with pron "-SIL-" (id 3); letters from <spell> are
  type-4 words with the char-table pron and i278 8.
- Output convention: an empty string is NULL (like the engine's CTTSString); zf2 relies on it.
- CharLowerW keeps U+0130; towupper/towlower are the "C" locale (ASCII only).
- Domain files enUS.<Domain>.dat are read from the folder of the main .dat (zf1_open path, or ZF1_DATDIR).
- The engine renders text after <lang langid="409"> with David even when Zira is selected: a text->audio
  driver must pick the voice per Speak group (zf1 itself is voice independent).

## 5. Status (David dumps; Zira's frontend output is identical)

`tests/fe1/run_all.sh` (all fields of every word and sentence, harness vs port):

| set | lines | identical |
|---|---|---|
| corpus.txt (prose, homographs, numbers, dates, times, currency, phones, addresses, URLs, acronyms, quotes, LTS, compounds, SAPI XML) | 375 | 375 |
| big/prose.txt (Python docs paragraphs) | 1200 | 1200 |
| big/misc.txt (homographs, quote/list lines, sentence-split edge cases, address lines, TN stress) | 1131 | 1131 |
| big/xml.txt (random SAPI XML incl. malformed) | 600 | 600 |
| big/stress.txt (sentence-separator stress) | 600 | 600 |
| big/fuzz.txt (character fuzz) | 1500 | 1500 |

End to end with zf2 (`tests/fe1/e2e.py`, feature matrices vs harness/zftap2): David corpus 375/375, David prose
1200/1200, Zira corpus 373/375 (the 2 lines are the <lang> voice switch above).
