// FUN_1800114e0 @ 1800114e0

ulonglong FUN_1800114e0(longlong *param_1,undefined8 param_2,undefined2 param_3,short param_4)

{
  short *psVar1;
  void *_Src;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  ulonglong uVar4;
  longlong lVar5;
  void *pvVar6;
  ulonglong uVar7;
  ushort uVar8;
  
  uVar4 = FUN_180011690(param_1,param_2,param_2);
  uVar7 = uVar4 & 0xffffffff;
  if ((int)uVar4 < 0) {
    return uVar4;
  }
  uVar8 = param_4 - (short)param_1[4];
  uVar4 = (ulonglong)uVar8;
  if (uVar8 < *(ushort *)((longlong)param_1 + 0x22)) {
LAB_18001152f:
    uVar8 = *(ushort *)(param_1[5] + 10 + uVar4 * 0x10);
    if (uVar8 <= *(ushort *)(param_1[5] + 8 + uVar4 * 0x10)) {
      auVar2._8_8_ = 0;
      auVar2._0_8_ = (ulonglong)uVar8 + 0x14;
      lVar5 = SUB168(ZEXT816(2) * auVar2,0);
      if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
        lVar5 = -1;
      }
      pvVar6 = (void *)thunk_FUN_18007ca58(lVar5);
      if (pvVar6 == (void *)0x0) goto LAB_180011675;
      memset(pvVar6,0,(ulonglong)*(ushort *)(param_1[5] + 10 + uVar4 * 0x10) * 2 + 0x28);
      _Src = *(void **)(param_1[5] + uVar4 * 0x10);
      if (_Src != (void *)0x0) {
        memcpy(pvVar6,_Src,(ulonglong)*(ushort *)(param_1[5] + 8 + uVar4 * 0x10) * 2);
      }
      psVar1 = (short *)(param_1[5] + 10 + uVar4 * 0x10);
      *psVar1 = *psVar1 + 0x14;
      _o_free(*(undefined8 *)(param_1[5] + uVar4 * 0x10));
      *(void **)(param_1[5] + uVar4 * 0x10) = pvVar6;
    }
    *(undefined2 *)
     (*(longlong *)(param_1[5] + uVar4 * 0x10) +
     (ulonglong)*(ushort *)(param_1[5] + 8 + uVar4 * 0x10) * 2) = param_3;
    psVar1 = (short *)(param_1[5] + 8 + uVar4 * 0x10);
    *psVar1 = *psVar1 + 1;
  }
  else {
    auVar3._8_8_ = 0;
    auVar3._0_8_ = uVar4 + 0x14;
    lVar5 = SUB168(ZEXT816(0x10) * auVar3,0);
    if (SUB168(ZEXT816(0x10) * auVar3,8) != 0) {
      lVar5 = -1;
    }
    pvVar6 = (void *)thunk_FUN_18007ca58(lVar5);
    if (pvVar6 != (void *)0x0) {
      memset(pvVar6,0,(uVar4 + 0x14) * 0x10);
      if ((void *)param_1[5] != (void *)0x0) {
        memcpy(pvVar6,(void *)param_1[5],(ulonglong)*(ushort *)((longlong)param_1 + 0x22) << 4);
      }
      *(ushort *)((longlong)param_1 + 0x22) = uVar8 + 0x14;
      _o_free(param_1[5]);
      param_1[5] = (longlong)pvVar6;
      goto LAB_18001152f;
    }
LAB_180011675:
    uVar7 = 0x8007000e;
  }
  return uVar7;
}


// FUN_180011ad0 @ 180011ad0

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8 * FUN_180011ad0(longlong param_1,byte *param_2)

