// FUN_180073a18 @ 180073a18

void FUN_180073a18(longlong param_1)

{
  *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_1 + 0x2e0);
  *(undefined8 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_1 + 0x2f0);
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x104) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined8 *)(param_1 + 0x29c) = 0;
  *(undefined8 *)(param_1 + 0x2a4) = 0;
  *(undefined4 *)(param_1 + 0x298) = 0;
  *(undefined8 *)(param_1 + 0x2ac) = 0;
  *(undefined8 *)(param_1 + 0x2b4) = 0;
  *(undefined8 *)(param_1 + 0x2fc) = 0;
  *(undefined8 *)(param_1 + 0x304) = 0;
  *(undefined8 *)(param_1 + 0x30c) = 0;
  *(undefined4 *)(param_1 + 0x314) = 0;
  *(undefined8 *)(param_1 + 0x2d4) = 0;
  *(undefined8 *)(param_1 + 700) = 0;
  *(undefined4 *)(param_1 + 0x2c4) = 0;
  *(undefined8 *)(param_1 + 0x98) = 0;
  *(undefined8 *)(param_1 + 0xa0) = 0;
  *(undefined8 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  FUN_18003da24(param_1);
  return;
}


// FUN_1801623e0 @ 1801623e0

int FUN_1801623e0(longlong param_1)

{
  int iVar1;
  bool bVar2;
  ulonglong uVar3;
  undefined7 extraout_var;
  undefined8 uVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  int iVar8;
  int local_res10 [2];
  int local_248 [4];
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_a0;
  undefined8 local_9c;
  undefined8 local_94;
  undefined8 local_8c;
  undefined4 local_84;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined4 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined4 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined4 local_28;
  
  local_234 = 0xffffffff;
  local_248[0] = 0;
  local_238 = 0;
  iVar8 = -2;
  local_9c = 0;
  local_94 = 0;
  local_a0 = 0;
  local_8c = 0;
  local_84 = 0;
  local_80 = 0;
  local_78 = 0;
  local_70 = 0;
  local_68 = 0;
  local_60 = 0;
  local_58 = 0;
  local_50 = 0;
  local_48 = 0;
  local_40 = 0;
  local_38 = 0;
  local_30 = 0;
  local_28 = 0;
  iVar6 = 0;
  iVar5 = 0;
LAB_180162498:
  if (iVar6 < 0) {
    return iVar6;
  }
  plVar7 = (longlong *)(param_1 + 0x98);
  uVar3 = FUN_18007ad50(plVar7);
  if ((int)uVar3 != 0) {
    return -7;
  }
  iVar1 = *(int *)(param_1 + 0xf8);
  if (iVar1 == 0x13) {
    if ((iVar5 != 0) &&
       (uVar4 = FUN_18016330c((int *)(param_1 + 0x100),local_res10), (int)uVar4 != 0)) {
      FUN_180161e84(param_1,local_248);
      return -2;
    }
    return -6;
  }
  if (iVar6 == 0) {
    if ((iVar1 != 1) && (iVar1 != 2)) {
      if (iVar1 == 10) {
        FUN_1801628d0((int *)(param_1 + 0x100),plVar7,param_1 + 0xb8);
        iVar6 = 10;
      }
      else {
        if (iVar1 != 0xd) goto LAB_180162685;
        FUN_180161040((int *)(param_1 + 0x298),plVar7,1,0,0);
      }
    }
  }
  else {
    if (iVar6 == 10) {
      if ((iVar1 == 1) || (iVar1 == 2)) goto LAB_1801626c7;
      if ((iVar1 == 10) || (iVar1 == 0xb)) {
LAB_180162659:
        FUN_1801628d0((int *)(param_1 + 0x100),plVar7,param_1 + 0xb8);
        goto LAB_1801626c7;
      }
LAB_180162685:
      iVar6 = 0x32;
      goto LAB_180162498;
    }
    if (iVar6 == 0x32) {
      if ((iVar1 == 1) || (iVar1 == 2)) goto LAB_1801626c7;
      if (iVar1 == 3) {
        bVar2 = FUN_180162aa4(plVar7);
        iVar6 = iVar8;
        if (((int)CONCAT71(extraout_var,bVar2) == 0) &&
           ((*(int *)(param_1 + 700) == 0 || (*(int *)(param_1 + 0xa8) == 1)))) {
          FUN_180162738(param_1,local_248);
          FUN_18003da24(param_1);
          iVar6 = 0x3c;
          iVar5 = local_248[0];
        }
        goto LAB_180162498;
      }
      iVar6 = iVar8;
      if ((iVar1 != 4) || ((*(int *)(param_1 + 700) != 0 && (2 < *(uint *)(param_1 + 0xa8)))))
      goto LAB_180162498;
LAB_18016251a:
      iVar6 = 0x46;
    }
    else {
      if (iVar6 != 0x3c) {
        if (iVar6 == 0x46) {
          if ((iVar1 == 1) || (iVar1 == 2)) {
            *(undefined4 *)(param_1 + 0x2c4) = *(undefined4 *)(param_1 + 0xa4);
            iVar6 = iVar8;
          }
          else {
            if (iVar1 == 0xb) goto LAB_180162659;
            if ((iVar1 != 0xc) ||
               (*(short *)(*plVar7 + (ulonglong)*(uint *)((longlong)plVar7 + 0xc) * 2) != 0x2e))
            goto LAB_1801624fd;
          }
          goto LAB_1801626c7;
        }
        if (iVar6 == 0x50) {
          iVar6 = iVar8;
          if (iVar5 != 0) {
            FUN_180161e84(param_1,local_248);
            iVar5 = local_248[0];
          }
        }
        else if (iVar6 == 0x5a) {
          if (iVar1 == 0xb) {
LAB_180162504:
            FUN_1801628d0((int *)(param_1 + 0x100),plVar7,param_1 + 0xb8);
            goto LAB_18016251a;
          }
LAB_1801624fd:
          iVar6 = 0x50;
        }
        goto LAB_180162498;
      }
      if ((iVar1 != 1) && (iVar1 != 2)) {
        if (iVar1 != 0xb) {
          if ((iVar1 != 0xc) ||
             (*(short *)(*plVar7 + (ulonglong)*(uint *)((longlong)plVar7 + 0xc) * 2) != 0x2e))
          goto LAB_1801624fd;
          goto LAB_18016251a;
        }
        goto LAB_180162504;
      }
      iVar6 = 0x5a;
    }
  }
LAB_1801626c7:
  FUN_18003da24(param_1);
  goto LAB_180162498;
}


