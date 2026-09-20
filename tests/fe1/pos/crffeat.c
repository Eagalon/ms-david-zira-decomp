// FUN_180038d5c @ 180038d5c

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_180038d5c(longlong *param_1,undefined8 *param_2,longlong *param_3,longlong *param_4,
                       ulonglong param_5,uint param_6)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  short *psVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  undefined **ppuVar9;
  code *pcVar10;
  longlong *plVar11;
  longlong lVar12;
  undefined1 auStackY_2f8 [32];
  longlong *local_2b8;
  longlong *local_2b0;
  ulonglong local_2a8;
  undefined **local_298;
  undefined2 *local_290;
  uint local_288;
  undefined2 local_280 [132];
  undefined **local_178;
  undefined2 *local_170;
  uint local_168;
  undefined2 local_160 [132];
  ulonglong local_58;
  
  local_58 = DAT_1801c0240 ^ (ulonglong)auStackY_2f8;
  local_2a8 = param_5;
  lVar1 = *(longlong *)(param_1[4] + param_5 * 8);
  local_288 = 0x80000000;
  local_290 = local_280;
  uVar6 = 0;
  local_280[0] = 0;
  ppuVar9 = CQuickStringW<128>::vftable;
  local_298 = CQuickStringW<128>::vftable;
  local_2b8 = param_3;
  local_2b0 = param_4;
  psVar5 = FUN_18001c490(lVar1 + 0x30);
  uVar8 = 0xffffffffffffffff;
  do {
    uVar8 = uVar8 + 1;
  } while (psVar5[uVar8] != (short)uVar6);
  if (uVar8 < 0x3fffffff) {
    uVar8 = FUN_1801441e8((longlong)&local_298,psVar5,uVar8,0x80);
    if (-1 < (int)uVar8) {
      uVar8 = FUN_18006822c((longlong)&local_298,&DAT_18018529c);
    }
    uVar8 = uVar8 & 0xffffffff;
    uVar6 = 0;
    ppuVar9 = CQuickStringW<128>::vftable;
    param_3 = local_2b8;
    param_4 = local_2b0;
  }
  else {
    uVar8 = 0x8007000e;
  }
  if ((uint)uVar6 < *(uint *)(lVar1 + 8)) {
    lVar12 = lVar1 + 0x50;
    plVar11 = (longlong *)(lVar1 + 0x10);
    uVar7 = uVar6;
    do {
      if ((int)uVar8 < 0) goto LAB_180038fc8;
      local_168 = 0x80000000;
      local_170 = local_160;
      local_160[0] = (undefined2)uVar6;
      lVar2 = *plVar11;
      local_178 = ppuVar9;
      if (lVar2 == 0) {
        pcVar10 = *(code **)(*param_1 + 0x10);
        psVar5 = FUN_18001c490(lVar12);
        uVar4 = (*pcVar10)(param_1,&local_178,*param_2,psVar5);
      }
      else if (*(int *)(lVar2 + 0x68) == 0x48) {
        uVar6 = FUN_18003901c(param_1,(longlong)&local_178,(longlong *)*param_2,lVar2,param_3,
                              param_4,param_6);
        uVar4 = (uint)uVar6;
      }
      else {
        psVar5 = FUN_1800776f0(param_1,(longlong)&local_178,(longlong *)*param_2,lVar2,param_3,
                               param_4);
        uVar4 = (uint)psVar5;
      }
      uVar8 = (ulonglong)uVar4;
      if (-1 < (int)uVar4) {
        uVar6 = FUN_18006822c((longlong)&local_298,local_170);
        uVar8 = uVar6 & 0xffffffff;
        if ((-1 < (int)uVar6) && (uVar7 < *(int *)(lVar1 + 8) - 1)) {
          uVar8 = FUN_18006822c((longlong)&local_298,&DAT_1801888a8);
          uVar8 = uVar8 & 0xffffffff;
        }
      }
      local_178 = CQuickStringTBase::vftable;
      if ((local_168 & 0x80000000) == 0) {
        _o_free(local_170);
      }
      uVar7 = uVar7 + 1;
      plVar11 = plVar11 + 1;
      lVar12 = lVar12 + 0x20;
      uVar6 = 0;
      ppuVar9 = CQuickStringW<128>::vftable;
      param_3 = local_2b8;
      param_4 = local_2b0;
      param_5 = local_2a8;
    } while (uVar7 < *(uint *)(lVar1 + 8));
  }
  if (-1 < (int)uVar8) {
    iVar3 = FUN_1800e4e8c(param_1[2],(longlong)local_290);
    local_2b8 = (longlong *)CONCAT44(local_2b8._4_4_,iVar3);
    if (param_5 < (ulonglong)param_2[2]) {
      *(int *)(param_2[1] + param_5 * 4) = iVar3;
    }
    else {
      uVar4 = FUN_1800e286c(param_2 + 1,(undefined4 *)&local_2b8);
      uVar8 = (ulonglong)uVar4;
    }
  }
LAB_180038fc8:
  local_298 = CQuickStringTBase::vftable;
  if ((local_288 & 0x80000000) == 0) {
    _o_free(local_290);
  }
  return uVar8;
}


