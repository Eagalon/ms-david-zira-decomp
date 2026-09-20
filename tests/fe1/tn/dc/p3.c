// FUN_18000ed84 @ 18000ed84

int FUN_18000ed84(undefined8 param_1,ushort param_2,uint param_3,longlong param_4,ushort *param_5)

{
  longlong lVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  ulonglong uVar5;
  uint uVar6;
  
  uVar5 = (ulonglong)param_2;
  if (0x200 < param_3) {
    return 1;
  }
  uVar6 = 1;
  iVar3 = 0;
  if (*param_5 <= param_2) {
    while( true ) {
      if ((param_2 == 0xffff) ||
         (lVar1 = *(longlong *)
                   (*(longlong *)(param_5 + 4) +
                   (ulonglong)((ushort)(param_2 - *param_5) >> 0xe) * 8) +
                  (ulonglong)((ushort)(param_2 - *param_5) & 0x3fff) * 0x12, lVar1 == 0))
      goto LAB_18000ee09;
      uVar2 = *(ushort *)(lVar1 + 0xc);
      if (uVar2 != 0) break;
      uVar6 = uVar6 + 1;
LAB_18000ee35:
      param_2 = *(ushort *)(lVar1 + 0x10);
    }
    if (*(int *)(param_4 + (ulonglong)uVar2 * 4) == 0) {
      iVar3 = FUN_18000ed84(param_1,uVar2,param_3 + 1,param_4,param_5);
    }
    uVar4 = *(int *)(param_4 + (ulonglong)*(ushort *)(lVar1 + 0xc) * 4) + 1;
    if (uVar6 < uVar4) {
      uVar6 = uVar4;
    }
    if (uVar6 + param_3 < 0x201) {
      if (iVar3 != 0) goto LAB_18000ee09;
      if (*(int *)(param_4 + (ulonglong)*(ushort *)(lVar1 + 0xe) * 4) == 0) {
        iVar3 = FUN_18000ed84(param_1,*(ushort *)(lVar1 + 0xe),param_3 + 1,param_4,param_5);
      }
      uVar4 = *(int *)(param_4 + (ulonglong)*(ushort *)(lVar1 + 0xe) * 4) + 1;
      if (uVar6 < uVar4) {
        uVar6 = uVar4;
      }
      if (uVar6 + param_3 < 0x201) {
        if (iVar3 == 0) goto LAB_18000ee35;
        goto LAB_18000ee09;
      }
    }
    iVar3 = 1;
  }
LAB_18000ee09:
  *(uint *)(param_4 + uVar5 * 4) = uVar6;
  return iVar3;
}


// FUN_18000e440 @ 18000e440

int FUN_18000e440(undefined8 param_1,ushort param_2,undefined8 *param_3,longlong param_4,
                 ushort *param_5)

