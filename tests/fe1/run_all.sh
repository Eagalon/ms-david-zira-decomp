#!/bin/sh
# Regression: build zf1 (OUT=zf1_main) and compare every test set with the engine dumps
# (engine dumps are regenerated with harness/zftap1.exe when missing).
cd "$(dirname "$0")"
OUT=zf1_main sh ../../src/mk.sh
EXE=../../build/zf1_main.exe
run() {   # $1 = corpus path (without .txt), $2 = engine dump
  [ -f "$2" ] || ../../harness/zftap1.exe david "$1.txt" "$2"
  $EXE "$1.txt" "$1.port"
  printf '%-14s ' "$(basename $1)"; PYTHONIOENCODING=utf-8 python compare.py "$2" "$1.port" -v 0 | tail -1
}
run corpus david.dump
for s in prose misc xml stress fuzz; do run big/$s big/$s.dump; done
