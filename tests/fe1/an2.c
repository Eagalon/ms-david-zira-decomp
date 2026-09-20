// FUN_1800c7838 @ 1800c7838

int FUN_1800c7838(longlong param_1,longlong param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  longlong local_res10 [3];
  
  local_res10[0] = 0;
  iVar3 = 0;
  if (*(int *)(param_2 + 0x18) != 0) {
    iVar1 = *(int *)(param_2 + 0xc);
    bVar4 = false;
    if (iVar1 != 0) goto LAB_1800c78a4;
    if (*(int *)(param_2 + 8) < 0) {
      iVar3 = FUN_18006e874(local_res10,(undefined8 *)(param_1 + 0x420),3,param_2,
                            *(undefined8 *)(param_2 + 0x68),*(undefined4 *)(param_2 + 0x74),
                            *(undefined4 *)(param_2 + 0x70),*(undefined4 *)(param_2 + 0x74),
                            *(undefined2 *)(param_1 + 0x10),local_res10);
      return iVar3;
    }
  }
  iVar1 = *(int *)(param_2 + 0xc);
  bVar4 = iVar1 == 0;
LAB_1800c78a4:
  if ((!bVar4 && -1 < iVar1) || (*(longlong *)(param_2 + 0x48) != 0)) {
    uVar2 = *(uint *)(param_2 + 0x74);
    iVar3 = FUN_18006e874((ulonglong)uVar2,(undefined8 *)(param_1 + 0x420),3,param_2,
                          *(undefined8 *)(param_2 + 0x68),uVar2,*(undefined4 *)(param_2 + 0x70),
                          uVar2,*(undefined2 *)(param_1 + 0x10),local_res10);
    if (-1 < iVar3) {
      *(undefined4 *)(local_res10[0] + 0x210) = *(undefined4 *)(param_2 + 0xc);
    }
  }
  return iVar3;
}


// FUN_1800c6d3c @ 1800c6d3c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800c6d3c(longlong param_1,longlong param_2,int param_3)

{
  uint uVar1;
  ulonglong uVar2;
  longlong *plVar3;
  longlong local_res10;
  
  if (*(longlong *)(param_2 + 0x68) == 0) {
    return 0x8000ffff;
  }
  *(longlong *)(param_1 + 0x478) = *(longlong *)(param_2 + 0x68);
  *(undefined4 *)(param_1 + 0x450) = 1;
  uVar2 = 0;
  if ((*(longlong *)(param_2 + 0x68) != 0) && (uVar2 = 0, *(int *)(param_2 + 0x74) != 0)) {
    plVar3 = (longlong *)(param_1 + 0x458);
    FUN_180019d20((longlong)plVar3);
    uVar1 = (**(code **)(*plVar3 + 0x10))
                      (plVar3,*(undefined8 *)(param_2 + 0x68),*(undefined4 *)(param_2 + 0x74));
    uVar2 = (ulonglong)uVar1;
    if ((int)uVar1 < 0) goto LAB_1800c6e40;
  }
  if (*(longlong *)(param_2 + 0x80) == 0) {
    uVar1 = *(uint *)(param_2 + 0x74);
    local_res10 = 0;
    uVar1 = FUN_18006e874((ulonglong)uVar1,(undefined8 *)(param_1 + 0x420),3,param_2,
                          *(undefined8 *)(param_2 + 0x68),uVar1,*(undefined4 *)(param_2 + 0x70),
                          uVar1,*(undefined2 *)(param_1 + 0x10),&local_res10);
    uVar2 = (ulonglong)uVar1;
    if ((-1 < (int)uVar1) &&
       (*(undefined8 *)(local_res10 + 0x268) = *(undefined8 *)(param_2 + 0x68), param_3 == 0)) {
      *(undefined8 *)(param_1 + 0x478) = 0;
      *(undefined4 *)(param_1 + 0x450) = 0;
      FUN_180019d20(param_1 + 0x458);
    }
  }
LAB_1800c6e40:
  *(undefined2 *)(*(longlong *)(param_2 + 0x68) + (ulonglong)*(uint *)(param_2 + 0x74) * 2) = 0;
  return uVar2 & 0xffffffff;
}


