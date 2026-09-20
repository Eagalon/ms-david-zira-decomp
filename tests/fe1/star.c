// FUN_180028500 @ 180028500

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_180028500(longlong *param_1,longlong param_2,longlong *param_3)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  uint uVar7;
  longlong *local_res8;
  longlong *local_res10;
  longlong local_res18;
  
  lVar1 = *param_1;
  *param_3 = param_2;
  local_res10 = (longlong *)0x0;
  local_res18 = param_2;
  iVar2 = (**(code **)(lVar1 + 0x58))(param_1,&local_res10,&local_res18);
  if (-1 < iVar2) {
    while (lVar1 = local_res18, local_res18 != 0) {
      local_res8 = (longlong *)0x0;
      iVar2 = (**(code **)(*param_1 + 0x58))(param_1,&local_res8,&local_res18);
      if (iVar2 < 0) {
        return iVar2;
      }
      puVar6 = (ushort *)(**(code **)(*local_res8 + 0x80))();
      iVar3 = (**(code **)(*local_res10 + 0x220))();
      iVar4 = (**(code **)(*local_res10 + 0x210))();
      iVar5 = (**(code **)(*local_res8 + 0x210))();
      if (iVar3 + iVar4 != iVar5) {
        return iVar2;
      }
      if (puVar6 == (ushort *)0x0) {
        return iVar2;
      }
      uVar7 = *puVar6 - 0x2a;
      if (uVar7 == 0) {
        uVar7 = (uint)puVar6[1];
      }
      if (uVar7 != 0) {
        return iVar2;
      }
      local_res10 = local_res8;
      *param_3 = lVar1;
    }
  }
  return iVar2;
}


// FUN_1800288f8 @ 1800288f8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8 FUN_1800288f8(longlong *param_1,longlong param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  longlong *local_res8;
  longlong local_res10;
  longlong *local_res18;
  
  local_res8 = (longlong *)0x0;
  local_res18 = (longlong *)0x0;
  local_res10 = param_2;
  uVar4 = (**(code **)(*param_1 + 0x58))(param_1,&local_res8,&local_res10);
  if (-1 < (int)uVar4) {
    if ((local_res10 != 0) &&
       (uVar4 = (**(code **)(*param_1 + 0x58))(param_1,&local_res18,&local_res10), (int)uVar4 < 0))
    {
      return uVar4;
    }
    if ((local_res8 != (longlong *)0x0) && (local_res18 != (longlong *)0x0)) {
      iVar1 = (**(code **)(*local_res8 + 0x220))();
      iVar2 = (**(code **)(*local_res8 + 0x210))();
      iVar3 = (**(code **)(*local_res18 + 0x210))();
      if (iVar1 + iVar2 == iVar3) {
        return 0;
      }
    }
    uVar4 = 1;
  }
  return uVar4;
}


// FUN_1800283f8 @ 1800283f8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800283f8(longlong *param_1,longlong param_2,longlong *param_3)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  uint uVar7;
  longlong *plVar8;
  longlong *plVar9;
  longlong *local_res8;
  longlong local_res10;
  
  *param_3 = 0;
  local_res8 = (longlong *)0x0;
  plVar8 = (longlong *)0x0;
  local_res10 = param_2;
  do {
    lVar1 = local_res10;
    iVar5 = (**(code **)(*param_1 + 0x58))(param_1,&local_res8,&local_res10);
    if (iVar5 < 0) {
      return iVar5;
    }
    plVar9 = plVar8;
    if ((local_res8 != (longlong *)0x0) &&
       (puVar6 = (ushort *)(**(code **)(*local_res8 + 0x80))(), plVar9 = local_res8,
       puVar6 != (ushort *)0x0)) {
      uVar7 = *puVar6 - 0x2a;
      if (uVar7 == 0) {
        uVar7 = (uint)puVar6[1];
      }
      if (uVar7 == 0) {
        if (plVar8 == (longlong *)0x0) {
          return iVar5;
        }
        if (local_res8 == (longlong *)0x0) {
          return iVar5;
        }
        iVar2 = (**(code **)(*plVar8 + 0x220))(plVar8);
        iVar3 = (**(code **)(*plVar8 + 0x210))(plVar8);
        iVar4 = (**(code **)(*local_res8 + 0x210))();
        if (iVar2 + iVar3 != iVar4) {
          return iVar5;
        }
        iVar5 = FUN_180028500(param_1,lVar1,param_3);
        return iVar5;
      }
    }
    plVar8 = plVar9;
    if (local_res10 == 0) {
      return iVar5;
    }
  } while( true );
}


// FUN_1800289bc @ 1800289bc

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800289bc(longlong *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  int iVar2;
  longlong *local_res10 [2];
  longlong local_res20;
  
  iVar2 = 0;
  local_res20 = param_2;
  while( true ) {
    lVar1 = local_res20;
    if (iVar2 < 0) {
      return iVar2;
    }
    if (local_res20 == 0) break;
    local_res10[0] = (longlong *)0x0;
    iVar2 = (**(code **)(*param_1 + 0x58))(param_1,local_res10,&local_res20);
    if (((-1 < iVar2) && (iVar2 = (**(code **)(*param_1 + 0x88))(param_1,lVar1), -1 < iVar2)) &&
       (local_res10[0] != (longlong *)0x0)) {
      (**(code **)(*local_res10[0] + 0x268))();
    }
    if (lVar1 == param_3) {
      return iVar2;
    }
  }
  return iVar2;
}


// FUN_180028620 @ 180028620

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_180028620(longlong *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  longlong *local_res10;
  longlong local_res20;
  
  iVar2 = 0;
  local_res20 = param_2;
  do {
    lVar1 = local_res20;
    if (iVar2 < 0) {
      return iVar2;
    }
    if (local_res20 == 0) {
      return iVar2;
    }
    local_res10 = (longlong *)0x0;
    iVar2 = (**(code **)(*param_1 + 0x58))(param_1,&local_res10,&local_res20);
    if ((-1 < iVar2) && (local_res10 != (longlong *)0x0)) {
      puVar3 = (ushort *)(**(code **)(*local_res10 + 0x80))();
      if (puVar3 != (ushort *)0x0) {
        uVar4 = *puVar3 - 0x2a;
        if (uVar4 == 0) {
          uVar4 = (uint)puVar3[1];
        }
        if (uVar4 == 0) {
          iVar2 = (**(code **)(*param_1 + 0x88))(param_1,lVar1);
          if ((-1 < iVar2) && (local_res10 != (longlong *)0x0)) {
            (**(code **)(*local_res10 + 0x268))();
          }
          goto LAB_180028704;
        }
      }
      iVar2 = (**(code **)(*local_res10 + 0x1f8))(local_res10,1);
    }
LAB_180028704:
    if (lVar1 == param_3) {
      return iVar2;
    }
  } while( true );
}


