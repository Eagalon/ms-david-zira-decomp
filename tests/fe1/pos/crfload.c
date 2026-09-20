// FUN_1800e4f00 @ 1800e4f00

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_1800e4f00(longlong param_1,undefined8 *param_2,ulonglong param_3,longlong *param_4)

{
  undefined8 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  ushort *puVar5;
  int iVar6;
  uint uVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  ushort *local_res10;
  ulonglong local_res18 [2];
  undefined8 *local_38;
  undefined8 local_30;
  
  local_res18[0] = param_3;
  local_38 = param_2;
  if (param_3 < 0x18) {
LAB_1800e5166:
    uVar7 = 0x8000ffff;
  }
  else {
    uVar2 = *(undefined4 *)((longlong)param_2 + 4);
    uVar3 = *(undefined4 *)(param_2 + 1);
    uVar4 = *(undefined4 *)((longlong)param_2 + 0xc);
    local_38 = param_2 + 3;
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)param_2;
    *(undefined4 *)(param_1 + 0x28) = uVar2;
    *(undefined4 *)(param_1 + 0x2c) = uVar3;
    *(undefined4 *)(param_1 + 0x30) = uVar4;
    local_res18[0] = param_3 - 0x18;
    *(undefined8 *)(param_1 + 0x34) = param_2[2];
    if ((*(char *)(param_1 + 0x20) == '\0') ||
       (iVar6 = _o__strnicmp((char *)(param_1 + 0x20),(undefined4 *)(param_1 + 0x24),3), iVar6 == 0)
       ) {
      lVar8 = *(longlong *)(param_1 + 0x28) - _DAT_180188900;
      if (lVar8 == 0) {
        lVar8 = *(longlong *)(param_1 + 0x30) - _DAT_180188908;
      }
      if (lVar8 == 0) {
        uVar10 = FUN_1800355c0((undefined2 *)(param_1 + 0x44),(longlong *)&local_38,local_res18);
        uVar7 = (uint)uVar10;
        if (-1 < (int)uVar7) {
          uVar10 = FUN_1800355c0((undefined2 *)&local_res10,(longlong *)&local_38,local_res18);
          uVar7 = (uint)uVar10;
          if (-1 < (int)uVar7) {
            local_res10 = (ushort *)0x0;
            uVar9 = FUN_1800b4388((longlong *)&local_res10,1,4,(longlong *)&local_38,local_res18);
            uVar7 = (uint)uVar9;
            if (-1 < (int)uVar7) {
              *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)local_res10;
              iVar6 = _o__strnicmp((undefined4 *)(param_1 + 0x3c),&DAT_18018a9d4,4);
              if (iVar6 != 0) goto LAB_1800e5137;
              uVar10 = FUN_180035a50((undefined4 *)(param_1 + 0x40),(longlong *)&local_38,
                                     local_res18);
              uVar7 = (uint)uVar10;
              if (-1 < (int)uVar7) {
                if (local_res18[0] < 0x20) goto LAB_1800e5166;
                local_res18[0] = local_res18[0] - 0x20;
                uVar10 = local_38[1];
                *(undefined8 *)(param_1 + 0x48) = *local_38;
                *(undefined8 *)(param_1 + 0x50) = uVar10;
                puVar1 = local_38 + 2;
                uVar10 = local_38[3];
                local_38 = local_38 + 4;
                *(undefined8 *)(param_1 + 0x58) = *puVar1;
                *(undefined8 *)(param_1 + 0x60) = uVar10;
                *(ulonglong *)(param_1 + 0xe0) =
                     (ulonglong)*(uint *)(param_1 + 0x48) + (longlong)param_2;
                *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0x4c);
                uVar9 = FUN_1800e52bc(param_1 + -0x18,(longlong *)&local_38,local_res18);
                uVar7 = (uint)uVar9;
              }
            }
          }
        }
      }
      else {
        uVar7 = 0x80048018;
      }
    }
    else {
LAB_1800e5137:
      uVar7 = 0x8004800f;
    }
  }
  if ((-1 < (int)uVar7) &&
     (uVar7 = FUN_18003880c(param_1 + -0x18,&local_38,local_res18), -1 < (int)uVar7)) {
    local_res10 = (ushort *)0x0;
    uVar9 = FUN_1800b4388((longlong *)&local_res10,1,(ulonglong)*(uint *)(param_1 + 0x58),
                          (longlong *)&local_38,local_res18);
    uVar7 = (uint)uVar9;
    if (-1 < (int)uVar7) {
      local_30 = 0;
      uVar7 = FUN_18003cbe0(&local_30,local_res10,*(undefined4 *)(param_1 + 0x58));
      if (-1 < (int)uVar7) {
        local_res10 = (ushort *)0x0;
        *(undefined8 *)(param_1 + 200) = local_30;
        if (local_res18[0] < *(uint *)(param_1 + 0x5c)) {
LAB_1800e51c4:
          uVar7 = 0x8004800f;
        }
        else {
          uVar9 = FUN_1800b4388((longlong *)&local_res10,1,(ulonglong)*(uint *)(param_1 + 0x5c),
                                (longlong *)&local_38,local_res18);
          puVar5 = local_res10;
          uVar7 = (uint)uVar9;
          if (-1 < (int)uVar7) {
            local_res10 = (ushort *)0x0;
            *(ushort **)(param_1 + 0xd0) = puVar5;
            if (local_res18[0] < *(uint *)(param_1 + 0x60)) goto LAB_1800e51c4;
            uVar9 = FUN_1800b4388((longlong *)&local_res10,1,(ulonglong)*(uint *)(param_1 + 0x60),
                                  (longlong *)&local_38,local_res18);
            uVar7 = (uint)uVar9;
            if (-1 < (int)uVar7) {
              lVar8 = param_3 - local_res18[0];
              *(ushort **)(param_1 + 0xd8) = local_res10;
              goto LAB_1800e51cb;
            }
          }
        }
      }
    }
  }
  lVar8 = 0;
LAB_1800e51cb:
  *param_4 = lVar8;
  return uVar7;
}