// FUN_1800c6f58 @ 1800c6f58

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_1800c6f58(longlong param_1,longlong param_2)

{
  short *psVar1;
  short *psVar2;
  short sVar3;
  short sVar4;
  longlong lVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  longlong *plVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  longlong *plVar12;
  short *psVar13;
  code *pcVar14;
  undefined *puVar15;
  ulonglong uVar16;
  undefined4 uVar17;
  short *psVar18;
  undefined1 auStackY_718 [32];
  short local_6e8 [4];
  longlong *local_6e0;
  short *local_6d8;
  int local_6d0 [2];
  undefined8 *local_6c8;
  longlong *local_6c0;
  short *local_6b8;
  longlong local_6b0;
  undefined **local_6a8;
  undefined8 local_6a0;
  undefined8 uStack_698;
  undefined8 local_690;
  undefined8 local_688 [4];
  short local_668 [392];
  undefined2 local_358 [392];
  ulonglong local_48;
  
  local_48 = DAT_1801c0240 ^ (ulonglong)auStackY_718;
  uVar16 = 0;
  if ((*(short **)(param_2 + 0x30) != (short *)0x0) &&
     (uVar16 = 0, **(short **)(param_2 + 0x30) != 0)) {
    local_6b0 = param_2;
    local_6b8 = (short *)FUN_18007ca58(0x370);
    if ((local_6b8 == (short *)0x0) ||
       (plVar9 = FUN_18001ba9c((undefined8 *)local_6b8), plVar9 == (longlong *)0x0)) {
      uVar16 = 0x8007000e;
    }
    else {
      plVar9[0x12] = param_2;
      (**(code **)(*plVar9 + 0x30))(plVar9,*(undefined2 *)(param_1 + 0x10));
      (**(code **)(*plVar9 + 0x60))(plVar9,0);
      if (*(longlong *)(param_2 + 0x68) == 0) {
        uVar16 = 0;
        if ((*(longlong *)(param_1 + 0x430) != 0) &&
           (plVar12 = *(longlong **)(*(longlong *)(param_1 + 0x428) + 0x10), uVar16 = 0,
           plVar12 != (longlong *)0x0)) {
          iVar7 = (**(code **)(*plVar12 + 0x220))(plVar12,0);
          iVar6 = (**(code **)(*plVar12 + 0x210))(plVar12);
          uVar16 = (ulonglong)(uint)(iVar7 + iVar6);
        }
        (**(code **)(*plVar9 + 0x208))(plVar9,uVar16);
        (**(code **)(*plVar9 + 0x218))(plVar9,0);
        uVar17 = 1;
        puVar15 = &DAT_18017f888;
      }
      else {
        (**(code **)(*plVar9 + 0x208))(plVar9,*(undefined4 *)(param_2 + 0x70));
        (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined4 *)(param_2 + 0x74));
        uVar17 = *(undefined4 *)(param_2 + 0x74);
        puVar15 = *(undefined **)(param_2 + 0x68);
      }
      uVar8 = (**(code **)(*plVar9 + 0x70))(plVar9,puVar15,uVar17);
      uVar16 = (ulonglong)uVar8;
      if (-1 < (int)uVar8) {
        local_6d8 = (short *)0x0;
        uVar10 = FUN_18003861c(&local_6d8,*(void **)(param_2 + 0x30));
        uVar16 = uVar10 & 0xffffffff;
        local_6b8 = local_6d8;
        if (-1 < (int)uVar10) {
          psVar13 = local_6d8;
          local_6c0 = plVar9;
          if (param_1 == -0x488) {
            uVar16 = 0x8000ffff;
          }
          else {
            do {
              if (*psVar13 == 0) break;
              if (-1 < (int)uVar16) {
                do {
                  if (*psVar13 != 0x20) {
                    if (*psVar13 == 0x7c) {
                      local_6c8 = (undefined8 *)FUN_18007ca58(0x370);
                      if ((local_6c8 == (undefined8 *)0x0) ||
                         (plVar9 = FUN_18001ba9c(local_6c8), plVar9 == (longlong *)0x0)) {
                        uVar16 = 0x8007000e;
                      }
                      else {
                        plVar9[0x12] = param_2;
                        (**(code **)(*plVar9 + 0x30))(plVar9,*(undefined2 *)(param_1 + 0x10));
                        (**(code **)(*plVar9 + 0x60))(plVar9,1);
                        (**(code **)(*plVar9 + 0x100))(plVar9,1);
                        uVar8 = (**(code **)(*plVar9 + 0x78))(plVar9,&DAT_180185cc0);
                        uVar16 = (ulonglong)uVar8;
                        if (-1 < (int)uVar8) {
                          uVar8 = (**(code **)(*(longlong *)(param_1 + 0x488) + 0x10))
                                            ((longlong *)(param_1 + 0x488));
                          uVar16 = (ulonglong)uVar8;
                          if (-1 < (int)uVar8) goto LAB_1800c722a;
                        }
                        (**(code **)plVar9[1])();
                      }
                    }
                    else {
                      plVar9 = local_6c0;
                      if (*psVar13 != 0x2016) break;
                    }
                  }
LAB_1800c722a:
                  psVar13 = psVar13 + 1;
                  plVar9 = local_6c0;
                } while (-1 < (int)uVar16);
              }
              sVar3 = *psVar13;
              psVar18 = psVar13;
              while ((((sVar3 != 0 && (sVar3 != 0x20)) && (sVar3 != 0x7c)) && (sVar3 != 0x2016))) {
                psVar18 = psVar18 + 1;
                sVar3 = *psVar18;
              }
              *psVar18 = 0;
              memset(local_668,0,0x302);
              local_6e8[0] = 0;
              if (-1 < (int)uVar16) {
                plVar12 = *(longlong **)(*(longlong *)(param_1 + 0x558) + 0x350);
                uVar8 = (**(code **)(*plVar12 + 0xa8))(plVar12,psVar13,local_6e8);
                uVar16 = (ulonglong)uVar8;
                if (-1 < (int)uVar8) {
                  lVar5 = *(longlong *)(param_1 + 0x558);
                  puVar11 = FUN_1800197b4(local_688,0x180180958);
                  plVar12 = FUN_1800c6b84((longlong *)(lVar5 + 8),local_6e8[0],puVar11);
                  if (plVar12 == (longlong *)0x0) {
                    plVar12 = *(longlong **)(param_1 + 0x558);
                    local_6e8[0] = *(short *)(param_1 + 0x10);
                  }
                  puVar11 = (undefined8 *)plVar12[0x11];
                  if (puVar11 != (undefined8 *)0x0) {
                    uVar8 = (**(code **)*puVar11)(puVar11,psVar13,local_668,0x181);
                    uVar16 = (ulonglong)uVar8;
                    local_6d8 = (short *)0x0;
                    if (-1 < (int)uVar8) {
                      lVar5 = *(longlong *)(param_1 + 0x4c8);
                      if (lVar5 != 0) {
                        puVar11 = FUN_1800197b4(local_688,0x180180958);
                        plVar12 = FUN_18006f208((longlong *)(lVar5 + 8),local_6e8[0],puVar11);
                        if (plVar12 != (longlong *)0x0) {
                          uVar8 = (**(code **)(*plVar12 + 0x20))(plVar12);
                          uVar16 = (ulonglong)uVar8;
                          if ((int)uVar8 < 0) goto LAB_1800c7433;
                        }
                      }
                      if ((local_6d8 == (short *)0x0) ||
                         (iVar7 = FUN_1800cb1a8((longlong)local_6d8,(longlong)local_668), iVar7 != 0
                         )) {
LAB_1800c7403:
                        uVar8 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x148))
                                          (*(longlong **)(param_1 + 0x18),local_668,0x181);
                        uVar16 = (ulonglong)uVar8;
                      }
                      else {
                        memset(local_358,0,0x302);
                        uVar10 = FUN_1800cb574((longlong)local_6d8,(longlong)local_668,local_358,
                                               0x181,(int *)&local_6c8);
                        uVar16 = uVar10 & 0xffffffff;
                        if (-1 < (int)uVar10) {
                          uVar8 = FUN_18001f248(local_668,0x181,(longlong)local_358);
                          uVar16 = (ulonglong)uVar8;
                          if (-1 < (int)uVar8) goto LAB_1800c7403;
                        }
                      }
                    }
                  }
                }
              }
LAB_1800c7433:
              psVar13 = local_668;
              if (-1 < (int)uVar16) {
                for (; sVar4 = *psVar13, plVar9 = local_6c0, sVar4 != 0; psVar13 = psVar13 + 1) {
                  iVar7 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x68))
                                    (*(longlong **)(param_1 + 0x18),sVar4);
                  if (((iVar7 != 0) ||
                      (iVar7 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x70))(), iVar7 != 0))
                     && ((psVar13 == local_668 ||
                         (iVar7 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x28))(),
                         iVar7 == 0)))) {
                    do {
                      psVar1 = psVar13 + 1;
                      if (*psVar1 == 0) goto LAB_1800c74d9;
                      *psVar13 = *psVar1;
                      iVar7 = (**(code **)(**(longlong **)(param_1 + 0x18) + 0x28))();
                    } while ((iVar7 == 0) && (psVar2 = psVar13 + 2, psVar13 = psVar1, *psVar2 != 0))
                    ;
                    *psVar1 = sVar4;
                    psVar13 = psVar1;
                  }
