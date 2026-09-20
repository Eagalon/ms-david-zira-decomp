// FUN_180062900 @ 180062900

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_180062900(longlong param_1,ulonglong param_2,undefined4 param_3,longlong param_4,
                 longlong *param_5)

{
  ushort uVar1;
  longlong *plVar2;
  longlong *plVar3;
  int iVar4;
  ulonglong uVar5;
  ushort *puVar6;
  longlong lVar7;
  ulonglong uVar8;
  ulonglong local_res8;
  longlong local_38;
  longlong *local_30;
  
  uVar8 = 0;
  local_30 = (longlong *)0x0;
  local_res8 = local_res8 & 0xffffffff00000000;
  lVar7 = param_1 + -8;
  local_38 = 0;
  iVar4 = FUN_1800780e8(lVar7,param_2,(int *)&local_res8,&local_38);
  if (-1 < iVar4) {
    iVar4 = FUN_18006e874(lVar7,(undefined8 *)(param_1 + 0x418),0,local_38,param_2,param_3,
                          (undefined4)local_res8,param_3,*(undefined2 *)(param_1 + 8),&local_30);
    plVar3 = local_30;
    if ((-1 < iVar4) &&
       ((param_4 == 0 || (iVar4 = (**(code **)*local_30)(local_30,L"pPron",param_4), -1 < iVar4))))
    {
      if ((param_5 != (longlong *)0x0) && (param_5[1] != 0)) {
        do {
          local_res8 = 0;
          plVar2 = *(longlong **)(*param_5 + uVar8 * 8);
          iVar4 = (**(code **)(*plVar2 + 0x228))(plVar2,&local_res8);
          if (-1 < iVar4) {
            uVar5 = FUN_18009071c(plVar3 + 0x59,&local_res8);
            iVar4 = (int)uVar5;
          }
          uVar8 = uVar8 + 1;
        } while (uVar8 < (ulonglong)param_5[1]);
        if (iVar4 < 0) {
          return iVar4;
        }
      }
      puVar6 = (ushort *)(**(code **)(*plVar3 + 0x80))(plVar3);
      if (puVar6 != (ushort *)0x0) {
        uVar1 = *puVar6;
        while (uVar1 != 0) {
          if (uVar1 < 0x201d) {
            if (uVar1 == 0x201c) {
LAB_180062a96:
              *puVar6 = 0x22;
            }
            else {
              if (uVar1 != 0x2b9) {
                if (uVar1 == 0x2ba) goto LAB_180062a96;
                if (uVar1 != 700) {
                  if (uVar1 == 0x2ee) goto LAB_180062a96;
                  if ((uVar1 != 0x2018) && (uVar1 != 0x2019)) goto LAB_180062a9b;
                }
              }
LAB_180062a8f:
              *puVar6 = 0x27;
            }
          }
          else {
            if (uVar1 == 0x201d) goto LAB_180062a96;
            if (uVar1 == 0x2032) goto LAB_180062a8f;
            if ((uVar1 == 0x2033) || (uVar1 == 0xff02)) goto LAB_180062a96;
            if (uVar1 == 0xff07) goto LAB_180062a8f;
          }
LAB_180062a9b:
          puVar6 = puVar6 + 1;
          uVar1 = *puVar6;
        }
      }
    }
  }
  return iVar4;
}


// FUN_1800c4ab4 @ 1800c4ab4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

int FUN_1800c4ab4(longlong param_1,undefined8 *param_2,undefined8 param_3,longlong param_4,
                 undefined8 param_5,uint param_6,undefined4 param_7,wchar_t *param_8,
                 undefined8 *param_9,undefined2 param_10,undefined2 param_11)

{
  code *pcVar1;
  longlong *plVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong *local_38;
  undefined8 local_30 [5];
  
  if (param_8 == (wchar_t *)0x0) {
    iVar3 = -0x7ff8ffa9;
  }
  else {
    local_38 = (longlong *)0x0;
    iVar3 = FUN_18006e874((ulonglong)param_6,param_2,0,param_4,param_5,param_6,param_7,param_6,
                          param_11,&local_38);
    plVar2 = local_38;
    if ((local_38 != (longlong *)0x0) && (-1 < iVar3)) {
      iVar3 = wcscmp(param_8,L"sp:compoundWord");
      if (iVar3 != 0) {
        iVar3 = (**(code **)(*plVar2 + 0xb8))(plVar2,param_8);
        if (iVar3 < 0) goto LAB_1800c4bcd;
      }
      iVar3 = (**(code **)(*plVar2 + 0xe8))(plVar2,param_10,*(undefined8 *)(param_1 + 0x530));
      if (-1 < iVar3) {
        pcVar1 = *(code **)(*plVar2 + 0xd8);
        puVar4 = FUN_18001b878(local_30,param_9);
        iVar3 = (*pcVar1)(plVar2,puVar4);
      }
    }
  }
LAB_1800c4bcd:
  FUN_18001d780(param_9);
  return iVar3;
}