{
  short sVar1;
  longlong *plVar2;
  byte *pbVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  char cVar8;
  uint uVar9;
  undefined8 *puVar10;
  longlong lVar11;
  longlong lVar12;
  longlong lVar13;
  ushort uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  ulonglong uVar18;
  longlong lVar19;
  ulonglong uVar20;
  undefined8 *puVar21;
  short sVar22;
  short *psVar23;
  undefined8 *puVar24;
  undefined8 *puVar25;
  undefined8 *puVar26;
  undefined8 *local_res10;
  undefined8 *local_res18;
  
  plVar2 = *(longlong **)(param_1 + 0x10);
  puVar26 = (undefined8 *)0x0;
  psVar23 = *(short **)(param_1 + 0x28);
  if ((int)plVar2[2] != 0) {
    uVar20 = (**(code **)(*plVar2 + 0x10))(plVar2);
    uVar20 = (uVar20 & 0xffffffff) % (ulonglong)*(uint *)(plVar2 + 2);
    uVar18 = uVar20;
    puVar10 = puVar26;
    do {
      iVar15 = (int)uVar18;
      puVar24 = (undefined8 *)(plVar2[1] + uVar18 * 0x18);
      if (((*(longlong *)(plVar2[1] + 0x10 + uVar18 * 0x18) == 0) &&
          (*(char *)(puVar24 + 1) == '\0')) ||
         (cVar8 = (**(code **)(*plVar2 + 0x18))(plVar2,*puVar24,param_2), cVar8 != '\0')) {
        if (-1 < iVar15) {
          lVar19 = *(longlong *)(plVar2[1] + 0x10 + (longlong)iVar15 * 0x18);
          puVar10 = puVar26;
          if (lVar19 != 0) {
            if ((*(short *)(lVar19 + 0xc) == *(short *)(param_2 + 0xc)) &&
               (*(short *)(lVar19 + 0xe) == *(short *)(param_2 + 0xe))) {
              return (undefined8 *)0x0;
            }
            uVar14 = (ushort)psVar23[8] >> 0xe;
            if ((ushort)psVar23[8] < (ushort)psVar23[1]) {
              lVar12 = (ulonglong)uVar14 * 8;
              if (*(longlong *)(lVar12 + *(longlong *)(psVar23 + 4)) == 0) {
                lVar11 = thunk_FUN_18007ca58(0x48000);
                *(longlong *)(lVar12 + *(longlong *)(psVar23 + 4)) = lVar11;
                if (lVar11 == 0) {
                  puVar10 = (undefined8 *)0x8007000e;
                  goto LAB_180011b7d;
                }
              }
              uVar4 = *(undefined8 *)(param_2 + 8);
              lVar13 = (ulonglong)(ushort)(psVar23[8] + uVar14 * -0x4000) * 0x12;
              lVar11 = *(longlong *)(lVar12 + *(longlong *)(psVar23 + 4));
              puVar26 = (undefined8 *)(lVar11 + lVar13);
              *puVar26 = *(undefined8 *)param_2;
              puVar26[1] = uVar4;
              *(undefined2 *)(lVar11 + 0x10 + lVar13) = *(undefined2 *)(param_2 + 0x10);
              lVar12 = *(longlong *)(lVar12 + *(longlong *)(psVar23 + 4));
              goto LAB_180011e82;
            }
            puVar10 = (undefined8 *)0x80041003;
          }
LAB_180011b7d:
          if ((int)puVar10 < 0) {
            return puVar10;
          }
        }
        break;
      }
      if ((int)puVar10 == 0) {
        uVar9 = (**(code **)(*plVar2 + 0x20))(plVar2);
        puVar10 = (undefined8 *)(ulonglong)uVar9;
        if (1 < *(uint *)(plVar2 + 2)) {
          puVar10 = (undefined8 *)(ulonglong)(uVar9 % (*(uint *)(plVar2 + 2) - 1) + 1);
        }
      }
      uVar16 = iVar15 + (int)puVar10;
      uVar9 = uVar16 - (int)plVar2[2];
      if (uVar16 < *(uint *)(plVar2 + 2)) {
        uVar9 = uVar16;
      }
      uVar18 = (ulonglong)uVar9;
    } while (uVar9 != (uint)uVar20);
  }
  plVar2 = *(longlong **)(param_1 + 0x18);
  psVar23 = *(short **)(param_1 + 0x28);
  if ((int)plVar2[2] != 0) {
    uVar20 = (**(code **)(*plVar2 + 0x10))(plVar2);
    uVar20 = (uVar20 & 0xffffffff) % (ulonglong)*(uint *)(plVar2 + 2);
    uVar9 = (uint)uVar20;
    puVar10 = puVar26;
    do {
      iVar15 = (int)uVar20;
      puVar24 = (undefined8 *)(plVar2[1] + uVar20 * 0x18);
      if (((*(longlong *)(plVar2[1] + 0x10 + uVar20 * 0x18) == 0) &&
          (*(char *)(puVar24 + 1) == '\0')) ||
         (cVar8 = (**(code **)(*plVar2 + 0x18))(plVar2,*puVar24,param_2), cVar8 != '\0')) {
        if (-1 < iVar15) {
          lVar19 = *(longlong *)(plVar2[1] + 0x10 + (longlong)iVar15 * 0x18);
          puVar10 = puVar26;
          if (lVar19 != 0) {
            if ((*(short *)(lVar19 + 0xc) == *(short *)(param_2 + 0xc)) &&
               (*(short *)(lVar19 + 0xe) == *(short *)(param_2 + 0xe))) {
              return (undefined8 *)0x0;
            }
            uVar14 = (ushort)psVar23[8] >> 0xe;
            if ((ushort)psVar23[8] < (ushort)psVar23[1]) {
              lVar12 = (ulonglong)uVar14 * 8;
              if (*(longlong *)(lVar12 + *(longlong *)(psVar23 + 4)) != 0) {
LAB_180011fe0:
                uVar4 = *(undefined8 *)(param_2 + 8);
                lVar13 = (ulonglong)(ushort)(psVar23[8] + uVar14 * -0x4000) * 0x12;
                lVar11 = *(longlong *)(*(longlong *)(psVar23 + 4) + lVar12);
                puVar26 = (undefined8 *)(lVar11 + lVar13);
                *puVar26 = *(undefined8 *)param_2;
                puVar26[1] = uVar4;
                *(undefined2 *)(lVar11 + 0x10 + lVar13) = *(undefined2 *)(param_2 + 0x10);
                lVar12 = *(longlong *)(*(longlong *)(psVar23 + 4) + lVar12);
LAB_180011e82:
                psVar23[8] = psVar23[8] + 1;
                sVar22 = psVar23[8];
                sVar1 = *psVar23;
                *(undefined2 *)(lVar12 + 0x10 + lVar13) = *(undefined2 *)(lVar19 + 0x10);
                *(short *)(lVar19 + 0x10) = sVar22 + -1 + sVar1;
                return (undefined8 *)0x0;
              }
              lVar11 = thunk_FUN_18007ca58(0x48000);
              *(longlong *)(lVar12 + *(longlong *)(psVar23 + 4)) = lVar11;
              if (lVar11 != 0) goto LAB_180011fe0;
              puVar10 = (undefined8 *)0x8007000e;
            }
            else {
              puVar10 = (undefined8 *)0x80041003;
            }
          }
          if ((int)puVar10 < 0) {
            return puVar10;
          }
        }
        break;
      }
      if ((int)puVar10 == 0) {
        uVar16 = (**(code **)(*plVar2 + 0x20))(plVar2);
        puVar10 = (undefined8 *)(ulonglong)uVar16;
        if (1 < *(uint *)(plVar2 + 2)) {
          puVar10 = (undefined8 *)(ulonglong)(uVar16 % (*(uint *)(plVar2 + 2) - 1) + 1);
        }
      }
      uVar17 = iVar15 + (int)puVar10;
      uVar16 = uVar17 - (int)plVar2[2];
      if (uVar17 < *(uint *)(plVar2 + 2)) {
        uVar16 = uVar17;
      }
      uVar20 = (ulonglong)uVar16;
    } while (uVar16 != uVar9);
  }
  lVar19 = *(longlong *)(param_1 + 0x20);
  psVar23 = *(short **)(param_1 + 0x28);
  local_res10 = (undefined8 *)0x0;
  local_res18 = (undefined8 *)0x0;
  puVar7 = *(undefined8 **)(lVar19 + 8);
  iVar15 = 0;
  puVar10 = puVar26;
  puVar24 = puVar26;
  puVar21 = puVar26;
  puVar25 = puVar26;
  puVar6 = local_res10;
  while (local_res10._0_4_ = iVar15, puVar5 = puVar7, uVar9 = 0, puVar5 != (undefined8 *)0x0) {
    pbVar3 = (byte *)puVar5[2];
    if ((*(ushort *)(param_2 + 10) <= *(ushort *)(pbVar3 + 10)) && ((int)puVar21 == 0)) {
      puVar21 = (undefined8 *)0x1;
      puVar25 = puVar24;
      local_res18 = puVar24;
    }
    if ((((*(short *)(pbVar3 + 2) == *(short *)(param_2 + 2)) &&
         (*(short *)(pbVar3 + 4) == *(short *)(param_2 + 4))) &&
        (*(short *)(pbVar3 + 6) == *(short *)(param_2 + 6))) &&
       (*(short *)(pbVar3 + 8) == *(short *)(param_2 + 8))) {
      local_res10._0_4_ = (int)puVar6;
      puVar10 = puVar6;
      if ((((*param_2 ^ *pbVar3) & 2) == 0) && (((*param_2 ^ *pbVar3) & 1) == 0)) {
        sVar22 = -1;
        if ((*(short *)(pbVar3 + 0xc) != *(short *)(param_2 + 0xc)) ||
           (puVar10 = puVar26, *(short *)(pbVar3 + 0xe) != *(short *)(param_2 + 0xe))) {
          uVar14 = (ushort)psVar23[8] >> 0xe;
          if ((ushort)psVar23[1] <= (ushort)psVar23[8]) {
            uVar9 = 0x80041003;
            break;
          }
          lVar12 = (ulonglong)uVar14 * 8;
          if (*(longlong *)(lVar12 + *(longlong *)(psVar23 + 4)) == 0) {
            lVar11 = thunk_FUN_18007ca58(0x48000);
            *(longlong *)(lVar12 + *(longlong *)(psVar23 + 4)) = lVar11;
            puVar25 = local_res18;
            if (lVar11 == 0) {
              uVar9 = 0x8007000e;
              break;
            }
          }
          uVar4 = *(undefined8 *)(param_2 + 8);
          lVar13 = (ulonglong)(ushort)(psVar23[8] + uVar14 * -0x4000) * 0x12;
          lVar11 = *(longlong *)(*(longlong *)(psVar23 + 4) + lVar12);
          puVar10 = (undefined8 *)(lVar11 + lVar13);
          *puVar10 = *(undefined8 *)param_2;
          puVar10[1] = uVar4;
          *(undefined2 *)(lVar11 + 0x10 + lVar13) = *(undefined2 *)(param_2 + 0x10);
          puVar10 = (undefined8 *)(lVar13 + *(longlong *)(*(longlong *)(psVar23 + 4) + lVar12));
          psVar23[8] = psVar23[8] + 1;
          sVar22 = psVar23[8] + -1 + *psVar23;
        }
        if (*(ushort *)(param_2 + 10) < *(ushort *)(pbVar3 + 10)) {
          if ((sVar22 == -1) || (puVar10 == (undefined8 *)0x0)) {
            uVar4 = *(undefined8 *)(param_2 + 8);
            *(undefined8 *)pbVar3 = *(undefined8 *)param_2;
            *(undefined8 *)(pbVar3 + 8) = uVar4;
            *(undefined2 *)(pbVar3 + 0x10) = *(undefined2 *)(param_2 + 0x10);
          }
          else {
            puVar5[2] = puVar10;
            *(undefined2 *)(puVar10 + 2) = *(undefined2 *)(puVar5 + 1);
            *(short *)(puVar5 + 1) = sVar22;
          }
          if (puVar24 != (undefined8 *)0x0) {
            *puVar24 = *puVar5;
            if (puVar25 == (undefined8 *)0x0) {
              *puVar5 = *(undefined8 *)(lVar19 + 8);
              *(undefined8 **)(lVar19 + 8) = puVar5;
            }
            else {
              *puVar5 = *puVar25;
              *puVar25 = puVar5;
            }
          }
        }
        else if ((sVar22 != -1) && (puVar10 != (undefined8 *)0x0)) {
          *(undefined2 *)(puVar10 + 2) = *(undefined2 *)(pbVar3 + 0x10);
          *(short *)(pbVar3 + 0x10) = sVar22;
        }
        local_res10 = (undefined8 *)0x1;
        puVar10 = (undefined8 *)0x1;
        puVar6 = local_res10;
      }
    }
    local_res10 = puVar6;
    iVar15 = (int)puVar10;
    puVar24 = puVar5;
    puVar6 = local_res10;
    puVar7 = (undefined8 *)*puVar5;
  }
  if (((int)uVar9 < 0) || ((int)local_res10 != 0)) {
    puVar10 = (undefined8 *)(ulonglong)uVar9;
  }
  else {
    psVar23 = *(short **)(param_1 + 0x28);
    uVar14 = (ushort)psVar23[8] >> 0xe;
    puVar10 = (undefined8 *)0x80041003;
    if ((ushort)psVar23[8] < (ushort)psVar23[1]) {
      lVar19 = (ulonglong)uVar14 * 8;
      if (*(longlong *)(lVar19 + *(longlong *)(psVar23 + 4)) == 0) {
        lVar12 = thunk_FUN_18007ca58(0x48000);
        *(longlong *)(lVar19 + *(longlong *)(psVar23 + 4)) = lVar12;
        if (lVar12 == 0) {
          return (undefined8 *)0x8007000e;
        }
      }
      uVar4 = *(undefined8 *)(param_2 + 8);
      lVar11 = (ulonglong)(ushort)(psVar23[8] + uVar14 * -0x4000) * 0x12;
      lVar12 = *(longlong *)(lVar19 + *(longlong *)(psVar23 + 4));
      puVar10 = (undefined8 *)(lVar12 + lVar11);
      *puVar10 = *(undefined8 *)param_2;
      puVar10[1] = uVar4;
      *(undefined2 *)(lVar12 + 0x10 + lVar11) = *(undefined2 *)(param_2 + 0x10);
      lVar19 = *(longlong *)(lVar19 + *(longlong *)(psVar23 + 4));
      psVar23[8] = psVar23[8] + 1;
      lVar19 = lVar19 + lVar11;
      sVar22 = psVar23[8] + -1 + *psVar23;
      lVar12 = *(longlong *)(param_1 + 0x20);
      puVar24 = *(undefined8 **)(lVar12 + 0x10);
      if (puVar24 == (undefined8 *)0x0) {
        puVar10 = (undefined8 *)FUN_18007ca58(0x18);
        puVar24 = puVar26;
        if (puVar10 != (undefined8 *)0x0) {
          *puVar10 = 0;
          *(short *)(puVar10 + 1) = sVar22;
          puVar10[2] = lVar19;
          puVar24 = puVar10;
        }
        if (puVar24 == (undefined8 *)0x0) {
          return (undefined8 *)0x8007000e;
        }
      }
      else {
        *(undefined8 *)(lVar12 + 0x10) = *puVar24;
        *puVar24 = 0;
        *(short *)(puVar24 + 1) = sVar22;
        puVar24[2] = lVar19;
      }
      puVar10 = *(undefined8 **)(lVar12 + 8);
      puVar21 = puVar26;
      while (puVar25 = puVar10, puVar25 != (undefined8 *)0x0) {
        if (*(ushort *)(lVar19 + 10) < *(ushort *)(puVar25[2] + 10)) {
          *puVar24 = puVar25;
          break;
        }
        puVar21 = puVar25;
        puVar10 = (undefined8 *)*puVar25;
      }
      puVar10 = puVar26;
      if (puVar21 == (undefined8 *)0x0) {
        *(undefined8 **)(lVar12 + 8) = puVar24;
      }
      else {
        *puVar21 = puVar24;
      }
    }
  }
  return puVar10;
}


