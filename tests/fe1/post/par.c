// FUN_1800b90a8 @ 1800b90a8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

longlong * FUN_1800b90a8(longlong *param_1,longlong param_2)

{
  int iVar1;
  uint uVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong *plVar6;
  ulonglong uVar7;
  undefined8 *puVar8;
  longlong *plVar9;
  longlong *plVar10;
  longlong *plVar11;
  longlong *plVar12;
  int local_res10 [2];
  longlong *local_res18;
  longlong *local_res20;
  longlong *local_58;
  undefined8 *local_50;
  longlong *local_48;
  longlong *local_40;
  
  plVar3 = (longlong *)0x0;
  if (param_2 == 0) {
    plVar3 = (longlong *)0x80070057;
  }
  else if ((int)param_1[1] == 0) {
    plVar3 = (longlong *)0x0;
  }
  else {
    local_50 = (undefined8 *)FUN_18014a13c(param_2);
    plVar4 = (longlong *)FUN_180034e44(param_2);
    plVar9 = plVar3;
    if (plVar4[2] != 0) {
      plVar9 = *(longlong **)(*plVar4 + 0x10);
    }
    lVar5 = FUN_180034e44(param_2);
    local_48 = (longlong *)0x0;
    if (*(longlong *)(lVar5 + 0x10) != 0) {
      local_48 = *(longlong **)(*(longlong *)(lVar5 + 8) + 0x10);
    }
    if (plVar9 != (longlong *)0x0) {
      do {
        plVar4 = (longlong *)0x0;
        if (plVar9 == local_48) break;
        if ((int)plVar3 < 0) {
          return plVar3;
        }
        iVar1 = FUN_1800b8af4(local_48,plVar9,(uint *)param_1[4],(ulonglong)*(uint *)(param_1 + 3));
        if (iVar1 != 0) {
          local_res10[0] = 0;
          plVar6 = FUN_1800b6688(plVar9);
          local_58 = (longlong *)0x0;
          local_res18 = (longlong *)((ulonglong)local_res18 & 0xffffffff00000000);
          local_res20 = (longlong *)0x0;
          plVar11 = plVar4;
          if (plVar6 != (longlong *)0x0) {
            local_40 = (longlong *)FUN_18007ca58(0x38);
            if (local_40 == (longlong *)0x0) {
              plVar3 = (longlong *)0x8007000e;
            }
            else {
              local_40[1] = 0;
              local_40[2] = 0;
              local_40[3] = 0;
              local_40[4] = 0;
              local_40[5] = 0;
              *(undefined4 *)(local_40 + 6) = 10;
              *local_40 = (longlong)CParallelStruct::vftable;
              plVar11 = local_40;
              local_res20 = local_40;
            }
          }
          plVar12 = plVar4;
          if (local_50[2] != 0) {
            plVar12 = *(longlong **)
                       (*(longlong *)
                         (*(longlong *)(*(longlong *)(local_50[1] + 0x10) + 0x10) + 0x10) + 8);
          }
LAB_1800b9282:
          if (plVar6 != (longlong *)0x0) {
            if (-1 < (int)plVar3) {
              if ((int)plVar4 != 1) {
                iVar1 = (**(code **)(*plVar6 + 0x270))(plVar6);
                plVar10 = plVar6;
                if (iVar1 != 0) goto LAB_1800b927a;
                uVar7 = FUN_1800b8d80((longlong)param_1,plVar12,plVar6,(longlong *)&local_58,
                                      (int *)&local_res18,local_res10);
                plVar3 = (longlong *)(uVar7 & 0xffffffff);
                if (-1 < (int)uVar7) {
                  if (local_res10[0] != 0) goto code_r0x0001800b925a;
                  goto LAB_1800b929b;
                }
                goto LAB_1800b9343;
              }
              goto LAB_1800b929b;
            }
            goto LAB_1800b9343;
          }
          if (-1 < (int)plVar3) {
LAB_1800b929b:
            if (local_res10[0] != 0) {
              if (1 < (ulonglong)plVar11[3]) {
                uVar2 = (**(code **)(*param_1 + 8))(param_1,plVar11,local_res10);
                plVar3 = (longlong *)(ulonglong)uVar2;
                if ((int)uVar2 < 0) goto LAB_1800b9343;
              }
              if (local_res10[0] != 0) {
                local_res18 = (longlong *)0x0;
                plVar3 = (longlong *)FUN_180045a04((longlong)(plVar9 + 1),0);
                uVar7 = FUN_1800b8ca4(param_1,plVar3,(longlong *)&local_res18,local_res10);
                plVar3 = (longlong *)(uVar7 & 0xffffffff);
                if ((int)uVar7 == 0) {
                  if (local_res10[0] != 0) {
                    uVar2 = FUN_1800b8a38((longlong)plVar11,plVar9,local_res18,3);
                    plVar4 = local_res18;
                    plVar3 = (longlong *)(ulonglong)uVar2;
                    if (-1 < (int)uVar2) {
                      puVar8 = FUN_18008b5e0(local_50,&local_res20);
                      plVar11 = local_res20;
                      plVar9 = plVar4;
                      if (puVar8 != (undefined8 *)0x0) goto LAB_1800b9338;
                      plVar3 = (longlong *)0x8007000e;
                    }
                  }
                }
                else if (-1 < (int)uVar7) {
LAB_1800b9338:
                  if (local_res10[0] != 0) goto LAB_1800b935b;
                }
              }
            }
          }
LAB_1800b9343:
          if (plVar11 != (longlong *)0x0) {
            (**(code **)*plVar11)(plVar11);
          }
        }
LAB_1800b935b:
        plVar9 = (longlong *)FUN_180045a04((longlong)(plVar9 + 1),0);
      } while (plVar9 != (longlong *)0x0);
      if ((int)plVar3 < 0) {
        return plVar3;
      }
    }
    uVar2 = (**(code **)*param_1)(param_1);
    plVar3 = (longlong *)(ulonglong)uVar2;
  }
  return plVar3;
code_r0x0001800b925a:
  plVar4 = (longlong *)((ulonglong)local_res18 & 0xffffffff);
  uVar2 = FUN_1800b897c((longlong)plVar11,local_58,plVar6,local_res18._0_4_);
  plVar3 = (longlong *)(ulonglong)uVar2;
  plVar10 = local_58;
  if (-1 < (int)uVar2) {
LAB_1800b927a:
    plVar6 = FUN_1800b6688(plVar10);
  }
  goto LAB_1800b9282;
}


