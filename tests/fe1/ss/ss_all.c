// FUN_18005d050 @ 18005d050

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_18005d050(longlong param_1,ushort *param_2,uint param_3)

{
  uint *puVar1;
  int iVar2;
  undefined8 uVar3;
  uint uVar4;
  undefined4 uVar5;
  longlong lVar7;
  uint uVar8;
  int iVar9;
  ushort *puVar10;
  undefined1 auStack_388 [32];
  int local_368 [187];
  int local_7c;
  int local_58;
  int local_54;
  ulonglong local_48;
  ulonglong uVar6;
  
  local_48 = DAT_1801c0240 ^ (ulonglong)auStack_388;
  uVar6 = 0;
  uVar5 = 0;
  puVar1 = (uint *)(param_1 + 0x20);
  *puVar1 = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  if (*(longlong *)(param_1 + 8) == 0) {
    return 0;
  }
  uVar4 = param_3;
  if (499 < param_3) {
    uVar4 = 500;
  }
  puVar10 = param_2;
  if (uVar4 != 0) {
    do {
      uVar3 = FUN_180072d30(*puVar10);
      if (((int)uVar3 == 0) && (uVar3 = FUN_180079ea4(*puVar10), (int)uVar3 == 0)) break;
      uVar8 = (int)uVar6 + 1;
      uVar6 = (ulonglong)uVar8;
      puVar10 = puVar10 + 1;
    } while (uVar8 < uVar4);
    if (499 < (uint)uVar6) {
      *puVar1 = 500;
      goto LAB_18005d142;
    }
  }
  FUN_180073fa0(local_368,*(undefined8 *)(param_1 + 8),*(undefined8 *)(param_1 + 0x18));
  iVar9 = (int)uVar6;
  FUN_180073970(local_368,param_2 + uVar6,param_3 - iVar9);
  uVar4 = local_7c + iVar9;
  *puVar1 = uVar4;
  if (uVar4 == 0) {
    if (param_3 != 0) {
      *puVar1 = 1;
    }
  }
  else if (500 < uVar4) {
    if (iVar9 == 0) {
      iVar9 = 499;
      lVar7 = 499;
      do {
        iVar2 = _o_iswspace(param_2[lVar7]);
        if ((iVar2 != 0) || (uVar3 = FUN_180079ea4(param_2[lVar7]), (int)uVar3 != 0)) break;
        iVar9 = iVar9 + -1;
        lVar7 = lVar7 + -1;
      } while (-1 < lVar7);
      lVar7 = (longlong)iVar9;
      if (-1 < iVar9) {
        do {
          iVar2 = _o_iswspace(param_2[lVar7]);
          if ((iVar2 == 0) && (uVar3 = FUN_180079ea4(param_2[lVar7]), (int)uVar3 == 0)) break;
          iVar9 = iVar9 + -1;
          lVar7 = lVar7 + -1;
        } while (-1 < lVar7);
      }
      if (iVar9 < 0) {
        iVar9 = 500;
      }
      else {
        iVar9 = iVar9 + 1;
      }
    }
    *(int *)(param_1 + 0x20) = iVar9;
    goto LAB_18005d142;
  }
  if ((local_58 != 0) || (local_54 != 0)) {
    uVar5 = 1;
  }
LAB_18005d142:
  *(undefined4 *)(param_1 + 0x24) = uVar5;
  return 1;
}


// FUN_1800293d4 @ 1800293d4

undefined8 * FUN_1800293d4(undefined8 param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)FUN_18007ca58(0x28);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    puVar1[3] = param_1;
    *puVar1 = CSentSepImpl::vftable;
    puVar1[1] = 0;
    puVar1[4] = 0;
    puVar2 = puVar1;
  }
  return puVar2;
}


// FUN_180047748 @ 180047748

uint FUN_180047748(longlong param_1,undefined2 param_2,int *param_3,ulonglong param_4)

{
  uint *puVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  uint uVar4;
  undefined8 uVar5;
  void *_Dst;
  uint uVar6;
  ulonglong uVar7;
  uint uVar8;
  uint *puVar9;
  uint uVar10;
  uint *puVar11;
  uint *puVar12;
  size_t _Size;
  
  if (*(int *)(param_1 + 0x20) != 0) {
    return 0x80048002;
  }
  puVar1 = (uint *)(param_3 + 1);
  puVar9 = (uint *)((param_4 & 0xffffffff) + (longlong)param_3);
  *(undefined2 *)(param_1 + 0x24) = param_2;
  uVar6 = 0;
  if (puVar9 <= puVar1) {
    return 0x80048018;
  }
  if (*param_3 != 0xc) {
    return 0x80048018;
  }
  puVar12 = (uint *)(param_3 + 0xd);
  if (puVar9 <= puVar12) {
    return 0x80048018;
  }
  uVar10 = 0;
  puVar11 = puVar1;
  uVar8 = 0;
  do {
    if ((int)uVar6 < 0) {
      return uVar6;
    }
    uVar6 = *puVar11 + uVar8;
    uVar4 = 0xffffffff;
    if (uVar8 <= uVar6) {
      uVar4 = uVar6;
    }
    uVar10 = uVar10 + 1;
    uVar6 = -(uint)(uVar6 < uVar8) & 0x80070216;
    puVar11 = puVar11 + 1;
    uVar8 = uVar4;
  } while (uVar10 < 0xc);
  if ((int)uVar6 < 0) {
    return uVar6;
  }
  uVar7 = 8;
  uVar5 = FUN_180009930(8,(ulonglong)uVar4);
  if ((int)uVar5 != 0) {
    auVar2._8_8_ = 0;
    auVar2._0_8_ = uVar7 & 0xffffffff;
    auVar3._8_8_ = 0;
    auVar3._0_8_ = CONCAT44(0,uVar4);
    _Size = SUB168(auVar2 * auVar3,0);
    if (SUB168(auVar2 * auVar3,8) != 0) {
      _Size = uVar7 - 9;
    }
    _Dst = (void *)thunk_FUN_18007ca58(_Size);
    if (_Dst != (void *)0x0) {
      memset(_Dst,0,_Size);
      puVar12 = (uint *)(param_3 + 0xd);
      goto LAB_18004788c;
    }
    puVar12 = (uint *)(param_3 + 0xd);
  }
  _Dst = (void *)0x0;
LAB_18004788c:
  *(void **)(param_1 + 0xe8) = _Dst;
  if (_Dst == (void *)0x0) {
    return 0x8007000e;
  }
  if (puVar12 + CONCAT44(0,uVar4) < puVar9) {
    uVar8 = 0;
    while( true ) {
      uVar7 = (ulonglong)uVar8;
      if (uVar4 <= uVar8) {
        if (-1 < (int)uVar6) {
          *(void **)(param_1 + 0x68) = _Dst;
          *(uint *)(param_1 + 0x70) = *puVar1;
          uVar8 = *puVar1;
          *(void **)(param_1 + 0x78) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0x80) = param_3[2];
          uVar8 = uVar8 + param_3[2];
          *(void **)(param_1 + 0x48) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0x50) = param_3[3];
          uVar8 = uVar8 + param_3[3];
          *(void **)(param_1 + 0x98) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0xa0) = param_3[4];
          uVar8 = uVar8 + param_3[4];
          *(void **)(param_1 + 0x28) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0x30) = param_3[5];
          uVar8 = uVar8 + param_3[5];
          *(void **)(param_1 + 0x38) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0x40) = param_3[6];
          uVar8 = uVar8 + param_3[6];
          *(void **)(param_1 + 0x58) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0x60) = param_3[7];
          uVar8 = uVar8 + param_3[7];
          *(void **)(param_1 + 0x88) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0x90) = param_3[8];
          uVar8 = uVar8 + param_3[8];
          *(void **)(param_1 + 0xb8) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0xc0) = param_3[9];
          uVar8 = uVar8 + param_3[9];
          *(void **)(param_1 + 0xd8) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0xe0) = param_3[10];
          uVar8 = uVar8 + param_3[10];
          *(void **)(param_1 + 0xa8) = (void *)((longlong)_Dst + (ulonglong)uVar8 * 8);
          *(int *)(param_1 + 0xb0) = param_3[0xb];
          *(void **)(param_1 + 200) =
               (void *)((longlong)_Dst + (ulonglong)(uVar8 + param_3[0xb]) * 8);
          *(int *)(param_1 + 0xd0) = param_3[0xc];
          *(undefined4 *)(param_1 + 0x20) = 1;
          return uVar6;
        }
        return uVar6;
      }
      *(ulonglong *)((longlong)_Dst + uVar7 * 8) =
           (ulonglong)puVar12[uVar7] + (longlong)(puVar12 + CONCAT44(0,uVar4));
      _Dst = *(void **)(param_1 + 0xe8);
      if (puVar9 <= *(uint **)((longlong)_Dst + uVar7 * 8)) break;
      uVar8 = uVar8 + 1;
    }
  }
  return 0x80048018;
}


// FUN_18007b43c @ 18007b43c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_18007b43c(longlong param_1,undefined2 param_2,longlong *param_3)

{
  uint uVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  wchar_t *pwVar5;
  undefined1 auStack_298 [32];
  uint *local_278;
  int local_268;
  uint local_264;
  int *local_260;
  undefined *local_258;
  wchar_t local_248 [264];
  ulonglong local_38;
  
  local_38 = DAT_1801c0240 ^ (ulonglong)auStack_298;
  local_268 = 0;
  memset(local_248,0,0x208);
  uVar1 = (**(code **)(*param_3 + 0x20))(param_3,&DAT_180182590,&DAT_1801825a0,&local_268);
  if (-1 < (int)uVar1) {
    if (local_268 == 0) {
      uVar3 = (**(code **)(*param_3 + 0x10))(param_3);
      pwVar5 = L"SENTSEP_%s";
    }
    else {
      uVar3 = (**(code **)(*param_3 + 0x18))();
      pwVar5 = L"UPDATE_SENTSEP_%s";
    }
    uVar1 = FUN_1800179d4(local_248,0x104,pwVar5,uVar3);
  }
  uVar4 = (ulonglong)uVar1;
  local_258 = &DAT_1801c0dc0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_1801c0dc0);
  if (((int)uVar1 < 0) || (*(longlong *)(param_1 + 0x68) != 0)) goto LAB_18007b5d4;
  puVar2 = FUN_1800b528c((ushort *)local_248,(undefined8 *)(param_1 + 0x68));
  uVar4 = (ulonglong)puVar2 & 0xffffffff;
  if (((int)puVar2 < 0) || (*(int *)(*(longlong *)(param_1 + 0x68) + 0x20) != 0))
  goto LAB_18007b5d4;
  local_260 = (int *)0x0;
  local_264 = 0;
  local_278 = &local_264;
  uVar1 = (**(code **)(*param_3 + 8))(param_3,&DAT_180182590,&DAT_1801825a0,&local_260);
  uVar4 = (ulonglong)uVar1;
  if ((int)uVar1 < 0) {
    if (uVar1 == 0x8004801a) {
      uVar3 = FUN_1800c0c84(*(longlong *)(param_1 + 0x68),param_2);
      uVar1 = (uint)uVar3;
      goto LAB_18007b5b3;
    }
  }
  else {
    uVar1 = FUN_180047748(*(longlong *)(param_1 + 0x68),param_2,local_260,(ulonglong)local_264);
LAB_18007b5b3:
    uVar4 = (ulonglong)uVar1;
    if (-1 < (int)uVar1) goto LAB_18007b5d4;
  }
  FUN_18002d720((undefined8 *)
                (-(ulonglong)(*(longlong *)(param_1 + 0x68) != 0) &
                *(longlong *)(param_1 + 0x68) + 8U));
  *(undefined8 *)(param_1 + 0x68) = 0;
LAB_18007b5d4:
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_1801c0dc0);
  return uVar4;
}


// FUN_180072d30 @ 180072d30

undefined8 FUN_180072d30(ushort param_1)

{
  uint uVar1;
  undefined8 uVar2;
  
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 8;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x800000;
  }
  if ((((((uVar1 == 0) && (0x1e < (ushort)(param_1 - 1))) && (0x20 < (ushort)(param_1 - 0x7f))) &&
       ((param_1 != 0x202f && (param_1 != 0x205f)))) &&
      ((param_1 != 0x2060 && ((param_1 != 0x2420 && (param_1 != 0x2422)))))) &&
     ((param_1 != 0x2423 && (param_1 != 0x2424)))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}


// FUN_180079ea4 @ 180079ea4

undefined8 FUN_180079ea4(short param_1)

{
  if ((((param_1 != 10) && (param_1 != 0xb)) && (param_1 != 0xd)) && (param_1 != 0x8d)) {
    return 0;
  }
  return 1;
}


// FUN_180073fa0 @ 180073fa0

undefined4 * FUN_180073fa0(undefined4 *param_1,undefined8 param_2,undefined8 param_3)

{
  *param_1 = 0;
  *(undefined8 *)(param_1 + 0x1e) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 0x12) = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  param_1[0x14] = 0;
  param_1[6] = 0;
  *(undefined8 *)(param_1 + 0x22) = param_2;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 10) = 0;
  *(undefined8 *)(param_1 + 0xc) = 0;
  param_1[0xe] = 0;
  *(undefined8 *)(param_1 + 0x16) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x1a) = 0;
  param_1[0x1c] = 0;
  param_1[0x20] = 0;
  param_1[0x24] = 1;
  *(undefined8 *)(param_1 + 0x26) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x2a) = 0;
  param_1[0x2c] = 0;
  *(undefined8 *)(param_1 + 0x2e) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x32) = 0;
  param_1[0x34] = 0;
  *(undefined8 *)(param_1 + 0x36) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x3a) = 0;
  param_1[0x3c] = 0;
  *(undefined8 *)(param_1 + 0x3e) = 0;
  param_1[0x41] = 0xffffffff;
  param_1[0x40] = 0;
  *(undefined8 *)(param_1 + 0xa7) = 0;
  *(undefined8 *)(param_1 + 0xa9) = 0;
  param_1[0xa6] = 0;
  *(undefined8 *)(param_1 + 0xab) = 0;
  param_1[0xad] = 0;
  param_1[0xbd] = 0;
  *(undefined8 *)(param_1 + 0xb2) = param_2;
  *(undefined8 *)(param_1 + 0xc6) = param_3;
  return param_1;
}


// FUN_180073970 @ 180073970

int FUN_180073970(int *param_1,undefined8 param_2,int param_3)

{
  int iVar1;
  ulonglong uVar2;
  
  *param_1 = -1;
  *(undefined8 *)(param_1 + 0xb8) = param_2;
  param_1[0xbc] = param_3;
  FUN_180073a18((longlong)param_1);
  iVar1 = *param_1;
  while( true ) {
    if (iVar1 == -7) {
      *param_1 = 0;
      FUN_1800686e0((longlong)param_1);
      return param_1[0xc5];
    }
    if (iVar1 == -6) break;
    if (iVar1 == -5) {
      iVar1 = FUN_18016225c((longlong)param_1);
      goto LAB_1800739f0;
    }
    if (iVar1 == -4) {
      iVar1 = FUN_180161ff8((longlong)param_1);
      goto LAB_1800739f0;
    }
    if (iVar1 == -3) {
      iVar1 = FUN_180161a1c((longlong)param_1);
      goto LAB_1800739f0;
    }
    if (iVar1 == -2) {
      uVar2 = FUN_180064630((longlong)param_1);
      iVar1 = (int)uVar2;
      goto LAB_1800739f0;
    }
    if (iVar1 == -1) {
      iVar1 = FUN_1801623e0((longlong)param_1);
LAB_1800739f0:
      *param_1 = iVar1;
    }
  }
  iVar1 = FUN_180161e00((longlong)param_1);
  goto LAB_1800739f0;
}


// FUN_18007ca58 @ 18007ca58

void FUN_18007ca58(longlong param_1)

{
  FUN_18007c6f8(param_1);
  return;
}


// FUN_180009930 @ 180009930

undefined8 FUN_180009930(ulonglong param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  
  if ((param_2 < 0x100000000) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     param_2 <= SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffff)) / auVar1,0))) {
    return 1;
  }
  return 0;
}


// FUN_1800179d4 @ 1800179d4

undefined4 FUN_1800179d4(wchar_t *param_1,longlong param_2,wchar_t *param_3,undefined8 param_4)

{
  size_t _Count;
  int iVar1;
  undefined4 uVar2;
  undefined8 local_res20;
  
  if (param_2 - 1U < 0x7fffffff) {
    _Count = param_2 - 1;
    uVar2 = 0;
    local_res20 = param_4;
    iVar1 = FID_conflict__vsnprintf(param_1,_Count,param_3,(va_list)&local_res20);
    if ((iVar1 < 0) || (_Count < (ulonglong)(longlong)iVar1)) {
      uVar2 = 0x8007007a;
    }
    else if ((longlong)iVar1 != _Count) {
      return 0;
    }
    param_1[_Count] = L'\0';
  }
  else {
    uVar2 = 0x80070057;
    if (param_2 != 0) {
      *param_1 = L'\0';
    }
  }
  return uVar2;
}


// FUN_1800b528c @ 1800b528c

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8 * FUN_1800b528c(ushort *param_1,undefined8 *param_2)

{
  longlong *plVar1;
  uint uVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  undefined8 *puVar5;
  undefined8 local_res18;
  undefined8 *local_res20;
  
  FUN_18005bd20(&local_res18,(LPCRITICAL_SECTION)&DAT_1801c0dc0);
  puVar3 = (undefined8 *)FUN_1800264ac(0x1801c0dc0,param_1);
  puVar5 = (undefined8 *)0x0;
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)FUN_18007c6f8(0xf0);
    plVar1 = puVar3 + 1;
    *(undefined4 *)(puVar3 + 3) = 0;
    puVar3[2] = 0;
    *puVar3 = CSentSepInfo::vftable;
    *plVar1 = (longlong)CSentSepInfo::vftable;
    *(undefined4 *)(puVar3 + 4) = 0;
    *(undefined2 *)((longlong)puVar3 + 0x24) = 0;
    puVar3[0x1d] = 0;
    local_res20 = puVar3;
    uVar4 = FUN_18002652c((longlong)plVar1,param_1);
    puVar5 = (undefined8 *)(uVar4 & 0xffffffff);
    if ((int)uVar4 < 0) goto LAB_1800b5362;
    uVar2 = (**(code **)(*plVar1 + 8))(plVar1);
    puVar5 = (undefined8 *)(ulonglong)uVar2;
    if ((int)uVar2 < 0) goto LAB_1800b5362;
    uVar4 = FUN_180026564(0x1801c0dc0,(ushort *)puVar3[2],puVar3);
    puVar5 = (undefined8 *)(uVar4 & 0xffffffff);
    if ((int)uVar4 < 0) goto LAB_1800b5362;
  }
  *param_2 = puVar3;
  LOCK();
  *(int *)(puVar3 + 3) = *(int *)(puVar3 + 3) + 1;
  UNLOCK();
  puVar3 = (undefined8 *)0x0;
