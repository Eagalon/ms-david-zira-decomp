// FUN_18004e81c @ 18004e81c

void FUN_18004e81c(longlong *param_1,int *param_2,longlong param_3,undefined8 *param_4,
                  longlong *param_5,uint *param_6,uint *param_7)

{
  short *psVar1;
  uint uVar2;
  longlong lVar3;
  ushort *puVar4;
  
  if (*param_2 == 1) {
    psVar1 = *(short **)(param_2 + 2);
    *param_4 = psVar1;
    if (psVar1 != (short *)0x0) {
      lVar3 = 0x800;
      do {
        if (*psVar1 == 0) break;
        psVar1 = psVar1 + 1;
        lVar3 = lVar3 + -1;
      } while (lVar3 != 0);
      uVar2 = -(uint)(lVar3 != 0) & 0x800U - (int)lVar3;
      if (lVar3 != 0) goto LAB_18004e86d;
    }
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = (uint)*(ushort *)(param_2 + 2);
    *param_4 = *(undefined8 *)(param_2 + 4);
  }
LAB_18004e86d:
  *param_6 = uVar2;
  puVar4 = (ushort *)((longlong)*(int *)(param_3 + 4) + *param_1);
  *param_5 = (longlong)(puVar4 + 1);
  *param_7 = (uint)*puVar4;
  return;
}


// FUN_18005391c @ 18005391c

int FUN_18005391c(longlong param_1,ushort *param_2,int param_3,int param_4)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  
  iVar4 = 0;
  iVar3 = param_3 - param_4;
  if ((param_1 != 0) && (param_2 != (ushort *)0x0)) {
    if (param_4 <= param_3) {
      param_3 = param_4;
    }
    lVar5 = param_1 - (longlong)param_2;
    for (; iVar4 < param_3; iVar4 = iVar4 + 1) {
      uVar1 = *(ushort *)(lVar5 + (longlong)param_2);
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      if (uVar1 != uVar2) {
        return (uint)uVar1 - (uint)uVar2;
      }
    }
  }
  return iVar3;
}


// FUN_18015f15c @ 18015f15c

int FUN_18015f15c(longlong param_1,short *param_2,int param_3,int param_4,undefined4 *param_5)

{
  int iVar1;
  uint uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  short *psVar5;
  int iVar6;
  ulonglong uVar7;
  
  uVar3 = 0;
  if ((param_5 != (undefined4 *)0x0) && (0 < param_4)) {
    *param_5 = 0xffffffff;
    iVar6 = -1;
    uVar4 = uVar3;
    psVar5 = param_2;
    if (0 < (longlong)param_4 + -1) {
      do {
        if ((iVar6 == -1) || (*psVar5 == param_2[iVar6])) {
          iVar6 = iVar6 + 1;
          uVar4 = uVar4 + 1;
          psVar5 = param_2 + uVar4;
          iVar1 = iVar6;
          if (*psVar5 == param_2[iVar6]) {
            iVar1 = param_5[iVar6];
          }
          param_5[uVar4] = iVar1;
        }
        else {
          iVar6 = param_5[iVar6];
        }
      } while ((longlong)uVar4 < (longlong)param_4 + -1);
    }
    uVar4 = uVar3;
    uVar7 = uVar3;
    if (0 < param_3) {
      do {
        iVar1 = (int)uVar7;
        iVar6 = (int)uVar3;
        if (param_4 <= iVar6) goto LAB_18015f22b;
        if ((iVar6 == -1) || (*(short *)(param_1 + uVar4 * 2) == param_2[iVar6])) {
          uVar7 = (ulonglong)(iVar1 + 1);
          uVar4 = uVar4 + 1;
          uVar2 = iVar6 + 1;
        }
        else {
          uVar2 = param_5[iVar6];
        }
        uVar3 = (ulonglong)uVar2;
        iVar1 = (int)uVar7;
      } while ((longlong)uVar4 < (longlong)param_3);
      if (param_4 <= (int)uVar2) {
LAB_18015f22b:
        return iVar1 - param_4;
      }
    }
  }
  return -1;
}


// FUN_18015ef84 @ 18015ef84

int FUN_18015ef84(undefined2 *param_1,undefined2 *param_2,int param_3,int param_4)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = param_3 - param_4;
  if ((param_1 != (undefined2 *)0x0) && (param_2 != (undefined2 *)0x0)) {
    iVar6 = 0;
    if (param_4 <= param_3) {
      iVar6 = 0;
      param_3 = param_4;
    }
    for (; iVar6 < param_3; iVar6 = iVar6 + 1) {
      uVar1 = *param_1;
      sVar2 = _o_towlower(*param_2);
      sVar3 = _o_towlower(uVar1);
      if (sVar3 != sVar2) {
        uVar1 = *param_1;
        uVar4 = _o_towlower(*param_2);
        uVar5 = _o_towlower(uVar1);
        return (uint)uVar5 - (uint)uVar4;
      }
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
  }
  return iVar7;
}


// FUN_18015e880 @ 18015e880

bool FUN_18015e880(longlong *param_1,int *param_2,longlong param_3)

