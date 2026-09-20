// FUN_180068c6c @ 180068c6c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_180068c6c(longlong *param_1,longlong *param_2,longlong *param_3,undefined4 param_4,
                 longlong *param_5)

{
  longlong lVar1;
  int extraout_EAX;
  int iVar2;
  undefined8 *puVar3;
  short *psVar4;
  code *pcVar5;
  longlong *plVar6;
  longlong *local_res10;
  
  local_res10 = param_2;
  FUN_1800777cc(param_2,param_3,param_5);
  iVar2 = extraout_EAX;
  if (-1 < extraout_EAX) {
    puVar3 = FUN_18009d148(param_1,(longlong *)&local_res10);
    puVar3 = FUN_1800bcac8(param_1,(longlong)puVar3,*param_5);
    if (puVar3 == (undefined8 *)0x0) {
      if (*param_5 != 0) {
        puVar3 = (undefined8 *)(*param_5 + 8);
        (**(code **)*puVar3)(puVar3,1);
        *param_5 = 0;
      }
      iVar2 = -0x7ff8fff2;
    }
    else {
      if ((int)param_2[0x5e] != 0) {
        lVar1 = *param_5;
        *(int *)(lVar1 + 0x2f0) = (int)param_2[0x5e];
        plVar6 = (longlong *)(lVar1 + 0x2f8);
        *(longlong *)(lVar1 + 0x318) = param_2[99];
        pcVar5 = *(code **)(*plVar6 + 0x20);
        psVar4 = FUN_18001c490((longlong)(param_2 + 0x5f));
        iVar2 = (*pcVar5)(plVar6,psVar4);
        if (iVar2 < 0) {
          return iVar2;
        }
        FUN_180019d20((longlong)(param_2 + 0x5f));
        *(undefined4 *)(param_2 + 0x5e) = 0;
        param_2[99] = 0;
      }
      *(undefined4 *)(*param_5 + 0x210) = param_4;
    }
  }
  return iVar2;
}


// FUN_1800199a8 @ 1800199a8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_1800199a8(longlong *param_1,longlong param_2)

{
  int iVar1;
  longlong lVar2;
  uint uVar3;
  longlong *plVar4;
  
  plVar4 = (longlong *)(-(ulonglong)(param_2 != 0) & param_2 + 8U);
  iVar1 = (**(code **)(*param_1 + 0x248))();
  if (iVar1 == 0) {
    uVar3 = 0;
    if ((plVar4 != (longlong *)0x0) &&
       (uVar3 = 0, (ulonglong)*(uint *)(param_1 + 0x4a) < (ulonglong)plVar4[1])) {
      uVar3 = *(uint *)(*plVar4 + (ulonglong)*(uint *)(param_1 + 0x4a) * 4);
      lVar2 = (**(code **)(*param_1 + 0xc0))(param_1);
      if ((lVar2 != 0) && ((param_1[0x35] != 0 && (param_1 != *(longlong **)(param_1[0x35] + 8)))))
      {
        uVar3 = (uVar3 * *(int *)(param_2 + 0x30)) / 100;
      }
      if (((int)param_1[0x57] == 1) && (uVar3 != 0)) {
        uVar3 = *(uint *)(param_2 + 0x28);
      }
    }
  }
  else {
    uVar3 = (**(code **)(*param_1 + 0x248))(param_1);
  }
  return uVar3;
}


// FUN_18014ad10 @ 18014ad10

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_18014ad10(undefined8 *param_1,longlong *param_2,longlong *param_3,undefined4 param_4)

{
  longlong lVar1;
  int extraout_EAX;
  int iVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *local_res10;
  longlong local_28 [2];
  
  if ((param_2 == (longlong *)0x0) || (param_3 == (longlong *)0x0)) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    local_28[0] = 0;
    local_res10 = param_2;
    FUN_1800777cc(param_2,param_3,local_28);
    iVar2 = extraout_EAX;
    if (-1 < extraout_EAX) {
      plVar3 = FUN_18009d148(param_1,(longlong *)&local_res10);
      lVar1 = local_28[0];
      puVar4 = FUN_1800c7d74(param_1,plVar3,local_28[0]);
      if (puVar4 == (undefined8 *)0x0) {
        if (lVar1 != 0) {
          (*(code *)**(undefined8 **)(lVar1 + 8))((undefined8 *)(lVar1 + 8),1);
        }
        iVar2 = -0x7ff8fff2;
      }
      else {
        *(undefined4 *)(lVar1 + 0x210) = param_4;
        param_2[0x56] = lVar1;
      }
    }
  }
  return iVar2;
}


// FUN_180019e34 @ 180019e34

undefined4 FUN_180019e34(longlong *param_1)

{
  longlong lVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if ((*(uint *)(param_1 + 0x11) & 0xfffffffb) == 0) {
    lVar1 = FUN_18001a1d4(param_1);
    uVar2 = 0;
    if (lVar1 == 0) {
      uVar2 = 1;
    }
  }
  return uVar2;
}


// FUN_180046570 @ 180046570

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

void FUN_180046570(longlong *param_1,longlong *param_2,longlong *param_3)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 *puVar3;
  
  if ((param_3 != (longlong *)0x0) && (param_2 != (longlong *)0x0)) {
    lVar2 = 0;
    if (param_1[2] != 0) {
      lVar2 = *(longlong *)(*param_1 + 0x10);
    }
    for (; lVar2 != 0; lVar2 = FUN_180045a04(lVar2 + 8,0)) {
      FUN_18014b054(lVar2 + 8,(longlong *)0x0,0);
    }
    puVar3 = (undefined8 *)*param_3;
    while (puVar3 != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)puVar3[2];
      puVar3 = (undefined8 *)*puVar3;
      if (puVar1 != (undefined8 *)0x0) {
        (**(code **)*puVar1)(puVar1,1);
      }
    }
    FUN_180002ad8(param_3);
    puVar3 = (undefined8 *)*param_2;
    while (puVar3 != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)puVar3[2];
      puVar3 = (undefined8 *)*puVar3;
      if (puVar1 != (undefined8 *)0x0) {
        (**(code **)*puVar1)(puVar1,1);
      }
    }
    FUN_180046640(param_2);
  }
  return;
}


