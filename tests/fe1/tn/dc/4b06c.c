// FUN_18004b06c @ 18004b06c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_18004b06c(longlong param_1,undefined8 *param_2,longlong *param_3,undefined8 *param_4)

{
  undefined2 uVar1;
  bool bVar2;
  longlong lVar3;
  uint uVar4;
  int iVar5;
  ulonglong uVar6;
  wchar_t *_Str;
  wchar_t *pwVar7;
  longlong lVar8;
  short *psVar9;
  undefined8 uVar10;
  longlong *plVar11;
  undefined8 *puVar12;
  ulonglong uVar13;
  wchar_t *_Str_00;
  ulonglong uVar14;
  code *pcVar15;
  longlong *plVar16;
  longlong *plVar17;
  wchar_t *pwVar18;
  undefined1 auStackY_108 [32];
  int local_b4;
  longlong *local_b0;
  longlong local_a8;
  wchar_t *local_a0;
  undefined8 *local_98;
  longlong local_90;
  undefined **local_88;
  undefined8 local_80;
  undefined8 uStack_78;
  undefined8 local_70;
  wchar_t local_68 [6];
  wchar_t awStack_5c [2];
  wchar_t awStack_58 [2];
  wchar_t awStack_54 [2];
  ulonglong local_50;
  
  local_50 = DAT_1801c0240 ^ (ulonglong)auStackY_108;
  local_a8 = 0;
  local_90 = param_1;
  uVar4 = (**(code **)(*param_3 + 0x118))(param_3,&local_a8);
  plVar17 = (longlong *)*param_4;
  uVar14 = (ulonglong)uVar4;
  if (-1 < (int)uVar4) {
    while (plVar17 != (longlong *)0x0) {
      _Str_00 = (wchar_t *)plVar17[2];
      plVar17 = (longlong *)*plVar17;
      if (_Str_00 == (wchar_t *)0x0) {
        return uVar14;
      }
      uVar13 = 0xffffffffffffffff;
      do {
        uVar13 = uVar13 + 1;
      } while (_Str_00[uVar13] != L'\0');
      uVar6 = 0xffffffff;
      if (uVar13 < 0x100000000) {
        uVar6 = uVar13 & 0xffffffff;
      }
      uVar14 = (ulonglong)(-(uint)(0xffffffff < uVar13) & 0x80070216);
      local_a0 = _Str_00 + uVar6;
      if (uVar13 < 0x100000000) {
        do {
          if (local_a0 <= _Str_00) break;
          local_98 = (undefined8 *)0x0;
          local_b4 = 0;
          bVar2 = false;
          local_68[4] = u__break__180181010[0];
          local_68[5] = u__break__180181010[1];
          awStack_5c[0] = u__break__180181010[2];
          awStack_5c[1] = u__break__180181010[3];
          awStack_58[0] = u__break__180181010[4];
          awStack_58[1] = u__break__180181010[5];
          awStack_54[0] = u__break__180181010[6];
          awStack_54[1] = u__break__180181010[7];
          uVar14 = 0;
          builtin_wcsncpy(local_68,L"ms]",4);
          _Str = wcsstr(_Str_00,local_68 + 4);
          pwVar18 = (wchar_t *)0x0;
          if ((_Str != (wchar_t *)0x0) && (pwVar7 = wcsstr(_Str,local_68), pwVar7 != (wchar_t *)0x0)
             ) {
            local_70 = 0;
            local_88 = CTTSString::vftable;
            lVar8 = (longlong)pwVar7 - (longlong)_Str >> 1;
            bVar2 = true;
            local_80 = 0;
            uStack_78 = 0;
            local_98 = (undefined8 *)(lVar8 + 3);
            psVar9 = FUN_180029d20((longlong)&local_88,(longlong)(_Str + 7),lVar8 - 7);
            uVar14 = (ulonglong)psVar9 & 0xffffffff;
            if (-1 < (int)psVar9) {
              psVar9 = FUN_18001c490((longlong)&local_88);
              local_b4 = _o__wtoi(psVar9);
            }
            FUN_18001d780(&local_88);
            pwVar18 = _Str;
          }
          lVar8 = local_a8;
          if ((int)uVar14 < 0) {
            return uVar14;
          }
          if (bVar2) {
            if (_Str_00 < pwVar18) {
              local_b0 = (longlong *)0x0;
              lVar8 = (longlong)pwVar18 - (longlong)_Str_00 >> 1;
              uVar4 = FUN_18006e874(lVar8,param_2,0,local_a8,_Str_00,(int)lVar8,(int)param_3[0x4e],
                                    *(undefined4 *)((longlong)param_3 + 0x274),
                                    *(undefined2 *)(local_90 + 0x10),&local_b0);
              plVar11 = local_b0;
              uVar14 = (ulonglong)uVar4;
              if (-1 < (int)uVar4) {
                uVar4 = (**(code **)(*local_b0 + 0x198))(local_b0,1);
                uVar14 = (ulonglong)uVar4;
                if (-1 < (int)uVar4) {
                  uVar10 = (**(code **)(*param_3 + 0xc0))(param_3);
                  uVar4 = (**(code **)(*plVar11 + 0xb8))(plVar11,uVar10);
                  uVar14 = (ulonglong)uVar4;
                  if (-1 < (int)uVar4) {
                    pcVar15 = *(code **)(*plVar11 + 0xd8);
                    uVar10 = (**(code **)(*param_3 + 0xe0))(param_3,&local_88);
                    uVar4 = (*pcVar15)(plVar11,uVar10);
                    uVar14 = (ulonglong)uVar4;
                    if (-1 < (int)uVar4) goto LAB_18004b2f3;
                  }
                }
              }
            }
            else {
LAB_18004b2f3:
              if ((param_2[2] != 0) &&
                 (plVar11 = *(longlong **)(param_2[1] + 0x10), plVar11 != (longlong *)0x0)) {
                iVar5 = (**(code **)(*plVar11 + 0x248))(plVar11);
                (**(code **)(*plVar11 + 0x240))(plVar11,local_b4 + iVar5);
                (**(code **)(*plVar11 + 0x1b8))(plVar11,0);
              }
            }
            _Str_00 = pwVar18 + (longlong)local_98;
          }
          else {
            uVar14 = 0;
            uVar1 = *(undefined2 *)(local_90 + 0x10);
            local_b0 = (longlong *)
                       CONCAT44(local_b0._4_4_,*(undefined4 *)((longlong)param_3 + 0x274));
            lVar3 = param_3[0x4e];
            local_98 = (undefined8 *)FUN_18007ca58(0x370);
            if ((local_98 == (undefined8 *)0x0) ||
               (plVar11 = FUN_18001ba9c(local_98), plVar11 == (longlong *)0x0)) {
              uVar14 = 0x8007000e;
              _Str_00 = local_a0;
            }
            else {
              plVar11[0x12] = lVar8;
              (**(code **)(*plVar11 + 0x30))(plVar11,uVar1);
              (**(code **)(*plVar11 + 0x208))(plVar11,(int)lVar3);
              (**(code **)(*plVar11 + 0x218))(plVar11,(ulonglong)local_b0 & 0xffffffff);
              (**(code **)(*plVar11 + 0x60))(plVar11,0);
              if (*(longlong *)(lVar8 + 0x48) == 0) {
                uVar4 = (**(code **)(*plVar11 + 0x70))(plVar11,_Str_00);
                uVar14 = (ulonglong)uVar4;
                if (-1 < (int)uVar4) goto LAB_18004b437;
LAB_18004b4b8:
                (**(code **)plVar11[1])(plVar11 + 1,1);
                _Str_00 = local_a0;
                plVar11 = (longlong *)0x0;
                if ((int)uVar14 < 0) goto LAB_18004b60a;
              }
              else {
LAB_18004b437:
                if (*(int *)(param_2 + 6) != 0) {
                  *(int *)(plVar11 + 0x5e) = *(int *)(param_2 + 6);
                  plVar16 = plVar11 + 0x5f;
                  plVar11[99] = param_2[0xb];
                  pcVar15 = *(code **)(*plVar16 + 0x20);
                  psVar9 = FUN_18001c490((longlong)(param_2 + 7));
                  uVar4 = (*pcVar15)(plVar16,psVar9);
                  uVar14 = (ulonglong)uVar4;
                  if ((int)uVar4 < 0) goto LAB_18004b4b8;
                  FUN_180019d20((longlong)(param_2 + 7));
                  *(undefined4 *)(param_2 + 6) = 0;
                  param_2[0xb] = 0;
                }
                puVar12 = FUN_180018e8c(param_2,(longlong)plVar11);
                if (puVar12 == (undefined8 *)0x0) {
                  uVar14 = 0x8007000e;
                  goto LAB_18004b4b8;
                }
                if ((int)uVar14 < 0) goto LAB_18004b4b8;
              }
              if ((int)param_3[0x5e] != 0) {
                *(int *)(plVar11 + 0x5e) = (int)param_3[0x5e];
                plVar16 = plVar11 + 0x5f;
                plVar11[99] = param_3[99];
                pcVar15 = *(code **)(*plVar16 + 0x20);
                psVar9 = FUN_18001c490((longlong)(param_3 + 0x5f));
                uVar4 = (*pcVar15)(plVar16,psVar9);
                uVar14 = (ulonglong)uVar4;
                _Str_00 = local_a0;
                if ((int)uVar4 < 0) goto LAB_18004b60a;
                FUN_180019d20((longlong)(param_3 + 0x5f));
                *(undefined4 *)(param_3 + 0x5e) = 0;
                param_3[99] = 0;
              }
              uVar4 = (**(code **)(*plVar11 + 0x198))(plVar11,1);
              uVar14 = (ulonglong)uVar4;
              _Str_00 = local_a0;
              if (-1 < (int)uVar4) {
                uVar10 = (**(code **)(*param_3 + 0xc0))(param_3);
                uVar4 = (**(code **)(*plVar11 + 0xb8))(plVar11,uVar10);
                uVar14 = (ulonglong)uVar4;
                _Str_00 = local_a0;
                if (-1 < (int)uVar4) {
                  pcVar15 = *(code **)(*plVar11 + 0xd8);
                  uVar10 = (**(code **)(*param_3 + 0xe0))(param_3,&local_88);
                  uVar4 = (*pcVar15)(plVar11,uVar10);
                  uVar14 = (ulonglong)uVar4;
                  _Str_00 = local_a0;
                  if ((-1 < (int)uVar4) && (plVar17 != (longlong *)0x0)) {
                    (**(code **)(*plVar11 + 0x1a8))(plVar11,2);
                    (**(code **)(*plVar11 + 0x1b8))(plVar11,1);
                    _Str_00 = local_a0;
                  }
                }
              }
            }
          }
LAB_18004b60a:
        } while (-1 < (int)uVar14);
      }
      if ((int)uVar14 < 0) {
        return uVar14;
      }
    }
  }
  return uVar14;
}


