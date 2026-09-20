// FUN_1801619e4 @ 1801619e4
uint FUN_1801619e4(ushort param_1)
{
  uint uVar1;
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 1;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x100000;
  }
  return uVar1;
}
// FUN_180161db0 @ 180161db0
undefined8 FUN_180161db0(longlong *param_1)
{
  int iVar1;
  if ((((int)param_1[1] != 3) ||
      (iVar1 = _o_iswdigit(*(undefined2 *)
                            (*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2)),
      iVar1 == 0)) && ((int)param_1[1] != 4)) {
    return 0;
  }
  return 1;
}
// FUN_180161028 @ 180161028
undefined8 FUN_180161028(int *param_1)
{
  undefined8 uVar1;
  uVar1 = 0;
  if ((0 < *param_1) || (0 < param_1[4])) {
    uVar1 = 1;
  }
  return uVar1;
}
// FUN_180066b20 @ 180066b20
uint FUN_180066b20(ushort param_1)
{
  uint uVar1;
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 2;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x200000;
  }
  return uVar1;
}
// FUN_18016330c @ 18016330c
undefined8 FUN_18016330c(int *param_1,int *param_2)
{
  undefined8 uVar1;
  uVar1 = 0;
  if ((*param_1 == 0) && (-1 < param_1[1])) {
    uVar1 = 1;
    *param_2 = param_1[(longlong)param_1[1] + 0x34];
  }
  return uVar1;
}
// FUN_1801628d0 @ 1801628d0
void FUN_1801628d0(int *param_1,longlong *param_2,longlong param_3)
{
  undefined2 local_res20 [4];
  local_res20[0] = 0;
  FUN_180163334(param_1,param_2,param_3,local_res20);
  return;
}
// FUN_180161040 @ 180161040
void FUN_180161040(int *param_1,longlong *param_2,int param_3,int param_4,int param_5)
{
  int iVar1;
  undefined8 uVar2;
  short sVar3;
  uint uVar4;
  uVar4 = *(uint *)((longlong)param_2 + 0xc);
  sVar3 = *(short *)(*param_2 + (ulonglong)uVar4 * 2);
  if ((sVar3 - 0xabU & 0xffef) == 0) {
    iVar1 = param_1[4];
    if (sVar3 == 0xab) {
      if (iVar1 == 0) {
        param_1[7] = uVar4;
      }
      iVar1 = iVar1 + 1;
    }
    else {
      iVar1 = iVar1 + -1;
    }
    param_1[4] = iVar1;
  }
  else {
    if ((int)param_2[1] != 0xd) {
      sVar3 = *(short *)(*param_2 + (ulonglong)((int)param_2[2] + -1 + uVar4) * 2);
    }
    uVar2 = FUN_180160fe0(sVar3);
    if ((int)uVar2 == 0) {
      uVar2 = FUN_1800632f4(sVar3);
      if ((int)uVar2 != 0) {
        if (param_4 == 0) {
          iVar1 = param_1[1];
          if (param_3 == 0) {
            iVar1 = iVar1 + -1;
          }
          else {
            if (iVar1 == 0) {
              param_1[5] = uVar4;
            }
            if (param_5 != 0) {
              param_1[3] = param_1[3] + 1;
            }
            iVar1 = iVar1 + 1;
          }
          param_1[1] = iVar1;
        }
        else {
          param_1[2] = param_1[2] + 1;
        }
      }
    }
    else {
      iVar1 = *param_1;
      if (param_3 == 0) {
        iVar1 = iVar1 + -1;
      }
      else {
        if (iVar1 == 0) {
          param_1[6] = uVar4;
        }
        iVar1 = iVar1 + 1;
      }
      *param_1 = iVar1;
    }
  }
  return;
}
// FUN_1801628a0 @ 1801628a0
void FUN_1801628a0(int *param_1)
{
  if (*param_1 < 0) {
    *param_1 = 0;
    param_1[6] = 0;
  }
  if (param_1[4] < 0) {
    param_1[4] = 0;
    param_1[7] = 0;
  }
  if (param_1[1] < 0) {
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[5] = 0;
  }
  return;
}
// FUN_180160fe0 @ 180160fe0
undefined8 FUN_180160fe0(short param_1)
{
  if ((((0x28 < (ushort)(param_1 - 0x93U)) ||
       ((0x10001000003U >> ((ulonglong)(ushort)(param_1 - 0x93U) & 0x3f) & 1) == 0)) &&
      (param_1 != 0x22)) && (3 < (ushort)(param_1 + 0xdfe4U))) {
    return 0;
  }
  return 1;
}
// FUN_1800632f4 @ 1800632f4
undefined8 FUN_1800632f4(short param_1)
{
  undefined8 uVar1;
  if ((((param_1 != 0x27) && (param_1 != 0x91)) &&
      ((0x21 < (ushort)(param_1 + 0xdfe8U) ||
       ((0x200000009U >> ((ulonglong)(ushort)(param_1 + 0xdfe8U) & 0x3f) & 1) == 0)))) &&
     (uVar1 = FUN_180079148(param_1), (int)uVar1 == 0)) {
    return 0;
  }
  return 1;
}
// FUN_1801616b0 @ 1801616b0
uint FUN_1801616b0(longlong param_1,short *param_2,ulonglong param_3)
{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  short *psVar4;
  longlong lVar5;
  uVar3 = param_3 & 0xffffffff;
  uVar1 = (uint)param_3;
  psVar4 = param_2 + ((param_3 & 0xffffffff) - 1);
  if (param_2 < psVar4) {
    lVar5 = (longlong)psVar4 - (longlong)param_2;
    do {
      if ((ushort)(*psVar4 + 0xdff0U) < 2) {
        uVar3 = lVar5 >> 1;
      }
      uVar1 = (uint)uVar3;
      psVar4 = psVar4 + -1;
      lVar5 = lVar5 + -2;
    } while (param_2 < psVar4);
  }
  if (uVar1 < 0x80) {
    plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 8))();
    uVar3 = FUN_180061864((longlong)param_2,uVar1,plVar2);
    uVar1 = ~(uint)uVar3 >> 0x1f;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
