// FUN_18002c5f0 @ 18002c5f0

undefined8
FUN_18002c5f0(longlong param_1,longlong param_2,longlong param_3,uint param_4,undefined4 *param_5,
             longlong *param_6,longlong *param_7)

{
  int iVar1;
  longlong lVar2;
  int *piVar3;
  byte *pbVar4;
  ushort uVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  ushort uVar9;
  ushort uVar10;
  byte *pbVar11;
  byte *pbVar12;
  int iVar13;
  int iVar14;
  short sVar15;
  ulonglong uVar16;
  ushort *puVar17;
  ulonglong uVar18;
  short sVar19;
  uint uVar20;
  undefined8 uVar21;
  uint local_res20 [2];
  byte *local_f0;
  longlong local_e0;
  longlong local_d8;
  short local_c8;
  ushort local_c6;
  uint local_c0;
  byte *local_b8;
  byte *local_b0;
  byte *local_a8;
  byte *local_a0;
  
  if ((((param_2 == 0) || (param_3 == 0)) || (param_5 == (undefined4 *)0x0)) ||
     ((param_6 == (longlong *)0x0 || (param_7 == (longlong *)0x0)))) {
    uVar21 = 0x80070057;
  }
  else {
    *param_5 = 0;
    *param_7 = 0;
    *param_6 = 0;
    local_res20[0] = param_4;
    memset(&local_c8,0,0x70);
    iVar13 = -1;
    local_d8 = 0;
    lVar2 = *(longlong *)(param_1 + 0x18);
    local_b0 = *(byte **)(lVar2 + 0x48);
    local_c6 = 0x10;
    uVar9 = 0x10;
    local_e0 = local_d8;
    iVar14 = iVar13;
    while ((local_e0 != param_3 && ((uVar9 & 0x10) != 0))) {
      local_a0 = (byte *)0x0;
      local_b8 = local_b0;
      FUN_18002cc60(lVar2,&local_c8);
      pbVar12 = local_b8;
      FUN_18002cb20(lVar2,(longlong)&local_c8);
      iVar1 = iVar13 + 1;
      if ((local_c6 & 1) == 0) {
        iVar1 = iVar13;
      }
      iVar13 = iVar1;
      local_f0 = local_a0;
      pbVar11 = local_b8;
      pbVar4 = local_f0;
      uVar9 = local_c6 & 0xff;
      while( true ) {
        local_f0 = pbVar4;
        uVar18 = 0;
        sVar19 = 0;
        if (local_c8 == *(short *)(param_2 + local_e0 * 2)) break;
        iVar1 = local_c0 + iVar13;
        if ((uVar9 & 2) != 0) {
          if (((local_c6 >> 9 & 1) == 0) && (pbVar11 = local_a8, (uVar9 & 0x20) == 0))
          goto LAB_18002ca44;
          local_f0 = (byte *)0x0;
        }
        uVar5 = (ushort)*pbVar11;
        uVar9 = **(ushort **)(lVar2 + 8);
        uVar16 = uVar18;
        sVar15 = sVar19;
        if (uVar9 <= *pbVar11) {
          do {
            sVar15 = sVar15 + uVar9;
            uVar16 = uVar16 + 1;
            uVar5 = (uVar5 - uVar9) * 0x100 + (ushort)pbVar11[uVar16];
            uVar9 = (*(ushort **)(lVar2 + 8))[uVar16];
          } while (uVar9 <= uVar5);
        }
        pbVar11 = pbVar11 + uVar16 + 1;
        local_c8 = *(short *)(*(longlong *)(lVar2 + 0x28) + (ulonglong)(ushort)(sVar15 + uVar5) * 4)
        ;
        local_c6 = *(ushort *)
                    (*(longlong *)(lVar2 + 0x28) + 2 + (ulonglong)(ushort)(sVar15 + uVar5) * 4);
        uVar20 = 0;
        if ((local_c6 & 4) == 0) {
          local_c0 = 0;
          pbVar12 = pbVar11;
        }
        else {
          local_c0 = (uint)*pbVar11;
          pbVar12 = pbVar11 + 1;
          if (local_c0 < 0xc0) {
            if (0x7f < local_c0) {
              local_c0 = (local_c0 & 0x7f) << 8 | (uint)*pbVar12;
              pbVar12 = pbVar11 + 2;
            }
          }
          else {
            local_c0 = (*pbVar12 & 0x7f | (local_c0 & 0x3f) << 7) << 8 | (uint)pbVar11[2];
            pbVar12 = pbVar11 + 3;
          }
        }
        iVar13 = iVar1 + 1;
        if ((local_c6 & 1) == 0) {
          iVar13 = iVar1;
        }
        uVar5 = local_c6 & 0x1d0;
        pbVar11 = pbVar12;
        pbVar4 = local_f0;
        uVar9 = local_c6;
        if (uVar5 != 0) {
          if (uVar5 == 0x10) {
            puVar17 = *(ushort **)(lVar2 + 0x20);
            sVar15 = 0;
            uVar10 = (ushort)*pbVar12;
            uVar5 = *puVar17;
            if (uVar5 <= *pbVar12) {
              do {
                sVar19 = sVar15 + uVar5;
                uVar20 = (int)uVar18 + 1;
                uVar18 = (ulonglong)uVar20;
                puVar17 = puVar17 + 1;
                uVar10 = (uVar10 - uVar5) * 0x100 + (ushort)pbVar11[1];
                uVar5 = *puVar17;
                pbVar11 = pbVar11 + 1;
                sVar15 = sVar19;
              } while (uVar5 <= uVar10);
            }
            if (local_f0 == (byte *)0x0) {
              local_f0 = pbVar12 + (int)(uVar20 + 1);
            }
            pbVar11 = pbVar12 + (int)(uVar20 + 1);
            pbVar4 = local_f0 +
                     *(uint *)(*(longlong *)(lVar2 + 0x40) +
                              (ulonglong)(ushort)(sVar19 + uVar10) * 4);
          }
          else {
            pbVar4 = pbVar12;
            if (uVar5 != 0x50) {
              if (uVar5 == 0x90) {
                uVar10 = (ushort)*pbVar12;
                puVar17 = *(ushort **)(lVar2 + 0x18);
                uVar5 = *puVar17;
                if (uVar5 <= *pbVar12) {
                  do {
                    uVar20 = (int)uVar18 + 1;
                    uVar18 = (ulonglong)uVar20;
                    puVar17 = puVar17 + 1;
                    uVar10 = (uVar10 - uVar5) * 0x100 + (ushort)pbVar11[1];
                    uVar5 = *puVar17;
                    pbVar11 = pbVar11 + 1;
                  } while (uVar5 <= uVar10);
                }
                pbVar11 = pbVar12 + (int)(uVar20 + 1);
                pbVar4 = local_f0;
              }
              else {
                pbVar4 = local_f0;
                if (uVar5 == 0x110) {
                  pbVar11 = pbVar12 + 3;
                }
              }
            }
          }
        }
      }
      uVar5 = local_c6 & 0x1c0;
      local_b8 = pbVar12;
      pbVar11 = local_f0;
      if (((local_c6 & 0x1c0) != 0) && (pbVar11 = pbVar12, uVar5 != 0x40)) {
        if (uVar5 == 0x80) {
          local_res20[0] = local_res20[0] & 0xffff0000;
          FUN_18003abf0((short *)local_res20,*(ushort **)(lVar2 + 0x18),pbVar12);
          uVar18 = (ulonglong)
                   *(uint *)(*(longlong *)(lVar2 + 0x38) + (ulonglong)(ushort)local_res20[0] * 4);
        }
        else {
          if (uVar5 != 0x100) {
            local_b0 = (byte *)0x0;
            pbVar11 = local_b0;
            goto LAB_18002c8ff;
          }
          uVar18 = (ulonglong)CONCAT21(CONCAT11(*pbVar12,pbVar12[1]),pbVar12[2]);
        }
        pbVar11 = (byte *)(uVar18 + *(longlong *)(lVar2 + 0x48));
      }
LAB_18002c8ff:
      local_b0 = pbVar11;
      local_e0 = local_e0 + 1;
      if ((uVar9 & 1) != 0) {
        local_d8 = local_e0;
        iVar14 = iVar13;
      }
    }
LAB_18002ca44:
    plVar8 = (longlong *)0x0;
    if (iVar14 == -1) {
      uVar21 = 1;
    }
    else {
      *param_5 = 1;
      plVar6 = (longlong *)thunk_FUN_18007ca58(4);
      plVar7 = plVar8;
      if (plVar6 != (longlong *)0x0) {
        *(undefined4 *)plVar6 = 0;
        plVar7 = plVar6;
      }
      *param_6 = (longlong)plVar7;
      plVar7 = (longlong *)thunk_FUN_18007ca58(8);
      if (plVar7 != (longlong *)0x0) {
        *plVar7 = 0;
        plVar8 = plVar7;
      }
      *param_7 = (longlong)plVar8;
      piVar3 = (int *)*param_6;
      if (piVar3 != (int *)0x0) {
        if (plVar8 != (longlong *)0x0) {
          *piVar3 = iVar14;
          *plVar8 = local_d8;
          return 0;
        }
        if (piVar3 != (int *)0x0) {
          _o_free();
          *param_6 = 0;
        }
      }
      if (*param_7 != 0) {
        _o_free();
        *param_7 = 0;
      }
      *param_5 = 0;
      uVar21 = 0x8007000e;
    }
  }
  return uVar21;
}


