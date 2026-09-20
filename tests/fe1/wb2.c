// FUN_1800cbe0c @ 1800cbe0c

uint FUN_1800cbe0c(longlong param_1,undefined2 param_2,uint *param_3,uint param_4)

{
  uint uVar1;
  longlong lVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  uint uVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  void *pvVar13;
  longlong lVar14;
  void *pvVar15;
  ulonglong uVar16;
  ulonglong uVar17;
  void *pvVar18;
  longlong lVar19;
  uint *puVar20;
  longlong lVar21;
  uint *puVar22;
  uint *puVar23;
  uint *puVar24;
  uint *local_40;
  
  if (*(int *)(param_1 + 0x18) != 0) {
    return 0x80048002;
  }
  lVar2 = *(longlong *)(param_1 + 0x68);
  puVar23 = param_3 + 1;
  lVar19 = *(longlong *)(param_1 + 0x60);
  puVar22 = (uint *)((ulonglong)param_4 + (longlong)param_3);
  *(undefined2 *)(param_1 + 0x1c) = param_2;
  if (puVar23 < puVar22) {
    uVar9 = *param_3;
    uVar17 = (ulonglong)uVar9;
    *(uint *)(param_1 + 0x20) = uVar9;
    lVar10 = DAT_180189560;
    lVar14 = lVar19 - DAT_180189558;
    if (lVar14 == 0) {
      lVar14 = lVar2 - DAT_180189560;
    }
    local_40 = puVar22;
    if (lVar14 == 0) {
LAB_1800cbf27:
      puVar20 = (uint *)((ulonglong)(((~uVar9 & 1) + uVar9) * 2 + 2) + (longlong)puVar23);
      lVar14 = DAT_180189548;
      lVar21 = DAT_180189550;
      param_3 = puVar23;
      if (puVar20 < puVar22) {
        uVar16 = 4;
        uVar12 = FUN_180009930(4,uVar17);
        if ((int)uVar12 != 0) {
          auVar3._8_8_ = 0;
          auVar3._0_8_ = uVar16 & 0xffffffff;
          auVar6._8_8_ = 0;
          auVar6._0_8_ = uVar17;
          pvVar18 = SUB168(auVar3 * auVar6,0);
          if (SUB168(auVar3 * auVar6,8) != 0) {
            pvVar18 = (void *)(uVar16 - 5);
          }
          pvVar15 = pvVar18;
          pvVar13 = (void *)thunk_FUN_18007ca58((longlong)pvVar18);
          if (pvVar13 == (void *)0x0) {
            pvVar13 = (void *)0x0;
          }
          else {
            pvVar15 = pvVar13;
            memset(pvVar13,0,(size_t)pvVar18);
          }
          lVar10 = DAT_180189560;
          lVar14 = DAT_180189548;
          lVar21 = DAT_180189550;
          if (pvVar13 != (void *)0x0) {
            FUN_1800cbdec(pvVar15,(longlong)pvVar13,(longlong)puVar23,
                          (ulonglong)*(uint *)(param_1 + 0x20));
            *(void **)(param_1 + 0x28) = pvVar13;
            goto LAB_1800cbfee;
          }
        }
        puVar22 = local_40;
        uVar9 = 0x8007000e;
      }
      else {
        uVar9 = 0x80048018;
      }
    }
    else {
      lVar14 = lVar19 - DAT_180189548;
      if (lVar14 == 0) {
        lVar14 = lVar2 - DAT_180189550;
      }
      if (lVar14 == 0) goto LAB_1800cbf27;
      lVar10 = lVar19 - DAT_180189278;
      if (lVar10 == 0) {
        lVar10 = lVar2 - DAT_180189280;
      }
      if (lVar10 == 0) {
LAB_1800cbf02:
        puVar20 = (uint *)((ulonglong)(uVar9 * 4) + (longlong)puVar23);
        if (puVar20 < puVar22) {
          *(uint **)(param_1 + 0x28) = puVar23;
          goto LAB_1800cbfee;
        }
      }
      else {
        lVar10 = lVar19 - DAT_180189568;
        if (lVar10 == 0) {
          lVar10 = lVar2 - DAT_180189570;
        }
        puVar20 = puVar23;
        if (lVar10 == 0) goto LAB_1800cbf02;
LAB_1800cbfee:
        puVar22 = local_40;
        puVar24 = puVar20 + 1;
        puVar23 = puVar20;
        if (puVar24 < local_40) {
          uVar9 = *puVar20;
          uVar17 = (ulonglong)uVar9;
          *(uint *)(param_1 + 0x30) = uVar9;
          lVar10 = DAT_180189560;
          lVar14 = lVar19 - DAT_180189558;
          if (lVar14 == 0) {
            lVar14 = lVar2 - DAT_180189560;
          }
          if (lVar14 == 0) {
LAB_1800cc0b0:
            puVar20 = (uint *)((ulonglong)(((~uVar9 & 1) + uVar9) * 2 + 2) + (longlong)puVar24);
            if (local_40 <= puVar20) {
LAB_1800cc0c9:
              lVar10 = DAT_180189560;
              lVar14 = DAT_180189548;
              lVar21 = DAT_180189550;
              param_3 = puVar24;
              uVar9 = 0x80048018;
              goto LAB_1800cc381;
            }
            uVar16 = 4;
            lVar14 = DAT_180189548;
            lVar21 = DAT_180189550;
            uVar12 = FUN_180009930(4,uVar17);
            if ((int)uVar12 != 0) {
              auVar4._8_8_ = 0;
              auVar4._0_8_ = uVar16 & 0xffffffff;
              auVar7._8_8_ = 0;
              auVar7._0_8_ = uVar17;
              pvVar18 = SUB168(auVar4 * auVar7,0);
              if (SUB168(auVar4 * auVar7,8) != 0) {
                pvVar18 = (void *)(uVar16 - 5);
              }
              pvVar15 = pvVar18;
              pvVar13 = (void *)thunk_FUN_18007ca58((longlong)pvVar18);
              if (pvVar13 == (void *)0x0) {
                pvVar13 = (void *)0x0;
              }
              else {
                pvVar15 = pvVar13;
                memset(pvVar13,0,(size_t)pvVar18);
              }
              lVar10 = DAT_180189560;
              lVar14 = DAT_180189548;
              lVar21 = DAT_180189550;
              if (pvVar13 != (void *)0x0) {
                FUN_1800cbdec(pvVar15,(longlong)pvVar13,(longlong)puVar24,
                              (ulonglong)*(uint *)(param_1 + 0x30));
                *(void **)(param_1 + 0x38) = pvVar13;
                goto LAB_1800cc173;
              }
            }
          }
          else {
            lVar14 = lVar19 - DAT_180189548;
            if (lVar14 == 0) {
              lVar14 = lVar2 - DAT_180189550;
            }
            if (lVar14 == 0) goto LAB_1800cc0b0;
            lVar10 = lVar19 - DAT_180189278;
            if (lVar10 == 0) {
              lVar10 = lVar2 - DAT_180189280;
            }
            if (lVar10 == 0) {
LAB_1800cc091:
              puVar20 = (uint *)((ulonglong)(uVar9 * 4) + (longlong)puVar24);
              puVar23 = puVar24;
              if (local_40 <= puVar20) goto LAB_1800cbf11;
              *(uint **)(param_1 + 0x38) = puVar24;
            }
            else {
              lVar10 = lVar19 - DAT_180189568;
              if (lVar10 == 0) {
                lVar10 = lVar2 - DAT_180189570;
              }
              puVar20 = puVar24;
              if (lVar10 == 0) goto LAB_1800cc091;
            }
LAB_1800cc173:
            puVar24 = puVar20 + 1;
            puVar23 = puVar20;
            if (puVar22 <= puVar24) goto LAB_1800cbf11;
            uVar1 = *puVar20;
            uVar17 = (ulonglong)uVar1;
            *(uint *)(param_1 + 0x40) = uVar1;
            lVar10 = DAT_180189560;
            lVar11 = lVar19 - DAT_180189558;
            if (lVar11 == 0) {
              lVar11 = lVar2 - DAT_180189560;
            }
            lVar14 = DAT_180189548;
            lVar21 = DAT_180189550;
            uVar9 = 0;
            if (lVar11 != 0) {
              lVar11 = lVar19 - DAT_180189548;
              if (lVar11 == 0) {
                lVar11 = lVar2 - DAT_180189550;
              }
              if (lVar11 != 0) {
                lVar11 = lVar19 - DAT_180189278;
                if (lVar11 == 0) {
                  lVar11 = lVar2 - DAT_180189280;
                }
                if (lVar11 != 0) {
                  lVar11 = lVar19 - DAT_180189568;
                  if (lVar11 == 0) {
                    lVar11 = lVar2 - DAT_180189570;
                  }
                  param_3 = puVar24;
                  if (lVar11 != 0) goto LAB_1800cc381;
                }
                param_3 = (uint *)((ulonglong)(uVar1 * 4) + (longlong)puVar24);
                if (param_3 < puVar22) {
                  *(uint **)(param_1 + 0x48) = puVar24;
                  lVar10 = DAT_180189560;
                  lVar14 = DAT_180189548;
                  lVar21 = DAT_180189550;
                  uVar9 = 0;
                }
                else {
                  param_3 = puVar24;
                  uVar9 = 0x80048018;
                }
                goto LAB_1800cc381;
              }
            }
            param_3 = (uint *)((ulonglong)(((~uVar1 & 1) + uVar1) * 2 + 2) + (longlong)puVar24);
            if (puVar22 <= param_3) goto LAB_1800cc0c9;
            uVar16 = 4;
            uVar12 = FUN_180009930(4,uVar17);
            if ((int)uVar12 != 0) {
              auVar5._8_8_ = 0;
              auVar5._0_8_ = uVar16 & 0xffffffff;
              auVar8._8_8_ = 0;
              auVar8._0_8_ = uVar17;
              pvVar18 = SUB168(auVar5 * auVar8,0);
              if (SUB168(auVar5 * auVar8,8) != 0) {
                pvVar18 = (void *)(uVar16 - 5);
              }
              pvVar15 = pvVar18;
              pvVar13 = (void *)thunk_FUN_18007ca58((longlong)pvVar18);
              if (pvVar13 == (void *)0x0) {
                pvVar13 = (void *)0x0;
              }
              else {
                pvVar15 = pvVar13;
                memset(pvVar13,0,(size_t)pvVar18);
              }
              lVar10 = DAT_180189560;
              lVar14 = DAT_180189548;
              lVar21 = DAT_180189550;
              if (pvVar13 != (void *)0x0) {
                FUN_1800cbdec(pvVar15,(longlong)pvVar13,(longlong)puVar24,
                              (ulonglong)*(uint *)(param_1 + 0x40));
                *(void **)(param_1 + 0x48) = pvVar13;
                lVar10 = DAT_180189560;
                lVar14 = DAT_180189548;
                lVar21 = DAT_180189550;
                goto LAB_1800cc381;
              }
            }
          }
          param_3 = puVar24;
          uVar9 = 0x8007000e;
          goto LAB_1800cc381;
        }
      }
LAB_1800cbf11:
      lVar10 = DAT_180189560;
      lVar14 = DAT_180189548;
      lVar21 = DAT_180189550;
      param_3 = puVar23;
      uVar9 = 0x80048018;
    }
  }
  else {
    lVar10 = DAT_180189560;
    lVar14 = DAT_180189548;
    lVar21 = DAT_180189550;
    uVar9 = 0x80048018;
  }
LAB_1800cc381:
  lVar14 = lVar19 - lVar14;
  if (lVar14 == 0) {
    lVar14 = lVar2 - lVar21;
  }
  if (lVar14 != 0) {
    lVar14 = lVar19 - DAT_180189568;
    if (lVar14 == 0) {
      lVar14 = lVar2 - DAT_180189570;
    }
    if (lVar14 != 0) {
      lVar14 = lVar19 - DAT_180189278;
      if (lVar14 == 0) {
        lVar14 = lVar2 - DAT_180189280;
      }
      if (lVar14 != 0) {
        lVar19 = lVar19 - DAT_180189558;
        if (lVar19 == 0) {
          lVar19 = lVar2 - lVar10;
        }
        if (lVar19 != 0) {
          return 0x80048018;
        }
      }
      if ((int)uVar9 < 0) {
        return uVar9;
      }
      local_40 = (uint *)0x0;
      uVar9 = FUN_18003cbe0(&local_40,(ushort *)param_3,(int)puVar22 - (int)param_3);
      if ((int)uVar9 < 0) {
        return uVar9;
      }
      *(uint **)(param_1 + 0x50) = local_40;
      goto LAB_1800cc496;
    }
  }
  if ((int)uVar9 < 0) {
    return uVar9;
  }
  puVar23 = param_3 + 1;
  if (puVar23 < puVar22) {
    uVar9 = *param_3;
    if ((uVar9 & 3) != 0) {
      uVar9 = (uVar9 - (uVar9 & 3)) + 4;
    }
    puVar20 = (uint *)((ulonglong)uVar9 + (longlong)puVar23);
    if (puVar20 < puVar22) {
      local_40 = (uint *)0x0;
      uVar9 = FUN_18003cbe0(&local_40,(ushort *)puVar23,*param_3);
      if ((int)uVar9 < 0) {
        return uVar9;
      }
      puVar23 = puVar20 + 1;
      *(uint **)(param_1 + 0x50) = local_40;
      if ((puVar23 < puVar22) && ((uint *)((ulonglong)*puVar20 + (longlong)puVar23) <= puVar22)) {
        local_40 = (uint *)0x0;
        uVar9 = FUN_18003cbe0(&local_40,(ushort *)puVar23,*puVar20);
        if ((int)uVar9 < 0) {
          return uVar9;
        }
        *(uint **)(param_1 + 0x58) = local_40;
LAB_1800cc496:
        *(undefined4 *)(param_1 + 0x18) = 1;
        return uVar9;
      }
    }
  }
  return 0x80048018;
}


