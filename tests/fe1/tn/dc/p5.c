// FUN_18006565c @ 18006565c

ulonglong *
FUN_18006565c(longlong param_1,ulonglong *param_2,undefined8 *param_3,ushort param_4,
             undefined8 *param_5,ushort *param_6,ushort *param_7,longlong param_8)

{
  ushort *puVar1;
  undefined1 auVar2 [16];
  longlong lVar3;
  undefined8 *puVar4;
  void *pvVar5;
  ulonglong uVar6;
  ulonglong *_Dst;
  ulonglong *puVar7;
  ulonglong *puVar8;
  ushort *puVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  ushort uVar12;
  ushort uVar14;
  ulonglong *local_res10;
  undefined8 *local_res18;
  ushort local_res20;
  ushort local_58;
  ulonglong *puVar13;
  
  puVar7 = (ulonglong *)0x0;
  *param_5 = 0;
  uVar14 = 0;
  *param_6 = 0;
  uVar10 = 0xffff;
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  if (param_4 != 0) {
    uVar11 = (ulonglong)param_4;
    do {
      puVar9 = (ushort *)*param_3;
      if ((((*param_7 <= puVar9[1]) &&
           (lVar3 = FUN_18000f1f0((short *)param_7,puVar9[1]), lVar3 != 0)) &&
          (*(int *)(puVar9 + 6) == 0)) && ((short)uVar10 == *(short *)(lVar3 + 4))) {
        lVar3 = FUN_18003aa40(*(longlong *)(*(longlong *)(param_1 + 0x18) + 0xb8),
                              *(uint *)(*(longlong *)
                                         (*(longlong *)(*(longlong *)(param_1 + 0x18) + 0x40) +
                                         (ulonglong)*puVar9 * 8) + 0x14));
        uVar10 = 0xffff;
        if (lVar3 != 0) {
          uVar14 = uVar14 + 1;
        }
      }
      param_3 = param_3 + 1;
      uVar11 = uVar11 - 1;
    } while (uVar11 != 0);
  }
  puVar4 = local_res18;
  _Dst = puVar7;
  puVar8 = puVar7;
  if (uVar14 != 0) {
    uVar6 = CONCAT62(0,uVar14);
    auVar2._8_8_ = 0;
    auVar2._0_8_ = uVar6;
    uVar11 = SUB168(ZEXT816(0x20) * auVar2,0);
    if (SUB168(ZEXT816(0x20) * auVar2,8) != 0) {
      uVar11 = 0xffffffffffffffff;
    }
    lVar3 = uVar11 + 8;
    if (0xfffffffffffffff7 < uVar11) {
      lVar3 = -1;
    }
    local_res10 = (ulonglong *)thunk_FUN_18007ca58(lVar3);
    if (local_res10 != (ulonglong *)0x0) {
      *local_res10 = uVar6;
      _Dst = local_res10 + 1;
      FUN_180084c3c((longlong)_Dst,0x20,(ulonglong)uVar14,FUN_18013faf0);
    }
    if (_Dst == (ulonglong *)0x0) {
      puVar8 = (ulonglong *)0x8007000e;
    }
    else {
      memset(_Dst,0,uVar6 << 5);
      local_58 = 0;
      puVar8 = (ulonglong *)0x0;
      puVar13 = puVar7;
      if (param_4 != 0) {
        do {
          puVar9 = (ushort *)0x0;
          puVar8 = puVar7;
          if ((int)puVar7 < 0) break;
          puVar1 = (ushort *)puVar4[(longlong)puVar13];
          if (((*param_7 <= puVar1[1]) &&
              (lVar3 = FUN_18000f1f0((short *)param_7,puVar1[1]), lVar3 != 0)) &&
             ((*(int *)(puVar1 + 6) == 0 &&
              ((*(short *)(lVar3 + 4) == -1 &&
               (uVar11 = FUN_18003aa40(*(longlong *)(*(longlong *)(param_1 + 0x18) + 0xb8),
                                       *(uint *)(*(longlong *)
                                                  (*(longlong *)
                                                    (*(longlong *)(param_1 + 0x18) + 0x40) +
                                                  (ulonglong)*puVar1 * 8) + 0x14)),
               puVar4 = local_res18, uVar11 != 0)))))) {
            local_res10 = (ulonglong *)((ulonglong)local_res10 & 0xffffffffffff0000);
            puVar4 = (undefined8 *)thunk_FUN_18007ca58(200);
            if (puVar4 != (undefined8 *)0x0) {
              *puVar4 = 8;
              puVar9 = (ushort *)(puVar4 + 1);
              FUN_180084c3c((longlong)puVar9,0x18,8,FUN_18013fab0);
            }
            puVar4 = local_res18;
            if (puVar9 != (ushort *)0x0) {
              pvVar5 = FUN_180136b94(param_1,(longlong)puVar1,8,puVar9,(ushort *)&local_res10,
                                     param_7,param_8);
              puVar7 = (ulonglong *)((ulonglong)pvVar5 & 0xffffffff);
              if ((int)pvVar5 < 0) {
                FUN_180135c80((longlong)puVar9);
                puVar4 = local_res18;
              }
              else {
                uVar6 = (ulonglong)local_58;
                _Dst[uVar6 * 4 + 1] = uVar11;
                *(ushort *)(_Dst + uVar6 * 4) = puVar1[0x1e];
                *(undefined2 *)(_Dst + uVar6 * 4 + 2) = local_res10._0_2_;
                _Dst[uVar6 * 4 + 3] = (ulonglong)puVar9;
                local_58 = local_58 + 1;
                puVar4 = local_res18;
              }
            }
          }
          uVar12 = (short)puVar13 + 1;
          puVar13 = (ulonglong *)(ulonglong)uVar12;
          puVar8 = puVar7;
        } while (uVar12 < local_res20);
      }
    }
  }
  *param_5 = _Dst;
  *param_6 = uVar14;
  return puVar8;
}


