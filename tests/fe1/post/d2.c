// FUN_1800b711c @ 1800b711c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800b711c(longlong param_1,longlong *param_2,longlong *param_3)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  int iVar3;
  uint uVar4;
  longlong lVar5;
  short *psVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined4 *_Dst;
  undefined4 *puVar9;
  longlong lVar10;
  size_t _Size;
  size_t sVar11;
  ulonglong uVar12;
  int local_res8 [2];
  undefined8 local_48;
  ulonglong uStack_40;
  undefined8 local_38;
  
  lVar5 = (**(code **)(**(longlong **)(param_1 + 8) + 0x80))();
  if (lVar5 == 0) {
    return 1;
  }
  local_res8[0] = 0;
  psVar6 = (short *)(**(code **)(**(longlong **)(param_1 + 8) + 0x80))();
  uVar7 = FUN_18001f36c(param_3,psVar6,local_res8);
  if ((int)uVar7 != 0) {
    return uVar7 & 0xffffffff;
  }
  sVar11 = 0xffffffffffffffff;
  if (local_res8[0] == -1) {
    return uVar7 & 0xffffffff;
  }
  iVar3 = FUN_18007b17c(param_3);
  uVar12 = (ulonglong)iVar3;
  uVar7 = (ulonglong)((int)sVar11 + 0x19);
  uVar8 = FUN_180009930(uVar7,uVar12);
  if ((int)uVar8 == 0) {
    return 0x8007000e;
  }
  auVar1._8_8_ = 0;
  auVar1._0_8_ = uVar7 & 0xffffffff;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uVar12;
  _Size = SUB168(auVar1 * auVar2,0);
  if (SUB168(auVar1 * auVar2,8) != 0) {
    _Size = sVar11;
  }
  _Dst = (undefined4 *)thunk_FUN_18007ca58(_Size);
  if (_Dst == (undefined4 *)0x0) {
    _Dst = (undefined4 *)0x0;
  }
  else {
    memset(_Dst,0,_Size);
  }
  if (_Dst == (undefined4 *)0x0) {
    return 0x8007000e;
  }
  lVar5 = uVar12 - 1;
  puVar9 = _Dst;
  lVar10 = lVar5;
  if (0 < lVar5) {
    do {
      *puVar9 = 3;
      *(longlong *)(puVar9 + 2) = param_1;
      lVar10 = lVar10 + -1;
      puVar9 = puVar9 + 6;
    } while (lVar10 != 0);
  }
  _Dst[lVar5 * 6] = 1;
  *(undefined **)(_Dst + lVar5 * 6 + 2) = &DAT_180184218;
  local_38 = 0;
  local_48 = 0;
  uStack_40 = 0;
  uVar4 = FUN_18001f970(param_3,local_res8[0],(longlong)_Dst,iVar3,(undefined4 *)&local_48);
  uVar7 = (ulonglong)uVar4;
  if (uVar4 == 0) {
    uVar12 = uStack_40 & 0xffffffff;
  }
  else {
    if (uVar4 != 1) goto LAB_1800b7292;
    uVar7 = 0;
    uVar12 = 0;
  }
  (**(code **)(*param_2 + 0x18))(param_2,uVar12);
LAB_1800b7292:
  _o_free(_Dst);
  return uVar7;
}


// FUN_180061840 @ 180061840

undefined8 FUN_180061840(longlong param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  if (param_2 == (undefined8 *)0x0) {
    return 0x80070057;
  }
  uVar1 = *(undefined8 *)(param_1 + 0x98);
  *param_2 = *(undefined8 *)(param_1 + 0x90);
  param_2[1] = uVar1;
  return 0;
}


// FUN_1800b7ca8 @ 1800b7ca8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800b7ca8(longlong param_1,longlong *param_2,longlong *param_3,longlong param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (((param_4 == 0) || (param_3 == (longlong *)0x0)) || (param_2[1] == 0)) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    FUN_1800603f0((longlong *)(param_1 + 0x18),param_4);
    *(undefined4 *)(param_1 + 0x10) = 1;
    *(longlong **)(param_1 + 0x30) = param_3;
    uVar1 = (**(code **)(*param_3 + 0x38))(param_3);
    *(undefined2 *)(param_1 + 0x38) = uVar1;
    FUN_180036064((longlong *)(param_1 + 0x40),0);
    lVar4 = *(longlong *)(param_1 + 0x48);
    iVar2 = FUN_180036064((longlong *)(param_1 + 0x40),param_2[1] + lVar4);
    if (-1 < iVar2) {
      lVar5 = param_2[1];
      puVar3 = (undefined8 *)(*(longlong *)(param_1 + 0x40) + lVar4 * 8);
      if (lVar5 != 0) {
        lVar4 = *param_2 - (longlong)puVar3;
        do {
          *puVar3 = *(undefined8 *)(lVar4 + (longlong)puVar3);
          puVar3 = puVar3 + 1;
          lVar5 = lVar5 + -1;
        } while (lVar5 != 0);
      }
    }
  }
  return iVar2;
}


