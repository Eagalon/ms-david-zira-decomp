// FUN_1800b8af4 @ 1800b8af4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined4 FUN_1800b8af4(undefined8 param_1,longlong *param_2,uint *param_3,ulonglong param_4)

{
  ushort uVar1;
  int iVar2;
  longlong lVar3;
  short *psVar4;
  ulonglong uVar5;
  
  if (param_2 != (longlong *)0x0) {
    lVar3 = FUN_18001b0e0((longlong)(param_2 + 0x13));
    if ((char)lVar3 == '\0') {
      uVar5 = 0;
      do {
        if (param_4 <= uVar5) {
          return 0;
        }
        uVar1 = (**(code **)(*param_2 + 0xf8))(param_2);
        if ((uint)uVar1 == *param_3) {
          psVar4 = FUN_18001c490((longlong)(param_2 + 0x13));
          iVar2 = _o__wcsicmp(psVar4);
          if (iVar2 == 0) {
            return 1;
          }
        }
        uVar5 = uVar5 + 1;
        param_3 = param_3 + 0xb;
      } while( true );
    }
  }
  return 0;
}


// FUN_1800b6688 @ 1800b6688

longlong * FUN_1800b6688(longlong *param_1)

{
  ulonglong uVar1;
  
  do {
    param_1 = (longlong *)FUN_18005c630((longlong)(param_1 + 1),0);
    if (param_1 == (longlong *)0x0) {
      return (longlong *)0x0;
    }
    uVar1 = FUN_18001a56c(param_1);
  } while ((int)uVar1 == 0);
  return param_1;
}


// FUN_1800b8d80 @ 1800b8d80

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8
FUN_1800b8d80(longlong param_1,longlong *param_2,longlong *param_3,longlong *param_4,int *param_5,
             undefined4 *param_6)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  
  if ((((param_3 == (longlong *)0x0) || (param_4 == (longlong *)0x0)) || (param_5 == (int *)0x0)) ||
     (param_6 == (undefined4 *)0x0)) {
    return 0x80070057;
  }
  *param_4 = 0;
  iVar2 = FUN_1800b8af4(param_1,param_3,*(uint **)(param_1 + 0x10),
                        (ulonglong)*(uint *)(param_1 + 0xc));
  uVar7 = 0;
  do {
    uVar6 = uVar7;
    if (((param_3 == param_2) || (iVar2 != 0)) ||
       (iVar3 = (**(code **)(*param_3 + 0x68))(param_3), iVar3 == 1)) break;
    puVar4 = (undefined8 *)(**(code **)(*param_3 + 0xd0))(param_3);
    if ((puVar4 != (undefined8 *)0x0) && (param_3 != (longlong *)*puVar4)) {
      param_3 = (longlong *)*puVar4;
    }
    iVar3 = (**(code **)(*param_3 + 0x68))(param_3);
    plVar5 = param_3 + 1;
    *param_4 = (longlong)param_3;
    param_3 = (longlong *)FUN_18005c630((longlong)plVar5,0);
    iVar2 = FUN_1800b8af4(plVar5,param_3,*(uint **)(param_1 + 0x10),
                          (ulonglong)*(uint *)(param_1 + 0xc));
    uVar6 = uVar7 + 1;
    if (iVar3 != 0) {
      uVar6 = uVar7;
    }
    uVar7 = uVar6;
  } while (param_3 != (longlong *)0x0);
  lVar1 = *param_4;
  *param_6 = 0;
  if (lVar1 == 0) {
    return 0;
  }
  if ((param_3 == (longlong *)0x0) || (iVar2 == 0)) {
    if (uVar6 == 0) {
      return 0;
    }
    if (*param_5 != 2) {
      return 0;
    }
  }
  else {
    if (uVar6 == 0) {
      return 0;
    }
    if (*param_5 == 0) {
      if (2 < uVar6) {
        return 0;
      }
      *param_5 = 2;
      goto LAB_1800b8ed5;
    }
    if (*param_5 != 2) {
      return 0;
    }
    if (uVar6 < 3) goto LAB_1800b8ed5;
  }
  *param_5 = 1;