LAB_1800c74d9:
                }
              }
              local_6e0 = (longlong *)0x0;
              if (-1 < (int)uVar16) {
                uVar8 = (**(code **)(*plVar9 + 0x228))(plVar9);
                uVar16 = (ulonglong)uVar8;
              }
              local_6d0[0] = 0;
              local_6a8 = CTTSString::vftable;
              local_6a0 = 0;
              uStack_698 = 0;
              local_690 = 0;
              if (-1 < (int)uVar16) {
                plVar12 = *(longlong **)(param_1 + 0x590);
                if (plVar12 != (longlong *)0x0) {
                  uVar8 = (**(code **)(*plVar12 + 0x90))(plVar12,local_668,&local_6a8,local_6d0);
                  uVar16 = (ulonglong)uVar8;
                  if ((int)uVar8 < 0) goto LAB_1800c7600;
                }
                plVar12 = local_6e0;
                if (local_6d0[0] == 0) {
                  psVar13 = local_668;
                  pcVar14 = *(code **)(*local_6e0 + 0x88);
                }
                else {
                  pcVar14 = *(code **)(*local_6e0 + 0x88);
                  psVar13 = FUN_18001c490((longlong)&local_6a8);
                }
                uVar8 = (*pcVar14)(plVar12,psVar13,0x14);
                uVar16 = (ulonglong)uVar8;
                if (-1 < (int)uVar8) {
                  uVar8 = (**(code **)(*local_6e0 + 0x30))();
                  uVar16 = (ulonglong)uVar8;
                  if (-1 < (int)uVar8) {
                    uVar8 = (**(code **)(*(longlong *)(param_1 + 0x488) + 0x10))();
                    uVar16 = (ulonglong)uVar8;
                    if (-1 < (int)uVar8) {
                      local_6e0 = (longlong *)0x0;
                    }
                  }
                }
              }
LAB_1800c7600:
              if (local_6e0 != (longlong *)0x0) {
                _o_free(local_6e0);
                local_6e0 = (longlong *)0x0;
              }
              *psVar18 = sVar3;
              FUN_18001d780(&local_6a8);
              param_2 = local_6b0;
              psVar13 = psVar18;
            } while (-1 < (int)uVar16);
          }
        }
        if (local_6b8 != (short *)0x0) {
          _o_free();
        }
      }
      (**(code **)plVar9[1])(plVar9 + 1,1);
    }
  }
  return uVar16;
}