// FUN_180139b5c @ 180139b5c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8
FUN_180139b5c(longlong *param_1,undefined8 param_2,uint *param_3,ushort *param_4,undefined8 param_5,
             longlong param_6)

{
  ushort *puVar1;
  undefined8 uVar2;
  ushort uVar3;
  ulonglong uVar4;
  ushort local_res10 [4];
  
  uVar3 = (ushort)param_2;
  if (uVar3 <= *(ushort *)(param_1 + 3)) {
    (**(code **)(*param_1 + 0x38))(param_1,param_2,param_4);
    local_res10[0] = 0;
    FUN_1801388f8((longlong)param_1,uVar3,local_res10);
    puVar1 = FUN_180138d28((longlong)param_1,local_res10[0] + uVar3,*param_4,1);
    if ((puVar1 != (ushort *)0x0) && ((char)puVar1[9] != '\0')) {
      if ((puVar1[8] == 0) || (param_3 == (uint *)0x0)) {
        return 1;
      }
      for (uVar4 = 0; (ushort)uVar4 < puVar1[8]; uVar4 = (ulonglong)(ushort)((ushort)uVar4 + 1)) {
        uVar2 = FUN_18013ee34(param_3,*(longlong *)(*(longlong *)(puVar1 + 4) + uVar4 * 0x10),
                              *(uint *)(*(longlong *)(puVar1 + 4) + 8 + uVar4 * 0x10),param_6);
        if ((char)uVar2 != '\0') {
          return 1;
        }
      }
    }
  }
  return 0;
}


