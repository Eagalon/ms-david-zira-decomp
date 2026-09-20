// FUN_1800e34c8 @ 1800e34c8

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_1800e34c8(longlong *param_1,longlong param_2,longlong param_3,TypeDescriptor *param_4)

{
  uint uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  TypeDescriptor *pTVar4;
  
  *(uint *)&param_4->spare = (uint)(*(longlong *)(param_1[2] + 0x48) != 0);
  param_4[4].pVFTable = (void *)0x1;
  if ((param_2 == 0) || (param_3 == 0)) {
    uVar3 = 1;
  }
  else {
    pTVar4 = param_4;
    uVar1 = (**(code **)(*param_1 + 0x18))();
    uVar3 = (ulonglong)uVar1;
    if (-1 < (int)uVar1) {
      if (param_4[2].spare == (void *)0x0) {
        uVar3 = 1;
      }
      else {
        uVar2 = FUN_1800e39f0((longlong)param_4);
        uVar3 = uVar2 & 0xffffffff;
        if (-1 < (int)uVar2) {
          uVar2 = FUN_1800e392c((longlong)param_4,*(undefined4 *)(param_1[1] + 0x68));
          uVar3 = uVar2 & 0xffffffff;
          if (-1 < (int)uVar2) {
            uVar3 = FUN_1800e378c(param_1,(ulonglong)param_4);
            uVar3 = uVar3 & 0xffffffff;
          }
        }
      }
    }
    if ((int)uVar3 == 0) {
      uVar1 = FUN_1800e46b0((longlong)param_4);
      uVar3 = (ulonglong)uVar1;
      if ((uVar1 == 0) && ((int *)param_1[3] != (int *)0x0)) {
        FUN_1800e3db8((longlong)param_4,(int *)param_1[3],(TypeDescriptor *)param_1[1],pTVar4);
      }
    }
  }
  return uVar3;
}


// FUN_1800cd650 @ 1800cd650

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 * FUN_1800cd650(longlong param_1,longlong *param_2,longlong *param_3,longlong param_4)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  uint uVar3;
  undefined8 uVar4;
  undefined2 *puVar5;
  undefined2 uVar6;
  ulonglong uVar7;
  longlong lVar8;
  size_t _Size;
  longlong lVar9;
  undefined2 *puVar10;
  ulonglong uVar11;
  size_t sVar12;
  longlong lVar13;
  undefined1 auStack_388 [48];
  undefined1 local_358 [784];
  ulonglong local_48;
  
  local_48 = DAT_1801c0240 ^ (ulonglong)auStack_388;
  puVar10 = (undefined2 *)0x0;
  if ((((param_2 == (longlong *)0x0) || (param_3 == (longlong *)0x0)) || (param_4 == 0)) ||
     (param_2 != param_3)) {
    puVar10 = (undefined2 *)0x80070057;
  }
  else {
    *(undefined4 *)(param_2 + 100) = *(undefined4 *)(*(longlong *)(param_4 + 0x18) + 4);
    if (_DAT_180193f28 < (double)(float)(*(uint **)(param_4 + 0x18))[1]) {
      sVar12 = 0xffffffffffffffff;
      lVar13 = *(longlong *)
                (*(longlong *)(*(longlong *)(param_1 + 8) + 0x80) +
                (ulonglong)**(uint **)(param_4 + 0x18) * 8);
      lVar9 = -1;
      do {
        lVar8 = lVar9;
        lVar9 = lVar8 + 1;
      } while (*(short *)(lVar13 + lVar9 * 2) != 0);
      uVar11 = lVar8 + 2;
      uVar7 = 2;
      uVar4 = FUN_180009930(2,uVar11);
      if ((int)uVar4 != 0) {
        auVar1._8_8_ = 0;
        auVar1._0_8_ = uVar7 & 0xffffffff;
        auVar2._8_8_ = 0;
        auVar2._0_8_ = uVar11;
        _Size = SUB168(auVar1 * auVar2,0);
        if (SUB168(auVar1 * auVar2,8) != 0) {
          _Size = sVar12;
        }
        puVar5 = (undefined2 *)thunk_FUN_18007ca58(_Size);
        if (puVar5 != (undefined2 *)0x0) {
          memset(puVar5,0,_Size);
          puVar10 = puVar5;
        }
        if (puVar10 != (undefined2 *)0x0) {
          if (lVar9 != 0) {
            lVar13 = lVar13 - (longlong)puVar10;
            puVar5 = puVar10;
            lVar8 = lVar9;
            do {
              if (*(short *)(lVar13 + (longlong)puVar5) == 0x25) {
                uVar6 = 0x20;
              }
              else {
                uVar6 = *(undefined2 *)(lVar13 + (longlong)puVar5);
              }
              *puVar5 = uVar6;
              puVar5 = puVar5 + 1;
              lVar8 = lVar8 + -1;
            } while (lVar8 != 0);
          }
          puVar10[lVar9] = 0;
          memset(local_358,0,0x302);
          uVar3 = (**(code **)(**(longlong **)(param_1 + 0x40) + 0xf0))
                            (*(longlong **)(param_1 + 0x40),puVar10,local_358,0x181);
          if (-1 < (int)uVar3) {
            uVar3 = (**(code **)(*param_2 + 0x88))(param_2,local_358,0x16);
          }
          _o_free(puVar10);
          return (undefined2 *)(ulonglong)uVar3;
        }
      }
      puVar10 = (undefined2 *)0x8007000e;
    }
  }
  return puVar10;
}


// FUN_1800cbb00 @ 1800cbb00

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

void FUN_1800cbb00(longlong param_1,longlong param_2)

{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  puVar1 = (undefined8 *)**(undefined8 **)(param_2 + 0x20);
  plVar2 = (longlong *)*puVar1;
  do {
    plVar4 = plVar2;
    plVar2 = (longlong *)(**(code **)(*plVar4 + 0x18))(plVar4);
  } while (plVar2 != (longlong *)0x0);
  plVar2 = (longlong *)*puVar1;
  do {
    plVar3 = plVar2;
    plVar2 = (longlong *)(**(code **)(*plVar3 + 0x10))(plVar3);
  } while (plVar2 != (longlong *)0x0);
  FUN_1800e43f0(*(longlong **)(param_1 + 0x10),puVar1,plVar4,plVar3);
  return;
}