LAB_1800b5362:
  FUN_18007b110(&local_res18);
  if (puVar3 != (undefined8 *)0x0) {
    (**(code **)(puVar3[1] + 0x10))(puVar3 + 1,1);
  }
  return puVar5;
}


// FUN_1800c0c84 @ 1800c0c84

undefined8 FUN_1800c0c84(longlong param_1,undefined2 param_2)

{
  if (*(int *)(param_1 + 0x20) != 0) {
    return 0x80048002;
  }
  *(undefined2 *)(param_1 + 0x24) = param_2;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined8 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined8 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined8 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined8 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined8 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined8 *)(param_1 + 0xa8) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined8 *)(param_1 + 0xb8) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  *(undefined8 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined8 *)(param_1 + 0xd8) = 0;
  *(undefined4 *)(param_1 + 0xe0) = 0;
  *(undefined8 *)(param_1 + 0xe8) = 0;
  *(undefined4 *)(param_1 + 0x20) = 1;
  return 0;
}


// FUN_18002d720 @ 18002d720

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

void FUN_18002d720(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)();
  }
  return;
}


// FUN_180072dbc @ 180072dbc

undefined4 FUN_180072dbc(ushort param_1)

{
  ulonglong uVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = (ulonglong)(param_1 >> 8);
  if (*(short *)(&DAT_180171e80 + uVar1 * 0x10) == 1) {
    return *(undefined4 *)(&PTR_DAT_180171e88 + uVar1 * 2);
  }
  pbVar2 = (&PTR_DAT_180171e88)[uVar1 * 2];
  bVar4 = (byte)param_1;
  if (*(short *)(&DAT_180171e80 + uVar1 * 0x10) == 2) {
    uVar1 = (ulonglong)pbVar2[bVar4];
  }
  else if (*(ushort *)(&DAT_180171e82 + uVar1 * 0x10) < 4) {
    for (; *pbVar2 < bVar4; pbVar2 = pbVar2 + 2) {
    }
    uVar1 = (ulonglong)pbVar2[1];
  }
  else {
    uVar3 = 0;
    uVar6 = (uint)*(ushort *)(&DAT_180171e82 + uVar1 * 0x10);
    do {
      while( true ) {
        uVar5 = uVar3;
        if ((int)uVar6 <= (int)uVar3) goto LAB_180072e40;
        uVar5 = (int)(uVar6 + uVar3) >> 1;
        if (bVar4 <= pbVar2[(int)(uVar5 * 2)]) break;
        uVar3 = uVar5 + 1;
      }
      uVar6 = uVar5;
    } while (bVar4 < pbVar2[(int)(uVar5 * 2)]);
LAB_180072e40:
    uVar1 = (ulonglong)pbVar2[(longlong)(int)(uVar5 * 2) + 1];
  }
  return *(undefined4 *)(&DAT_180192970 + uVar1 * 4);
}


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


// FUN_18007c6f8 @ 18007c6f8

void FUN_18007c6f8(longlong param_1)

{
  code *pcVar1;
  longlong lVar2;
  int iVar3;
  
  do {
    lVar2 = _o_malloc(param_1);
    if (lVar2 != 0) {
      return;
    }
    iVar3 = _o__callnewh(param_1);
  } while (iVar3 != 0);
  if (param_1 == -1) {
                    /* WARNING: Subroutine does not return */
    FUN_1800cf160();
  }
  FUN_18007cc74();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}


// FUN_18005bd20 @ 18005bd20

undefined8 * FUN_18005bd20(undefined8 *param_1,LPCRITICAL_SECTION param_2)

{
  *param_1 = param_2;
  if (param_2 != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(param_2);
  }
  return param_1;
}


// FUN_1800264ac @ 1800264ac

undefined8 FUN_1800264ac(longlong param_1,ushort *param_2)

{
  short sVar1;
  short sVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  ulonglong uVar5;
  short *psVar6;
  ushort *puVar7;
  longlong lVar8;
  
  plVar3 = *(longlong **)(param_1 + 0x30);
  uVar5 = 0;
  if (plVar3 == (longlong *)0x0) {
    return 0;
  }
  puVar7 = param_2;
  if (*plVar3 != 0) {
    for (; *puVar7 != 0; puVar7 = puVar7 + 1) {
      uVar5 = (ulonglong)((int)uVar5 * 0x1003f + (uint)*puVar7);
    }
    for (puVar4 = *(undefined8 **)(*plVar3 + (uVar5 % (ulonglong)*(uint *)(plVar3 + 1)) * 8);
        puVar4 != (undefined8 *)0x0; puVar4 = (undefined8 *)puVar4[2]) {
      psVar6 = (short *)*puVar4;
      lVar8 = (longlong)param_2 - (longlong)psVar6;
      do {
        sVar1 = *psVar6;
        sVar2 = *(short *)((longlong)psVar6 + lVar8);
        if (sVar1 != sVar2) break;
        psVar6 = psVar6 + 1;
      } while (sVar2 != 0);
      if (sVar1 == sVar2) {
        return puVar4[1];
      }
    }
  }
  return 0;
}


// FUN_18002652c @ 18002652c

undefined8 FUN_18002652c(longlong param_1,undefined8 param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  
  lVar1 = _o__wcsdup();
  uVar2 = 0;
  *(longlong *)(param_1 + 8) = lVar1;
  if (lVar1 == 0) {
    uVar2 = 0x8007000e;
  }
  return uVar2;
}


// FUN_180026564 @ 180026564

undefined8 FUN_180026564(longlong param_1,ushort *param_2,undefined8 param_3)

{
  longlong *plVar1;
  undefined8 uVar2;
  
  plVar1 = *(longlong **)(param_1 + 0x30);
  if (plVar1 == (longlong *)0x0) {
    plVar1 = (longlong *)FUN_18007ca58(0x10);
    if (plVar1 != (longlong *)0x0) {
      *plVar1 = 0;
      *(undefined4 *)(plVar1 + 1) = 100;
    }
    *(longlong **)(param_1 + 0x30) = plVar1;
    if (plVar1 == (longlong *)0x0) {
      return 0x8007000e;
    }
  }
  uVar2 = FUN_180075cac(plVar1,param_2,param_3);
  return uVar2;
}


// FUN_18007b110 @ 18007b110

void FUN_18007b110(undefined8 *param_1)

{
  if ((LPCRITICAL_SECTION)*param_1 != (LPCRITICAL_SECTION)0x0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)*param_1);
  }
  return;
}


// FUN_18003da24 @ 18003da24

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

void FUN_18003da24(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  ushort uVar5;
  undefined7 extraout_var;
  undefined8 *puVar6;
  int *piVar7;
  
  puVar6 = (undefined8 *)(param_1 + 0xb8);
  FUN_18007b2e4((undefined8 *)(param_1 + 0xd8),puVar6);
  plVar1 = (longlong *)(param_1 + 0x98);
  FUN_18007b2e4(puVar6,plVar1);
  *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xc0);
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(param_1 + 0x18);
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  uVar5 = (**(code **)(**(longlong **)(param_1 + 0x2c8) + 0x68))();
  FUN_18003dbc0((longlong *)(param_1 + 8),plVar1,(uint)((uVar5 & 0x3ff) == 0x12),
                *(longlong *)(param_1 + 0x318));
  piVar7 = (int *)(param_1 + 0xa8);
  *(uint *)(param_1 + 0x2d4) = *(uint *)(param_1 + 0x2d4) | *(uint *)(param_1 + 0x7c);
  *(uint *)(param_1 + 0x2d8) = *(uint *)(param_1 + 0x2d8) | *(uint *)(param_1 + 0x80);
  if (((*(int *)(param_1 + 0xb0) != 0) && (*piVar7 == 0)) ||
     (bVar4 = FUN_18007b288(plVar1), (int)CONCAT71(extraout_var,bVar4) != 0)) {
    *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xa0);
    return;
  }
  iVar2 = *(int *)(param_1 + 0xa0);
  iVar3 = *piVar7;
  *(int *)(param_1 + 0xf8) = iVar2;
  if (((iVar2 == 3) || (iVar2 == 4)) || ((iVar2 == 5 || ((iVar2 == 6 || (iVar2 == 7)))))) {
    *(int *)(param_1 + 0x300) = *(int *)(param_1 + 0x300) + iVar3;
    *(int *)(param_1 + 0x2fc) = *(int *)(param_1 + 0x2fc) + 1;
    if (*(int *)(param_1 + 0x30c) != 0) {
      *(int *)(param_1 + 0x308) = *(int *)(param_1 + 0x308) + 1;
      goto LAB_18003db84;
    }
  }
  else {
    if (iVar2 != 0xc) {
      if (iVar2 == 0xe) {
        if (*(short *)(*(longlong *)(param_1 + 0x98) + (ulonglong)*(uint *)(param_1 + 0xa4) * 2) ==
            0x3b) {
          *(undefined4 *)(param_1 + 0x30c) = 1;
        }
        goto LAB_18003db98;
      }
      if (iVar2 == 0x10) {
        *(undefined4 *)(param_1 + 0x314) = 1;
        return;
      }
      if (iVar2 != 0x12) goto LAB_18003db8b;
    }
LAB_18003db84:
    *(undefined4 *)(param_1 + 0x30c) = 0;
  }
LAB_18003db8b:
  if (iVar2 - 1U < 2) {
    return;
  }
  if (iVar2 == 0x10) {
    return;
  }
LAB_18003db98:
  *(int *)(param_1 + 0x304) = *(int *)(param_1 + 0x304) + iVar3;
  return;
}


// FUN_18007b288 @ 18007b288

bool FUN_18007b288(longlong *param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if ((int)param_1[2] == 1) {
    bVar1 = *(short *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2) == 0;
  }
  return bVar1;
}


// FUN_18007ad50 @ 18007ad50

ulonglong FUN_18007ad50(longlong *param_1)

{
  bool bVar1;
  undefined7 extraout_var;
  ulonglong uVar2;
  
  uVar2 = 0;
  if ((int)param_1[3] == 0) {
    bVar1 = FUN_18007b288(param_1);
    if ((int)CONCAT71(extraout_var,bVar1) == 0) goto LAB_18007ad6c;
  }
  uVar2 = 1;
LAB_18007ad6c:
  return uVar2 & 0xffffffff;
}


// FUN_1801619e4 @ 1801619e4

uint FUN_1801619e4(ushort param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 1;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x100000;
  }
  return uVar1;
}


// FUN_180161db0 @ 180161db0

undefined8 FUN_180161db0(longlong *param_1)

{
  int iVar1;
  
  if ((((int)param_1[1] != 3) ||
      (iVar1 = _o_iswdigit(*(undefined2 *)
                            (*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2)),
      iVar1 == 0)) && ((int)param_1[1] != 4)) {
    return 0;
  }
  return 1;
}


// FUN_180161028 @ 180161028

undefined8 FUN_180161028(int *param_1)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if ((0 < *param_1) || (0 < param_1[4])) {
    uVar1 = 1;
  }
  return uVar1;
}


// FUN_180066b20 @ 180066b20

uint FUN_180066b20(ushort param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 2;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x200000;
  }
  return uVar1;
}


// FUN_18016330c @ 18016330c

undefined8 FUN_18016330c(int *param_1,int *param_2)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if ((*param_1 == 0) && (-1 < param_1[1])) {
    uVar1 = 1;
    *param_2 = param_1[(longlong)param_1[1] + 0x34];
  }
  return uVar1;
}


// FUN_1801628d0 @ 1801628d0

void FUN_1801628d0(int *param_1,longlong *param_2,longlong param_3)

{
  undefined2 local_res20 [4];
  
  local_res20[0] = 0;
  FUN_180163334(param_1,param_2,param_3,local_res20);
  return;
}


// FUN_180161040 @ 180161040

void FUN_180161040(int *param_1,longlong *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined8 uVar2;
  short sVar3;
  uint uVar4;
  
  uVar4 = *(uint *)((longlong)param_2 + 0xc);
  sVar3 = *(short *)(*param_2 + (ulonglong)uVar4 * 2);
  if ((sVar3 - 0xabU & 0xffef) == 0) {
    iVar1 = param_1[4];
    if (sVar3 == 0xab) {
      if (iVar1 == 0) {
        param_1[7] = uVar4;
      }
      iVar1 = iVar1 + 1;
    }
    else {
      iVar1 = iVar1 + -1;
    }
    param_1[4] = iVar1;
  }
  else {
    if ((int)param_2[1] != 0xd) {
      sVar3 = *(short *)(*param_2 + (ulonglong)((int)param_2[2] + -1 + uVar4) * 2);
    }
    uVar2 = FUN_180160fe0(sVar3);
    if ((int)uVar2 == 0) {
      uVar2 = FUN_1800632f4(sVar3);
      if ((int)uVar2 != 0) {
        if (param_4 == 0) {
          iVar1 = param_1[1];
          if (param_3 == 0) {
            iVar1 = iVar1 + -1;
          }
          else {
            if (iVar1 == 0) {
              param_1[5] = uVar4;
            }
            if (param_5 != 0) {
              param_1[3] = param_1[3] + 1;
            }
            iVar1 = iVar1 + 1;
          }
          param_1[1] = iVar1;
        }
        else {
          param_1[2] = param_1[2] + 1;
        }
      }
    }
    else {
      iVar1 = *param_1;
      if (param_3 == 0) {
        iVar1 = iVar1 + -1;
      }
      else {
        if (iVar1 == 0) {
          param_1[6] = uVar4;
        }
        iVar1 = iVar1 + 1;
      }
      *param_1 = iVar1;
    }
  }
  return;
}


// FUN_1801628a0 @ 1801628a0

void FUN_1801628a0(int *param_1)

{
  if (*param_1 < 0) {
    *param_1 = 0;
    param_1[6] = 0;
  }
  if (param_1[4] < 0) {
    param_1[4] = 0;
    param_1[7] = 0;
  }
  if (param_1[1] < 0) {
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[5] = 0;
  }
  return;
}


// FUN_180160fe0 @ 180160fe0

undefined8 FUN_180160fe0(short param_1)

{
  if ((((0x28 < (ushort)(param_1 - 0x93U)) ||
       ((0x10001000003U >> ((ulonglong)(ushort)(param_1 - 0x93U) & 0x3f) & 1) == 0)) &&
      (param_1 != 0x22)) && (3 < (ushort)(param_1 + 0xdfe4U))) {
    return 0;
  }
  return 1;
}


// FUN_1800632f4 @ 1800632f4

undefined8 FUN_1800632f4(short param_1)

{
  undefined8 uVar1;
  
  if ((((param_1 != 0x27) && (param_1 != 0x91)) &&
      ((0x21 < (ushort)(param_1 + 0xdfe8U) ||
       ((0x200000009U >> ((ulonglong)(ushort)(param_1 + 0xdfe8U) & 0x3f) & 1) == 0)))) &&
     (uVar1 = FUN_180079148(param_1), (int)uVar1 == 0)) {
    return 0;
  }
  return 1;
}


// FUN_1801616b0 @ 1801616b0

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_1801616b0(longlong param_1,short *param_2,ulonglong param_3)

{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  short *psVar4;
  longlong lVar5;
  
  uVar3 = param_3 & 0xffffffff;
  uVar1 = (uint)param_3;
  psVar4 = param_2 + ((param_3 & 0xffffffff) - 1);
  if (param_2 < psVar4) {
    lVar5 = (longlong)psVar4 - (longlong)param_2;
    do {
      if ((ushort)(*psVar4 + 0xdff0U) < 2) {
        uVar3 = lVar5 >> 1;
      }
      uVar1 = (uint)uVar3;
      psVar4 = psVar4 + -1;
      lVar5 = lVar5 + -2;
    } while (param_2 < psVar4);
  }
  if (uVar1 < 0x80) {
    plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 8))();
    uVar3 = FUN_180061864((longlong)param_2,uVar1,plVar2);
    uVar1 = ~(uint)uVar3 >> 0x1f;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// FUN_180061864 @ 180061864

ulonglong FUN_180061864(longlong param_1,uint param_2,longlong *param_3)

{
  ushort uVar1;
  ulonglong uVar2;
  int iVar3;
  longlong lVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  
  iVar7 = 0;
  if (param_3 != (longlong *)0x0) {
    iVar6 = (int)param_3[1] + -1;
    while (iVar7 <= iVar6) {
      uVar2 = (longlong)(iVar6 + iVar7) / 2;
      iVar3 = (int)uVar2;
      puVar5 = *(ushort **)(*param_3 + (longlong)iVar3 * 8);
      lVar4 = param_1 - (longlong)puVar5;
      for (uVar8 = 0; uVar8 < param_2; uVar8 = uVar8 + 1) {
        if (*puVar5 == 0) goto LAB_1800618e4;
        uVar1 = *(ushort *)(lVar4 + (longlong)puVar5);
        if (uVar1 < *puVar5) goto LAB_1800618de;
        if (uVar1 != *puVar5) goto LAB_1800618e4;
        puVar5 = puVar5 + 1;
      }
      if (uVar8 == param_2) {
        if (*puVar5 == 0) {
          return uVar2 & 0xffffffff;
        }
LAB_1800618de:
        iVar6 = iVar3 + -1;
      }
      else {
LAB_1800618e4:
        iVar7 = iVar3 + 1;
      }
    }
  }
  return 0xffffffff;
}


// FUN_18003f9ac @ 18003f9ac

uint FUN_18003f9ac(ushort param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 7;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x10400000;
  }
  return uVar1;
}


// FUN_1801628f4 @ 1801628f4

undefined8 FUN_1801628f4(longlong *param_1)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  ushort *puVar4;
  uint uVar5;
  
  bVar2 = false;
  uVar5 = 0;
  uVar1 = *(uint *)(param_1 + 2);
  puVar4 = (ushort *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2);
  do {
    if (uVar1 <= uVar5) {
      return 1;
    }
    if (bVar2) {
      if (bVar2) {
        if (*puVar4 != 0x2e) {
          return 0;
        }
        bVar2 = false;
      }
    }
    else {
      uVar3 = FUN_1801619e4(*puVar4);
      if (uVar3 == 0) {
        return 0;
      }
      bVar2 = true;
    }
    uVar5 = uVar5 + 1;
    puVar4 = puVar4 + 1;
  } while( true );
}


// FUN_18016296c @ 18016296c

