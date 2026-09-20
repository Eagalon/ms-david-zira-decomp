// FUN_1800433c8 @ 1800433c8

ulonglong FUN_1800433c8(longlong param_1,ushort *param_2,undefined8 *param_3,longlong param_4,
                       ushort param_5,uint param_6)

{
  uint *puVar1;
  undefined1 auVar2 [16];
  uint uVar3;
  uint *puVar4;
  longlong *plVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  longlong lVar8;
  void *_Dst;
  undefined8 *puVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  ushort uVar12;
  int iVar13;
  ushort uVar14;
  uint local_res10;
  longlong local_58;
  
  *(undefined8 **)(param_2 + 0x18) = param_3;
  *(ushort *)((longlong)param_3 + 0x72) = param_2[2];
  uVar10 = 0;
  *(ushort *)((longlong)param_3 + 0x74) = param_2[3];
  uVar12 = *param_2;
  lVar8 = *(longlong *)(param_1 + 0x18);
  uVar11 = uVar10;
  puVar4 = (uint *)FUN_180043b44(lVar8,uVar12);
  local_res10 = (uint)uVar11;
  uVar3 = local_res10 + 1;
  if (puVar4 != (uint *)0x0) {
    if ((puVar4[8] != local_res10) && (puVar4[9] != local_res10)) {
      local_res10 = uVar3;
    }
    if (uVar12 != param_5) {
      if (puVar4[10] != 0xffffffff) {
        puVar1 = *(uint **)(*(longlong *)(lVar8 + 0xa0) + (ulonglong)puVar4[10] * 8);
        if (puVar1 != (uint *)0x0) {
          plVar5 = (longlong *)FUN_18007ca58(0x10);
          plVar6 = (longlong *)0x0;
          if (plVar5 != (longlong *)0x0) {
            *plVar5 = 0;
            *(undefined2 *)(plVar5 + 1) = 0;
            plVar6 = plVar5;
          }
          param_3[7] = plVar6;
          if (plVar6 == (longlong *)0x0) {
            return 0x8007000e;
          }
          puVar7 = FUN_18013e50c(plVar6,puVar1,*(longlong *)(param_1 + 0x18));
          uVar11 = 0;
          uVar10 = (ulonglong)puVar7 & 0xffffffff;
          if ((int)puVar7 < 0) {
            return uVar10;
          }
        }
        uVar3 = 1;
      }
      if (((param_6 == 0) && (puVar4[8] != (uint)uVar11)) && (*puVar4 != uVar3)) {
        *(uint *)(param_3 + 0xf) = uVar3;
        lVar8 = FUN_18003aa40(*(longlong *)(*(longlong *)(param_1 + 0x18) + 0xb8),puVar4[6]);
        param_6 = uVar3;
        if (lVar8 != 0) {
          lVar8 = _o__wcsdup(lVar8);
          uVar11 = 0;
          param_3[0x10] = lVar8;
          if (lVar8 == 0) {
            return 0x8007000e;
          }
        }
      }
    }
  }
  iVar13 = *(int *)(param_2 + 0x10);
  lVar8 = -1;
  if (iVar13 == 3) {
    uVar12 = param_2[9];
    if (uVar12 == 0xffff) {
      uVar12 = param_2[8];
    }
    local_58 = *(longlong *)(param_2 + 0xc);
    iVar13 = *(int *)(param_2 + 6);
  }
  else {
    local_58 = *(longlong *)(param_2 + 0x14);
    uVar12 = param_2[0x12];
  }
  *(ushort *)((longlong)param_3 + 0x34) = *param_2;
  if ((short)uVar12 < 1) {
    if (iVar13 != 2) {
      uVar3 = FUN_180066868(*(longlong *)(param_1 + 0x18),param_3,*param_2,param_2[1],param_4,
                            param_2[2],param_2[3]);
      return (ulonglong)uVar3;
    }
    if (*(ulonglong *)(param_2 + 0x14) != uVar11) {
      *(int *)(param_3 + 1) = (int)uVar11;
      do {
        lVar8 = lVar8 + 1;
      } while (*(short *)(*(longlong *)(param_2 + 0x14) + lVar8 * 2) != (short)uVar11);
      *(short *)(param_3 + 5) = (short)lVar8;
      lVar8 = _o__wcsdup(*(undefined8 *)(param_2 + 0x14));
      param_3[4] = lVar8;
      if (lVar8 == 0) {
        return 0x8007000e;
      }
      return uVar10;
    }
    return uVar10;
  }
  if (((puVar4 != (uint *)0x0) &&
      (lVar8 = *(longlong *)(*(longlong *)(param_1 + 0x18) + 0xc0), lVar8 != 0)) &&
     (lVar8 = FUN_18003aa40(lVar8,*puVar4), lVar8 != 0)) {
    lVar8 = _o__wcsdup(lVar8);
    uVar11 = 0;
    param_3[4] = lVar8;
    if (lVar8 == 0) {
      uVar10 = 0x8007000e;
    }
  }
  *(uint *)(param_3 + 1) = (iVar13 != 0) + 1;
  if (local_res10 != (uint)uVar11) {
    *(undefined4 *)(param_3 + 6) = 1;
  }
  if (-1 < (int)uVar10) {
    auVar2._8_8_ = 0;
    auVar2._0_8_ = (longlong)(short)uVar12;
    lVar8 = SUB168(ZEXT816(8) * auVar2,0);
    if (SUB168(ZEXT816(8) * auVar2,8) != 0) {
      lVar8 = -1;
    }
    _Dst = (void *)thunk_FUN_18007ca58(lVar8);
    param_3[2] = _Dst;
    *(ushort *)(param_3 + 5) = uVar12;
    if (_Dst == (void *)0x0) {
      return 0x8007000e;
    }
    memset(_Dst,0,(longlong)(short)uVar12 * 8);
    uVar14 = 0;
    if ((short)uVar12 < 1) {
      return uVar10;
    }
    do {
      if ((int)uVar10 < 0) {
        return uVar10;
      }
      uVar11 = (ulonglong)uVar14;
      *(undefined8 *)(param_3[2] + uVar11 * 8) =
           *(undefined8 *)(*(longlong *)(local_58 + uVar11 * 8) + 0x30);
      lVar8 = *(longlong *)(param_3[2] + uVar11 * 8);
      if (lVar8 == 0) {
        puVar7 = (undefined8 *)FUN_18007ca58(0xb8);
        puVar9 = (undefined8 *)0x0;
        if (puVar7 != (undefined8 *)0x0) {
          puVar9 = FUN_18013dd18(puVar7);
        }
        *(undefined8 **)(param_3[2] + uVar11 * 8) = puVar9;
        lVar8 = *(longlong *)(param_3[2] + uVar11 * 8);
        if (lVar8 == 0) {
          uVar10 = 0x8007000e;
        }
        else {
          *(undefined4 *)(lVar8 + 0x30) = *(undefined4 *)(param_3 + 6);
          uVar10 = FUN_1800433c8(param_1,*(ushort **)(local_58 + uVar11 * 8),
                                 *(undefined8 **)(param_3[2] + uVar11 * 8),param_4,*param_2,param_6)
          ;
          uVar10 = uVar10 & 0xffffffff;
        }
      }
      else {
        *(undefined4 *)(lVar8 + 0x30) = *(undefined4 *)(param_3 + 6);
        FUN_18007acc8(*(longlong *)(param_3[2] + uVar11 * 8));
      }
      uVar14 = uVar14 + 1;
    } while ((int)(uint)uVar14 < (int)(short)uVar12);
    return uVar10;
  }
  return uVar10;
}


