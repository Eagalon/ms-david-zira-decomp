// FUN_180022470 @ 180022470

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

uint FUN_180022470(undefined8 *param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  byte local_res8 [8];
  
  local_res8[0] = 0;
  (**(code **)*param_1)(param_1,local_res8,1);
  *param_2 = *param_2 + 1;
  bVar3 = local_res8[0] & 0x40;
  uVar2 = local_res8[0] & 0x3f;
  while ((char)local_res8[0] < '\0') {
    (**(code **)*param_1)(param_1,local_res8,1);
    *param_2 = *param_2 + 1;
    uVar2 = local_res8[0] & 0x7f | uVar2 << 7;
  }
  uVar1 = -uVar2;
  if (bVar3 == 0) {
    uVar1 = uVar2;
  }
  return uVar1;
}


// FUN_180022714 @ 180022714

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_180022714(uint *param_1,undefined8 *param_2,uint *param_3,undefined8 param_4)

{
  bool bVar1;
  uint uVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  longlong *plVar5;
  undefined8 uVar6;
  basic_ostream<char,std::char_traits<char>_> *pbVar7;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar8;
  longlong *plVar9;
  longlong lVar10;
  char *pcVar11;
  uint *puVar12;
  ulonglong uVar13;
  bool bVar14;
  uint uVar15;
  ulonglong uVar16;
  undefined1 auStack_1a8 [32];
  longlong *local_188;
  uint local_180;
  undefined8 *local_178;
  uint *local_170;
  longlong local_168 [4];
  longlong local_148 [3];
  longlong *local_130;
  longlong local_128 [4];
  longlong local_108 [4];
  longlong local_e8 [4];
  longlong local_c8 [4];
  undefined8 local_a8 [12];
  ulonglong local_48;
  
  local_48 = DAT_1801c0240 ^ (ulonglong)auStack_1a8;
  bVar14 = false;
  local_180 = 0;
  plVar9 = *(longlong **)(param_1 + 0x1e);
  *(int *)(plVar9 + 4) = (int)plVar9[10];
  *(undefined1 *)((longlong)plVar9 + 0x24) = *(undefined1 *)(*(longlong *)(param_1 + 0x1e) + 0x2c);
  local_178 = param_2;
  local_170 = param_3;
  uVar2 = FUN_180022470(param_2,(int *)param_3);
  local_180 = uVar2;
  FUN_180071f4c(local_c8);
  puVar3 = FUN_180023160((undefined8 *)&DAT_1801c10a8);
  FUN_180071eb4(local_c8,puVar3,DAT_1801c10b8);
  FUN_180071f4c(local_e8);
  puVar3 = FUN_180023160((undefined8 *)&DAT_1801c0ee8);
  FUN_180071eb4(local_e8,puVar3,DAT_1801c0ef8);
  FUN_180071e4c(local_148);
  uVar15 = 0;
  do {
    if (uVar2 <= uVar15) {
      if ((*(char *)(*(longlong *)(param_1 + 0x1e) + 0xb8) == '\0') && (uVar2 != 0)) {
        uVar13 = 0;
        uVar16 = (ulonglong)uVar2;
        do {
          puVar3 = (undefined8 *)FUN_1800237ac(local_148,uVar13);
          plVar9 = (longlong *)*puVar3;
          lVar10 = FUN_1800237ac(local_148,uVar13);
          lVar10 = *(longlong *)(lVar10 + 8);
          (**(code **)(*plVar9 + 8))(plVar9,local_108);
          uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c0f88);
          if ((char)uVar6 != '\0') {
            FUN_1800daa34((longlong)param_1,lVar10,1);
            *(undefined1 *)(*(longlong *)(param_1 + 0x1e) + 0xb9) = 1;
            if ((*(byte *)(*(longlong *)(param_1 + 0x1e) + 0xbc) & 2) != 0) {
              FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)cout_exref,"VECTOR_INFO "
                           );
              uVar6 = FUN_1800cfd1c((undefined8 *)&DAT_1801c0f88,"VECTOR_INFO");
              if ((char)uVar6 != '\0') {
                pbVar7 = FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                       "as (");
                pbVar7 = (basic_ostream<char,std::char_traits<char>_> *)
                         FUN_180069bb0(pbVar7,&DAT_1801c0f88);
                FUN_180068848(pbVar7,") ");
              }
              std::basic_ostream<char,std::char_traits<char>_>::operator<<
                        ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_1800d19e0);
            }
          }
          thunk_FUN_1800cfb74(local_108);
          uVar13 = uVar13 + 1;
          uVar16 = uVar16 - 1;
          uVar2 = local_180;
        } while (uVar16 != 0);
      }
      uVar15 = 0;
      do {
        if (uVar2 <= uVar15) {
          if ((param_1[0x1a] != 0) && (param_1[0x1b] != 0)) {
            *(undefined1 *)(param_1 + 0x1d) = 1;
            param_1[0x1a] = param_1[0x1a] * 2;
            param_1[0x1b] = param_1[0x1b] * 2;
          }
          lVar10 = *(longlong *)(param_1 + 0x1e);
          plVar9 = FUN_180071d6c(local_168,local_148);
          FUN_180022f64(lVar10,(undefined8 *)(param_1 + 2),plVar9);
          FUN_1800d4cd0(local_148);
          thunk_FUN_1800cfb74(local_e8);
          thunk_FUN_1800cfb74(local_c8);
          return;
        }
        plVar9 = *(longlong **)(local_148[0] + (ulonglong)uVar15 * 0x10);
        plVar4 = *(longlong **)(local_148[0] + 8 + (ulonglong)uVar15 * 0x10);
        (**(code **)(*plVar9 + 8))(plVar9,local_108);
        uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c10e8);
        if ((char)uVar6 == '\0') {
          uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c10c8);
          if ((char)uVar6 == '\0') {
            uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c1068);
            if ((char)uVar6 == '\0') {
              uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c1048);
              if ((char)uVar6 != '\0') {
                lVar10 = *(longlong *)(param_1 + 0x14);
                plVar9 = FUN_180071e7c(local_128,local_e8);
                FUN_1800209b4(lVar10,plVar9,(longlong)plVar4,0);
                lVar10 = *(longlong *)(param_1 + 0x14);
                plVar9 = FUN_180071e7c(local_128,(undefined8 *)&DAT_1801c1048);
                plVar9 = FUN_1800d59f8((longlong)param_1,local_168,plVar9);
                param_4 = 0;
                uVar13 = FUN_1800209b4(lVar10,plVar9,(longlong)plVar4,0);
                param_1[0x1b] = (uint)uVar13;
              }
            }
            else {
              lVar10 = *(longlong *)(param_1 + 0x14);
              plVar9 = FUN_180071e7c(local_128,local_c8);
              FUN_1800209b4(lVar10,plVar9,(longlong)plVar4,0);
              lVar10 = *(longlong *)(param_1 + 0x14);
              plVar9 = FUN_180071e7c(local_128,(undefined8 *)&DAT_1801c1068);
              plVar9 = FUN_1800d59f8((longlong)param_1,local_168,plVar9);
              param_4 = 0;
              uVar13 = FUN_1800209b4(lVar10,plVar9,(longlong)plVar4,0);
              param_1[0x1a] = (uint)uVar13;
            }
          }
          else {
            if ((*(byte *)(*(longlong *)(param_1 + 0x1e) + 0xbc) & 2) != 0) {
              pbVar7 = FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                     "toolversions ");
              pcVar11 = (char *)(**(code **)(*plVar4 + 8))(plVar4,local_128);
              pbVar7 = (basic_ostream<char,std::char_traits<char>_> *)FUN_180069bb0(pbVar7,pcVar11);
              std::basic_ostream<char,std::char_traits<char>_>::operator<<(pbVar7,FUN_1800d19e0);
              thunk_FUN_1800cfb74(local_128);
            }
            puVar12 = param_1 + 10;
            lVar10 = *(longlong *)(param_1 + 0x1e);
            param_1[0xd] = *(uint *)(lVar10 + 0x30);
            param_1[0xe] = *(uint *)(lVar10 + 0x38);
            FUN_1800d7640((int *)puVar12,plVar4,lVar10,param_4);
            *(undefined1 *)(param_1 + 0x12) = 1;
            FUN_1800da4e8((int *)puVar12,plVar4);
            FUN_1800da8cc((int *)puVar12,plVar4);
            FUN_1800da658((int *)puVar12);
          }
        }
        else {
          for (uVar13 = 0; uVar2 = local_180, (uint)uVar13 < *(uint *)(plVar4 + 2);
              uVar13 = (ulonglong)((uint)uVar13 + 1)) {
            lVar10 = *(longlong *)(plVar4[3] + uVar13 * 8);
            if (*(int *)(lVar10 + 8) != 3) {
              plVar9 = FUN_180072478(local_168,
                                     "FST file property error: DEFINED_LISTS should be list of lists."
                                    );
              FUN_1800d2524(local_a8,plVar9);
                    /* WARNING: Subroutine does not return */
              _CxxThrowException(local_a8,(ThrowInfo *)&DAT_1801b66d8);
            }
            plVar9 = (longlong *)**(longlong **)(lVar10 + 0x18);
            if ((int)plVar9[1] != 2) {
              plVar9 = FUN_180072478(local_168,
                                     "FST file property error: DEFINED_LISTS should be list of lists of strings."
                                    );
              FUN_1800d2524(local_a8,plVar9);
                    /* WARNING: Subroutine does not return */
              _CxxThrowException(local_a8,(ThrowInfo *)&DAT_1801b66d8);
            }
            (**(code **)(*plVar9 + 8))(plVar9,local_128);
            FUN_1800dd1fc(*(longlong *)(param_1 + 0x14),lVar10);
            thunk_FUN_1800cfb74(local_128);
          }
        }
        thunk_FUN_1800cfb74(local_108);
        uVar15 = uVar15 + 1;
      } while( true );
    }
    plVar4 = (longlong *)FUN_180022068(plVar9,param_2,param_3);
    local_188 = plVar4;
    plVar5 = (longlong *)FUN_180021f70(plVar9,param_2,local_170);
    local_130 = plVar5;
    puVar3 = FUN_1800d95a8(local_168,&local_188,&local_130);
    FUN_1800d6184(local_148,puVar3);
    (**(code **)(*plVar4 + 8))(plVar4,local_108);
    uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c1088);
    if ((((char)uVar6 == '\0') &&
        (uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c0ea8), (char)uVar6 == '\0')) &&
       (uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c0f08), (char)uVar6 == '\0')) {
      uVar6 = FUN_180022f20(local_108,(undefined8 *)&DAT_1801c0fa8);
      if ((char)uVar6 != '\0') {
        if (*(char *)(*(longlong *)(param_1 + 0x1e) + 0xb9) == '\0') {
          FUN_1800daa34((longlong)param_1,(longlong)plVar5,
                        *(int *)(*(longlong *)(param_1 + 0x1e) + 0x40));
          *(undefined1 *)(*(longlong *)(param_1 + 0x1e) + 0xb8) = 1;
          if ((*(byte *)(*(longlong *)(param_1 + 0x1e) + 0xbc) & 2) != 0) {
            FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                          "GLOBAL_VECTOR_INFO ]");
            uVar6 = FUN_1800cfd1c((undefined8 *)&DAT_1801c0fa8,"GLOBAL_VECTOR_INFO");
            if ((char)uVar6 != '\0') {
              pbVar7 = FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                     "as (");
              pbVar7 = (basic_ostream<char,std::char_traits<char>_> *)
                       FUN_180069bb0(pbVar7,&DAT_1801c0fa8);
              FUN_180068848(pbVar7,")");
            }
            std::basic_ostream<char,std::char_traits<char>_>::operator<<
                      ((basic_ostream<char,std::char_traits<char>_> *)cout_exref,FUN_1800d19e0);
          }
        }
        else {
          pbVar7 = FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)cout_exref,
                                 "WARNING: net contains GLOBAL_VECTOR_INFO,");
          pbVar7 = FUN_180068848(pbVar7,"but already loading VECTOR_INFO");
          pbVar8 = std::basic_ostream<char,std::char_traits<char>_>::operator<<
                             (pbVar7,FUN_1800d19e0);
          FUN_180068848((basic_ostream<char,std::char_traits<char>_> *)pbVar8,
                        "Loading VECTOR_INFO instead.");
        }
      }
    }
    else {
      if (*(longlong *)(param_1 + 6) == 0) {
LAB_1800229b4:
        bVar1 = true;
      }
      else {
        puVar3 = (undefined8 *)(**(code **)(*plVar5 + 8))(plVar5,local_128);
        bVar14 = true;
        uVar6 = FUN_180022f20((undefined8 *)(param_1 + 2),puVar3);
        if ((char)uVar6 != '\0') goto LAB_1800229b4;
        bVar1 = false;
      }
      puVar12 = param_1 + 2;
      if (bVar14) {
        bVar14 = false;
        thunk_FUN_1800cfb74(local_128);
      }
      if (!bVar1) {
        plVar9 = FUN_180072478(local_128,
                               "Both old and new style Network names set, but inconsistently.");
        FUN_1800d2524(local_a8,plVar9);
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(local_a8,(ThrowInfo *)&DAT_1801b66d8);
      }
      plVar4 = (longlong *)(**(code **)(*plVar5 + 8))(plVar5,local_128);
      FUN_180072370((longlong *)puVar12,plVar4);
      thunk_FUN_1800cfb74(local_128);
      uVar6 = FUN_180022f20((undefined8 *)puVar12,(undefined8 *)&DAT_1801c0f68);
      if (((char)uVar6 == '\0') || ((*param_1 >> 0x13 & 1) != 0)) {
        uVar6 = FUN_180022f20((undefined8 *)puVar12,(undefined8 *)&DAT_1801c0f48);
        param_2 = local_178;
        if ((char)uVar6 != '\0') {
          *(undefined1 *)(*(longlong *)(param_1 + 0x1e) + 0xba) = 1;
        }
      }
      else {
        *(undefined1 *)(*(longlong *)(param_1 + 0x1e) + 0xbb) = 1;
        param_2 = local_178;
      }
    }
    thunk_FUN_1800cfb74(local_108);
    uVar15 = uVar15 + 1;
    param_3 = local_170;
    uVar2 = local_180;
  } while( true );
}


