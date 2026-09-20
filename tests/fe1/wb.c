// FUN_180076454 @ 180076454

undefined8
FUN_180076454(longlong param_1,longlong param_2,ulonglong param_3,ulonglong *param_4,int param_5)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong lVar8;
  ulonglong uVar9;
  ulonglong local_48 [2];
  
  lVar8 = *(longlong *)(param_1 + 8);
  if (lVar8 == 0) {
    return 0x80048011;
  }
  lVar5 = *(longlong *)(lVar8 + 0x60);
  lVar2 = *(longlong *)(lVar8 + 0x68);
  lVar1 = *(longlong *)(lVar8 + 0x50);
  lVar8 = *(longlong *)(lVar8 + 0x58);
  lVar7 = lVar5 - DAT_180189548;
  if (lVar7 == 0) {
    lVar7 = lVar2 - DAT_180189550;
  }
  if (lVar7 != 0) {
    lVar7 = lVar5 - DAT_180189568;
    if (lVar7 == 0) {
      lVar7 = lVar2 - DAT_180189570;
    }
    if (lVar7 != 0) {
      lVar8 = lVar5 - DAT_180189278;
      if (lVar8 == 0) {
        lVar8 = lVar2 - DAT_180189280;
      }
      if (lVar8 != 0) {
        lVar5 = lVar5 - DAT_180189558;
        if (lVar5 == 0) {
          lVar5 = lVar2 - DAT_180189560;
        }
        if (lVar5 != 0) {
          return 1;
        }
      }
      if (lVar1 == 0) {
        return 1;
      }
      local_48[0] = 0;
      iVar3 = FUN_18002c550(lVar1,param_2,param_3,local_48);
      uVar9 = local_48[0];
      if (iVar3 == -1) {
        return 1;
      }
      if (local_48[0] != param_3) {
        uVar4 = FUN_18004d024(param_2,param_3,local_48[0] & 0xffffffff,(undefined4 *)0x0);
        uVar6 = FUN_180050e54(param_1,uVar4);
        if ((int)uVar6 == 0) {
          uVar4 = FUN_18004d024(param_2,param_3,(ulonglong)((int)uVar9 - 1),(undefined4 *)0x0);
          uVar6 = FUN_180050e54(param_1,uVar4);
          if ((int)uVar6 == 0) {
            return 1;
          }
        }
      }
      goto LAB_18007658c;
    }
  }
  if (lVar1 != 0) {
    local_48[0] = 0;
    iVar3 = FUN_18002c550(lVar1,param_2,param_3,local_48);
    uVar9 = local_48[0];
    if ((iVar3 != -1) && ((local_48[0] != param_3 || (param_5 == 0)))) {
      uVar4 = FUN_18004d024(param_2,param_3,local_48[0] & 0xffffffff,(undefined4 *)0x0);
      uVar6 = FUN_180050e54(param_1,uVar4);
      if ((int)uVar6 == 0) {
        uVar4 = FUN_18004d024(param_2,param_3,(ulonglong)((int)uVar9 - 1),(undefined4 *)0x0);
        uVar6 = FUN_180050e54(param_1,uVar4);
        if ((int)uVar6 == 0) goto LAB_180076611;
      }
LAB_18007658c:
      if (param_4 == (ulonglong *)0x0) {
        return 0;
      }
      *param_4 = uVar9;
      return 0;
    }
  }
LAB_180076611:
  if (lVar8 == 0) {
    return 1;
  }
  local_48[0] = 0;
  iVar3 = FUN_18002c550(lVar8,param_2,param_3,local_48);
  if (iVar3 != -1) {
    if (local_48[0] == param_3) {
      if (param_4 != (ulonglong *)0x0) {
        *param_4 = local_48[0];
      }
      return 0;
    }
    return 1;
  }
  return 1;
}


// FUN_18007a588 @ 18007a588

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

undefined4
FUN_18007a588(undefined8 param_1,undefined8 param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined4 uVar1;
  
  if (param_3 < 0x100000000) {
    uVar1 = 0;
    if ((int)param_3 != 0) {
      uVar1 = (**(code **)*param_4)(param_4,param_2,(int)param_3,0,0);
    }
  }
  else {
    uVar1 = 0x80070216;
  }
  return uVar1;
}


