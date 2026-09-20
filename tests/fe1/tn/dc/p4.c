// FUN_18000ecb4 @ 18000ecb4

undefined8 FUN_18000ecb4(undefined8 param_1,ushort param_2,ushort *param_3)

{
  short *psVar1;
  undefined8 uVar2;
  longlong lVar3;
  ushort uVar4;
  
  if (param_2 < *param_3) {
    return 0;
  }
  lVar3 = 0;
  if (param_2 == 0xffff) goto LAB_18000ed15;
  uVar4 = param_2 - *param_3;
  lVar3 = *(longlong *)(param_3 + 4);
  do {
    lVar3 = *(longlong *)(lVar3 + (ulonglong)(uVar4 >> 0xe) * 8) +
            (ulonglong)(uVar4 & 0x3fff) * 0x12;
LAB_18000ed15:
    do {
      if ((lVar3 == 0) || (*(ushort *)(lVar3 + 0xc) == 0)) {
        return 1;
      }
      uVar2 = FUN_18000ecb4(param_1,*(ushort *)(lVar3 + 0xc),param_3);
      if ((int)uVar2 == 0) {
        return 0;
      }
      uVar2 = FUN_18000ecb4(param_1,*(ushort *)(lVar3 + 0xe),param_3);
      if ((int)uVar2 == 0) {
        return 0;
      }
      psVar1 = (short *)(lVar3 + 0x10);
      lVar3 = 0;
    } while (*psVar1 == -1);
    uVar4 = *psVar1 - *param_3;
    lVar3 = *(longlong *)(param_3 + 4);
  } while( true );
}


// FUN_18000e708 @ 18000e708

int FUN_18000e708(undefined8 param_1,ushort param_2,undefined8 *param_3,longlong param_4,
                 ushort *param_5)