// FUN_1800437fc @ 1800437fc

int FUN_1800437fc(longlong param_1,longlong param_2,char param_3)

{
  short sVar1;
  undefined8 *puVar2;
  undefined1 auVar3 [16];
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  void *_Dst;
  bool bVar8;
  ulonglong uVar9;
  bool bVar10;
  uint uVar11;
  ushort uVar12;
  ushort uVar13;
  ulonglong uVar14;
  undefined8 *puVar15;
  int iVar16;
  ulonglong uVar17;
  short sVar18;
  ulonglong uVar19;
  ushort uVar20;
  bool bVar21;
  bool bVar22;
  bool local_res10;
  
  iVar16 = *(int *)(param_2 + 8);
  iVar5 = 0;
  if (iVar16 == 0) {
    iVar5 = 0;
  }
  else {
    lVar7 = *(longlong *)(param_1 + 0x18);
    lVar6 = FUN_180043b44(lVar7,*(ushort *)(param_2 + 0x34));
    bVar22 = false;
    bVar10 = bVar22;
    if (lVar6 != 0) {
      bVar10 = *(int *)((ulonglong)*(uint *)(lVar6 + 0x1c) +
                       *(longlong *)(*(longlong *)(lVar7 + 200) + 0x10)) != 0;
    }
    bVar21 = true;
    bVar8 = bVar21;
    if ((param_3 == '\0') &&
       ((lVar6 == 0 ||
        (*(short *)((ulonglong)*(uint *)(lVar6 + 0x2c) +
                   *(longlong *)(*(longlong *)(lVar7 + 200) + 0x10)) == 0)))) {
      bVar8 = bVar22;
    }
    if (((iVar16 == 1) || ((iVar16 == 2 && (*(short *)(param_2 + 0x28) == 1)))) &&
       ((bVar10 != false || (bVar8 != false)))) {
      bVar22 = bVar21;
    }
    local_res10 = bVar22;
    for (uVar19 = 0; uVar12 = (ushort)uVar19, uVar12 < *(ushort *)(param_2 + 0x28);
        uVar19 = (ulonglong)(ushort)((short)uVar19 + 1)) {
      sVar18 = *(short *)(param_2 + 0x34);
      puVar2 = *(undefined8 **)(*(longlong *)(param_2 + 0x10) + uVar19 * 8);
      sVar1 = *(short *)((longlong)puVar2 + 0x34);
      lVar7 = param_1;
      iVar5 = FUN_1800437fc(param_1,(longlong)puVar2,bVar8);
      if (iVar5 < 0) {
        return iVar5;
      }
      if (((bVar22 != false) && (sVar1 == sVar18)) && (puVar2[7] == 0)) {
        iVar16 = *(int *)(puVar2 + 1);
        iVar4 = (int)uVar19;
        if (iVar16 == 0) {
          if ((((short *)puVar2[4] == (short *)0x0) || (*(short *)puVar2[4] == 0)) &&
             (*(uint *)(puVar2 + 3) < 2)) {
LAB_180043950:
            *(short *)(param_2 + 0x2a) =
                 *(short *)(param_2 + 0x2a) + *(short *)((longlong)puVar2 + 0x2a);
            uVar20 = *(ushort *)(param_2 + 0x28);
            uVar13 = uVar12;
            if (iVar4 < (int)(uVar20 - 1)) {
              do {
                uVar19 = (ulonglong)uVar13;
                uVar13 = uVar13 + 1;
                *(undefined8 *)(*(longlong *)(param_2 + 0x10) + uVar19 * 8) =
                     *(undefined8 *)(*(longlong *)(param_2 + 0x10) + 8 + uVar19 * 8);
                uVar20 = *(ushort *)(param_2 + 0x28);
              } while ((int)(uint)uVar13 < (int)(uVar20 - 1));
            }
            *(undefined4 *)(param_2 + 8) = 1;
            uVar19 = (ulonglong)(ushort)(uVar12 - 1);
            *(ushort *)(param_2 + 0x28) = uVar20 - 1;
            FUN_18006718c(puVar2);
          }
        }
        else {
          if (*(short *)(puVar2 + 5) == 0) goto LAB_180043950;
          if (iVar16 == 1) {
            *(undefined4 *)(param_2 + 8) = 1;
            uVar20 = (*(short *)(param_2 + 0x28) + *(short *)(puVar2 + 5)) - 1;
            uVar9 = CONCAT62(0,uVar20);
            auVar3._8_8_ = 0;
            auVar3._0_8_ = uVar9;
            lVar7 = SUB168(ZEXT816(8) * auVar3,0);
            if (SUB168(ZEXT816(8) * auVar3,8) != 0) {
              lVar7 = -1;
            }
            _Dst = (void *)thunk_FUN_18007ca58(lVar7);
            if (_Dst == (void *)0x0) {
              return -0x7ff8fff2;
            }
            memset(_Dst,0,uVar9 * 8);
            uVar14 = 0;
            lVar7 = 1;
            uVar9 = uVar14;
            uVar17 = uVar14;
            if (uVar12 != 0) {
              do {
                *(undefined8 *)((longlong)_Dst + uVar17 * 8) =
                     *(undefined8 *)(uVar9 + *(longlong *)(param_2 + 0x10));
                uVar17 = uVar17 + 1;
                uVar19 = uVar19 - 1;
                uVar9 = uVar9 + 8;
              } while (uVar19 != 0);
            }
            if (*(short *)(puVar2 + 5) != 0) {
              do {
                sVar18 = (short)uVar14;
                FUN_18007acc8(*(longlong *)(puVar2[2] + uVar14 * 8));
                uVar13 = sVar18 + (short)lVar7;
                *(undefined8 *)((longlong)_Dst + uVar17 * 8) =
                     *(undefined8 *)(puVar2[2] + uVar14 * 8);
                uVar17 = uVar17 + lVar7;
                uVar14 = (ulonglong)uVar13;
              } while (uVar13 < *(ushort *)(puVar2 + 5));
            }
            uVar11 = (int)lVar7 + iVar4;
            uVar19 = (ulonglong)uVar11;
            if ((ushort)uVar11 < *(ushort *)(param_2 + 0x28)) {
              puVar15 = (undefined8 *)((longlong)_Dst + uVar17 * 8);
              do {
                uVar9 = uVar19 & 0xffff;
                uVar13 = (short)uVar19 + (short)lVar7;
                uVar19 = (ulonglong)uVar13;
                *puVar15 = *(undefined8 *)(*(longlong *)(param_2 + 0x10) + uVar9 * 8);
                puVar15 = puVar15 + 1;
              } while (uVar13 < *(ushort *)(param_2 + 0x28));
            }
            *(ushort *)(param_2 + 0x28) = uVar20;
            _o_free(*(undefined8 *)(param_2 + 0x10));
            *(void **)(param_2 + 0x10) = _Dst;
            uVar19 = (ulonglong)(ushort)(uVar12 + *(short *)(puVar2 + 5) + -1);
            *(short *)(param_2 + 0x2a) =
                 *(short *)(param_2 + 0x2a) + *(short *)((longlong)puVar2 + 0x2a);
            FUN_18006718c(puVar2);
            bVar22 = local_res10;
          }
          else if ((iVar16 == 2) && (*(int *)(param_2 + 8) != 2)) {
            uVar19 = FUN_1801370d4(CONCAT71((int7)((ulonglong)lVar7 >> 8),*(uint *)(puVar2 + 3) < 2)
                                   ,param_2,uVar12);
            iVar5 = (int)uVar19;
            if (iVar5 < 0) {
              return iVar5;
            }
            bVar22 = *(short *)(param_2 + 0x28) == 1;
            uVar19 = 0xffff;
            local_res10 = bVar22;
          }
        }
      }
    }
  }
  return iVar5;
}