// FUN_1800c4780 @ 1800c4780

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_1800c4780(longlong param_1,longlong *param_2,undefined2 param_3)

{
  uint uVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong *plVar4;
  ulonglong uVar5;
  wchar_t *pwVar6;
  undefined1 auStack_2a8 [32];
  uint *local_288;
  uint local_278;
  int local_274;
  uint *local_270 [2];
  undefined8 local_260;
  undefined8 local_258;
  undefined8 uStack_250;
  wchar_t local_248 [264];
  ulonglong local_38;
  
  local_38 = DAT_1801c0240 ^ (ulonglong)auStack_2a8;
  if ((param_2 == (longlong *)0x0) || (lVar2 = (**(code **)(*param_2 + 0x10))(param_2), lVar2 == 0))
  {
    return 0x80070057;
  }
  *(undefined2 *)(param_1 + 0x10) = param_3;
  if (*(longlong *)(param_1 + 8) != 0) {
    return 0;
  }
  local_274 = 0;
  local_258 = DAT_180189278;
  uStack_250 = DAT_180189280;
  memset(local_248,0,0x208);
  uVar1 = (**(code **)(*param_2 + 0x20))(param_2,&DAT_180186240,&local_258,&local_274);
  if (-1 < (int)uVar1) {
    if (local_274 == 0) {
      uVar3 = (**(code **)(*param_2 + 0x10))(param_2);
      pwVar6 = L"WORDBREAKER_%s";
    }
    else {
      uVar3 = (**(code **)(*param_2 + 0x18))();
      pwVar6 = L"UPDATE_WORDBREAKER_%s";
    }
    uVar1 = FUN_1800179d4(local_248,0x104,pwVar6,uVar3);
  }
  uVar5 = (ulonglong)uVar1;
  FUN_18005bd20(&local_260,(LPCRITICAL_SECTION)&DAT_1801c0dc0);
  if ((-1 < (int)uVar1) && (*(longlong *)(param_1 + 8) == 0)) {
    plVar4 = FUN_1800c465c((ushort *)local_248,(undefined8 *)(param_1 + 8));
    uVar5 = (ulonglong)plVar4 & 0xffffffff;
    if ((-1 < (int)plVar4) && (*(int *)(*(longlong *)(param_1 + 8) + 0x18) == 0)) {
      local_270[0] = (uint *)0x0;
      local_278 = 0;
      local_288 = &local_278;
      uVar1 = (**(code **)(*param_2 + 8))(param_2,&DAT_180186240,&local_258,local_270);
      uVar5 = (ulonglong)uVar1;
      if (uVar1 == 0x80048018) {
        local_258 = CONCAT44(DAT_180189558._4_4_,(undefined4)DAT_180189558);
        uStack_250 = CONCAT44(DAT_180189560._4_4_,(undefined4)DAT_180189560);
        local_288 = &local_278;
        uVar1 = (**(code **)(*param_2 + 8))(param_2,&DAT_180186240,&local_258,local_270);
        uVar5 = (ulonglong)uVar1;
        if (uVar1 == 0x80048018) {
          local_258 = CONCAT44(DAT_180189548._4_4_,(undefined4)DAT_180189548);
          uStack_250 = CONCAT44(DAT_180189550._4_4_,(undefined4)DAT_180189550);
          local_288 = &local_278;
          uVar1 = (**(code **)(*param_2 + 8))(param_2,&DAT_180186240,&local_258,local_270);
          uVar5 = (ulonglong)uVar1;
          if (uVar1 == 0x80048018) {
            local_258 = CONCAT44(DAT_180189568._4_4_,(undefined4)DAT_180189568);
            uStack_250 = CONCAT44(DAT_180189570._4_4_,(undefined4)DAT_180189570);
            local_288 = &local_278;
            uVar1 = (**(code **)(*param_2 + 8))(param_2,&DAT_180186240,&local_258,local_270);
            uVar5 = (ulonglong)uVar1;
          }
        }
      }
      lVar2 = *(longlong *)(param_1 + 8);
      if (lVar2 != 0) {
        *(undefined8 *)(lVar2 + 0x60) = local_258;
        *(undefined8 *)(lVar2 + 0x68) = uStack_250;
      }
      if ((int)uVar5 < 0) {
        if ((int)uVar5 == -0x7ffb7fe6) {
          if (*(int *)(lVar2 + 0x18) == 0) {
            *(undefined2 *)(lVar2 + 0x1c) = param_3;
            *(undefined **)(lVar2 + 0x28) = &DAT_180189578;
            *(undefined4 *)(lVar2 + 0x20) = 1;
            *(undefined4 *)(lVar2 + 0x30) = 0;
            *(undefined8 *)(lVar2 + 0x38) = 0;
            *(undefined4 *)(lVar2 + 0x40) = 0;
            *(undefined8 *)(lVar2 + 0x48) = 0;
            *(undefined4 *)(lVar2 + 0x18) = 1;
            uVar5 = 0;
            goto LAB_1800c49f6;
          }
          uVar5 = 0x80048002;
        }
      }
      else {
        uVar1 = FUN_1800cbe0c(lVar2,param_3,local_270[0],local_278);
        uVar5 = (ulonglong)uVar1;
        if (-1 < (int)uVar1) goto LAB_1800c49f6;
      }
      FUN_18002d720(*(undefined8 **)(param_1 + 8));
      *(undefined8 *)(param_1 + 8) = 0;
    }
  }
LAB_1800c49f6:
  FUN_18007b110(&local_260);
  return uVar5;
}


