// FUN_1800bb3e0 @ 1800bb3e0

void FUN_1800bb3e0(longlong param_1)

{
  longlong lVar1;
  int local_res8 [8];
  
  local_res8[0] = 0;
  lVar1 = FUN_1800902a8(*(longlong *)(*(longlong *)(param_1 + 0x558) + 0x1f0),local_res8,0x80070057)
  ;
  if (((-1 < local_res8[0]) && (lVar1 != 0)) && (*(longlong *)(lVar1 + 0x28) != 0)) {
    FUN_180060c48(*(longlong *)(lVar1 + 0x28),(longlong *)(param_1 + 0x420));
  }
  return;
}


// FUN_180060c48 @ 180060c48

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Removing unreachable block (ram,0x000180060cac) */

ulonglong FUN_180060c48(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  longlong *plVar4;
  ulonglong uVar5;
  longlong *plVar6;
  undefined1 local_38 [32];
  
  if (*(longlong *)(param_1 + 0x18) != 0) {
    plVar6 = (longlong *)0x0;
    if (*param_2 != 0) {
      plVar6 = *(longlong **)(*param_2 + 0x10);
    }
    for (; plVar6 != (longlong *)0x0; plVar6 = (longlong *)FUN_180045a04((longlong)(plVar6 + 1),0))
    {
      uVar5 = (**(code **)(*plVar6 + 0x110))();
      if ((int)uVar5 < 0) {
        return uVar5;
      }
      plVar4 = *(longlong **)(param_1 + 8);
      plVar3 = (longlong *)0x0;
      if (plVar4 != (longlong *)0x0) {
        puVar2 = (undefined8 *)(**(code **)(*plVar6 + 0xe0))(plVar6,local_38);
        plVar3 = FUN_18006df80(plVar4,puVar2);
      }
      lVar1 = *(longlong *)(param_1 + 0x18);
      if (*(int *)(lVar1 + 0x10) != 0) {
        *(longlong **)(lVar1 + 8) = plVar6;
        if (((plVar3 == (longlong *)0x0) ||
            (plVar4 = (longlong *)(**(code **)(*plVar3 + 0x48))(), plVar4 == (longlong *)0x0)) ||
           (uVar5 = FUN_1800200dc(lVar1,plVar4), (int)uVar5 == 1)) {
          uVar5 = FUN_1800200dc(lVar1,(longlong *)(lVar1 + 0x18));
        }
        if ((int)uVar5 < 0) {
          return uVar5;
        }
      }
    }
    *(undefined4 *)(param_2 + 0xc) = 1;
  }
  return 0;
}


// FUN_1800200dc @ 1800200dc

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800200dc(longlong param_1,longlong *param_2)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  int iVar3;
  uint uVar4;
  longlong lVar5;
  short *psVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined4 *_Dst;
  undefined4 *puVar9;
  longlong *plVar10;
  code *pcVar11;
  longlong lVar12;
  size_t _Size;
  size_t sVar13;
  ulonglong uVar14;
  int local_res8 [2];
  undefined8 local_38;
  ulonglong uStack_30;
  undefined8 local_28;
  
  lVar5 = (**(code **)(**(longlong **)(param_1 + 8) + 0x80))();
  if (lVar5 == 0) {
    return 1;
  }
  local_res8[0] = 0;
  psVar6 = (short *)(**(code **)(**(longlong **)(param_1 + 8) + 0x80))();
  uVar7 = FUN_18001f36c(param_2,psVar6,local_res8);
  if ((int)uVar7 != 0) {
    return uVar7 & 0xffffffff;
  }
  sVar13 = 0xffffffffffffffff;
  if (local_res8[0] == -1) {
    return uVar7 & 0xffffffff;
  }
  iVar3 = FUN_18007b17c(param_2);
  uVar14 = (ulonglong)iVar3;
  uVar7 = 0x18;
  uVar8 = FUN_180009930(0x18,uVar14);
  if ((int)uVar8 == 0) {
    return 0x8007000e;
  }
  auVar1._8_8_ = 0;
  auVar1._0_8_ = uVar7 & 0xffffffff;
  auVar2._8_8_ = 0;
  auVar2._0_8_ = uVar14;
  _Size = SUB168(auVar1 * auVar2,0);
  if (SUB168(auVar1 * auVar2,8) != 0) {
    _Size = sVar13;
  }
  _Dst = (undefined4 *)thunk_FUN_18007ca58(_Size);
  if (_Dst == (undefined4 *)0x0) {
    _Dst = (undefined4 *)0x0;
  }
  else {
    memset(_Dst,0,_Size);
  }
  if (_Dst == (undefined4 *)0x0) {
    return 0x8007000e;
  }
  lVar5 = uVar14 - 1;
  puVar9 = _Dst;
  lVar12 = lVar5;
  if (0 < lVar5) {
    do {
      *puVar9 = 3;
      *(longlong *)(puVar9 + 2) = param_1;
      lVar12 = lVar12 + -1;
      puVar9 = puVar9 + 6;
    } while (lVar12 != 0);
  }
  _Dst[lVar5 * 6] = 1;
  *(undefined **)(_Dst + lVar5 * 6 + 2) = &DAT_180185250;
  local_28 = 0;
  local_38 = 0;
  uStack_30 = 0;
  uVar4 = FUN_18001f970(param_2,local_res8[0],(longlong)_Dst,iVar3,(undefined4 *)&local_38);
  uVar7 = uStack_30;
  uVar14 = (ulonglong)uVar4;
  if (uVar4 == 0) {
    plVar10 = *(longlong **)(param_1 + 8);
    pcVar11 = *(code **)(*plVar10 + 0x100);
    if ((int)uStack_30 == 8) goto LAB_1800202a6;
    (*pcVar11)(plVar10,uStack_30 & 0xffffffff);
    (**(code **)(**(longlong **)(param_1 + 8) + 0x60))();
    plVar10 = (longlong *)FUN_18005c630(*(longlong *)(param_1 + 8) + 8,0);
    if ((plVar10 == (longlong *)0x0) ||
       (iVar3 = (**(code **)(*plVar10 + 0x68))(plVar10), iVar3 != 0)) goto LAB_1800202b0;
    uVar7 = uVar7 & 0xffffffff;
    pcVar11 = *(code **)(*plVar10 + 0x100);
  }
  else {
    if (uVar4 != 1) goto LAB_1800202b0;
    plVar10 = *(longlong **)(param_1 + 8);
    uVar14 = 0;
    pcVar11 = *(code **)(*plVar10 + 0x100);
LAB_1800202a6:
    uVar7 = 8;
  }
  (*pcVar11)(plVar10,uVar7);