// FUN_180043ee8 @ 180043ee8

int FUN_180043ee8(longlong param_1,ushort *param_2,ulonglong param_3,undefined8 *param_4)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  uint *puVar6;
  ushort *puVar7;
  ulonglong uVar8;
  int iVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  ulonglong uVar12;
  uint uVar13;
  uint local_38 [4];
  
  iVar2 = 0;
  uVar8 = 1;
  lVar4 = param_1;
  if (*(char *)(param_1 + 0x10) == '\t') {
    iVar9 = 1;
    iVar2 = 1;
    if ((((1 < param_3) &&
         (puVar11 = param_4, uVar3 = FUN_1800442c8(*param_2), iVar2 = iVar9, (int)uVar3 == 0)) &&
        (uVar3 = FUN_1800442c8(param_2[param_3 - 1]), (int)uVar3 != 0)) &&
       ((param_2[param_3 - 2] - 0x53 & 0xffdf) == 0)) {
      iVar2 = FUN_18007a588(0xffdf,param_2,param_3,puVar11);
      if (-1 < iVar2) {
        return 0;
      }
      uVar8 = 1;
      lVar4 = param_1;
    }
    if (iVar2 < (int)uVar8) {
      return iVar2;
    }
  }
  puVar7 = param_2 + (param_3 - 1);
  if ((param_2 == (ushort *)0x0) || (param_3 == 0)) {
    uVar13 = 0;
    local_38[0] = 0;
    uVar10 = uVar8 & 0xffffffff;
    uVar12 = uVar8 & 0xffffffff;
    uVar1 = 0;
    if (param_2 == (ushort *)0x0) goto LAB_180044084;
  }
  else if (((uVar8 < param_3) && ((ushort)(*param_2 + 0x2800) < 0x400)) &&
          ((ushort)(param_2[1] + 0x2400) < 0x400)) {
    uVar12 = 2;
    uVar1 = CONCAT22(*param_2,param_2[1]);
  }
  else {
    uVar12 = uVar8 & 0xffffffff;
    uVar1 = (uint)*param_2;
  }
  local_38[0] = uVar1;
  uVar10 = uVar8 & 0xffffffff;
  uVar5 = param_3 - 1;
  uVar13 = 0;
  if (uVar5 < param_3) {
    if (((uVar5 == 0) || (0x3ff < (ushort)(param_2[param_3 - 2] + 0x2800))) ||
       (0x3ff < (ushort)(param_2[uVar5] + 0x2400))) {
      uVar13 = (uint)param_2[uVar5];
      uVar10 = uVar8 & 0xffffffff;
    }
    else {
      puVar7 = param_2 + (param_3 - 2);
      uVar13 = CONCAT22(param_2[param_3 - 2],param_2[uVar5]);
      uVar10 = 2;
    }
  }
LAB_180044084:
  if (param_2 <= puVar7) {
    puVar6 = local_38;
    lVar4 = _o_bsearch(puVar6,*(undefined8 *)(*(longlong *)(lVar4 + 8) + 0x48),
                       *(undefined4 *)(*(longlong *)(lVar4 + 8) + 0x40),4,FUN_180049ff0);
    if (lVar4 != 0) {
      iVar2 = FUN_18007a588(puVar6,param_2,uVar12,param_4);
      param_2 = param_2 + uVar12;
    }
  }
  if ((-1 < iVar2) && (param_2 <= puVar7)) {
    puVar6 = local_38;
    uVar8 = (longlong)puVar7 - (longlong)param_2 >> 1;
    local_38[0] = uVar13;
    lVar4 = _o_bsearch(puVar6,*(undefined8 *)(*(longlong *)(param_1 + 8) + 0x48),
                       *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x40),4,FUN_180049ff0);
    if (lVar4 == 0) {
      uVar10 = uVar10 + uVar8;
      puVar7 = param_2;
    }
    else {
      iVar2 = FUN_18007a588(puVar6,param_2,uVar8,param_4);
      if (iVar2 < 0) {
        return iVar2;
      }
    }
    iVar2 = FUN_18007a588(puVar6,puVar7,uVar10,param_4);
  }
  return iVar2;
}