undefined8 FUN_18016296c(longlong *param_1)

{
  wchar_t _Ch;
  wchar_t *pwVar1;
  undefined8 uVar2;
  uint uVar3;
  wchar_t *pwVar4;
  
  pwVar4 = (wchar_t *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2);
  if (pwVar4 == (wchar_t *)0x0) {
LAB_1801629be:
    uVar2 = 0;
  }
  else {
    for (uVar3 = 0; uVar3 < *(uint *)(param_1 + 2); uVar3 = uVar3 + 1) {
      _Ch = *pwVar4;
      pwVar4 = pwVar4 + 1;
      pwVar1 = wcschr(L"iIvVxXlLcCdDmM",_Ch);
      if (pwVar1 == (wchar_t *)0x0) goto LAB_1801629be;
    }
    uVar2 = 1;
  }
  return uVar2;
}


// FUN_1801629d8 @ 1801629d8

bool FUN_1801629d8(longlong *param_1)

{
  undefined2 *puVar1;
  longlong lVar2;
  uint uVar3;
  longlong lVar4;
  int iVar5;
  uint uVar6;
  undefined2 *puVar7;
  ulonglong uVar8;
  
  uVar8 = (ulonglong)*(uint *)((longlong)param_1 + 0xc);
  lVar4 = *param_1;
  uVar6 = 0;
  uVar3 = *(uint *)(param_1 + 2);
  puVar1 = (undefined2 *)(lVar4 + uVar8 * 2);
  puVar7 = puVar1;
  if (uVar3 != 0) {
    do {
      iVar5 = _o_iswdigit(*puVar7);
      if (iVar5 == 0) break;
      uVar6 = uVar6 + 1;
      puVar7 = puVar7 + 1;
    } while (uVar6 < uVar3);
    if (uVar6 != 0) {
      if ((uVar6 == uVar3 - 1) &&
         ((lVar2 = uVar6 + uVar8, *(short *)(lVar4 + lVar2 * 2) == 0x61 ||
          (*(short *)(lVar4 + lVar2 * 2) == 0x6f)))) {
        return true;
      }
      if ((uVar6 == uVar3 - 2) && (puVar1[uVar6] == 0x65)) {
        return *(short *)(lVar4 + ((uVar6 + 1) + uVar8) * 2) == 0x72;
      }
    }
  }
  return false;
}


// FUN_180160f40 @ 180160f40

ulonglong FUN_180160f40(int *param_1,longlong *param_2)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  uint uVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  
  iVar1 = (int)param_2[2];
  iVar2 = *(int *)((longlong)param_2 + 0xc);
  lVar3 = *param_2;
  uVar8 = 0;
  uVar5 = FUN_1800632f4(*(short *)(lVar3 + (ulonglong)(uint)(iVar1 + -1 + iVar2) * 2));
  if ((int)uVar5 != 0) {
    uVar4 = (uint)uVar8;
    uVar6 = uVar4 + 1;
    uVar7 = uVar4;
    if (((int)uVar6 < iVar1) &&
       ((*(short *)(lVar3 + (ulonglong)(uint)(iVar1 + -2 + iVar2) * 2) - 0x53U & 0xffdf) == 0)) {
      uVar7 = uVar6;
    }
    FUN_180161040(param_1,param_2,0,uVar7,uVar4);
    uVar8 = (ulonglong)uVar6;
  }
  return uVar8 & 0xffffffff;
}


// FUN_180161d5c @ 180161d5c

undefined4 FUN_180161d5c(longlong *param_1,longlong param_2)

{
  int iVar1;
  longlong lVar2;
  undefined4 uVar3;
  
  lVar2 = -1;
  do {
    lVar2 = lVar2 + 1;
  } while (*(short *)(param_2 + lVar2 * 2) != 0);
  uVar3 = 0;
  if ((int)lVar2 == (int)param_1[2]) {
    iVar1 = _o__wcsnicmp(param_2,*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2,
                         (int)param_1[2]);
    uVar3 = 0;
    if (iVar1 == 0) {
      uVar3 = 1;
    }
  }
  return uVar3;
}


// FUN_180161740 @ 180161740

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_180161740(longlong param_1,longlong param_2,uint param_3)

{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined1 auStack_138 [32];
  ushort local_118 [128];
  ulonglong local_18;
  
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_138;
  if (param_3 < 0x80) {
    FUN_180058730((short *)local_118,0x80,param_2,(ulonglong)param_3);
    uVar1 = FUN_1801631c8(local_118,param_3);
    if (uVar1 == param_3) {
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x38))();
      uVar3 = FUN_180061864((longlong)local_118,param_3,plVar2);
      return ~(uint)uVar3 >> 0x1f;
    }
  }
  return 0;
}


// FUN_1801617e4 @ 1801617e4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_1801617e4(longlong param_1,longlong param_2,uint param_3)

{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined1 auStack_138 [32];
  ushort local_118 [128];
  ulonglong local_18;
  
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_138;
  if (param_3 < 0x80) {
    FUN_180058730((short *)local_118,0x80,param_2,(ulonglong)param_3);
    uVar1 = FUN_1801631c8(local_118,param_3);
    if (uVar1 == param_3) {
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x18))();
      uVar3 = FUN_180061864((longlong)local_118,param_3,plVar2);
      return ~(uint)uVar3 >> 0x1f;
    }
  }
  return 0;
}


// FUN_18003f58c @ 18003f58c

uint FUN_18003f58c(ushort param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 3;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x10000000;
  }
  return uVar1;
}


// FUN_180161624 @ 180161624

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_180161624(longlong param_1,ushort *param_2,uint param_3)

{
  uint uVar1;
  undefined8 uVar2;
  longlong *plVar3;
  ulonglong uVar4;
  uint uVar5;
  ushort *puVar6;
  
  uVar1 = FUN_1801619e4(*param_2);
  uVar5 = 0;
  if (uVar1 != 0) {
    uVar5 = 0;
    puVar6 = param_2;
    if (param_3 != 0) {
      do {
        uVar2 = FUN_1800632f4(*puVar6);
        if ((int)uVar2 != 0) break;
        uVar5 = uVar5 + 1;
        puVar6 = puVar6 + 1;
      } while (uVar5 < param_3);
    }
    plVar3 = (longlong *)(**(code **)**(undefined8 **)(param_1 + 0x80))();
    uVar4 = FUN_180061864((longlong)param_2,uVar5,plVar3);
    uVar5 = ~(uint)uVar4 >> 0x1f;
  }
  return uVar5;
}


// FUN_180161e84 @ 180161e84

void FUN_180161e84(longlong param_1,int *param_2)

{
  undefined8 uVar1;
  int *piVar2;
  undefined8 *puVar3;
  int *piVar4;
  undefined8 *puVar5;
  longlong lVar6;
  
  if (*param_2 != 0) {
    FUN_180068f88((undefined8 *)(param_1 + 8),(undefined8 *)(param_1 + 0x40));
    *param_2 = 0;
    lVar6 = 3;
    *(int *)(param_1 + 0x2fc) = param_2[1];
    *(int *)(param_1 + 0x300) = param_2[2];
    *(int *)(param_1 + 0x304) = param_2[3];
    piVar2 = param_2 + 4;
    puVar3 = (undefined8 *)(param_1 + 0x100);
    do {
      puVar5 = puVar3;
      piVar4 = piVar2;
      uVar1 = *(undefined8 *)(piVar4 + 2);
      *puVar5 = *(undefined8 *)piVar4;
      puVar5[1] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 6);
      puVar5[2] = *(undefined8 *)(piVar4 + 4);
      puVar5[3] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 10);
      puVar5[4] = *(undefined8 *)(piVar4 + 8);
      puVar5[5] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0xe);
      puVar5[6] = *(undefined8 *)(piVar4 + 0xc);
      puVar5[7] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x12);
      puVar5[8] = *(undefined8 *)(piVar4 + 0x10);
      puVar5[9] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x16);
      puVar5[10] = *(undefined8 *)(piVar4 + 0x14);
      puVar5[0xb] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x1a);
      puVar5[0xc] = *(undefined8 *)(piVar4 + 0x18);
      puVar5[0xd] = uVar1;
      uVar1 = *(undefined8 *)(piVar4 + 0x1e);
      puVar5[0xe] = *(undefined8 *)(piVar4 + 0x1c);
      puVar5[0xf] = uVar1;
      lVar6 = lVar6 + -1;
      piVar2 = piVar4 + 0x20;
      puVar3 = puVar5 + 0x10;
    } while (lVar6 != 0);
    uVar1 = *(undefined8 *)(piVar4 + 0x22);
    puVar5[0x10] = *(undefined8 *)(piVar4 + 0x20);
    puVar5[0x11] = uVar1;
    puVar5[0x12] = *(undefined8 *)(piVar4 + 0x24);
    *(int *)(param_1 + 0x298) = param_2[0x6a];
    *(int *)(param_1 + 0x29c) = param_2[0x6b];
    *(int *)(param_1 + 0x2a0) = param_2[0x6c];
    *(int *)(param_1 + 0x2a4) = param_2[0x6d];
    *(int *)(param_1 + 0x2a8) = param_2[0x6e];
    *(int *)(param_1 + 0x2ac) = param_2[0x6f];
    *(int *)(param_1 + 0x2b0) = param_2[0x70];
    *(int *)(param_1 + 0x2b4) = param_2[0x71];
    FUN_18007b2e4((undefined8 *)(param_1 + 0x98),(undefined8 *)(param_2 + 0x72));
    FUN_18007b2e4((undefined8 *)(param_1 + 0xb8),(undefined8 *)(param_2 + 0x7a));
    FUN_18007b2e4((undefined8 *)(param_1 + 0xd8),(undefined8 *)(param_2 + 0x82));
    *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xa0);
  }
  return;
}


// FUN_180162aa4 @ 180162aa4

bool FUN_180162aa4(longlong *param_1)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  short *psVar4;
  uint uVar5;
  
  uVar1 = *(uint *)(param_1 + 2);
  if (((int)param_1[1] == 3) && (1 < uVar1)) {
    iVar2 = 1;
    psVar4 = (short *)(*param_1 + (ulonglong)*(uint *)((longlong)param_1 + 0xc) * 2);
    for (uVar5 = 0; uVar5 < uVar1; uVar5 = uVar5 + 1) {
      if (iVar2 == 1) {
        iVar2 = _o_iswdigit(*psVar4);
        if (iVar2 != 0) {
          return false;
        }
        iVar2 = 2;
      }
      else if (iVar2 == 2) {
        if (*psVar4 == 0x2e) {
          return false;
        }
        iVar2 = 3;
      }
      else if ((iVar2 == 3) && (*psVar4 == 0x2e)) {
        return false;
      }
      psVar4 = psVar4 + 1;
    }
    if (iVar2 == 3) {
      uVar3 = FUN_18016296c(param_1);
      return (int)uVar3 == 0;
    }
  }
  return false;
}


// FUN_180162738 @ 180162738

void FUN_180162738(longlong param_1,undefined4 *param_2)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong lVar6;
  
  FUN_180068f88((undefined8 *)(param_1 + 0x40),(undefined8 *)(param_1 + 8));
  *(undefined4 *)(param_1 + 0x78) = 1;
  *param_2 = 1;
  param_2[1] = *(undefined4 *)(param_1 + 0x2fc);
  param_2[2] = *(undefined4 *)(param_1 + 0x300);
  param_2[3] = *(undefined4 *)(param_1 + 0x304);
  FUN_18007b2e4((undefined8 *)(param_2 + 0x72),(undefined8 *)(param_1 + 0x98));
  FUN_18007b2e4((undefined8 *)(param_2 + 0x7a),(undefined8 *)(param_1 + 0xb8));
  FUN_18007b2e4((undefined8 *)(param_2 + 0x82),(undefined8 *)(param_1 + 0xd8));
  lVar6 = 3;
  puVar2 = (undefined8 *)(param_1 + 0x100);
  puVar3 = (undefined8 *)(param_2 + 4);
  do {
    puVar5 = puVar3;
    puVar4 = puVar2;
    uVar1 = puVar4[1];
    *puVar5 = *puVar4;
    puVar5[1] = uVar1;
    uVar1 = puVar4[3];
    puVar5[2] = puVar4[2];
    puVar5[3] = uVar1;
    uVar1 = puVar4[5];
    puVar5[4] = puVar4[4];
    puVar5[5] = uVar1;
    uVar1 = puVar4[7];
    puVar5[6] = puVar4[6];
    puVar5[7] = uVar1;
    uVar1 = puVar4[9];
    puVar5[8] = puVar4[8];
    puVar5[9] = uVar1;
    uVar1 = puVar4[0xb];
    puVar5[10] = puVar4[10];
    puVar5[0xb] = uVar1;
    uVar1 = puVar4[0xd];
    puVar5[0xc] = puVar4[0xc];
    puVar5[0xd] = uVar1;
    uVar1 = puVar4[0xf];
    puVar5[0xe] = puVar4[0xe];
    puVar5[0xf] = uVar1;
    lVar6 = lVar6 + -1;
    puVar2 = puVar4 + 0x10;
    puVar3 = puVar5 + 0x10;
  } while (lVar6 != 0);
  uVar1 = puVar4[0x11];
  puVar5[0x10] = puVar4[0x10];
  puVar5[0x11] = uVar1;
  puVar5[0x12] = puVar4[0x12];
  param_2[0x6a] = *(undefined4 *)(param_1 + 0x298);
  param_2[0x6b] = *(undefined4 *)(param_1 + 0x29c);
  param_2[0x6c] = *(undefined4 *)(param_1 + 0x2a0);
  param_2[0x6d] = *(undefined4 *)(param_1 + 0x2a4);
  param_2[0x6e] = *(undefined4 *)(param_1 + 0x2a8);
  param_2[0x6f] = *(undefined4 *)(param_1 + 0x2ac);
  param_2[0x70] = *(undefined4 *)(param_1 + 0x2b0);
  param_2[0x71] = *(undefined4 *)(param_1 + 0x2b4);
  return;
}


// FUN_1800cf160 @ 1800cf160

void FUN_1800cf160(void)

{
  undefined8 local_28 [5];
  
  FUN_1800cdb2c(local_28);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_28,(ThrowInfo *)&DAT_1801b65f0);
}


// FUN_18007cc74 @ 18007cc74

void FUN_18007cc74(void)

{
  undefined8 local_28 [5];
  
  FUN_18007cc50(local_28);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_28,(ThrowInfo *)&DAT_1801b6468);
}


// FUN_180075cac @ 180075cac

undefined8 FUN_180075cac(longlong *param_1,ushort *param_2,undefined8 param_3)

{
  uint *puVar1;
  short sVar2;
  short sVar3;
  ulonglong uVar4;
  uint uVar5;
  longlong lVar6;
  longlong *_Dst;
  short *psVar7;
  undefined8 *puVar8;
  
  puVar1 = (uint *)(param_1 + 1);
  _Dst = param_1;
  if (*param_1 == 0) {
    lVar6 = SUB168(ZEXT816(8) * ZEXT416(*puVar1),0);
    if (SUB168(ZEXT816(8) * ZEXT416(*puVar1),8) != 0) {
      lVar6 = -1;
    }
    _Dst = (longlong *)thunk_FUN_18007ca58(lVar6);
    *param_1 = (longlong)_Dst;
    if (_Dst == (longlong *)0x0) {
      return 0x8007000e;
    }
    memset(_Dst,0,(ulonglong)*puVar1 << 3);
  }
  uVar5 = FUN_1800466e0(_Dst,param_2);
  uVar4 = (ulonglong)uVar5 % (ulonglong)*puVar1;
  puVar8 = *(undefined8 **)(*param_1 + uVar4 * 8);
  do {
    if (puVar8 == (undefined8 *)0x0) {
      puVar8 = (undefined8 *)FUN_18007ca58(0x18);
      if (puVar8 == (undefined8 *)0x0) {
        return 0x8007000e;
      }
      *puVar8 = param_2;
      puVar8[1] = param_3;
      puVar8[2] = *(undefined8 *)(*param_1 + uVar4 * 8);
      *(undefined8 **)(*param_1 + uVar4 * 8) = puVar8;
      return 0;
    }
    psVar7 = (short *)*puVar8;
    lVar6 = (longlong)param_2 - (longlong)psVar7;
    do {
      sVar2 = *psVar7;
      sVar3 = *(short *)((longlong)psVar7 + lVar6);
      if (sVar2 != sVar3) break;
      psVar7 = psVar7 + 1;
    } while (sVar3 != 0);
    if (sVar2 == sVar3) {
      return 0;
    }
    puVar8 = (undefined8 *)puVar8[2];
  } while( true );
}


// FUN_18007b2e4 @ 18007b2e4

undefined8 * FUN_18007b2e4(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != param_2) {
    *param_1 = *param_2;
    *(undefined4 *)(param_1 + 1) = *(undefined4 *)(param_2 + 1);
    *(undefined4 *)((longlong)param_1 + 0xc) = *(undefined4 *)((longlong)param_2 + 0xc);
    *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_2 + 2);
    *(undefined4 *)((longlong)param_1 + 0x14) = *(undefined4 *)((longlong)param_2 + 0x14);
    *(undefined4 *)(param_1 + 3) = *(undefined4 *)(param_2 + 3);
  }
  return param_1;
}


// FUN_18003dbc0 @ 18003dbc0

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_18003dbc0(longlong *param_1,longlong *param_2,uint param_3,longlong param_4)

