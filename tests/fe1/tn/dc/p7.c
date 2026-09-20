// FUN_18013c7a0 @ 18013c7a0

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_18013c7a0(longlong param_1,int param_2,longlong param_3,int *param_4)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong *plVar3;
  uint uVar4;
  ulonglong uVar5;
  longlong *plVar6;
  int iVar7;
  ulonglong uVar8;
  longlong *local_68;
  undefined8 local_60;
  int local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined4 local_40;
  undefined4 local_34;
  
  uVar5 = 0;
  if (((param_2 < 1) || (param_3 == 0)) || (param_4 == (int *)0x0)) {
    uVar4 = 0x80070057;
  }
  else {
    iVar7 = 0;
    local_58 = 0;
    local_50 = 0;
    local_60 = 0;
    local_68 = (longlong *)0x0;
    local_48 = 0;
    local_40 = 10;
    local_34 = 1;
    uVar4 = FUN_180041cd0(param_1,param_2,(longlong *)&local_68,(undefined8 *)0x0);
    if (-1 < (int)uVar4) {
      uVar8 = uVar5;
      plVar3 = local_68;
      if (local_58 < 1) {
        uVar4 = 0x80041004;
      }
      else {
        while ((plVar3 != (longlong *)0x0 &&
               (iVar7 = (int)uVar8, (longlong)uVar5 < (longlong)param_2))) {
          plVar1 = (longlong *)*plVar3;
          plVar2 = *(longlong **)plVar3[2];
          if (plVar2 != (longlong *)0x0) {
            (**(code **)(*plVar2 + 8))(plVar2);
          }
          plVar6 = (longlong *)plVar3[2];
          FUN_18013d438((longlong *)&local_68,plVar3);
          if (plVar6 != (longlong *)0x0) {
            FUN_18013a09c(plVar6);
          }
          if (plVar2 != (longlong *)0x0) {
            *(longlong **)(param_3 + uVar5 * 8) = plVar2;
            uVar8 = (ulonglong)(iVar7 + 1);
            uVar5 = uVar5 + 1;
          }
          iVar7 = (int)uVar8;
          plVar3 = plVar1;
        }
        *param_4 = iVar7;
      }
    }
    FUN_180139e64(&local_68);
  }
  return uVar4;
}


// FUN_180042988 @ 180042988

ulonglong FUN_180042988(longlong param_1,longlong param_2,uint param_3,longlong *param_4,
                       undefined8 *param_5)

{
  undefined4 *puVar1;
  uint uVar2;
  longlong *plVar3;
  longlong lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined4 *puVar7;
  ulonglong uVar8;
  longlong lVar9;
  ulonglong uVar10;
  
  puVar6 = (undefined8 *)0x0;
  uVar10 = 1;
  if (*(int *)(param_2 + 0x78) == 0) {
    uVar10 = (ulonglong)param_3;
  }
  if (*(int *)(param_2 + 8) == 0) {
    uVar10 = FUN_180075edc(param_1,param_2,param_4,param_5);
    uVar2 = (uint)uVar10;
  }
  else if (*(int *)(param_2 + 8) == 1) {
    plVar3 = FUN_180042690(param_1,param_2,uVar10,param_4,param_5);
    uVar2 = (uint)plVar3;
  }
  else {
    uVar10 = FUN_180042df8(param_1,param_2,uVar10,param_4,param_5);
    uVar2 = (uint)uVar10;
  }
  uVar10 = (ulonglong)uVar2;
  if ((int)uVar2 < 0) {
    return uVar10;
  }
  if ((param_3 == 0) && (*(int *)(param_2 + 0x78) != 0)) {
    uVar2 = *(int *)(param_2 + 0x78) << 3;
    *(uint *)(*param_4 + 0xe8) = (uVar2 ^ *(uint *)(*param_4 + 0xe8)) & 0xfffffff7 ^ uVar2;
    if ((*(longlong *)(*param_4 + 0xb0) == 0) && (*(longlong *)(param_2 + 0x80) != 0)) {
      lVar4 = _o__wcsdup();
      *(longlong *)(*param_4 + 0xb0) = lVar4;
      if (lVar4 != 0) goto LAB_180042a5c;
    }
    else {
LAB_180042a5c:
      if ((*(longlong *)(*param_4 + 0x78) == 0) && (*(longlong *)(param_2 + 0x38) != 0)) {
        puVar5 = (undefined8 *)FUN_18007ca58(0x10);
        if (puVar5 != (undefined8 *)0x0) {
          *puVar5 = 0;
          *(undefined2 *)(puVar5 + 1) = 0;
          puVar6 = puVar5;
        }
        *(undefined8 **)(*param_4 + 0x78) = puVar6;
        if (puVar6 == (undefined8 *)0x0) goto LAB_180042bb6;
        puVar6 = FUN_18013e388(*(longlong **)(*param_4 + 0x78),*(longlong **)(param_2 + 0x38));
        uVar10 = (ulonglong)puVar6 & 0xffffffff;
        if ((int)puVar6 < 0) {
          return uVar10;
        }
      }
      if ((*(int *)(*param_4 + 200) != 0) ||
         (FUN_18013a18c((longlong *)(*param_4 + 0xb8),param_2 + 0x88),
         *(int *)(*param_4 + 200) == *(int *)(param_2 + 0x98))) {
        if ((int)uVar10 < 0) {
          return uVar10;
        }
        goto LAB_180042afc;
      }
    }
LAB_180042bb6:
    uVar10 = 0x8007000e;
  }
  else {
LAB_180042afc:
    puVar6 = *(undefined8 **)(param_2 + 0x40);
    while (puVar6 != (undefined8 *)0x0) {
      puVar1 = (undefined4 *)puVar6[2];
      puVar6 = (undefined8 *)*puVar6;
      puVar7 = (undefined4 *)FUN_18007ca58(0x38);
      if (puVar7 == (undefined4 *)0x0) goto LAB_180042bb6;
      *puVar7 = 0xffffffff;
      *(undefined2 *)(puVar7 + 1) = 0xffff;
      puVar7[6] = 0;
      *(undefined8 *)(puVar7 + 8) = 0;
      *(undefined8 *)(puVar7 + 4) = 0;
      *(undefined8 *)(puVar7 + 2) = 0;
      *(undefined8 *)(puVar7 + 10) = 0;
      puVar7[0xc] = 10;
      if (puVar7 == (undefined4 *)0x0) goto LAB_180042bb6;
      uVar8 = FUN_180141718(puVar7,puVar1);
      uVar10 = uVar8 & 0xffffffff;
      if ((int)uVar8 < 0) {
        return uVar10;
      }
      lVar4 = *param_4;
      lVar9 = FUN_180042bdc(lVar4 + 0x80,0,*(undefined8 *)(lVar4 + 0x80));
      if (lVar9 != 0) {
        *(undefined4 **)(lVar9 + 0x10) = puVar7;
        if (*(longlong *)(lVar4 + 0x80) == 0) {
          *(longlong *)(lVar4 + 0x88) = lVar9;
        }
        else {
          *(longlong *)(*(longlong *)(lVar4 + 0x80) + 8) = lVar9;
        }
        *(longlong *)(lVar4 + 0x80) = lVar9;
      }
    }
  }
  return uVar10;
}


