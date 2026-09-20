// FUN_18000fc40 @ 18000fc40

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

wchar_t * FUN_18000fc40(longlong param_1,short param_2,char param_3,uint param_4,int param_5,
                       longlong *param_6)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  short sVar3;
  longlong lVar4;
  undefined2 *puVar5;
  short *psVar6;
  undefined8 uVar7;
  bool bVar8;
  char cVar9;
  bool bVar10;
  undefined2 uVar11;
  ushort uVar12;
  ushort uVar13;
  int iVar14;
  undefined8 *puVar15;
  wchar_t *pwVar16;
  uint *puVar17;
  longlong *plVar18;
  longlong lVar19;
  undefined8 *puVar20;
  int *piVar21;
  longlong lVar22;
  undefined8 uVar23;
  undefined7 extraout_var;
  byte bVar24;
  wchar_t *pwVar25;
  ulonglong uVar26;
  byte *pbVar27;
  ushort uVar28;
  short sVar29;
  wchar_t *pwVar30;
  longlong *plVar31;
  uint uVar32;
  uint uVar33;
  ulonglong uVar34;
  ushort uVar35;
  ulonglong uVar36;
  undefined8 *puVar37;
  short *psVar38;
  uint uVar39;
  undefined8 *puVar40;
  longlong *plVar41;
  ushort *puVar42;
  longlong *plVar43;
  uint uVar44;
  uint uVar45;
  longlong lVar46;
  ushort *puVar47;
  longlong *plVar48;
  bool bVar49;
  undefined1 auStackY_128 [32];
  ushort *in_stack_fffffffffffffef8;
  ushort local_f6;
  ushort local_f4 [2];
  ushort local_f0;
  ushort local_ec [2];
  uint local_e8;
  undefined2 local_e4;
  uint local_e0;
  longlong *local_d8;
  short local_d0;
  byte *local_c8;
  uint local_c0;
  uint local_bc;
  longlong local_b8;
  longlong local_b0;
  longlong local_a8;
  longlong local_a0;
  ushort *local_98;
  short *local_90;
  longlong *local_88;
  uint *local_80;
  longlong local_78;
  longlong local_70;
  longlong local_68;
  undefined1 local_60 [4];
  undefined4 uStack_5c;
  short sStack_58;
  ushort uStack_56;
  short sStack_54;
  short sStack_52;
  undefined2 uStack_50;
  ulonglong local_48;
  
  local_48 = DAT_1801c0240 ^ (ulonglong)auStackY_128;
  psVar38 = (short *)param_6[5];
  local_d8 = param_6;
  if ((param_2 == -1) ||
     (pbVar27 = (byte *)(*(longlong *)
                          (*(longlong *)(psVar38 + 4) +
                          (ulonglong)((ushort)(param_2 - *psVar38) >> 0xe) * 8) +
                        (ulonglong)((ushort)(param_2 - *psVar38) & 0x3fff) * 0x12),
     pbVar27 == (byte *)0x0)) {
    pwVar30 = (wchar_t *)0x80070057;
  }
  else {
    puVar42 = (ushort *)(pbVar27 + 2);
    local_d0 = param_2;
    local_c8 = pbVar27;
    local_bc = param_4;
    local_b0 = param_1;
    local_88 = (longlong *)psVar38;
    if (*(short *)(pbVar27 + 4) == -1) {
      uVar36 = FUN_1800114e0((longlong *)param_6[2],pbVar27,param_2,*(short *)(pbVar27 + 6));
      uVar44 = (uint)uVar36;
      plVar41 = local_d8;
      if ((((*puVar42 == 0) && (*(short *)(pbVar27 + 6) == (short)local_d8[1])) &&
          ((((lVar46 = FUN_18000f1f0(psVar38,(short)local_d8[6]), lVar46 == 0 ||
             (*(ushort *)(lVar46 + 8) < *(ushort *)(pbVar27 + 8))) ||
            ((*(ushort *)(lVar46 + 8) == *(ushort *)(pbVar27 + 8) &&
             (*(ushort *)(pbVar27 + 10) < *(ushort *)(lVar46 + 10))))) &&
           (iVar14 = FUN_180139508(*plVar41,*(undefined2 *)(pbVar27 + 8)), plVar41 = local_d8,
           iVar14 != 0)))) && ((*pbVar27 & 3) == 0)) {
        *(short *)(local_d8 + 6) = local_d0;
      }
      bVar10 = true;
      bVar49 = true;
      if ((*puVar42 < *(ushort *)(*(longlong *)(param_1 + 0x18) + 0x38)) &&
         (lVar46 = *(longlong *)
                    (*(longlong *)(*(longlong *)(param_1 + 0x18) + 0x40) + (ulonglong)*puVar42 * 8),
         lVar46 != 0)) {
        bVar8 = bVar10;
        if (((*(int *)(lVar46 + 0x20) != 0) &&
            (((param_4 == *(uint *)(lVar46 + 0x30) || (param_4 == 0)) ||
             (bVar8 = false, *(uint *)(lVar46 + 0x30) == 0)))) && (bVar8 = bVar10, param_5 != 0)) {
          bVar8 = *(int *)(lVar46 + 0x18) == param_5;
        }
        bVar10 = bVar8;
        if ((*(int *)(param_1 + 0x28) != 0) && (bVar49 = true, *(ushort *)(lVar46 + 10) != 0)) {
          bVar49 = (*(ushort *)(lVar46 + 10) & (ushort)*(int *)(param_1 + 0x28)) != 0;
        }
      }
      lVar46 = plVar41[3];
      uVar12 = *(short *)(local_c8 + 6) - *(short *)(lVar46 + 0x20);
      if (uVar12 < *(ushort *)(lVar46 + 0x22)) {
        uVar28 = *(ushort *)(*(longlong *)(lVar46 + 0x28) + 8 + (ulonglong)uVar12 * 0x10);
        uVar36 = (ulonglong)uVar28;
        lVar46 = *(longlong *)(*(longlong *)(lVar46 + 0x28) + (ulonglong)uVar12 * 0x10);
        local_ec[0] = 0;
        if (uVar28 != 0) {
          do {
            pbVar27 = (byte *)0x0;
            if ((int)uVar44 < 0) break;
            sVar29 = *(short *)(lVar46 + (ulonglong)local_ec[0] * 2);
            if (sVar29 != -1) {
              uVar12 = sVar29 - (short)*local_88;
              pbVar27 = (byte *)(*(longlong *)
                                  (*(longlong *)((longlong)local_88 + 8) +
                                  (ulonglong)(uVar12 >> 0xe) * 8) +
                                (ulonglong)(uVar12 & 0x3fff) * 0x12);
            }
            if (bVar10) {
LAB_18000ff8c:
              if (bVar49) {
                local_a8 = plVar41[7];
                if (pbVar27 == (byte *)0x0) {
                  uVar44 = 0x80004005;
                }
                else {
                  lVar22 = *(longlong *)(param_1 + 0x18);
                  local_90 = (short *)plVar41[8];
                  psVar38 = (short *)0x0;
                  local_a0 = *(longlong *)
                              (*(longlong *)(lVar22 + 0x40) +
                              (ulonglong)*(ushort *)(pbVar27 + 2) * 8);
                  lVar19 = *(longlong *)
                            (*(longlong *)(lVar22 + 0x50) +
                            (ulonglong)((uint)*(ushort *)(pbVar27 + 4) + *(int *)(local_a0 + 4)) * 8
                            );
                  local_bc = (uint)*(ushort *)(lVar19 + 8);
                  puVar47 = (ushort *)
                            (*(longlong *)(*(longlong *)(lVar22 + 200) + 0x10) + 4 +
                            (ulonglong)*(uint *)(lVar19 + 4));
                  for (iVar14 = 0; iVar14 < (int)local_bc; iVar14 = iVar14 + 1) {
                    lVar19 = *(longlong *)
                              (*(longlong *)(lVar22 + 0x60) +
                              (ulonglong)(*(int *)(local_a0 + 0xc) + (uint)*puVar47) * 8);
                    if (*(short *)(lVar19 + 0xc) != -1) {
                      if (local_90 <= psVar38) {
                        uVar44 = 0x7a;
                        goto LAB_18001007b;
                      }
                      lVar4 = (longlong)psVar38 * 6;
                      if (param_3 == '\0') {
                        uVar11 = *(undefined2 *)(lVar19 + 8);
                      }
                      else {
                        uVar11 = *(undefined2 *)(lVar19 + 10);
                      }
                      psVar38 = (short *)(ulonglong)(ushort)((short)psVar38 + 1);
                      *(undefined2 *)(lVar4 + local_a8) = uVar11;
                      *(undefined2 *)(lVar4 + 2 + local_a8) = *(undefined2 *)(lVar19 + 2);
                      *(undefined2 *)(lVar4 + 4 + local_a8) = *(undefined2 *)(lVar19 + 0xc);
                    }
                    puVar47 = puVar47 + 2;
                  }
                  uVar44 = 0;
LAB_18001007b:
                  uVar12 = 0;
                  plVar41 = local_d8;
                  param_1 = local_b0;
                  if ((short)psVar38 != 0) {
                    local_90 = (short *)(lVar46 + (ulonglong)local_ec[0] * 2);
                    local_a0 = lVar46;
                    do {
                      local_f4[0] = (ushort)uVar36;
                      local_f0 = (ushort)psVar38;
                      plVar41 = local_d8;
                      lVar46 = local_a0;
                      param_1 = local_b0;
                      if ((int)uVar44 < 0) break;
                      puVar47 = (ushort *)(local_a8 + (ulonglong)uVar12 * 6);
                      if (*puVar47 == *puVar42) {
                        if (((*local_c8 >> 1 ^ *pbVar27) & 1) == 0) {
                          uVar28 = *(ushort *)(local_c8 + 10) + *(short *)(pbVar27 + 10);
                          if (uVar28 < *(ushort *)(local_c8 + 10)) {
LAB_18001119d:
                            uVar44 = 0x80041003;
                          }
                          else {
                            uVar13 = uVar28 + puVar47[2];
                            uVar35 = uVar13;
                            if (uVar13 < uVar28) {
                              uVar35 = 0xffff;
                            }
                            uVar44 = -(uint)(uVar13 < uVar28) & 0x80070216;
                            if (uVar13 < uVar28) {
                              if (uVar44 == 0x80070216) goto LAB_18001119d;
                            }
                            else {
                              _local_60 = (ulonglong)
                                          CONCAT24(*(undefined2 *)(pbVar27 + 6),
                                                   CONCAT22(*(undefined2 *)
                                                             (local_a8 + 2 + (ulonglong)uVar12 * 6),
                                                            *(undefined2 *)(pbVar27 + 2))) << 0x10;
                              sStack_58 = *(short *)(local_c8 + 8);
                              sStack_54 = *local_90;
                              sStack_52 = local_d0;
                              _local_60 = CONCAT71(stack0xffffffffffffffa1,
                                                   *local_c8 & 1 | *pbVar27 & 2);
                              uStack_50 = 0xffff;
                              uStack_56 = uVar35;
                              puVar15 = FUN_180011ad0((longlong)local_d8,local_60);
                              psVar38 = (short *)(ulonglong)local_f0;
                              uVar44 = (uint)puVar15;
                              uVar36 = (ulonglong)local_f4[0];
                            }
                          }
                        }
                      }
                      uVar12 = uVar12 + 1;
                      plVar41 = local_d8;
                      lVar46 = local_a0;
                      param_1 = local_b0;
                    } while (uVar12 < (ushort)psVar38);
                  }
                }
              }
            }
            else {
              piVar21 = (int *)FUN_180043b44(*(longlong *)(param_1 + 0x18),*(ushort *)(pbVar27 + 2))
              ;
              if (((piVar21 == (int *)0x0) || (piVar21[8] == 0)) || (*piVar21 != 1)) {
                bVar10 = true;
                goto LAB_18000ff8c;
              }
            }
            local_ec[0] = local_ec[0] + 1;
          } while (local_ec[0] < (ushort)uVar36);
        }
      }
    }
    else {
      FUN_1800114e0((longlong *)param_6[3],pbVar27,param_2,*(short *)(pbVar27 + 8));
      uVar44 = 0;
      lVar46 = *(longlong *)(param_1 + 0x18);
      uVar28 = 0;
      local_98 = (ushort *)param_6[7];
      uVar36 = param_6[8];
      local_f6 = 0;
      lVar22 = *(longlong *)(*(longlong *)(lVar46 + 0x40) + (ulonglong)*puVar42 * 8);
      lVar19 = *(longlong *)
                (*(longlong *)(lVar46 + 0x50) +
                (ulonglong)(*(int *)(lVar22 + 4) + (uint)*(ushort *)(local_c8 + 4)) * 8);
      uVar12 = *(ushort *)(lVar19 + 8);
      puVar42 = (ushort *)
                (*(longlong *)(*(longlong *)(lVar46 + 200) + 0x10) + 4 +
                (ulonglong)*(uint *)(lVar19 + 4));
      uVar45 = 0;
      for (uVar39 = uVar45; (int)uVar39 < (int)(uint)uVar12; uVar39 = uVar39 + 1) {
        lVar19 = *(longlong *)
                  (*(longlong *)(lVar46 + 0x60) +
                  (ulonglong)(*(int *)(lVar22 + 0xc) + (uint)*puVar42) * 8);
        if (*(short *)(lVar19 + 0xc) != -1) {
          if (uVar36 <= uVar28) {
            uVar44 = 0x7a;
            break;
          }
          lVar4 = (ulonglong)uVar28 * 6;
          if (param_3 == '\0') {
            uVar11 = *(undefined2 *)(lVar19 + 8);
          }
          else {
            uVar11 = *(undefined2 *)(lVar19 + 10);
          }
          *(undefined2 *)(lVar4 + (longlong)local_98) = uVar11;
          uVar28 = uVar28 + 1;
          *(undefined2 *)(lVar4 + 2 + (longlong)local_98) = *(undefined2 *)(lVar19 + 2);
          *(undefined2 *)(lVar4 + 4 + (longlong)local_98) = *(undefined2 *)(lVar19 + 0xc);
          local_f6 = uVar28;
        }
        puVar42 = puVar42 + 2;
      }
      if (uVar28 != 0) {
        if ((((*(ushort *)(local_c8 + 2) < *(ushort *)(*(longlong *)(param_1 + 0x18) + 0x38)) &&
             (piVar21 = *(int **)(*(longlong *)(*(longlong *)(param_1 + 0x18) + 0x40) +
                                 (ulonglong)*(ushort *)(local_c8 + 2) * 8), piVar21 != (int *)0x0))
            && (piVar21[8] != 0)) && (*piVar21 == 1)) {
          local_a0 = 1;
        }
        else {
          local_a0 = 0;
        }
        lVar46 = local_d8[2];
        uVar12 = *(short *)(local_c8 + 8) - *(short *)(lVar46 + 0x20);
        if (uVar12 < *(ushort *)(lVar46 + 0x22)) {
          uVar36 = 0;
          local_e8 = 0;
          local_b8 = *(longlong *)(*(longlong *)(lVar46 + 0x28) + (ulonglong)uVar12 * 0x10);
          uVar45 = (uint)*(ushort *)(*(longlong *)(lVar46 + 0x28) + 8 + (ulonglong)uVar12 * 0x10);
        }
        else {
          uVar36 = 0;
          local_b8 = 0;
          local_e8 = 0;
        }
LAB_18000fe62:
        lVar46 = local_b8;
        bVar10 = false;
        if (-1 < (int)uVar44) {
          uStack_50 = 0;
          uVar12 = 0;
          _local_60 = 0;
          sStack_58 = 0;
          uStack_56 = 0;
          sStack_54 = 0;
          sStack_52 = 0;
          if ((ushort)uVar45 == 0) {
LAB_18001038b:
            puVar42 = local_98;
            param_1 = local_b0;
            pwVar30 = (wchar_t *)0x0;
            uVar12 = *(ushort *)((longlong)local_98 + (uVar36 & 0xffff) * 6);
            uVar39 = 0;
            if ((uVar12 < *(ushort *)(*(longlong *)(local_b0 + 0x18) + 0x38)) &&
               (lVar22 = *(longlong *)
                          (*(longlong *)(*(longlong *)(local_b0 + 0x18) + 0x40) +
                          (ulonglong)uVar12 * 8), lVar22 != 0)) {
              if ((*(int *)(local_b0 + 0x28) == 0) || (*(ushort *)(lVar22 + 10) == 0)) {
                bVar10 = true;
              }
              else {
                bVar10 = (*(ushort *)(lVar22 + 10) & (ushort)*(int *)(local_b0 + 0x28)) != 0;
              }
              if (local_a0 != 0) {
                iVar14 = 1;
                if (*(int *)(lVar22 + 0x20) != 0) {
                  if ((((local_bc == *(uint *)(lVar22 + 0x30)) || (local_bc == 0)) ||
                      (pwVar16 = pwVar30, *(uint *)(lVar22 + 0x30) == 0)) &&
                     (pwVar16 = (wchar_t *)0x1, param_5 != 0)) {
                    pwVar16 = (wchar_t *)(ulonglong)(*(int *)(lVar22 + 0x18) == param_5);
                  }
                  iVar14 = (int)pwVar16;
                  uVar36 = (ulonglong)local_e8;
                }
                local_b8 = lVar46;
                if (iVar14 == 0) goto LAB_1800105bd;
              }
              local_b8 = lVar46;
              if (!bVar10) goto LAB_1800105bd;
            }
            lVar22 = *local_d8;
            pwVar16 = pwVar30;
            if (*(ushort *)(local_c8 + 8) < *(ushort *)(lVar22 + 0x18)) {
              pwVar16 = (wchar_t *)
                        (*(longlong *)(lVar22 + 0x10) + (ulonglong)*(ushort *)(local_c8 + 8) * 2);
            }
            lVar19 = *(longlong *)
                      (*(longlong *)(*(longlong *)(local_b0 + 0x18) + 0x40) + (ulonglong)uVar12 * 8)
            ;
            uVar32 = *(uint *)(lVar19 + 0x34);
            pwVar25 = pwVar30;
            if ((uVar32 != 0) &&
               (lVar4 = *(longlong *)(*(longlong *)(local_b0 + 0x18) + 0xb8),
               uVar32 < *(uint *)(lVar4 + 4))) {
              pwVar25 = (wchar_t *)(*(longlong *)(lVar4 + 0x10) + (ulonglong)uVar32 * 2);
            }
            local_b8 = lVar46;
            if (((*(int *)(lVar22 + 8) != 1) && (*(int *)(lVar19 + 0x38) == 0)) &&
               ((*(int *)(lVar19 + 0x3c) == 0 &&
                (((pwVar16 == (wchar_t *)0x0 || (pwVar25 == (wchar_t *)0x0)) ||
                 (pwVar16 = wcschr(pwVar25,*pwVar16), pwVar16 == (wchar_t *)0x0)))))) {
              uVar36 = (ulonglong)local_e8;
              goto LAB_1800105bd;
            }
            uVar23 = _local_60;
            uStack_56 = 0;
            sStack_54 = 0;
            sStack_52 = 0;
            uStack_50 = 0xffff;
            plVar41 = (longlong *)local_d8[2];
            psVar38 = (short *)local_d8[5];
            sStack_58 = *(short *)(local_c8 + 8);
            _local_60 = (uint6)CONCAT22(*(undefined2 *)
                                         ((longlong)puVar42 + (ulonglong)(ushort)local_e8 * 6),
                                        (short)_local_60);
            _local_60 = CONCAT26(sStack_58,_local_60);
            uVar7 = _local_60;
            local_60[0] = (byte)uVar23;
            bVar24 = (*local_c8 & 1) * '\x02' | local_60[0] & 0xfd;
            stack0xffffffffffffffa1 = SUB87(uVar7,1);
            _local_60 = CONCAT71(stack0xffffffffffffffa1,(bVar24 >> 1 ^ bVar24) & 1 ^ bVar24);
            if ((int)plVar41[2] != 0) {
              uVar36 = (**(code **)(*plVar41 + 0x10))(plVar41);
              uVar36 = (uVar36 & 0xffffffff) % (ulonglong)*(uint *)(plVar41 + 2);
              uVar34 = uVar36;
              do {
                iVar14 = (int)uVar34;
                puVar15 = (undefined8 *)(plVar41[1] + uVar34 * 0x18);
                if (((*(longlong *)(plVar41[1] + 0x10 + uVar34 * 0x18) == 0) &&
                    (*(char *)(puVar15 + 1) == '\0')) ||
                   (cVar9 = (**(code **)(*plVar41 + 0x18))(plVar41,*puVar15,local_60), cVar9 != '\0'
                   )) {
                  lVar46 = local_b8;
                  if (-1 < iVar14) {
                    lVar46 = *(longlong *)(plVar41[1] + 0x10 + (longlong)iVar14 * 0x18);
                    if (lVar46 != 0) {
                      if ((*(short *)(lVar46 + 0xc) == sStack_54) &&
                         (uVar44 = uVar39, *(short *)(lVar46 + 0xe) == sStack_52))
                      goto LAB_1800105af;
                      uVar12 = (ushort)psVar38[8] >> 0xe;
                      if ((ushort)psVar38[8] < (ushort)psVar38[1]) {
                        lVar22 = (ulonglong)uVar12 * 8;
                        if (*(longlong *)(lVar22 + *(longlong *)(psVar38 + 4)) != 0)
                        goto LAB_180010d55;
                        lVar19 = thunk_FUN_18007ca58(0x48000);
                        *(longlong *)(lVar22 + *(longlong *)(psVar38 + 4)) = lVar19;
                        if (lVar19 != 0) goto LAB_180010d55;
                        uVar39 = 0x8007000e;
                      }
                      else {
                        uVar39 = 0x80041003;
                      }
                    }
                    uVar44 = uVar39;
                    lVar46 = local_b8;
                    if ((int)uVar39 < 0) goto LAB_1800105af;
                  }
                  break;
                }
                if ((int)pwVar30 == 0) {
                  uVar44 = (**(code **)(*plVar41 + 0x20))(plVar41);
                  pwVar30 = (wchar_t *)(ulonglong)uVar44;
                  if (1 < *(uint *)(plVar41 + 2)) {
                    pwVar30 = (wchar_t *)(ulonglong)(uVar44 % (*(uint *)(plVar41 + 2) - 1) + 1);
                  }
                }
                uVar32 = iVar14 + (int)pwVar30;
                uVar44 = uVar32 - (int)plVar41[2];
                if (uVar32 < *(uint *)(plVar41 + 2)) {
                  uVar44 = uVar32;
                }
                uVar34 = (ulonglong)uVar44;
                lVar46 = local_b8;
              } while (uVar44 != (uint)uVar36);
            }
            local_b8 = lVar46;
            uVar39 = 0;
            plVar41 = (longlong *)local_d8[3];
            uVar44 = 0;
            psVar38 = (short *)local_d8[5];
            if ((int)plVar41[2] != 0) {
              uVar36 = (**(code **)(*plVar41 + 0x10))(plVar41);
              uVar36 = (uVar36 & 0xffffffff) % (ulonglong)*(uint *)(plVar41 + 2);
              uVar34 = uVar36;
              do {
                iVar14 = (int)uVar34;
                puVar15 = (undefined8 *)(plVar41[1] + uVar34 * 0x18);
                if (((*(longlong *)(plVar41[1] + 0x10 + uVar34 * 0x18) == 0) &&
                    (*(char *)(puVar15 + 1) == '\0')) ||
                   (cVar9 = (**(code **)(*plVar41 + 0x18))(plVar41,*puVar15,local_60), cVar9 != '\0'
                   )) {
                  if (-1 < iVar14) {
                    lVar46 = *(longlong *)(plVar41[1] + 0x10 + (longlong)iVar14 * 0x18);
                    if (lVar46 != 0) {
                      if ((*(short *)(lVar46 + 0xc) == sStack_54) &&
                         (*(short *)(lVar46 + 0xe) == sStack_52)) goto LAB_1800105af;
                      uVar12 = (ushort)psVar38[8] >> 0xe;
                      if ((ushort)psVar38[8] < (ushort)psVar38[1]) {
                        lVar22 = (ulonglong)uVar12 * 8;
                        if (*(longlong *)(lVar22 + *(longlong *)(psVar38 + 4)) != 0)
                        goto LAB_180010d55;
                        lVar19 = thunk_FUN_18007ca58(0x48000);
                        *(longlong *)(lVar22 + *(longlong *)(psVar38 + 4)) = lVar19;
                        if (lVar19 != 0) goto LAB_180010d55;
                        uVar44 = 0x8007000e;
                      }
                      else {
                        uVar44 = 0x80041003;
                      }
                    }
                    if ((int)uVar44 < 0) goto LAB_1800105af;
                  }
                  break;
                }
                if (uVar39 == 0) {
                  uVar39 = (**(code **)(*plVar41 + 0x20))(plVar41);
                  if (1 < *(uint *)(plVar41 + 2)) {
                    uVar39 = uVar39 % (*(uint *)(plVar41 + 2) - 1) + 1;
                  }
                }
                uVar33 = iVar14 + uVar39;
                uVar32 = uVar33 - (int)plVar41[2];
                if (uVar33 < *(uint *)(plVar41 + 2)) {
                  uVar32 = uVar33;
                }
                uVar34 = (ulonglong)uVar32;
              } while (uVar32 != (uint)uVar36);
            }
            plVar18 = (longlong *)0x0;
            psVar38 = (short *)local_d8[4];
            uVar44 = 0;
            psVar6 = (short *)local_d8[5];
            local_e0 = 0;
            local_c0 = 0;
            plVar41 = *(longlong **)(psVar38 + 4);
            plVar43 = plVar18;
            plVar48 = plVar18;
            local_90 = psVar38;
            if (*(longlong **)(psVar38 + 4) != (longlong *)0x0) {
              do {
                plVar31 = plVar41;
                lVar46 = 0;
                pbVar27 = (byte *)plVar31[2];
                if ((uStack_56 <= *(ushort *)(pbVar27 + 10)) && ((int)plVar18 == 0)) {
                  local_c0 = 1;
                  plVar43 = plVar48;
                }
                if ((((*(short *)(pbVar27 + 2) == local_60._2_2_) &&
                     (*(short *)(pbVar27 + 4) == (short)uStack_5c)) &&
                    (*(short *)(pbVar27 + 6) == uStack_5c._2_2_)) &&
                   (*(short *)(pbVar27 + 8) == sStack_58)) {
                  if ((((*pbVar27 ^ local_60[0]) & 2) != 0) || (((*pbVar27 ^ local_60[0]) & 1) != 0)
                     ) goto LAB_180010b14;
                  sVar29 = -1;
                  if ((*(short *)(pbVar27 + 0xc) != sStack_54) ||
                     (*(short *)(pbVar27 + 0xe) != sStack_52)) {
                    uVar12 = (ushort)psVar6[8] >> 0xe;
                    if ((ushort)psVar6[1] <= (ushort)psVar6[8]) {
                      uVar44 = 0x80041003;
LAB_1800112db:
                      plVar18 = (longlong *)(ulonglong)local_e0;
                      break;
                    }
                    lVar46 = (ulonglong)uVar12 * 8;
                    if (*(longlong *)(lVar46 + *(longlong *)(psVar6 + 4)) == 0) {
                      lVar22 = thunk_FUN_18007ca58(0x48000);
                      *(longlong *)(lVar46 + *(longlong *)(psVar6 + 4)) = lVar22;
                      psVar38 = local_90;
                      if (lVar22 == 0) {
                        uVar44 = 0x8007000e;
                        goto LAB_1800112db;
                      }
                    }
                    lVar19 = (ulonglong)(ushort)(psVar6[8] + uVar12 * -0x4000) * 0x12;
                    lVar22 = *(longlong *)(lVar46 + *(longlong *)(psVar6 + 4));
                    puVar1 = (undefined4 *)(lVar22 + lVar19);
                    *puVar1 = local_60;
                    puVar1[1] = uStack_5c;
                    puVar1[2] = CONCAT22(uStack_56,sStack_58);
                    puVar1[3] = CONCAT22(sStack_52,sStack_54);
                    *(undefined2 *)(lVar22 + 0x10 + lVar19) = uStack_50;
                    lVar46 = *(longlong *)(lVar46 + *(longlong *)(psVar6 + 4));
                    psVar6[8] = psVar6[8] + 1;
                    lVar46 = lVar46 + lVar19;
                    sVar29 = psVar6[8] + -1 + *psVar6;
                  }
                  if (uStack_56 < *(ushort *)(pbVar27 + 10)) {
                    if ((sVar29 == -1) || (lVar46 == 0)) {
                      *(undefined1 (*) [4])pbVar27 = local_60;
                      *(undefined4 *)(pbVar27 + 4) = uStack_5c;
                      *(uint *)(pbVar27 + 8) = CONCAT22(uStack_56,sStack_58);
                      *(uint *)(pbVar27 + 0xc) = CONCAT22(sStack_52,sStack_54);
                      *(undefined2 *)(pbVar27 + 0x10) = uStack_50;
                    }
                    else {
                      plVar31[2] = lVar46;
                      *(short *)(lVar46 + 0x10) = (short)plVar31[1];
                      *(short *)(plVar31 + 1) = sVar29;
                    }
                    if (plVar48 != (longlong *)0x0) {
                      *plVar48 = *plVar31;
                      if (plVar43 == (longlong *)0x0) {
                        *plVar31 = *(longlong *)(psVar38 + 4);
                        *(longlong **)(psVar38 + 4) = plVar31;
                      }
                      else {
                        *plVar31 = *plVar43;
                        *plVar43 = (longlong)plVar31;
                      }
                    }
                  }
                  else if ((sVar29 != -1) && (lVar46 != 0)) {
                    *(undefined2 *)(lVar46 + 0x10) = *(undefined2 *)(pbVar27 + 0x10);
                    *(short *)(pbVar27 + 0x10) = sVar29;
                  }
                  plVar18 = (longlong *)0x1;
                  local_e0 = 1;
                }
                else {
LAB_180010b14:
                  plVar18 = (longlong *)(ulonglong)local_e0;
                }
                uVar44 = 0;
                if ((longlong *)*plVar31 == (longlong *)0x0) break;
                plVar18 = (longlong *)(ulonglong)local_c0;
                plVar41 = (longlong *)*plVar31;
                plVar48 = plVar31;
              } while( true );
            }
            if ((-1 < (int)uVar44) && ((int)plVar18 == 0)) {
              psVar38 = (short *)local_d8[5];
              uVar12 = (ushort)psVar38[8] >> 0xe;
              if ((ushort)psVar38[8] < (ushort)psVar38[1]) {
                lVar46 = (ulonglong)uVar12 * 8;
                if (*(longlong *)(lVar46 + *(longlong *)(psVar38 + 4)) == 0) {
                  lVar22 = thunk_FUN_18007ca58(0x48000);
                  *(longlong *)(lVar46 + *(longlong *)(psVar38 + 4)) = lVar22;
                  if (lVar22 == 0) {
                    uVar44 = 0x8007000e;
                    goto LAB_1800105af;
                  }
                }
                lVar19 = (ulonglong)(ushort)(psVar38[8] + uVar12 * -0x4000) * 0x12;
                lVar22 = *(longlong *)(lVar46 + *(longlong *)(psVar38 + 4));
                puVar15 = (undefined8 *)(lVar22 + lVar19);
                *puVar15 = _local_60;
                puVar15[1] = CONCAT26(sStack_52,CONCAT24(sStack_54,CONCAT22(uStack_56,sStack_58)));
                *(undefined2 *)(lVar22 + 0x10 + lVar19) = uStack_50;
                lVar46 = *(longlong *)(lVar46 + *(longlong *)(psVar38 + 4));
                psVar38[8] = psVar38[8] + 1;
                lVar46 = lVar46 + lVar19;
                sVar29 = psVar38[8] + -1 + *psVar38;
                lVar22 = local_d8[4];
                puVar15 = *(undefined8 **)(lVar22 + 0x10);
                if (puVar15 == (undefined8 *)0x0) {
                  puVar20 = (undefined8 *)FUN_18007ca58(0x18);
                  puVar15 = (undefined8 *)0x0;
                  if (puVar20 != (undefined8 *)0x0) {
                    *puVar20 = 0;
                    *(short *)(puVar20 + 1) = sVar29;
                    puVar20[2] = lVar46;
                    puVar15 = puVar20;
                  }
                  uVar44 = 0x8007000e;
                  if (puVar15 == (undefined8 *)0x0) goto LAB_1800105af;
                }
                else {
                  *(undefined8 *)(lVar22 + 0x10) = *puVar15;
                  *puVar15 = 0;
                  *(short *)(puVar15 + 1) = sVar29;
                  puVar15[2] = lVar46;
                }
                puVar20 = *(undefined8 **)(lVar22 + 8);
                puVar40 = (undefined8 *)0x0;
                while (puVar37 = puVar20, puVar37 != (undefined8 *)0x0) {
                  if (*(ushort *)(lVar46 + 10) < *(ushort *)(puVar37[2] + 10)) {
                    *puVar15 = puVar37;
                    break;
                  }
                  puVar40 = puVar37;
                  puVar20 = (undefined8 *)*puVar37;
                }
                uVar44 = 0;
                if (puVar40 == (undefined8 *)0x0) {
                  *(undefined8 **)(lVar22 + 8) = puVar15;
                }
                else {
                  *puVar40 = puVar15;
                }
              }
              else {
                uVar44 = 0x80041003;
              }
            }
            goto LAB_1800105af;
          }
          do {
            uVar23 = _local_60;
            if ((int)uVar44 < 0) break;
            sVar29 = *(short *)(lVar46 + (ulonglong)uVar12 * 2);
            if (sVar29 == -1) {
              pbVar27 = (byte *)0x0;
            }
            else {
              uVar28 = sVar29 - (short)*local_88;
              pbVar27 = (byte *)(*(longlong *)
                                  (*(longlong *)((longlong)local_88 + 8) +
                                  (ulonglong)(uVar28 >> 0xe) * 8) +
                                (ulonglong)(uVar28 & 0x3fff) * 0x12);
            }
            psVar38 = (short *)((longlong)local_98 + (uVar36 & 0xffff) * 6);
            if ((*psVar38 == *(short *)(pbVar27 + 2)) && (((*pbVar27 >> 1 ^ *local_c8) & 1) == 0)) {
              uVar28 = *(short *)(local_c8 + 10) + *(short *)(pbVar27 + 10);
              if (*(ushort *)(local_c8 + 10) <= uVar28) {
                uVar35 = uVar28 + psVar38[2];
                if (uVar28 <= uVar35) {
                  local_60 = (undefined1  [4])CONCAT22(*(undefined2 *)(local_c8 + 2),local_60._0_2_)
                  ;
                  bVar10 = true;
                  _local_60 = CONCAT24(*(undefined2 *)
                                        ((longlong)local_98 + 2 + (ulonglong)(ushort)local_e8 * 6),
                                       local_60);
                  _local_60 = CONCAT26(*(undefined2 *)(local_c8 + 6),_local_60);
                  uVar7 = _local_60;
                  sStack_58 = *(short *)(pbVar27 + 8);
                  sStack_54 = local_d0;
                  local_60[0] = (byte)uVar23;
                  bVar24 = *local_c8 & 2 | local_60[0] & 0xfd;
                  _local_60 = CONCAT71((int7)((ulonglong)uVar7 >> 8),
                                       (bVar24 ^ *pbVar27) & 1 ^ bVar24);
                  uStack_50 = 0xffff;
                  uStack_56 = uVar35;
                  sStack_52 = sVar29;
                  puVar15 = FUN_180011ad0((longlong)local_d8,local_60);
                  uVar44 = (uint)puVar15;
                  uVar36 = (ulonglong)local_e8;
                  goto LAB_180010360;
                }
                uVar36 = (ulonglong)local_e8;
              }
              uVar44 = 0x80041003;
            }
LAB_180010360:
            uVar12 = uVar12 + 1;
          } while (uVar12 < (ushort)uVar45);
          param_1 = local_b0;
          uVar28 = local_f6;
          local_b8 = lVar46;
          if ((!bVar10) && (-1 < (int)uVar44)) goto LAB_18001038b;
          goto LAB_1800105bd;
        }
        goto LAB_18001010f;
      }
LAB_1800105e6:
      if (-1 < (int)uVar44) {
        uVar36 = 0;
        lVar46 = *(longlong *)(param_1 + 0x18);
        local_70 = local_d8[9];
        local_88 = (longlong *)*local_d8;
        sVar29 = *(short *)(local_c8 + 8);
        local_90 = (short *)local_d8[0xb];
        local_68 = local_d8[10];
        local_bc = *local_c8 & 1;
        local_f0 = 0;
        local_a0 = *(longlong *)
                    (*(longlong *)(lVar46 + 0x40) + (ulonglong)*(ushort *)(local_c8 + 2) * 8);
        lVar22 = *(longlong *)
                  (*(longlong *)(lVar46 + 0x50) +
                  (ulonglong)((uint)*(ushort *)(local_c8 + 4) + *(int *)(local_a0 + 4)) * 8);
        local_98 = (ushort *)
                   ((ulonglong)*(uint *)(lVar22 + 4) +
                   *(longlong *)(*(longlong *)(lVar46 + 200) + 0x10));
        uVar34 = (ulonglong)*(ushort *)(lVar22 + 8);
        local_c0 = (uint)*local_98;
        local_98 = local_98 + (uVar34 + 1) * 2;
        plVar41 = local_88;
        local_78 = lVar46;
LAB_18001067f:
        while( true ) {
          uVar44 = 0;
          iVar14 = (int)uVar34;
          local_b0 = CONCAT44(local_b0._4_4_,iVar14);
          if ((int)local_c0 <= iVar14) break;
          lVar22 = *(longlong *)(lVar46 + 0x70);
          puVar5 = *(undefined2 **)
                    (*(longlong *)(lVar46 + 0x60) +
                    (ulonglong)(*(int *)(local_a0 + 0xc) + (uint)*local_98) * 8);
          uVar34 = (ulonglong)*(uint *)(puVar5 + 4);
          uVar26 = (ulonglong)*(uint *)(puVar5 + 6);
          if ((int)plVar41[1] == 0) {
            local_80 = *(uint **)(lVar22 + uVar34 * 8);
            puVar17 = *(uint **)(lVar22 + uVar26 * 8);
          }
          else {
            local_80 = *(uint **)(lVar22 + uVar26 * 8);
            puVar17 = *(uint **)(lVar22 + uVar34 * 8);
          }
          if (*(int *)(puVar5 + 2) == 2) {
            local_80 = *(uint **)(lVar22 + uVar34 * 8);
            puVar17 = *(uint **)(lVar22 + uVar26 * 8);
          }
          if ((local_80 == (uint *)0x0) || (puVar17 == (uint *)0x0)) {
            uVar34 = (ulonglong)(iVar14 + 1);
            local_98 = local_98 + 2;
          }
          else {
            uVar36 = (ulonglong)*puVar17;
            uVar12 = 0;
            lVar22 = *(longlong *)(*(longlong *)(lVar46 + 200) + 0x10);
            uVar28 = uVar12;
            while( true ) {
              if (*(ushort *)(uVar36 + lVar22) <= uVar28) goto LAB_18001149a;
              uVar35 = 0xffff;
              if (*(short *)(*(longlong *)
                              (*(longlong *)(lVar46 + 0x80) +
                              (ulonglong)*(uint *)(lVar22 + uVar36 + 4 + (ulonglong)uVar28 * 4) * 8)
                            + 0x14) != -1) break;
              uVar28 = uVar28 + 1;
            }
            if (*(ushort *)(uVar36 + lVar22) != 0) {
              puVar17 = (uint *)(uVar36 + 4 + lVar22);
              uVar36 = (ulonglong)*(ushort *)(uVar36 + lVar22);
              do {
                uVar28 = *(ushort *)
                          (*(longlong *)(*(longlong *)(lVar46 + 0x80) + (ulonglong)*puVar17 * 8) +
                          0x14);
                if ((uVar28 != 0xffff) && ((uVar35 == 0xffff || (uVar28 < uVar35)))) {
                  uVar35 = uVar28;
                }
                puVar17 = puVar17 + 1;
                uVar36 = uVar36 - 1;
              } while (uVar36 != 0);
            }
            uVar11 = puVar5[1];
            uVar2 = *puVar5;
            lVar22 = *(longlong *)(lVar46 + 0xd8);
            uVar28 = *(ushort *)
                      ((ulonglong)*local_80 + *(longlong *)(*(longlong *)(lVar46 + 200) + 0x10));
            local_e0 = CONCAT22(local_e0._2_2_,uVar28);
            local_e4 = uVar11;
            local_a8 = lVar22;
            while( true ) {
              plVar41 = local_88;
              pwVar30 = (wchar_t *)0x0;
              local_e8 = CONCAT22(local_e8._2_2_,uVar12);
              if (uVar28 <= uVar12) break;
              piVar21 = *(int **)(*(longlong *)(lVar46 + 0x80) +
                                 (ulonglong)
                                 *(uint *)(*(longlong *)(*(longlong *)(lVar46 + 200) + 0x10) +
                                           (ulonglong)uVar12 * 4 + 4 + (ulonglong)*local_80) * 8);
              local_ec[0] = 0;
              local_f4[0] = 0;
              if (uVar35 != 0xffff) {
                bVar10 = false;
                if (((int)local_88[1] == 1) && (local_bc == 0)) {
                  iVar14 = *piVar21;
                  if (iVar14 == 0) {
                    if (((short)piVar21[3] != 0) || ((piVar21[1] & 0xfffffffdU) == 0)) {
                      bVar10 = true;
                    }
                    if (bVar10) {
LAB_180011378:
                      iVar14 = (**(code **)(*local_88 + 0x28))(local_88,sVar29,local_f4);
                      lVar22 = local_a8;
                      uVar11 = local_e4;
                      if (iVar14 == 0) goto LAB_1800108f4;
                    }
                  }
                  else if (((iVar14 - 1U & 0xfffffffc) == 0) && (iVar14 != 3)) goto LAB_180011378;
                }
                if (piVar21[1] == 1) {
                  uVar12 = *(ushort *)(piVar21 + 3);
                  local_b8 = CONCAT44(local_b8._4_4_,piVar21[4]);
                  uVar44 = piVar21[2];
                  pwVar16 = pwVar30;
                  if ((uVar44 != 0) && (uVar44 < *(uint *)(*(longlong *)(lVar46 + 0xb8) + 4))) {
                    pwVar16 = (wchar_t *)
                              (*(longlong *)(*(longlong *)(lVar46 + 0xb8) + 0x10) +
                              (ulonglong)uVar44 * 2);
                  }
                  if ((uint)(ushort)(sVar29 + local_f4[0]) + (uint)uVar12 <=
                      (uint)*(ushort *)(plVar41 + 3)) {
                    pwVar25 = (wchar_t *)
                              (plVar41[2] + (ulonglong)(ushort)(sVar29 + local_f4[0]) * 2);
                    iVar14 = wcsncmp(pwVar25,pwVar16,(ulonglong)uVar12);
                    if ((iVar14 == 0) ||
                       ((lVar22 = local_a8, plVar41 = local_88, uVar11 = local_e4,
                        (int)local_b8 != 0 &&
                        (iVar14 = _o__wcsnicmp(pwVar25,pwVar16,(ulonglong)uVar12), lVar22 = local_a8
                        , plVar41 = local_88, uVar11 = local_e4, iVar14 == 0)))) {
                      pwVar30 = (wchar_t *)0x1;
                      lVar22 = local_a8;
                      plVar41 = local_88;
                      uVar11 = local_e4;
                      local_ec[0] = uVar12;
                    }
                  }
                  uVar44 = (uint)pwVar30;
                  uVar12 = (ushort)local_e8;
                }
                else if (piVar21[1] == 2) {
                  if (piVar21[6] != 0xffffffff) {
                    pwVar30 = *(wchar_t **)
                               (*(longlong *)(lVar46 + 0xa0) + (ulonglong)(uint)piVar21[6] * 8);
                  }
                  uVar23 = FUN_180139b5c(plVar41,(ulonglong)(ushort)(sVar29 + local_f4[0]),
                                         (uint *)pwVar30,local_ec,in_stack_fffffffffffffef8,lVar46);
                  uVar44 = (uint)((int)uVar23 != 0);
                  uVar11 = local_e4;
                  lVar22 = local_a8;
                }
                else {
                  in_stack_fffffffffffffef8 = local_ec;
                  bVar10 = FUN_180139c40((longlong)plVar41,sVar29 + local_f4[0],
                                         *(ushort *)(piVar21 + 2),lVar22,in_stack_fffffffffffffef8);
                  uVar44 = (uint)CONCAT71(extraout_var,bVar10);
                  uVar11 = local_e4;
                  lVar22 = local_a8;
                }
                if (uVar44 == 0) goto LAB_1800108f4;
                uVar36 = (ulonglong)local_f0;
                if (local_f0 < (ushort)local_68) {
                  puVar5 = (undefined2 *)(local_70 + uVar36 * 8);
                  *puVar5 = uVar2;
                  puVar5[1] = uVar11;
                  puVar5[2] = local_f4[0] + local_ec[0];
                  puVar5[3] = uVar35;
                  if ((int)plVar41[1] == 1) {
                    iVar14 = *piVar21;
                    if (iVar14 == 0) {
                      if (((short)piVar21[3] != 0) || (uVar44 = local_bc, piVar21[1] == 0))
                      goto LAB_180010972;
                    }
                    else {
                      if ((iVar14 - 1U & 0xfffffffd) == 0) goto LAB_180010972;
                      if ((iVar14 - 4U < 2) || (uVar44 = 0, iVar14 == 2)) {
                        uVar44 = 1;
                      }
                    }
                  }
                  else {
LAB_180010972:
                    uVar44 = 0;
                  }
                  *(uint *)((longlong)local_90 + uVar36 * 4) = uVar44;
                  local_f0 = local_f0 + 1;
                  goto LAB_1800108f4;
                }
                uVar44 = 0x80004005;
                goto LAB_180010101;
              }
LAB_1800108f4:
              uVar12 = uVar12 + 1;
              lVar46 = local_78;
              uVar28 = (ushort)local_e0;
            }
            uVar34 = (ulonglong)((int)local_b0 + 1);
            uVar36 = (ulonglong)local_f0;
            local_98 = local_98 + 2;
          }
        }
LAB_180010101:
        lVar46 = local_70;
        uVar12 = 0;
        pbVar27 = local_c8;
        if ((short)uVar36 != 0) {
          while (-1 < (int)uVar44) {
            uVar34 = (ulonglong)uVar12;
            uStack_56 = *(short *)(pbVar27 + 10) + *(short *)(lVar46 + 6 + uVar34 * 8);
            if (uStack_56 < *(ushort *)(pbVar27 + 10)) {
              uVar44 = 0x80041003;
            }
            else {
              sStack_58 = *(short *)(lVar46 + 4 + uVar34 * 8) + *(short *)(pbVar27 + 8);
              sStack_54 = local_d0;
              sStack_52 = *(undefined2 *)(lVar46 + uVar34 * 8);
              _local_60 = (ulonglong)
                          CONCAT24(*(undefined2 *)(pbVar27 + 6),
                                   CONCAT22(*(undefined2 *)(lVar46 + 2 + uVar34 * 8),
                                            *(undefined2 *)(pbVar27 + 2))) << 0x10;
              uStack_50 = 0xffff;
              _local_60 = CONCAT71(stack0xffffffffffffffa1,
                                   *(byte *)((longlong)local_90 + uVar34 * 4) & 1 | *pbVar27 & 2);
              puVar15 = FUN_180011ad0((longlong)local_d8,local_60);
              uVar36 = (ulonglong)local_f0;
              uVar44 = (uint)puVar15;
              pbVar27 = local_c8;
            }
            uVar12 = uVar12 + 1;
            if ((ushort)uVar36 <= uVar12) break;
          }
        }
      }
    }
LAB_18001010f:
    pwVar30 = (wchar_t *)(ulonglong)uVar44;
  }
  return pwVar30;