// FUN_180064630 @ 180064630

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_180064630(longlong param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ulonglong uVar4;
  longlong *plVar5;
  ulonglong uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined7 extraout_var;
  short sVar9;
  wchar_t *pwVar10;
  uint uVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  int iVar14;
  undefined8 uVar15;
  ulonglong uVar16;
  uint uVar17;
  bool bVar18;
  int local_res10 [2];
  
  uVar17 = 0;
LAB_180064669:
  uVar15 = 10;
  uVar6 = 5;
LAB_180064673:
  uVar13 = 0;
LAB_180064676:
  uVar12 = uVar13;
  uVar13 = 0xfffffff9;
  uVar16 = 0x1e;
  iVar3 = (int)uVar12;
  if (iVar3 < 0) {
    return uVar12;
  }
  plVar5 = (longlong *)(param_1 + 0x98);
  uVar4 = FUN_18007ad50(plVar5);
  if ((int)uVar4 != 0) {
    return 0xfffffff9;
  }
  iVar14 = (int)uVar15;
  if (iVar3 < 0x1a) {
    if (iVar3 == 0x19) {
LAB_1800646ee:
      iVar3 = *(int *)(param_1 + 0xf8);
      uVar13 = uVar12;
      if ((iVar3 == 1) || (iVar3 == 2)) goto LAB_18006526e;
      if (iVar3 == 3) {
        uVar2 = *(uint *)((longlong)plVar5 + 0xc);
        lVar7 = *plVar5;
        uVar11 = *(uint *)(param_1 + 0xa8);
        plVar5 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x88) + 0x10))();
        uVar6 = FUN_180061864(lVar7 + (ulonglong)uVar2 * 2,uVar11,plVar5);
        if (-1 < (int)uVar6) {
          FUN_18003da24(param_1);
        }
      }
      uVar13 = 0xffffffff;
      goto LAB_180065276;
    }
    if (iVar3 != 0) {
      if (iVar3 == (int)uVar6) {
        uVar2 = *(uint *)(param_1 + 0xe0);
        iVar3 = 0;
        uVar15 = FUN_180161db0(plVar5);
        if ((uVar2 < 2) || (uVar2 == 10)) {
          FUN_180161040((int *)(param_1 + 0x298),(longlong *)(param_1 + 0xb8),1,0,(int)uVar15);
          uVar17 = *(uint *)(param_1 + 0xa4);
        }
        else {
          if (*(uint *)(param_1 + 0xc4) == uVar17) {
            uVar17 = *(uint *)(param_1 + 0xa4);
            iVar14 = 1;
          }
          else {
            iVar14 = 0;
            if (((*(int *)(param_1 + 200) != 0) &&
                (uVar8 = FUN_1800632f4(*(short *)(*(longlong *)(param_1 + 0xb8) +
                                                 (ulonglong)*(uint *)(param_1 + 0xc4) * 2)),
                (int)uVar8 != 0)) && (*(int *)(param_1 + 0xa8) != 0)) {
              sVar9 = *(short *)(*(longlong *)(param_1 + 0x98) +
                                (ulonglong)*(uint *)(param_1 + 0xa4) * 2);
              if ((sVar9 == 0) || (uVar1 = 1, (ushort)(sVar9 + 0x1800U) < 2)) {
                uVar1 = 0;
              }
              uVar2 = FUN_18003f9ac(uVar1);
              if (uVar2 != 0) {
                iVar3 = 1;
              }
            }
          }
          FUN_180161040((int *)(param_1 + 0x298),(longlong *)(param_1 + 0xb8),iVar14,iVar3,
                        (int)uVar15);
        }
        FUN_1801628a0((int *)(param_1 + 0x298));
        uVar13 = 0;
        goto LAB_180065276;
      }
      if (iVar3 == iVar14) {
        if ((*(int *)(param_1 + 0xf8) == 0xc) &&
           (*(short *)(*plVar5 + (ulonglong)*(uint *)((longlong)plVar5 + 0xc) * 2) == 0x2e)) {
          if (*(int *)(param_1 + 0xe0) == 0x1b) {
            uVar6 = (ulonglong)*(uint *)(param_1 + 0xe4);
            sVar9 = 0xb0;
            lVar7 = *(longlong *)(param_1 + 0xd8);
          }
          else {
            uVar13 = uVar16;
            if (*(int *)(param_1 + 0xe0) != 0xf) goto LAB_18006526e;
            uVar6 = (ulonglong)*(uint *)(param_1 + 0xe4);
            lVar7 = *(longlong *)(param_1 + 0xd8);
            if (*(short *)(lVar7 + uVar6 * 2) == 0xba) goto LAB_1800647db;
            sVar9 = 0x2da;
          }
          bVar18 = *(short *)(lVar7 + uVar6 * 2) == sVar9;
LAB_1800647d9:
          uVar13 = uVar16;
          if (bVar18) {
LAB_1800647db:
            uVar13 = 0xfffffffd;
          }
          goto LAB_18006526e;
        }
        goto LAB_180064673;
      }
      if (iVar3 == 0xf) {
        if ((*(int *)(param_1 + 0xf8) == 0xc) &&
           (*(short *)(*plVar5 + (ulonglong)*(uint *)((longlong)plVar5 + 0xc) * 2) == 0x2e)) {
          uVar15 = FUN_1801628f4((longlong *)(param_1 + 0xb8));
          if ((int)uVar15 != 0) {
            FUN_18003da24(param_1);
          }
          goto LAB_180064669;
        }
        goto LAB_180064673;
      }
      uVar13 = uVar12;
      if (iVar3 == 0x14) {
        if (*(int *)(param_1 + 0xf8) == 1 || *(int *)(param_1 + 0xf8) == 2) {
          uVar12 = 0x19;
          FUN_18003da24(param_1);
          plVar5 = (longlong *)(param_1 + 0x98);
          goto LAB_1800646ee;
        }
        goto LAB_180064673;
      }
      goto LAB_180064676;
    }
    iVar3 = *(int *)(param_1 + 0xf8);
    if (iVar14 < iVar3) {
      if (iVar3 == 0xb) {
        local_res10[0] = 0;
        if ((((*(int *)(param_1 + 0xfc) == 0xc) || (*(int *)(param_1 + 0xfc) == 0x13)) &&
            (uVar15 = FUN_18016330c((int *)(param_1 + 0x100),local_res10), (int)uVar15 != 0)) &&
           (*(int *)(param_1 + 0x2c4) <= local_res10[0])) {
          uVar12 = 0xfffffffb;
          *(undefined4 *)(param_1 + 0x2b8) = 1;
        }
        plVar5 = (longlong *)(param_1 + 0x98);
        goto LAB_180064e09;
      }
      if (iVar3 == 0xc) {
LAB_180064c7b:
        *(undefined4 *)(param_1 + 0x310) = 1;
        uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
        if ((uVar1 & 0x3ff) == 7) {
          uVar15 = FUN_18016296c((longlong *)(param_1 + 0xb8));
          uVar13 = uVar16;
          if (((int)uVar15 != 0) ||
             ((3 < *(uint *)(param_1 + 200) &&
              (iVar3 = _o__wcsnicmp(&DAT_180193d98,
                                    *(longlong *)(param_1 + 0xb8) + -6 +
                                    ((ulonglong)*(uint *)(param_1 + 0xc4) +
                                    (ulonglong)*(uint *)(param_1 + 200)) * 2,3), iVar3 == 0))))
          goto LAB_18006526e;
        }
        uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
        if ((uVar1 & 0x3ff) == 10) {
          bVar18 = FUN_1801629d8((longlong *)(param_1 + 0xb8));
          bVar18 = (int)CONCAT71(extraout_var,bVar18) == 0;
          goto LAB_1800647d9;
        }
        goto LAB_1800647db;
      }
      if (iVar3 == 0xd) {
        uVar13 = uVar6 & 0xffffffff;
      }
      else if (iVar3 == 0xe) {
        if (*(int *)(param_1 + 700) == 0) {
          uVar13 = uVar12;
          if ((*(short *)(*(longlong *)(param_1 + 0x98) + (ulonglong)*(uint *)(param_1 + 0xa4) * 2)
               == 0x3a) &&
             ((uVar15 = FUN_180161db0((longlong *)(param_1 + 0xb8)), (int)uVar15 == 0 &&
              (uVar15 = FUN_180161db0((longlong *)(param_1 + 0xd8)), (int)uVar15 == 0)))) {
            *(undefined4 *)(param_1 + 700) = 1;
LAB_180064d7d:
            uVar13 = 0x14;
          }
        }
        else if ((*(short *)(*(longlong *)(param_1 + 0x98) +
                            (ulonglong)*(uint *)(param_1 + 0xa4) * 2) != 0x3a) ||
                ((uVar15 = FUN_180161db0((longlong *)(param_1 + 0xb8)), uVar13 = uVar12,
                 (int)uVar15 == 0 &&
                 (uVar15 = FUN_180161db0((longlong *)(param_1 + 0xd8)), (int)uVar15 == 0))))
        goto LAB_180064d7d;
      }
      else {
        if ((iVar3 == 0x10) || (iVar3 == 0x11)) goto LAB_180064676;
        if (iVar3 == 0x12) goto LAB_18006496c;
        uVar13 = uVar12;
        if (iVar3 == 0x13) goto LAB_180064c7b;
      }
    }
    else {
      if (iVar3 != iVar14) {
        if ((iVar3 == 1) || (iVar3 == 2)) {
          uVar13 = 0x5a;
        }
        else if ((((iVar3 == 3) || (iVar3 == 4)) || (iVar3 == 5)) || ((iVar3 == 6 || (iVar3 == 7))))
        {
          *(undefined4 *)(param_1 + 0x310) = 0;
          *(undefined4 *)(param_1 + 0x2b8) = 0;
          uVar6 = FUN_180160f40((int *)(param_1 + 0x298),(longlong *)(param_1 + 0x98));
          if ((int)uVar6 != 0) {
            FUN_1801628a0((int *)(param_1 + 0x298));
          }
          iVar3 = *(int *)(param_1 + 0xf8);
          if (iVar3 == 3) {
            if (*(uint *)(param_1 + 0xa8) == 1) {
              uVar13 = 10;
            }
            else {
              uVar13 = uVar12;
              if ((*(uint *)(param_1 + 0xa8) & 1) != 0) {
                uVar13 = 0xf;
              }
            }
          }
          else if (iVar3 == 4) {
            uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
            if ((uVar1 & 0x3ff) == 0x15) {
              iVar3 = FUN_180161d5c((longlong *)(param_1 + 0xd8),0x180185284);
              if ((iVar3 == 0) &&
                 (iVar3 = FUN_180161d5c((longlong *)(param_1 + 0xd8),0x180193d88), iVar3 == 0)) {
                pwVar10 = L"roku";
LAB_180064b0e:
                iVar3 = FUN_180161d5c((longlong *)(param_1 + 0xd8),(longlong)pwVar10);
                uVar13 = uVar16;
                if (iVar3 == 0) goto LAB_18006526e;
              }
            }
            else {
              uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
              if ((uVar1 & 0x3ff) != 7) {
                uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
                if ((((uVar1 & 0x3ff) != 0xe) &&
                    (uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))(),
                    (uVar1 & 0x3ff) != 5)) &&
                   ((uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))(),
                    (uVar1 & 0x3ff) != 0x1b &&
                    (((uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))(),
                      (uVar1 & 0x3ff) != 0x1f &&
                      (uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))(),
                      (uVar1 & 0x3ff) != 0x1a)) &&
                     (uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))(),
                     (uVar1 & 0x3ff) != 0x24)))))) goto LAB_1800647db;
                uVar13 = (ulonglong)((-(uint)(*(uint *)(param_1 + 0xa8) < 5) & 0x21) - 3);
                goto LAB_18006526e;
              }
              iVar3 = FUN_180161d5c((longlong *)(param_1 + 0xd8),0x180193db4);
              if (iVar3 == 0) {
                pwVar10 = L"jahr";
                goto LAB_180064b0e;
              }
            }
            uVar13 = uVar16;
            if (4 < *(uint *)(param_1 + 0xa8)) goto LAB_1800647db;
          }
          else {
            if (iVar3 == 5) {
              iVar3 = FUN_180161d5c((longlong *)(param_1 + 0x98),0x180193d70);
              if (((iVar3 != 0) ||
                  (iVar3 = FUN_180161d5c((longlong *)(param_1 + 0x98),0x180193d78), iVar3 != 0)) &&
                 (uVar13 = uVar12, *(int *)(param_1 + 0xc0) == 0)) goto LAB_18006526e;
            }
            else if (iVar3 != 6) {
              uVar13 = uVar12;
              if (iVar3 != 7) goto LAB_18006526e;
              iVar3 = FUN_180161d5c((longlong *)(param_1 + 0x98),0x180193dd0);
              if ((((iVar3 != 0) ||
                   (iVar3 = FUN_180161d5c((longlong *)(param_1 + 0x98),0x180193d90), iVar3 != 0)) &&
                  (*(int *)(param_1 + 0xe0) != 0)) &&
                 (uVar2 = FUN_1801619e4(*(ushort *)
                                         (*(longlong *)(param_1 + 0xd8) +
                                         (ulonglong)*(uint *)(param_1 + 0xe4) * 2)), uVar2 != 0)) {
                *(undefined4 *)(param_1 + 0xa0) = 5;
              }
            }
            uVar13 = uVar16;
          }
        }
        else if ((iVar3 == 8) || (uVar13 = uVar12, iVar3 == 9)) {
LAB_18006496c:
          uVar13 = 0x50;
        }
        goto LAB_18006526e;
      }
