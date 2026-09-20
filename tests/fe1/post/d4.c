// FUN_18001fa3c @ 18001fa3c

int FUN_18001fa3c(longlong *param_1,longlong param_2,longlong param_3,int param_4)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  int iVar4;
  int *piVar5;
  
  iVar2 = 0;
  piVar5 = (int *)(param_3 + 8);
  lVar3 = 0;
  while ((iVar4 = -1, lVar3 < param_4 &&
         (iVar1 = FUN_18001ffa8(param_1,param_2,(int *)((longlong)piVar5[1] + *param_1),*piVar5),
         iVar4 = iVar2, iVar1 == 0))) {
    iVar2 = iVar2 + 1;
    lVar3 = lVar3 + 1;
    piVar5 = piVar5 + 4;
  }
  return iVar4;
}


// FUN_1800b790c @ 1800b790c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong * FUN_1800b790c(longlong param_1)

{
  int iVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  if (param_1 == 0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    plVar4 = (longlong *)0x0;
    lVar3 = FUN_18005c630(param_1 + 8,0);
    if (lVar3 != 0) {
      plVar4 = (longlong *)FUN_18005c630(param_1 + 8,0);
    }
    plVar2 = (longlong *)0x0;
    while (plVar4 != (longlong *)0x0) {
      iVar1 = (**(code **)(*plVar4 + 0x68))(plVar4);
      plVar5 = plVar4;
      if (iVar1 != 0) {
        plVar5 = plVar2;
      }
      plVar4 = (longlong *)FUN_18005c630((longlong)(plVar4 + 1),1);
      plVar2 = plVar5;
    }
  }
  return plVar2;
}


// FUN_1800b7a80 @ 1800b7a80

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong * FUN_1800b7a80(longlong *param_1)

{
  int iVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong *plVar4;
  
  plVar2 = FUN_1800b790c((longlong)param_1);
  plVar4 = (longlong *)0x0;
  if (plVar2 != (longlong *)0x0) {
    do {
      lVar3 = FUN_180045a04((longlong)(plVar2 + 1),1);
      if (lVar3 == 0) {
        return (longlong *)0x0;
      }
      plVar2 = (longlong *)FUN_180045a04((longlong)(plVar2 + 1),1);
      iVar1 = (**(code **)(*plVar2 + 0x68))(plVar2);
    } while ((iVar1 != 0) || (plVar4 = plVar2, plVar2 == param_1));
  }
  return plVar4;
}


// FUN_1800b7990 @ 1800b7990

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong * FUN_1800b7990(longlong *param_1)

{
  int iVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  
  if (param_1 == (longlong *)0x0) {
    plVar2 = (longlong *)0x0;
  }
  else {
    iVar1 = (**(code **)(*param_1 + 0x68))();
    plVar5 = param_1;
    if (iVar1 != 0) {
      plVar5 = (longlong *)0x0;
    }
    plVar3 = (longlong *)FUN_18005c630((longlong)(param_1 + 1),0);
    while (plVar2 = plVar5, plVar3 != (longlong *)0x0) {
      puVar4 = (undefined8 *)(**(code **)(*plVar3 + 0xd0))(plVar3);
      plVar5 = plVar3;
      if ((puVar4 != (undefined8 *)0x0) && (plVar3 != (longlong *)*puVar4)) {
        plVar5 = (longlong *)*puVar4;
      }
      iVar1 = (**(code **)(*plVar5 + 0x68))(plVar5);
      if ((iVar1 == 1) && (iVar1 = (**(code **)(*plVar5 + 0x108))(plVar5), iVar1 - 1U < 3)) {
        return plVar2;
      }
      iVar1 = (**(code **)(*plVar5 + 0x68))(plVar5);
      plVar3 = (longlong *)FUN_18005c630((longlong)(plVar5 + 1),0);
      if (iVar1 != 0) {
        plVar5 = plVar2;
      }
    }
  }
  return plVar2;
}


// FUN_1800b7afc @ 1800b7afc

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong * FUN_1800b7afc(longlong *param_1)

{
  int iVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong *plVar4;
  
  plVar2 = FUN_1800b7990(param_1);
  plVar4 = (longlong *)0x0;
  if (plVar2 != (longlong *)0x0) {
    do {
      lVar3 = FUN_180045a04((longlong)(plVar2 + 1),1);
      if (lVar3 == 0) {
        return (longlong *)0x0;
      }
      plVar2 = (longlong *)FUN_180045a04((longlong)(plVar2 + 1),1);
      iVar1 = (**(code **)(*plVar2 + 0x68))(plVar2);
    } while ((iVar1 != 0) || (plVar4 = plVar2, plVar2 == param_1));
  }
  return plVar4;
}