{
  ushort *puVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined8 uVar12;
  undefined7 extraout_var;
  ulonglong uVar13;
  longlong lVar14;
  longlong *plVar15;
  ulonglong uVar16;
  longlong lVar17;
  undefined8 uVar18;
  undefined7 extraout_var_00;
  undefined7 extraout_var_01;
  undefined7 extraout_var_02;
  char cVar19;
  ushort uVar20;
  uint uVar21;
  uint uVar22;
  int iVar23;
  short *psVar24;
  ulonglong uVar25;
  ushort uVar26;
  uint uVar27;
  uint uVar28;
  uint local_res8 [2];
  longlong *local_res10;
  uint local_res18;
  longlong local_res20;
  undefined4 uVar29;
  int iVar30;
  uint local_74;
  char local_70 [4];
  uint local_6c;
  char local_68;
  char local_67;
  uint local_64;
  uint local_60;
  uint local_5c;
  ulonglong local_58;
  uint local_50;
  uint local_4c;
  
  uVar21 = *(uint *)((longlong)param_1 + 0xc);
  lVar17 = *param_1;
  local_5c = 0;
  local_60 = 0;
  *(uint *)(param_1 + 2) = uVar21;
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  if (uVar21 == *(uint *)(param_1 + 1)) {
    iVar23 = 0x11;
    iVar8 = 0;
LAB_18003dc12:
    uVar29 = 0;
  }
  else {
    puVar1 = (ushort *)(lVar17 + (ulonglong)uVar21 * 2);
    uVar26 = *puVar1;
    if (uVar26 == 0) {
      iVar23 = 0xf;
      iVar8 = 1;
      goto LAB_18003dc12;
    }
    if (499 < uVar21) {
      FUN_1800774b4(param_2,lVar17,0xf,uVar21,0,0);
      *(undefined4 *)(param_2 + 3) = 1;
      goto LAB_18003f2ba;
    }
    uVar28 = *(uint *)(param_1 + 1) - uVar21;
    iVar8 = FUN_18003fdb8(param_1,(short *)puVar1,uVar28);
    if (iVar8 != 0) {
      FUN_1800774b4(param_2,lVar17,3,uVar21,2,0);
      *(int *)(param_1 + 2) = (int)param_1[2] + 2;
      goto LAB_18003f2ba;
    }
    uVar12 = FUN_180079ea4(uVar26);
    if ((int)uVar12 != 0) {
      iVar8 = 1;
      FUN_1800774b4(param_2,lVar17,0x10,uVar21,1,0);
      uVar21 = (int)param_1[2] + 1;
      uVar16 = (ulonglong)uVar21;
      *(uint *)(param_1 + 2) = uVar21;
      if (*(uint *)(param_1 + 1) <= uVar21) goto LAB_18003f2ba;
      if ((uVar26 == 10) || (bVar6 = false, uVar26 == 0x8d)) {
        bVar6 = true;
      }
      lVar17 = *param_1;
      if ((*(short *)(lVar17 + uVar16 * 2) == 10) ||
         (bVar5 = false, *(short *)(lVar17 + uVar16 * 2) == 0x8d)) {
        bVar5 = true;
      }
      if (((uVar26 != 0xd) || (!bVar5)) && ((!bVar6 || (*(short *)(lVar17 + uVar16 * 2) != 0xd))))
      goto LAB_18003f2ba;
      *(undefined4 *)(param_2 + 2) = 2;
LAB_18003f264:
      *(int *)(param_1 + 2) = (int)param_1[2] + iVar8;
      goto LAB_18003f2ba;
    }
    local_res8[0] = uVar28;
    bVar6 = FUN_18003fbe4(lVar17,uVar21,local_res8);
    if ((int)CONCAT71(extraout_var,bVar6) != 0) {
      uVar29 = 0;
      iVar8 = 0x12;
      uVar28 = local_res8[0];
LAB_18003dd81:
      FUN_1800774b4(param_2,lVar17,iVar8,uVar21,uVar28,uVar29);
      *(uint *)(param_1 + 2) = (int)param_1[2] + uVar28;
      goto LAB_18003f2ba;
    }
    uVar16 = (ulonglong)uVar21;
    uVar9 = FUN_18003f9ac(uVar26);
    iVar8 = 1;
    uVar22 = local_res18;
    if (uVar9 == 0) {
      if ((uVar26 & 0xff00) == 0) {
        uVar9 = (byte)(&DAT_180180820)[(byte)uVar26] & 8;
      }
      else {
        uVar9 = FUN_180072dbc(uVar26);
        uVar9 = uVar9 & 0x800000;
      }
      uVar20 = 0x5f;
      uVar22 = local_res18;
      if ((((uVar9 == 0) && (uVar13 = FUN_18007a664(uVar26), uVar22 = local_res18, (int)uVar13 == 0)
           ) && (1 < uVar28)) &&
         (((local_res18 & 8) == 0 ||
          ((uVar2 = *(ushort *)(lVar17 + (ulonglong)(uVar21 - 1) * 2), uVar20 != uVar2 &&
           (uVar21 = FUN_18003f9ac(uVar2), uVar21 == 0)))))) {
        lVar14 = (**(code **)(*(longlong *)param_1[0x10] + 0x50))();
        plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x58))();
        uVar21 = *(uint *)(param_1 + 2);
        uVar16 = (ulonglong)uVar21;
        lVar17 = *param_1;
        uVar13 = FUN_18003f9e4((ushort *)(lVar17 + uVar16 * 2),(int)param_1[1] - uVar21,1,plVar15,
                               lVar14);
        uVar28 = (uint)uVar13;
        if (uVar28 != 0) {
          uVar29 = 0x41;
          iVar8 = 3;
          goto LAB_18003dd81;
        }
      }
    }
    uVar21 = (uint)uVar16;
    if (uVar26 == 0x2026) {
      iVar23 = 8;
LAB_18003deac:
      iVar30 = 0;
LAB_18003deb0:
      lVar17 = *param_1;
LAB_18003f25f:
      FUN_1800774b4(param_2,lVar17,iVar23,uVar21,iVar8,iVar30);
      goto LAB_18003f264;
    }
    uVar20 = uVar26;
    uVar12 = FUN_180075e74(uVar26);
    if ((int)uVar12 != 0) {
      iVar23 = 0xc;
      goto LAB_18003deac;
    }
    uVar12 = FUN_18003f2e4(uVar20);
    if ((int)uVar12 != 0) {
      iVar23 = 0x13;
      goto LAB_18003deac;
    }
    uVar12 = FUN_180072d30(uVar20);
    if ((int)uVar12 == 0) {
      if ((ushort)(uVar26 + 0x1800) < 2) {
        uVar28 = uVar21 + 1;
        uVar16 = (ulonglong)uVar28;
        *(uint *)(param_1 + 2) = uVar28;
        if (uVar28 < *(uint *)(param_1 + 1)) {
          do {
            sVar3 = *(short *)(*param_1 + uVar16 * 2);
            if (sVar3 != -0x1800 && sVar3 != -0x17ff) break;
            uVar28 = (int)uVar16 + 1;
            uVar16 = (ulonglong)uVar28;
            *(uint *)(param_1 + 2) = uVar28;
          } while (uVar28 < *(uint *)(param_1 + 1));
        }
        iVar8 = (int)uVar16 - uVar21;
        iVar23 = 2;
        goto LAB_18003f2ac;
      }
      if ((int)param_1[0x11] != 0) {
        uVar20 = uVar26;
        uVar12 = FUN_18016156c(uVar26);
        if ((int)uVar12 == 0) {
          uVar12 = FUN_1801615c8(uVar20);
          if ((int)uVar12 == 0) goto LAB_18003dfa9;
          uVar16 = FUN_18007a664(uVar20);
          iVar23 = 0xb;
          iVar30 = (-(uint)((int)uVar16 != 0) & 0x10) + 0x10;
        }
        else {
          uVar16 = FUN_18007a664(uVar20);
          iVar23 = 10;
          iVar30 = (-(uint)((int)uVar16 != 0) & 0x10) + 0x10;
        }
        goto LAB_18003deb0;
      }
LAB_18003dfa9:
      uVar20 = uVar26;
      uVar12 = FUN_18003f934(uVar26);
      if ((int)uVar12 != 0) {
        iVar30 = 4;
        if (local_res18 == 0) {
          lVar17 = (**(code **)(*(longlong *)param_1[0x10] + 0x50))();
          plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x58))();
          uVar21 = *(uint *)(param_1 + 2);
          uVar16 = FUN_18003f9e4((ushort *)(*param_1 + (ulonglong)uVar21 * 2),
                                 (int)param_1[1] - uVar21,1,plVar15,lVar17);
          if ((int)uVar16 != 0) {
            iVar30 = 0x45;
            iVar8 = (int)uVar16;
          }
        }
        uVar16 = FUN_18007a664(uVar26);
        iVar23 = (-(uint)((int)uVar16 != 0) & 0xffffffee) + 0x1f;
        goto LAB_18003deb0;
      }
      uVar13 = FUN_18007a664(uVar20);
      if (((int)uVar13 != 0) || ((uVar26 - 0xab & 0xffef) == 0)) {
        iVar23 = 0xd;
        goto LAB_18003deac;
      }
      uVar20 = uVar26;
      uVar12 = FUN_18003f980(uVar26);
      if ((int)uVar12 != 0) {
        lVar17 = *param_1;
        uVar22 = uVar21 + 1;
        uVar13 = 3;
        *(uint *)(param_1 + 2) = uVar22;
        uVar16 = 1;
        local_5c = 3;
        uVar12 = 0;
        uVar25 = 4;
        uVar28 = uVar22;
        do {
          while( true ) {
            if (uVar28 < *(uint *)(param_1 + 1)) {
              uVar26 = *(ushort *)(lVar17 + (ulonglong)uVar28 * 2);
            }
            else {
              uVar26 = (ushort)uVar12;
            }
            iVar8 = (int)uVar16;
            if (iVar8 != 1) break;
            if ((uVar26 & 0xff00) == 0) {
              uVar28 = *(uint *)(param_1 + 2);
              uVar9 = (byte)(&DAT_180180820)[(byte)uVar26] & 8;
            }
            else {
              uVar9 = FUN_180072dbc(uVar26);
              uVar13 = (ulonglong)local_5c;
              uVar9 = uVar9 & 0x800000;
              uVar12 = 0;
              uVar25 = 4;
            }
            if (uVar9 == 0) {
              uVar18 = FUN_18003f980(uVar26);
              iVar23 = (int)uVar13;
              if ((int)uVar18 == 0) goto LAB_18003e18c;
              uVar28 = uVar28 + 1;
              uVar16 = 2;
              *(uint *)(param_1 + 2) = uVar28;
            }
            else {
              uVar28 = uVar28 + 1;
              uVar16 = uVar13 & 0xffffffff;
              *(uint *)(param_1 + 2) = uVar28;
            }
          }
          uVar9 = uVar28;
          if (iVar8 == 2) {
            if ((uVar28 - uVar21 < (uint)uVar13) &&
               (uVar18 = FUN_18003f980(uVar26), (int)uVar18 != 0)) {
              uVar28 = uVar28 + 1;
              *(uint *)(param_1 + 2) = uVar28;
            }
            else {
LAB_18003e17f:
              uVar16 = 0xffffffff;
              uVar22 = uVar9;
            }
          }
          else if (iVar8 == 3) {
            uVar18 = FUN_18003f980(uVar26);
            uVar9 = uVar22;
            if ((int)uVar18 == 0) goto LAB_18003e17f;
            uVar28 = uVar28 + 1;
            uVar16 = uVar25 & 0xffffffff;
            *(uint *)(param_1 + 2) = uVar28;
          }
          else if (iVar8 == 4) {
            uVar10 = uVar28 - uVar21 >> 1;
            if (((uVar10 != 2) && (uVar10 != (uint)uVar25)) && (uVar9 = uVar22, uVar10 == 6)) {
              uVar16 = 0xffffffff;
              uVar9 = uVar28;
            }
            uVar22 = uVar9;
            if (0 < (int)uVar16) {
              if ((uVar26 & 0xff00) == 0) {
                uVar10 = (byte)(&DAT_180180820)[(byte)uVar26] & 8;
              }
              else {
                uVar10 = FUN_180072dbc(uVar26);
                uVar13 = (ulonglong)local_5c;
                uVar10 = uVar10 & 0x800000;
                uVar12 = 0;
                uVar25 = 4;
              }
              if (uVar10 == 0) goto LAB_18003e17f;
              uVar28 = uVar28 + 1;
              uVar16 = uVar13 & 0xffffffff;
              *(uint *)(param_1 + 2) = uVar28;
            }
          }
          iVar23 = (int)uVar13;
        } while (0 < (int)uVar16);
LAB_18003e18c:
        *(uint *)(param_1 + 2) = uVar22;
        iVar8 = uVar22 - uVar21;
        uVar29 = (undefined4)uVar12;
        param_2 = local_res10;
        if (iVar8 - 1U < 2) {
          iVar23 = 0xc;
        }
        else {
          iVar23 = (int)CONCAT71((int7)((ulonglong)uVar12 >> 8),iVar8 != iVar23) + 8;
        }
        goto LAB_18003f2b2;
      }
      uVar12 = FUN_18003f4f4(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0xe;
        goto LAB_18003deac;
      }
      uVar12 = FUN_18003f324(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0x1b;
        iVar30 = 0x80;
        if (uVar26 != 0xa7) {
          iVar30 = 0;
        }
        goto LAB_18003deb0;
      }
      uVar12 = FUN_18003f51c(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0x1d;
        goto LAB_18003deac;
      }
      uVar12 = FUN_18003f474(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0x1c;
        goto LAB_18003deac;
      }
      uVar12 = FUN_18003f3cc(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0x1e;
        goto LAB_18003deac;
      }
      uVar12 = FUN_18003f4b4(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0x20;
        goto LAB_18003deac;
      }
      uVar12 = FUN_18003f44c(uVar20);
      if ((int)uVar12 != 0) {
        iVar23 = 0x1a;
        goto LAB_18003deac;
      }
      if ((uVar26 & 0xff00) == 0) {
        uVar28 = (byte)(&DAT_180180820)[(byte)uVar26] & 7;
      }
      else {
        uVar28 = FUN_180072dbc(uVar20);
        uVar28 = uVar28 & 0x10400000;
      }
      if (uVar28 != 0) {
        local_50 = 0;
        uVar28 = 0;
        local_70[0] = '\0';
        if ((uVar22 & 2) == 0) {
          cVar7 = (**(code **)(*(longlong *)param_1[0x10] + 0x60))();
          cVar19 = '\x01';
          if (cVar7 == '\0') goto LAB_18003e32f;
        }
        else {
LAB_18003e32f:
          cVar19 = '\0';
        }
        local_58 = CONCAT44(local_58._4_4_,uVar21);
        local_64 = 0;
        local_4c = 0;
        local_res8[0] = local_res8[0] & 0xffffff00;
        local_68 = '\0';
        local_67 = '\0';
        uVar13 = uVar16;
        uVar22 = 0;
        local_74 = uVar21;
        local_6c = uVar21;
        while( true ) {
          uVar9 = (uint)uVar13;
          uVar27 = 0xffffffff;
          uVar11 = 0xffffffff;
          uVar10 = uVar22;
          if ((int)uVar22 < 0) break;
          uVar4 = *(uint *)(param_1 + 2);
          if (uVar4 < *(uint *)(param_1 + 1)) {
            uVar26 = *(ushort *)(*param_1 + (ulonglong)uVar4 * 2);
          }
          else {
            uVar26 = 0;
          }
          uVar10 = uVar11;
          if ((((1 < (int)(*(uint *)(param_1 + 1) - uVar4)) &&
               ((ushort)(*(short *)(*param_1 + (ulonglong)uVar4 * 2) + 0x2800U) < 0x400)) &&
              ((ushort)(*(short *)(*param_1 + 2 + (ulonglong)uVar4 * 2) + 0x2400U) < 0x400)) ||
             (uVar20 = uVar26, uVar12 = FUN_18003f2e4(uVar26), (int)uVar12 != 0)) break;
          uVar11 = FUN_18003f9ac(uVar20);
          uVar12 = 0;
          if (((uVar11 == 0) && (uVar26 != 0x5f)) &&
             ((((uVar20 = uVar26, uVar18 = FUN_18003f324(uVar26), (int)uVar18 != 0 ||
                ((((uVar18 = FUN_18003f51c(uVar20), (int)uVar18 != 0 ||
                   (uVar18 = FUN_18003f474(uVar20), (int)uVar18 != 0)) ||
                  (uVar18 = FUN_18003f3cc(uVar20), (int)uVar18 != 0)) ||
                 ((uVar18 = FUN_18003f44c(uVar20), (int)uVar18 != 0 ||
                  (uVar18 = FUN_18003f4f4(uVar20), (int)uVar18 != 0)))))) ||
               ((uVar18 = FUN_18003f4b4(uVar20), (int)uVar18 != 0 ||
                (((ushort)((short)uVar12 + 0x2dU) == uVar26 ||
                 (uVar18 = FUN_18003f934(uVar20), (int)uVar18 != 0)))))) ||
              ((uVar18 = FUN_18003f980(uVar20), (int)uVar18 != 0 ||
               ((ushort)((short)uVar12 + 0x21U) == uVar26)))))) {
            if (((local_68 == (char)uVar12) && (*(uint *)(param_1 + 2) < *(uint *)(param_1 + 1))) &&
               ((uVar20 = uVar26, uVar12 = FUN_18003f934(uVar26), (int)uVar12 != 0 ||
                (uVar13 = FUN_18007a664(uVar20), (int)uVar13 == 0)))) {
              local_68 = '\x01';
              lVar17 = (**(code **)(*(longlong *)param_1[0x10] + 0x50))();
              plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x58))();
              uVar13 = FUN_18003f9e4((ushort *)(*param_1 + (ulonglong)local_74 * 2),
                                     (int)param_1[1] - local_74,((int)param_1[2] - local_74) + 1,
                                     plVar15,lVar17);
              uVar9 = local_6c;
              if ((int)uVar13 != 0) {
                uVar28 = uVar28 | 0x41;
                *(uint *)(param_1 + 2) = (int)uVar13 + local_74;
                break;
              }
            }
            if (((uVar26 != 0x2d) &&
                (uVar20 = uVar26, uVar12 = FUN_18003f934(uVar26), (int)uVar12 == 0)) &&
               (uVar12 = FUN_18003f980(uVar20), (int)uVar12 == 0)) {
              uVar10 = 0xffffffff;
              if (local_res18 != 0) break;
              if (uVar9 == local_74) {
                uVar9 = *(uint *)(param_1 + 2);
                local_res8[0] = CONCAT31(local_res8[0]._1_3_,cVar19);
                local_6c = uVar9;
                local_64 = uVar28;
              }
            }
          }
          uVar13 = (ulonglong)local_74;
          uVar10 = uVar28;
          if ((int)uVar22 < 0x3d) {
            if (uVar22 == 0x3c) {
              uVar11 = FUN_18003f8fc(uVar26);
              if (uVar11 == 0) {
                uVar12 = FUN_18003f980(uVar26);
                if ((int)uVar12 == 0) {
                  if ((uVar26 == 0x2c || uVar26 == 0x2d) || (uVar26 == 0x3a)) goto LAB_18003edc4;
                  uVar22 = 0x42;
                }
                else {
                  uVar22 = uVar27;
                  if (local_res18 == 0) {
LAB_18003edc4:
                    if (uVar9 == local_74) {
                      local_6c = *(uint *)(param_1 + 2);
                      local_res8[0] = CONCAT31(local_res8[0]._1_3_,cVar19);
                      local_64 = uVar28;
                    }
                    *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                    uVar22 = 0x3d;
                  }
                }
              }
              else {
                *(int *)(param_1 + 2) = (int)param_1[2] + 1;
              }
              goto LAB_18003e5d1;
            }
            if (uVar22 == 0) {
              uVar22 = FUN_18003f8fc(uVar26);
              if (uVar22 == 0) {
LAB_18003ed24:
                uVar22 = FUN_18003f58c(uVar26);
                if (uVar22 != 0) goto LAB_18003ed31;
LAB_18003ecd1:
                *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                uVar22 = 10;
                uVar10 = uVar28;
              }
              else {
                *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                uVar22 = 0x3c;
                uVar10 = uVar28 | 2;
              }
              goto LAB_18003e5d1;
            }
            if (uVar22 == 10) {
              cVar7 = cVar19;
              uVar20 = uVar26;
              uVar22 = local_res18;
              uVar12 = FUN_18003f980(uVar26);
              uVar11 = (uint)uVar13;
              if ((int)uVar12 != 0) {
                if (uVar9 == uVar11) {
                  local_6c = *(uint *)(param_1 + 2);
                  local_res8[0] = CONCAT31(local_res8[0]._1_3_,cVar7);
                  local_64 = uVar28;
                }
LAB_18003e94d:
                *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                uVar22 = 0x14;
                goto LAB_18003e5d1;
              }
              uVar12 = FUN_18003f934(uVar20);
              if ((int)uVar12 == 0) {
                uVar22 = FUN_18003f8fc(uVar20);
                if (uVar22 != 0) {
                  uVar28 = uVar28 | 2;
                  goto LAB_18003ecd1;
                }
                if ((uVar26 == 0xad) ||
                   ((((uVar22 = FUN_18003f9ac(uVar26), uVar22 != 0 &&
                      (uVar26 != 0xe800 && uVar26 != 0xe801)) || (uVar26 == 0x5f)) ||
                    (uVar26 == 0x2010 || uVar26 == 0x2011)))) goto LAB_18003ed24;
LAB_18003ea0e:
                uVar22 = uVar27;
                if (uVar26 == 0x28) {
                  uVar22 = 0x46;
                }
                goto LAB_18003e5d1;
              }
              if (cVar19 == '\0') {
                if (uVar22 == 0) {
                  if (uVar9 == uVar11) {
                    local_6c = *(uint *)(param_1 + 2);
                    local_res8[0] = local_res8[0] & 0xffffff00;
                    local_64 = uVar28;
                  }
                  local_58 = (ulonglong)*(uint *)(param_1 + 2);
                  *(uint *)(param_1 + 2) = *(uint *)(param_1 + 2) + 1;
                  uVar27 = 0x28;
                  uVar28 = uVar28 | 4;
                }
                goto LAB_18003efe9;
              }
              uVar10 = uVar28 | 4;
              local_58 = (ulonglong)*(uint *)(param_1 + 2);
              uVar22 = 0x28;
              *(uint *)(param_1 + 2) = *(uint *)(param_1 + 2) + 1;
              goto LAB_18003e5eb;
            }
            if (uVar22 == 0x14) {
              uVar22 = FUN_18003f9ac(uVar26);
              if ((uVar22 == 0) || (uVar26 == 0xe800 || uVar26 == 0xe801)) {
                if (uVar26 != 0x2d) {
                  uVar20 = uVar26;
                  uVar12 = FUN_18003f934(uVar26);
                  if ((int)uVar12 != 0) {
                    uVar22 = uVar27;
                    if (local_res18 == 0) {
                      if (uVar9 == local_74) {
                        local_6c = *(uint *)(param_1 + 2);
                        local_res8[0] = CONCAT31(local_res8[0]._1_3_,cVar19);
                        local_64 = uVar28;
                      }
                      uVar22 = *(uint *)(param_1 + 2);
                      uVar28 = uVar28 | 4;
                      local_58 = CONCAT44(local_58._4_4_,uVar22);
LAB_18003e873:
                      *(uint *)(param_1 + 2) = uVar22 + 1;
                      goto LAB_18003e835;
                    }
                    goto LAB_18003e5d1;
                  }
                  if ((uVar26 & 0xff00) == 0) {
                    uVar22 = (byte)(&DAT_180180820)[(byte)uVar26] & 8;
                  }
                  else {
                    uVar22 = FUN_180072dbc(uVar20);
                    uVar22 = uVar22 & 0x800000;
                  }
                  if ((uVar22 == 0) || ((local_res18 & 2) != 0 || (uVar28 & 4) != 0)) {
LAB_18003e909:
                    uVar22 = 0x32;
                  }
                  else {
                    plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x20))();
                    uVar13 = FUN_18003f9e4((ushort *)(*param_1 + (ulonglong)local_74 * 2),
                                           (int)param_1[1] - local_74,
                                           ((int)param_1[2] - local_74) + 1,plVar15,0);
                    iVar8 = (int)uVar13;
                    if (iVar8 == 0) {
                      plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x40))();
                      uVar13 = FUN_18003f9e4((ushort *)(*param_1 + (ulonglong)local_74 * 2),
                                             (int)param_1[1] - local_74,
                                             ((int)param_1[2] - local_74) + 1,plVar15,0);
                      iVar8 = (int)uVar13;
                      if (iVar8 == 0) goto LAB_18003e909;
                    }
                    *(uint *)(param_1 + 2) = iVar8 + local_74;
                    uVar22 = 0xfffffffe;
                  }
                  goto LAB_18003e5d1;
                }
                if (((local_res18 & 4) == 0) &&
                   (bVar6 = FUN_180161120((longlong)param_1,
                                          (ushort *)(*param_1 + (ulonglong)local_74 * 2),
                                          (int)param_1[2] - local_74,local_res20,local_70),
                   (int)CONCAT71(extraout_var_02,bVar6) != 0)) {
                  local_64 = uVar28;
                  if (local_70[0] != '\0') {
                    local_64 = uVar28 | 8;
                  }
                  local_6c = *(uint *)(param_1 + 2);
                  local_4c = 5;
                  uVar28 = local_64;
                }
              }
              else {
LAB_18003ea28:
                if ((*(int *)((longlong)param_1 + 0x74) == 0) &&
                   (uVar22 = FUN_1801619e4(uVar26), uVar22 != 0)) {
                  *(undefined4 *)((longlong)param_1 + 0x74) = 1;
                }
                else if (((int)param_1[0xf] == 0) && (uVar22 = FUN_180066b20(uVar26), uVar22 != 0))
                {
                  *(undefined4 *)(param_1 + 0xf) = 1;
                }
              }
