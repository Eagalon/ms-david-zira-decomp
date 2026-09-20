// FUN_1800c6888 @ 1800c6888

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_1800c6888(longlong param_1,longlong param_2,ulonglong param_3,ulonglong param_4,
                       undefined8 param_5,ulonglong param_6)

{
  longlong *plVar1;
  uint uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  undefined8 *puVar5;
  ulonglong uVar6;
  undefined1 auStackY_438 [32];
  undefined ***pppuVar7;
  ulonglong local_3e0;
  ulonglong local_3d8;
  uint local_3d0 [2];
  undefined8 local_3c8;
  undefined **local_3c0;
  undefined8 local_3b8;
  undefined8 uStack_3b0;
  undefined8 local_3a8;
  undefined8 local_398 [4];
  undefined1 local_378 [800];
  ulonglong local_58;
  
  local_58 = DAT_1801c0240 ^ (ulonglong)auStackY_438;
  local_3c8 = param_5;
  local_3d8 = param_6;
  uVar4 = 0;
  memset(local_378,0,800);
  local_3d0[0] = 0;
  uVar6 = param_3;
  if ((*(int *)(param_2 + 0x1c) != 0) &&
     (plVar1 = *(longlong **)(param_1 + 0x4d8), param_6 = local_3d8, plVar1 != (longlong *)0x0)) {
    local_3e0 = 0;
    uVar3 = FUN_1800652b0(*(short *)(param_1 + 0x10),&local_3e0);
    uVar4 = uVar3 & 0xffffffff;
    param_6 = local_3d8;
    if (-1 < (int)uVar3) {
      uVar2 = (**(code **)(*plVar1 + 0x18))
                        (plVar1,param_3,(longlong)(param_4 - param_3) >> 1,local_378);
      uVar4 = (ulonglong)uVar2;
      param_6 = local_3d8;
    }
  }
  while( true ) {
    if ((int)uVar4 < 0) {
      return uVar4;
    }
    if (param_4 <= uVar6) break;
    local_3d8 = local_3d8 & 0xffffffff00000000;
    local_3e0 = local_3e0 & 0xffffffff00000000;
    local_3c0 = CTTSString::vftable;
    local_3b8 = 0;
    uStack_3b0 = 0;
    local_3a8 = 0;
    pppuVar7 = &local_3c0;
    uVar2 = (**(code **)(**(longlong **)(param_1 + 0x4d0) + 0x18))
                      (*(longlong **)(param_1 + 0x4d0),uVar6,(longlong)(param_4 - uVar6) >> 1,
                       local_3c8);
    uVar4 = (ulonglong)uVar2;
    if (uVar2 == 0) {
      if (((int)local_3e0 == 0) ||
         (uVar4 = FUN_180070830(param_1,param_2,param_3,uVar6,uVar6 + (local_3e0 & 0xffffffff) * 2,
                                (longlong)local_378,pppuVar7,local_3d0,param_6), -1 < (int)uVar4)) {
        puVar5 = FUN_18001b878(local_398,&local_3c0);
        uVar4 = FUN_1800709a8((undefined8 *)(local_3e0 & 0xffffffff),param_2,
                              uVar6 + (longlong)(local_3e0 & 0xffffffff) * 2,(int)local_3d8,puVar5,
                              0xffff,param_6);
      }
      uVar4 = uVar4 & 0xffffffff;
      uVar6 = uVar6 + (ulonglong)(uint)((int)local_3d8 + (int)local_3e0) * 2;
    }
    else if (uVar2 == 1) {
      uVar6 = FUN_180070830(param_1,param_2,param_3,uVar6,param_4,(longlong)local_378,pppuVar7,
                            local_3d0,param_6);
      FUN_18001d780(&local_3c0);
      return uVar6 & 0xffffffff;
    }
    FUN_18001d780(&local_3c0);
  }
  return uVar4;
}


