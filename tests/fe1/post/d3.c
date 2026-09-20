// FUN_1800603f0 @ 1800603f0

void FUN_1800603f0(longlong *param_1,longlong param_2)

{
  *param_1 = param_2;
  if (param_2 != 0) {
    param_1[1] = *(int *)(param_2 + 0x10) + param_2;
  }
  return;
}


// FUN_18001f36c @ 18001f36c

ulonglong FUN_18001f36c(longlong *param_1,short *param_2,int *param_3)

{
  ushort uVar1;
  ushort uVar2;
  longlong lVar3;
  int iVar4;
  short *psVar5;
  ushort *puVar6;
  ulonglong uVar7;
  int iVar8;
  int iVar9;
  longlong lVar10;
  longlong lVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  
  lVar3 = *param_1;
  if (lVar3 == 0) {
    uVar7 = 0x80048001;
  }
  else {
    iVar13 = *(int *)(lVar3 + 8) + -1;
    iVar14 = 0;
    while (iVar4 = -1, iVar14 <= iVar13) {
      iVar4 = (iVar13 + iVar14) / 2;
      lVar11 = (longlong)iVar4 * 0x10 + param_1[1];
      if (lVar11 == 0) break;
      if (param_2 == (short *)0x0) {
LAB_18001f4ac:
        uVar12 = 0xffffffff;
      }
      else {
        lVar10 = 0x800;
        psVar5 = param_2;
        do {
          if (*psVar5 == 0) break;
          psVar5 = psVar5 + 1;
          lVar10 = lVar10 + -1;
        } while (lVar10 != 0);
        uVar12 = -(uint)(lVar10 != 0) & 0x800U - (int)lVar10;
        if (lVar10 == 0) goto LAB_18001f4ac;
      }
      puVar6 = (ushort *)(*(int *)(lVar11 + 4) + lVar3);
      uVar1 = *puVar6;
      puVar6 = puVar6 + 1;
      iVar8 = uVar12 - uVar1;
      if ((param_2 != (short *)0x0) && (puVar6 != (ushort *)0x0)) {
        if ((int)(uint)uVar1 <= (int)uVar12) {
          uVar12 = (uint)uVar1;
        }
        lVar11 = (longlong)param_2 - (longlong)puVar6;
        for (iVar9 = 0; iVar9 < (int)uVar12; iVar9 = iVar9 + 1) {
          uVar1 = *(ushort *)(lVar11 + (longlong)puVar6);
          uVar2 = *puVar6;
          puVar6 = puVar6 + 1;
          if (uVar1 != uVar2) {
            iVar8 = (uint)uVar1 - (uint)uVar2;
            break;
          }
        }
      }
      if (iVar8 < 0) {
        iVar13 = iVar4 + -1;
      }
      else {
        if (iVar8 < 1) break;
        iVar14 = iVar4 + 1;
      }
    }
    *param_3 = iVar4;
    uVar7 = (ulonglong)(iVar4 == -1);
  }
  return uVar7;
}


// FUN_18007b17c @ 18007b17c

undefined4 FUN_18007b17c(longlong *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*param_1 != 0) {
    uVar1 = *(undefined4 *)(*param_1 + 4);
  }
  return uVar1;
}


// FUN_18001f970 @ 18001f970

undefined4
FUN_18001f970(longlong *param_1,int param_2,longlong param_3,int param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  longlong lVar4;
  longlong lVar5;
  
  lVar4 = *param_1;
  uVar3 = 0;
  if (lVar4 == 0) {
    uVar3 = 0x80048001;
  }
  else if (((param_4 == *(int *)(lVar4 + 4)) && (-1 < param_2)) && (param_2 < *(int *)(lVar4 + 8)))
  {
    lVar5 = (longlong)param_2 * 0x10 + param_1[1];
    lVar4 = *(int *)(lVar5 + 0xc) + lVar4;
    iVar2 = FUN_18001fa3c(param_1,param_3,lVar4,*(int *)(lVar5 + 8));
    if (iVar2 == -1) {
      uVar3 = 1;
    }
    else {
      lVar5 = (longlong)iVar2;
      iVar2 = *(int *)(lVar4 + lVar5 * 0x10);
      if (iVar2 == 0) {
        uVar1 = *(undefined4 *)(lVar4 + 4 + lVar5 * 0x10);
        *param_5 = 0;
        param_5[2] = uVar1;
      }
      else if (iVar2 == 1) {
        *(longlong *)(param_5 + 2) = (longlong)*(int *)(lVar4 + 4 + lVar5 * 0x10) + *param_1 + 2;
        *param_5 = 1;
      }
      else {
        uVar3 = 0x80048011;
      }
    }
  }
  else {
    uVar3 = 0x80070057;
  }
  return uVar3;
}