{
  short *psVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined1 auVar4 [16];
  int iVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  longlong lVar9;
  void *pvVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  ushort uVar13;
  ushort uVar14;
  ushort uVar15;
  ushort uVar16;
  
  iVar5 = 0;
  uVar15 = 0;
  if ((param_2 == 0xffff) ||
     (lVar2 = *(longlong *)
               (*(longlong *)(param_5 + 4) + (ulonglong)((ushort)(param_2 - *param_5) >> 0xe) * 8) +
              (ulonglong)((ushort)(param_2 - *param_5) & 0x3fff) * 0x12, lVar2 == 0)) {
    return -0x7ff8ffa9;
  }
  uVar14 = *(ushort *)(lVar2 + 0xc);
  uVar7 = param_1;
  if ((uVar14 != 0) && (uVar15 = 0, uVar6 = FUN_18000ecb4(param_1,uVar14,param_5), (int)uVar6 == 0))
  {
    uVar15 = 1;
  }
  uVar13 = *(ushort *)(lVar2 + 0xe);
  uVar6 = FUN_18000ecb4(uVar7,uVar13,param_5);
  uVar16 = uVar15 + 1;
  if ((int)uVar6 != 0) {
    uVar16 = uVar15;
  }
  if (uVar16 == 1) {
    uVar7 = FUN_18000ecb4(uVar7,uVar13,param_5);
    if ((int)uVar7 != 0) {
      uVar13 = uVar14;
    }
    puVar8 = (undefined8 *)FUN_18007ca58(0x40);
    if (puVar8 == (undefined8 *)0x0) {
LAB_18000ec64:
      *param_3 = 0;
    }
    else {
      *puVar8 = 0xffffffffffffffff;
      *(undefined4 *)((longlong)puVar8 + 0xc) = 3;
      *(undefined2 *)((longlong)puVar8 + 0x12) = 0xffff;
      *(undefined4 *)(puVar8 + 4) = 3;
      *(undefined2 *)(puVar8 + 1) = 0;
      *(undefined2 *)(puVar8 + 2) = 0;
      puVar8[3] = 0;
      *(undefined2 *)((longlong)puVar8 + 0x24) = 0;
      puVar8[5] = 0;
      puVar8[6] = 0;
      *(undefined2 *)(puVar8 + 7) = 1;
      *(undefined4 *)((longlong)puVar8 + 0x3c) = 0;
      *param_3 = puVar8;
      if (puVar8 != (undefined8 *)0x0) {
        *(undefined4 *)((longlong)puVar8 + 0xc) = 0;
        *(undefined2 *)puVar8 = *(undefined2 *)(lVar2 + 2);
        *(undefined2 *)((longlong)puVar8 + 4) = *(undefined2 *)(lVar2 + 6);
        *(undefined2 *)((longlong)puVar8 + 6) = *(undefined2 *)(lVar2 + 8);
        *(undefined2 *)(puVar8 + 2) = 1;
        lVar9 = SUB168(ZEXT416(8) * ZEXT816(1),0);
        if (SUB168(ZEXT416(8) * ZEXT816(1),8) != 0) {
          lVar9 = -1;
        }
        pvVar10 = (void *)thunk_FUN_18007ca58(lVar9);
        *(ushort *)((longlong)puVar8 + 2) = param_2;
        puVar8[3] = pvVar10;
        *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(lVar2 + 10);
        if (pvVar10 == (void *)0x0) {
LAB_18000e9c1:
          *(undefined2 *)(puVar8 + 2) = 0;
        }
        else {
          memset(pvVar10,0,8);
          if (param_4 != 0) {
            lVar9 = *(longlong *)(param_4 + (ulonglong)uVar13 * 8);
            if (lVar9 != 0) {
              *(longlong *)puVar8[3] = lVar9;
              psVar1 = (short *)(*(longlong *)(param_4 + (ulonglong)uVar13 * 8) + 0x38);
              *psVar1 = *psVar1 + 1;
              goto LAB_18000ec72;
            }
          }
          if (*param_5 <= uVar13) {
            puVar8 = (undefined8 *)puVar8[3];
LAB_18000e90d:
            iVar5 = FUN_18000e440(param_1,uVar13,puVar8,param_4,param_5);
            goto LAB_18000ec6d;
          }
          puVar11 = (undefined8 *)FUN_18007ca58(0x40);
          if (puVar11 != (undefined8 *)0x0) {
            *puVar11 = 0xffffffffffffffff;
            *(undefined2 *)((longlong)puVar11 + 0x12) = 0xffff;
            *(undefined2 *)(puVar11 + 1) = 0;
            *(undefined4 *)((longlong)puVar11 + 0xc) = 3;
            *(undefined2 *)(puVar11 + 2) = 0;
            puVar11[3] = 0;
            *(undefined4 *)(puVar11 + 4) = 3;
            *(undefined2 *)((longlong)puVar11 + 0x24) = 0;
            puVar11[5] = 0;
            puVar11[6] = 0;
            *(undefined2 *)(puVar11 + 7) = 1;
            *(undefined4 *)((longlong)puVar11 + 0x3c) = 0;
            if (puVar11 != (undefined8 *)0x0) {
              *(undefined4 *)((longlong)puVar11 + 0xc) = 0;
              *(undefined2 *)puVar11 = *(undefined2 *)(lVar2 + 2);
              *(undefined2 *)((longlong)puVar11 + 4) = *(undefined2 *)(lVar2 + 6);
              *(undefined2 *)((longlong)puVar11 + 6) = *(undefined2 *)(lVar2 + 8);
              *(ushort *)((longlong)puVar11 + 2) = uVar13;
              *(undefined2 *)(puVar11 + 2) = 0;
              puVar11[3] = 0;
              *(undefined2 *)(puVar11 + 1) = *(undefined2 *)(lVar2 + 10);
              *(undefined8 **)puVar8[3] = puVar11;
              goto LAB_18000ec6d;
            }
          }
        }
      }
    }
LAB_18000ec68:
    iVar5 = -0x7ff8fff2;
  }
  else {
    puVar8 = (undefined8 *)FUN_18007ca58(0x40);
    if (puVar8 == (undefined8 *)0x0) goto LAB_18000ec64;
    *puVar8 = 0xffffffffffffffff;
    *(undefined4 *)((longlong)puVar8 + 0xc) = 3;
    *(undefined2 *)((longlong)puVar8 + 0x12) = 0xffff;
    *(undefined4 *)(puVar8 + 4) = 3;
    *(undefined2 *)(puVar8 + 1) = 0;
    *(undefined2 *)(puVar8 + 2) = 0;
    puVar8[3] = 0;
    *(undefined2 *)((longlong)puVar8 + 0x24) = 0;
    puVar8[5] = 0;
    puVar8[6] = 0;
    *(undefined2 *)(puVar8 + 7) = 1;
    *(undefined4 *)((longlong)puVar8 + 0x3c) = 0;
    *param_3 = puVar8;
    if (puVar8 == (undefined8 *)0x0) goto LAB_18000ec68;
    *(undefined4 *)((longlong)puVar8 + 0xc) = 0;
    *(undefined2 *)puVar8 = *(undefined2 *)(lVar2 + 2);
    *(undefined2 *)((longlong)puVar8 + 4) = *(undefined2 *)(lVar2 + 6);
    *(undefined2 *)((longlong)puVar8 + 6) = *(undefined2 *)(lVar2 + 8);
    auVar4._8_8_ = 0;
    auVar4._0_8_ = CONCAT62(0,uVar16);
    lVar9 = SUB168(ZEXT416(8) * auVar4,0);
    *(ushort *)(puVar8 + 2) = uVar16;
    if (SUB168(ZEXT416(8) * auVar4,8) != 0) {
      lVar9 = -1;
    }
    pvVar10 = (void *)thunk_FUN_18007ca58(lVar9);
    *(ushort *)((longlong)puVar8 + 2) = param_2;
    puVar8[3] = pvVar10;
    *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(lVar2 + 10);
    if (pvVar10 == (void *)0x0) goto LAB_18000e9c1;
    memset(pvVar10,0,CONCAT62(0,uVar16) * 8);
    if ((param_4 == 0) ||
       (lVar9 = *(longlong *)(param_4 + (ulonglong)*(ushort *)(lVar2 + 0xc) * 8), lVar9 == 0)) {
      iVar5 = FUN_18000e440(param_1,*(ushort *)(lVar2 + 0xc),(undefined8 *)puVar8[3],param_4,param_5
                           );
    }
    else {
      *(longlong *)puVar8[3] = lVar9;
      psVar1 = (short *)(*(longlong *)(param_4 + (ulonglong)*(ushort *)(lVar2 + 0xc) * 8) + 0x38);
      *psVar1 = *psVar1 + 1;
    }
    uVar13 = *(ushort *)(lVar2 + 0xe);
    if (((*param_5 <= uVar13) && (param_4 != 0)) &&
       (lVar9 = *(longlong *)(param_4 + (ulonglong)uVar13 * 8), lVar9 != 0)) {
      *(longlong *)(puVar8[3] + 8) = lVar9;
      psVar1 = (short *)(*(longlong *)(param_4 + (ulonglong)*(ushort *)(lVar2 + 0xe) * 8) + 0x38);
      *psVar1 = *psVar1 + 1;
      goto LAB_18000ec72;
    }
    if (-1 < iVar5) {
      if (*param_5 <= uVar13) {
        puVar8 = (undefined8 *)(puVar8[3] + 8);
        goto LAB_18000e90d;
      }
      puVar12 = (undefined8 *)FUN_18007ca58(0x40);
      puVar11 = (undefined8 *)0x0;
      if (puVar12 != (undefined8 *)0x0) {
        *puVar12 = 0xffffffffffffffff;
        *(undefined2 *)((longlong)puVar12 + 0x12) = 0xffff;
        *(undefined2 *)(puVar12 + 1) = 0;
        *(undefined4 *)((longlong)puVar12 + 0xc) = 3;
        *(undefined2 *)(puVar12 + 2) = 0;
        puVar12[3] = 0;
        *(undefined4 *)(puVar12 + 4) = 3;
        *(undefined2 *)((longlong)puVar12 + 0x24) = 0;
        puVar12[5] = 0;
        puVar12[6] = 0;
        *(undefined2 *)(puVar12 + 7) = 1;
        *(undefined4 *)((longlong)puVar12 + 0x3c) = 0;
        puVar11 = puVar12;
      }
      *(undefined8 **)(puVar8[3] + 8) = puVar11;
      if (*(longlong *)(puVar8[3] + 8) == 0) goto LAB_18000ec68;
      *(undefined4 *)(*(longlong *)(puVar8[3] + 8) + 0xc) = 0;
      **(undefined2 **)(puVar8[3] + 8) = *(undefined2 *)(lVar2 + 2);
      *(undefined2 *)(((longlong *)puVar8[3])[1] + 4) = *(undefined2 *)(*(longlong *)puVar8[3] + 6);
      *(undefined2 *)(*(longlong *)(puVar8[3] + 8) + 6) = *(undefined2 *)(lVar2 + 8);
      *(undefined2 *)(*(longlong *)(puVar8[3] + 8) + 2) = *(undefined2 *)(lVar2 + 0xe);
      *(undefined2 *)(*(longlong *)(puVar8[3] + 8) + 0x10) = 0;
      *(undefined8 *)(*(longlong *)(puVar8[3] + 8) + 0x18) = 0;
      plVar3 = (longlong *)puVar8[3];
      if (*plVar3 == 0) {
        *(undefined2 *)(plVar3[1] + 8) = *(undefined2 *)(lVar2 + 10);
      }
      else {
        *(short *)(plVar3[1] + 8) = *(short *)(lVar2 + 10) - *(short *)(*plVar3 + 8);
      }
    }
  }
LAB_18000ec6d:
  if (param_4 == 0) {
    return iVar5;
  }
LAB_18000ec72:
  *(undefined8 *)(param_4 + (ulonglong)param_2 * 8) = *param_3;
  return iVar5;
}