// FUN_180061864 @ 180061864
ulonglong FUN_180061864(longlong param_1,uint param_2,longlong *param_3)
{
  ushort uVar1;
  ulonglong uVar2;
  int iVar3;
  longlong lVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  iVar7 = 0;
  if (param_3 != (longlong *)0x0) {
    iVar6 = (int)param_3[1] + -1;
    while (iVar7 <= iVar6) {
      uVar2 = (longlong)(iVar6 + iVar7) / 2;
      iVar3 = (int)uVar2;
      puVar5 = *(ushort **)(*param_3 + (longlong)iVar3 * 8);
      lVar4 = param_1 - (longlong)puVar5;
      for (uVar8 = 0; uVar8 < param_2; uVar8 = uVar8 + 1) {
        if (*puVar5 == 0) goto LAB_1800618e4;
        uVar1 = *(ushort *)(lVar4 + (longlong)puVar5);
        if (uVar1 < *puVar5) goto LAB_1800618de;
        if (uVar1 != *puVar5) goto LAB_1800618e4;
        puVar5 = puVar5 + 1;
      }
      if (uVar8 == param_2) {
        if (*puVar5 == 0) {
          return uVar2 & 0xffffffff;
        }
LAB_1800618de:
        iVar6 = iVar3 + -1;
      }
      else {
LAB_1800618e4:
        iVar7 = iVar3 + 1;
      }
    }
  }
  return 0xffffffff;
}
// FUN_18003f9ac @ 18003f9ac
uint FUN_18003f9ac(ushort param_1)
{
  uint uVar1;
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 7;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x10400000;
  }
  return uVar1;
}
// FUN_1801628f4 @ 1801628f4
undefined8 FUN_1801628f4(longlong *param_1)
{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  bVar2 = false;
  uVar5 = 0;
  uVar1 = *(uint *)(param_1 + 2);
  puVar4 = (ushort *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2);
  do {
    if (uVar1 <= uVar5) {
      return 1;
    }
    if (bVar2) {
      if (bVar2) {
        if (*puVar4 != 0x2e) {
          return 0;
        }
        bVar2 = false;
      }
    }
    else {
      uVar3 = FUN_1801619e4(*puVar4);
      if (uVar3 == 0) {
        return 0;
      }
      bVar2 = true;
    }
    uVar5 = uVar5 + 1;
    puVar4 = puVar4 + 1;
  } while( true );
}
// FUN_18016296c @ 18016296c
undefined8 FUN_18016296c(longlong *param_1)
{
  wchar_t _Ch;
  wchar_t *pwVar1;
  undefined8 uVar2;
  uint uVar3;
  wchar_t *pwVar4;
  pwVar4 = (wchar_t *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2);
  if (pwVar4 == (wchar_t *)0x0) {
LAB_1801629be:
    uVar2 = 0;
  }
  else {
    for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 2); uVar3 = uVar3 + 1) {
      _Ch = *pwVar4;
      pwVar4 = pwVar4 + 1;
      pwVar1 = wcschr(L"iIvVxXlLcCdDmM",_Ch);
      if (pwVar1 == (wchar_t *)0x0) goto LAB_1801629be;
    }
    uVar2 = 1;
  }
  return uVar2;
}
// FUN_1801629d8 @ 1801629d8
bool FUN_1801629d8(longlong *param_1)
{
  undefined2 *puVar1;
  longlong lVar2;
  uint uVar3;
  longlong lVar4;
  int iVar5;
  uint uVar6;
  undefined2 *puVar7;
  ulonglong uVar8;
  uVar8 = (ulonglong)*(uint *)((longlong)param_1 + 0xc);
  lVar4 = *param_1;
  uVar6 = 0;
  uVar3 = *(uint *)(param_1 + 2);
  puVar1 = (undefined2 *)(lVar4 + uVar8 * 2);
  puVar7 = puVar1;
  if (uVar3 != 0) {
    do {
      iVar5 = _o_iswdigit(*puVar7);
      if (iVar5 == 0) break;
      uVar6 = uVar6 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar6 < uVar3);
    if (uVar6 != 0) {
      if ((uVar6 == uVar3 - 1) &&
         ((lVar2 = uVar6 + uVar8, *(short *)(lVar4 + lVar2 * 2) == 0x61 ||
          (*(short *)(lVar4 + lVar2 * 2) == 0x6f)))) {
        return true;
      }
      if ((uVar6 == uVar3 - 2) && (puVar1[uVar6] == 0x65)) {
        return *(short *)(lVar4 + ((uVar6 + 1) + uVar8) * 2) == 0x72;
      }
    }
  }
  return false;
}
// FUN_180160f40 @ 180160f40
ulonglong FUN_180160f40(int *param_1,longlong *param_2)
{
  int iVar1;
  int iVar2;
  longlong lVar3;
  uint uVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  iVar1 = (int)param_2[2];
  iVar2 = *(int *)((longlong)param_2 + 0xc);
  lVar3 = *param_2;
  uVar8 = 0;
  uVar5 = FUN_1800632f4(*(short *)(lVar3 + (ulonglong)(uint)(iVar1 + -1 + iVar2) * 2));
  if ((int)uVar5 != 0) {
    uVar4 = (uint)uVar8;
    uVar6 = uVar4 + 1;
    uVar7 = uVar4;
    if (((int)uVar6 < iVar1) &&
       ((*(short *)(lVar3 + (ulonglong)(uint)(iVar1 + -2 + iVar2) * 2) - 0x53U & 0xffdf) == 0)) {
      uVar7 = uVar6;
    }
    FUN_180161040(param_1,param_2,0,uVar7,uVar4);
    uVar8 = (ulonglong)uVar6;
  }
  return uVar8 & 0xffffffff;
}
// FUN_180161d5c @ 180161d5c
undefined4 FUN_180161d5c(longlong *param_1,longlong param_2)
{
  int iVar1;
  longlong lVar2;
  undefined4 uVar3;
  lVar2 = -1;
  do {
    lVar2 = lVar2 + 1;
  } while (*(short *)(param_2 + lVar2 * 2) != 0);
  uVar3 = 0;
  if ((int)lVar2 == (int)param_1[2]) {
    iVar1 = _o__wcsnicmp(param_2,*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2,
                         (int)param_1[2]);
    uVar3 = 0;
    if (iVar1 == 0) {
      uVar3 = 1;
    }
  }
  return uVar3;
}
// FUN_180161740 @ 180161740
uint FUN_180161740(longlong param_1,longlong param_2,uint param_3)
{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined1 auStack_138 [32];
  ushort local_118 [128];
  ulonglong local_18;
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_138;
  if (param_3 < 0x80) {
    FUN_180058730((short *)local_118,0x80,param_2,(ulonglong)param_3);
    uVar1 = FUN_1801631c8(local_118,param_3);
    if (uVar1 == param_3) {
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x38))();
      uVar3 = FUN_180061864((longlong)local_118,param_3,plVar2);
      return ~(uint)uVar3 >> 0x1f;
    }
  }
  return 0;
}
// FUN_1801617e4 @ 1801617e4
uint FUN_1801617e4(longlong param_1,longlong param_2,uint param_3)
{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined1 auStack_138 [32];
  ushort local_118 [128];
  ulonglong local_18;
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_138;
  if (param_3 < 0x80) {
    FUN_180058730((short *)local_118,0x80,param_2,(ulonglong)param_3);
    uVar1 = FUN_1801631c8(local_118,param_3);
    if (uVar1 == param_3) {
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x18))();
      uVar3 = FUN_180061864((longlong)local_118,param_3,plVar2);
      return ~(uint)uVar3 >> 0x1f;
    }
  }
  return 0;
}
// FUN_18003f58c @ 18003f58c
uint FUN_18003f58c(ushort param_1)
{
  uint uVar1;
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 3;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x10000000;
  }
  return uVar1;
}
// FUN_180161624 @ 180161624
uint FUN_180161624(longlong param_1,ushort *param_2,uint param_3)
{
  uint uVar1;
  undefined8 uVar2;
  longlong *plVar3;
  ulonglong uVar4;
  uint uVar5;
  ushort *puVar6;
  uVar1 = FUN_1801619e4(*param_2);
  uVar5 = 0;
  if (uVar1 != 0) {
    uVar5 = 0;
    puVar6 = param_2;
    if (param_3 != 0) {
      do {
        uVar2 = FUN_1800632f4(*puVar6);
        if ((int)uVar2 != 0) break;
        uVar5 = uVar5 + 1;
        puVar6 = puVar6 + 1;
      } while (uVar5 < param_3);
    }
    plVar3 = (longlong *)(**(code **)**(undefined8 **)(param_1 + 0x80))();
    uVar4 = FUN_180061864((longlong)param_2,uVar5,plVar3);
    uVar5 = ~(uint)uVar4 >> 0x1f;
  }
  return uVar5;
}
// FUN_180161e84 @ 180161e84
void FUN_180161e84(longlong param_1,int *param_2)
{
  undefined8 uVar1;
  int *piVar2;
  undefined8 *puVar3;
  int *piVar4;
  undefined8 *puVar5;
  longlong lVar6;
  if (*param_2 != 0) {
    FUN_180068f88((undefined8 *)(param_1 + 8),(undefined8 *)(param_1 + 0x40));
    *param_2 = 0;
    lVar6 = 3;
    *(int *)(param_1 + 0x2fc) = param_2[1];
    *(int *)(param_1 + 0x300) = param_2[2];
    *(int *)(param_1 + 0x304) = param_2[3];
    piVar2 = param_2 + 4;
    puVar3 = (undefined8 *)(param_1 + 0x100);
    do {
      puVar5 = puVar3;
      piVar4 = piVar2;
      uVar1 = *(undefined8 *)(piVar4 + 2);
      *puVar5 = *(undefined8 *)piVar4;
      puVar5[1] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 6);
      puVar5[2] = *(undefined8 *)(piVar4 + 4);
      puVar5[3] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 10);
      puVar5[4] = *(undefined8 *)(piVar4 + 8);
      puVar5[5] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0xe);
      puVar5[6] = *(undefined8 *)(piVar4 + 0xc);
      puVar5[7] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x12);
      puVar5[8] = *(undefined8 *)(piVar4 + 0x10);
      puVar5[9] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x16);
      puVar5[10] = *(undefined8 *)(piVar4 + 0x14);
      puVar5[0xb] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x1a);
      puVar5[0xc] = *(undefined8 *)(piVar4 + 0x18);
      puVar5[0xd] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x1e);
      puVar5[0xe] = *(undefined8 *)(piVar4 + 0x1c);
      puVar5[0xf] = uVar1;
      lVar6 = lVar6 + -1;
      piVar2 = piVar4 + 0x20;
      puVar3 = puVar5 + 0x10;
    } while (lVar6 != 0);
    uVar1 = *(undefined8 *)(piVar4 + 0x22);
    puVar5[0x10] = *(undefined8 *)(piVar4 + 0x20);
    puVar5[0x11] = uVar1;
    puVar5[0x12] = *(undefined8 *)(piVar4 + 0x24);
    *(int *)(param_1 + 0x298) = param_2[0x6a];
    *(int *)(param_1 + 0x29c) = param_2[0x6b];
    *(int *)(param_1 + 0x2a0) = param_2[0x6c];
    *(int *)(param_1 + 0x2a4) = param_2[0x6d];
    *(int *)(param_1 + 0x2a8) = param_2[0x6e];
    *(int *)(param_1 + 0x2ac) = param_2[0x6f];
    *(int *)(param_1 + 0x2b0) = param_2[0x70];
    *(int *)(param_1 + 0x2b4) = param_2[0x71];
    FUN_18007b2e4((undefined8 *)(param_1 + 0x98),(undefined8 *)(param_2 + 0x72));
    FUN_18007b2e4((undefined8 *)(param_1 + 0xb8),(undefined8 *)(param_2 + 0x7a));
    FUN_18007b2e4((undefined8 *)(param_1 + 0xd8),(undefined8 *)(param_2 + 0x82));
    *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xa0);
  }
  return;
}
// FUN_180162aa4 @ 180162aa4
bool FUN_180162aa4(longlong *param_1)
{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  short *psVar4;
  uint uVar5;
  uVar1 = *(uint *)(param_1 + 2);
  if (((int)param_1[1] == 3) && (1 < uVar1)) {
    iVar2 = 1;
    psVar4 = (short *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2);
    for (uVar5 = 0; uVar5 < uVar1; uVar5 = uVar5 + 1) {
      if (iVar2 == 1) {
        iVar2 = _o_iswdigit(*psVar4);
        if (iVar2 != 0) {
          return false;
        }
        iVar2 = 2;
      }
      else if (iVar2 == 2) {
        if (*psVar4 == 0x2e) {
          return false;
        }
        iVar2 = 3;
      }
      else if ((iVar2 == 3) && (*psVar4 == 0x2e)) {
        return false;
      }
      psVar4 = psVar4 + 1;
    }
    if (iVar2 == 3) {
      uVar3 = FUN_18016296c(param_1);
      return (int)uVar3 == 0;
    }
  }
  return false;
}
// FUN_180162738 @ 180162738
void FUN_180162738(longlong param_1,undefined4 *param_2)
{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong lVar6;
  FUN_180068f88((undefined8 *)(param_1 + 0x40),(undefined8 *)(param_1 + 8));
  *(undefined4 *)(param_1 + 0x78) = 1;
  *param_2 = 1;
  param_2[1] = *(undefined4 *)(param_1 + 0x2fc);
  param_2[2] = *(undefined4 *)(param_1 + 0x300);
  param_2[3] = *(undefined4 *)(param_1 + 0x304);
  FUN_18007b2e4((undefined8 *)(param_2 + 0x72),(undefined8 *)(param_1 + 0x98));
  FUN_18007b2e4((undefined8 *)(param_2 + 0x7a),(undefined8 *)(param_1 + 0xb8));
  FUN_18007b2e4((undefined8 *)(param_2 + 0x82),(undefined8 *)(param_1 + 0xd8));
  lVar6 = 3;
  puVar2 = (undefined8 *)(param_1 + 0x100);
  puVar3 = (undefined8 *)(param_2 + 4);
  do {
    puVar5 = puVar3;
    puVar4 = puVar2;
    uVar1 = puVar4[1];
    *puVar5 = *puVar4;
    puVar5[1] = uVar1;
    uVar1 = puVar4[3];
    puVar5[2] = puVar4[2];
    puVar5[3] = uVar1;
    uVar1 = puVar4[5];
    puVar5[4] = puVar4[4];
    puVar5[5] = uVar1;
    uVar1 = puVar4[7];
    puVar5[6] = puVar4[6];
    puVar5[7] = uVar1;
    uVar1 = puVar4[9];
    puVar5[8] = puVar4[8];
    puVar5[9] = uVar1;
    uVar1 = puVar4[0xb];
    puVar5[10] = puVar4[10];
    puVar5[0xb] = uVar1;
    uVar1 = puVar4[0xd];
    puVar5[0xc] = puVar4[0xc];
    puVar5[0xd] = uVar1;
    uVar1 = puVar4[0xf];
    puVar5[0xe] = puVar4[0xe];
    puVar5[0xf] = uVar1;
    lVar6 = lVar6 + -1;
    puVar2 = puVar4 + 0x10;
    puVar3 = puVar5 + 0x10;
  } while (lVar6 != 0);
  uVar1 = puVar4[0x11];
  puVar5[0x10] = puVar4[0x10];
  puVar5[0x11] = uVar1;
  puVar5[0x12] = puVar4[0x12];
  param_2[0x6a] = *(undefined4 *)(param_1 + 0x298);
  param_2[0x6b] = *(undefined4 *)(param_1 + 0x29c);
  param_2[0x6c] = *(undefined4 *)(param_1 + 0x2a0);
  param_2[0x6d] = *(undefined4 *)(param_1 + 0x2a4);
  param_2[0x6e] = *(undefined4 *)(param_1 + 0x2a8);
  param_2[0x6f] = *(undefined4 *)(param_1 + 0x2ac);
  param_2[0x70] = *(undefined4 *)(param_1 + 0x2b0);
  param_2[0x71] = *(undefined4 *)(param_1 + 0x2b4);
  return;
}
// FUN_1800cf160 @ 1800cf160
void FUN_1800cf160(void)
{
  undefined8 local_28 [5];
  FUN_1800cdb2c(local_28);
                      _CxxThrowException(local_28,(ThrowInfo *)&DAT_1801b65f0);
}
// FUN_18007cc74 @ 18007cc74
void FUN_18007cc74(void)
{
  undefined8 local_28 [5];
  FUN_18007cc50(local_28);
                      _CxxThrowException(local_28,(ThrowInfo *)&DAT_1801b6468);
}
// FUN_180075cac @ 180075cac
undefined8 FUN_180075cac(longlong *param_1,ushort *param_2,undefined8 param_3)
{
  uint *puVar1;
  short sVar2;
  short sVar3;
  ulonglong uVar4;
  uint uVar5;
  longlong lVar6;
  longlong *_Dst;
  short *psVar7;
  undefined8 *puVar8;
  puVar1 = (uint *)(param_1 + 1);
  _Dst = param_1;
  if (*param_1 == 0) {
    lVar6 = SUB168(ZEXT816(8) * ZEXT416(*puVar1),0);
    if (SUB168(ZEXT816(8) * ZEXT416(*puVar1),8) != 0) {
      lVar6 = -1;
    }
    _Dst = (longlong *)thunk_FUN_18007ca58(lVar6);
    *param_1 = (longlong)_Dst;
    if (_Dst == (longlong *)0x0) {
      return 0x8007000e;
    }
    memset(_Dst,0,(ulonglong)*puVar1 << 3);
  }
  uVar5 = FUN_1800466e0(_Dst,param_2);
  uVar4 = (ulonglong)uVar5 % (ulonglong)*puVar1;
  puVar8 = *(undefined8 **)(*param_1 + uVar4 * 8);
  do {
    if (puVar8 == (undefined8 *)0x0) {
      puVar8 = (undefined8 *)FUN_18007ca58(0x18);
      if (puVar8 == (undefined8 *)0x0) {
        return 0x8007000e;
      }
      *puVar8 = param_2;
      puVar8[1] = param_3;
      puVar8[2] = *(undefined8 *)(*param_1 + uVar4 * 8);
      *(undefined8 **)(*param_1 + uVar4 * 8) = puVar8;
      return 0;
    }
    psVar7 = (short *)*puVar8;
    lVar6 = (longlong)param_2 - (longlong)psVar7;
    do {
      sVar2 = *psVar7;
      sVar3 = *(short *)((longlong)psVar7 + lVar6);
      if (sVar2 != sVar3) break;
      psVar7 = psVar7 + 1;
    } while (sVar3 != 0);
    if (sVar2 == sVar3) {
      return 0;
    }
    puVar8 = (undefined8 *)puVar8[2];
  } while( true );
}
// FUN_180163334 @ 180163334
undefined8 FUN_180163334(int *param_1,longlong *param_2,longlong param_3,undefined2 *param_4)
{
  int iVar1;
  int iVar2;
  int local_res8 [2];
  int local_18 [4];
  local_18[0] = 0;
  local_res8[0] = 0;
  if (*param_1 != 0) {
    return 0;
  }
  FUN_18016345c(param_1,param_2,local_18,local_res8);
  if (local_res8[0] == -1) {
    iVar1 = param_1[1];
    if (iVar1 < 0x32) {
      if (iVar1 < 0) {
        if ((*(int *)(param_3 + 0x10) == 1) && (*(int *)(param_3 + 8) == 3)) {
          return 0;
        }
        *param_4 = 0;
        return 0;
      }
      iVar2 = param_1[(longlong)iVar1 + 2];
      param_1[1] = iVar1 + -1;
      if (iVar2 == local_18[0]) {
        return 0;
      }
      if (iVar2 == 0) {
        *param_4 = 0x29;
        return 0;
      }
      if (iVar2 == 1) {
        *param_4 = 0x7d;
        return 0;
      }
      if (iVar2 == 2) {
        *param_4 = 0x5d;
        return 0;
      }
      if (iVar2 == 3) {
        *param_4 = 0x2019;
        return 0;
      }
      if (iVar2 != 4) {
        if (iVar2 == 5) {
          *param_4 = 0x300d;
          return 0;
        }
        if (iVar2 != 6) {
          return 0;
        }
        *param_4 = 0x300f;
        return 0;
      }
      *param_4 = 0x201d;
      return 0;
    }
  }
  else {
    if (local_res8[0] != 1) {
      return 0;
    }
    iVar1 = param_1[1];
    iVar2 = iVar1 + 1;
    param_1[1] = iVar2;
    if (iVar2 < 0x32) {
      param_1[(longlong)iVar1 + 3] = local_18[0];
      param_1[(longlong)param_1[1] + 0x34] = *(int *)((longlong)param_2 + 0xc);
      return 0;
    }
  }
  *param_1 = 1;
  return 0;
}
// FUN_180079148 @ 180079148
undefined8 FUN_180079148(short param_1)
{
  undefined8 uVar1;
  uVar1 = 1;
  if ((((param_1 != 0x27) && (param_1 != 0x92)) && (1 < (ushort)(param_1 + 0xdfe7U))) &&
     (param_1 != 0x203a)) {
    uVar1 = 0;
  }
  return uVar1;
}
// FUN_180058730 @ 180058730
uint FUN_180058730(short *param_1,longlong param_2,longlong param_3,ulonglong param_4)
{
  short sVar1;
  uint uVar2;
  short *psVar3;
  longlong lVar4;
  longlong lVar5;
  if (param_2 - 1U < 0x7fffffff) {
    if (0x7ffffffe < param_4) {
LAB_180058798:
      *param_1 = 0;
      return 0x80070057;
    }
    lVar5 = param_4 - param_2;
    lVar4 = param_3 - (longlong)param_1;
    do {
      if ((lVar5 + param_2 == 0) || (sVar1 = *(short *)(lVar4 + (longlong)param_1), sVar1 == 0))
      break;
      *param_1 = sVar1;
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
    psVar3 = param_1 + -1;
    if (param_2 != 0) {
      psVar3 = param_1;
    }
    *psVar3 = 0;
    uVar2 = ~-(uint)(param_2 != 0) & 0x8007007a;
  }
  else {
    uVar2 = 0x80070057;
    if (param_2 != 0) goto LAB_180058798;
  }
  return uVar2;
}
// FUN_1801631c8 @ 1801631c8
int FUN_1801631c8(ushort *param_1,int param_2)
{
  ulonglong uVar1;
  int iVar2;
  for (iVar2 = param_2; iVar2 != 0; iVar2 = iVar2 + -1) {
    uVar1 = FUN_180163210(*param_1);
    *param_1 = (ushort)uVar1;
    param_1 = param_1 + 1;
  }
  return param_2;
}
// FUN_180068f88 @ 180068f88
undefined8 * FUN_180068f88(undefined8 *param_1,undefined8 *param_2)
{
  *param_1 = *param_2;
  *(undefined4 *)(param_1 + 1) = *(undefined4 *)(param_2 + 1);
  *(undefined4 *)((longlong)param_1 + 0xc) = *(undefined4 *)((longlong)param_2 + 0xc);
  *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_2 + 2);
  FUN_18007b2e4(param_1 + 3,param_2 + 3);
  return param_1;
}
// FUN_1800cdb2c @ 1800cdb2c
undefined8 * FUN_1800cdb2c(undefined8 *param_1)
{
  param_1[2] = 0;
  param_1[1] = "bad array new length";
  *param_1 = std::bad_array_new_length::vftable;
  return param_1;
}
// FUN_18007cc50 @ 18007cc50
undefined8 * FUN_18007cc50(undefined8 *param_1)
{
  param_1[2] = 0;
  param_1[1] = "bad allocation";
  *param_1 = std::bad_alloc::vftable;
  return param_1;
}
// FUN_1800466e0 @ 1800466e0
int FUN_1800466e0(undefined8 param_1,ushort *param_2)
{
  int iVar1;
  iVar1 = 0;
  for (; *param_2 != 0; param_2 = param_2 + 1) {
    iVar1 = iVar1 * 0x1003f + (uint)*param_2;
  }
  return iVar1;
}
// FUN_1800774b4 @ 1800774b4
longlong *
FUN_1800774b4(longlong *param_1,longlong param_2,int param_3,undefined4 param_4,undefined4 param_5,
             undefined4 param_6)
{
  *param_1 = param_2;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 1) = 0;
    *(undefined4 *)((longlong)param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 2) = 0;
  }
  FUN_1800774f8((longlong)param_1,param_3);
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)(param_1 + 2) = param_5;
  *(undefined4 *)((longlong)param_1 + 0x14) = param_6;
  *(undefined4 *)((longlong)param_1 + 0xc) = param_4;
  return param_1;
}
// FUN_18003fdb8 @ 18003fdb8
undefined4 FUN_18003fdb8(undefined8 param_1,short *param_2,int param_3)
{
  undefined4 uVar1;
  uVar1 = 1;
  if (((param_3 < 2) || (0x3ff < (ushort)(*param_2 + 0x2800U))) ||
     (0x3ff < (ushort)(param_2[1] + 0x2400U))) {
    uVar1 = 0;
  }
  return uVar1;
}
// FUN_18003fbe4 @ 18003fbe4
bool FUN_18003fbe4(longlong param_1,uint param_2,uint *param_3)
{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  undefined7 extraout_var_01;
  ushort uVar4;
  ushort *puVar5;
  ushort *puVar6;
  int iVar7;
  uVar3 = *param_3;
  puVar5 = (ushort *)(param_1 + (ulonglong)param_2 * 2);
  uVar4 = *puVar5;
  puVar6 = puVar5 + 1;
  if ((uVar3 < 3) || (uVar4 != 0x3a)) {
    if ((uVar4 == 0x3e) || (uVar4 == 0x7d)) {
      uVar3 = uVar3 - 1;
      if (uVar3 == 0) {
        return false;
      }
      uVar4 = *puVar6;
      puVar6 = puVar5 + 2;
    }
    if ((2 < uVar3) && (uVar4 == 0x38)) {
      if (*puVar6 != 0x2f) goto LAB_18003fccd;
      bVar1 = FUN_1801619b4(puVar6[1]);
      uVar2 = (uint)CONCAT71(extraout_var_01,bVar1);
      goto LAB_18003fc71;
    }
    if ((uVar4 == 0x3a) || ((uVar4 == 0x3b || (uVar4 == 0x38)))) goto LAB_18003fccd;
    bVar1 = uVar4 == 0x25;
  }
  else {
    if ((*puVar6 == 0x2f) && (puVar5[2] == 0x2f)) {
      return false;
    }
    bVar1 = FUN_1801619b4(*puVar6);
    if (((int)CONCAT71(extraout_var,bVar1) != 0) &&
       (bVar1 = FUN_1801619b4(puVar5[2]), (int)CONCAT71(extraout_var_00,bVar1) != 0)) {
      return false;
    }
    if (*puVar6 != 0x5c) goto LAB_18003fccd;
    uVar2 = FUN_18003f9ac(puVar5[2]);
LAB_18003fc71:
    bVar1 = uVar2 == 0;
  }
  if (!bVar1) {
    return false;
  }
LAB_18003fccd:
  iVar7 = uVar3 - 1;
  if (iVar7 != 0) {
    uVar4 = *puVar6;
    puVar5 = puVar6 + 1;
    if ((uVar4 == 0x2d) || (uVar4 == 0x5e)) {
      iVar7 = uVar3 - 2;
      if (iVar7 == 0) {
        return false;
      }
      uVar4 = *puVar5;
      puVar5 = puVar6 + 2;
    }
    if (((uVar4 == 0x6f) ||
        ((((ushort)(uVar4 - 0x28) < 0x35 &&
          ((0x10008210500081U >> ((ulonglong)(uVar4 - 0x28) & 0x3f) & 1) != 0)) || (uVar4 == 0x7c)))
        ) || (((uVar4 == 0x30 || (uVar4 == 0x29)) && (puVar5[-2] != 0x38)))) {
      uVar3 = (uint)((longlong)((longlong)puVar5 + ((ulonglong)param_2 * -2 - param_1)) >> 1);
      *param_3 = uVar3;
      puVar6 = puVar5;
      if (((ushort)(uVar4 - 0x28) < 2) && (iVar7 = iVar7 + -1, iVar7 != 0)) {
        uVar4 = *puVar5;
        puVar6 = puVar5 + 1;
        if (uVar4 == puVar5[-1]) {
          *param_3 = uVar3 + 1;
        }
      }
      uVar3 = FUN_18003f58c(uVar4);
      if ((uVar3 != 0) && (iVar7 != 1)) {
        uVar3 = FUN_18003f9ac(*puVar6);
        return uVar3 == 0;
      }
      return true;
    }
  }
  return false;
}
// FUN_18007a664 @ 18007a664
ulonglong FUN_18007a664(short param_1)
{
  undefined8 uVar1;
  ulonglong uVar2;
  uVar1 = FUN_1800632f4(param_1);
  uVar2 = 0;
  if ((int)uVar1 == 0) {
    uVar1 = FUN_180160fe0(param_1);
    if ((int)uVar1 == 0) goto LAB_18007a68b;
  }
  uVar2 = 1;
LAB_18007a68b:
  return uVar2 & 0xffffffff;
}
// FUN_18003f9e4 @ 18003f9e4
ulonglong FUN_18003f9e4(ushort *param_1,uint param_2,uint param_3,longlong *param_4,longlong param_5
                       )
{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  ushort *puVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ushort *puVar8;
  longlong lVar9;
  ulonglong uVar10;
  longlong lVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined8 *puVar16;
  if (param_4 != (longlong *)0x0) {
    iVar14 = (int)param_4[1] + -1;
    iVar12 = 0;
    do {
      iVar13 = 0;
      iVar15 = iVar14;
      iVar14 = -1;
      while (uVar6 = 0, iVar12 <= iVar15) {
        iVar3 = (iVar15 + iVar12) / 2;
        lVar11 = (longlong)iVar3;
        puVar5 = *(ushort **)(*param_4 + lVar11 * 8);
        lVar9 = (longlong)param_1 - (longlong)puVar5;
        uVar10 = uVar6;
        while( true ) {
          uVar4 = (uint)uVar10;
          if (param_2 <= uVar4) break;
          if (*puVar5 == 0) goto LAB_18003fa83;
          uVar1 = *(ushort *)(lVar9 + (longlong)puVar5);
          uVar2 = *puVar5;
          if (uVar1 >= uVar2 && uVar1 != uVar2) {
            if (((param_3 <= uVar4) && (iVar14 == -1)) &&
               ((uVar1 != 0x5f && (uVar4 = FUN_18003f9ac(uVar1), uVar4 == 0)))) {
              iVar14 = iVar3 + -1;
              iVar13 = iVar12;
            }
            goto LAB_18003fb44;
          }
          if (uVar1 < uVar2) goto LAB_18003fb4c;
          puVar5 = puVar5 + 1;
          uVar10 = (ulonglong)(uVar4 + 1);
        }
        if (uVar4 == param_2) {
          if (*puVar5 == 0) {
            return uVar10;
          }
LAB_18003fb4c:
          iVar15 = iVar3 + -1;
        }
        else {
LAB_18003fa83:
          if (param_3 <= uVar4) {
            puVar16 = (undefined8 *)(*param_4 + lVar11 * 8);
            goto LAB_18003fa99;
          }
LAB_18003fb44:
          iVar12 = iVar3 + 1;
        }
      }
      iVar12 = iVar13;
    } while (iVar13 <= iVar14);
  }
  return 0;
LAB_18003fa99:
  uVar7 = uVar6;
  if (iVar15 < lVar11) goto LAB_18003fb6f;
  if ((param_1[uVar10] != 0x5f) && (uVar4 = FUN_18003f9ac(param_1[uVar10]), uVar4 == 0)) {
    uVar6 = uVar10;
  }
  uVar10 = 0;
  uVar7 = uVar6;
  if (lVar11 == iVar15) goto LAB_18003fb6f;
  puVar16 = puVar16 + 1;
  lVar11 = lVar11 + 1;
  puVar5 = (ushort *)*puVar16;
  puVar8 = param_1;
  if (param_2 != 0) {
    do {
      if ((*puVar5 == 0) || (*puVar8 != *puVar5)) break;
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
      uVar4 = (int)uVar10 + 1;
      uVar10 = (ulonglong)uVar4;
    } while (uVar4 < param_2);
  }
  if (*puVar5 != 0) {
    if (*puVar8 <= *puVar5) goto LAB_18003fb6f;
    goto LAB_18003fa99;
  }
  uVar7 = uVar10;
  if ((uint)uVar10 == param_2) {
LAB_18003fb6f:
    if (((param_5 != 0) && ((int)uVar7 + 3U <= param_2)) && (param_1[uVar7] == 0x28)) {
      uVar4 = (int)uVar7 + 1;
      uVar6 = FUN_18003f9e4(param_1 + uVar4,(param_2 - uVar4) - 1,1,(longlong *)param_5,0);
      if (((int)uVar6 != 0) && (uVar4 = uVar4 + (int)uVar6, param_1[uVar4] == 0x29)) {
        uVar7 = (ulonglong)(uVar4 + 1);
      }
    }
    return uVar7;
  }
  goto LAB_18003fa99;
}
// FUN_180075e74 @ 180075e74
undefined8 FUN_180075e74(ushort param_1)
{
  bool bVar1;
  if (param_1 < 0x55f) {
    if (param_1 == 0x55e) {
      return 1;
    }
    if (param_1 == 0x21) {
      return 1;
    }
    if (param_1 == 0x3f) {
      return 1;
    }
    if (param_1 == 0x1c3) {
      return 1;
    }
    if (param_1 == 0x37e) {
      return 1;
    }
    bVar1 = param_1 == 0x55c;
  }
  else {
    if (param_1 == 0x61f) {
      return 1;
    }
    if (param_1 == 0x203c) {
      return 1;
    }
    if (param_1 == 0x2762) {
      return 1;
    }
    if (param_1 == 0xfe56) {
      return 1;
    }
    bVar1 = param_1 == 0xfe57;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}
// FUN_18003f2e4 @ 18003f2e4
undefined8 FUN_18003f2e4(short param_1)
{
  if ((((param_1 != 0x589) && (param_1 != 0x964)) && (param_1 != 0x3002)) &&
     (((param_1 != -0xff && (param_1 != -0xe1)) && (param_1 != -0x9f)))) {
    return 0;
  }
  return 1;
}
// FUN_18016156c @ 18016156c
undefined8 FUN_18016156c(ushort param_1)
{
  bool bVar1;
  if (param_1 < 0x300d) {
    if (param_1 == 0x300c) {
      return 1;
    }
    if (param_1 == 0x28) {
      return 1;
    }
    if (param_1 == 0x5b) {
      return 1;
    }
    if (param_1 == 0x7b) {
      return 1;
    }
    if (param_1 == 0x2018) {
      return 1;
    }
    bVar1 = param_1 == 0x201c;
  }
  else {
    if (param_1 == 0x300e) {
      return 1;
    }
    if (param_1 == 0xff08) {
      return 1;
    }
    if (param_1 == 0xff3b) {
      return 1;
    }
    if (param_1 == 0xff5b) {
      return 1;
    }
    bVar1 = param_1 == 0xff62;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}
// FUN_1801615c8 @ 1801615c8
undefined8 FUN_1801615c8(ushort param_1)
{
  bool bVar1;
  if (param_1 < 0x300e) {
    if (param_1 == 0x300d) {
      return 1;
    }
    if (param_1 == 0x29) {
      return 1;
    }
    if (param_1 == 0x5d) {
      return 1;
    }
    if (param_1 == 0x7d) {
      return 1;
    }
    if (param_1 == 0x2019) {
      return 1;
    }
    bVar1 = param_1 == 0x201d;
  }
  else {
    if (param_1 == 0x300f) {
      return 1;
    }
    if (param_1 == 0xff09) {
      return 1;
    }
    if (param_1 == 0xff3d) {
      return 1;
    }
    if (param_1 == 0xff5d) {
      return 1;
    }
    bVar1 = param_1 == 0xff63;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}
// FUN_18003f934 @ 18003f934
undefined8 FUN_18003f934(short param_1)
{
  undefined8 uVar1;
  uVar1 = 1;
  if ((((param_1 != 0x27) && (1 < (ushort)(param_1 + 0xdfe8U))) && (param_1 != 0xb4)) &&
     (((param_1 != 0x60 && (param_1 != 0x2032)) && (param_1 != -0xf9)))) {
    uVar1 = 0;
  }
  return uVar1;
}
// FUN_18003f980 @ 18003f980
undefined8 FUN_18003f980(short param_1)
{
  if (((param_1 != 0x2e) && (param_1 != -0xf2)) && (param_1 != 0x6d4)) {
    return 0;
  }
  return 1;
}
// FUN_18003f4f4 @ 18003f4f4
undefined8 FUN_18003f4f4(short param_1)
{
  if ((((param_1 != 0x2c) && (param_1 != 0x2f)) && (param_1 != 0x3a)) && (param_1 != 0x3b)) {
    return 0;
  }
  return 1;
}
// FUN_18003f324 @ 18003f324
undefined8 FUN_18003f324(ushort param_1)
{
  bool bVar1;
  if (param_1 < 0xb6) {
    if (param_1 == 0xb5) {
      return 1;
    }
    if (param_1 < 0x7d) {
      if (param_1 == 0x7c) {
        return 1;
      }
      if (param_1 == 0x23) {
        return 1;
      }
      if (param_1 == 0x25) {
        return 1;
      }
      if (param_1 == 0x26) {
        return 1;
      }
      if (param_1 == 0x2a) {
        return 1;
      }
      if (param_1 == 0x40) {
        return 1;
      }
      bVar1 = param_1 == 0x5c;
    }
    else {
      if (param_1 == 0xa6) {
        return 1;
      }
      if (param_1 == 0xa7) {
        return 1;
      }
      if (param_1 == 0xa9) {
        return 1;
      }
      if (param_1 == 0xae) {
        return 1;
      }
      bVar1 = param_1 == 0xb0;
    }
  }
  else if (param_1 < 0x2104) {
    if (param_1 == 0x2103) {
      return 1;
    }
    if (param_1 == 0xb6) {
      return 1;
    }
    if (param_1 == 0xb7) {
      return 1;
    }
    if (param_1 == 0x2020) {
      return 1;
    }
    if (param_1 == 0x2021) {
      return 1;
    }
    bVar1 = param_1 == 0x2030;
  }
  else {
    if (param_1 == 0x2105) {
      return 1;
    }
    if (param_1 == 0x2106) {
      return 1;
    }
    if (param_1 == 0x2109) {
      return 1;
    }
    if (param_1 == 0x2116) {
      return 1;
    }
    bVar1 = param_1 == 0x2122;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}
// FUN_18003f51c @ 18003f51c
undefined8 FUN_18003f51c(ushort param_1)
{
  bool bVar1;
  if (param_1 < 0x2212) {
    if (param_1 == 0x2211) {
      return 1;
    }
    if (param_1 == 0x2b) {
      return 1;
    }
    if (param_1 == 0x3c) {
      return 1;
    }
    if (param_1 == 0x3d) {
      return 1;
    }
    if (param_1 == 0x3e) {
      return 1;
    }
    if (param_1 == 0xac) {
      return 1;
    }
    if (param_1 == 0xb1) {
      return 1;
    }
    if (param_1 == 0xd7) {
      return 1;
    }
    bVar1 = param_1 == 0xf7;
  }
  else {
    if (param_1 == 0x221a) {
      return 1;
    }
    if (param_1 == 0x221e) {
      return 1;
    }
    if (param_1 == 0x222b) {
      return 1;
    }
    if (param_1 == 0x2248) {
      return 1;
    }
    if (param_1 == 0x2260) {
      return 1;
    }
    if (param_1 == 0x2264) {
      return 1;
    }
    bVar1 = param_1 == 0x2265;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}
// FUN_18003f474 @ 18003f474
undefined8 FUN_18003f474(short param_1)
{
  if ((((param_1 != 0x2022) && (param_1 != 0x25a1)) && (param_1 != 0x25aa)) &&
     (((param_1 != 0x25ab && (param_1 != 0x25ca)) && ((param_1 != 0x25cf && (param_1 != 0x25e6))))))
  {
    return 0;
  }
  return 1;
}
// FUN_18003f3cc @ 18003f3cc
undefined8 FUN_18003f3cc(ushort param_1)
{
  uint uVar1;
  int iVar2;
  bool bVar3;
  uVar1 = (uint)param_1;
  if (param_1 < 0x20a5) {
    if (param_1 == 0x20a4) {
      return 1;
    }
    if (0x9f2 < uVar1) {
      if (uVar1 == 0x9f3) {
        return 1;
      }
      if (uVar1 == 0xe3f) {
        return 1;
      }
      iVar2 = uVar1 - 0x20a0;
      if (iVar2 == 0) {
        return 1;
      }
      goto LAB_18003f3f1;
    }
    if (uVar1 == 0x9f2) {
      return 1;
    }
    if (uVar1 == 0x24) {
      return 1;
    }
    iVar2 = uVar1 - 0xa2;
    bVar3 = iVar2 == 0;
  }
  else if (uVar1 < 0x20ac) {
    if (uVar1 == 0x20ab) {
      return 1;
    }
    if (uVar1 == 0x20a6) {
      return 1;
    }
    iVar2 = uVar1 - 0x20a7;
    bVar3 = iVar2 == 0;
  }
  else {
    iVar2 = uVar1 - 0x20ac;
    bVar3 = iVar2 == 0;
  }
  if (bVar3) {
    return 1;
  }
  if (iVar2 == 1) {
    return 1;
  }
LAB_18003f3f1:
  if ((iVar2 != 2) && (iVar2 != 3)) {
    return 0;
  }
  return 1;
}
// FUN_18003f4b4 @ 18003f4b4
undefined8 FUN_18003f4b4(short param_1)
{
  if ((((param_1 != 0x2d) && (param_1 != 0x2010)) && (param_1 != 0x2012)) &&
     (((param_1 != 0x2013 && (param_1 != 0x2014)) && ((param_1 != 0x2015 && (param_1 != 0x2212))))))
  {
    return 0;
  }
  return 1;
}
// FUN_18003f44c @ 18003f44c
undefined8 FUN_18003f44c(short param_1)
{
  if ((param_1 != 0xbf) && (param_1 != 0xa1)) {
    return 0;
  }
  return 1;
}
// FUN_18003f8fc @ 18003f8fc
uint FUN_18003f8fc(ushort param_1)
{
  uint uVar1;
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 4;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x400000;
  }
  return uVar1;
}
// FUN_180161120 @ 180161120
bool FUN_180161120(longlong param_1,ushort *param_2,uint param_3,longlong param_4,
                  undefined1 *param_5)
{
  longlong lVar1;
  ushort *puVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  longlong *plVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  ushort uVar12;
  ushort *puVar13;
  ushort *puVar14;
  ulonglong uVar15;
  bool bVar16;
  undefined1 auStack_1b8 [32];
  longlong local_198;
  uint local_190;
  uint local_18c;
  undefined1 *local_188;
  longlong local_180;
  ushort *local_178;
  ulonglong local_170;
  undefined8 uStack_168;
  ushort local_158 [128];
  ulonglong local_58;
  local_58 = DAT_1801c0240 ^ (ulonglong)auStack_1b8;
  uVar11 = 0;
  puVar14 = param_2 + param_3;
  local_198 = param_1;
  puVar13 = param_2;
  local_178 = param_2;
  local_18c = param_3;
  local_180 = param_4;
  local_188 = param_5;
  while (((puVar13 < puVar14 && (uVar4 = FUN_18003f58c(*puVar13), uVar4 == 0)) &&
         (uVar4 = FUN_18003f9ac(*puVar13), uVar4 != 0))) {
    puVar13 = puVar13 + 1;
  }
  if ((puVar13 + 1 < puVar14) && (puVar2 = puVar13 + 1, (*puVar13 - 0x2c & 0xfffd) == 0)) {
    while (puVar13 = puVar2, uVar4 = FUN_18003f58c(*puVar13), uVar4 == 0) {
      uVar4 = FUN_18003f9ac(*puVar13);
      if ((uVar4 == 0) || (puVar13 = puVar13 + 1, puVar2 = puVar13, puVar14 <= puVar13)) break;
    }
  }
  uVar4 = param_3 - (int)((longlong)puVar13 - (longlong)param_2 >> 1);
  local_190 = uVar4;
  if ((puVar13 == param_2) || (2 < uVar4)) {
    if (uVar4 < 0x80) {
      plVar8 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x20))();
      uVar9 = FUN_180061864((longlong)puVar13,uVar4,plVar8);
      if (-1 < (int)uVar9) {
        return true;
      }
      uVar5 = FUN_1801619e4(*puVar13);
      if ((uVar5 == 0) || (uVar4 < 3)) {
        FUN_180058730((short *)local_158,0x80,(longlong)puVar13,(ulonglong)uVar4);
      }
      else {
        FUN_180058730((short *)local_158,0x80,(longlong)puVar13,(ulonglong)uVar4);
        uVar5 = FUN_1801631c8(local_158,uVar4);
        if (uVar5 == uVar4) {
          plVar8 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x20))();
          uVar9 = FUN_180061864((longlong)local_158,uVar4,plVar8);
          if (-1 < (int)uVar9) {
            return true;
          }
        }
        FUN_180058730((short *)local_158,0x80,(longlong)puVar13,(ulonglong)uVar4);
        lVar1 = local_180;
        puVar13 = local_158;
        uVar9 = uVar11;
        uVar15 = uVar11;
        param_1 = local_198;
        if (local_158[0] != 0) {
          do {
            uVar3 = local_158[0];
            if ((int)uVar15 == 0) {
              uVar3 = *puVar13;
              if (uVar3 < 0x100) {
                if ((uVar3 & 0xff00) == 0) {
                  if (((&DAT_180180820)[(ulonglong)uVar3 & 0xff] & 0x80) == 0) {
                    uVar12 = (ushort)(byte)(&DAT_180193c50)[(byte)uVar3];
                    goto LAB_18016133d;
                  }
                }
                else {
                  uVar15 = (ulonglong)uVar3 - 0x2018;
                  uVar12 = uVar3;
                  if (uVar15 < 8) {
                    uVar12 = *(ushort *)(&DAT_180193dd8 + uVar15 * 2);
                  }
LAB_18016133d:
                  uVar15 = uVar11;
                  if (uVar12 != 0x79) goto LAB_180161377;
                }
                uVar15 = 1;
              }
              else if (lVar1 != 0) {
                local_170 = 0;
                uStack_168 = 0;
                iVar6 = FUN_18005bbcc(lVar1,(uint)uVar3,(undefined4 *)&local_170);
                if ((iVar6 != 0) && ((local_170 & 0x100000000) != 0)) {
                  uVar15 = 1;
                }
              }
            }
LAB_180161377:
            uVar5 = FUN_180066b20(uVar3);
            puVar13 = puVar13 + 1;
            uVar5 = (uint)uVar9 | uVar5;
            local_158[0] = *puVar13;
            uVar9 = (ulonglong)uVar5;
          } while (local_158[0] != 0);
          param_2 = local_178;
          param_1 = local_198;
          uVar4 = local_190;
          if (((int)uVar15 == 0) && (uVar5 != 0)) {
            return true;
          }
        }
      }
      if ((3 < uVar4) && ((uVar4 & 1) == 0)) {
        bVar16 = local_188 != (undefined1 *)0x0;
        puVar14 = local_158;
        uVar9 = uVar11;
        do {
          uVar5 = (uint)uVar9;
          if ((uVar9 & 1) == 0) {
            uVar7 = FUN_18003f58c(*puVar14);
            if (uVar7 == 0) break;
            if ((bVar16) && (uVar7 = FUN_1801619e4(*puVar14), uVar7 != 0)) {
              bVar16 = true;
            }
            else {
              bVar16 = false;
            }
          }
          else {
            uVar10 = FUN_18003f980(*puVar14);
            if ((int)uVar10 == 0) break;
          }
          uVar5 = uVar5 + 1;
          uVar9 = (ulonglong)uVar5;
          puVar14 = puVar14 + 1;
        } while (uVar5 < uVar4);
        param_1 = local_198;
        if (uVar4 <= uVar5) {
          if (local_188 == (undefined1 *)0x0) {
            return true;
          }
          if (!bVar16) {
            return true;
          }
          *local_188 = 1;
          return true;
        }
      }
      uVar3 = (**(code **)(**(longlong **)(param_1 + 0x80) + 0x68))();
      if ((((uVar3 & 0x3ff) == 10) && (5 < uVar4)) && (uVar4 == (uVar4 / 3) * 3)) {
        puVar14 = local_158;
        do {
          uVar5 = (uint)uVar11;
          iVar6 = (int)(uVar11 / 3);
          uVar3 = *puVar14;
          if (uVar5 == iVar6 * 3) {
            uVar7 = FUN_18003f58c(uVar3);
LAB_1801614f1:
            if (uVar7 == 0) break;
          }
          else {
            if (uVar5 + iVar6 * -3 != 1) {
              uVar10 = FUN_18003f980(uVar3);
              uVar7 = (uint)uVar10;
              goto LAB_1801614f1;
            }
            if (uVar3 != local_158[uVar5 - 1]) break;
          }
          uVar5 = uVar5 + 1;
          uVar11 = (ulonglong)uVar5;
          puVar14 = puVar14 + 1;
        } while (uVar5 < uVar4);
        param_1 = local_198;
        if (uVar4 <= uVar5) {
          return true;
        }
      }
      param_3 = local_18c;
      if (puVar13 != param_2) goto LAB_180161519;
    }
    bVar16 = false;
  }
  else {
LAB_180161519:
    plVar8 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x20))();
    uVar11 = FUN_180061864((longlong)param_2,param_3,plVar8);
    bVar16 = -1 < (int)uVar11;
  }
  return bVar16;
}
// FUN_180161888 @ 180161888
uint FUN_180161888(longlong param_1,ushort *param_2,uint param_3,int param_4)
{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined1 auStack_138 [32];
  ushort local_118 [128];
  ulonglong local_18;
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_138;
  if (param_3 < 0x80) {
    if (param_4 == 0) {
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x40))();
    }
    else {
      FUN_180058730((short *)local_118,0x80,(longlong)param_2,(ulonglong)param_3);
      uVar1 = FUN_1801631c8(local_118,param_3);
      if (uVar1 != param_3) goto LAB_180161934;
      uVar3 = FUN_180163284(local_118[0]);
      local_118[0] = (ushort)uVar3;
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x40))();
      param_2 = local_118;
    }
    uVar3 = FUN_180061864((longlong)param_2,param_3,plVar2);
    uVar1 = ~(uint)uVar3 >> 0x1f;
  }
  else {
LAB_180161934:
    uVar1 = 0;
  }
  return uVar1;
}
// FUN_180161964 @ 180161964
undefined4 FUN_180161964(undefined8 param_1,ushort param_2)
{
  uint uVar1;
  uVar1 = FUN_18003f9ac(param_2);
  if (uVar1 == 0) {
    if (param_2 == 0xad) {
      return 1;
    }
  }
  else if (1 < (ushort)(param_2 + 0x1800)) {
    return 1;
  }
  if (param_2 == 0x5f) {
    return 1;
  }
  return 0;
}
// FUN_18016345c @ 18016345c
void FUN_18016345c(undefined8 param_1,longlong *param_2,undefined4 *param_3,undefined4 *param_4)
{
  ushort uVar1;
  uVar1 = *(ushort *)(*param_2 + (ulonglong)*(uint *)((longlong)param_2 + 0xc) * 2);
  if (uVar1 < 0x300e) {
    if (uVar1 == 0x300d) {
LAB_18016357e:
      *param_3 = 5;
LAB_180163533:
      *param_4 = 0xffffffff;
      return;
    }
    if (0x7d < uVar1) {
      if (uVar1 != 0x2018) {
        if (uVar1 == 0x2019) {
          *param_3 = 3;
          goto LAB_180163533;
        }
        if (uVar1 == 0x201c) {
          *param_3 = 4;
          goto LAB_1801634bc;
        }
        if (uVar1 == 0x201d) {
          *param_3 = 4;
          goto LAB_180163533;
        }
        if (uVar1 != 0x300c) {
          return;
        }
      }
LAB_1801634e4:
      *param_3 = 3;
      goto LAB_1801634bc;
    }
    if (uVar1 == 0x7d) {
LAB_180163587:
      *param_3 = 1;
      goto LAB_180163533;
    }
    if (uVar1 != 0x28) {
      if (uVar1 == 0x29) {
LAB_18016352f:
        *param_3 = 0;
        goto LAB_180163533;
      }
      if (uVar1 == 0x5b) {
LAB_18016352a:
        *param_3 = 2;
        goto LAB_1801634bc;
      }
      if (uVar1 == 0x5d) goto LAB_180163557;
      if (uVar1 != 0x7b) {
        return;
      }
      goto LAB_1801634b5;
    }
  }
  else {
    if (0xff3d < uVar1) {
      if (uVar1 == 0xff5b) {
LAB_1801634b5:
        *param_3 = 1;
        goto LAB_1801634bc;
      }
      if (uVar1 == 0xff5d) goto LAB_180163587;
      if (uVar1 == 0xff62) goto LAB_1801634e4;
      if (uVar1 != 0xff63) {
        return;
      }
      goto LAB_18016357e;
    }
    if (uVar1 == 0xff3d) {
LAB_180163557:
      *param_3 = 2;
      goto LAB_180163533;
    }
    if (uVar1 == 0x300e) {
      *param_3 = 6;
      goto LAB_1801634bc;
    }
    if (uVar1 == 0x300f) {
      *param_3 = 6;
      goto LAB_180163533;
    }
    if (uVar1 != 0xff08) {
      if (uVar1 != 0xff09) {
        if (uVar1 != 0xff3b) {
          return;
        }
        goto LAB_18016352a;
      }
      goto LAB_18016352f;
    }
  }
  *param_3 = 0;
LAB_1801634bc:
  *param_4 = 1;
  return;
}
// FUN_180163210 @ 180163210
ulonglong FUN_180163210(ushort param_1)
{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined6 extraout_var;
  if ((param_1 & 0xff00) == 0) {
    if ((((&DAT_180180820)[(ulonglong)param_1 & 0xff] & 1) != 0) &&
       (uVar3 = _o_tolower((ulonglong)param_1), ((&DAT_180180820)[uVar3 & 0xff] & 2) != 0)) {
      return uVar3;
    }
  }
  else {
    uVar2 = FUN_180072dbc(param_1);
    if ((uVar2 >> 0x14 & 1) != 0) {
      uVar1 = FUN_180162b68(param_1,-1,0x200000);
      return CONCAT62(extraout_var,uVar1);
    }
  }
  return (ulonglong)param_1;
}
// FUN_1800774f8 @ 1800774f8
longlong FUN_1800774f8(longlong param_1,int param_2)
{
  *(int *)(param_1 + 8) = param_2;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return param_1;
}
// FUN_1801619b4 @ 1801619b4
bool FUN_1801619b4(ushort param_1)
{
  if ((param_1 & 0xff00) != 0) {
    return false;
  }
  return ((&DAT_180180820)[(ulonglong)param_1 & 0xff] & 0x14) == 4;
}
// FUN_18005bbcc @ 18005bbcc
undefined4 FUN_18005bbcc(longlong param_1,undefined4 param_2,undefined4 *param_3)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_res10 [2];
  uVar2 = 0;
  if ((*(longlong *)(param_1 + 0x10) != 0) && (uVar2 = 0, *(int *)(param_1 + 8) != 0)) {
    local_res10[0] = param_2;
    puVar1 = (undefined4 *)
             _o_bsearch(local_res10,*(longlong *)(param_1 + 0x10),*(undefined4 *)(param_1 + 8),0x10,
                        FUN_18004e7e0);
    if (puVar1 != (undefined4 *)0x0) {
      uVar2 = 1;
      *param_3 = *puVar1;
      *(undefined2 *)(param_3 + 1) = *(undefined2 *)(puVar1 + 1);
      *(ulonglong *)(param_3 + 2) = (ulonglong)(uint)puVar1[2] + *(longlong *)(param_1 + 0x18);
      *(ulonglong *)(param_3 + 4) = (ulonglong)(uint)puVar1[3] + *(longlong *)(param_1 + 0x18);
    }
  }
  return uVar2;
}
// FUN_180163284 @ 180163284
ulonglong FUN_180163284(ushort param_1)
{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined6 extraout_var;
  if ((param_1 & 0xff00) == 0) {
    if (((&DAT_180180820)[(ulonglong)param_1 & 0xff] & 2) != 0) {
      if (param_1 == 0xff) {
        return 0x178;
      }
      uVar3 = _o_toupper((ulonglong)param_1);
      if (((&DAT_180180820)[uVar3 & 0xff] & 1) != 0) {
        return uVar3;
      }
    }
  }
  else {
    uVar2 = FUN_180072dbc(param_1);
    if ((uVar2 >> 0x15 & 1) != 0) {
      uVar1 = FUN_180162b68(param_1,1,0x100000);
      return CONCAT62(extraout_var,uVar1);
    }
  }
  return (ulonglong)param_1;
}
// FUN_180162b68 @ 180162b68
ushort FUN_180162b68(ushort param_1,short param_2,uint param_3)
{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  bool bVar5;
  uVar3 = FUN_180072dbc(param_1);
  if ((param_3 & uVar3) != 0) {
    return param_1;
  }
  uVar1 = param_1 >> 8;
  uVar4 = param_1;
  if (uVar1 < 0x11) {
    if (uVar1 == 0x10) {
LAB_180162bc6:
      sVar2 = param_2 * 2;
LAB_180162c20:
      param_2 = param_2 + sVar2;
LAB_180162c23:
      param_2 = param_2 << 4;
    }
    else if (uVar1 == 1) {
      if (param_1 < 0x19e) {
        if (param_1 == 0x19d) {
LAB_180162f62:
          sVar2 = 0xd5;
        }
        else if (param_1 < 400) {
          if (param_1 == 399) {
LAB_180162f11:
            sVar2 = 0xca;
          }
          else {
            if (param_1 == 0x130) {
              return 0x130;
            }
            if (param_1 == 0x131) {
              return 0x131;
            }
            if (param_1 == 0x178) {
              uVar4 = 0xff;
              goto LAB_180162bf2;
            }
            if (param_1 == 0x181) goto LAB_180162ef4;
            if (param_1 == 0x186) goto LAB_180162eed;
            if ((param_1 != 0x189) && (param_1 != 0x18a)) {
              if (param_1 == 0x18e) goto LAB_180162ede;
              goto LAB_180162bef;
            }
LAB_180162ee6:
            sVar2 = 0xcd;
          }
        }
        else if (param_1 == 400) {
LAB_180162f5b:
          sVar2 = 0xcb;
        }
        else {
          if (param_1 == 0x193) goto LAB_180162ee6;
          if (param_1 == 0x194) {
LAB_180162f54:
            sVar2 = 0xcf;
          }
          else {
            if (param_1 == 0x195) {
              return 0x195;
            }
            if (param_1 != 0x196) {
              if (param_1 == 0x197) {
LAB_180162f4d:
                sVar2 = 0xd1;
                goto LAB_180162ef9;
              }
              if (param_1 != 0x19c) goto LAB_180162bef;
            }
LAB_180162f46:
            sVar2 = 0xd3;
          }
        }
LAB_180162ef9:
        sVar2 = param_2 * sVar2;
        goto LAB_180162eff;
      }
      if (param_1 < 0x1c7) {
        if (param_1 != 0x1c6) {
          if (param_1 == 0x19e) {
            return 0x19e;
          }
          if (param_1 == 0x19f) {
LAB_180162fbb:
            sVar2 = 0xd6;
          }
          else if ((param_1 == 0x1a9) || (param_1 == 0x1ae)) {
LAB_180162fb1:
            sVar2 = 0xda;
          }
          else if ((param_1 == 0x1b1) || (param_1 == 0x1b2)) {
LAB_180162fa7:
            sVar2 = 0xd9;
          }
          else {
            if (param_1 != 0x1b7) {
              bVar5 = param_1 == 0x1c4;
              goto LAB_180162fed;
            }
LAB_180162e82:
            sVar2 = 0xdb;
          }
          goto LAB_180162ef9;
        }
      }
      else if ((((param_1 != 0x1c7) && (param_1 != 0x1c9)) && (param_1 != 0x1ca)) &&
              (param_1 != 0x1cc)) {
        if (param_1 == 0x1dd) {
LAB_180162ede:
          sVar2 = param_2 * 0x4f;
          goto LAB_180162eff;
        }
        if (param_1 != 0x1f1) {
          bVar5 = param_1 == 499;
LAB_180162fed:
          if (!bVar5) goto LAB_180162bef;
        }
      }
      param_2 = param_2 * 2;
    }
    else if (uVar1 == 2) {
      if (0x217 < param_1) {
        if (param_1 < 0x254) {
LAB_180162ef4:
          sVar2 = 0xd2;
        }
        else {
          if (0x254 < param_1) {
            if (599 < param_1) {
              if (param_1 < 0x259) goto LAB_180162bf2;
              if (param_1 < 0x25a) goto LAB_180162f11;
              if (param_1 < 0x25b) goto LAB_180162bf2;
              if (param_1 < 0x25c) goto LAB_180162f5b;
              if (param_1 < 0x25f) goto LAB_180162bf2;
              if (0x260 < param_1) {
                if (0x263 < param_1) {
                  if (param_1 < 0x268) goto LAB_180162bf2;
                  if (param_1 < 0x269) goto LAB_180162f4d;
                  if (0x269 < param_1) {
                    if (param_1 < 0x26c) goto LAB_180162bf2;
                    if (0x26f < param_1) {
                      if (param_1 < 0x272) goto LAB_180162bf2;
                      if (0x272 < param_1) {
                        if (param_1 < 0x274) goto LAB_180162bf2;
                        if (0x275 < param_1) {
                          if (param_1 < 0x27f) goto LAB_180162bf2;
                          if (0x283 < param_1) {
                            if (param_1 < 0x287) goto LAB_180162bf2;
                            if (0x288 < param_1) {
                              if (0x28b < param_1) {
                                if ((param_1 < 0x291) || ((0x292 < param_1 && (param_1 < 0x2a9))))
                                goto LAB_180162bf2;
                                goto LAB_180162e82;
                              }
                              goto LAB_180162fa7;
                            }
                          }
                          goto LAB_180162fb1;
                        }
                        goto LAB_180162fbb;
                      }
                      goto LAB_180162f62;
                    }
                  }
                  goto LAB_180162f46;
                }
                goto LAB_180162f54;
              }
            }
            goto LAB_180162ee6;
          }
LAB_180162eed:
          sVar2 = 0xce;
        }
        goto LAB_180162ef9;
      }
    }
    else if (uVar1 == 3) {
      if (0x3ef < param_1) {
        return param_1;
      }
      if (((byte)param_1 & 0xf0) == 0xd0) {
        return param_1;
      }
      if (param_1 < 0x387) {
LAB_180162c8c:
        sVar2 = param_2 * 0x26;
        goto LAB_180162eff;
      }
      if (param_1 < 0x38b) {
LAB_180162ca1:
        sVar2 = param_2 * 0x25;
        goto LAB_180162eff;
      }
      if (param_1 < 0x38d) {
LAB_180162c59:
        param_2 = param_2 << 6;
      }
      else {
        if (param_1 < 0x390) {
LAB_180162c69:
          sVar2 = param_2 * 0x3f;
          goto LAB_180162eff;
        }
        if (0x3ab < param_1) {
          if (param_1 < 0x3ad) goto LAB_180162c8c;
          if (param_1 < 0x3b0) goto LAB_180162ca1;
          if (0x3c1 < param_1) {
            if (param_1 < 0x3c3) {
              sVar2 = param_2 * 0x1f;
              goto LAB_180162eff;
            }
            if (0x3cb < param_1) {
              if (param_1 < 0x3cd) goto LAB_180162c59;
              if (0x3cf < param_1) goto LAB_180162bef;
              goto LAB_180162c69;
            }
          }
        }
LAB_180162beb:
        param_2 = param_2 << 5;
      }
    }
    else {
      if (uVar1 != 4) {
        if (uVar1 != 5) {
          return param_1;
        }
        goto LAB_180162bc6;
      }
      if (((param_1 & 0xf0) == 0) || ((param_1 & 0xf0) == 0x50)) {
        sVar2 = param_2 << 2;
        goto LAB_180162c20;
      }
      if (param_1 < 0x460) goto LAB_180162beb;
    }
LAB_180162bef:
    uVar4 = param_1 - param_2;
  }
  else {
    if (uVar1 == 0x1e) goto LAB_180162bef;
    if (uVar1 == 0x1f) {
      if (param_1 < 0x1f70) goto LAB_180163174;
      if (param_1 < 0x1f72) {
LAB_1801630d8:
        sVar2 = param_2 * 0x4a;
      }
      else if (param_1 < 0x1f76) {
LAB_1801630fb:
        sVar2 = param_2 * 0x56;
      }
      else if (param_1 < 0x1f78) {
LAB_180163140:
        sVar2 = param_2 * 100;
      }
      else if (param_1 < 0x1f7a) {
LAB_1801631a6:
        sVar2 = param_2 * 0x80;
      }
      else if (param_1 < 0x1f7c) {
LAB_18016318a:
        sVar2 = param_2 * 0x70;
      }
      else {
        if (0x1f7d < param_1) {
          if (param_1 < 0x1fb0) goto LAB_180162bf2;
          if (0x1fb1 < param_1) {
            if (param_1 < 0x1fb5) goto LAB_180162bf2;
            if (0x1fb9 < param_1) {
              if (param_1 < 0x1fbc) goto LAB_1801630d8;
              if (param_1 < 0x1fbd) goto LAB_180162bf2;
              if (param_1 < 0x1fcc) goto LAB_1801630fb;
              if (param_1 < 0x1fcd) goto LAB_180162bf2;
              if (0x1fd1 < param_1) {
                if (param_1 < 0x1fd4) goto LAB_180162bf2;
                if (0x1fd9 < param_1) {
                  if (param_1 < 0x1fdc) goto LAB_180163140;
                  if (0x1fe1 < param_1) {
                    if (param_1 < 0x1fe5) goto LAB_180162bf2;
                    if (0x1fe5 < param_1) {
                      if (param_1 < 0x1fea) goto LAB_180163174;
                      if (param_1 < 0x1fec) goto LAB_18016318a;
                      if (param_1 != 0x1fec) {
                        if (param_1 < 0x1ffa) goto LAB_1801631a6;
                        goto LAB_1801631b3;
                      }
                    }
                    sVar2 = param_2 * 7;
                    goto LAB_1801631b9;
                  }
                }
              }
            }
          }
LAB_180163174:
          uVar4 = param_1 + param_2 * 8;
          goto LAB_180162bf2;
        }
LAB_1801631b3:
        sVar2 = param_2 * 0x7e;
      }
LAB_1801631b9:
      uVar4 = sVar2 + param_1;
      goto LAB_180162bf2;
    }
    if (uVar1 == 0x21) goto LAB_180162c23;
    if (uVar1 != 0x24) {
      if (uVar1 != 0xff) {
        return param_1;
      }
      goto LAB_180162beb;
    }
    sVar2 = param_2 * 0x1a;
LAB_180162eff:
    uVar4 = param_1 - sVar2;
  }
LAB_180162bf2:
  uVar3 = FUN_180072dbc(uVar4);
  if ((param_3 & uVar3) != 0) {
    param_1 = uVar4;
  }
  return param_1;
}
// FUN_18004e7e0 @ 18004e7e0
int FUN_18004e7e0(uint *param_1,uint *param_2)
{
  if (*param_1 <= *param_2) {
    return -(uint)(*param_1 != *param_2);
  }
  return 1;
}
