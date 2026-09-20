#!/bin/sh
# Fork C (POS / polyphony / homograph CRF) unit tests.  Usage: sh run.sh [corpus.txt]   (default: homo.txt + prose.txt)
# 1. harness/zftap1_pos.exe dumps the engine (TAGIN/TAGOUT, PTIN/PTOUT, LEX8, SETPRON, W lines incl. f320)
# 2. ptconv.py / polyconv.py convert, 3. build/zf1_t_pos.exe and build/zf1_t_poly.exe compare.
set -e
cd "$(dirname "$0")"
IN=${1:-big.txt}
[ -f big.txt ] || cat homo.txt prose.txt > big.txt
../../../harness/zftap1_pos.exe david "$IN" run_pos.dump hooks
python ptconv.py run_pos.dump run_pt.txt
python polyconv.py run_pos.dump run_poly.txt
../../../build/zf1_t_pos.exe run run_pt.txt run_pt.txt.lex | tail -1     # Brill core on engine candidates
../../../build/zf1_t_pos.exe cand run_pt.txt run_pt.txt.lex | tail -1    # candidate POS lists
../../../build/zf1_t_pos.exe tag run_pt.txt run_pt.txt.lex | tail -1     # CPOSTaggerImpl::Tag on word lists
../../../build/zf1_t_poly.exe run_poly.txt | tail -2                     # RegularText, CPolyphony, CRF