LAB_18003e996:
              *(int *)(param_1 + 2) = (int)param_1[2] + 1;
              uVar22 = 0x1e;
              uVar10 = uVar28;
              goto LAB_18003e5d1;
            }
            if (uVar22 == 0x1e) {
              uVar20 = uVar26;
              uVar12 = FUN_18003f980(uVar26);
              if ((int)uVar12 != 0) goto LAB_18003e94d;
              uVar12 = FUN_18003f934(uVar20);
              if ((int)uVar12 == 0) {
                uVar22 = FUN_18003f8fc(uVar20);
                if (uVar22 == 0) {
                  if ((uVar26 == 0xad) ||
                     (((uVar22 = FUN_18003f9ac(uVar26), uVar22 != 0 &&
                       (uVar26 != 0xe800 && uVar26 != 0xe801)) || (uVar26 == 0x5f))))
                  goto LAB_18003ea28;
                  if (uVar26 != 0x2d) goto LAB_18003ea0e;
                  uVar22 = uVar27;
                  if (local_res18 != 0) goto LAB_18003e5d1;
                  if (uVar9 == local_74) {
                    local_6c = *(uint *)(param_1 + 2);
                    local_res8[0] = CONCAT31(local_res8[0]._1_3_,cVar19);
                    local_64 = uVar28;
                  }
                }
                else {
                  uVar28 = uVar28 | 2;
                }
                goto LAB_18003e996;
              }
              if ((uVar28 & 4) != 0) {
                uVar28 = *(uint *)(param_1 + 2);
                *(uint *)(param_1 + 2) = uVar28 + 1;
                uVar22 = 0x28;
                local_58 = (ulonglong)uVar28;
                goto LAB_18003e5d1;
              }
LAB_18003ef13:
              uVar22 = 0xffffffff;
              goto LAB_18003e5d1;
            }
            if (uVar22 != 0x28) {
              if (uVar22 == 0x32) {
                if ((local_res18 & 4) == 0) {
                  uVar13 = (ulonglong)local_74;
                  uVar22 = FUN_180161888((longlong)param_1,(ushort *)(*param_1 + uVar13 * 2),
                                         (int)param_1[2] - local_74,0);
                  if (uVar22 == 0) {
                    bVar6 = FUN_180161120((longlong)param_1,(ushort *)(*param_1 + uVar13 * 2),
                                          (int)param_1[2] - local_74,local_res20,local_70);
                    if ((int)CONCAT71(extraout_var_00,bVar6) == 0) {
                      uVar28 = FUN_180161888((longlong)param_1,(ushort *)(*param_1 + uVar13 * 2),
                                             (int)param_1[2] - local_74,1);
                      if (uVar28 != 0) goto LAB_18003e5c9;
                      lVar17 = *param_1;
                      lVar14 = param_1[2];
                      plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x28))();
                      uVar13 = FUN_180061864(lVar17 + uVar13 * 2,(int)lVar14 - local_74,plVar15);
                      uVar9 = local_6c;
                      if ((int)uVar13 < 0) goto LAB_18003e6e1;
                      uVar22 = 0xfffffffb;
                    }
                    else {
                      uVar22 = 0xfffffffe;
                      if (local_70[0] != '\0') {
                        uVar10 = uVar28 | 8;
                      }
                    }
                  }
                  else {
LAB_18003e5c9:
                    uVar22 = 0xfffffffd;
                  }
                }
                else {
LAB_18003e6e1:
                  if ((local_res18 == 0) && (local_74 < uVar9)) {
                    lVar17 = *param_1;
                    uVar13 = (ulonglong)uVar9;
                    lVar14 = lVar17;
                    uVar12 = FUN_18003f4b4(*(short *)(lVar17 + (ulonglong)uVar9 * 2));
                    if (((int)uVar12 == 0) &&
                       (uVar28 = (int)param_1[2] - 1, uVar13 = (ulonglong)uVar28, uVar9 < uVar28)) {
                      psVar24 = (short *)(lVar17 + uVar13 * 2);
                      do {
                        uVar12 = FUN_18003f4b4(*psVar24);
                        if ((int)uVar12 != 0) break;
                        uVar28 = (int)uVar13 - 1;
                        uVar13 = (ulonglong)uVar28;
                        psVar24 = psVar24 + -1;
                      } while (uVar9 < uVar28);
                    }
                    iVar8 = (int)uVar13;
                    uVar13 = uVar13 & 0xffffffff;
                    uVar12 = FUN_18003f4b4(*(short *)(lVar14 + uVar13 * 2));
                    if (((int)uVar12 != 0) &&
                       (bVar6 = FUN_180161120((longlong)param_1,
                                              (ushort *)(lVar14 + (uVar13 + 1) * 2),
                                              ((int)param_1[2] - iVar8) - 1,local_res20,
                                              (undefined1 *)0x0), uVar22 = 0xffffffff,
                       (int)CONCAT71(extraout_var_01,bVar6) != 0)) goto LAB_18003e5d1;
                  }
                  *(int *)(param_1 + 2) = (int)param_1[2] + -1;
                  uVar22 = 0xffffffff;
                }
              }
              goto LAB_18003e5d1;
            }
            iVar8 = FUN_180161964(0x28,uVar26);
            if (iVar8 != 0) {
              uVar22 = FUN_18003f58c(uVar26);
              if (uVar22 != 0) {
                uVar28 = uVar28 | 1;
                if ((*(int *)((longlong)param_1 + 0x74) == 0) &&
                   (uVar22 = FUN_1801619e4(uVar26), uVar22 != 0)) {
                  *(undefined4 *)((longlong)param_1 + 0x74) = 1;
                }
                else if (((int)param_1[0xf] == 0) && (uVar22 = FUN_180066b20(uVar26), uVar22 != 0))
                {
                  *(undefined4 *)(param_1 + 0xf) = 1;
                }
              }
              uVar9 = FUN_18003f8fc(uVar26);
              *(int *)(param_1 + 2) = (int)param_1[2] + 1;
              uVar22 = 0x28;
              uVar10 = uVar28 | 2;
              if (uVar9 == 0) {
                uVar10 = uVar28;
              }
              goto LAB_18003e5d1;
            }
            if (uVar26 == 0x2d) goto LAB_18003e805;
            uVar22 = *(uint *)(param_1 + 2);
            uVar13 = (ulonglong)uVar26;
            uVar12 = FUN_18003f934(uVar26);
            if ((int)uVar12 == 0) {
              uVar12 = FUN_18003f980((short)uVar13);
              if ((int)uVar12 != 0) {
                if (uVar22 < *(uint *)(param_1 + 1)) {
                  lVar17 = *param_1;
                  iVar8 = FUN_180161964(uVar13,*(ushort *)(lVar17 + (ulonglong)(uVar22 - 1) * 2));
                  if ((iVar8 != 0) &&
                     (iVar8 = FUN_180161964(uVar13,*(ushort *)(lVar17 + (ulonglong)(uVar22 + 1) * 2)
                                           ), iVar8 != 0)) {
                    local_74 = (int)local_58 + 1;
                    cVar19 = '\0';
                    uVar27 = 10;
                    *(uint *)(param_1 + 2) = local_74;
                    goto LAB_18003efe9;
                  }
                }
                uVar22 = (-(uint)(cVar19 != '\0') & 0x51) - 1;
                goto LAB_18003e5d1;
              }
              lVar17 = *param_1;
              uVar9 = uVar22 - 1;
              uVar12 = FUN_180079148(*(short *)(lVar17 + (ulonglong)uVar9 * 2));
              if (((int)uVar12 != 0) &&
                 (uVar12 = FUN_18003f980(*(short *)(lVar17 + (ulonglong)(uVar22 - 2) * 2)),
                 (int)uVar12 != 0)) {
                *(uint *)(param_1 + 2) = uVar9;
                goto LAB_18003e909;
              }
              if (uVar26 == 0x28) {
                uVar22 = 0x46;
                goto LAB_18003e5d1;
              }
              uVar27 = (-(uint)(cVar19 != '\0') & 0x51) - 1;
            }
            else {
              uVar9 = FUN_18003f58c(*(ushort *)(*param_1 + (ulonglong)(uVar22 - 1) * 2));
              if (uVar9 != 0) goto LAB_18003e873;
              cVar19 = '\0';
            }
          }
          else {
            if (uVar22 == 0x3d) {
              uVar28 = FUN_18003f8fc(uVar26);
              if (uVar28 == 0) {
                uVar12 = FUN_18003f980(uVar26);
                iVar8 = (int)param_1[2];
                if (((int)uVar12 == 0) ||
                   (uVar12 = FUN_18003f980(*(short *)(*param_1 + (ulonglong)(iVar8 - 1) * 2)),
                   (int)uVar12 == 0)) {
                  *(int *)(param_1 + 2) = iVar8 + -1;
                  uVar22 = 0x42;
                }
                else {
                  *(int *)(param_1 + 2) = iVar8 + 1;
                }
              }
              else {
                *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                uVar22 = 0x3c;
              }
            }
            else if (uVar22 == 0x42) {
              uVar22 = FUN_18003f58c(uVar26);
              if ((uVar22 != 0) || (uVar26 == 0x5f)) {
LAB_18003ed31:
                uVar28 = uVar28 | 1;
                if ((*(int *)((longlong)param_1 + 0x74) == 0) &&
                   (uVar22 = FUN_1801619e4(uVar26), uVar22 != 0)) {
                  *(undefined4 *)((longlong)param_1 + 0x74) = 1;
                }
                else if (((int)param_1[0xf] == 0) && (uVar22 = FUN_180066b20(uVar26), uVar22 != 0))
                {
                  *(undefined4 *)(param_1 + 0xf) = 1;
                }
                goto LAB_18003ecd1;
              }
              uVar20 = uVar26;
              uVar12 = FUN_18003f934(uVar26);
              if ((int)uVar12 == 0) {
                uVar12 = FUN_18003f980(uVar20);
                if ((int)uVar12 == 0) goto LAB_18003ea0e;
                *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                uVar22 = 0xfffffffa;
              }
              else {
LAB_18003e805:
                uVar22 = uVar27;
                if (local_res18 == 0) {
                  if (uVar9 == local_74) {
                    local_6c = *(uint *)(param_1 + 2);
                    local_res8[0] = CONCAT31(local_res8[0]._1_3_,cVar19);
                    local_64 = uVar28;
                  }
                  *(int *)(param_1 + 2) = (int)param_1[2] + 1;
LAB_18003e835:
                  uVar22 = 0x28;
                  uVar10 = uVar28;
                }
              }
            }
            else if (uVar22 == 0x46) {
              *(int *)(param_1 + 2) = (int)param_1[2] + 1;
              local_50 = *(uint *)(param_1 + 2);
              uVar22 = 0x47;
            }
            else if (uVar22 == 0x47) {
              uVar9 = FUN_18003f58c(uVar26);
              uVar28 = local_50;
              if (uVar9 == 0) {
                if (uVar26 == 0x29) {
                  uVar13 = (ulonglong)local_50;
                  uVar22 = *(uint *)(param_1 + 2);
                  if (local_50 < uVar22) {
                    lVar17 = *param_1;
                    plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x50))();
                    uVar13 = FUN_180061864(lVar17 + uVar13 * 2,uVar22 - uVar28,plVar15);
                    if (-1 < (int)uVar13) {
                      *(int *)(param_1 + 2) = (int)param_1[2] + 1;
                      uVar22 = 0xffffffff;
                      goto LAB_18003e5d1;
                    }
                  }
                }
                *(uint *)(param_1 + 2) = uVar28 - 1;
                goto LAB_18003ef13;
              }
              if ((*(int *)((longlong)param_1 + 0x74) == 0) &&
                 (uVar28 = FUN_1801619e4(uVar26), uVar28 != 0)) {
                *(undefined4 *)((longlong)param_1 + 0x74) = 1;
              }
              else if (((int)param_1[0xf] == 0) && (uVar28 = FUN_180066b20(uVar26), uVar28 != 0)) {
                *(undefined4 *)(param_1 + 0xf) = 1;
              }
              *(int *)(param_1 + 2) = (int)param_1[2] + 1;
            }
            else if ((uVar22 == 0x50) && (uVar22 = uVar27, cVar19 != '\0')) {
              uVar9 = (int)param_1[2] - 1;
              uVar12 = FUN_18003f934(*(short *)(*param_1 + (ulonglong)uVar9 * 2));
              if ((int)uVar12 != 0) {
                *(uint *)(param_1 + 2) = uVar9;
                bVar6 = (uint)local_58 == uVar9;
                if (bVar6) {
                  local_58 = uVar13;
                  uVar10 = uVar28 & 0xfffffffb;
                }
              }
            }
