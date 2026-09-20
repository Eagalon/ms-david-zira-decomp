// FUN_18001bf24 @ 18001bf24

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_18001bf24(uint *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  code *pcVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  short *psVar8;
  longlong lVar9;
  short *psVar10;
  ulonglong uVar11;
  longlong lVar12;
  longlong *plVar13;
  uint uVar14;
  longlong *plVar15;
  longlong *plVar16;
  longlong *plVar17;
  ulonglong uVar18;
  longlong *plVar19;
  longlong *plVar20;
  longlong *plVar21;
  longlong *plVar22;
  undefined8 local_58;
  short *local_50;
  longlong local_48;
  
  if (param_2 == 0) {
    iVar6 = -0x7ff8ffa9;
  }
  else {
    iVar6 = 0;
    plVar2 = *(longlong **)(*(longlong *)(param_2 + 0xe0) + 0x2d8);
    plVar7 = (longlong *)FUN_180034e44(param_2);
    plVar21 = (longlong *)0x0;
    if (plVar7[2] != 0) {
      plVar21 = *(longlong **)(*plVar7 + 0x10);
    }
    while ((plVar7 = plVar21, plVar7 != (longlong *)0x0 && (-1 < iVar6))) {
      plVar1 = plVar7 + 0x17;
      FUN_18001d344((longlong)plVar1,(longlong)(plVar7 + 0x13));
      FUN_18001ca14((longlong)plVar1);
      plVar15 = (longlong *)0x0;
      while (uVar14 = (uint)plVar15, plVar17 = (longlong *)0xffffffff, uVar14 < param_1[0xc]) {
        FUN_1800197b4(&local_58,*(longlong *)(param_1 + 0xe) + (longlong)plVar15 * 0x14);
        psVar8 = (short *)FUN_18001c3f8((longlong)plVar1,(longlong)&local_58);
        FUN_18001d780(&local_58);
        if (psVar8 != (short *)0x0) {
          FUN_18007ac40((longlong)plVar1,psVar8);
          plVar21 = (longlong *)0x0;
          plVar17 = plVar15;
          if (-1 < (int)uVar14) goto LAB_18001c1b1;
          break;
        }
        plVar15 = (longlong *)(ulonglong)(uVar14 + 1);
      }
      pcVar3 = *(code **)(*plVar2 + 0x10);
      uVar4 = (**(code **)(*plVar7 + 0xf0))(plVar7);
      iVar5 = (*pcVar3)(plVar2,uVar4);
      if (iVar5 == 1) {
        plVar21 = (longlong *)0x0;
        plVar22 = plVar21;
        while (uVar14 = (uint)plVar22, plVar15 = plVar17, uVar14 < *param_1) {
          FUN_1800197b4(&local_58,*(longlong *)(param_1 + 2) + (longlong)plVar22 * 0x14);
          plVar16 = (longlong *)0x0;
          plVar15 = plVar1;
          plVar21 = plVar16;
          lVar9 = FUN_18001b0e0((longlong)plVar1);
          psVar8 = local_50;
          if ((char)lVar9 == '\0') {
            if (local_50 != (short *)0x0) {
              plVar16 = (longlong *)0x0;
              if (*local_50 != (short)plVar21) {
                plVar13 = plVar21;
                if (local_50 != (short *)0x0) {
                  plVar13 = (longlong *)0xffffffffffffffff;
                  do {
                    plVar13 = (longlong *)((longlong)plVar13 + 1);
                  } while (local_50[(longlong)plVar13] != (short)plVar21);
                }
                lVar9 = FUN_18001b0e0((longlong)plVar15);
                plVar15 = plVar21;
                if ((char)lVar9 == '\0') {
                  plVar15 = (longlong *)0xffffffffffffffff;
                  do {
                    plVar15 = (longlong *)((longlong)plVar15 + 1);
                  } while (*(short *)(plVar7[0x18] + (longlong)plVar15 * 2) != (short)plVar21);
                }
                plVar20 = (longlong *)plVar7[0x18];
                plVar16 = plVar21;
                for (plVar15 = (longlong *)
                               ((longlong)plVar20 + ((longlong)plVar15 - (longlong)plVar13) * 2);
                    plVar19 = plVar16, plVar21 = plVar16, plVar20 <= plVar15;
                    plVar15 = (longlong *)((longlong)plVar15 + -2)) {
                  while( true ) {
                    plVar16 = plVar15;
                    if (plVar13 <= plVar19) goto LAB_18001c100;
                    psVar10 = FUN_18001c490((longlong)&local_58);
                    if (*(short *)((longlong)plVar15 + (longlong)plVar19 * 2) !=
                        psVar10[(longlong)plVar19]) break;
                    plVar19 = (longlong *)((longlong)plVar19 + 1);
                  }
                  plVar16 = plVar21;
                }
              }
              goto LAB_18001c100;
            }
          }
          else {
LAB_18001c100:
            if (psVar8 != (short *)0x0) {
              _o_free(psVar8);
              plVar21 = (longlong *)0x0;
            }
          }
          if (local_48 != 0) {
            _o_free();
            plVar21 = (longlong *)0x0;
          }
          lVar9 = FUN_18001ca70((longlong)plVar1);
          lVar12 = -1;
          do {
            lVar12 = lVar12 + 1;
          } while (*(short *)(*(longlong *)(param_1 + 2) + (longlong)plVar22 * 0x14 + lVar12 * 2) !=
                   (short)plVar21);
          if (plVar16 == (longlong *)(plVar7[0x18] + (lVar9 - lVar12) * 2)) {
            FUN_18001d14c((longlong)(plVar7 + 0x17),(short *)&DAT_18017db58);
            iVar6 = (**(code **)(plVar7[0x17] + 8))
                              (plVar7 + 0x17,
                               *(longlong *)(param_1 + 2) + (longlong)(int)uVar14 * 0x14);
            plVar21 = (longlong *)0x0;
            plVar15 = plVar22;
            if (iVar6 < 0) goto LAB_18001c3af;
            break;
          }
          plVar22 = (longlong *)(ulonglong)(uVar14 + 1);
        }
LAB_18001c1b1:
        if ((int)plVar15 < 0) goto LAB_18001c1bd;
      }
      else {
LAB_18001c1bd:
        pcVar3 = *(code **)(*plVar2 + 0x10);
        uVar4 = (**(code **)(*plVar7 + 0xf0))(plVar7);
        iVar5 = (*pcVar3)(plVar2,uVar4);
        if (iVar5 == 3) {
          uVar18 = 0;
          while (uVar14 = (uint)uVar18, uVar14 < param_1[4]) {
            FUN_1800197b4(&local_58,*(longlong *)(param_1 + 6) + uVar18 * 0x14);
            uVar11 = FUN_18001c3f8((longlong)(plVar7 + 0x17),(longlong)&local_58);
            FUN_18001d780(&local_58);
            lVar9 = FUN_18001ca70((longlong)(plVar7 + 0x17));
            lVar12 = -1;
            do {
              lVar12 = lVar12 + 1;
            } while (*(short *)(*(longlong *)(param_1 + 6) + uVar18 * 0x14 + lVar12 * 2) != 0);
            if (uVar11 == plVar7[0x18] + (lVar9 - lVar12) * 2) {
              FUN_18001d14c((longlong)(plVar7 + 0x17),(short *)&DAT_18017db58);
              iVar6 = (**(code **)(plVar7[0x17] + 8))
                                (plVar7 + 0x17,
                                 *(longlong *)(param_1 + 6) + (longlong)(int)uVar14 * 0x14);
              plVar21 = (longlong *)0x0;
              if ((iVar6 < 0) || (-1 < (int)uVar14)) goto LAB_18001c3af;
              break;
            }
            uVar18 = (ulonglong)(uVar14 + 1);
          }
        }
        pcVar3 = *(code **)(*plVar2 + 0x10);
        uVar4 = (**(code **)(*plVar7 + 0xf0))(plVar7);
        iVar5 = (*pcVar3)(plVar2,uVar4);
        uVar18 = 0;
        plVar21 = (longlong *)0x0;
        if (iVar5 == 2) {
          while( true ) {
            plVar21 = (longlong *)0x0;
            uVar14 = (uint)uVar18;
            if (param_1[8] <= uVar14) break;
            FUN_1800197b4(&local_58,*(longlong *)(param_1 + 10) + uVar18 * 0x14);
            uVar11 = FUN_18001c3f8((longlong)(plVar7 + 0x17),(longlong)&local_58);
            FUN_18001d780(&local_58);
            lVar9 = FUN_18001ca70((longlong)(plVar7 + 0x17));
            lVar12 = -1;
            do {
              lVar12 = lVar12 + 1;
            } while (*(short *)(*(longlong *)(param_1 + 10) + uVar18 * 0x14 + lVar12 * 2) != 0);
            if (uVar11 == plVar7[0x18] + (lVar9 - lVar12) * 2) {
              FUN_18001d14c((longlong)(plVar7 + 0x17),(short *)&DAT_18017db58);
              iVar6 = (**(code **)(plVar7[0x17] + 8))
                                (plVar7 + 0x17,
                                 *(longlong *)(param_1 + 10) + (longlong)(int)uVar14 * 0x14);
              plVar21 = (longlong *)0x0;
              break;
            }
            uVar18 = (ulonglong)(uVar14 + 1);
          }
        }
      }
LAB_18001c3af:
      if (((longlong *)plVar7[5] != plVar21) && (*(longlong *)plVar7[6] != 0)) {
        plVar21 = *(longlong **)(*(longlong *)plVar7[6] + 0x10);
      }
    }
  }
  return iVar6;
}


