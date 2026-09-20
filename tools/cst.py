"""print float/double/int at VAs: python cst.py f 18017d3a0 d 18017f890 ..."""
import sys, struct, pefile
pe = pefile.PE(r'D:/llm-experiments/misk/zira/bin/MSTTSEngine_OneCore.dll', fast_load=True)
b = pe.OPTIONAL_HEADER.ImageBase; img = pe.get_memory_mapped_image()
a = sys.argv[1:]
for t, v in zip(a[::2], a[1::2]):
    r = int(v, 16) - b
    if t == 'f': print(v, 'f', struct.unpack_from('<f', img, r)[0])
    elif t == 'd': print(v, 'd', struct.unpack_from('<d', img, r)[0])
    else: print(v, 'i', hex(struct.unpack_from('<I', img, r)[0]))