// FUN_1800b7d70 @ 1800b7d70

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800b7d70(longlong param_1,longlong *param_2)

{
  int iVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  ulonglong uVar6;
  uint local_res10 [2];
  longlong local_res18;
  longlong *local_res20;
  longlong local_60 [3];
  undefined4 local_48;
  
  plVar5 = (longlong *)0x0;
  if (param_2 == (longlong *)0x0) {
    return -0x7ff8ffa9;
  }
  local_60[0] = 0;
  local_60[1] = 0;
  local_60[2] = 0;
  local_48 = 0;
  iVar1 = FUN_180091d1c((longlong)param_2,local_60);
  plVar2 = (longlong *)(**(code **)(*param_2 + 0x50))(param_2);
  plVar4 = (longlong *)param_2[0x6d];
  *(longlong *)(param_1 + 8) = param_2[0xb0];
  if (iVar1 < 0) goto LAB_1800b7fb5;
  if (plVar4 == (longlong *)0x0) {
    iVar1 = -0x7fffbffb;
    goto LAB_1800b7fb5;
  }
  local_res18 = 0;
  local_res10[0] = 0;
  iVar1 = (**(code **)(*plVar4 + 8))(plVar4,&DAT_180181998,&DAT_180181988,&local_res18,local_res10);
  if (iVar1 < 0) {
    if (iVar1 != -0x7ffb7fe6) goto LAB_1800b7fb5;
LAB_1800b7efc:
    local_res18 = 0;
    local_res10[0] = 0;
    local_res20 = (longlong *)0x0;
    iVar1 = (**(code **)*plVar4)
                      (plVar4,&DAT_1801861b0,&DAT_180188900,&local_res18,local_res10,&local_res20);
    if (iVar1 < 0) {
      if (iVar1 == -0x7ffb7fe6) {
        iVar1 = 0;
      }
      goto LAB_1800b7fb5;
    }
    if (local_res18 == 0) goto LAB_1800b7fb5;
    plVar4 = (longlong *)FUN_18007ca58(0x20);
    if (plVar4 != (longlong *)0x0) {
      plVar4[1] = 0;
      plVar4[2] = 0;
      plVar4[3] = 0;
      *plVar4 = (longlong)CCRFSentTypeDetector::vftable;
      plVar5 = plVar4;
    }
    *(longlong **)(param_1 + 0x10) = plVar5;
    if (plVar5 != (longlong *)0x0) {
      uVar6 = FUN_1800e3650(plVar5,local_res18,(ulonglong)local_res10[0],(longlong)local_res20,
                            0x1801888c8);
      iVar1 = (int)uVar6;
      goto LAB_1800b7fb5;
    }
  }
  else {
    if (local_res18 == 0) goto LAB_1800b7efc;
    local_res20 = (longlong *)FUN_18007ca58(0xa0);
    plVar3 = plVar5;
    if (local_res20 != (longlong *)0x0) {
      *local_res20 = (longlong)CRuleSentAndPuncDetector::vftable;
      local_res20[1] = 0;
      *(undefined4 *)(local_res20 + 2) = 0;
      local_res20[3] = 0;
      local_res20[4] = 0;
      local_res20[5] = 0;
      local_res20[6] = 0;
      *(undefined2 *)(local_res20 + 7) = 0xffff;
      local_res20[8] = 0;
      local_res20[9] = 0;
      local_res20[10] = 0;
      *(undefined4 *)(local_res20 + 0xb) = 0;
      local_res20[0xc] = (longlong)CTTSString::vftable;
      local_res20[0xd] = 0;
      local_res20[0xe] = 0;
      local_res20[0xf] = 0;
      local_res20[0x10] = (longlong)CTTSString::vftable;
      local_res20[0x11] = 0;
      local_res20[0x12] = 0;
      local_res20[0x13] = 0;
      plVar3 = local_res20;
    }
    *(longlong **)(param_1 + 0x18) = plVar3;
    if (plVar3 != (longlong *)0x0) {
      iVar1 = FUN_1800b7ca8((longlong)plVar3,local_60,plVar2,local_res18);
      if (iVar1 < 0) goto LAB_1800b7fb5;
      goto LAB_1800b7efc;
    }
  }
  iVar1 = -0x7ff8fff2;
LAB_1800b7fb5:
  FUN_18001d7d0(local_60);
  return iVar1;
}