// FUN_180139c40 @ 180139c40

bool FUN_180139c40(longlong param_1,ushort param_2,ushort param_3,longlong param_4,ushort *param_5)

{
  short *psVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  undefined7 extraout_var;
  ulonglong uVar5;
  
  *param_5 = 0;
  psVar1 = (short *)(*(longlong *)(param_1 + 0x10) + (ulonglong)param_2 * 2);
  if (param_2 < *(ushort *)(param_1 + 0x18)) {
    uVar5 = 0;
    do {
      iVar4 = _o_iswspace(psVar1[uVar5]);
      if (iVar4 != 0) break;
      uVar3 = *param_5 + 1;
      uVar5 = (ulonglong)uVar3;
      *param_5 = uVar3;
    } while ((uint)uVar3 + (uint)param_2 < (uint)*(ushort *)(param_1 + 0x18));
  }
  bVar2 = FUN_180141d2c((undefined8 *)(*(longlong *)(param_4 + 8) + (ulonglong)param_3 * 0x28),
                        psVar1,(ulonglong)*param_5);
  return (int)CONCAT71(extraout_var,bVar2) != 0;
}


// FUN_180043b44 @ 180043b44

undefined8 FUN_180043b44(longlong param_1,ushort param_2)

{
  if (param_2 < *(ushort *)(param_1 + 0x38)) {
    return *(undefined8 *)(*(longlong *)(param_1 + 0x40) + (ulonglong)param_2 * 8);
  }
  return 0;
}


