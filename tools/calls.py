import sys,re,subprocess
sys.stdout.reconfigure(encoding="utf-8", errors="replace")
# outline: list call targets + vtable calls + strings in function(s)
for a in sys.argv[1:]:
    loc = a.startswith('loc:'); a=a[4:] if loc else a
    out=subprocess.run(['python',r'D:/llm-experiments/misk/zira/tools/fn.py']+(['loc'] if loc else [])+[a],capture_output=True,text=True).stdout
    print('=====',a, len(out.split('\n')),'lines')
    for l in out.split('\n'):
        m=re.findall(r'(FUN_[0-9a-f]+|\(\*\*?\(code \*\*?\)\(?\*?\(?[^)]*\+ 0x[0-9a-f]+\)|L"[^"]*"|\w+::vftable|0x8004801a)',l)
        if m: print('  ',l.strip()[:150])
