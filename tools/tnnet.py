#!/usr/bin/env python3
"""tnnet.py - parse OneCore TransducerNetwork blobs (7d5841ab TN, 19a6569a compound, 388b0327 phone conv)."""
import struct, sys
sys.path.insert(0, r'D:/llm-experiments/misk/zira/tools')
from locdat import Dat
class Net:
    def __init__(s, d, off, size):
        s.d=d; s.base=off; s.end=off+size; p=off+16
        s.v1,s.v2=struct.unpack_from('<II',d,p); p+=8
        s.nsym,s.x3a=struct.unpack_from('<HH',d,p); p+=4
        s.cnt=list(struct.unpack_from('<7I',d,p)); p+=28
        s.nB,s.nC,s.nD,s.nE,s.nF,s.nG,s.nH=s.cnt
        s.d0,s.d2=struct.unpack_from('<HH',d,p); p+=4
        s.hdr_end=p
        s.A=p; p+=64*s.nsym
        s.B=p; p+=12*s.nB
        s.C=p; p+=16*s.nC
        s.D=p; p+=4*s.nD
        s.E=p; p+=28*s.nE
        s.F=p; p+=8*s.nF
        s.G=p; p+=4*s.nG
        s.H=p; p+=12*s.nH
        s.blobs=[]
        for k in range(3):
            f=struct.unpack_from('<I',d,p)[0]; p+=4
            if f:
                n=struct.unpack_from('<I',d,p)[0]; p+=4
                s.blobs.append((p,n)); p+=n
            else: s.blobs.append(None)
        s.tail=p
if __name__=='__main__':
    dat=Dat()
    for t in ('7d5841ab','19a6569a','388b0327'):
        c,sz=dat.res(t); n=Net(dat.d,c,sz)
        print(t, 'v',n.v1,n.v2,'nsym',n.nsym,n.x3a,'cnt',n.cnt,'d0/d2',n.d0,n.d2,'blobs',n.blobs,'tail at',hex(n.tail-c),'of',hex(sz))