{
  uint uVar1;
  int iVar2;
  uint local_res20 [2];
  uint local_28 [2];
  undefined2 *local_20;
  undefined2 *local_18 [2];
  
  local_18[0] = (undefined2 *)0x0;
  local_20 = (undefined2 *)0x0;
  local_res20[0] = 0;
  local_28[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,local_18,(longlong *)&local_20,local_res20,local_28);
  uVar1 = local_28[0];
  if ((int)local_res20[0] < (int)local_28[0]) {
    uVar1 = local_res20[0];
  }
  iVar2 = FUN_18015ef84(local_18[0],local_20,uVar1,local_28[0]);
  return iVar2 == 0;
}


// FUN_18015e900 @ 18015e900

bool FUN_18015e900(longlong *param_1,int *param_2,longlong param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint local_res8 [2];
  uint local_res20 [2];
  short *local_28;
  longlong local_20;
  
  puVar3 = (undefined4 *)0x0;
  local_20 = 0;
  local_28 = (short *)0x0;
  local_res20[0] = 0;
  local_res8[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,&local_20,(longlong *)&local_28,local_res20,local_res8);
  puVar2 = (undefined4 *)param_1[2];
  if ((undefined4 *)param_1[2] == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)thunk_FUN_18007ca58(0x2000);
    if (puVar2 != (undefined4 *)0x0) {
      memset(puVar2,0,0x2000);
      puVar3 = puVar2;
    }
    param_1[2] = (longlong)puVar3;
    puVar2 = puVar3;
  }
  iVar1 = FUN_180053a04(local_20,local_28,local_res20[0],local_res8[0],puVar2);
  return iVar1 != -1;
}


// FUN_18015ea30 @ 18015ea30

undefined4 * FUN_18015ea30(longlong *param_1,int *param_2,longlong param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint local_res20 [2];
  uint local_28 [2];
  short *local_20;
  longlong local_18 [2];
  
  puVar3 = (undefined4 *)0x0;
  local_20 = (short *)0x0;
  local_18[0] = 0;
  local_res20[0] = 0;
  local_28[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,&local_20,local_18,local_res20,local_28);
  if ((0 < (int)local_res20[0]) || ((int)local_28[0] < 1)) {
    puVar2 = (undefined4 *)param_1[2];
    if ((undefined4 *)param_1[2] == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)thunk_FUN_18007ca58(0x2000);
      if (puVar2 != (undefined4 *)0x0) {
        memset(puVar2,0,0x2000);
        puVar3 = puVar2;
      }
      param_1[2] = (longlong)puVar3;
      puVar2 = puVar3;
    }
    iVar1 = FUN_180053a04(local_18[0],local_20,local_28[0],local_res20[0],puVar2);
    puVar3 = (undefined4 *)(ulonglong)(iVar1 != -1);
  }
  return puVar3;
}


// FUN_18015ec90 @ 18015ec90

bool FUN_18015ec90(longlong *param_1,int *param_2,longlong param_3)

{
  int iVar1;
  uint local_res20 [2];
  uint local_28 [2];
  ushort *local_20;
  longlong local_18 [2];
  
  local_18[0] = 0;
  local_20 = (ushort *)0x0;
  local_28[0] = 0;
  local_res20[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,local_18,(longlong *)&local_20,local_28,local_res20);
  iVar1 = FUN_18005391c(local_18[0],local_20,local_28[0],local_res20[0]);
  return iVar1 != 0;
}


// FUN_18015ed80 @ 18015ed80

bool FUN_18015ed80(longlong *param_1,int *param_2,longlong param_3)

{
  int iVar1;
  uint local_res20 [2];
  uint local_28 [2];
  undefined2 *local_20;
  undefined2 *local_18 [2];
  
  local_18[0] = (undefined2 *)0x0;
  local_20 = (undefined2 *)0x0;
  local_28[0] = 0;
  local_res20[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,local_18,(longlong *)&local_20,local_28,local_res20);
  iVar1 = FUN_18015ef84(local_18[0],local_20,local_28[0],local_res20[0]);
  return iVar1 != 0;
}


// FUN_18015ed00 @ 18015ed00

bool FUN_18015ed00(longlong *param_1,int *param_2,longlong param_3)

{
  uint uVar1;
  int iVar2;
  uint local_res20 [2];
  uint local_28 [2];
  undefined2 *local_20;
  undefined2 *local_18 [2];
  
  local_18[0] = (undefined2 *)0x0;
  local_20 = (undefined2 *)0x0;
  local_res20[0] = 0;
  local_28[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,local_18,(longlong *)&local_20,local_res20,local_28);
  uVar1 = local_28[0];
  if ((int)local_res20[0] < (int)local_28[0]) {
    uVar1 = local_res20[0];
  }
  iVar2 = FUN_18015ef84(local_18[0],local_20,uVar1,local_28[0]);
  return iVar2 != 0;
}


// FUN_18015eb00 @ 18015eb00

bool FUN_18015eb00(longlong *param_1,int *param_2,longlong param_3)

{
  int iVar1;
  bool bVar2;
  uint local_res20 [2];
  uint local_28 [2];
  longlong local_20;
  undefined2 *local_18 [2];
  
  bVar2 = false;
  local_20 = 0;
  local_18[0] = (undefined2 *)0x0;
  local_res20[0] = 0;
  local_28[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,&local_20,(longlong *)local_18,local_res20,local_28);
  if (((int)local_28[0] <= (int)local_res20[0]) && (-1 < (int)local_28[0])) {
    iVar1 = FUN_18015ef84((undefined2 *)
                          (local_20 + (longlong)(int)(local_res20[0] - local_28[0]) * 2),local_18[0]
                          ,local_28[0],local_28[0]);
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}