LAB_180064e09:
      FUN_1801628d0((int *)(param_1 + 0x100),plVar5,param_1 + 0xb8);
      *(undefined4 *)(param_1 + 700) = 0;
      uVar13 = uVar12;
    }
  }
  else {
    if (iVar3 == 0x1e) {
      iVar3 = *(int *)(param_1 + 0xf8);
      if (*(int *)(param_1 + 0xfc) == 7) {
        if ((iVar3 != 1) || (*(uint *)(param_1 + 0xa8) < 2)) goto LAB_180064673;
      }
      else {
        *(undefined4 *)(param_1 + 0x2c0) = 1;
        if ((iVar3 == 1) || (iVar3 == 2)) {
          if (*(uint *)(param_1 + 0xa8) < 2) {
            uVar13 = 0x28;
            goto LAB_18006526e;
          }
        }
        else if (iVar3 == 0xb) {
          if (*(int *)(param_1 + 0xe0) == iVar14) goto LAB_180064673;
        }
        else if (iVar3 != 0xc) {
          if (iVar3 == 0xd) {
            sVar9 = *(short *)(*plVar5 + (ulonglong)*(uint *)((longlong)plVar5 + 0xc) * 2);
            uVar8 = FUN_180160fe0(sVar9);
            if ((int)uVar8 != 0) goto LAB_180065258;
            bVar18 = sVar9 == 0xbb;
          }
          else {
            if ((iVar3 == 0x10) || (iVar3 == 0x11)) {
              if ((*(int *)(param_1 + 0xe0) != 0) ||
                 (iVar3 = FUN_180161d5c((longlong *)(param_1 + 0xb8),0x180193da0), iVar3 != 0))
              goto LAB_180065212;
              goto LAB_180065276;
            }
            bVar18 = iVar3 == 0x12;
          }
          if (!bVar18) goto LAB_180064673;
        }
      }
LAB_180065258:
      *(undefined4 *)(param_1 + 0x310) = 1;
      uVar13 = 0xfffffffc;
      goto LAB_180064676;
    }
    if (iVar3 == 0x28) {
      if (*(int *)(param_1 + 0xf8) - 0xbU < 2) goto LAB_180065258;
      if (1 < *(int *)(param_1 + 0xf8) - 0x10U) {
        plVar5 = (longlong *)(param_1 + 0x98);
        if (*(int *)(param_1 + 0xe0) == 6) {
          uVar15 = FUN_180161db0(plVar5);
          if ((int)uVar15 == 0) {
            uVar2 = FUN_180066b20(*(ushort *)
                                   (*(longlong *)(param_1 + 0x98) +
                                   (ulonglong)*(uint *)(param_1 + 0xa4) * 2));
            bVar18 = uVar2 == 0;
            goto LAB_180064fc1;
          }
        }
        else {
          uVar2 = FUN_180161740(param_1 + 8,
                                *(longlong *)(param_1 + 0xd8) +
                                (ulonglong)*(uint *)(param_1 + 0xe4) * 2,*(uint *)(param_1 + 0xe8));
          if (uVar2 != 0) {
            uVar15 = FUN_180161db0(plVar5);
            if (((((int)uVar15 == 0) &&
                 (uVar2 = FUN_1801617e4(param_1 + 8,
                                        *(longlong *)(param_1 + 0x98) +
                                        (ulonglong)*(uint *)(param_1 + 0xa4) * 2,
                                        *(uint *)(param_1 + 0xa8)), uVar2 == 0)) &&
                ((*(int *)(param_1 + 0xa8) != 1 ||
                 (uVar2 = FUN_18003f58c(*(ushort *)
                                         (*(longlong *)(param_1 + 0x98) +
                                         (ulonglong)*(uint *)(param_1 + 0xa4) * 2)), uVar2 == 0))))
               && ((uVar15 = FUN_18016296c((longlong *)(param_1 + 0x98)), (int)uVar15 == 0 &&
                   (uVar2 = FUN_180066b20(*(ushort *)
                                           (*(longlong *)(param_1 + 0x98) +
                                           (ulonglong)*(uint *)(param_1 + 0xa4) * 2)), uVar2 == 0)))
               ) {
              *(undefined4 *)(param_1 + 0x310) = 1;
            }
            else {
              uVar13 = 0;
            }
            goto LAB_180065276;
          }
          uVar2 = FUN_1801619e4(*(ushort *)(*plVar5 + (ulonglong)*(uint *)(param_1 + 0xa4) * 2));
          if (uVar2 != 0) {
            uVar2 = *(uint *)(param_1 + 0xe4);
            lVar7 = *(longlong *)(param_1 + 0xd8);
            uVar11 = *(uint *)(param_1 + 0xe8);
            plVar5 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x88) + 0x30))();
            uVar6 = FUN_180061864(lVar7 + (ulonglong)uVar2 * 2,uVar11,plVar5);
            if (((int)uVar6 < 0) &&
               (((uVar1 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))(),
                 (uVar1 & 0x3ff) != 7 || (*(int *)(param_1 + 0xe0) != 4)) ||
                (*(uint *)(param_1 + 0xe8) < 5)))) {
              uVar11 = *(int *)(param_1 + 0xa4) + *(uint *)(param_1 + 0xa8);
              uVar2 = FUN_180161624(param_1 + 8,
                                    (ushort *)
                                    (*(longlong *)(param_1 + 0x98) +
                                    (ulonglong)*(uint *)(param_1 + 0xa4) * 2),
                                    *(uint *)(param_1 + 0xa8));
              if (((uVar2 == 0) || (*(uint *)(param_1 + 0x2f0) <= uVar11)) ||
                 (*(short *)(*(longlong *)(param_1 + 0x2e0) + (ulonglong)uVar11 * 2) == 0x2e))
              goto LAB_180064fc7;
            }