// FUN_180044194 @ 180044194

ushort * FUN_180044194(longlong param_1,ushort *param_2,longlong param_3)

{
  ushort *puVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  longlong lVar6;
  uint local_res10 [2];
  uint local_res18 [4];
  
  puVar1 = param_2 + param_3;
  lVar6 = 1;
  while( true ) {
    if (puVar1 <= param_2) {
      return (ushort *)0x0;
    }
    uVar5 = 0;
    uVar2 = (longlong)puVar1 - (longlong)param_2 >> 1;
    lVar4 = lVar6;
    if ((param_2 != (ushort *)0x0) && (uVar2 != 0)) {
      if ((uVar2 < 2) ||
         ((0x3ff < (ushort)(*param_2 + 0x2800) || (0x3ff < (ushort)(param_2[1] + 0x2400))))) {
        uVar5 = (uint)*param_2;
      }
      else {
        lVar4 = 2;
        uVar5 = CONCAT22(*param_2,param_2[1]);
      }
    }
    local_res10[0] = uVar5;
    lVar3 = _o_bsearch(local_res10,*(undefined8 *)(*(longlong *)(param_1 + 8) + 0x28),
                       *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x20),4,FUN_180049ff0);
    if (lVar3 != 0) break;
    local_res18[0] = uVar5;
    lVar3 = _o_bsearch(local_res18,*(undefined8 *)(*(longlong *)(param_1 + 8) + 0x38),
                       *(undefined4 *)(*(longlong *)(param_1 + 8) + 0x30),4,FUN_180049ff0);
    if (lVar3 != 0) {
      return param_2;
    }
    param_2 = param_2 + lVar4;
  }
  return param_2;
}


// FUN_18011c420 @ 18011c420

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_18011c420(longlong param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4,
                       longlong *param_5)

{
  longlong *plVar1;
  uint uVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined8 *local_18 [2];
  
  puVar3 = (undefined8 *)FUN_18007ca58(0x60);
  if (puVar3 != (undefined8 *)0x0) {
    puVar3[1] = 0;
    *(undefined4 *)(puVar3 + 5) = 0;
    puVar3[6] = 0;
    *(undefined2 *)(puVar3 + 7) = 0xffff;
    *puVar3 = CWordBreakingInfo::vftable;
    puVar3[2] = param_2;
    *(undefined4 *)(puVar3 + 3) = param_3;
    puVar3[4] = param_4;
    puVar3[8] = 0;
    puVar3[9] = 0;
    puVar3[10] = 0;
    *(undefined4 *)(puVar3 + 0xb) = 0;
    if (puVar3 != (undefined8 *)0x0) {
      local_18[0] = puVar3;
      uVar4 = FUN_18004c0c4((longlong *)(param_1 + 8),local_18);
      uVar5 = uVar4 & 0xffffffff;
      if ((int)uVar4 < 0) {
        (**(code **)*puVar3)(puVar3,1);
        return uVar5;
      }
      if (param_5 == (longlong *)0x0) {
        return uVar5;
      }
      uVar4 = 0;
      if (param_5[1] == 0) {
        return uVar5;
      }
      do {
        local_18[0] = (undefined8 *)0x0;
        plVar1 = *(longlong **)(*param_5 + uVar4 * 8);
        uVar2 = (**(code **)(*plVar1 + 0x228))(plVar1,local_18);
        uVar5 = (ulonglong)uVar2;
        if (-1 < (int)uVar2) {
          uVar5 = FUN_18009071c(puVar3 + 8,local_18);
          uVar5 = uVar5 & 0xffffffff;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < (ulonglong)param_5[1]);
      return uVar5;
    }
  }
  return 0x8007000e;
}


// FUN_180049ff0 @ 180049ff0

int FUN_180049ff0(uint *param_1,uint *param_2)

{
  if (*param_2 < *param_1) {
    return 1;
  }
  return -(uint)(*param_1 != *param_2);
}