LAB_180010d55:
  lVar4 = (ulonglong)(ushort)(psVar38[8] + uVar12 * -0x4000) * 0x12;
  lVar19 = *(longlong *)(lVar22 + *(longlong *)(psVar38 + 4));
  puVar15 = (undefined8 *)(lVar19 + lVar4);
  *puVar15 = _local_60;
  puVar15[1] = CONCAT26(sStack_52,CONCAT24(sStack_54,CONCAT22(uStack_56,sStack_58)));
  *(undefined2 *)(lVar19 + 0x10 + lVar4) = uStack_50;
  lVar22 = *(longlong *)(lVar22 + *(longlong *)(psVar38 + 4));
  psVar38[8] = psVar38[8] + 1;
  sVar29 = psVar38[8];
  sVar3 = *psVar38;
  *(undefined2 *)(lVar22 + 0x10 + lVar4) = *(undefined2 *)(lVar46 + 0x10);
  *(short *)(lVar46 + 0x10) = sVar29 + -1 + sVar3;
  uVar44 = 0;
LAB_1800105af:
  uVar36 = (ulonglong)local_e8;
  param_1 = local_b0;
  uVar28 = local_f6;
LAB_1800105bd:
  uVar12 = (short)uVar36 + 1;
  uVar36 = CONCAT62((int6)(uVar36 >> 0x10),uVar12);
  local_e8 = (uint)uVar36;
  if (uVar28 <= uVar12) goto LAB_1800105e6;
  goto LAB_18000fe62;
LAB_18001149a:
  uVar36 = (ulonglong)local_f0;
  uVar34 = (ulonglong)(iVar14 + 1);
  local_98 = local_98 + 2;
  goto LAB_18001067f;
}


