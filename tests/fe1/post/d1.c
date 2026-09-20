// FUN_1800b72c4 @ 1800b72c4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800b72c4(longlong param_1,longlong *param_2,longlong *param_3)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined8 uVar4;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    uVar1 = 1;
  }
  else {
    lVar2 = FUN_180034e44((longlong)param_2);
    uVar4 = 0;
    if (*(longlong *)(lVar2 + 0x10) != 0) {
      uVar4 = *(undefined8 *)(*(longlong *)(lVar2 + 8) + 0x10);
    }
    *(undefined8 *)(param_1 + 8) = uVar4;
    if (((param_3 != (longlong *)0x0) &&
        (plVar3 = (longlong *)(**(code **)(*param_3 + 0x48))(param_3), plVar3 != (longlong *)0x0))
       && (uVar1 = FUN_1800b711c(param_1,param_2,plVar3), (int)uVar1 != 1)) {
      return uVar1;
    }
    uVar1 = FUN_1800b711c(param_1,param_2,(longlong *)(param_1 + 0x18));
  }
  return uVar1;
}


// FUN_1800c0dd8 @ 1800c0dd8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800c0dd8(longlong *param_1,longlong param_2)

{
  int iVar1;
  uint uVar2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong lVar6;
  TypeDescriptor local_58;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined8 local_38;
  undefined8 uStack_30;
  undefined8 local_28;
  undefined4 local_20;
  undefined8 local_18;
  
  if (param_2 == 0) {
    uVar3 = 0x80070057;
  }
  else {
    uVar3 = FUN_18014a0a8(param_2);
    plVar4 = (longlong *)FUN_180034e44(param_2);
    if (plVar4[2] == 0) {
      lVar6 = 0;
      lVar5 = 0;
    }
    else {
      lVar5 = *(longlong *)(*plVar4 + 0x10);
      lVar6 = *(longlong *)(plVar4[1] + 0x10);
    }
    local_58.pVFTable = CCRFRuntimeData::vftable;
    local_58.spare._0_4_ = 0;
    local_48 = 0;
    uStack_40 = 0;
    local_38 = 0;
    uStack_30 = 0;
    local_28 = 0;
    local_20 = 0;
    local_18 = 1;
    iVar1 = (int)uVar3;
    if (-1 < iVar1) {
      uVar3 = FUN_1800e34c8(param_1,lVar5,lVar6,&local_58);
      iVar1 = (int)uVar3;
    }
    uVar3 = uVar3 & 0xffffffff;
    if (iVar1 == 0) {
      uVar2 = (**(code **)(*param_1 + 0x38))(param_1,param_2,&local_58);
      uVar3 = (ulonglong)uVar2;
    }
    FUN_1800e380c(&local_58.pVFTable);
  }
  return uVar3;
}


// FUN_18006df80 @ 18006df80

longlong * FUN_18006df80(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  longlong *plVar2;
  undefined8 local_res18 [2];
  undefined8 local_28 [4];
  
  puVar1 = FUN_18001b878(local_28,param_2);
  plVar2 = FUN_18006dfd0(param_1,puVar1,local_res18);
  FUN_18001d780(param_2);
  return plVar2;
}


