// FUN_18001ee6c @ 18001ee6c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_18001ee6c(longlong param_1)

{
  uint uVar1;
  int iVar2;
  longlong lVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  ulonglong uVar7;
  uint *local_res8;
  undefined8 *local_res10;
  undefined8 local_res18 [2];
  undefined1 local_58 [32];
  undefined8 local_38 [4];
  
  local_res8 = (uint *)0x0;
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x110))
                    (*(longlong **)(param_1 + 0x18),&local_res8);
  uVar7 = (ulonglong)uVar1;
  if ((((-1 < (int)uVar1) &&
       (lVar3 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x80))(), lVar3 != 0)) &&
      (iVar2 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x68))(), iVar2 == 0)) &&
     ((local_res8 == (uint *)0x0 || ((*local_res8 & 0xfffffffb) == 0)))) {
    plVar6 = *(longlong **)(param_1 + 0x1928);
    if (plVar6 != (longlong *)0x0) {
      puVar4 = (undefined8 *)
               (**(code **)(**(longlong **)(param_1 + 0x18) + 0xe0))
                         (*(longlong **)(param_1 + 0x18),local_58);
      local_res10 = puVar4;
      puVar5 = FUN_18001b878(local_38,puVar4);
      plVar6 = FUN_18006dfd0(plVar6,puVar5,local_res18);
      FUN_18001d780(puVar4);
      if ((plVar6 != (longlong *)0x0) &&
         (plVar6 = (longlong *)(**(code **)(*plVar6 + 0x20))(plVar6), plVar6 != (longlong *)0x0)) {
        uVar7 = FUN_18001efa0(param_1,plVar6,0xe);
        if ((int)uVar7 != 1) {
          return uVar7 & 0xffffffff;
        }
      }
    }
    uVar7 = FUN_18001efa0(param_1,(longlong *)(param_1 + 0x1910),0xd);
    uVar7 = uVar7 & 0xffffffff;
  }
  return uVar7;
}


// FUN_1800c2524 @ 1800c2524

undefined8 * FUN_1800c2524(undefined8 *param_1)

{
  *param_1 = CPolyphony::vftable;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[4] = CTTSString::vftable;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = CTTSString::vftable;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = CTTSString::vftable;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = CTTSString::vftable;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = CTTSString::vftable;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = CTTSString::vftable;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  *(undefined2 *)((longlong)param_1 + 0x190a) = 0;
  *(undefined4 *)((longlong)param_1 + 0x190c) = 0;
  param_1[0x322] = 0;
  param_1[0x323] = 0;
  param_1[0x324] = 0;
  *(undefined2 *)(param_1 + 0x328) = 0xffff;
  param_1[0x325] = 0;
  param_1[0x326] = 0;
  param_1[0x327] = 0;
  param_1[0x329] = 0;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  return param_1;
}