LAB_180065212:
            *(undefined4 *)(param_1 + 0x310) = 1;
            goto LAB_180065276;
          }
        }
LAB_180064fc7:
        uVar13 = 0;
        goto LAB_180065276;
      }
      goto LAB_180064676;
    }
    if (iVar3 == 0x3c) {
      iVar3 = *(int *)(param_1 + 0xf8);
      if (((iVar3 == 3) || (iVar3 == 4)) || ((iVar3 == 5 || ((iVar3 == 6 || (iVar3 == 7)))))) {
        uVar2 = FUN_180066b20(*(ushort *)
                               (*plVar5 + (ulonglong)*(uint *)((longlong)plVar5 + 0xc) * 2));
        if ((uVar2 == 0) ||
           ((uVar15 = FUN_180161db0((longlong *)(param_1 + 0x98)), (int)uVar15 != 0 ||
            (1 < *(uint *)(param_1 + 200))))) goto LAB_180065212;
        bVar18 = *(int *)(param_1 + 0xe0) == 0xc;
LAB_180064fc1:
        if (bVar18) goto LAB_180065212;
        goto LAB_180064fc7;
      }
      if (((iVar3 == 10) || (iVar3 == 0xb)) || (iVar3 == 0xc)) goto LAB_180065258;
      if (iVar3 != 0xd) goto LAB_180064673;
      goto LAB_180064676;
    }
    if (iVar3 != 0x50) {
      uVar13 = uVar12;
      if (iVar3 == 0x5a) goto LAB_180064673;
      goto LAB_180064676;
    }
    iVar3 = *(int *)(param_1 + 0xf8);
    *(undefined4 *)(param_1 + 0x310) = 1;
    if ((iVar3 == 1) || (iVar3 == 2)) {
      uVar13 = 0x3c;
      if ((*(int *)(param_1 + 0xe0) - 8U & 0xfffffffb) == 0) {
        *(undefined4 *)(param_1 + 0xc0) = 0xc;
      }
    }
    else {
      uVar13 = uVar12;
      if ((iVar3 != 8) && (iVar3 != 9)) {
        if (iVar3 != 0xc) {
          if (iVar3 == 0xd) goto LAB_18006526e;
          goto LAB_180064673;
        }
        if ((*(int *)(param_1 + 0xc0) != 8) ||
           (*(short *)(*(longlong *)(param_1 + 0x98) + (ulonglong)*(uint *)(param_1 + 0xa4) * 2) !=
            0x2e)) goto LAB_180064673;
      }
    }
  }
