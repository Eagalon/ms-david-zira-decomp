// FUN_1800e2fa8 @ 1800e2fa8

undefined8 FUN_1800e2fa8(longlong param_1,ulonglong param_2)

{
  uint uVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  uint uVar9;
  longlong *plVar10;
  uint uVar11;
  longlong lVar12;
  float fVar13;
  undefined8 uVar14;
  ulonglong local_res10;
  uint local_res18 [2];
  ulonglong local_res20;
  ulonglong local_68;
  
  local_res18[0] = *(uint *)(param_2 + 0x28);
  local_68 = (ulonglong)local_res18[0];
  uVar1 = *(uint *)(*(longlong *)(param_1 + 8) + 0x68);
  lVar2 = *(longlong *)(param_2 + 0x10);
  uVar3 = *(undefined8 *)(param_2 + 0x40);
  if (local_res18[0] != 0) {
    lVar7 = 0;
    local_res10 = param_2;
    do {
      uVar9 = 0;
      lVar6 = *(longlong *)(lVar7 + *(longlong *)(param_2 + 0x20));
      if (uVar1 != 0) {
        lVar12 = 0;
        do {
          local_res20 = (ulonglong)uVar9;
          uVar14 = FUN_1800e2f60(param_1,(undefined8 *)(lVar6 + 8),(int *)&local_res20);
          uVar9 = uVar9 + 1;
          *(int *)(*(longlong *)(*(longlong *)(lVar2 + 0x10) + lVar7) + -0x50 + lVar12 + 0x60) =
               (int)uVar14;
          lVar4 = *(longlong *)(*(longlong *)(lVar2 + 0x10) + lVar7);
          *(undefined8 *)(lVar12 + 0x58 + lVar4) = uVar3;
          *(undefined8 *)(lVar12 + 0x30 + lVar4) = uVar3;
          param_2 = local_res10;
          lVar12 = lVar12 + 0x60;
        } while (uVar9 < uVar1);
      }
      lVar7 = lVar7 + 8;
      local_68 = local_68 - 1;
    } while (local_68 != 0);
    if (1 < local_res18[0]) {
      lVar7 = *(longlong *)(param_2 + 0x20);
      local_res20 = (ulonglong)(local_res18[0] - 1);
      lVar6 = 8;
      do {
        lVar12 = *(longlong *)(lVar6 + lVar7);
        uVar9 = 0;
        if (uVar1 != 0) {
          lVar4 = *(longlong *)(lVar6 + *(longlong *)(lVar2 + 0x10));
          lVar8 = 0;
          do {
            uVar11 = 0;
            plVar10 = (longlong *)(lVar4 + 0x20);
            do {
              local_res18[1] = 0;
              local_res10 = (ulonglong)uVar11;
              local_res18[0] = uVar9;
              fVar13 = FUN_1800e2e68(param_1,(undefined8 *)(lVar12 + 0x28),(int *)local_res18,
                                     (int *)&local_res10);
              lVar5 = *plVar10;
              uVar11 = uVar11 + 1;
              plVar10 = plVar10 + 0xc;
              **(float **)(lVar8 + lVar5) = fVar13;
            } while (uVar11 < uVar1);
            uVar9 = uVar9 + 1;
            lVar8 = lVar8 + 8;
          } while (uVar9 < uVar1);
        }
        lVar6 = lVar6 + 8;
        local_res20 = local_res20 - 1;
      } while (local_res20 != 0);
    }
  }
  return 0;
}


// FUN_1800e3188 @ 1800e3188