{
  short *psVar1;
  longlong lVar2;
  undefined1 auVar3 [16];
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined8 *puVar7;
  void *_Dst;
  ushort uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  ushort uVar11;
  ulonglong uVar12;
  
  iVar4 = 0;
  uVar12 = 0;
  uVar10 = (ulonglong)param_2;
  uVar9 = param_1;
  if ((param_2 != 0xffff) &&
     (lVar6 = *(longlong *)
               (*(longlong *)(param_5 + 4) + (ulonglong)((ushort)(param_2 - *param_5) >> 0xe) * 8) +
              (ulonglong)((ushort)(param_2 - *param_5) & 0x3fff) * 0x12, lVar6 != 0)) {
    do {
      uVar5 = FUN_18000ecb4(uVar9,(ushort)uVar10,param_5);
      uVar10 = (ulonglong)*(ushort *)(lVar6 + 0x10);
      uVar11 = (ushort)uVar12 + 1;
      if ((int)uVar5 != 0) {
        uVar11 = (ushort)uVar12;
      }
      uVar12 = CONCAT62(0,uVar11);
      lVar6 = FUN_18000f1f0((short *)param_5,*(ushort *)(lVar6 + 0x10));
    } while (lVar6 != 0);
    if (1 < uVar11) {
      puVar7 = (undefined8 *)FUN_18007ca58(0x40);
      if (puVar7 == (undefined8 *)0x0) {
        *param_3 = 0;
      }
      else {
        *puVar7 = 0xffffffffffffffff;
        *(undefined2 *)(puVar7 + 1) = 0;
        *(undefined4 *)((longlong)puVar7 + 0xc) = 3;
        *(undefined4 *)(puVar7 + 4) = 3;
        *(undefined2 *)(puVar7 + 2) = 0;
        *(undefined2 *)(puVar7 + 7) = 1;
        *(undefined2 *)((longlong)puVar7 + 0x12) = 0xffff;
        puVar7[3] = 0;
        *(undefined2 *)((longlong)puVar7 + 0x24) = 0;
        puVar7[5] = 0;
        puVar7[6] = 0;
        *(undefined4 *)((longlong)puVar7 + 0x3c) = 0;
        *param_3 = puVar7;
        if (puVar7 != (undefined8 *)0x0) {
          *(undefined4 *)((longlong)puVar7 + 0xc) = 1;
          auVar3._8_8_ = 0;
          auVar3._0_8_ = uVar12;
          lVar6 = SUB168(ZEXT416(8) * auVar3,0);
          *(undefined2 *)(puVar7 + 1) = 0xffff;
          *(ushort *)(puVar7 + 2) = uVar11;
          if (SUB168(ZEXT416(8) * auVar3,8) != 0) {
            lVar6 = -1;
          }
          _Dst = (void *)thunk_FUN_18007ca58(lVar6);
          puVar7[3] = _Dst;
          if (_Dst == (void *)0x0) {
            iVar4 = -0x7ff8fff2;
            *(undefined2 *)(puVar7 + 2) = 0;
          }
          else {
            memset(_Dst,0,(longlong)*(short *)(puVar7 + 2) << 3);
            uVar10 = (ulonglong)param_2;
            lVar6 = FUN_18000f1f0((short *)param_5,param_2);
            *(undefined2 *)puVar7 = *(undefined2 *)(lVar6 + 2);
            *(undefined2 *)((longlong)puVar7 + 4) = *(undefined2 *)(lVar6 + 6);
            *(undefined2 *)((longlong)puVar7 + 6) = *(undefined2 *)(lVar6 + 8);
            *(ushort *)((longlong)puVar7 + 2) = param_2;
            if (*(short *)(puVar7 + 1) == -1) {
              *(undefined2 *)(puVar7 + 1) = *(undefined2 *)(lVar6 + 10);
            }
            uVar11 = 0;
            do {
              uVar8 = (ushort)uVar10;
              if ((iVar4 < 0) || ((int)*(short *)(puVar7 + 2) <= (int)(uint)uVar11)) break;
              if ((uVar8 == param_2) || (param_4 == 0)) {
LAB_18000e64d:
                uVar9 = param_1;
                uVar5 = FUN_18000ecb4(param_1,uVar8,param_5);
                if ((int)uVar5 == 0) {
                  iVar4 = FUN_18000e708(uVar9,uVar8,
                                        (undefined8 *)(puVar7[3] + (ulonglong)uVar11 * 8),param_4,
                                        param_5);
                }
              }
              else {
                lVar2 = *(longlong *)(param_4 + (uVar10 & 0xffff) * 8);
                if (lVar2 == 0) goto LAB_18000e64d;
                *(longlong *)(puVar7[3] + (ulonglong)uVar11 * 8) = lVar2;
                psVar1 = (short *)(*(longlong *)(param_4 + (uVar10 & 0xffff) * 8) + 0x38);
                *psVar1 = *psVar1 + 1;
              }
              uVar10 = (ulonglong)*(ushort *)(lVar6 + 0x10);
              lVar6 = FUN_18000f1f0((short *)param_5,*(ushort *)(lVar6 + 0x10));
              uVar11 = uVar11 + 1;
            } while (lVar6 != 0);
          }
          goto LAB_18000e6dc;
        }
      }
      iVar4 = -0x7ff8fff2;
      goto LAB_18000e6dc;
    }
  }
  iVar4 = FUN_18000e708(uVar9,param_2,param_3,param_4,param_5);
LAB_18000e6dc:
  if (param_4 != 0) {
    *(undefined8 *)(param_4 + (ulonglong)param_2 * 8) = *param_3;
  }
  return iVar4;
}


// FUN_1801376cc @ 1801376cc

ulonglong FUN_1801376cc(longlong *param_1,longlong param_2,undefined8 *param_3,ushort *param_4)