// FUN_18005e7b8 @ 18005e7b8

int FUN_18005e7b8(undefined8 param_1,longlong param_2,longlong *param_3,int *param_4,int *param_5)

{
  longlong lVar1;
  undefined1 auVar2 [16];
  ushort uVar3;
  int extraout_EAX;
  uint uVar4;
  void *_Dst;
  longlong lVar5;
  int iVar6;
  int unaff_EDI;
  int iVar7;
  
  uVar3 = *(ushort *)(param_2 + 0x10);
  uVar4 = (uint)uVar3;
  iVar7 = 0;
  iVar6 = 0;
  if (0 < (short)uVar3) {
    lVar5 = 0;
    do {
      uVar3 = (ushort)uVar4;
      if (iVar7 < 0) break;
      lVar1 = *(longlong *)(*(longlong *)(param_2 + 0x18) + lVar5);
      if (*(int *)(lVar1 + 0x3c) == 0) {
        *(undefined4 *)(lVar1 + 0x3c) = 1;
        FUN_18005e7b8(param_1,*(longlong *)(lVar5 + *(longlong *)(param_2 + 0x18)),param_3,param_4,
                      param_5);
        iVar7 = extraout_EAX;
      }
      uVar3 = *(ushort *)(param_2 + 0x10);
      uVar4 = (uint)(short)uVar3;
      iVar6 = iVar6 + 1;
      lVar5 = lVar5 + 8;
    } while (iVar6 < (int)uVar4);
  }
  iVar6 = *param_5;
  *(ushort *)(param_2 + 0x12) = uVar3;
  if (((-1 < iVar6) && (-1 < *param_4)) && (iVar6 <= *param_4)) {
    if (0x7ffffff5 < iVar6) {
      return unaff_EDI;
    }
    iVar6 = iVar6 + 10;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = (longlong)iVar6;
    lVar5 = SUB168(ZEXT816(8) * auVar2,0);
    if (SUB168(ZEXT816(8) * auVar2,8) != 0) {
      lVar5 = -1;
    }
    _Dst = (void *)thunk_FUN_18007ca58(lVar5);
    if (_Dst == (void *)0x0) {
      return unaff_EDI;
    }
    *param_5 = iVar6;
    memset(_Dst,0,(longlong)iVar6 * 8);
    if ((*param_3 != 0) && (*param_4 != 0)) {
      memcpy(_Dst,(void *)*param_3,(longlong)*param_4 << 3);
    }
    _o_free(*param_3);
    *param_3 = (longlong)_Dst;
  }
  if ((-1 < iVar7) && (*param_3 != 0)) {
    iVar7 = *param_4;
    *(longlong *)(*param_3 + (longlong)iVar7 * 8) = param_2;
    *param_4 = iVar7 + 1;
  }
  return unaff_EDI;
}