// FUN_1800b748c @ 1800b748c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800b748c(longlong *param_1,longlong *param_2)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  longlong *plVar4;
  undefined8 uVar5;
  
  if ((param_1 == (longlong *)0x0) || (param_2 == (longlong *)0x0)) {
    iVar2 = -0x7ff8ffa9;
  }
  else {
    plVar4 = FUN_1800b7990(param_1);
    FUN_180019d20((longlong)param_2);
    iVar2 = (**(code **)(*param_2 + 8))(param_2);
    for (; (-1 < iVar2 && (plVar4 != (longlong *)0x0));
        plVar4 = (longlong *)FUN_180045a04((longlong)(plVar4 + 1),0)) {
      iVar3 = (**(code **)(*plVar4 + 0x68))(plVar4);
      if (iVar3 == 0) {
        pcVar1 = *(code **)(*param_2 + 0x18);
        uVar5 = (**(code **)(*plVar4 + 0x80))(plVar4);
        iVar2 = (*pcVar1)(param_2,uVar5,&DAT_18017f888);
      }
    }
  }
  return iVar2;
}


// FUN_18005c630 @ 18005c630

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong FUN_18005c630(longlong param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  longlong lVar3;
  
  if (*(longlong *)(param_1 + 0x20) != 0) {
    lVar3 = *(longlong *)(*(longlong *)(param_1 + 0x28) + 8);
    while (lVar3 != 0) {
      lVar1 = *(longlong *)(lVar3 + 0x10);
      lVar3 = *(longlong *)(lVar3 + 8);
      if (param_2 == 0) {
        return lVar1;
      }
      if (lVar1 == 0) {
        return 0;
      }
      iVar2 = (**(code **)(*(longlong *)(lVar1 + 8) + 8))();
      if (iVar2 == 0) {
        return lVar1;
      }
    }
  }
  return 0;
}


// FUN_180045a04 @ 180045a04

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong FUN_180045a04(longlong param_1,int param_2)

{
  longlong lVar1;
  int iVar2;
  undefined8 *puVar3;
  
  if (*(longlong *)(param_1 + 0x20) != 0) {
    puVar3 = (undefined8 *)**(undefined8 **)(param_1 + 0x28);
    while (puVar3 != (undefined8 *)0x0) {
      lVar1 = puVar3[2];
      puVar3 = (undefined8 *)*puVar3;
      if (param_2 == 0) {
        return lVar1;
      }
      if (lVar1 == 0) {
        return 0;
      }
      iVar2 = (**(code **)(*(longlong *)(lVar1 + 8) + 8))();
      if (iVar2 == 0) {
        return lVar1;
      }
    }
  }
  return 0;
}


// FUN_1800b7fd8 @ 1800b7fd8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8 FUN_1800b7fd8(undefined8 param_1,longlong *param_2,longlong *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  wchar_t *_Str1;
  undefined8 uVar5;
  
  if ((param_2 == (longlong *)0x0) || (param_3 == (longlong *)0x0)) {
LAB_1800b80c1:
    uVar5 = 0;
  }
  else {
    lVar4 = (**(code **)(*param_2 + 0xc0))(param_2);
    if (lVar4 == 0) {
LAB_1800b807c:
      iVar2 = (**(code **)(*param_2 + 0x220))(param_2);
      iVar1 = (**(code **)(*param_2 + 0x210))(param_2);
      uVar3 = (**(code **)(*param_3 + 0x210))(param_3);
      if (uVar3 <= (uint)(iVar2 + iVar1)) goto LAB_1800b80c1;
    }
    else {
      lVar4 = (**(code **)(*param_3 + 0xc0))(param_3);
      if (lVar4 == 0) goto LAB_1800b807c;
      iVar2 = (**(code **)(*param_2 + 0x210))(param_2);
      iVar1 = (**(code **)(*param_3 + 0x210))(param_3);
      if (iVar2 != iVar1) goto LAB_1800b807c;
      _Str1 = (wchar_t *)(**(code **)(*param_2 + 0xc0))(param_2);
      iVar2 = wcscmp(_Str1,L"sp:default");
      if (iVar2 == 0) goto LAB_1800b807c;
    }
    uVar5 = 1;
  }
  return uVar5;
}


// FUN_1800b7b78 @ 1800b7b78

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800b7b78(longlong *param_1,longlong *param_2,longlong *param_3)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong lVar6;
  
  if (((param_1 == (longlong *)0x0) || (param_2 == (longlong *)0x0)) || (param_3 == (longlong *)0x0)
     ) {
    iVar3 = -0x7ff8ffa9;
  }
  else {
    iVar3 = 0;
    plVar4 = FUN_1800b7990(param_1);
    FUN_180019d20((longlong)param_3);
    do {
      if (plVar4 == (longlong *)0x0) {
        return iVar3;
      }
      iVar2 = (**(code **)(*plVar4 + 0x68))(plVar4);
      if (iVar2 == 0) {
        lVar5 = (**(code **)(*plVar4 + 0x80))(plVar4);
        pcVar1 = *(code **)(*param_2 + 8);
        (**(code **)(*plVar4 + 0xf0))(plVar4);
        lVar6 = (*pcVar1)(param_2);
        if (((lVar5 != 0) && (lVar6 != 0)) &&
           (iVar3 = (**(code **)(*param_3 + 0x18))(param_3,lVar5,&DAT_1801888a8), -1 < iVar3)) {
          iVar3 = (**(code **)(*param_3 + 0x18))(param_3,lVar6,&DAT_18017f888);
        }
      }
      plVar4 = (longlong *)FUN_180045a04((longlong)(plVar4 + 1),0);
    } while (-1 < iVar3);
  }
  return iVar3;
}