{
  longlong lVar1;
  uint uVar2;
  uint extraout_EAX;
  ulonglong uVar3;
  uint uVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  ushort uVar8;
  ulonglong uVar9;
  int iVar10;
  ulonglong uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  uint local_res10 [2];
  int local_res18 [2];
  longlong *local_res20;
  
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = 0;
  }
  if (param_4 != (ushort *)0x0) {
    *param_4 = 0;
  }
  local_res20 = (longlong *)0x0;
  local_res10[0] = 0;
  local_res18[0] = 0;
  if (param_2 == 0) {
    return 0;
  }
  FUN_18005e7b8(param_1,param_2,(longlong *)&local_res20,(int *)local_res10,local_res18);
  uVar2 = local_res10[0];
  uVar11 = (ulonglong)extraout_EAX;
  plVar7 = local_res20;
  if (-1 < (int)extraout_EAX) {
    uVar9 = (ulonglong)local_res10[0];
    if (0 < (int)local_res10[0]) {
      uVar11 = (ulonglong)local_res10[0];
      do {
        lVar1 = *plVar7;
        *(undefined4 *)(lVar1 + 0x3c) = 0;
        if (*(int *)(lVar1 + 0xc) == 1) {
          _o_qsort(*(longlong *)(lVar1 + 0x18) + 8,(longlong)(*(short *)(lVar1 + 0x10) + -1),8,
                   FUN_180136900);
        }
        plVar7 = plVar7 + 1;
        uVar11 = uVar11 - 1;
      } while (uVar11 != 0);
    }
    plVar7 = local_res20;
    iVar10 = 0;
    plVar5 = param_1;
    uVar3 = FUN_18013695c(param_1,param_2);
    uVar11 = uVar3 & 0xffffffff;
    if (-1 < (int)uVar3) {
      uVar4 = *(uint *)(param_2 + 0x3c);
      if (2000 < (int)uVar4) {
        fVar12 = 0.0;
        plVar5 = (longlong *)(ulonglong)uVar4;
        fVar13 = DAT_180182368;
        do {
          uVar4 = (uint)plVar5;
          if (9 < iVar10) break;
          fVar15 = (fVar12 + fVar13) * DAT_18017f884;
          plVar6 = plVar7;
          uVar11 = uVar9;
          if (0 < (int)uVar2) {
            do {
              plVar5 = plVar6 + 1;
              *(undefined4 *)(*plVar6 + 0x3c) = 0;
              uVar11 = uVar11 - 1;
              plVar6 = plVar5;
            } while (uVar11 != 0);
          }
          uVar3 = FUN_18005d318(plVar5,(longlong)plVar7,uVar2,fVar15);
          fVar14 = fVar13;
          if (-1 < (int)uVar3) {
            plVar5 = param_1;
            uVar3 = FUN_18013695c(param_1,param_2);
            fVar14 = fVar13;
          }
          fVar13 = fVar15;
          uVar11 = uVar3 & 0xffffffff;
          uVar4 = *(uint *)(param_2 + 0x3c);
          if (((int)uVar4 < 0x7d1) && (fVar12 = fVar13, fVar13 = fVar14, 0x5db < (int)uVar4)) break;
          iVar10 = iVar10 + 1;
          plVar5 = (longlong *)(ulonglong)uVar4;
        } while (-1 < (int)uVar3);
      }
      if (-1 < (int)uVar11) {
        if (2000 < (int)uVar4) {
          uVar3 = FUN_18005d318(plVar5,(longlong)plVar7,uVar2,0.0);
          uVar11 = uVar3 & 0xffffffff;
          if ((int)uVar3 < 0) goto LAB_18013794e;
          plVar5 = plVar7;
          uVar11 = uVar9;
          if (0 < (int)uVar2) {
            do {
              *(undefined4 *)(*plVar5 + 0x3c) = 0;
              uVar11 = uVar11 - 1;
              plVar5 = plVar5 + 1;
            } while (uVar11 != 0);
          }
          plVar5 = param_1;
          uVar3 = FUN_18013695c(param_1,param_2);
          uVar11 = uVar3 & 0xffffffff;
          if ((int)uVar3 < 0) goto LAB_18013794e;
        }
        if (2000 < *(int *)(param_2 + 0x3c)) {
          uVar3 = FUN_180137690(plVar5,(longlong)plVar7,uVar2);
          uVar11 = uVar3 & 0xffffffff;
          if ((int)uVar3 < 0) goto LAB_18013794e;
          plVar5 = plVar7;
          uVar11 = uVar9;
          if (0 < (int)uVar2) {
            do {
              *(undefined4 *)(*plVar5 + 0x3c) = 0;
              uVar11 = uVar11 - 1;
              plVar5 = plVar5 + 1;
            } while (uVar11 != 0);
          }
          uVar3 = FUN_18013695c(param_1,param_2);
          uVar11 = uVar3 & 0xffffffff;
          if ((int)uVar3 < 0) goto LAB_18013794e;
        }
        uVar8 = 0;
        plVar5 = plVar7;
        if (0 < (int)uVar2) {
          do {
            if (0 < *(int *)(*plVar5 + 0x3c)) {
              lVar1 = plVar7[uVar8];
              plVar7[uVar8] = *plVar5;
              *plVar5 = lVar1;
              *(uint *)(plVar7[uVar8] + 0x3c) = (uint)uVar8;
              uVar8 = uVar8 + 1;
            }
            uVar9 = uVar9 - 1;
            plVar5 = plVar5 + 1;
          } while (uVar9 != 0);
        }
        if ((param_3 != (undefined8 *)0x0) && (param_4 != (ushort *)0x0)) {
          *param_3 = plVar7;
          *param_4 = uVar8;
          return uVar11;
        }
      }
    }
  }
LAB_18013794e:
  _o_free(plVar7);
  return uVar11;
}