LAB_18006526e:
  FUN_18003da24(param_1);
LAB_180065276:
  uVar6 = 5;
  uVar15 = 10;
  goto LAB_180064676;
}


// FUN_180161a1c @ 180161a1c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_180161a1c(longlong param_1)

{
  int iVar1;
  int iVar2;
  longlong *plVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  int iVar9;
  undefined8 uVar10;
  int *piVar11;
  int local_res8 [2];
  
  *(undefined4 *)(param_1 + 0x310) = 1;
  iVar1 = -7;
  iVar2 = -4;
  iVar9 = 0;
LAB_180161a50:
  do {
    uVar10 = 4;
    do {
      while( true ) {
        if (iVar9 < 0) {
          return iVar9;
        }
        plVar3 = (longlong *)(param_1 + 0x98);
        uVar7 = FUN_18007ad50(plVar3);
        if ((int)uVar7 != 0) {
          return -7;
        }
        iVar4 = *(int *)(param_1 + 0xf8);
        if (iVar4 == 0x13) {
          return -6;
        }
        if (iVar9 != 0) break;
        iVar9 = iVar2;
        if ((iVar4 == 1) || (iVar4 == 2)) {
          iVar9 = iVar1;
          if (1 < *(uint *)(param_1 + 0xa8)) goto LAB_180161d20;
          iVar9 = iVar2;
          if ((*(short *)(*(longlong *)(param_1 + 0xb8) + (ulonglong)*(uint *)(param_1 + 0xc4) * 2)
               != 0x2e) && (*(int *)(param_1 + 0xfc) != (int)uVar10)) {
            iVar9 = 10;
            if ((iVar4 != 1) || (*(int *)(param_1 + 0xfc) != 0x13)) goto LAB_180161d20;
            iVar9 = -7;
          }
        }
        else if (iVar4 == 0xb) {
          piVar11 = (int *)(param_1 + 0x100);
          *(undefined4 *)(param_1 + 0x2b8) = 1;
          uVar10 = FUN_18016330c(piVar11,local_res8);
          iVar9 = -4;
          if ((int)uVar10 == 0) goto LAB_180161a50;
          FUN_1801628d0(piVar11,plVar3,param_1 + 0xb8);
          *(undefined4 *)(param_1 + 0x2b8) = 0;
          FUN_18003da24(param_1);
          uVar5 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
          uVar10 = 4;
          iVar9 = iVar2;
          if (((((uVar5 & 0x3ff) == 4) && (*(int *)(param_1 + 0xe0) == 0x13)) &&
              (*(int *)(param_1 + 0xc0) == 0xb)) &&
             ((*(int *)(param_1 + 200) == 1 &&
              ((ushort)(*(short *)(*(longlong *)(param_1 + 0xb8) +
                                  (ulonglong)*(uint *)(param_1 + 0xc4) * 2) + 0xdfe3U) < 2)))) {
            iVar9 = -7;
          }
        }
        else if (iVar4 != 0xc) {
          if (iVar4 == 0xd) {
            uVar8 = FUN_1800632f4(*(short *)(*plVar3 + (ulonglong)*(uint *)(param_1 + 0xa4) * 2));
            iVar9 = -4;
            if ((int)uVar8 != 0) {
              FUN_180161040((int *)(param_1 + 0x298),plVar3,0,0,0);
              FUN_1801628a0((int *)(param_1 + 0x298));
              FUN_18003da24(param_1);
              iVar9 = iVar2;
              goto LAB_180161a50;
            }
          }
          else if ((iVar4 != 0x12) && (iVar9 = -2, *(int *)(param_1 + 0xfc) == 0x13)) {
            iVar9 = iVar1;
          }
        }
      }
    } while (iVar9 != 10);
    if (((((iVar4 != 3) && (iVar4 != 4)) && (iVar4 != 5)) && ((iVar4 != 6 && (iVar4 != 7)))) &&
       (iVar4 != 10)) {
      if (iVar4 == 0xc) {
        iVar9 = 0;
LAB_180161d20:
        FUN_18003da24(param_1);
      }
      else {
LAB_180161b4f:
        uVar10 = FUN_180161028((int *)(param_1 + 0x298));
        if ((int)uVar10 == 0) {
          iVar9 = iVar1;
          if ((*(int *)(param_1 + 0x2b8) == 0) &&
             (uVar10 = FUN_18016330c((int *)(param_1 + 0x100),local_res8), (int)uVar10 != 0)) {
            iVar9 = -5;
          }
        }
        else {
          iVar9 = -4;
        }
      }
      goto LAB_180161a50;
    }
    uVar5 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
    if ((uVar5 & 0x3ff) == 10) {
      uVar5 = *(ushort *)(*plVar3 + (ulonglong)*(uint *)(param_1 + 0xa4) * 2);
      uVar6 = FUN_180066b20(uVar5);
      if ((uVar6 == 0) && (uVar5 != 0x28)) goto LAB_180161b0a;
      iVar9 = -2;
    }
    else {
LAB_180161b0a:
      uVar5 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
      if (((uVar5 & 0x3ff) != 0xc) ||
         (uVar6 = FUN_1801616b0(param_1 + 8,
                                (short *)(*plVar3 + (ulonglong)*(uint *)(param_1 + 0xa4) * 2),
                                (ulonglong)*(uint *)(param_1 + 0xa8)), uVar6 == 0))
      goto LAB_180161b4f;
      iVar9 = -2;
    }
  } while( true );
}