LAB_18003e5d1:
            uVar27 = uVar22;
            uVar28 = uVar10;
            if ((cVar19 != '\0') && ((uVar22 < 0x50 || (0x59 < (int)uVar22)))) {
LAB_18003e5eb:
              uVar20 = uVar26;
              uVar12 = FUN_18003f934(uVar26);
              uVar27 = uVar22;
              uVar28 = uVar10;
              if (((int)uVar12 == 0) && (uVar12 = FUN_18003f980(uVar20), (int)uVar12 == 0)) {
                uVar22 = FUN_18003f58c(uVar20);
                if ((uVar22 == 0) && (uVar26 != 0x5f)) {
                  cVar19 = '\0';
                }
                else {
                  cVar19 = '\x01';
                }
              }
            }
          }
LAB_18003efe9:
          uVar13 = (ulonglong)local_6c;
          uVar22 = uVar27;
          if (499 < *(uint *)(param_1 + 2)) {
            local_67 = '\x01';
            uVar22 = 0xffffffff;
          }
        }
        uVar22 = local_6c;
        if (uVar21 < local_74) {
          uVar10 = 0xffffffff;
        }
        uVar9 = *(uint *)(param_1 + 2) - 1;
        uVar27 = *(uint *)(param_1 + 2);
        while (*(short *)(*param_1 + (ulonglong)uVar9 * 2) == 0x5f) {
          *(uint *)(param_1 + 2) = uVar27 - 1;
          uVar9 = uVar27 - 2;
          uVar27 = uVar27 - 1;
        }
        if (uVar10 == 0xfffffffe) {
          uVar9 = 5;
        }
        else if (uVar10 == 0xfffffffa) {
          local_60 = 1;
          uVar9 = 4;
        }
        else if (uVar10 == 0xfffffffb) {
          uVar9 = 6;
        }
        else if (uVar10 == 0xfffffffd) {
          uVar9 = 7;
        }
        else {
          uVar9 = local_5c;
          if (uVar10 == 0xffffffff) {
            local_5c = 3;
            if ((uVar21 < local_6c) && (local_6c < uVar27)) {
              iVar8 = 0;
              if (local_res18 == 0) {
                if ((uVar28 & 0x40) == 0) {
                  lVar17 = (**(code **)(*(longlong *)param_1[0x10] + 0x50))();
                  plVar15 = (longlong *)(**(code **)(*(longlong *)param_1[0x10] + 0x58))();
                  uVar27 = *(uint *)(param_1 + 2);
                  uVar16 = FUN_18003f9e4((ushort *)(*param_1 + uVar16 * 2),uVar27 - uVar21,
                                         uVar27 - uVar21,plVar15,lVar17);
                  iVar8 = (int)uVar16;
                  if (iVar8 != 0) {
                    uVar28 = uVar28 | 0x40;
                  }
                }
                local_60 = (uint)(iVar8 == 0);
              }
              else {
                *(uint *)(param_1 + 2) = local_6c;
                uVar28 = local_64;
                uVar27 = local_6c;
                if (local_4c != 0) {
                  local_5c = local_4c;
                }
              }
            }
            uVar9 = local_5c;
            if ((uVar28 & 4) != 0) {
              uVar10 = (uint)local_58;
              if ((local_60 != 0) && (uVar10 < uVar22)) {
                cVar19 = (char)local_res8[0];
              }
              if (cVar19 == '\0') {
                if (local_res18 == 0) {
                  local_60 = local_60 | 2;
                }
                else {
                  if (uVar10 < uVar27) {
                    *(uint *)(param_1 + 2) = uVar10;
                    uVar27 = uVar10;
                  }
                  uVar28 = 1;
                }
              }
            }
          }
        }
        param_2 = local_res10;
        FUN_1800774b4(local_res10,*param_1,uVar9,uVar21,uVar27 - uVar21,uVar28);
        if (local_67 != '\0') {
          *(undefined4 *)(param_2 + 3) = 1;
        }
        goto LAB_18003f2ba;
      }
      uVar20 = uVar26;
      uVar12 = FUN_180075e74(uVar26);
      if (((((int)uVar12 != 0) || (uVar12 = FUN_18003f2e4(uVar20), (int)uVar12 != 0)) ||
          (uVar26 == 0x2024)) ||
         (((uVar26 == 0x2025 || (uVar26 == 0x2026)) ||
          ((uVar26 == 0x203d || (bVar6 = false, uVar26 == 0xff0e)))))) {
        bVar6 = true;
      }
      lVar17 = *param_1;
      iVar30 = 0;
      iVar8 = 1;
      iVar23 = 0xc;
      if (!bVar6) {
        iVar23 = 0xf;
      }
      goto LAB_18003f25f;
    }
    uVar28 = uVar21 + 1;
    uVar16 = (ulonglong)uVar28;
    *(uint *)(param_1 + 2) = uVar28;
    if (uVar28 < *(uint *)(param_1 + 1)) {
      lVar17 = *param_1;
      do {
        uVar26 = *(ushort *)(lVar17 + uVar16 * 2);
        uVar12 = FUN_180079ea4(uVar26);
        if (((int)uVar12 != 0) || (uVar12 = FUN_180072d30(uVar26), (int)uVar12 == 0)) break;
        uVar28 = (int)uVar16 + 1;
        uVar16 = (ulonglong)uVar28;
        *(uint *)(param_1 + 2) = uVar28;
      } while (uVar28 < *(uint *)(param_1 + 1));
    }
    iVar8 = (int)uVar16 - uVar21;
    iVar23 = 1;
LAB_18003f2ac:
    uVar29 = 0;
    lVar17 = *param_1;
  }
LAB_18003f2b2:
  FUN_1800774b4(param_2,lVar17,iVar23,uVar21,iVar8,uVar29);
LAB_18003f2ba:
  FUN_18007b2e4(param_1 + 3,param_2);
  return local_60;
}


// FUN_180163334 @ 180163334

undefined8 FUN_180163334(int *param_1,longlong *param_2,longlong param_3,undefined2 *param_4)

{
  int iVar1;
  int iVar2;
  int local_res8 [2];
  int local_18 [4];
  
  local_18[0] = 0;
  local_res8[0] = 0;
  if (*param_1 != 0) {
    return 0;
  }
  FUN_18016345c(param_1,param_2,local_18,local_res8);
  if (local_res8[0] == -1) {
    iVar1 = param_1[1];
    if (iVar1 < 0x32) {
      if (iVar1 < 0) {
        if ((*(int *)(param_3 + 0x10) == 1) && (*(int *)(param_3 + 8) == 3)) {
          return 0;
        }
        *param_4 = 0;
        return 0;
      }
      iVar2 = param_1[(longlong)iVar1 + 2];
      param_1[1] = iVar1 + -1;
      if (iVar2 == local_18[0]) {
        return 0;
      }
      if (iVar2 == 0) {
        *param_4 = 0x29;
        return 0;
      }
      if (iVar2 == 1) {
        *param_4 = 0x7d;
        return 0;
      }
      if (iVar2 == 2) {
        *param_4 = 0x5d;
        return 0;
      }
      if (iVar2 == 3) {
        *param_4 = 0x2019;
        return 0;
      }
      if (iVar2 != 4) {
        if (iVar2 == 5) {
          *param_4 = 0x300d;
          return 0;
        }
        if (iVar2 != 6) {
          return 0;
        }
        *param_4 = 0x300f;
        return 0;
      }
      *param_4 = 0x201d;
      return 0;
    }
  }
  else {
    if (local_res8[0] != 1) {
      return 0;
    }
    iVar1 = param_1[1];
    iVar2 = iVar1 + 1;
    param_1[1] = iVar2;
    if (iVar2 < 0x32) {
      param_1[(longlong)iVar1 + 3] = local_18[0];
      param_1[(longlong)param_1[1] + 0x34] = *(int *)((longlong)param_2 + 0xc);
      return 0;
    }
  }
  *param_1 = 1;
  return 0;
}


// FUN_180079148 @ 180079148

undefined8 FUN_180079148(short param_1)

{
  undefined8 uVar1;
  
  uVar1 = 1;
  if ((((param_1 != 0x27) && (param_1 != 0x92)) && (1 < (ushort)(param_1 + 0xdfe7U))) &&
     (param_1 != 0x203a)) {
    uVar1 = 0;
  }
  return uVar1;
}


// FUN_180058730 @ 180058730

uint FUN_180058730(short *param_1,longlong param_2,longlong param_3,ulonglong param_4)

{
  short sVar1;
  uint uVar2;
  short *psVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (param_2 - 1U < 0x7fffffff) {
    if (0x7ffffffe < param_4) {
LAB_180058798:
      *param_1 = 0;
      return 0x80070057;
    }
    lVar5 = param_4 - param_2;
    lVar4 = param_3 - (longlong)param_1;
    do {
      if ((lVar5 + param_2 == 0) || (sVar1 = *(short *)(lVar4 + (longlong)param_1), sVar1 == 0))
      break;
      *param_1 = sVar1;
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
    psVar3 = param_1 + -1;
    if (param_2 != 0) {
      psVar3 = param_1;
    }
    *psVar3 = 0;
    uVar2 = ~-(uint)(param_2 != 0) & 0x8007007a;
  }
  else {
    uVar2 = 0x80070057;
    if (param_2 != 0) goto LAB_180058798;
  }
  return uVar2;
}


// FUN_1801631c8 @ 1801631c8

int FUN_1801631c8(ushort *param_1,int param_2)

{
  ulonglong uVar1;
  int iVar2;
  
  for (iVar2 = param_2; iVar2 != 0; iVar2 = iVar2 + -1) {
    uVar1 = FUN_180163210(*param_1);
    *param_1 = (ushort)uVar1;
    param_1 = param_1 + 1;
  }
  return param_2;
}


// FUN_180068f88 @ 180068f88

undefined8 * FUN_180068f88(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = *param_2;
  *(undefined4 *)(param_1 + 1) = *(undefined4 *)(param_2 + 1);
  *(undefined4 *)((longlong)param_1 + 0xc) = *(undefined4 *)((longlong)param_2 + 0xc);
  *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_2 + 2);
  FUN_18007b2e4(param_1 + 3,param_2 + 3);
  return param_1;
}


// FUN_1800cdb2c @ 1800cdb2c

undefined8 * FUN_1800cdb2c(undefined8 *param_1)

{
  param_1[2] = 0;
  param_1[1] = "bad array new length";
  *param_1 = std::bad_array_new_length::vftable;
  return param_1;
}


// FUN_18007cc50 @ 18007cc50

undefined8 * FUN_18007cc50(undefined8 *param_1)

{
  param_1[2] = 0;
  param_1[1] = "bad allocation";
  *param_1 = std::bad_alloc::vftable;
  return param_1;
}


// FUN_1800466e0 @ 1800466e0

int FUN_1800466e0(undefined8 param_1,ushort *param_2)

{
  int iVar1;
  
  iVar1 = 0;
  for (; *param_2 != 0; param_2 = param_2 + 1) {
    iVar1 = iVar1 * 0x1003f + (uint)*param_2;
  }
  return iVar1;
}


// FUN_1800774b4 @ 1800774b4

longlong *
FUN_1800774b4(longlong *param_1,longlong param_2,int param_3,undefined4 param_4,undefined4 param_5,
             undefined4 param_6)

{
  *param_1 = param_2;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 1) = 0;
    *(undefined4 *)((longlong)param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 2) = 0;
  }
  FUN_1800774f8((longlong)param_1,param_3);
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)(param_1 + 2) = param_5;
  *(undefined4 *)((longlong)param_1 + 0x14) = param_6;
  *(undefined4 *)((longlong)param_1 + 0xc) = param_4;
  return param_1;
}


// FUN_18003fdb8 @ 18003fdb8

undefined4 FUN_18003fdb8(undefined8 param_1,short *param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if (((param_3 < 2) || (0x3ff < (ushort)(*param_2 + 0x2800U))) ||
     (0x3ff < (ushort)(param_2[1] + 0x2400U))) {
    uVar1 = 0;
  }
  return uVar1;
}


// FUN_18003fbe4 @ 18003fbe4

bool FUN_18003fbe4(longlong param_1,uint param_2,uint *param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  undefined7 extraout_var_01;
  ushort uVar4;
  ushort *puVar5;
  ushort *puVar6;
  int iVar7;
  
  uVar3 = *param_3;
  puVar5 = (ushort *)(param_1 + (ulonglong)param_2 * 2);
  uVar4 = *puVar5;
  puVar6 = puVar5 + 1;
  if ((uVar3 < 3) || (uVar4 != 0x3a)) {
    if ((uVar4 == 0x3e) || (uVar4 == 0x7d)) {
      uVar3 = uVar3 - 1;
      if (uVar3 == 0) {
        return false;
      }
      uVar4 = *puVar6;
      puVar6 = puVar5 + 2;
    }
    if ((2 < uVar3) && (uVar4 == 0x38)) {
      if (*puVar6 != 0x2f) goto LAB_18003fccd;
      bVar1 = FUN_1801619b4(puVar6[1]);
      uVar2 = (uint)CONCAT71(extraout_var_01,bVar1);
      goto LAB_18003fc71;
    }
    if ((uVar4 == 0x3a) || ((uVar4 == 0x3b || (uVar4 == 0x38)))) goto LAB_18003fccd;
    bVar1 = uVar4 == 0x25;
  }
  else {
    if ((*puVar6 == 0x2f) && (puVar5[2] == 0x2f)) {
      return false;
    }
    bVar1 = FUN_1801619b4(*puVar6);
    if (((int)CONCAT71(extraout_var,bVar1) != 0) &&
       (bVar1 = FUN_1801619b4(puVar5[2]), (int)CONCAT71(extraout_var_00,bVar1) != 0)) {
      return false;
    }
    if (*puVar6 != 0x5c) goto LAB_18003fccd;
    uVar2 = FUN_18003f9ac(puVar5[2]);
LAB_18003fc71:
    bVar1 = uVar2 == 0;
  }
  if (!bVar1) {
    return false;
  }
LAB_18003fccd:
  iVar7 = uVar3 - 1;
  if (iVar7 != 0) {
    uVar4 = *puVar6;
    puVar5 = puVar6 + 1;
    if ((uVar4 == 0x2d) || (uVar4 == 0x5e)) {
      iVar7 = uVar3 - 2;
      if (iVar7 == 0) {
        return false;
      }
      uVar4 = *puVar5;
      puVar5 = puVar6 + 2;
    }
    if (((uVar4 == 0x6f) ||
        ((((ushort)(uVar4 - 0x28) < 0x35 &&
          ((0x10008210500081U >> ((ulonglong)(uVar4 - 0x28) & 0x3f) & 1) != 0)) || (uVar4 == 0x7c)))
        ) || (((uVar4 == 0x30 || (uVar4 == 0x29)) && (puVar5[-2] != 0x38)))) {
      uVar3 = (uint)((longlong)((longlong)puVar5 + ((ulonglong)param_2 * -2 - param_1)) >> 1);
      *param_3 = uVar3;
      puVar6 = puVar5;
      if (((ushort)(uVar4 - 0x28) < 2) && (iVar7 = iVar7 + -1, iVar7 != 0)) {
        uVar4 = *puVar5;
        puVar6 = puVar5 + 1;
        if (uVar4 == puVar5[-1]) {
          *param_3 = uVar3 + 1;
        }
      }
      uVar3 = FUN_18003f58c(uVar4);
      if ((uVar3 != 0) && (iVar7 != 1)) {
        uVar3 = FUN_18003f9ac(*puVar6);
        return uVar3 == 0;
      }
      return true;
    }
  }
  return false;
}


// FUN_18007a664 @ 18007a664

ulonglong FUN_18007a664(short param_1)

{
  undefined8 uVar1;
  ulonglong uVar2;
  
  uVar1 = FUN_1800632f4(param_1);
  uVar2 = 0;
  if ((int)uVar1 == 0) {
    uVar1 = FUN_180160fe0(param_1);
    if ((int)uVar1 == 0) goto LAB_18007a68b;
  }
  uVar2 = 1;
LAB_18007a68b:
  return uVar2 & 0xffffffff;
}


// FUN_18003f9e4 @ 18003f9e4

ulonglong FUN_18003f9e4(ushort *param_1,uint param_2,uint param_3,longlong *param_4,longlong param_5
                       )

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  ushort *puVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ushort *puVar8;
  longlong lVar9;
  ulonglong uVar10;
  longlong lVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined8 *puVar16;
  
  if (param_4 != (longlong *)0x0) {
    iVar14 = (int)param_4[1] + -1;
    iVar12 = 0;
    do {
      iVar13 = 0;
      iVar15 = iVar14;
      iVar14 = -1;
      while (uVar6 = 0, iVar12 <= iVar15) {
        iVar3 = (iVar15 + iVar12) / 2;
        lVar11 = (longlong)iVar3;
        puVar5 = *(ushort **)(*param_4 + lVar11 * 8);
        lVar9 = (longlong)param_1 - (longlong)puVar5;
        uVar10 = uVar6;
        while( true ) {
          uVar4 = (uint)uVar10;
          if (param_2 <= uVar4) break;
          if (*puVar5 == 0) goto LAB_18003fa83;
          uVar1 = *(ushort *)(lVar9 + (longlong)puVar5);
          uVar2 = *puVar5;
          if (uVar1 >= uVar2 && uVar1 != uVar2) {
            if (((param_3 <= uVar4) && (iVar14 == -1)) &&
               ((uVar1 != 0x5f && (uVar4 = FUN_18003f9ac(uVar1), uVar4 == 0)))) {
              iVar14 = iVar3 + -1;
              iVar13 = iVar12;
            }
            goto LAB_18003fb44;
          }
          if (uVar1 < uVar2) goto LAB_18003fb4c;
          puVar5 = puVar5 + 1;
          uVar10 = (ulonglong)(uVar4 + 1);
        }
        if (uVar4 == param_2) {
          if (*puVar5 == 0) {
            return uVar10;
          }
LAB_18003fb4c:
          iVar15 = iVar3 + -1;
        }
        else {
LAB_18003fa83:
          if (param_3 <= uVar4) {
            puVar16 = (undefined8 *)(*param_4 + lVar11 * 8);
            goto LAB_18003fa99;
          }
LAB_18003fb44:
          iVar12 = iVar3 + 1;
        }
      }
      iVar12 = iVar13;
    } while (iVar13 <= iVar14);
  }
  return 0;
