// FUN_180018ed4 @ 180018ed4

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_180018ed4(longlong param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  code *pcVar4;
  undefined2 uVar5;
  uint uVar6;
  ulonglong uVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  undefined8 *puVar13;
  ulonglong uVar14;
  longlong *local_res10;
  undefined8 *local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 uStack_118;
  undefined4 local_110;
  undefined8 *local_108;
  undefined8 uStack_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 uStack_e8;
  undefined4 local_e0;
  undefined8 *local_d8;
  undefined8 uStack_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 uStack_b8;
  undefined4 local_b0;
  undefined8 *local_a8 [2];
  longlong local_98;
  undefined8 local_70 [9];
  
  uVar7 = FUN_180079408(param_1);
  uVar14 = uVar7 & 0xffffffff;
  if (((int)uVar7 < 0) || (*(longlong *)(param_1 + 0x4e0) == 0)) {
    return uVar14;
  }
  local_138 = (undefined8 *)0x0;
  uStack_130 = 0;
  local_128 = 0;
  local_120 = 0;
  uStack_118 = 0;
  local_110 = 10;
  local_d8 = (undefined8 *)0x0;
  uStack_d0 = 0;
  local_c8 = 0;
  local_c0 = 0;
  uStack_b8 = 0;
  local_b0 = 10;
  puVar1 = (undefined8 *)(param_1 + 0x420);
  puVar13 = (undefined8 *)*puVar1;
  while (puVar13 != (undefined8 *)0x0) {
    plVar2 = (longlong *)puVar13[2];
    puVar13 = (undefined8 *)*puVar13;
    local_res10 = plVar2;
    if (plVar2 != (longlong *)0x0) {
      lVar8 = (**(code **)(*plVar2 + 0xc0))(plVar2);
      if (lVar8 == 0) {
        puVar12 = FUN_180019234(&local_138,&local_res10);
        if (puVar12 == (undefined8 *)0x0) {
          uVar14 = 0x8007000e;
          goto LAB_1800191f5;
        }
      }
      else {
        uVar9 = (**(code **)(*plVar2 + 0x80))(plVar2);
        local_108 = (undefined8 *)0x0;
        uStack_100 = 0;
        local_f8 = 0;
        local_f0 = 0;
        uStack_e8 = 0;
        local_e0 = 10;
        uVar6 = (**(code **)(**(longlong **)(param_1 + 0x4e0) + 0x18))
                          (*(longlong **)(param_1 + 0x4e0),uVar9,lVar8,&local_108);
        uVar14 = (ulonglong)uVar6;
        if (uVar6 == 1) {
          puVar10 = FUN_180019234(&local_138,&local_res10);
          puVar12 = local_108;
          if (puVar10 == (undefined8 *)0x0) {
            uVar14 = 0x8007000e;
          }
        }
        else {
          puVar12 = local_108;
          if (uVar6 == 0) {
            FUN_180078228(local_a8);
            uVar7 = FUN_18004b06c(param_1,local_a8,plVar2,&local_108);
            uVar14 = uVar7 & 0xffffffff;
            if (-1 < (int)uVar7) {
              if ((local_98 == 1) && (local_a8[0] != (undefined8 *)0x0)) {
                plVar3 = (longlong *)local_a8[0][2];
                pcVar4 = *(code **)(*plVar3 + 0xe8);
                uVar9 = *(undefined8 *)(param_1 + 0x530);
                uVar5 = (**(code **)(*plVar2 + 0xf0))(plVar2);
                (*pcVar4)(plVar3,uVar5,uVar9);
              }
              puVar12 = *(undefined8 **)(param_1 + 0x4c0);
              puVar10 = local_a8[0];
              if (puVar12 != (undefined8 *)0x0) {
                uVar6 = (**(code **)*puVar12)(puVar12,local_a8,0,0);
                uVar14 = (ulonglong)uVar6;
                puVar10 = local_a8[0];
                if ((int)uVar6 < 0) goto LAB_1800190f4;
              }
              do {
                if (puVar10 == (undefined8 *)0x0) {
                  FUN_1800192f8(local_a8);
                  puVar12 = FUN_180019234(&local_d8,&local_res10);
                  uVar14 = 0;
                  if (puVar12 == (undefined8 *)0x0) {
                    uVar14 = 0x8007000e;
                  }
                  goto LAB_1800190f4;
                }
                puVar12 = (undefined8 *)*puVar10;
                puVar11 = FUN_180019234(&local_138,puVar10 + 2);
                puVar10 = puVar12;
              } while (puVar11 != (undefined8 *)0x0);
              uVar14 = 0x8007000e;
            }
LAB_1800190f4:
            FUN_18001d780(local_70);
            puVar12 = local_a8[0];
            while (puVar12 != (undefined8 *)0x0) {
              plVar2 = puVar12 + 2;
              puVar12 = (undefined8 *)*puVar12;
              if (*plVar2 != 0) {
                puVar10 = (undefined8 *)(*plVar2 + 8);
                (**(code **)*puVar10)(puVar10,1);
              }
            }
            FUN_1800192f8(local_a8);
            FUN_1800192f8(local_a8);
            puVar12 = local_108;
          }
        }
        while (puVar12 != (undefined8 *)0x0) {
          plVar2 = puVar12 + 2;
          puVar12 = (undefined8 *)*puVar12;
          if (*plVar2 != 0) {
            _o_free();
          }
        }
        FUN_1800192f8(&local_108);
      }
    }
    if ((int)uVar14 < 0) goto LAB_1800191f5;
  }
  FUN_1800192f8(puVar1);
  puVar13 = local_d8;
  while (puVar12 = local_138, puVar13 != (undefined8 *)0x0) {
    plVar2 = puVar13 + 2;
    puVar13 = (undefined8 *)*puVar13;
    if (*plVar2 != 0) {
      puVar12 = (undefined8 *)(*plVar2 + 8);
      (**(code **)*puVar12)(puVar12,1);
    }
  }
  do {
    uVar14 = 0;
    if (puVar12 == (undefined8 *)0x0) {
LAB_1800191f5:
      FUN_1800192f8(&local_d8);
      FUN_1800192f8(&local_138);
      return uVar14;
    }
    plVar2 = (longlong *)puVar12[2];
    puVar12 = (undefined8 *)*puVar12;
    local_res10 = plVar2;
    if ((plVar2 == (longlong *)0x0) ||
       (puVar13 = FUN_180019234(puVar1,&local_res10), puVar13 == (undefined8 *)0x0)) {
      uVar14 = 0x8007000e;
      goto LAB_1800191f5;
    }
    plVar2[5] = (longlong)puVar1;
    plVar2[6] = (longlong)puVar13;
  } while( true );
}