// FUN_180161ff8 @ 180161ff8

int FUN_180161ff8(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  int *piVar9;
  bool bVar10;
  int local_res8 [2];
  
  iVar2 = *(int *)(param_1 + 0xfc);
  iVar7 = 0;
LAB_180162015:
  uVar8 = 0x14;
LAB_18016201b:
  if (iVar7 < 0) {
    return iVar7;
  }
  plVar1 = (longlong *)(param_1 + 0x98);
  uVar4 = FUN_18007ad50(plVar1);
  if ((int)uVar4 != 0) {
    return -7;
  }
  iVar6 = *(int *)(param_1 + 0xf8);
  if (iVar6 == 0x13) {
    return -6;
  }
  if (iVar7 != 0) goto code_r0x00018016204d;
  uVar5 = FUN_180161028((int *)(param_1 + 0x298));
  iVar7 = (-(uint)((int)uVar5 != 0) & 10) + 10;
  goto LAB_18016206f;
code_r0x00018016204d:
  if ((iVar7 != 10) && (iVar7 != (int)uVar8)) goto LAB_18016201b;
LAB_18016206f:
  if (iVar6 != 1) {
    if (iVar6 == 2) goto LAB_180162222;
    if (iVar6 == 3) {
      if (((iVar2 == 5) && (*(int *)(param_1 + 0xfc) == 1)) && (*(int *)(param_1 + 200) == 1)) {
        uVar3 = FUN_180066b20(*(ushort *)(*plVar1 + (ulonglong)*(uint *)(param_1 + 0xa4) * 2));
        if (uVar3 != 0) {
          iVar7 = -2;
          goto LAB_180162015;
        }
        uVar8 = 0x14;
      }
      if ((*(int *)(param_1 + 0xfc) == 0xd) ||
         (((iVar7 == 10 && (*(int *)(param_1 + 0x2b8) == 0)) &&
          ((*(int *)(param_1 + 0xfc) == 0xb ||
           (uVar5 = FUN_18016330c((int *)(param_1 + 0x100),local_res8), (int)uVar5 != 0)))))) {
        iVar7 = -5;
        goto LAB_18016201b;
      }
    }
    else {
      if (iVar6 == 0xb) {
        piVar9 = (int *)(param_1 + 0x100);
        uVar8 = FUN_18016330c(piVar9,local_res8);
        FUN_1801628d0(piVar9,plVar1,param_1 + 0xb8);
        if ((int)uVar8 == 0) {
          *(undefined4 *)(param_1 + 0x2b8) = 1;
        }
        goto LAB_180162222;
      }
      if (iVar6 == 0xc) goto LAB_180162222;
      if (iVar6 == 0xd) {
        FUN_180161040((int *)(param_1 + 0x298),plVar1,0,0,0);
        FUN_1801628a0((int *)(param_1 + 0x298));
        uVar8 = FUN_180160fe0(*(short *)(*plVar1 + (ulonglong)*(uint *)(param_1 + 0xa4) * 2));
        if ((int)uVar8 != 0) {
          bVar10 = iVar7 == 10;
          iVar7 = 0;
          if (bVar10) {
            iVar7 = 0x14;
          }
        }
        goto LAB_180162222;
      }
      if (iVar6 == 0xe) {
        iVar7 = -2;
        goto LAB_18016201b;
      }
      if (iVar6 == 0x12) goto LAB_180162222;
    }
    iVar7 = -7;
    goto LAB_18016201b;
  }
  if (((*(int *)(param_1 + 0x2b8) != 0) || (*(int *)(param_1 + 0xa8) != 1)) ||
     (*(int *)(param_1 + 0xfc) != 0xd)) {
    if (iVar7 != 10) goto LAB_180162222;
    if ((*(int *)(param_1 + 0xa8) != 1) ||
       (((*(int *)(param_1 + 0xfc) - 0xbU & 0xfffffffd) != 0 &&
        (uVar8 = FUN_18016330c((int *)(param_1 + 0x100),local_res8), (int)uVar8 == 0)))) {
      iVar7 = -7;
LAB_180162222:
      FUN_18003da24(param_1);
      goto LAB_180162015;
    }
  }
  iVar7 = -5;
  goto LAB_180162222;
}


