// FUN_1800b8608 @ 1800b8608

longlong * FUN_1800b8608(int *param_1,longlong param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  longlong lVar3;
  uint uVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  short *psVar8;
  short *psVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  longlong *plVar12;
  longlong *plVar13;
  undefined8 *local_res10;
  longlong *local_58;
  undefined8 uStack_50;
  longlong local_48;
  undefined8 local_40;
  undefined8 uStack_38;
  undefined4 local_30;
  
  plVar5 = (longlong *)0x0;
  if (param_2 == 0) {
    plVar5 = (longlong *)0x80070057;
  }
  else if (*param_1 == 0) {
    plVar5 = (longlong *)0x80048001;
  }
  else {
    plVar6 = (longlong *)FUN_18014a1d8(param_2);
    FUN_18007a47c(plVar6);
    plVar7 = (longlong *)FUN_180034e44(param_2);
    plVar12 = plVar5;
    if (plVar7[2] != 0) {
      plVar12 = *(longlong **)(*plVar7 + 0x10);
    }
    local_58 = (longlong *)0x0;
    uStack_50 = 0;
    local_48 = 0;
    local_40 = 0;
    uStack_38 = 0;
    local_30 = 10;
    plVar7 = plVar5;
    do {
      if (plVar12 == (longlong *)0x0) break;
      psVar8 = FUN_1800b8364((longlong)param_1,plVar12);
      if (psVar8 != (short *)0x0) {
        plVar5 = local_58;
        psVar9 = psVar8;
        if (*(int *)(psVar8 + 2) != 0) {
          psVar9 = FUN_1800b832c((longlong)param_1,psVar8[1]);
          plVar5 = local_58;
        }
        do {
          plVar13 = (longlong *)0x0;
          if (plVar5 == (longlong *)0x0) goto LAB_1800b876f;
          puVar1 = (undefined8 *)plVar5[2];
          plVar13 = (longlong *)*plVar5;
          plVar5 = plVar13;
        } while ((short *)puVar1[1] != psVar9);
        if (puVar1 == (undefined8 *)0x0) {
LAB_1800b876f:
          uVar4 = FUN_1800b8818(plVar13,psVar8,plVar12,plVar7,(longlong *)&local_58);
          plVar5 = (longlong *)(ulonglong)uVar4;
        }
        else {
          uVar4 = FUN_1800b8574(plVar13,(longlong *)&local_58,(longlong)puVar1);
          plVar5 = (longlong *)(ulonglong)uVar4;
          if (-1 < (int)uVar4) {
            puVar10 = (undefined8 *)FUN_18007ca58(0x20);
            if (puVar10 == (undefined8 *)0x0) {
              local_res10 = (undefined8 *)0x0;
            }
            else {
              uVar2 = *puVar1;
              *puVar10 = puVar1[2];
              puVar10[1] = uVar2;
              puVar10[2] = plVar12;
              puVar10[3] = plVar7;
              local_res10 = puVar10;
              puVar11 = FUN_18008b5e0(plVar6,&local_res10);
              if (puVar11 != (undefined8 *)0x0) goto LAB_1800b8760;
              _o_free(puVar10,0x20);
            }
            plVar5 = (longlong *)0x8007000e;
          }
LAB_1800b8760:
          _o_free(puVar1);
        }
      }
      plVar12 = (longlong *)FUN_180045a04((longlong)(plVar12 + 1),0);
      plVar7 = (longlong *)((longlong)plVar7 + 1);
    } while (-1 < (int)plVar5);
    while (plVar12 = local_58, local_48 != 0) {
      lVar3 = local_58[2];
      local_58 = (longlong *)*local_58;
      if (local_58 == (longlong *)0x0) {
        uStack_50 = 0;
      }
      else {
        local_58[1] = 0;
      }
      FUN_18007a918((longlong)&local_58,plVar12);
      if (lVar3 != 0) {
        _o_free(lVar3,0x18);
      }
    }
    FUN_1800192f8(&local_58);
  }
  return plVar5;
}


