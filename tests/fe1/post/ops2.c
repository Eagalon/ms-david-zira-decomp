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


// FUN_18015ec10 @ 18015ec10

bool FUN_18015ec10(longlong *param_1,int *param_2,longlong param_3)

{
  uint uVar1;
  int iVar2;
  uint local_res20 [2];
  uint local_28 [2];
  ushort *local_20;
  longlong local_18 [2];
  
  local_18[0] = 0;
  local_20 = (ushort *)0x0;
  local_res20[0] = 0;
  local_28[0] = 0;
  FUN_18004e81c(param_1,param_2,param_3,local_18,(longlong *)&local_20,local_res20,local_28);
  uVar1 = local_28[0];
  if ((int)local_res20[0] < (int)local_28[0]) {
    uVar1 = local_res20[0];
  }
  iVar2 = FUN_18005391c(local_18[0],local_20,uVar1,local_28[0]);
  return iVar2 != 0;
}


// FUN_18015ee10 @ 18015ee10

bool FUN_18015ee10(longlong *param_1,int *param_2,longlong param_3)

{
  bool bVar1;
  undefined7 extraout_var;
  
  bVar1 = FUN_18015ef00(param_1,param_2,param_3);
  return (int)CONCAT71(extraout_var,bVar1) == 0;
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