LAB_18003fa99:
  uVar7 = uVar6;
  if (iVar15 < lVar11) goto LAB_18003fb6f;
  if ((param_1[uVar10] != 0x5f) && (uVar4 = FUN_18003f9ac(param_1[uVar10]), uVar4 == 0)) {
    uVar6 = uVar10;
  }
  uVar10 = 0;
  uVar7 = uVar6;
  if (lVar11 == iVar15) goto LAB_18003fb6f;
  puVar16 = puVar16 + 1;
  lVar11 = lVar11 + 1;
  puVar5 = (ushort *)*puVar16;
  puVar8 = param_1;
  if (param_2 != 0) {
    do {
      if ((*puVar5 == 0) || (*puVar8 != *puVar5)) break;
      puVar8 = puVar8 + 1;
      puVar5 = puVar5 + 1;
      uVar4 = (int)uVar10 + 1;
      uVar10 = (ulonglong)uVar4;
    } while (uVar4 < param_2);
  }
  if (*puVar5 != 0) {
    if (*puVar8 <= *puVar5) goto LAB_18003fb6f;
    goto LAB_18003fa99;
  }
  uVar7 = uVar10;
  if ((uint)uVar10 == param_2) {
LAB_18003fb6f:
    if (((param_5 != 0) && ((int)uVar7 + 3U <= param_2)) && (param_1[uVar7] == 0x28)) {
      uVar4 = (int)uVar7 + 1;
      uVar6 = FUN_18003f9e4(param_1 + uVar4,(param_2 - uVar4) - 1,1,(longlong *)param_5,0);
      if (((int)uVar6 != 0) && (uVar4 = uVar4 + (int)uVar6, param_1[uVar4] == 0x29)) {
        uVar7 = (ulonglong)(uVar4 + 1);
      }
    }
    return uVar7;
  }
  goto LAB_18003fa99;
}


// FUN_180075e74 @ 180075e74

undefined8 FUN_180075e74(ushort param_1)

{
  bool bVar1;
  
  if (param_1 < 0x55f) {
    if (param_1 == 0x55e) {
      return 1;
    }
    if (param_1 == 0x21) {
      return 1;
    }
    if (param_1 == 0x3f) {
      return 1;
    }
    if (param_1 == 0x1c3) {
      return 1;
    }
    if (param_1 == 0x37e) {
      return 1;
    }
    bVar1 = param_1 == 0x55c;
  }
  else {
    if (param_1 == 0x61f) {
      return 1;
    }
    if (param_1 == 0x203c) {
      return 1;
    }
    if (param_1 == 0x2762) {
      return 1;
    }
    if (param_1 == 0xfe56) {
      return 1;
    }
    bVar1 = param_1 == 0xfe57;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}


// FUN_18003f2e4 @ 18003f2e4

undefined8 FUN_18003f2e4(short param_1)

{
  if ((((param_1 != 0x589) && (param_1 != 0x964)) && (param_1 != 0x3002)) &&
     (((param_1 != -0xff && (param_1 != -0xe1)) && (param_1 != -0x9f)))) {
    return 0;
  }
  return 1;
}


// FUN_18016156c @ 18016156c

undefined8 FUN_18016156c(ushort param_1)

{
  bool bVar1;
  
  if (param_1 < 0x300d) {
    if (param_1 == 0x300c) {
      return 1;
    }
    if (param_1 == 0x28) {
      return 1;
    }
    if (param_1 == 0x5b) {
      return 1;
    }
    if (param_1 == 0x7b) {
      return 1;
    }
    if (param_1 == 0x2018) {
      return 1;
    }
    bVar1 = param_1 == 0x201c;
  }
  else {
    if (param_1 == 0x300e) {
      return 1;
    }
    if (param_1 == 0xff08) {
      return 1;
    }
    if (param_1 == 0xff3b) {
      return 1;
    }
    if (param_1 == 0xff5b) {
      return 1;
    }
    bVar1 = param_1 == 0xff62;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}


// FUN_1801615c8 @ 1801615c8

undefined8 FUN_1801615c8(ushort param_1)

{
  bool bVar1;
  
  if (param_1 < 0x300e) {
    if (param_1 == 0x300d) {
      return 1;
    }
    if (param_1 == 0x29) {
      return 1;
    }
    if (param_1 == 0x5d) {
      return 1;
    }
    if (param_1 == 0x7d) {
      return 1;
    }
    if (param_1 == 0x2019) {
      return 1;
    }
    bVar1 = param_1 == 0x201d;
  }
  else {
    if (param_1 == 0x300f) {
      return 1;
    }
    if (param_1 == 0xff09) {
      return 1;
    }
    if (param_1 == 0xff3d) {
      return 1;
    }
    if (param_1 == 0xff5d) {
      return 1;
    }
    bVar1 = param_1 == 0xff63;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}


// FUN_18003f934 @ 18003f934

undefined8 FUN_18003f934(short param_1)

{
  undefined8 uVar1;
  
  uVar1 = 1;
  if ((((param_1 != 0x27) && (1 < (ushort)(param_1 + 0xdfe8U))) && (param_1 != 0xb4)) &&
     (((param_1 != 0x60 && (param_1 != 0x2032)) && (param_1 != -0xf9)))) {
    uVar1 = 0;
  }
  return uVar1;
}


// FUN_18003f980 @ 18003f980

undefined8 FUN_18003f980(short param_1)

{
  if (((param_1 != 0x2e) && (param_1 != -0xf2)) && (param_1 != 0x6d4)) {
    return 0;
  }
  return 1;
}


// FUN_18003f4f4 @ 18003f4f4

undefined8 FUN_18003f4f4(short param_1)

{
  if ((((param_1 != 0x2c) && (param_1 != 0x2f)) && (param_1 != 0x3a)) && (param_1 != 0x3b)) {
    return 0;
  }
  return 1;
}


// FUN_18003f324 @ 18003f324

undefined8 FUN_18003f324(ushort param_1)

{
  bool bVar1;
  
  if (param_1 < 0xb6) {
    if (param_1 == 0xb5) {
      return 1;
    }
    if (param_1 < 0x7d) {
      if (param_1 == 0x7c) {
        return 1;
      }
      if (param_1 == 0x23) {
        return 1;
      }
      if (param_1 == 0x25) {
        return 1;
      }
      if (param_1 == 0x26) {
        return 1;
      }
      if (param_1 == 0x2a) {
        return 1;
      }
      if (param_1 == 0x40) {
        return 1;
      }
      bVar1 = param_1 == 0x5c;
    }
    else {
      if (param_1 == 0xa6) {
        return 1;
      }
      if (param_1 == 0xa7) {
        return 1;
      }
      if (param_1 == 0xa9) {
        return 1;
      }
      if (param_1 == 0xae) {
        return 1;
      }
      bVar1 = param_1 == 0xb0;
    }
  }
  else if (param_1 < 0x2104) {
    if (param_1 == 0x2103) {
      return 1;
    }
    if (param_1 == 0xb6) {
      return 1;
    }
    if (param_1 == 0xb7) {
      return 1;
    }
    if (param_1 == 0x2020) {
      return 1;
    }
    if (param_1 == 0x2021) {
      return 1;
    }
    bVar1 = param_1 == 0x2030;
  }
  else {
    if (param_1 == 0x2105) {
      return 1;
    }
    if (param_1 == 0x2106) {
      return 1;
    }
    if (param_1 == 0x2109) {
      return 1;
    }
    if (param_1 == 0x2116) {
      return 1;
    }
    bVar1 = param_1 == 0x2122;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}


// FUN_18003f51c @ 18003f51c

undefined8 FUN_18003f51c(ushort param_1)

{
  bool bVar1;
  
  if (param_1 < 0x2212) {
    if (param_1 == 0x2211) {
      return 1;
    }
    if (param_1 == 0x2b) {
      return 1;
    }
    if (param_1 == 0x3c) {
      return 1;
    }
    if (param_1 == 0x3d) {
      return 1;
    }
    if (param_1 == 0x3e) {
      return 1;
    }
    if (param_1 == 0xac) {
      return 1;
    }
    if (param_1 == 0xb1) {
      return 1;
    }
    if (param_1 == 0xd7) {
      return 1;
    }
    bVar1 = param_1 == 0xf7;
  }
  else {
    if (param_1 == 0x221a) {
      return 1;
    }
    if (param_1 == 0x221e) {
      return 1;
    }
    if (param_1 == 0x222b) {
      return 1;
    }
    if (param_1 == 0x2248) {
      return 1;
    }
    if (param_1 == 0x2260) {
      return 1;
    }
    if (param_1 == 0x2264) {
      return 1;
    }
    bVar1 = param_1 == 0x2265;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}


// FUN_18003f474 @ 18003f474

undefined8 FUN_18003f474(short param_1)

{
  if ((((param_1 != 0x2022) && (param_1 != 0x25a1)) && (param_1 != 0x25aa)) &&
     (((param_1 != 0x25ab && (param_1 != 0x25ca)) && ((param_1 != 0x25cf && (param_1 != 0x25e6))))))
  {
    return 0;
  }
  return 1;
}


// FUN_18003f3cc @ 18003f3cc

undefined8 FUN_18003f3cc(ushort param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = (uint)param_1;
  if (param_1 < 0x20a5) {
    if (param_1 == 0x20a4) {
      return 1;
    }
    if (0x9f2 < uVar1) {
      if (uVar1 == 0x9f3) {
        return 1;
      }
      if (uVar1 == 0xe3f) {
        return 1;
      }
      iVar2 = uVar1 - 0x20a0;
      if (iVar2 == 0) {
        return 1;
      }
      goto LAB_18003f3f1;
    }
    if (uVar1 == 0x9f2) {
      return 1;
    }
    if (uVar1 == 0x24) {
      return 1;
    }
    iVar2 = uVar1 - 0xa2;
    bVar3 = iVar2 == 0;
  }
  else if (uVar1 < 0x20ac) {
    if (uVar1 == 0x20ab) {
      return 1;
    }
    if (uVar1 == 0x20a6) {
      return 1;
    }
    iVar2 = uVar1 - 0x20a7;
    bVar3 = iVar2 == 0;
  }
  else {
    iVar2 = uVar1 - 0x20ac;
    bVar3 = iVar2 == 0;
  }
  if (bVar3) {
    return 1;
  }
  if (iVar2 == 1) {
    return 1;
  }
LAB_18003f3f1:
  if ((iVar2 != 2) && (iVar2 != 3)) {
    return 0;
  }
  return 1;
}


// FUN_18003f4b4 @ 18003f4b4

undefined8 FUN_18003f4b4(short param_1)

{
  if ((((param_1 != 0x2d) && (param_1 != 0x2010)) && (param_1 != 0x2012)) &&
     (((param_1 != 0x2013 && (param_1 != 0x2014)) && ((param_1 != 0x2015 && (param_1 != 0x2212))))))
  {
    return 0;
  }
  return 1;
}


// FUN_18003f44c @ 18003f44c

undefined8 FUN_18003f44c(short param_1)

{
  if ((param_1 != 0xbf) && (param_1 != 0xa1)) {
    return 0;
  }
  return 1;
}


// FUN_18003f8fc @ 18003f8fc

uint FUN_18003f8fc(ushort param_1)

{
  uint uVar1;
  
  if ((param_1 & 0xff00) == 0) {
    uVar1 = (byte)(&DAT_180180820)[(ulonglong)param_1 & 0xff] & 4;
  }
  else {
    uVar1 = FUN_180072dbc(param_1);
    uVar1 = uVar1 & 0x400000;
  }
  return uVar1;
}


// FUN_180161120 @ 180161120

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool FUN_180161120(longlong param_1,ushort *param_2,uint param_3,longlong param_4,
                  undefined1 *param_5)

{
  longlong lVar1;
  ushort *puVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  longlong *plVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  ushort uVar12;
  ushort *puVar13;
  ushort *puVar14;
  ulonglong uVar15;
  bool bVar16;
  undefined1 auStack_1b8 [32];
  longlong local_198;
  uint local_190;
  uint local_18c;
  undefined1 *local_188;
  longlong local_180;
  ushort *local_178;
  ulonglong local_170;
  undefined8 uStack_168;
  ushort local_158 [128];
  ulonglong local_58;
  
  local_58 = DAT_1801c0240 ^ (ulonglong)auStack_1b8;
  uVar11 = 0;
  puVar14 = param_2 + param_3;
  local_198 = param_1;
  puVar13 = param_2;
  local_178 = param_2;
  local_18c = param_3;
  local_180 = param_4;
  local_188 = param_5;
  while (((puVar13 < puVar14 && (uVar4 = FUN_18003f58c(*puVar13), uVar4 == 0)) &&
         (uVar4 = FUN_18003f9ac(*puVar13), uVar4 != 0))) {
    puVar13 = puVar13 + 1;
  }
  if ((puVar13 + 1 < puVar14) && (puVar2 = puVar13 + 1, (*puVar13 - 0x2c & 0xfffd) == 0)) {
    while (puVar13 = puVar2, uVar4 = FUN_18003f58c(*puVar13), uVar4 == 0) {
      uVar4 = FUN_18003f9ac(*puVar13);
      if ((uVar4 == 0) || (puVar13 = puVar13 + 1, puVar2 = puVar13, puVar14 <= puVar13)) break;
    }
  }
  uVar4 = param_3 - (int)((longlong)puVar13 - (longlong)param_2 >> 1);
  local_190 = uVar4;
  if ((puVar13 == param_2) || (2 < uVar4)) {
    if (uVar4 < 0x80) {
      plVar8 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x20))();
      uVar9 = FUN_180061864((longlong)puVar13,uVar4,plVar8);
      if (-1 < (int)uVar9) {
        return true;
      }
      uVar5 = FUN_1801619e4(*puVar13);
      if ((uVar5 == 0) || (uVar4 < 3)) {
        FUN_180058730((short *)local_158,0x80,(longlong)puVar13,(ulonglong)uVar4);
      }
      else {
        FUN_180058730((short *)local_158,0x80,(longlong)puVar13,(ulonglong)uVar4);
        uVar5 = FUN_1801631c8(local_158,uVar4);
        if (uVar5 == uVar4) {
          plVar8 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x20))();
          uVar9 = FUN_180061864((longlong)local_158,uVar4,plVar8);
          if (-1 < (int)uVar9) {
            return true;
          }
        }
        FUN_180058730((short *)local_158,0x80,(longlong)puVar13,(ulonglong)uVar4);
        lVar1 = local_180;
        puVar13 = local_158;
        uVar9 = uVar11;
        uVar15 = uVar11;
        param_1 = local_198;
        if (local_158[0] != 0) {
          do {
            uVar3 = local_158[0];
            if ((int)uVar15 == 0) {
              uVar3 = *puVar13;
              if (uVar3 < 0x100) {
                if ((uVar3 & 0xff00) == 0) {
                  if (((&DAT_180180820)[(ulonglong)uVar3 & 0xff] & 0x80) == 0) {
                    uVar12 = (ushort)(byte)(&DAT_180193c50)[(byte)uVar3];
                    goto LAB_18016133d;
                  }
                }
                else {
                  uVar15 = (ulonglong)uVar3 - 0x2018;
                  uVar12 = uVar3;
                  if (uVar15 < 8) {
                    uVar12 = *(ushort *)(&DAT_180193dd8 + uVar15 * 2);
                  }
LAB_18016133d:
                  uVar15 = uVar11;
                  if (uVar12 != 0x79) goto LAB_180161377;
                }
                uVar15 = 1;
              }
              else if (lVar1 != 0) {
                local_170 = 0;
                uStack_168 = 0;
                iVar6 = FUN_18005bbcc(lVar1,(uint)uVar3,(undefined4 *)&local_170);
                if ((iVar6 != 0) && ((local_170 & 0x100000000) != 0)) {
                  uVar15 = 1;
                }
              }
            }
LAB_180161377:
            uVar5 = FUN_180066b20(uVar3);
            puVar13 = puVar13 + 1;
            uVar5 = (uint)uVar9 | uVar5;
            local_158[0] = *puVar13;
            uVar9 = (ulonglong)uVar5;
          } while (local_158[0] != 0);
          param_2 = local_178;
          param_1 = local_198;
          uVar4 = local_190;
          if (((int)uVar15 == 0) && (uVar5 != 0)) {
            return true;
          }
        }
      }
      if ((3 < uVar4) && ((uVar4 & 1) == 0)) {
        bVar16 = local_188 != (undefined1 *)0x0;
        puVar14 = local_158;
        uVar9 = uVar11;
        do {
          uVar5 = (uint)uVar9;
          if ((uVar9 & 1) == 0) {
            uVar7 = FUN_18003f58c(*puVar14);
            if (uVar7 == 0) break;
            if ((bVar16) && (uVar7 = FUN_1801619e4(*puVar14), uVar7 != 0)) {
              bVar16 = true;
            }
            else {
              bVar16 = false;
            }
          }
          else {
            uVar10 = FUN_18003f980(*puVar14);
            if ((int)uVar10 == 0) break;
          }
          uVar5 = uVar5 + 1;
          uVar9 = (ulonglong)uVar5;
          puVar14 = puVar14 + 1;
        } while (uVar5 < uVar4);
        param_1 = local_198;
        if (uVar4 <= uVar5) {
          if (local_188 == (undefined1 *)0x0) {
            return true;
          }
          if (!bVar16) {
            return true;
          }
          *local_188 = 1;
          return true;
        }
      }
      uVar3 = (**(code **)(**(longlong **)(param_1 + 0x80) + 0x68))();
      if ((((uVar3 & 0x3ff) == 10) && (5 < uVar4)) && (uVar4 == (uVar4 / 3) * 3)) {
        puVar14 = local_158;
        do {
          uVar5 = (uint)uVar11;
          iVar6 = (int)(uVar11 / 3);
          uVar3 = *puVar14;
          if (uVar5 == iVar6 * 3) {
            uVar7 = FUN_18003f58c(uVar3);
LAB_1801614f1:
            if (uVar7 == 0) break;
          }
          else {
            if (uVar5 + iVar6 * -3 != 1) {
              uVar10 = FUN_18003f980(uVar3);
              uVar7 = (uint)uVar10;
              goto LAB_1801614f1;
            }
            if (uVar3 != local_158[uVar5 - 1]) break;
          }
          uVar5 = uVar5 + 1;
          uVar11 = (ulonglong)uVar5;
          puVar14 = puVar14 + 1;
        } while (uVar5 < uVar4);
        param_1 = local_198;
        if (uVar4 <= uVar5) {
          return true;
        }
      }
      param_3 = local_18c;
      if (puVar13 != param_2) goto LAB_180161519;
    }
    bVar16 = false;
  }
  else {
LAB_180161519:
    plVar8 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x20))();
    uVar11 = FUN_180061864((longlong)param_2,param_3,plVar8);
    bVar16 = -1 < (int)uVar11;
  }
  return bVar16;
}