undefined8 FUN_1800e3188(longlong param_1,longlong param_2)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  int iVar4;
  ulonglong uVar5;
  longlong *plVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  longlong lVar10;
  longlong lVar11;
  uint uVar12;
  undefined8 uVar13;
  float fVar14;
  longlong *local_res18;
  uint local_res20;
  int local_88 [4];
  longlong local_78;
  longlong local_70;
  longlong local_68;
  longlong *local_60;
  
  uVar8 = *(uint *)(param_2 + 0x28);
  uVar12 = 0;
  lVar3 = *(longlong *)(param_2 + 0x10);
  iVar1 = *(int *)(lVar3 + 0x44);
  uVar2 = *(uint *)(*(longlong *)(param_1 + 8) + 0x68);
  if (uVar8 != 0) {
    lVar10 = 0;
    lVar11 = 0;
    local_res20 = uVar8;
    do {
      uVar7 = 0;
      local_res18 = (longlong *)0x0;
      fVar14 = 0.0;
      local_70 = *(longlong *)(lVar11 + *(longlong *)(param_2 + 0x20));
      if (uVar2 != 0) {
        local_68 = 0;
        do {
          uVar8 = local_res20;
          if (*(uint *)(lVar10 + *(longlong *)(lVar3 + 0x10)) <= uVar7) break;
          iVar9 = iVar1;
          if (uVar7 != 0) {
            iVar9 = 1 - iVar1;
          }
          local_res18 = (longlong *)CONCAT44(local_res18._4_4_,iVar9);
          uVar13 = FUN_1800e2f60(param_1,(undefined8 *)(local_70 + 8),(int *)&local_res18);
          fVar14 = (float)uVar13;
          if (uVar12 == 0) {
            uVar13 = FUN_1800e2ec8(param_1,(longlong *)(local_70 + 8),param_2,0,1,
                                   (int *)&local_res18);
            fVar14 = fVar14 + (float)uVar13;
          }
          uVar7 = uVar7 + 1;
          *(float *)(*(longlong *)(*(longlong *)(lVar3 + 0x30) + lVar11) + 0x10 + local_68) = fVar14
          ;
          local_68 = local_68 + 0x60;
          uVar8 = local_res20;
        } while (uVar7 < uVar2);
      }
      uVar7 = uVar2;
      if (uVar2 < *(uint *)(lVar10 + *(longlong *)(lVar3 + 0x10))) {
        do {
          uVar5 = (ulonglong)uVar7;
          uVar7 = uVar7 + 1;
          *(float *)(*(longlong *)(lVar11 + *(longlong *)(lVar3 + 0x30)) + 0x10 + uVar5 * 0x60) =
               fVar14;
        } while (uVar7 < *(uint *)(lVar10 + *(longlong *)(lVar3 + 0x10)));
      }
      uVar12 = uVar12 + 1;
      lVar11 = lVar11 + 8;
      lVar10 = lVar10 + 4;
    } while (uVar12 < uVar8);
    uVar12 = 1;
    if (1 < uVar8) {
      lVar10 = *(longlong *)(lVar3 + 0x10);
      local_68 = 4;
      iVar9 = 1 - iVar1;
      lVar11 = 8;
      local_70 = 0;
      do {
        uVar8 = 0;
        fVar14 = 0.0;
        local_88[2] = 0;
        local_88[3] = 0;
        local_88[1] = 0;
        local_78 = *(longlong *)(lVar11 + *(longlong *)(param_2 + 0x20));
        local_res18 = (longlong *)((ulonglong)local_res18 & 0xffffffff00000000);
        if (*(int *)(local_70 + lVar10) != 0) {
          plVar6 = (longlong *)(local_78 + 8);
          local_60 = plVar6;
          local_88[0] = iVar1;
          do {
            if (uVar8 < uVar2) {
              iVar4 = iVar9;
              if (uVar8 == 0) {
                iVar4 = iVar1;
              }
              local_88[2] = iVar4;
              fVar14 = FUN_1800e2e68(param_1,(undefined8 *)(local_78 + 0x28),local_88 + 2,local_88);
              plVar6 = local_60;
            }
            uVar8 = uVar8 + 1;
            uVar13 = FUN_1800e2ec8(param_1,plVar6,param_2,uVar12,uVar8,local_88);
            uVar5 = (ulonglong)local_res18 & 0xffffffff;
            local_res18 = (longlong *)CONCAT44(local_res18._4_4_,uVar8);
            plVar6 = (longlong *)(local_78 + 8);
            **(float **)
              (*(longlong *)(*(longlong *)(lVar11 + *(longlong *)(lVar3 + 0x30)) + 0x20) + uVar5 * 8
              ) = (float)uVar13 + fVar14;
            lVar10 = *(longlong *)(lVar3 + 0x10);
          } while (uVar8 < *(uint *)(local_70 + lVar10));
        }
        local_88[0] = iVar9;
        if (1 < *(uint *)(local_68 + lVar10)) {
          local_res18 = (longlong *)(local_78 + 8);
          uVar5 = 1;
          do {
            uVar8 = (uint)uVar5;
            if (uVar8 - 1 < uVar2) {
              iVar4 = iVar9;
              if (uVar8 == 1) {
                iVar4 = iVar1;
              }
              local_88[2] = iVar4;
              fVar14 = FUN_1800e2e68(param_1,(undefined8 *)(local_78 + 0x28),local_88 + 2,local_88);
            }
            uVar13 = FUN_1800e2ec8(param_1,local_res18,param_2,uVar12,uVar8,local_88);
            lVar10 = *(longlong *)(lVar3 + 0x10);
            *(float *)**(undefined8 **)
                        (*(longlong *)(lVar11 + *(longlong *)(lVar3 + 0x30)) + 0x20 + uVar5 * 0x60)
                 = (float)uVar13 + fVar14;
            uVar5 = (ulonglong)(uVar8 + 1);
          } while (uVar8 + 1 < *(uint *)(local_68 + lVar10));
        }
        local_70 = local_70 + 4;
        local_68 = local_68 + 4;
        uVar12 = uVar12 + 1;
        lVar11 = lVar11 + 8;
      } while (uVar12 < local_res20);
    }
  }
  return 0;
}