// FUN_18016225c @ 18016225c

int FUN_18016225c(longlong param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = -7;
  iVar2 = 0;
LAB_18016227d:
  do {
    while( true ) {
      while( true ) {
        iVar6 = iVar2;
        if (iVar6 < 0) {
          return iVar6;
        }
        uVar4 = FUN_18007ad50((longlong *)(param_1 + 0x98));
        if ((int)uVar4 != 0) {
          return -7;
        }
        iVar1 = *(int *)(param_1 + 0xf8);
        if (iVar1 == 0x13) {
          return -6;
        }
        iVar2 = iVar7;
        if (iVar1 < 0xb) goto code_r0x0001801622b1;
        if (iVar1 != 0xb) break;
        iVar2 = -4;
      }
      if (iVar1 != 0xd) break;
      iVar2 = -7;
      if (*(int *)(param_1 + 0xfc) != 1) {
        iVar2 = -2;
      }
    }
    if (((iVar1 != 0xf) && (iVar1 != 0x1b)) &&
       ((iVar1 != 0x1c && ((iVar1 != 0x1d && (iVar1 != 0x20)))))) goto LAB_18016237d;
  } while (*(int *)(param_1 + 0x2c0) == 0);
  *(undefined4 *)(param_1 + 0x2c0) = 0;
  goto LAB_18016237d;
code_r0x0001801622b1:
  if (iVar1 == 10) goto LAB_18016227d;
  if ((iVar1 == 1) || (iVar1 == 2)) {
    FUN_18003da24(param_1);
    iVar2 = iVar6;
    goto LAB_18016227d;
  }
  if (iVar1 != 3) {
    if (iVar1 == 4) {
      if ((*(int *)(param_1 + 0xa8) == 2) || (*(int *)(param_1 + 0x310) != 0)) goto LAB_18016227d;
    }
    else if ((iVar1 != 5) && ((iVar1 != 6 && (iVar1 != 7)))) goto LAB_18016237d;
  }
  uVar3 = FUN_1801619e4(*(ushort *)
                         (*(longlong *)(param_1 + 0x98) + (ulonglong)*(uint *)(param_1 + 0xa4) * 2))
  ;
  if ((uVar3 != 0) ||
     (((*(byte *)(param_1 + 0xac) & 0x40) != 0 ||
      (((*(int *)(param_1 + 0xfc) == 1 && ((*(int *)(param_1 + 0xe0) - 0xbU & 0xfffffffd) == 0)) &&
       (uVar5 = FUN_180161db0((longlong *)(param_1 + 0x98)), (int)uVar5 != 0))))))
  goto LAB_18016227d;
LAB_18016237d:
  iVar2 = -2;
  goto LAB_18016227d;
}


