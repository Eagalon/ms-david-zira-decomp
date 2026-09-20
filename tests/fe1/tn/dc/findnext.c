// FUN_180061910 @ 180061910

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_180061910(longlong param_1,longlong param_2,uint param_3,longlong param_4,
                       uint *param_5,uint *param_6,uint *param_7,undefined2 *param_8)

{
  short sVar1;
  short sVar2;
  longlong *plVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  UINT UVar8;
  short *psVar9;
  longlong lVar10;
  ulonglong uVar11;
  uint *puVar12;
  undefined ***pppuVar13;
  LPCWSTR pWVar14;
  uint uVar15;
  ulonglong uVar16;
  uint uVar17;
  undefined8 uVar18;
  uint *puVar19;
  uint uVar20;
  uint *local_res10;
  uint local_res18;
  longlong local_res20;
  uint local_98;
  uint local_94;
  undefined4 local_90;
  uint local_8c;
  ulonglong *local_88;
  undefined8 local_80;
  undefined8 *local_78;
  longlong *local_70;
  undefined **local_68;
  LPCWSTR local_60;
  undefined8 uStack_58;
  undefined8 local_50;
  
  if ((param_2 == 0) || (param_3 == 0)) {
    return 0x80070057;
  }
  if (*(longlong *)(param_1 + 8) == 0) {
    return 0x80048011;
  }
  local_res10 = (uint *)0x0;
  local_68 = CTTSString::vftable;
  local_60 = (LPCWSTR)0x0;
  uStack_58 = 0;
  local_50 = 0;
  local_res18 = param_3;
  local_res20 = param_4;
  psVar9 = FUN_180029d20((longlong)&local_68,param_2,(ulonglong)param_3);
  uVar16 = (ulonglong)psVar9 & 0xffffffff;
  puVar19 = (uint *)0x0;
  if (-1 < (int)psVar9) {
    lVar10 = FUN_18001b0e0((longlong)&local_68);
    if ((char)lVar10 != '\0') {
      FUN_18001d780(&local_68);
      return 1;
    }
    lVar10 = *(longlong *)(param_1 + 8);
    uVar4 = (**(code **)(**(longlong **)(param_1 + 0x20) + 0x38))();
    uVar18 = *(undefined8 *)(param_1 + 0x10);
    psVar9 = FUN_18001c490((longlong)&local_68);
    uVar5 = FUN_180138e18(lVar10,(longlong)psVar9,0,&local_res10,uVar18,uVar4);
    uVar16 = (ulonglong)uVar5;
    puVar19 = local_res10;
  }
  uVar5 = 0;
  local_80 = (BSTR)((ulonglong)local_80._4_4_ << 0x20);
  uVar20 = 0;
  local_94 = 0;
  local_8c = 0;
  uVar15 = uVar5;
  if ((int)uVar16 < 0) {
    local_94 = 0;
    uVar20 = uVar5;
    uVar17 = local_94;
    if ((int)uVar16 != -0x7ffb7fe7) goto LAB_180061be4;
  }
  else {
    if (puVar19 != (uint *)0x0) {
      uVar20 = (uint)(ushort)puVar19[6];
      local_94 = (uint)(ushort)puVar19[6];
    }
    uVar16 = 0x80048019;
  }
  uVar17 = uVar20;
  if ((((local_res20 == 0) && (lVar10 = *(longlong *)(param_1 + 0x28), lVar10 != 0)) &&
      (uVar15 = 0, *(longlong *)(lVar10 + 0x38) != 0)) && (*(longlong *)(lVar10 + 0x48) != 0)) {
    local_res10 = (uint *)((ulonglong)local_res10 & 0xffffffff00000000);
    local_98 = 0;
    local_90 = 1;
    local_94 = uVar20;
    uVar20 = uVar5;
    do {
      local_88 = (ulonglong *)0x0;
      if ((local_60 == (LPCWSTR)0x0) || (pWVar14 = local_60, *local_60 == L'\0')) {
        pWVar14 = (LPCWSTR)0x0;
      }
      puVar12 = *(uint **)(param_1 + 0x28);
      uVar11 = FUN_180075900((longlong)puVar12,pWVar14,&local_88);
      uVar16 = uVar11 & 0xffffffff;
      if ((int)uVar11 < 0) goto LAB_180061bc9;
      uVar11 = FUN_180061f08(puVar12,local_88,(undefined4 *)&local_res10,&local_98,
                             (longlong *)param_7,param_8,&local_90);
      uVar15 = local_98;
      uVar16 = uVar11 & 0xffffffff;
      if ((int)uVar11 < 0) goto LAB_180061bc9;
      if (local_90 == 0) {
        puVar12 = param_7;
        FUN_180019d20((longlong)param_7);
        *param_8 = 0xffff;
        uVar16 = 0x80048019;
        goto LAB_180061bc9;
      }
      if (local_98 == 0) goto LAB_180061bc9;
      iVar7 = (int)local_res10;
      uVar11 = (ulonglong)local_res10 & 0xffffffff;
      sVar1 = (short)local_res10;
      sVar2 = (short)uVar20;
      iVar6 = FUN_180062154((longlong)puVar19,sVar1 + sVar2);
      uVar17 = local_res18;
      if ((iVar6 != 0) &&
         (iVar6 = FUN_180139508((longlong)puVar19,(short)uVar15 + sVar2 + sVar1),
         uVar17 = local_res18, iVar6 != 0)) {
        if (param_5 != (uint *)0x0) {
          *param_5 = iVar7 + uVar20;
        }
        puVar12 = param_5;
        uVar5 = 1;
        if (param_6 != (uint *)0x0) {
          *param_6 = uVar15;
          uVar5 = 1;
        }
        goto LAB_180061bc9;
      }
      do {
        uVar5 = (int)uVar11 + 1;
        uVar11 = (ulonglong)uVar5;
        puVar12 = puVar19;
        iVar7 = FUN_180062154((longlong)puVar19,(short)uVar5 + sVar2);
        if (iVar7 != 0) break;
      } while (uVar5 + uVar20 < uVar17);
      local_res10 = (uint *)CONCAT44(local_res10._4_4_,uVar5);
      uVar20 = uVar20 + uVar5;
      uVar5 = (uint)local_80;
      if (uVar17 <= uVar20) goto LAB_180061ba2;
      pppuVar13 = &local_68;
      FUN_18007ac40((longlong)pppuVar13,local_60 + uVar11);
      FUN_18007ac98(pppuVar13,(longlong *)local_88);
    } while( true );
  }
  goto LAB_180061be4;
LAB_180061ba2:
  if (param_7 != (uint *)0x0) {
    puVar12 = param_7;
    FUN_180019d20((longlong)param_7);
  }
LAB_180061bc9:
  FUN_18007ac98(puVar12,(longlong *)local_88);
  uVar17 = local_94;
  uVar15 = uVar5;
LAB_180061be4:
  uVar11 = 0;
  local_78 = (undefined8 *)0x0;
  uVar5 = local_8c;
  if ((int)uVar16 == -0x7ffb7fe7) {
    do {
      if ((uVar15 != 0) || ((ushort)uVar17 <= (ushort)uVar5)) break;
      local_res10 = (uint *)((ulonglong)local_res10 & 0xffffffffffff0000);
      uVar20 = (**(code **)(**(longlong **)(param_1 + 8) + 0x10))
                         (*(longlong **)(param_1 + 8),puVar19,uVar5 & 0xffff,
                          (local_res20 != 0) + '\x01',local_res20,&local_78,&local_res10);
      uVar11 = (ulonglong)uVar20;
      if (-1 < (int)uVar20) {
        uVar16 = (ulonglong)local_res10 & 0xffff;
        if (((ushort)local_res10 != 0) && (local_78 != (undefined8 *)0x0)) {
          uVar15 = 1;
          if (param_5 != (uint *)0x0) {
            *param_5 = uVar5 & 0xffff;
          }
          if (param_6 != (uint *)0x0) {
            *param_6 = (uint)(ushort)local_res10;
          }
          local_70 = (longlong *)0x0;
          uVar5 = FUN_1800b6e90(&local_70);
          plVar3 = local_70;
          uVar11 = (ulonglong)uVar5;
          if (-1 < (int)uVar5) {
            uVar5 = (**(code **)(*local_70 + 0xe8))
                              (local_70,*(undefined2 *)(*(longlong *)(param_1 + 8) + 8));
            uVar11 = (ulonglong)uVar5;
            if (-1 < (int)uVar5) {
              uVar5 = (**(code **)(*plVar3 + 0xc0))(plVar3,local_78);
              uVar11 = (ulonglong)uVar5;
              if (-1 < (int)uVar5) {
                uVar5 = (**(code **)(*plVar3 + 0xb8))(plVar3,1);
                uVar11 = (ulonglong)uVar5;
              }
            }
          }
          local_88 = (ulonglong *)0x0;
          if ((int)uVar11 < 0) {
LAB_180061ed3:
            if ((int)uVar11 == -0x7ffbeffc) {
              uVar11 = 0;
              uVar15 = 0;
            }
          }
          else {
            uVar5 = (**(code **)(*plVar3 + 0x20))(plVar3,&local_88);
            uVar11 = (ulonglong)uVar5;
            if ((int)uVar5 < 0) goto LAB_180061ed3;
            local_80 = (BSTR)0x0;
            uVar5 = (**(code **)(*local_88 + 0x30))(local_88,&local_80);
            uVar11 = (ulonglong)uVar5;
            if (((-1 < (int)uVar5) && (UVar8 = SysStringLen(local_80), uVar15 = 0, UVar8 != 0)) &&
               (uVar15 = 1, param_7 != (uint *)0x0)) {
              uVar5 = (**(code **)(*(longlong *)param_7 + 8))(param_7,local_80);
              uVar11 = (ulonglong)uVar5;
            }
            SysFreeString(local_80);
            if (((-1 < (int)uVar11) && (uVar15 != 0)) && (param_8 != (undefined2 *)0x0)) {
              local_98 = 0;
              uVar5 = (**(code **)(*local_88 + 0x20))(local_88,&local_98);
              uVar11 = (ulonglong)uVar5;
              uVar5 = 0;
              while( true ) {
                if (((int)uVar11 < 0) || (local_98 <= uVar5)) goto LAB_180061e10;
                local_90 = 0;
                uVar20 = (**(code **)(*local_88 + 0x28))(local_88,uVar5,&local_90);
                uVar11 = (ulonglong)uVar20;
                if ((-1 < (int)uVar20) && ((short)local_90 == *(short *)(param_1 + 0x18))) break;
                uVar5 = uVar5 + 1;
              }
              *param_8 = local_90._2_2_;
            }
          }
LAB_180061e10:
          FUN_18001ea48((longlong *)&local_88);
          FUN_18001ea48((longlong *)&local_70);
          uVar5 = local_8c;
          if (((int)uVar11 < 0) || (uVar15 != 0)) goto LAB_180061e54;
          uVar16 = (ulonglong)local_res10 & 0xffff;
        }
        local_8c = (**(code **)(*(longlong *)puVar19 + 8))(puVar19,uVar5 & 0xffff,uVar16);
        uVar5 = local_8c;
      }
LAB_180061e54:
      if (local_78 != (undefined8 *)0x0) {
        (**(code **)*local_78)(local_78,1);
        local_78 = (undefined8 *)0x0;
      }
      uVar17 = local_94;
    } while (-1 < (int)uVar11);
    uVar16 = uVar11;
    if (local_78 != (undefined8 *)0x0) {
      (**(code **)*local_78)(local_78,1);
      local_78 = (undefined8 *)0x0;
    }
  }
  if (-1 < (int)uVar16) {
    uVar16 = (ulonglong)(uVar15 == 0);
  }
  if (puVar19 != (uint *)0x0) {
    (*(code *)**(undefined8 **)puVar19)(puVar19,1);
  }
  FUN_18001d780(&local_68);
  return uVar16;
}


