// FUN_1800cd820 @ 1800cd820

ulonglong FUN_1800cd820(undefined8 param_1,longlong param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  longlong *local_res10 [3];
  
  if ((((param_2 == 0) || (param_3 == 0)) || (param_4 == 0)) ||
     (((param_2 != param_3 || ((longlong *)(param_4 + 0x20) == (longlong *)0x0)) ||
      (*(longlong *)(param_4 + 0x28) != 0)))) {
    uVar1 = 0x80070057;
  }
  else {
    local_res10[0] = (longlong *)FUN_18007ca58(0x48);
    if (local_res10[0] != (longlong *)0x0) {
      local_res10[0][1] = 0;
      local_res10[0][2] = 0;
      local_res10[0][3] = 0;
      *(undefined4 *)(local_res10[0] + 4) = 0;
      local_res10[0][5] = 0;
      local_res10[0][6] = 0;
      local_res10[0][7] = 0;
      *(undefined4 *)(local_res10[0] + 8) = 0;
      if (local_res10[0] != (longlong *)0x0) {
        *local_res10[0] = param_2 + 0x38;
        uVar1 = FUN_1800cb868((longlong *)(param_4 + 0x20),local_res10);
        uVar2 = uVar1 & 0xffffffff;
        if (-1 < (int)uVar1) {
          return uVar2;
        }
        if (local_res10[0] == (longlong *)0x0) {
          return uVar2;
        }
        FUN_1800cb83c((longlong)local_res10[0]);
        return uVar2;
      }
    }
    uVar1 = 0x8007000e;
  }
  return uVar1;
}


// FUN_1800e39f0 @ 1800e39f0

undefined8 FUN_1800e39f0(longlong param_1)

{
  uint uVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined8 uVar4;
  void *_Dst;
  ulonglong uVar5;
  void *pvVar6;
  ulonglong uVar7;
  void *pvVar8;
  size_t _Size;
  
  pvVar6 = (void *)0x0;
  if (*(longlong *)(param_1 + 0x18) == 0) {
    uVar1 = *(uint *)(param_1 + 0x28);
    uVar5 = 8;
    uVar7 = CONCAT44(0,uVar1);
    uVar4 = FUN_180009930(8,(ulonglong)uVar1);
    if ((int)uVar4 == 0) {
      *(undefined8 *)(param_1 + 0x18) = 0;
    }
    else {
      auVar2._8_8_ = 0;
      auVar2._0_8_ = uVar5 & 0xffffffff;
      auVar3._8_8_ = 0;
      auVar3._0_8_ = uVar7;
      _Size = SUB168(auVar2 * auVar3,0);
      if (SUB168(auVar2 * auVar3,8) != 0) {
        _Size = uVar5 - 9;
      }
      _Dst = (void *)thunk_FUN_18007ca58(_Size);
      pvVar8 = pvVar6;
      if (_Dst != (void *)0x0) {
        memset(_Dst,0,_Size);
        pvVar8 = _Dst;
      }
      *(void **)(param_1 + 0x18) = pvVar8;
      if (pvVar8 != (void *)0x0) {
        if (uVar1 == 0) {
          return 0;
        }
        do {
          *(undefined4 *)((longlong)pvVar6 + *(longlong *)(param_1 + 0x18)) = 0xffff;
          pvVar6 = (void *)((longlong)pvVar6 + 8);
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
        return 0;
      }
    }
    uVar4 = 0x8007000e;
  }
  else {
    uVar4 = 0x80048011;
  }
  return uVar4;
}


// FUN_1800e392c @ 1800e392c

ulonglong FUN_1800e392c(longlong param_1,undefined4 param_2)

{
  undefined4 uVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  ulonglong *puVar5;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    puVar4 = (undefined8 *)FUN_18007ca58(0x20);
    if (puVar4 == (undefined8 *)0x0) {
      *(undefined8 *)(param_1 + 0x10) = 0;
    }
    else {
      *(undefined4 *)(puVar4 + 1) = 0;
      *(undefined4 *)((longlong)puVar4 + 0xc) = 0;
      puVar4[2] = 0;
      puVar4[3] = 0;
      *puVar4 = CCRFLattice::vftable;
      *(undefined8 **)(param_1 + 0x10) = puVar4;
      if (puVar4 != (undefined8 *)0x0) {
        uVar1 = *(undefined4 *)(param_1 + 0x28);
        FUN_1800e58e0((longlong)puVar4);
        *(undefined4 *)(puVar4 + 1) = uVar1;
        *(undefined4 *)((longlong)puVar4 + 0xc) = param_2;
        puVar5 = FUN_1800e55bc((longlong)puVar4);
        uVar3 = (ulonglong)puVar5 & 0xffffffff;
        if (-1 < (int)puVar5) {
          uVar2 = FUN_1800e543c((longlong)puVar4);
          uVar3 = (ulonglong)uVar2;
          if (-1 < (int)uVar2) {
            return uVar3;
          }
        }
        FUN_1800e58e0((longlong)puVar4);
        return uVar3;
      }
    }
    uVar3 = 0x8007000e;
  }
  else {
    uVar3 = 0x80048011;
  }
  return uVar3;
}


