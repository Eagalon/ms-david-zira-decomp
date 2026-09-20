"""Assemble a self-contained folder: the built library and CLI, plus your own voice data next to them.

The port reads the voice data at runtime, so a portable copy is the dist folder with a data/ folder
beside it and a launcher that points at it. Nothing here is redistributable: the data is Microsoft's
and stays on your machines.

  python tools/make_portable.py [--arch x64] [--voices David Zira Mark]
                                [--src C:/Windows/Speech_OneCore/Engines/TTS/en-US]

Writes build/<arch>/portable/ with zira.exe, zira_tts.dll, the headers, data/ and zira.bat / zira.sh.
"""
import argparse
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_SRC = r"C:/Windows/Speech_OneCore/Engines/TTS/en-US"
SHARED = ["MSTTSLocEnUS.dat"]                     # the language data every voice uses
PER_VOICE = [".APM", ".BEP", ".INI"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--arch", default="x64")
    ap.add_argument("--src", default=DEFAULT_SRC)
    ap.add_argument("--voices", nargs="+", default=["David"])
    a = ap.parse_args()

    dist = os.path.join(ROOT, "build", a.arch, "dist")
    out = os.path.join(ROOT, "build", a.arch, "portable")
    if not os.path.isdir(dist):
        sys.exit("no dist folder at %s - run src\\build.bat %s first" % (dist, a.arch))
    if not os.path.isdir(a.src):
        sys.exit("no voice data at %s (pass --src)" % a.src)

    data = os.path.join(out, "data")
    os.makedirs(data, exist_ok=True)
    for f in os.listdir(dist):
        shutil.copy2(os.path.join(dist, f), out)
    total, missing = 0, []
    for fn in SHARED:
        p = os.path.join(a.src, fn)
        if os.path.exists(p):
            shutil.copy2(p, data)
            total += os.path.getsize(p)
        else:
            missing.append(fn)
    for v in a.voices:
        for ext in PER_VOICE:
            fn = "M1033%s%s" % (v, ext)
            p = os.path.join(a.src, fn)
            if os.path.exists(p):
                shutil.copy2(p, data)
                total += os.path.getsize(p)
            else:
                missing.append(fn)
    with open(os.path.join(out, "zira.bat"), "w", newline="\r\n") as f:
        f.write('@echo off\r\n"%~dp0zira.exe" --data "%~dp0data" %*\r\n')
    with open(os.path.join(out, "zira.sh"), "w", newline="\n") as f:
        f.write('#!/bin/sh\nexec "$(dirname "$0")/zira" --data "$(dirname "$0")/data" "$@"\n')
    with open(os.path.join(out, "README.txt"), "a", newline="\r\n") as f:
        f.write("\r\nThis folder carries its own copy of the voice data (data\\), so it runs anywhere.\r\n"
                "That data is Microsoft's: keep the folder to your own machines.\r\n"
                "Run it with zira.bat (Windows) or zira.sh.\r\n")
    print("%s: %s, %.1f MB of voice data + the library" % (out, ", ".join(a.voices), total / 1e6))
    if missing:
        print("missing (not copied): %s" % ", ".join(missing))


if __name__ == "__main__":
    main()