// FUN_18002c550 @ 18002c550

undefined4 FUN_18002c550(longlong param_1,longlong param_2,longlong param_3,undefined8 *param_4)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined4 uVar3;
  undefined4 local_res10 [2];
  undefined8 *local_18;
  undefined4 *local_10;
  
  if ((param_2 == 0) || (param_3 == 0)) {
    uVar3 = 0xffffffff;
  }
  else {
    uVar3 = 0xffffffff;
    local_res10[0] = 0;
    local_10 = (undefined4 *)0x0;
    local_18 = (undefined8 *)0x0;
    if (param_4 != (undefined8 *)0x0) {
      *param_4 = 0;
    }
    uVar2 = FUN_18002c5f0(param_1,param_2,param_3,(uint)param_4,local_res10,(longlong *)&local_10,
                          (longlong *)&local_18);
    puVar1 = local_18;
    if ((int)uVar2 == 0) {
      *param_4 = *local_18;
      uVar3 = *local_10;
      _o_free();
      _o_free(puVar1);
    }
  }
  return uVar3;
}


// FUN_18004d024 @ 18004d024

uint FUN_18004d024(longlong param_1,ulonglong param_2,ulonglong param_3,undefined4 *param_4)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 1;
  uVar3 = 0;
  if ((param_1 != 0) && (uVar3 = 0, param_3 < param_2)) {
    if (((param_3 + 1 < param_2) &&
        ((sVar1 = *(short *)(param_1 + param_3 * 2), (ushort)(sVar1 + 0x2800U) < 0x400 &&
         (sVar2 = *(short *)(param_1 + 2 + param_3 * 2), (ushort)(sVar2 + 0x2400U) < 0x400)))) ||
       ((param_3 != 0 &&
        ((sVar1 = *(short *)(param_1 + -2 + param_3 * 2), (ushort)(sVar1 + 0x2800U) < 0x400 &&
         (sVar2 = *(short *)(param_1 + param_3 * 2), (ushort)(sVar2 + 0x2400U) < 0x400)))))) {
      uVar4 = 2;
      uVar3 = CONCAT22(sVar1,sVar2);
    }
    else {
      uVar3 = (uint)*(ushort *)(param_1 + param_3 * 2);
      uVar4 = 1;
    }
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = uVar4;
  }
  return uVar3;
}


// FUN_180050e54 @ 180050e54

undefined8 FUN_180050e54(longlong param_1,undefined4 param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  undefined4 local_res10 [2];
  
  local_res10[0] = param_2;
  lVar1 = _o_bsearch(local_res10,*(undefined8 *)(*(longlong *)(param_1 + 8) + 0x28),
                     *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x20),4,FUN_180049ff0);
  uVar2 = 0;
  if ((lVar1 != 0) ||
     (local_res10[0] = param_2,
     lVar1 = _o_bsearch(local_res10,*(undefined8 *)(*(longlong *)(param_1 + 8) + 0x38),
                        *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x30),4,FUN_180049ff0),
     lVar1 != 0)) {
    uVar2 = 1;
  }
  return uVar2;
}


// FUN_1800442c8 @ 1800442c8

undefined8 FUN_1800442c8(short param_1)

{
  undefined8 uVar1;
  
  uVar1 = 1;
  if ((((param_1 != 0x2032) && (param_1 != 0x2018 && param_1 != 0x2019)) && (param_1 != 0x27)) &&
     (param_1 != -0xf9)) {
    uVar1 = 0;
  }
  return uVar1;
}