LAB_1800202b0:
  _o_free(_Dst);
  return uVar14;
}


// FUN_1800c7fa0 @ 1800c7fa0

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_1800c7fa0(longlong param_1,longlong *param_2,longlong *param_3,longlong param_4)

{
  longlong lVar1;
  short *psVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  int iVar5;
  undefined8 uVar6;
  size_t _Size;
  int *piVar7;
  longlong lVar8;
  ulonglong uVar9;
  int *piVar10;
  int *piVar11;
  uint uVar12;
  longlong lVar13;
  longlong lVar14;
  int *piVar15;
  int *piVar16;
  
  piVar10 = (int *)0x0;
  if (((param_2 == (longlong *)0x0) || (param_3 == (longlong *)0x0)) || (param_4 == 0)) {
    uVar12 = 0x80070057;
  }
  else {
    piVar16 = (int *)CONCAT44(0,*(uint *)(param_4 + 0x28));
    uVar9 = 4;
    lVar1 = *(longlong *)(param_4 + 0x18);
    lVar13 = lVar1;
    lVar14 = param_1;
    uVar6 = FUN_180009930(4,(ulonglong)piVar16);
    piVar11 = piVar10;
    if ((int)uVar6 != 0) {
      auVar3._8_8_ = 0;
      auVar3._0_8_ = uVar9 & 0xffffffff;
      auVar4._8_8_ = 0;
      auVar4._0_8_ = piVar16;
      _Size = SUB168(auVar3 * auVar4,0);
      if (SUB168(auVar3 * auVar4,8) != 0) {
        _Size = 0xffffffffffffffff;
      }
      piVar7 = (int *)thunk_FUN_18007ca58(_Size);
      piVar10 = (int *)0x0;
      lVar13 = lVar1;
      lVar14 = param_1;
      piVar11 = piVar10;
      if (piVar7 != (int *)0x0) {
        memset(piVar7,0,_Size);
        piVar10 = piVar7;
        piVar11 = (int *)0x0;
      }
    }
    uVar12 = ~-(uint)(piVar10 != (int *)0x0) & 0x8007000e;
    piVar7 = piVar10;
    piVar15 = piVar11;
    while ((lVar8 = -1, piVar15 < piVar16 && (piVar10 != (int *)0x0))) {
      psVar2 = *(short **)
                (*(longlong *)(*(longlong *)(lVar14 + 8) + 0x80) +
                (ulonglong)*(uint *)(lVar13 + (longlong)piVar15 * 8) * 8);
      if (psVar2 == (short *)0x0) {
LAB_1800c80fa:
        uVar12 = 0x8000ffff;
        goto LAB_1800c8178;
      }
      do {
        lVar8 = lVar8 + 1;
      } while (psVar2[lVar8] != (short)piVar11);
      if (((lVar8 != 2) || (*psVar2 != 0x23)) || (iVar5 = _o_iswdigit(psVar2[1]), iVar5 == 0))
      goto LAB_1800c80fa;
      iVar5 = _o__wtoi(psVar2 + 1);
      piVar15 = (int *)((longlong)piVar15 + 1);
      *piVar7 = iVar5 + 1;
      piVar11 = (int *)0x0;
      piVar7 = piVar7 + 1;
      lVar13 = lVar1;
      lVar14 = param_1;
    }
    while (((-1 < (int)uVar12 && (param_2 != (longlong *)0x0)) && (piVar11 < piVar16))) {
      iVar5 = (**(code **)(*param_2 + 0x1d0))(param_2);
      if ((iVar5 == 0) && (3 < piVar10[(longlong)piVar11])) {
        (**(code **)(*param_2 + 0x60))(param_2,1);
        uVar12 = (**(code **)(*param_2 + 0x100))(param_2);
      }
      piVar11 = (int *)((longlong)piVar11 + 1);
      if (param_2 == param_3) break;
      param_2 = (longlong *)FUN_180045a04((longlong)(param_2 + 1),0);
    }
    if (piVar10 != (int *)0x0) {
LAB_1800c8178:
      _o_free(piVar10);
    }
  }
  return uVar12;
}


