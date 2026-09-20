// FUN_1800c4f10 @ 1800c4f10

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

wchar_t * FUN_1800c4f10(longlong param_1,longlong param_2,void *param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  ulonglong uVar4;
  longlong lVar5;
  short *psVar6;
  wchar_t *_Str1;
  wchar_t *pwVar7;
  code *pcVar8;
  longlong *plVar9;
  int local_res20 [2];
  undefined8 in_stack_ffffffffffffff58;
  undefined **local_98;
  undefined8 local_90;
  undefined8 uStack_88;
  undefined8 local_80;
  undefined **local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 uStack_60;
  undefined4 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined4 local_38;
  
  _Str1 = (wchar_t *)0x0;
  iVar3 = 0;
  if (param_4 == 0) {
    return (wchar_t *)0x0;
  }
  if ((*(longlong *)(param_1 + 0x4d0) == 0) || (*(longlong *)(param_1 + 0x4e0) == 0)) {
    local_78 = CTTSWordSink::vftable;
    local_70 = 0;
    local_68 = 0;
    uStack_60 = 0;
    local_58 = 0;
    local_50 = 0;
    local_48 = 0;
    uStack_40 = 0;
    local_38 = 0;
    uVar2 = (**(code **)(**(longlong **)(param_1 + 0x4b8) + 8))
                      (*(longlong **)(param_1 + 0x4b8),param_3,(ulonglong)param_4,&local_78,1);
    if (-1 < (int)uVar2) {
      uVar2 = FUN_180071b70(param_1,(longlong)&local_78);
    }
    FUN_1800727ac(&local_78);
    return (wchar_t *)(ulonglong)uVar2;
  }
  lVar5 = param_1;
  pwVar7 = _Str1;
  if (*(int *)(param_1 + 0x4ec) != 0) {
    uVar4 = FUN_1800c5db4(param_1,param_2,param_3,param_4);
    iVar1 = (int)uVar4;
    pwVar7 = (wchar_t *)(uVar4 & 0xffffffff);
    if (iVar1 == 0) {
      return pwVar7;
    }
    if (iVar1 == -0x7ffb7ffd) {
      pwVar7 = (wchar_t *)0x0;
    }
    else if (iVar1 < 0) {
      return pwVar7;
    }
  }
  local_98 = CTTSString::vftable;
  local_90 = 0;
  uStack_88 = 0;
  local_80 = 0;
  plVar9 = *(longlong **)(param_2 + 0x20);
  if (plVar9 != (longlong *)0x0) {
    uVar2 = FUN_1800c6aec(lVar5,*plVar9,plVar9[1],(longlong *)&local_98);
    pwVar7 = (wchar_t *)(ulonglong)uVar2;
  }
  local_res20[0] = 0;
  if (-1 < (int)pwVar7) {
    lVar5 = FUN_18001b0e0((longlong)&local_98);
    if ((char)lVar5 == '\0') {
      plVar9 = *(longlong **)(param_1 + 0x4e0);
      pcVar8 = *(code **)(*plVar9 + 0x20);
      psVar6 = FUN_18001c490((longlong)&local_98);
      uVar2 = (*pcVar8)(plVar9,psVar6,local_res20);
      pwVar7 = (wchar_t *)(ulonglong)uVar2;
      iVar3 = local_res20[0];
      if ((int)uVar2 < 0) goto LAB_1800c512f;
    }
    pwVar7 = (wchar_t *)((longlong)param_3 + (ulonglong)param_4 * 2);
    if (iVar3 != 0) {
      _Str1 = FUN_18001c490((longlong)&local_98);
    }
    if (*(int *)(param_1 + 0x4e8) == 0) {
      if ((_Str1 == (wchar_t *)0x0) || (iVar3 = wcscmp(_Str1,L"ml:address"), iVar3 != 0)) {
        uVar4 = FUN_18003f5c4(param_1,param_2,(longlong)param_3,pwVar7,in_stack_ffffffffffffff58,
                              _Str1);
        pwVar7 = (wchar_t *)(uVar4 & 0xffffffff);
        goto LAB_1800c512f;
      }
      local_78 = CTTSWordSink::vftable;
      local_70 = 0;
      local_68 = 0;
      uStack_60 = 0;
      local_58 = 0;
      local_50 = 0;
      local_48 = 0;
      uStack_40 = 0;
      local_38 = 0;
      uVar4 = FUN_1800c6888(param_1,param_2,(ulonglong)param_3,(ulonglong)pwVar7,_Str1,
                            (ulonglong)&local_78);
      pwVar7 = (wchar_t *)(uVar4 & 0xffffffff);
      if (-1 < (int)uVar4) {
        uVar2 = FUN_180071b70(param_1,(longlong)&local_78);
        pwVar7 = (wchar_t *)(ulonglong)uVar2;
      }
    }
    else {
      local_78 = CTTSWordSink::vftable;
      local_70 = 0;
      local_68 = 0;
      uStack_60 = 0;
      local_58 = 0;
      local_50 = 0;
      local_48 = 0;
      uStack_40 = 0;
      local_38 = 0;
      uVar4 = FUN_1800c6888(param_1,param_2,(ulonglong)param_3,(ulonglong)pwVar7,_Str1,
                            (ulonglong)&local_78);
      pwVar7 = (wchar_t *)(uVar4 & 0xffffffff);
      if (-1 < (int)uVar4) {
        uVar2 = FUN_180071b70(param_1,(longlong)&local_78);
        pwVar7 = (wchar_t *)(ulonglong)uVar2;
      }
    }
    FUN_1800727ac(&local_78);
  }
LAB_1800c512f:
  FUN_18001d780(&local_98);
  return pwVar7;
}


// FUN_1800c6aec @ 1800c6aec

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

void FUN_1800c6aec(undefined8 param_1,longlong param_2,longlong param_3,longlong *param_4)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_4 + 8))(param_4,&DAT_1801892d0);
  if ((-1 < iVar1) && (param_2 != 0)) {
    iVar1 = (**(code **)(*param_4 + 8))(param_4,param_2);
    if ((-1 < iVar1) && (param_3 != 0)) {
      iVar1 = (**(code **)(*param_4 + 8))(param_4,&DAT_18018636c);
      if (-1 < iVar1) {
        (**(code **)(*param_4 + 8))(param_4,param_3);
      }
    }
  }
  return;
}