// FUN_1800e378c @ 1800e378c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8 FUN_1800e378c(longlong *param_1,ulonglong param_2)

{
  undefined8 uVar1;
  
  uVar1 = (**(code **)(*param_1 + 0x40))();
  if (-1 < (int)uVar1) {
    if (*(int *)(param_2 + 8) == 0) {
      uVar1 = FUN_1800e2fa8((longlong)param_1,param_2);
    }
    else {
      uVar1 = FUN_1800e3188((longlong)param_1,param_2);
    }
    if ((-1 < (int)uVar1) && (1 < *(ulonglong *)(param_2 + 0x40))) {
      if ((*(int *)(param_2 + 0x28) != 0) && (*(int *)(param_1[1] + 0x68) != 0)) {
        FUN_1800e2c3c((longlong)param_1,param_2);
        FUN_1800e2d24((longlong)param_1,param_2);
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}


// FUN_1800e46b0 @ 1800e46b0

int FUN_1800e46b0(longlong param_1)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  undefined8 uVar4;
  uint *puVar5;
  float fVar6;
  int iVar7;
  longlong lVar8;
  longlong lVar9;
  longlong *plVar10;
  float *pfVar11;
  ulonglong uVar12;
  longlong lVar13;
  uint uVar14;
  uint uVar15;
  double dVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  uint local_res18;
  uint local_res20;
  ulonglong local_c0;
  longlong local_b0;
  ulonglong local_88;
  undefined8 local_80;
  longlong local_78;
  longlong local_70;
  undefined8 local_68;
  undefined4 local_60;
  
  if (param_1 == 0) {
    return -0x7ff8ffa9;
  }
  uVar1 = *(uint *)(param_1 + 0x28);
  lVar2 = *(longlong *)(param_1 + 0x10);
  uVar14 = *(uint *)(lVar2 + 0xc);
  lVar3 = *(longlong *)(param_1 + 0x18);
  uVar4 = *(undefined8 *)(param_1 + 0x40);
  if (lVar3 == 0) {
    return -0x7ff8ffa9;
  }
  if (*(longlong *)(lVar2 + 0x10) == 0) {
    return -0x7ff8ffa9;
  }
  iVar7 = 0;
  uVar15 = 0;
  if (uVar14 != 0) {
    lVar13 = 0;
    do {
      if (iVar7 < 0) break;
      lVar9 = **(longlong **)(lVar2 + 0x10) + lVar13;
      iVar7 = FUN_1800e4624(lVar9,0,*(undefined4 *)(lVar9 + 0x10));
      dVar16 = FUN_1800e4654((double)*(float *)(lVar3 + 4),(double)*(float *)(lVar9 + 0x10),
                             (uint)(uVar15 == 0));
      *(float *)(lVar3 + 4) = (float)dVar16;
      uVar15 = uVar15 + 1;
      lVar13 = lVar13 + 0x60;
    } while (uVar15 < uVar14);
  }
  fVar6 = DAT_180194104;
  local_res20 = 1;
  if (1 < uVar1) {
    pfVar11 = (float *)(lVar3 + 0xc);
    do {
      if (iVar7 < 0) break;
      uVar15 = 0;
      if (uVar14 != 0) {
        local_b0 = 0;
        do {
          if (iVar7 < 0) break;
          lVar13 = *(longlong *)(*(longlong *)(lVar2 + 0x10) + (-4 - lVar3) + (longlong)pfVar11) +
                   local_b0;
          plVar10 = *(longlong **)(lVar13 + 0x20);
          if (*(float *)(lVar13 + 0x10) <= fVar6) {
            iVar7 = FUN_1800e4624(lVar13,*(undefined8 *)(*(longlong *)(*plVar10 + 8) + 0x38),fVar6);
          }
          else {
            local_res18 = 0;
            do {
              if (iVar7 < 0) break;
              lVar9 = *(longlong *)(*plVar10 + 8);
              if (lVar9 == 0) {
                iVar7 = -0x7fff0001;
              }
              uVar12 = -(ulonglong)(lVar9 != 0) & lVar9 + 0x28U;
              local_c0 = 0;
              if (*(longlong *)(uVar12 + 0x18) != 0) {
                lVar9 = 0;
                do {
                  if (iVar7 < 0) break;
                  lVar8 = *(longlong *)(uVar12 + 0x10) + lVar9;
                  iVar7 = FUN_1800e4624(lVar13,lVar8,
                                        *(float *)(lVar8 + 0x10) + *(float *)*plVar10 +
                                        *(float *)(lVar13 + 0x10));
                  local_c0 = local_c0 + 1;
                  lVar9 = lVar9 + 0x18;
                } while (local_c0 < *(ulonglong *)(uVar12 + 0x18));
              }
              local_res18 = local_res18 + 1;
              plVar10 = plVar10 + 1;
            } while (local_res18 < uVar14);
          }
          if (*(longlong *)(param_1 + 0x40) == 1) {
            dVar16 = FUN_1800e4654((double)*pfVar11,
                                   (double)*(float *)(*(longlong *)(lVar13 + 0x38) + 0x10),
                                   (uint)(uVar15 == 0));
            *pfVar11 = (float)dVar16;
          }
          uVar15 = uVar15 + 1;
          local_b0 = local_b0 + 0x60;
        } while (uVar15 < uVar14);
      }
      local_res20 = local_res20 + 1;
      pfVar11 = pfVar11 + 2;
    } while (local_res20 < uVar1);
  }
  local_88 = 0;
  local_78 = 0;
  local_70 = 0;
  local_68 = 0;
  local_60 = 0;
  local_80 = uVar4;
  if (uVar14 != 0) {
    lVar13 = 0;
    uVar15 = 0;
    if (-1 < iVar7) {
      do {
        lVar9 = *(longlong *)(*(longlong *)(lVar2 + 0x10) + (ulonglong)(uVar1 - 1) * 8);
        uVar12 = 0;
        if (*(longlong *)(lVar9 + 0x40 + lVar13) != 0) {
          lVar8 = 0;
          do {
            FUN_1800e57ec(&local_88,(undefined8 *)(*(longlong *)(lVar9 + 0x38 + lVar13) + lVar8));
            uVar12 = uVar12 + 1;
            lVar8 = lVar8 + 0x18;
          } while (uVar12 < *(ulonglong *)(lVar9 + 0x40 + lVar13));
        }
        uVar15 = uVar15 + 1;
        lVar13 = lVar13 + 0x60;
      } while (uVar15 < uVar14);
    }
  }
  lVar13 = local_70;
  uVar12 = local_88;
  uVar17 = 0;
  uVar18 = 0;
  if ((-1 < iVar7) && (1 < *(ulonglong *)(param_1 + 0x40))) {
    uVar14 = *(uint *)(lVar2 + 0xc);
    uVar15 = 0;
    if (uVar14 != 0) {
      pfVar11 = (float *)(**(longlong **)(lVar2 + 0x10) + 0xc);
      do {
        dVar16 = FUN_1800e4654((double)CONCAT44(uVar18,uVar17),(double)*pfVar11,(uint)(uVar15 == 0))
        ;
        uVar17 = SUB84(dVar16,0);
        uVar18 = (undefined4)((ulonglong)dVar16 >> 0x20);
        uVar15 = uVar15 + 1;
        pfVar11 = pfVar11 + 0x18;
      } while (uVar15 < uVar14);
    }
  }
  plVar10 = (longlong *)0x0;
  if (lVar13 != 0) {
    plVar10 = (longlong *)(local_78 + uVar12 * 0x18);
  }
  uVar14 = uVar1;
  uVar15 = uVar1;
  if (plVar10 == (longlong *)0x0) {
LAB_1800e4b20:
    if (iVar7 < 0) goto LAB_1800e4b2f;
  }
  else {
    do {
      uVar15 = uVar14 - 1;
      if (uVar14 == 0) goto LAB_1800e4b20;
      if (iVar7 < 0) goto LAB_1800e4b2f;
      puVar5 = (uint *)plVar10[1];
      if (uVar1 <= *puVar5) {
        iVar7 = -0x7fff0001;
        goto LAB_1800e4b2f;
      }
      *(uint *)(lVar3 + (ulonglong)*puVar5 * 8) = puVar5[1];
      if (*(ulonglong *)(param_1 + 0x40) < 2) {
        uVar14 = *puVar5;
        dVar16 = (double)_o_exp((double)(*(float *)(*(longlong *)(puVar5 + 0xe) + 0x10) -
                                        *(float *)(lVar3 + 4 + (ulonglong)uVar14 * 8)));
        *(float *)(lVar3 + 4 + (ulonglong)uVar14 * 8) = (float)dVar16;
      }
      else {
        dVar16 = (double)_o_exp((double)(((float)puVar5[3] + (float)puVar5[2]) - (float)puVar5[4]) -
                                (double)CONCAT44(uVar18,uVar17));
        *(float *)(lVar3 + 4 + (ulonglong)*puVar5 * 8) = (float)dVar16;
      }
      plVar10 = (longlong *)*plVar10;
      uVar14 = uVar15;
    } while (plVar10 != (longlong *)0x0);
  }
  if (uVar15 != 0) {
    iVar7 = -0x7fff0001;
  }
LAB_1800e4b2f:
  FUN_18001d7d0(&local_78);
  return iVar7;
}


// FUN_1800e3db8 @ 1800e3db8

ulonglong FUN_1800e3db8(longlong param_1,int *param_2,TypeDescriptor *param_3,
                       TypeDescriptor *param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  TypeDescriptor *pTVar3;
  
  if ((param_2 == (int *)0x0) || (param_3 == (TypeDescriptor *)0x0)) {
    uVar2 = 0x80070057;
  }
  else {
    pTVar3 = param_3;
    uVar1 = FUN_18008a5bc(param_2,0x18018a550,param_3,param_4);
    uVar2 = uVar1 & 0xffffffff;
    if (-1 < (int)uVar1) {
      uVar1 = FUN_1800e3e64(param_1,param_2,pTVar3,param_4);
      uVar2 = uVar1 & 0xffffffff;
      if (-1 < (int)uVar1) {
        uVar1 = FUN_1800e3ac4(param_1,param_2,(longlong)param_3,param_4);
        uVar2 = uVar1 & 0xffffffff;
        if (-1 < (int)uVar1) {
          uVar1 = FUN_1800e3f70(param_1,param_2,(longlong)param_3,param_4);
          uVar2 = uVar1 & 0xffffffff;
          if (-1 < (int)uVar1) {
            FUN_18008a5bc(param_2,0x18018a528,param_3,param_4);
          }
        }
      }
    }
  }
  return uVar2;
}


