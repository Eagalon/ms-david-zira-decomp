// FUN_18003cc9c @ 18003cc9c

uint FUN_18003cc9c(longlong param_1,ushort *param_2,undefined4 param_3)

{
  uint uVar1;
  undefined8 *puVar2;
  
  if (param_2 == (ushort *)0x0) {
    uVar1 = 0x80070057;
  }
  else {
    *(ushort **)(param_1 + 8) = param_2;
    *(undefined4 *)(param_1 + 0x10) = param_3;
    puVar2 = FUN_18003cce0(param_2);
    *(undefined8 **)(param_1 + 0x18) = puVar2;
    uVar1 = ~-(uint)(puVar2 != (undefined8 *)0x0) & 0x80004005;
  }
  return uVar1;
}


// FUN_18002cc60 @ 18002cc60

void FUN_18002cc60(longlong param_1,undefined2 *param_2)

{
  longlong lVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  ushort uVar5;
  ushort *puVar6;
  int iVar7;
  ushort uVar8;
  uint uVar9;
  short sVar10;
  short sVar11;
  
  pbVar3 = *(byte **)(param_2 + 8);
  puVar6 = *(ushort **)(param_1 + 8);
  iVar7 = 0;
  sVar10 = 0;
  sVar11 = 0;
  uVar8 = (ushort)*pbVar3;
  uVar5 = *puVar6;
  pbVar4 = pbVar3;
  if (uVar5 <= *pbVar3) {
    do {
      sVar11 = sVar10 + uVar5;
      puVar6 = puVar6 + 1;
      iVar7 = iVar7 + 1;
      uVar8 = (uVar8 - uVar5) * 0x100 + (ushort)pbVar4[1];
      uVar5 = *puVar6;
      pbVar4 = pbVar4 + 1;
      sVar10 = sVar11;
    } while (uVar5 <= uVar8);
  }
  pbVar3 = pbVar3 + (iVar7 + 1);
  lVar1 = (ulonglong)(ushort)(sVar11 + uVar8) * 4;
  *param_2 = *(undefined2 *)(lVar1 + *(longlong *)(param_1 + 0x28));
  uVar5 = *(ushort *)(lVar1 + 2 + *(longlong *)(param_1 + 0x28));
  param_2[1] = uVar5;
  if ((uVar5 & 4) == 0) {
    *(undefined4 *)(param_2 + 4) = 0;
  }
  else {
    bVar2 = *pbVar3;
    uVar9 = (uint)bVar2;
    pbVar4 = pbVar3 + 1;
    if (0xbf < bVar2) {
      *(uint *)(param_2 + 4) = (*pbVar4 & 0x7f | (bVar2 & 0x3f) << 7) << 8 | (uint)pbVar3[2];
      *(byte **)(param_2 + 8) = pbVar3 + 3;
      return;
    }
    if (0x7f < bVar2) {
      uVar9 = (bVar2 & 0x7f) << 8 | (uint)*pbVar4;
      pbVar4 = pbVar3 + 2;
    }
    *(uint *)(param_2 + 4) = uVar9;
    pbVar3 = pbVar4;
  }
  *(byte **)(param_2 + 8) = pbVar3;
  return;
}


// FUN_18002cb20 @ 18002cb20

void FUN_18002cb20(longlong param_1,longlong param_2)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  ushort *puVar8;
  
  uVar1 = *(ushort *)(param_2 + 2) & 0x1d0;
  if (uVar1 != 0) {
    pbVar7 = *(byte **)(param_2 + 0x10);
    if (uVar1 == 0x10) {
      puVar8 = *(ushort **)(param_1 + 0x20);
      uVar2 = (ushort)*pbVar7;
      iVar6 = 0;
      sVar3 = 0;
      sVar4 = 0;
      uVar1 = *puVar8;
      pbVar5 = pbVar7;
      if (uVar1 <= *pbVar7) {
        do {
          puVar8 = puVar8 + 1;
          sVar4 = sVar3 + uVar1;
          iVar6 = iVar6 + 1;
          uVar2 = (uVar2 - uVar1) * 0x100 + (ushort)pbVar5[1];
          uVar1 = *puVar8;
          pbVar5 = pbVar5 + 1;
          sVar3 = sVar4;
        } while (uVar1 <= uVar2);
      }
      pbVar7 = pbVar7 + (iVar6 + 1);
      pbVar5 = *(byte **)(param_2 + 0x28);
      if (*(byte **)(param_2 + 0x28) == (byte *)0x0) {
        *(byte **)(param_2 + 0x28) = pbVar7;
        pbVar5 = pbVar7;
      }
      *(byte **)(param_2 + 0x28) =
           pbVar5 + *(uint *)(*(longlong *)(param_1 + 0x40) + (ulonglong)(ushort)(sVar4 + uVar2) * 4
                             );
    }
    else if (uVar1 == 0x50) {
      *(byte **)(param_2 + 0x28) = pbVar7;
    }
    else if (uVar1 == 0x90) {
      puVar8 = *(ushort **)(param_1 + 0x18);
      iVar6 = 0;
      uVar2 = (ushort)*pbVar7;
      uVar1 = *puVar8;
      pbVar5 = pbVar7;
      if (uVar1 <= *pbVar7) {
        do {
          puVar8 = puVar8 + 1;
          iVar6 = iVar6 + 1;
          uVar2 = (uVar2 - uVar1) * 0x100 + (ushort)pbVar5[1];
          uVar1 = *puVar8;
          pbVar5 = pbVar5 + 1;
        } while (uVar1 <= uVar2);
      }
      pbVar7 = pbVar7 + (iVar6 + 1);
    }
    else if (uVar1 == 0x110) {
      pbVar7 = pbVar7 + 3;
    }
    *(byte **)(param_2 + 0x10) = pbVar7;
  }
  return;
}


// FUN_18003abf0 @ 18003abf0

int FUN_18003abf0(short *param_1,ushort *param_2,byte *param_3)

{
  byte *pbVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  ushort uVar7;
  
  uVar3 = (ushort)*param_3;
  iVar4 = 0;
  iVar5 = 0;
  uVar7 = *param_2;
  sVar6 = 0;
  if (uVar7 <= *param_3) {
    do {
      pbVar1 = param_3 + 1;
      param_3 = param_3 + 1;
      sVar2 = uVar3 - uVar7;
      param_2 = param_2 + 1;
      sVar6 = sVar6 + uVar7;
      uVar7 = *param_2;
      iVar5 = iVar4 + 1;
      uVar3 = sVar2 * 0x100 + (ushort)*pbVar1;
      iVar4 = iVar5;
    } while (uVar7 <= uVar3);
  }
  *param_1 = sVar6 + uVar3;
  return iVar5 + 1;
}