// FUN_1801374f8 @ 1801374f8

ulonglong FUN_1801374f8(longlong param_1,ushort *param_2,undefined8 *param_3,longlong param_4,
                       int param_5)

{
  longlong *plVar1;
  void *_Dst;
  ulonglong uVar2;
  undefined8 *puVar3;
  longlong lVar4;
  
  if (param_5 == 0) {
LAB_1801375d1:
    uVar2 = FUN_1800433c8(param_1,param_2,param_3,param_4,0xffff,0);
  }
  else {
    *(undefined2 *)((longlong)param_3 + 0x34) = 0xffff;
    *(undefined4 *)(param_3 + 1) = 2;
    *(undefined2 *)(param_3 + 5) = 2;
    *(ushort *)((longlong)param_3 + 0x72) = param_2[2];
    *(ushort *)((longlong)param_3 + 0x74) = param_2[3];
    _Dst = (void *)thunk_FUN_18007ca58(0x10);
    plVar1 = param_3 + 2;
    *plVar1 = (longlong)_Dst;
    if (_Dst != (void *)0x0) {
      memset(_Dst,0,(ulonglong)*(ushort *)(param_3 + 5) << 3);
      lVar4 = 0;
      do {
        *(undefined8 *)(lVar4 + *plVar1) = 0;
        lVar4 = lVar4 + 8;
      } while (lVar4 < 0x10);
      puVar3 = (undefined8 *)FUN_18007ca58(0xb8);
      if (puVar3 != (undefined8 *)0x0) {
        param_3 = FUN_18013dd18(puVar3);
        if (param_3 != (undefined8 *)0x0) {
          *(undefined8 **)*plVar1 = param_3;
          goto LAB_1801375d1;
        }
      }
    }
    uVar2 = 0x8007000e;
  }
  return uVar2;
}


// FUN_180136288 @ 180136288

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined8
FUN_180136288(undefined8 param_1,longlong param_2,ushort param_3,ushort param_4,longlong *param_5)

{
  int iVar1;
  undefined2 *puVar2;
  undefined8 *puVar3;
  void *_Dst;
  void *_Src;
  longlong lVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  bool bVar8;
  
  if (((param_5 != (longlong *)0x0) && (*param_5 != 0)) && (param_2 != 0)) {
    uVar5 = (uint)param_3 + (uint)param_4;
    uVar6 = (uint)*(ushort *)(param_2 + 0x18);
    bVar7 = uVar5 < uVar6;
    if (uVar5 <= uVar6) {
      bVar8 = false;
      if (param_3 != 0) {
        puVar2 = (undefined2 *)FUN_1800479c0(param_2,param_3 - 1);
        iVar1 = _o_iswspace(*puVar2);
        bVar8 = iVar1 == 0;
      }
      if (uVar5 < uVar6) {
        puVar2 = (undefined2 *)FUN_1800479c0(param_2,param_4 + param_3);
        iVar1 = _o_iswspace(*puVar2);
        bVar7 = iVar1 == 0;
      }
      puVar3 = (undefined8 *)FUN_18007ca58(0xb8);
      if ((puVar3 != (undefined8 *)0x0) &&
         (puVar3 = FUN_18013dd18(puVar3), puVar3 != (undefined8 *)0x0)) {
        *(undefined4 *)(puVar3 + 1) = 0;
        *(ushort *)((longlong)puVar3 + 0x72) = param_3;
        *(ushort *)((longlong)puVar3 + 0x74) = param_4 + param_3;
        _Dst = (void *)_o_malloc((param_4 + 1) * 2);
        puVar3[4] = _Dst;
        if (_Dst != (void *)0x0) {
          _Src = (void *)FUN_1800479c0(param_2,param_3);
          memcpy(_Dst,_Src,(ulonglong)param_4 * 2);
          *(undefined2 *)((ulonglong)param_4 * 2 + puVar3[4]) = 0;
          if (puVar3[4] == 0) {
            lVar4 = 0;
          }
          else {
            lVar4 = -1;
            do {
              lVar4 = lVar4 + 1;
            } while (*(short *)(puVar3[4] + lVar4 * 2) != 0);
          }
          *(undefined2 *)((longlong)puVar3 + 0x2a) = 0xffff;
          *(short *)(puVar3 + 5) = (short)lVar4;
          if (bVar8) {
            *(uint *)(puVar3 + 3) = (uint)bVar7 * 2 + 1;
          }
          else if (bVar7 != 0) {
            *(undefined4 *)(puVar3 + 3) = 2;
          }
          *(undefined8 **)
           (*(longlong *)(*param_5 + 0x10) + -8 + (ulonglong)*(ushort *)(*param_5 + 0x28) * 8) =
               puVar3;
          return 0;
        }
        (**(code **)*puVar3)(puVar3,1);
        return 0x8007000e;
      }
      return 0x8007000e;
    }
  }
  return 0x80070057;
}