// FUN_18013695c @ 18013695c

ulonglong FUN_18013695c(undefined8 param_1,longlong param_2)

{
  longlong lVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  short sVar7;
  uint uVar8;
  ulonglong uVar9;
  
  uVar5 = 0;
  uVar8 = 0;
  uVar2 = uVar5;
  if (*(int *)(param_2 + 0xc) == 1) {
    sVar7 = *(short *)(param_2 + 0x12);
    *(undefined4 *)(param_2 + 0x3c) = 1;
    uVar3 = uVar5;
    uVar6 = uVar5;
    if (0 < sVar7) {
      do {
        if ((int)uVar2 < 0) break;
        lVar1 = *(longlong *)(uVar6 + *(longlong *)(param_2 + 0x18));
        if (*(int *)(lVar1 + 0x3c) == 0) {
          uVar2 = FUN_18013695c(param_1,lVar1);
          sVar7 = *(short *)(param_2 + 0x12);
          uVar2 = uVar2 & 0xffffffff;
        }
        if (-1 < (int)uVar2) {
          *(int *)(param_2 + 0x3c) =
               *(int *)(param_2 + 0x3c) +
               *(int *)(*(longlong *)(*(longlong *)(param_2 + 0x18) + uVar6) + 0x3c);
        }
        uVar4 = (int)uVar3 + 1;
        uVar3 = (ulonglong)uVar4;
        uVar6 = uVar6 + 8;
      } while ((int)uVar4 < (int)sVar7);
    }
    if (0x10000 < *(uint *)(param_2 + 0x3c)) {
      if ((0 < sVar7) && (uVar3 = uVar5, uVar6 = uVar5, uVar9 = uVar5, -1 < (int)uVar2)) {
        do {
          uVar8 = (uint)uVar9;
          uVar4 = (int)uVar6 + *(int *)(*(longlong *)(uVar3 + *(longlong *)(param_2 + 0x18)) + 0x3c)
          ;
          uVar6 = (ulonglong)uVar4;
          if (0xffff < uVar4) break;
          uVar8 = uVar8 + 1;
          uVar9 = (ulonglong)uVar8;
          uVar3 = uVar3 + 8;
        } while ((int)uVar8 < (int)sVar7);
      }
      *(undefined4 *)(param_2 + 0x3c) = 0;
      sVar7 = (short)uVar8 + -1;
      if ((int)uVar8 < 2) {
        sVar7 = 1;
      }
      *(short *)(param_2 + 0x12) = sVar7;
      uVar3 = uVar5;
      uVar6 = uVar5;
      if (0 < sVar7) {
        do {
          if ((int)uVar2 < 0) {
            return uVar2;
          }
          uVar4 = (int)uVar6 + 1;
          uVar8 = (int)uVar5 + *(int *)(*(longlong *)(uVar3 + *(longlong *)(param_2 + 0x18)) + 0x3c)
          ;
          uVar5 = (ulonglong)uVar8;
          *(uint *)(param_2 + 0x3c) = uVar8;
          uVar3 = uVar3 + 8;
          uVar6 = (ulonglong)uVar4;
        } while ((int)uVar4 < (int)sVar7);
      }
    }
  }
  else if (*(int *)(param_2 + 0xc) == 0) {
    sVar7 = *(short *)(param_2 + 0x12);
    uVar3 = uVar5;
    if (0 < sVar7) {
      do {
        if ((int)uVar2 < 0) break;
        lVar1 = *(longlong *)(uVar3 + *(longlong *)(param_2 + 0x18));
        if (*(int *)(lVar1 + 0x3c) == 0) {
          uVar2 = FUN_18013695c(param_1,lVar1);
          sVar7 = *(short *)(param_2 + 0x12);
          uVar2 = uVar2 & 0xffffffff;
        }
        if (-1 < (int)uVar2) {
          *(int *)(param_2 + 0x3c) =
               *(int *)(param_2 + 0x3c) +
               *(int *)(*(longlong *)(uVar3 + *(longlong *)(param_2 + 0x18)) + 0x3c);
        }
        uVar8 = (int)uVar5 + 1;
        uVar5 = (ulonglong)uVar8;
        uVar3 = uVar3 + 8;
      } while ((int)uVar8 < (int)sVar7);
    }
    if (*(int *)(param_2 + 0x3c) == 0) {
      *(undefined4 *)(param_2 + 0x3c) = 1;
    }
  }
  return uVar2;
}


// FUN_180136900 @ 180136900

int FUN_180136900(longlong *param_1,longlong *param_2)

{
  return (uint)*(ushort *)(*param_1 + 8) - (uint)*(ushort *)(*param_2 + 8);
}