// FUN_180161888 @ 180161888

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

uint FUN_180161888(longlong param_1,ushort *param_2,uint param_3,int param_4)

{
  uint uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined1 auStack_138 [32];
  ushort local_118 [128];
  ulonglong local_18;
  
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_138;
  if (param_3 < 0x80) {
    if (param_4 == 0) {
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x40))();
    }
    else {
      FUN_180058730((short *)local_118,0x80,(longlong)param_2,(ulonglong)param_3);
      uVar1 = FUN_1801631c8(local_118,param_3);
      if (uVar1 != param_3) goto LAB_180161934;
      uVar3 = FUN_180163284(local_118[0]);
      local_118[0] = (ushort)uVar3;
      plVar2 = (longlong *)(**(code **)(**(longlong **)(param_1 + 0x80) + 0x40))();
      param_2 = local_118;
    }
    uVar3 = FUN_180061864((longlong)param_2,param_3,plVar2);
    uVar1 = ~(uint)uVar3 >> 0x1f;
  }
  else {
LAB_180161934:
    uVar1 = 0;
  }
  return uVar1;
}


// FUN_180161964 @ 180161964

undefined4 FUN_180161964(undefined8 param_1,ushort param_2)

{
  uint uVar1;
  
  uVar1 = FUN_18003f9ac(param_2);
  if (uVar1 == 0) {
    if (param_2 == 0xad) {
      return 1;
    }
  }
  else if (1 < (ushort)(param_2 + 0x1800)) {
    return 1;
  }
  if (param_2 == 0x5f) {
    return 1;
  }
  return 0;
}


// FUN_18016345c @ 18016345c

void FUN_18016345c(undefined8 param_1,longlong *param_2,undefined4 *param_3,undefined4 *param_4)

{
  ushort uVar1;
  
  uVar1 = *(ushort *)(*param_2 + (ulonglong)*(uint *)((longlong)param_2 + 0xc) * 2);
  if (uVar1 < 0x300e) {
    if (uVar1 == 0x300d) {
LAB_18016357e:
      *param_3 = 5;
LAB_180163533:
      *param_4 = 0xffffffff;
      return;
    }
    if (0x7d < uVar1) {
      if (uVar1 != 0x2018) {
        if (uVar1 == 0x2019) {
          *param_3 = 3;
          goto LAB_180163533;
        }
        if (uVar1 == 0x201c) {
          *param_3 = 4;
          goto LAB_1801634bc;
        }
        if (uVar1 == 0x201d) {
          *param_3 = 4;
          goto LAB_180163533;
        }
        if (uVar1 != 0x300c) {
          return;
        }
      }
LAB_1801634e4:
      *param_3 = 3;
      goto LAB_1801634bc;
    }
    if (uVar1 == 0x7d) {
LAB_180163587:
      *param_3 = 1;
      goto LAB_180163533;
    }
    if (uVar1 != 0x28) {
      if (uVar1 == 0x29) {
LAB_18016352f:
        *param_3 = 0;
        goto LAB_180163533;
      }
      if (uVar1 == 0x5b) {
LAB_18016352a:
        *param_3 = 2;
        goto LAB_1801634bc;
      }
      if (uVar1 == 0x5d) goto LAB_180163557;
      if (uVar1 != 0x7b) {
        return;
      }
      goto LAB_1801634b5;
    }
  }
  else {
    if (0xff3d < uVar1) {
      if (uVar1 == 0xff5b) {
LAB_1801634b5:
        *param_3 = 1;
        goto LAB_1801634bc;
      }
      if (uVar1 == 0xff5d) goto LAB_180163587;
      if (uVar1 == 0xff62) goto LAB_1801634e4;
      if (uVar1 != 0xff63) {
        return;
      }
      goto LAB_18016357e;
    }
    if (uVar1 == 0xff3d) {
LAB_180163557:
      *param_3 = 2;
      goto LAB_180163533;
    }
    if (uVar1 == 0x300e) {
      *param_3 = 6;
      goto LAB_1801634bc;
    }
    if (uVar1 == 0x300f) {
      *param_3 = 6;
      goto LAB_180163533;
    }
    if (uVar1 != 0xff08) {
      if (uVar1 != 0xff09) {
        if (uVar1 != 0xff3b) {
          return;
        }
        goto LAB_18016352a;
      }
      goto LAB_18016352f;
    }
  }
  *param_3 = 0;
LAB_1801634bc:
  *param_4 = 1;
  return;
}


// FUN_180163210 @ 180163210

ulonglong FUN_180163210(ushort param_1)

{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined6 extraout_var;
  
  if ((param_1 & 0xff00) == 0) {
    if ((((&DAT_180180820)[(ulonglong)param_1 & 0xff] & 1) != 0) &&
       (uVar3 = _o_tolower((ulonglong)param_1), ((&DAT_180180820)[uVar3 & 0xff] & 2) != 0)) {
      return uVar3;
    }
  }
  else {
    uVar2 = FUN_180072dbc(param_1);
    if ((uVar2 >> 0x14 & 1) != 0) {
      uVar1 = FUN_180162b68(param_1,-1,0x200000);
      return CONCAT62(extraout_var,uVar1);
    }
  }
  return (ulonglong)param_1;
}


// FUN_1800774f8 @ 1800774f8

longlong FUN_1800774f8(longlong param_1,int param_2)

{
  *(int *)(param_1 + 8) = param_2;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
  }
  return param_1;
}


// FUN_1801619b4 @ 1801619b4

bool FUN_1801619b4(ushort param_1)

{
  if ((param_1 & 0xff00) != 0) {
    return false;
  }
  return ((&DAT_180180820)[(ulonglong)param_1 & 0xff] & 0x14) == 4;
}


// FUN_18005bbcc @ 18005bbcc

undefined4 FUN_18005bbcc(longlong param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_res10 [2];
  
  uVar2 = 0;
  if ((*(longlong *)(param_1 + 0x10) != 0) && (uVar2 = 0, *(int *)(param_1 + 8) != 0)) {
    local_res10[0] = param_2;
    puVar1 = (undefined4 *)
             _o_bsearch(local_res10,*(longlong *)(param_1 + 0x10),*(undefined4 *)(param_1 + 8),0x10,
                        FUN_18004e7e0);
    if (puVar1 != (undefined4 *)0x0) {
      uVar2 = 1;
      *param_3 = *puVar1;
      *(undefined2 *)(param_3 + 1) = *(undefined2 *)(puVar1 + 1);
      *(ulonglong *)(param_3 + 2) = (ulonglong)(uint)puVar1[2] + *(longlong *)(param_1 + 0x18);
      *(ulonglong *)(param_3 + 4) = (ulonglong)(uint)puVar1[3] + *(longlong *)(param_1 + 0x18);
    }
  }
  return uVar2;
}


// FUN_180163284 @ 180163284

ulonglong FUN_180163284(ushort param_1)

{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined6 extraout_var;
  
  if ((param_1 & 0xff00) == 0) {
    if (((&DAT_180180820)[(ulonglong)param_1 & 0xff] & 2) != 0) {
      if (param_1 == 0xff) {
        return 0x178;
      }
      uVar3 = _o_toupper((ulonglong)param_1);
      if (((&DAT_180180820)[uVar3 & 0xff] & 1) != 0) {
        return uVar3;
      }
    }
  }
  else {
    uVar2 = FUN_180072dbc(param_1);
    if ((uVar2 >> 0x15 & 1) != 0) {
      uVar1 = FUN_180162b68(param_1,1,0x100000);
      return CONCAT62(extraout_var,uVar1);
    }
  }
  return (ulonglong)param_1;
}


// FUN_180162b68 @ 180162b68

ushort FUN_180162b68(ushort param_1,short param_2,uint param_3)

{
  ushort uVar1;
  short sVar2;
  uint uVar3;
  ushort uVar4;
  bool bVar5;
  
  uVar3 = FUN_180072dbc(param_1);
  if ((param_3 & uVar3) != 0) {
    return param_1;
  }
  uVar1 = param_1 >> 8;
  uVar4 = param_1;
  if (uVar1 < 0x11) {
    if (uVar1 == 0x10) {
LAB_180162bc6:
      sVar2 = param_2 * 2;
LAB_180162c20:
      param_2 = param_2 + sVar2;
LAB_180162c23:
      param_2 = param_2 << 4;
    }
    else if (uVar1 == 1) {
      if (param_1 < 0x19e) {
        if (param_1 == 0x19d) {
LAB_180162f62:
          sVar2 = 0xd5;
        }
        else if (param_1 < 400) {
          if (param_1 == 399) {
LAB_180162f11:
            sVar2 = 0xca;
          }
          else {
            if (param_1 == 0x130) {
              return 0x130;
            }
            if (param_1 == 0x131) {
              return 0x131;
            }
            if (param_1 == 0x178) {
              uVar4 = 0xff;
              goto LAB_180162bf2;
            }
            if (param_1 == 0x181) goto LAB_180162ef4;
            if (param_1 == 0x186) goto LAB_180162eed;
            if ((param_1 != 0x189) && (param_1 != 0x18a)) {
              if (param_1 == 0x18e) goto LAB_180162ede;
              goto LAB_180162bef;
            }
LAB_180162ee6:
            sVar2 = 0xcd;
          }
        }
        else if (param_1 == 400) {
LAB_180162f5b:
          sVar2 = 0xcb;
        }
        else {
          if (param_1 == 0x193) goto LAB_180162ee6;
          if (param_1 == 0x194) {
LAB_180162f54:
            sVar2 = 0xcf;
          }
          else {
            if (param_1 == 0x195) {
              return 0x195;
            }
            if (param_1 != 0x196) {
              if (param_1 == 0x197) {
LAB_180162f4d:
                sVar2 = 0xd1;
                goto LAB_180162ef9;
              }
              if (param_1 != 0x19c) goto LAB_180162bef;
            }
LAB_180162f46:
            sVar2 = 0xd3;
          }
        }
LAB_180162ef9:
        sVar2 = param_2 * sVar2;
        goto LAB_180162eff;
      }
      if (param_1 < 0x1c7) {
        if (param_1 != 0x1c6) {
          if (param_1 == 0x19e) {
            return 0x19e;
          }
          if (param_1 == 0x19f) {
LAB_180162fbb:
            sVar2 = 0xd6;
          }
          else if ((param_1 == 0x1a9) || (param_1 == 0x1ae)) {
LAB_180162fb1:
            sVar2 = 0xda;
          }
          else if ((param_1 == 0x1b1) || (param_1 == 0x1b2)) {
LAB_180162fa7:
            sVar2 = 0xd9;
          }
          else {
            if (param_1 != 0x1b7) {
              bVar5 = param_1 == 0x1c4;
              goto LAB_180162fed;
            }
LAB_180162e82:
            sVar2 = 0xdb;
          }
          goto LAB_180162ef9;
        }
      }
      else if ((((param_1 != 0x1c7) && (param_1 != 0x1c9)) && (param_1 != 0x1ca)) &&
              (param_1 != 0x1cc)) {
        if (param_1 == 0x1dd) {
LAB_180162ede:
          sVar2 = param_2 * 0x4f;
          goto LAB_180162eff;
        }
        if (param_1 != 0x1f1) {
          bVar5 = param_1 == 499;
LAB_180162fed:
          if (!bVar5) goto LAB_180162bef;
        }
      }
      param_2 = param_2 * 2;
    }
    else if (uVar1 == 2) {
      if (0x217 < param_1) {
        if (param_1 < 0x254) {
LAB_180162ef4:
          sVar2 = 0xd2;
        }
        else {
          if (0x254 < param_1) {
            if (599 < param_1) {
              if (param_1 < 0x259) goto LAB_180162bf2;
              if (param_1 < 0x25a) goto LAB_180162f11;
              if (param_1 < 0x25b) goto LAB_180162bf2;
              if (param_1 < 0x25c) goto LAB_180162f5b;
              if (param_1 < 0x25f) goto LAB_180162bf2;
              if (0x260 < param_1) {
                if (0x263 < param_1) {
                  if (param_1 < 0x268) goto LAB_180162bf2;
                  if (param_1 < 0x269) goto LAB_180162f4d;
                  if (0x269 < param_1) {
                    if (param_1 < 0x26c) goto LAB_180162bf2;
                    if (0x26f < param_1) {
                      if (param_1 < 0x272) goto LAB_180162bf2;
                      if (0x272 < param_1) {
                        if (param_1 < 0x274) goto LAB_180162bf2;
                        if (0x275 < param_1) {
                          if (param_1 < 0x27f) goto LAB_180162bf2;
                          if (0x283 < param_1) {
                            if (param_1 < 0x287) goto LAB_180162bf2;
                            if (0x288 < param_1) {
                              if (0x28b < param_1) {
                                if ((param_1 < 0x291) || ((0x292 < param_1 && (param_1 < 0x2a9))))
                                goto LAB_180162bf2;
                                goto LAB_180162e82;
                              }
                              goto LAB_180162fa7;
                            }
                          }
                          goto LAB_180162fb1;
                        }
                        goto LAB_180162fbb;
                      }
                      goto LAB_180162f62;
                    }
                  }
                  goto LAB_180162f46;
                }
                goto LAB_180162f54;
              }
            }
            goto LAB_180162ee6;
          }
LAB_180162eed:
          sVar2 = 0xce;
        }
        goto LAB_180162ef9;
      }
    }
    else if (uVar1 == 3) {
      if (0x3ef < param_1) {
        return param_1;
      }
      if (((byte)param_1 & 0xf0) == 0xd0) {
        return param_1;
      }
      if (param_1 < 0x387) {
LAB_180162c8c:
        sVar2 = param_2 * 0x26;
        goto LAB_180162eff;
      }
      if (param_1 < 0x38b) {
LAB_180162ca1:
        sVar2 = param_2 * 0x25;
        goto LAB_180162eff;
      }
      if (param_1 < 0x38d) {
LAB_180162c59:
        param_2 = param_2 << 6;
      }
      else {
        if (param_1 < 0x390) {
LAB_180162c69:
          sVar2 = param_2 * 0x3f;
          goto LAB_180162eff;
        }
        if (0x3ab < param_1) {
          if (param_1 < 0x3ad) goto LAB_180162c8c;
          if (param_1 < 0x3b0) goto LAB_180162ca1;
          if (0x3c1 < param_1) {
            if (param_1 < 0x3c3) {
              sVar2 = param_2 * 0x1f;
              goto LAB_180162eff;
            }
            if (0x3cb < param_1) {
              if (param_1 < 0x3cd) goto LAB_180162c59;
              if (0x3cf < param_1) goto LAB_180162bef;
              goto LAB_180162c69;
            }
          }
        }
LAB_180162beb:
        param_2 = param_2 << 5;
      }
    }
    else {
      if (uVar1 != 4) {
        if (uVar1 != 5) {
          return param_1;
        }
        goto LAB_180162bc6;
      }
      if (((param_1 & 0xf0) == 0) || ((param_1 & 0xf0) == 0x50)) {
        sVar2 = param_2 << 2;
        goto LAB_180162c20;
      }
      if (param_1 < 0x460) goto LAB_180162beb;
    }
LAB_180162bef:
    uVar4 = param_1 - param_2;
  }
  else {
    if (uVar1 == 0x1e) goto LAB_180162bef;
    if (uVar1 == 0x1f) {
      if (param_1 < 0x1f70) goto LAB_180163174;
      if (param_1 < 0x1f72) {
LAB_1801630d8:
        sVar2 = param_2 * 0x4a;
      }
      else if (param_1 < 0x1f76) {
LAB_1801630fb:
        sVar2 = param_2 * 0x56;
      }
      else if (param_1 < 0x1f78) {
LAB_180163140:
        sVar2 = param_2 * 100;
      }
      else if (param_1 < 0x1f7a) {
LAB_1801631a6:
        sVar2 = param_2 * 0x80;
      }
      else if (param_1 < 0x1f7c) {
LAB_18016318a:
        sVar2 = param_2 * 0x70;
      }
      else {
        if (0x1f7d < param_1) {
          if (param_1 < 0x1fb0) goto LAB_180162bf2;
          if (0x1fb1 < param_1) {
            if (param_1 < 0x1fb5) goto LAB_180162bf2;
            if (0x1fb9 < param_1) {
              if (param_1 < 0x1fbc) goto LAB_1801630d8;
              if (param_1 < 0x1fbd) goto LAB_180162bf2;
              if (param_1 < 0x1fcc) goto LAB_1801630fb;
              if (param_1 < 0x1fcd) goto LAB_180162bf2;
              if (0x1fd1 < param_1) {
                if (param_1 < 0x1fd4) goto LAB_180162bf2;
                if (0x1fd9 < param_1) {
                  if (param_1 < 0x1fdc) goto LAB_180163140;
                  if (0x1fe1 < param_1) {
                    if (param_1 < 0x1fe5) goto LAB_180162bf2;
                    if (0x1fe5 < param_1) {
                      if (param_1 < 0x1fea) goto LAB_180163174;
                      if (param_1 < 0x1fec) goto LAB_18016318a;
                      if (param_1 != 0x1fec) {
                        if (param_1 < 0x1ffa) goto LAB_1801631a6;
                        goto LAB_1801631b3;
                      }
                    }
                    sVar2 = param_2 * 7;
                    goto LAB_1801631b9;
                  }
                }
              }
            }
          }
LAB_180163174:
          uVar4 = param_1 + param_2 * 8;
          goto LAB_180162bf2;
        }
LAB_1801631b3:
        sVar2 = param_2 * 0x7e;
      }
LAB_1801631b9:
      uVar4 = sVar2 + param_1;
      goto LAB_180162bf2;
    }
    if (uVar1 == 0x21) goto LAB_180162c23;
    if (uVar1 != 0x24) {
      if (uVar1 != 0xff) {
        return param_1;
      }
      goto LAB_180162beb;
    }
    sVar2 = param_2 * 0x1a;
LAB_180162eff:
    uVar4 = param_1 - sVar2;
  }
LAB_180162bf2:
  uVar3 = FUN_180072dbc(uVar4);
  if ((param_3 & uVar3) != 0) {
    param_1 = uVar4;
  }
  return param_1;
}


// FUN_18004e7e0 @ 18004e7e0

int FUN_18004e7e0(uint *param_1,uint *param_2)

{
  if (*param_1 <= *param_2) {
    return -(uint)(*param_1 != *param_2);
  }
  return 1;
}


