// FUN_180069c00 @ 180069c00

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_180069c00(uint *param_1,longlong *param_2,uint *param_3,uint param_4)

{
  ulonglong uVar1;
  char cVar2;
  int *piVar3;
  ulonglong *puVar4;
  code *pcVar5;
  longlong *plVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong *plVar12;
  longlong *plVar13;
  longlong *plVar14;
  ulonglong uVar15;
  longlong lVar16;
  byte bVar17;
  uint *puVar18;
  byte bVar19;
  ulonglong uVar20;
  longlong lVar21;
  int iVar22;
  undefined4 *puVar23;
  ulonglong *puVar24;
  uint uVar25;
  ulonglong uVar26;
  undefined8 *puVar27;
  longlong *plVar28;
  int iVar29;
  bool bVar30;
  undefined1 auStackY_2a8 [32];
  byte local_258 [4];
  uint local_254;
  uint local_250 [2];
  longlong *local_248;
  longlong lStack_240;
  ulonglong local_238;
  ulonglong local_230;
  longlong local_228;
  undefined8 local_220;
  ulonglong *local_218;
  undefined8 local_210;
  longlong *local_208;
  ulonglong local_200;
  longlong *local_1f8;
  longlong local_1f0;
  longlong **local_1e8;
  uint local_1e0;
  uint local_1d8;
  uint local_1d4;
  uint local_1d0;
  longlong *local_1c8;
  ulonglong uStack_1c0;
  ulonglong local_1b8;
  ulonglong local_1b0;
  uint *local_1a8;
  longlong *local_1a0;
  ulonglong local_198;
  undefined8 local_188;
  ulonglong uStack_180;
  ulonglong local_168;
  undefined8 *local_160;
  uint *local_158;
  ulonglong *local_150;
  undefined8 *puStack_148;
  undefined8 *local_140;
  ulonglong local_138;
  longlong local_130;
  ulonglong *local_128;
  undefined8 uStack_120;
  longlong local_118;
  longlong local_110;
  undefined8 uStack_108;
  longlong local_100;
  longlong **local_f8;
  undefined8 local_f0;
  ulonglong local_e8 [4];
  undefined4 local_c8;
  undefined1 local_c4;
  undefined8 local_b8 [12];
  ulonglong local_58;
  
  local_58 = DAT_1801c0240 ^ (ulonglong)auStackY_2a8;
  *param_3 = 0;
  local_1a8 = param_1;
  local_1a0 = param_2;
  local_158 = param_3;
  uVar7 = FUN_180022470(param_2,(int *)param_3);
  local_138 = (longlong)(int)uVar7;
  uVar8 = FUN_180022470(param_2,(int *)param_3);
  uVar9 = FUN_180022470(param_2,(int *)param_3);
  *(longlong *)param_1 = (longlong)(int)uVar9;
  FUN_180022714(param_1,param_2,param_3,(ulonglong)param_4);
  FUN_1800745f0(local_e8);
  local_218 = local_e8;
  local_c8 = *(undefined4 *)(*(longlong *)(param_1 + 0x1e) + 0x50);
  local_c4 = *(undefined1 *)(*(longlong *)(param_1 + 0x1e) + 0x2c);
  local_110 = 0;
  uStack_108 = 0;
  local_100 = 0;
  local_128 = (ulonglong *)0x0;
  uStack_120 = 0;
  local_118 = 0;
  local_1d4 = 0;
  local_1d8 = 0;
  FUN_180020500((longlong)param_1,param_2,&local_218,param_3,&local_110,(longlong *)&local_128,
                &local_1d8,&local_1d4);
  local_220 = (ulonglong *)0x140000000;
  plVar12 = *(longlong **)(param_1 + 0x16);
  local_218 = (ulonglong *)0x140000000;
  puVar27 = (undefined8 *)plVar12[1];
  uVar26 = (longlong)puVar27 - *plVar12 >> 3;
  local_168 = uVar26;
  if (puVar27 == (undefined8 *)plVar12[2]) {
    FUN_1800d7d00(plVar12,puVar27,&local_218);
  }
  else {
    *puVar27 = 0x140000000;
    plVar12[1] = plVar12[1] + 8;
  }
  param_1[0x18] = (uint)uVar26;
  uVar26 = (longlong)(int)uVar7;
  if ((*param_1 >> 8 & 1) != 0) {
    local_220 = (ulonglong *)CONCAT44(3,(undefined4)local_220);
    plVar12 = *(longlong **)(param_1 + 0x16);
    local_218 = local_220;
    plVar28 = (longlong *)plVar12[1];
    lVar10 = *plVar12;
    if (plVar28 == (longlong *)plVar12[2]) {
      FUN_1800d7d00(plVar12,plVar28,&local_218);
    }
    else {
      *plVar28 = (longlong)local_220;
      plVar12[1] = plVar12[1] + 8;
    }
    iVar22 = (int)((longlong)plVar28 - lVar10 >> 3);
    local_168 = CONCAT44(local_168._4_4_,iVar22);
    uVar26 = (ulonglong)param_1[0x18];
    lVar10 = **(longlong **)(param_1 + 0x16);
    if ((ulonglong)((*(longlong **)(param_1 + 0x16))[1] - lVar10 >> 3) <= uVar26) {
                    /* WARNING: Subroutine does not return */
      FUN_1800d4ee8();
    }
    puVar18 = (uint *)(lVar10 + 4 + uVar26 * 8);
    *puVar18 = *puVar18 ^ (iVar22 * 8 ^ *(uint *)(lVar10 + 4 + uVar26 * 8)) & 0x7ffffff8;
    uVar26 = local_138;
  }
  local_130 = local_110;
  local_218 = local_128;
  if (0 < (int)uVar8) {
    local_248 = (longlong *)0x0;
    lStack_240 = 0;
    local_238 = 0;
    local_230 = 0;
    local_228 = 0;
    local_248 = (longlong *)FUN_18007c6f8(0x10);
    local_248[1] = 0;
    *local_248 = (longlong)&local_248;
    local_1e8 = (longlong **)0x0;
    local_1e0 = local_1e0 & 0xffff0000;
    local_1c8 = (longlong *)0x0;
    uStack_1c0 = 0;
    local_198 = 0;
    local_1b8 = 0;
    if (uVar26 != 0) {
      if (0x1555555555555555 < uVar26) {
                    /* WARNING: Subroutine does not return */
        FUN_1800d4ea8();
      }
      uVar26 = uVar26 * 0xc;
      if (uVar26 < 0x1000) {
        if (uVar26 == 0) {
          local_1c8 = (longlong *)0x0;
        }
        else {
          local_1c8 = (longlong *)FUN_18007c6f8(uVar26);
        }
      }
      else {
        if (uVar26 + 0x27 <= uVar26) {
                    /* WARNING: Subroutine does not return */
          FUN_1800cf160();
        }
        lVar10 = FUN_18007c6f8(uVar26 + 0x27);
        if (lVar10 == 0) {
          _o__invalid_parameter_noinfo_noreturn();
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
        local_1c8 = (longlong *)(lVar10 + 0x27U & 0xffffffffffffffe0);
        local_1c8[-1] = lVar10;
      }
      local_198 = (longlong)local_1c8 + uVar26;
      *local_1c8 = (longlong)local_1e8;
      *(uint *)(local_1c8 + 1) = local_1e0;
      plVar12 = local_1c8;
      puVar23 = (undefined4 *)((longlong)local_1c8 + 0xc);
      for (uVar26 = uVar26 - 0xc >> 2; uVar26 != 0; uVar26 = uVar26 - 1) {
        *puVar23 = (int)*plVar12;
        plVar12 = (longlong *)((longlong)plVar12 + 4);
        puVar23 = puVar23 + 1;
      }
    }
    plVar12 = local_1c8;
    local_150 = (ulonglong *)0x0;
    puStack_148 = (undefined8 *)0x0;
    local_160 = (undefined8 *)0x0;
    local_140 = (undefined8 *)0x0;
    local_208 = local_1c8;
    uStack_1c0 = local_198;
    local_1b8 = local_198;
    if ((((int)local_228 + (int)local_230 & 3U) == 0) && (local_238 <= local_228 + 4U >> 2)) {
      FUN_1800da02c((longlong)&local_248);
    }
    local_230 = local_230 & local_238 * 4 - 1;
    uVar26 = local_228 + local_230;
    lVar10 = (local_238 - 1 & uVar26 >> 2) * 8;
    if (*(longlong *)(lStack_240 + lVar10) == 0) {
      uVar11 = FUN_18007c6f8(0x10);
      *(undefined8 *)(lVar10 + lStack_240) = uVar11;
    }
    *(undefined4 *)(*(longlong *)(lVar10 + lStack_240) + (ulonglong)((uint)uVar26 & 3) * 4) = 0;
    local_228 = local_228 + 1;
    local_254 = 1;
    local_250[0] = 0;
    local_1d0 = 0;
    local_220 = local_150;
    puVar27 = puStack_148;
    param_2 = param_2;
    while (local_228 != 0) {
      uVar26 = local_230 + local_228 + -1;
      uVar26 = (ulonglong)
               *(uint *)(*(longlong *)(lStack_240 + (uVar26 >> 2 & local_238 - 1) * 8) +
                        (ulonglong)((uint)uVar26 & 3) * 4);
      bVar17 = 0;
      local_258[0] = 0;
      (**(code **)*param_2)(param_2,local_258,1);
      puVar18 = local_158;
      *local_158 = *local_158 + 1;
      if ((local_258[0] & 0x40) == 0) {
        uVar20 = 0;
        uVar7 = 0;
      }
      else {
        uVar7 = local_258[0] & 0xf;
        bVar17 = local_258[0] >> 5 & 1;
        bVar19 = local_258[0] & 0x10;
        while (uVar20 = (ulonglong)uVar7, (char)local_258[0] < '\0') {
          (**(code **)*param_2)(param_2,local_258,1);
          *puVar18 = *puVar18 + 1;
          uVar7 = local_258[0] & 0x7f | uVar7 << 7;
        }
        uVar7 = (uint)(bVar19 != 0);
      }
      uVar8 = *(uint *)(local_130 + uVar20 * 4);
      bVar19 = *(byte *)((longlong)local_218 + uVar20);
      lVar10 = (longlong)puVar27 - (longlong)local_220;
      local_200 = 0;
      if (puVar27 == local_160) {
        FUN_1800d7d00((longlong *)&local_150,puVar27,&local_200);
        local_160 = local_140;
        local_220 = local_150;
      }
      else {
        *puVar27 = 0;
        puStack_148 = puVar27 + 1;
      }
      puVar27 = puStack_148;
      plVar28 = local_1a0;
      plVar12 = local_208;
      uVar9 = (uint)bVar19 << 0x1d | *(uint *)(puStack_148 + -1) & 0x1fffffff;
      uVar9 = ((uint)bVar19 << 0x18 ^ uVar9) & 0x18000000 ^ uVar9;
      *(uint *)(puStack_148 + -1) = (uVar8 ^ uVar9) & 0x7ffffff ^ uVar9;
      uVar9 = 0;
      if (uVar8 == 1) {
        uVar9 = 4;
      }
      *(uint *)((longlong)puStack_148 + -4) =
           *(uint *)((longlong)puStack_148 + -4) & 0xfffffff8 | (uint)bVar17 | uVar7 * 2 | uVar9;
      puVar18 = (uint *)((longlong)local_208 + uVar26 * 0xc);
      if (*(char *)((longlong)puVar18 + 9) == '\0') {
        *puVar18 = (uint)(lVar10 >> 3);
        *(undefined1 *)((longlong)puVar18 + 9) = 1;
      }
      local_200 = uVar26;
      uVar9 = (**(code **)(*local_1a0 + 8))(local_1a0);
      uVar7 = local_254;
      if ((uVar9 & 0x40) == 0) {
        uVar7 = FUN_180022470(plVar28,(int *)local_158);
        *(uint *)((longlong)puVar27 + -4) =
             *(uint *)((longlong)puVar27 + -4) ^
             (uVar7 * 8 ^ *(uint *)((longlong)puVar27 + -4)) & 0x7ffffff8;
        if ((bVar17 != 0) && (local_228 = local_228 + -1, local_228 == 0)) {
          local_230 = 0;
        }
        if (uVar7 == local_254) {
          if (uVar8 == 1) {
            *(undefined1 *)((longlong)plVar12 + (ulonglong)uVar7 * 0xc + 8) = 1;
          }
          local_254 = local_254 + 1;
        }
      }
      else {
        *(uint *)((longlong)puVar27 + -4) =
             *(uint *)((longlong)puVar27 + -4) ^
             (local_254 * 8 ^ *(uint *)((longlong)puVar27 + -4)) & 0x7ffffff8;
        if (uVar8 == 1) {
          *(undefined1 *)((longlong)plVar12 + (ulonglong)local_254 * 0xc + 8) = 1;
        }
        if ((bVar17 != 0) && (local_228 = local_228 + -1, local_228 == 0)) {
          local_230 = 0;
        }
        local_254 = local_254 + 1;
        if ((((int)local_228 + (int)local_230 & 3U) == 0) && (local_238 <= local_228 + 4U >> 2)) {
          FUN_1800da02c((longlong)&local_248);
        }
        local_230 = local_230 & local_238 * 4 - 1;
        uVar26 = local_228 + local_230;
        lVar10 = (local_238 - 1 & uVar26 >> 2) * 8;
        if (*(longlong *)(lStack_240 + lVar10) == 0) {
          uVar11 = FUN_18007c6f8(0x10);
          *(undefined8 *)(lStack_240 + lVar10) = uVar11;
        }
        *(uint *)(*(longlong *)(lStack_240 + lVar10) + (ulonglong)((uint)uVar26 & 3) * 4) = uVar7;
        local_228 = local_228 + 1;
        uVar26 = local_200;
        plVar12 = local_208;
      }
      param_1 = local_1a8;
      puVar24 = local_220;
      param_2 = local_1a0;
      if (bVar17 != 0) {
        plVar28 = (longlong *)((longlong)puVar27 - (longlong)local_220 >> 3);
        uVar7 = (uint)plVar28;
        local_188 = plVar28;
        if ((char)puVar18[2] == '\0') {
          *(int *)((longlong)plVar12 + uVar26 * 0xc + 4) =
               (int)((*(longlong **)(local_1a8 + 0x16))[1] - **(longlong **)(local_1a8 + 0x16) >> 3)
          ;
          uVar8 = *(uint *)((longlong)plVar12 + uVar26 * 0xc);
          if (uVar8 < uVar7) {
            puVar24 = local_220 + uVar8;
            uVar20 = (ulonglong)(uVar7 - uVar8);
            do {
              local_210 = *puVar24;
              uVar7 = (uint)(local_210 >> 0x20);
              if (((uint)local_210 & 0x7ffffff) == local_1d8) {
                local_250[0] = uVar7 >> 3 & 0xfffffff;
              }
              else if (((uint)local_210 & 0x7ffffff) == local_1d4) {
                local_1d0 = uVar7 >> 3 & 0xfffffff;
              }
              plVar28 = *(longlong **)(param_1 + 0x16);
              puVar4 = (ulonglong *)plVar28[1];
              if (puVar4 == (ulonglong *)plVar28[2]) {
                FUN_1800d7d00(plVar28,puVar4,&local_210);
              }
              else {
                *puVar4 = local_210;
                plVar28[1] = plVar28[1] + 8;
              }
              puVar24 = puVar24 + 1;
              uVar20 = uVar20 - 1;
              uVar26 = local_200;
              plVar28 = local_188;
            } while (uVar20 != 0);
          }
        }
        else {
          local_1f8 = (longlong *)0x0;
          local_1f0 = 0;
          plVar12 = (longlong *)FUN_18007c6f8(0x28);
          param_1 = local_1a8;
          *plVar12 = (longlong)plVar12;
          plVar12[1] = (longlong)plVar12;
          plVar12[2] = (longlong)plVar12;
          *(undefined2 *)(plVar12 + 3) = 0x101;
          for (uVar8 = *puVar18; local_1f8 = plVar12, uVar8 < uVar7; uVar8 = uVar8 + 1) {
            uVar26 = puVar24[uVar8];
            lVar10 = *(longlong *)(param_1 + 0x14);
            uVar20 = (ulonglong)((uint)uVar26 & 0x7ffffff);
            if ((ulonglong)(*(longlong *)(lVar10 + 0x118) - *(longlong *)(lVar10 + 0x110) >> 2) <=
                uVar20) {
LAB_18006ad18:
                    /* WARNING: Subroutine does not return */
              FUN_1800d4ee8();
            }
            if ((ulonglong)(*(longlong *)(lVar10 + 0x100) - *(longlong *)(lVar10 + 0xf8) >> 2) <=
                uVar20) goto LAB_18006ad18;
            uVar25 = (uint)(uVar26 >> 0x23) & 0xfffffff;
            uVar9 = uVar25 | 0x80000000;
            if (*(int *)(*(longlong *)(lVar10 + 0x110) + uVar20 * 4) == 0x12) {
              uVar9 = uVar25;
            }
            uVar25 = uVar9 | 0x40000000;
            if ((uVar26 >> 0x21 & 1) == 0) {
              uVar25 = uVar9;
            }
            uVar9 = *(uint *)(*(longlong *)(lVar10 + 0xf8) + uVar20 * 4) >> 4;
            plVar13 = (longlong *)plVar12[1];
            uStack_180 = 0;
            cVar2 = *(char *)((longlong)plVar13 + 0x19);
            local_188 = plVar13;
            plVar14 = plVar12;
            while (plVar6 = plVar13, cVar2 == '\0') {
              bVar30 = uVar9 <= *(uint *)((longlong)plVar6 + 0x1c);
              if (bVar30) {
                plVar13 = (longlong *)*plVar6;
                plVar14 = plVar6;
              }
              else {
                plVar13 = (longlong *)plVar6[2];
              }
              uStack_180 = (ulonglong)bVar30;
              cVar2 = *(char *)((longlong)plVar13 + 0x19);
              local_188 = plVar6;
            }
            if ((*(char *)((longlong)plVar14 + 0x19) != '\0') ||
               (uVar9 < *(uint *)((longlong)plVar14 + 0x1c))) {
              if (local_1f0 == 0x666666666666666) {
                    /* WARNING: Subroutine does not return */
                FUN_1800d8d5c();
              }
              local_f8 = &local_1f8;
              local_f0 = 0;
              plVar13 = (longlong *)FUN_18007c6f8(0x28);
              *(uint *)((longlong)plVar13 + 0x1c) = uVar9;
              *(undefined4 *)(plVar13 + 4) = 0;
              *plVar13 = (longlong)plVar12;
              plVar13[1] = (longlong)plVar12;
              plVar13[2] = (longlong)plVar12;
              *(undefined2 *)(plVar13 + 3) = 0;
              local_f0 = 0;
              plVar14 = FUN_1800d8b80((longlong *)&local_1f8,&local_188,plVar13);
            }
            *(uint *)(plVar14 + 4) = uVar25;
            plVar12 = local_1f8;
            puVar24 = local_220;
          }
          lVar10 = *(longlong *)(param_1 + 0x16);
          plVar13 = (longlong *)*plVar12;
          iVar22 = *(int *)((longlong)plVar13 + 0x1c);
          uVar26 = (ulonglong)local_188 >> 0x20;
          local_188 = (longlong *)CONCAT44((int)uVar26,iVar22);
          if (*(char *)((longlong)plVar12 + 0x19) == '\0') {
            if (*(char *)((longlong)plVar13 + 0x19) == '\0') {
              cVar2 = *(char *)(plVar13[2] + 0x19);
              plVar12 = (longlong *)plVar13[2];
              while (cVar2 == '\0') {
                cVar2 = *(char *)(plVar12[2] + 0x19);
                plVar13 = plVar12;
                plVar12 = (longlong *)plVar12[2];
              }
            }
            else {
              cVar2 = *(char *)(plVar12[1] + 0x19);
              plVar14 = (longlong *)plVar12[1];
              while ((plVar13 = plVar14, cVar2 == '\0' && (plVar12 == (longlong *)*plVar13))) {
                cVar2 = *(char *)(plVar13[1] + 0x19);
                plVar14 = (longlong *)plVar13[1];
                plVar12 = plVar13;
              }
              if (*(char *)((longlong)plVar12 + 0x19) != '\0') {
                plVar13 = plVar12;
              }
            }
          }
          else {
            plVar13 = (longlong *)plVar12[2];
          }
          piVar3 = *(int **)(lVar10 + 0x20);
          lVar21 = *(longlong *)(lVar10 + 0x18);
          uVar7 = (*(int *)((longlong)plVar13 + 0x1c) - iVar22) + 1;
          uVar26 = local_210 >> 0x20;
          local_210 = CONCAT44((int)uVar26,uVar7);
          if (piVar3 == *(int **)(lVar10 + 0x28)) {
            FUN_1800d05fc((longlong *)(lVar10 + 0x18),piVar3,(undefined4 *)&local_188);
            iVar22 = (int)local_188;
          }
          else {
            *piVar3 = iVar22;
            *(longlong *)(lVar10 + 0x20) = *(longlong *)(lVar10 + 0x20) + 4;
          }
          puVar18 = *(uint **)(lVar10 + 0x20);
          if (puVar18 == *(uint **)(lVar10 + 0x28)) {
            FUN_1800d05fc((longlong *)(lVar10 + 0x18),puVar18,(undefined4 *)&local_210);
            uVar7 = (uint)local_210;
          }
          else {
            *puVar18 = uVar7;
            *(longlong *)(lVar10 + 0x20) = *(longlong *)(lVar10 + 0x20) + 4;
          }
          local_210 = local_210 & 0xffffffff00000000;
          FUN_1800d7f80((longlong *)(lVar10 + 0x18),(longlong *)&local_1e8,*(int **)(lVar10 + 0x20),
                        (ulonglong)uVar7,(int *)&local_210);
          plVar12 = (longlong *)*local_1f8;
          while (iVar29 = (int)((longlong)piVar3 - lVar21 >> 2), plVar12 != local_1f8) {
            *(int *)(*(longlong *)(lVar10 + 0x18) +
                    (ulonglong)(uint)((*(int *)((longlong)plVar12 + 0x1c) - iVar22) + 2 + iVar29) *
                    4) = (int)plVar12[4];
            plVar13 = (longlong *)plVar12[2];
            if (*(char *)((longlong)plVar13 + 0x19) == '\0') {
              cVar2 = *(char *)(*plVar13 + 0x19);
              plVar12 = plVar13;
              plVar13 = (longlong *)*plVar13;
              while (cVar2 == '\0') {
                cVar2 = *(char *)(*plVar13 + 0x19);
                plVar12 = plVar13;
                plVar13 = (longlong *)*plVar13;
              }
            }
            else {
              cVar2 = *(char *)(plVar12[1] + 0x19);
              plVar14 = (longlong *)plVar12[1];
              plVar13 = plVar12;
              while ((plVar12 = plVar14, cVar2 == '\0' && (plVar13 == (longlong *)plVar12[2]))) {
                cVar2 = *(char *)(plVar12[1] + 0x19);
                plVar14 = (longlong *)plVar12[1];
                plVar13 = plVar12;
              }
            }
          }
          *(int *)((longlong)local_208 + local_200 * 0xc + 4) = iVar29;
          cVar2 = *(char *)(local_1f8[1] + 0x19);
          plVar12 = (longlong *)local_1f8[1];
          while (cVar2 == '\0') {
            FUN_1800d9808(&local_1f8,&local_1f8,(longlong *)plVar12[2]);
            plVar13 = (longlong *)*plVar12;
            FUN_1800cda5c((longlong)plVar12,0x28);
            plVar12 = plVar13;
            cVar2 = *(char *)((longlong)plVar13 + 0x19);
          }
          FUN_1800cda5c((longlong)local_1f8,0x28);
          uVar26 = local_200;
          plVar12 = local_208;
        }
        uVar7 = *(uint *)((longlong)plVar12 + uVar26 * 0xc);
        puVar27 = puStack_148;
        param_2 = local_1a0;
        if (uVar7 < (uint)plVar28) {
          puStack_148 = puStack_148 + -(ulonglong)((uint)plVar28 - uVar7);
          puVar27 = puStack_148;
        }
      }
    }
    lVar10 = (*(longlong **)(param_1 + 0x16))[1];
    lVar21 = **(longlong **)(param_1 + 0x16);
    uVar7 = (uint)local_168;
    while (uVar7 = uVar7 + 1, uVar7 < (uint)(lVar10 - lVar21 >> 3)) {
      lVar16 = **(longlong **)(param_1 + 0x16);
      if ((ulonglong)((*(longlong **)(param_1 + 0x16))[1] - lVar16 >> 3) <= (ulonglong)uVar7)
      goto LAB_18006ad2a;
      lVar16 = lVar16 + (ulonglong)uVar7 * 8;
      uVar8 = *(uint *)(lVar16 + 4);
      iVar22 = *(int *)((longlong)plVar12 + (ulonglong)(uVar8 >> 3 & 0xfffffff) * 0xc + 4);
      if (iVar22 == 0) {
        uVar8 = uVar8 & 0x80000007;
      }
      else {
        uVar8 = (iVar22 * 8 ^ uVar8) & 0x7ffffff8 ^ uVar8;
      }
      *(uint *)(lVar16 + 4) = uVar8;
    }
    uVar7 = 0;
    if (0 < (longlong)local_138) {
      uVar26 = 0;
      do {
        if (*(char *)((longlong)plVar12 + uVar26 * 0xc + 8) != '\0') {
          lVar10 = *(longlong *)(param_1 + 0x16);
          iVar22 = *(int *)((longlong)plVar12 + uVar26 * 0xc + 4);
          uVar26 = (ulonglong)(iVar22 + 1);
          lVar21 = *(longlong *)(lVar10 + 0x20);
          lVar16 = *(longlong *)(lVar10 + 0x18);
          if ((ulonglong)(lVar21 - lVar16 >> 2) <= uVar26) {
LAB_18006ad24:
                    /* WARNING: Subroutine does not return */
            FUN_1800d4ee8();
          }
          uVar8 = *(uint *)(lVar16 + uVar26 * 4);
          uVar9 = 0;
          if (uVar8 != 0) {
            do {
              uVar26 = (ulonglong)(uVar9 + iVar22 + 2);
              if ((ulonglong)(lVar21 - lVar16 >> 2) <= uVar26) goto LAB_18006ad24;
              puVar18 = (uint *)(lVar16 + uVar26 * 4);
              uVar25 = *puVar18;
              if (uVar25 != 0) {
                *puVar18 = uVar25 & 0xc0000000 |
                           *(uint *)((longlong)plVar12 + (ulonglong)(uVar25 & 0x3fffffff) * 0xc + 4)
                ;
                lVar21 = *(longlong *)(lVar10 + 0x20);
                lVar16 = *(longlong *)(lVar10 + 0x18);
              }
              uVar9 = uVar9 + 1;
            } while (uVar9 < uVar8);
          }
        }
        uVar7 = uVar7 + 1;
        uVar26 = (ulonglong)uVar7;
      } while ((longlong)uVar26 < (longlong)local_138);
    }
    if (local_1d0 != 0) {
      uVar26 = (ulonglong)*(uint *)((longlong)plVar12 + (ulonglong)local_1d0 * 0xc + 4);
      lVar10 = **(longlong **)(param_1 + 0x16);
      if ((ulonglong)((*(longlong **)(param_1 + 0x16))[1] - lVar10 >> 3) <= uVar26)
      goto LAB_18006ad2a;
      uVar26 = (ulonglong)(*(uint *)(lVar10 + uVar26 * 8) & 0x7ffffff);
      lVar10 = *(longlong *)(*(longlong *)(param_1 + 0x14) + 0xf8);
      if ((ulonglong)(*(longlong *)(*(longlong *)(param_1 + 0x14) + 0x100) - lVar10 >> 2) <= uVar26)
      goto LAB_18006ad1e;
      if (param_1[0x1a] == 0) {
        param_1[0x1a] = *(uint *)(lVar10 + uVar26 * 4) >> 4;
      }
    }
    if (local_250[0] != 0) {
      uVar26 = (ulonglong)*(uint *)((longlong)plVar12 + (ulonglong)local_250[0] * 0xc + 4);
      lVar10 = **(longlong **)(param_1 + 0x16);
      if ((ulonglong)((*(longlong **)(param_1 + 0x16))[1] - lVar10 >> 3) <= uVar26)
      goto LAB_18006ad2a;
      uVar26 = (ulonglong)(*(uint *)(lVar10 + uVar26 * 8) & 0x7ffffff);
      lVar10 = *(longlong *)(*(longlong *)(param_1 + 0x14) + 0xf8);
      if ((ulonglong)(*(longlong *)(*(longlong *)(param_1 + 0x14) + 0x100) - lVar10 >> 2) <= uVar26)
      {
LAB_18006ad1e:
                    /* WARNING: Subroutine does not return */
        FUN_1800d4ee8();
      }
      if (param_1[0x1b] == 0) {
        param_1[0x1b] = *(uint *)(lVar10 + uVar26 * 4) >> 4;
      }
    }
    uVar26 = local_168 & 0xffffffff;
    lVar10 = **(longlong **)(param_1 + 0x16);
    if ((ulonglong)((*(longlong **)(param_1 + 0x16))[1] - lVar10 >> 3) <= uVar26) {
LAB_18006ad2a:
                    /* WARNING: Subroutine does not return */
      FUN_1800d4ee8();
    }
    puVar18 = (uint *)(lVar10 + 4 + uVar26 * 8);
    *puVar18 = *puVar18 ^
               (*(int *)((longlong)plVar12 + 4) * 8 ^ *(uint *)(lVar10 + 4 + uVar26 * 8)) &
               0x7ffffff8;
    if (local_220 != (ulonglong *)0x0) {
      FUN_1800cda5c((longlong)local_220,((longlong)local_160 - (longlong)local_220 >> 3) * 8);
    }
    FUN_1800cda5c((longlong)plVar12,((longlong)(local_198 - (longlong)plVar12) >> 2) << 2);
    while (local_228 != 0) {
      local_228 = local_228 + -1;
      if (local_228 == 0) {
        local_230 = 0;
      }
    }
    local_228 = 0;
    lVar10 = lStack_240;
    uVar26 = local_238;
    if (lStack_240 != 0) {
      while (uVar26 != 0) {
        uVar26 = uVar26 - 1;
        lVar21 = *(longlong *)(lVar10 + uVar26 * 8);
        if (lVar21 != 0) {
          FUN_1800cda5c(lVar21,0x10);
          lVar10 = lStack_240;
        }
      }
      FUN_1800cda5c(lVar10,local_238 * 8);
    }
    plVar12 = local_248;
    local_238 = 0;
    lStack_240 = 0;
    local_248 = (longlong *)0x0;
    FUN_1800cda5c((longlong)plVar12,0x10);
    param_3 = local_158;
  }
  lVar10 = local_130;
  param_1[0x19] =
       (int)((*(longlong **)(param_1 + 0x16))[1] - **(longlong **)(param_1 + 0x16) >> 3) -
       param_1[0x18];
  uVar7 = FUN_180022470(param_2,(int *)param_3);
  if (uVar7 != *param_3) {
    plVar12 = FUN_180072478(&local_1c8,"Network byte count mismatch");
    FUN_1800d2524(local_b8,plVar12);
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_b8,(ThrowInfo *)&DAT_1801b66d8);
  }
  if (*(longlong *)(param_1 + 6) == 0) goto LAB_18006ac84;
  lVar21 = *(longlong *)(param_1 + 0x14);
  uVar7 = param_1[0x18];
  puVar18 = param_1 + 2;
  local_1c8 = (longlong *)0x0;
  uStack_1c0 = 0;
  local_1b8 = 0;
  local_1b0 = 0;
  uVar26 = *(ulonglong *)(param_1 + 6);
  if (0xf < *(ulonglong *)(param_1 + 8)) {
    puVar18 = *(uint **)puVar18;
  }
  if (0x7fffffffffffffff < uVar26) {
                    /* WARNING: Subroutine does not return */
    FUN_1800cf188();
  }
  local_1b0 = 0xf;
  if (uVar26 < 0x10) {
    local_1c8 = *(longlong **)puVar18;
    uStack_1c0 = *(ulonglong *)(puVar18 + 2);
    local_1b8 = uVar26;
  }
  else {
    uVar20 = uVar26 | 0xf;
    if (uVar20 < 0x8000000000000000) {
      if (uVar20 < 0x16) {
        uVar20 = 0x16;
      }
      uVar1 = uVar20 + 1;
      if (0xfff < uVar1) {
        uVar15 = uVar20 + 0x28;
        if (uVar15 <= uVar1) {
                    /* WARNING: Subroutine does not return */
          FUN_1800cf160();
        }
        goto LAB_18006ab6c;
      }
      if (uVar1 == 0) {
        local_1c8 = (longlong *)0x0;
      }
      else {
        local_1c8 = (longlong *)FUN_18007c6f8(uVar1);
      }
    }
    else {
      uVar15 = 0x8000000000000027;
      uVar20 = 0x7fffffffffffffff;
LAB_18006ab6c:
      lVar16 = FUN_18007c6f8(uVar15);
      if (lVar16 == 0) {
        _o__invalid_parameter_noinfo_noreturn();
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      local_1c8 = (longlong *)(lVar16 + 0x27U & 0xffffffffffffffe0);
      local_1c8[-1] = lVar16;
    }
    local_1b8 = uVar26;
    local_1b0 = uVar20;
    memcpy(local_1c8,puVar18,uVar26 + 1);
  }
  local_1e8 = &local_1c8;
  uVar8 = FUN_1800dd018(lVar21 + 0x1d8,&local_1c8);
  uVar9 = (uint)(*(longlong *)(lVar21 + 0x238) - *(longlong *)(lVar21 + 0x230) >> 2);
  if (uVar9 <= uVar8) {
    uVar26 = (ulonglong)((uVar8 - uVar9) + 1);
    do {
      local_250[0] = 0;
      puVar23 = *(undefined4 **)(lVar21 + 0x238);
      if (puVar23 == *(undefined4 **)(lVar21 + 0x240)) {
        FUN_1800d05fc((longlong *)(lVar21 + 0x230),puVar23,local_250);
      }
      else {
        *puVar23 = 0;
        *(longlong *)(lVar21 + 0x238) = *(longlong *)(lVar21 + 0x238) + 4;
      }
      uVar26 = uVar26 - 1;
    } while (uVar26 != 0);
  }
  if ((ulonglong)(*(longlong *)(lVar21 + 0x238) - *(longlong *)(lVar21 + 0x230) >> 2) <=
      (ulonglong)uVar8) {
                    /* WARNING: Subroutine does not return */
    FUN_1800d4ee8();
  }
  *(uint *)(*(longlong *)(lVar21 + 0x230) + (ulonglong)uVar8 * 4) = uVar7;
  FUN_1800cfb74((longlong *)&local_1c8);
LAB_18006ac84:
  if (local_218 != (ulonglong *)0x0) {
    FUN_1800cda5c((longlong)local_218,local_118 - (longlong)local_218);
  }
  if (lVar10 != 0) {
    FUN_1800cda5c(lVar10,(local_100 - lVar10 >> 2) * 4);
  }
  FUN_180074534((longlong *)local_e8);
  return;
}