LAB_1800b8ed5:
  *param_6 = 1;
  return 0;
}


// FUN_1800b897c @ 1800b897c

undefined4 FUN_1800b897c(longlong param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  longlong *plVar1;
  undefined8 *puVar2;
  undefined8 *local_18 [2];
  
  local_18[0] = (undefined8 *)FUN_18007ca58(0x18);
  if (local_18[0] != (undefined8 *)0x0) {
    *(undefined4 *)(local_18[0] + 2) = param_4;
    plVar1 = (longlong *)(param_1 + 8);
    *local_18[0] = param_2;
    local_18[0][1] = param_3;
    puVar2 = FUN_18004db10((longlong)plVar1,local_18,0,*plVar1);
    if (*plVar1 == 0) {
      *(undefined8 **)(param_1 + 0x10) = puVar2;
    }
    else {
      *(undefined8 **)(*plVar1 + 8) = puVar2;
    }
    if (puVar2 != (undefined8 *)0x0) {
      *plVar1 = (longlong)puVar2;
      return 0;
    }
    if (local_18[0] != (undefined8 *)0x0) {
      _o_free(local_18[0],0x18);
    }
  }
  return 0x8007000e;
}


// FUN_1800b8ca4 @ 1800b8ca4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8 FUN_1800b8ca4(longlong *param_1,longlong *param_2,longlong *param_3,undefined4 *param_4)

{
  int iVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong *plVar4;
  
  if ((param_3 == (longlong *)0x0) || (param_4 == (undefined4 *)0x0)) {
    uVar3 = 0x80070057;
  }
  else {
    *param_4 = 0;
    *param_3 = 0;
    plVar4 = param_1;
    if (param_2 != (longlong *)0x0) {
      do {
        iVar1 = FUN_1800b8af4(plVar4,param_2,(uint *)param_1[2],
                              (ulonglong)*(uint *)((longlong)param_1 + 0xc));
        if (iVar1 != 0) break;
        iVar1 = (**(code **)(*param_2 + 0x68))(param_2);
        if (iVar1 == 1) break;
        lVar2 = (**(code **)(*param_2 + 0xd0))(param_2);
        if ((lVar2 != 0) && (param_2 != *(longlong **)(lVar2 + 8))) {
          param_2 = *(longlong **)(lVar2 + 8);
        }
        iVar1 = FUN_18001a144(param_2);
        if (iVar1 != 0) {
          *param_3 = (longlong)param_2;
        }
        plVar4 = param_2 + 1;
        param_2 = (longlong *)FUN_180045a04((longlong)plVar4,0);
      } while (param_2 != (longlong *)0x0);
      if (*param_3 != 0) {
        *param_4 = 1;
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}


// FUN_1800b8a38 @ 1800b8a38

undefined4 FUN_1800b8a38(longlong param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  undefined8 *puVar1;
  undefined8 *local_18 [2];
  
  local_18[0] = (undefined8 *)FUN_18007ca58(0x18);
  if (local_18[0] != (undefined8 *)0x0) {
    *local_18[0] = param_2;
    local_18[0][1] = param_3;
    *(undefined4 *)(local_18[0] + 2) = param_4;
    puVar1 = FUN_18004db10(param_1 + 8,local_18,*(undefined8 *)(param_1 + 0x10),0);
    if (*(undefined8 **)(param_1 + 0x10) == (undefined8 *)0x0) {
      *(undefined8 **)(param_1 + 8) = puVar1;
    }
    else {
      **(undefined8 **)(param_1 + 0x10) = puVar1;
    }
    if (puVar1 != (undefined8 *)0x0) {
      *(undefined8 **)(param_1 + 0x10) = puVar1;
      return 0;
    }
    if (local_18[0] != (undefined8 *)0x0) {
      _o_free(local_18[0],0x18);
    }
  }
  return 0x8007000e;
}