// FUN_180161e00 @ 180161e00

int FUN_180161e00(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  int iVar3;
  
  iVar3 = 0;
LAB_180161e0f:
  do {
    if (iVar3 < 0) {
      return iVar3;
    }
    uVar2 = FUN_18007ad50((longlong *)(param_1 + 0x98));
    if ((int)uVar2 != 0) {
      return -7;
    }
    iVar1 = *(int *)(param_1 + 0xf8);
    if ((iVar1 != 1) && (iVar1 != 2)) {
      if (iVar1 == 0xb) {
        iVar3 = -5;
      }
      else if (iVar1 == 0xc) {
        iVar3 = -3;
      }
      else if (iVar1 != 0x13) {
        *(undefined4 *)(param_1 + 0x310) = 1;
        iVar3 = -7;
        goto LAB_180161e0f;
      }
    }
    FUN_18003da24(param_1);
  } while( true );
}


// FUN_1800686e0 @ 1800686e0

void FUN_1800686e0(longlong param_1)

{
  uint uVar1;
  ushort *puVar2;
  bool bVar3;
  undefined8 uVar4;
  undefined7 extraout_var;
  ushort uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  ushort *puVar9;
  ushort *puVar10;
  
  if (*(int *)(param_1 + 0xf8) == 0x10) {
    FUN_18003da24(param_1);
  }
  uVar1 = *(uint *)(param_1 + 0xa4);
  iVar7 = 0;
  *(uint *)(param_1 + 0x2e8) = uVar1;
  uVar6 = uVar1;
  if ((*(int *)(param_1 + 0xb0) != 0) && (uVar1 == 0)) {
    uVar6 = *(uint *)(param_1 + 0xa8);
    *(uint *)(param_1 + 0x2e8) = uVar6;
  }
  puVar2 = *(ushort **)(param_1 + 0x2e0);
  puVar10 = puVar2 + uVar6;
  puVar9 = puVar10;
  while( true ) {
    puVar9 = puVar9 + -1;
    *(uint *)(param_1 + 0x2ec) = uVar6;
    if ((uVar6 == 0) ||
       ((uVar4 = FUN_180072d30(*puVar9), (int)uVar4 == 0 &&
        (uVar4 = FUN_180079ea4(*puVar9), (int)uVar4 == 0)))) break;
    uVar6 = uVar6 - 1;
  }
  bVar3 = FUN_18007b288((longlong *)(param_1 + 0x98));
  iVar8 = 0;
  if (((int)CONCAT71(extraout_var,bVar3) == 0) &&
     ((iVar8 = iVar7, *(int *)(param_1 + 0xb0) == 0 || (uVar1 != 0)))) {
    iVar7 = *(int *)(param_1 + 0xf8);
    if ((iVar7 != 1) && (iVar7 != 2)) {
      if ((((iVar7 == 3) || (iVar7 == 4)) || (iVar7 == 5)) || ((iVar7 == 6 || (iVar7 == 7)))) {
        *(int *)(param_1 + 0x300) = *(int *)(param_1 + 0x300) - *(int *)(param_1 + 0xa8);
        *(int *)(param_1 + 0x2fc) = *(int *)(param_1 + 0x2fc) + -1;
      }
      else if (iVar7 == 0x10) goto LAB_180068809;
      *(int *)(param_1 + 0x304) = *(int *)(param_1 + 0x304) - *(int *)(param_1 + 0xa8);
    }
  }
LAB_180068809:
  while (puVar2 < puVar10) {
    puVar10 = puVar10 + -1;
    uVar5 = *puVar10;
    if ((uVar5 - 0x20 & 0xff7f) != 0) goto LAB_180068813;
    iVar8 = iVar8 + 1;
  }
  uVar5 = puVar10[-1];
LAB_180068813:
  iVar7 = -1;
  if (uVar5 != 9) {
    iVar7 = iVar8;
  }
  *(int *)(param_1 + 0x2f8) = iVar7;
  return;
}


