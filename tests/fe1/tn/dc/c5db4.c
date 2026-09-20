// FUN_1800c5db4 @ 1800c5db4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800c5db4(longlong param_1,longlong param_2,void *param_3,uint param_4)

{
  undefined8 *puVar1;
  code *pcVar2;
  void *pvVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  longlong lVar9;
  short *psVar10;
  ulonglong uVar11;
  short *psVar12;
  ulonglong uVar13;
  longlong lVar14;
  ulonglong uVar15;
  undefined2 *puVar16;
  longlong lVar17;
  longlong *plVar18;
  ulonglong uVar19;
  short sVar20;
  uint local_res10 [2];
  undefined **local_168;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined **local_148;
  undefined8 local_140;
  undefined8 uStack_138;
  undefined8 local_130;
  undefined **local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined8 local_110;
  longlong local_108;
  undefined **local_100;
  undefined8 local_f8;
  undefined8 uStack_f0;
  undefined8 local_e8;
  undefined **local_e0;
  undefined8 local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined **local_c0;
  undefined8 local_b8;
  undefined8 uStack_b0;
  undefined8 local_a8;
  undefined **local_a0;
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined **local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined4 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined4 local_38;
  
  uVar19 = (ulonglong)param_4;
  local_128 = CTTSString::vftable;
  local_120 = 0;
  uStack_118 = 0;
  local_110 = 0;
  uVar6 = 0;
  local_res10[0] = 0;
  local_148 = CTTSString::vftable;
  local_140 = 0;
  uStack_138 = 0;
  local_130 = 0;
  local_e0 = CTTSString::vftable;
  local_d8 = 0;
  uStack_d0 = 0;
  local_c8 = 0;
  local_168 = CTTSString::vftable;
  local_160 = 0;
  uStack_158 = 0;
  local_150 = 0;
  local_100 = CTTSString::vftable;
  local_f8 = 0;
  uStack_f0 = 0;
  local_e8 = 0;
  plVar18 = *(longlong **)(param_2 + 0x20);
  if ((plVar18 != (longlong *)0x0) && (*plVar18 != 0)) {
    uVar8 = FUN_1800c4bf8(param_1,plVar18,local_res10);
    uVar11 = uVar8 & 0xffffffff;
    uVar5 = 0;
    if ((int)uVar8 < 0) {
LAB_1800c5ecd:
      if ((int)uVar11 < 0) goto LAB_1800c6379;
    }
    else {
      uVar5 = uVar6;
      if (local_res10[0] != 0) {
        iVar4 = _o__wcsicmp(**(undefined8 **)(param_2 + 0x20),L"date");
        puVar1 = *(undefined8 **)(param_2 + 0x20);
        if (iVar4 == 0) {
          uVar8 = FUN_1800c5900((longlong)puVar1,param_3,param_4,puVar1,(longlong *)&local_148,
                                (longlong *)&local_128,(longlong)&local_168);
          uVar11 = uVar8 & 0xffffffff;
          uVar5 = ~(uint)uVar8 >> 0x1f;
          goto LAB_1800c5ecd;
        }
        iVar4 = _o__wcsicmp(*puVar1,L"time");
        puVar1 = *(undefined8 **)(param_2 + 0x20);
        if (iVar4 == 0) {
          uVar8 = FUN_1800c6510(puVar1,(longlong)param_3,param_4,puVar1,(longlong *)&local_148,
                                (longlong *)&local_128);
          uVar11 = uVar8 & 0xffffffff;
          uVar5 = 0;
          if ((int)uVar8 < 0) goto LAB_1800c5ecd;
          FUN_18001d14c((longlong)&local_168,*(short **)(*(longlong *)(param_2 + 0x20) + 8));
        }
        else {
          iVar4 = _o__wcsicmp(*puVar1,L"cardinal");
          uVar5 = 0;
          if (iVar4 != 0) goto LAB_1800c5ed5;
          uVar7 = FUN_1800c573c(param_1,param_3,param_4,*(longlong **)(param_2 + 0x20),
                                (longlong *)&local_148,(longlong *)&local_128,(longlong *)&local_168
                                ,(longlong *)&local_100);
          uVar11 = (ulonglong)uVar7;
          uVar5 = 0;
          if ((int)uVar7 < 0) goto LAB_1800c5ecd;
        }
        uVar5 = 1;
      }
    }
LAB_1800c5ed5:
    lVar9 = FUN_18001b0e0((longlong)&local_148);
    if (((char)lVar9 == '\0') && (uVar5 != 0)) {
      local_res10[0] = 0;
      lVar9 = FUN_18001b0e0((longlong)&local_128);
      if ((char)lVar9 == '\0') {
        plVar18 = *(longlong **)(param_1 + 0x4e0);
        pcVar2 = *(code **)(*plVar18 + 0x20);
        psVar10 = FUN_18001c490((longlong)&local_128);
        uVar5 = (*pcVar2)(plVar18,psVar10,local_res10);
        uVar11 = (ulonglong)uVar5;
        uVar6 = local_res10[0];
        if ((int)uVar5 < 0) goto LAB_1800c6379;
      }
      if (uVar6 != 0) {
        local_a0 = CTTSString::vftable;
        local_98 = 0;
        uStack_90 = 0;
        local_88 = 0;
        local_c0 = CTTSString::vftable;
        local_b8 = 0;
        uStack_b0 = 0;
        local_a8 = 0;
        uVar6 = FUN_18002c3e0((longlong *)&local_e0,param_1 + 0x28);
        uVar8 = (ulonglong)uVar6;
        uVar11 = FUN_18001ca70((longlong)&local_148);
        lVar9 = param_1 + 0x28 + ((longlong)param_3 + (-0x28 - param_1) >> 1 & 0xffffffffU) * 2;
        local_108 = lVar9 + uVar11 * 2;
        uVar15 = 0xffffffffffffffff;
        if ((int)uVar6 < 0) {
LAB_1800c6210:
          uVar19 = 0;
          iVar4 = (int)uVar8;
          if (((iVar4 + 0x80000000U & 0x80000000) != 0) || (uVar11 = uVar8, iVar4 == -0x7ffb7ffd)) {
            if (iVar4 == -0x7ffb7ffd) goto LAB_1800c6235;
            goto LAB_1800c627c;
          }
        }
        else {
          if (uVar11 <= uVar19) {
            uVar13 = 0;
            if (uVar11 != 0) {
              do {
                psVar10 = FUN_18001c490((longlong)&local_148);
                *(short *)(lVar9 + uVar13 * 2) = psVar10[uVar13];
                uVar13 = uVar13 + 1;
              } while (uVar13 < uVar11);
            }
            if (uVar13 < uVar19) {
              puVar16 = (undefined2 *)(lVar9 + uVar13 * 2);
              for (lVar17 = uVar19 - uVar13; lVar17 != 0; lVar17 = lVar17 + -1) {
                *puVar16 = 0x20;
                puVar16 = puVar16 + 1;
              }
            }
            lVar17 = FUN_18001b0e0((longlong)&local_168);
            if ((char)lVar17 == '\0') {
              FUN_18001d14c((longlong)&local_a0,*(short **)(*(longlong *)(param_2 + 0x20) + 8));
              psVar10 = FUN_18001c490((longlong)&local_168);
              uVar19 = 0xffffffffffffffff;
              do {
                uVar19 = uVar19 + 1;
              } while (psVar10[uVar19] != 0);
              psVar12 = FUN_18001c490((longlong)&local_168);
              psVar10 = *(short **)(*(longlong *)(param_2 + 0x20) + 8);
              lVar17 = -1;
              do {
                lVar14 = lVar17;
                lVar17 = lVar14 + 1;
              } while (psVar10[lVar17] != 0);
              uVar6 = FUN_180058730(psVar10,lVar14 + 2,(longlong)psVar12,uVar19);
              uVar8 = (ulonglong)uVar6;
            }
            lVar17 = FUN_18001b0e0((longlong)&local_100);
            if ((char)lVar17 == '\0') {
              FUN_18001d14c((longlong)&local_c0,*(short **)(*(longlong *)(param_2 + 0x20) + 0x10));
              psVar10 = FUN_18001c490((longlong)&local_100);
              uVar19 = 0xffffffffffffffff;
              do {
                uVar19 = uVar19 + 1;
              } while (psVar10[uVar19] != 0);
              psVar12 = FUN_18001c490((longlong)&local_100);
              psVar10 = *(short **)(*(longlong *)(param_2 + 0x20) + 0x10);
              lVar17 = -1;
              do {
                lVar14 = lVar17;
                lVar17 = lVar14 + 1;
              } while (psVar10[lVar17] != 0);
              uVar6 = FUN_180058730(psVar10,lVar14 + 2,(longlong)psVar12,uVar19);
              uVar8 = (ulonglong)uVar6;
            }
            if (-1 < (int)uVar8) {
              local_78 = CTTSWordSink::vftable;
              local_70 = 0;
              local_68 = 0;
              uStack_60 = 0;
              local_58 = 0;
              local_50 = 0;
              local_48 = 0;
              uStack_40 = 0;
              local_38 = 0;
              psVar10 = FUN_18001c490((longlong)&local_128);
              uVar6 = FUN_1800c5620(param_1,param_2,lVar9,local_108,psVar10,&local_78);
              if (-1 < (int)uVar6) {
                uVar6 = FUN_180071b70(param_1,(longlong)&local_78);
              }
              uVar8 = (ulonglong)uVar6;
              FUN_1800727ac(&local_78);
            }
            goto LAB_1800c6210;
          }
          uVar8 = 0x80048003;
LAB_1800c6235:
          uVar19 = 0;
          lVar9 = FUN_18001b0e0((longlong)&local_e0);
          if ((char)lVar9 == '\0') {
            psVar10 = FUN_18001c490((longlong)&local_e0);
            uVar19 = 0xffffffffffffffff;
            do {
              uVar19 = uVar19 + 1;
            } while (psVar10[uVar19] != 0);
            psVar10 = FUN_18001c490((longlong)&local_e0);
            uVar6 = FUN_180058730((short *)(param_1 + 0x28),0x1f5,(longlong)psVar10,uVar19);
            uVar19 = (ulonglong)uVar6;
            uVar11 = uVar19;
            if ((int)uVar6 < 0) goto LAB_1800c635f;
          }
LAB_1800c627c:
          lVar9 = FUN_18001b0e0((longlong)&local_a0);
          if ((char)lVar9 == '\0') {
            pvVar3 = *(void **)(*(longlong *)(param_2 + 0x20) + 8);
            lVar9 = -1;
            do {
              lVar9 = lVar9 + 1;
            } while (*(short *)((longlong)pvVar3 + lVar9 * 2) != 0);
            uVar6 = (int)lVar9 + 1;
            uVar19 = FUN_180008a38(pvVar3,2,(ulonglong)uVar6);
            sVar20 = 0;
            uVar11 = uVar19 & 0xffffffff;
            if ((int)uVar19 < 0) goto LAB_1800c635f;
            psVar10 = FUN_18001c490((longlong)&local_a0);
            uVar19 = 0xffffffffffffffff;
            do {
              uVar19 = uVar19 + 1;
            } while (psVar10[uVar19] != sVar20);
            uVar6 = FUN_180058730(*(short **)(*(longlong *)(param_2 + 0x20) + 8),(ulonglong)uVar6,
                                  (longlong)psVar10,uVar19);
            uVar19 = (ulonglong)uVar6;
          }
          uVar11 = uVar19;
          if (-1 < (int)uVar19) {
            lVar9 = FUN_18001b0e0((longlong)&local_c0);
            if ((char)lVar9 == '\0') {
              pvVar3 = *(void **)(*(longlong *)(param_2 + 0x20) + 0x10);
              lVar9 = -1;
              do {
                lVar9 = lVar9 + 1;
              } while (*(short *)((longlong)pvVar3 + lVar9 * 2) != 0);
              uVar6 = (int)lVar9 + 1;
              uVar19 = FUN_180008a38(pvVar3,2,(ulonglong)uVar6);
              sVar20 = 0;
              uVar11 = uVar19 & 0xffffffff;
              if (-1 < (int)uVar19) {
                psVar10 = FUN_18001c490((longlong)&local_c0);
                do {
                  uVar15 = uVar15 + 1;
                } while (psVar10[uVar15] != sVar20);
                uVar6 = FUN_180058730(*(short **)(*(longlong *)(param_2 + 0x20) + 0x10),
                                      (ulonglong)uVar6,(longlong)psVar10,uVar15);
                uVar11 = (ulonglong)uVar6;
                if (-1 < (int)uVar6) goto LAB_1800c635d;
              }
            }
            else {
LAB_1800c635d:
              uVar11 = uVar8;
            }
          }
        }
LAB_1800c635f:
        FUN_18001d780(&local_c0);
        FUN_18001d780(&local_a0);
        goto LAB_1800c6379;
      }
    }
  }
  uVar11 = 0x80048003;
LAB_1800c6379:
  FUN_18001d780(&local_100);
  FUN_18001d780(&local_168);
  FUN_18001d780(&local_e0);
  FUN_18001d780(&local_148);
  FUN_18001d780(&local_128);
  return uVar11;
}


