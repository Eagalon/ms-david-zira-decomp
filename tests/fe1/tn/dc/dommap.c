// FUN_18002bf08 @ 18002bf08

/* WARNING: Function: _guard_dispatch_icall replaced with injection: guard_dispatch_icall */

ulonglong FUN_18002bf08(undefined8 param_1,longlong *param_2)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  longlong lVar5;
  wchar_t *pwVar6;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  short *psVar7;
  ulonglong uVar8;
  undefined8 *puVar9;
  undefined7 extraout_var_01;
  ulonglong uVar10;
  code *pcVar11;
  longlong local_res10;
  undefined **local_88;
  longlong local_80;
  longlong lStack_78;
  undefined8 local_70;
  undefined8 local_68 [4];
  undefined8 local_48 [4];
  
  bVar2 = false;
  if (param_2 == (longlong *)0x0) {
    return 0;
  }
  local_res10 = 0;
  uVar3 = (**(code **)(*param_2 + 0x110))(param_2,&local_res10);
  uVar10 = (ulonglong)uVar3;
  if (-1 < (int)uVar3) {
    if (*(longlong **)(local_res10 + 0x20) != (longlong *)0x0) {
      local_88 = CTTSString::vftable;
      local_80 = 0;
      lStack_78 = 0;
      local_70 = 0;
      lVar5 = **(longlong **)(local_res10 + 0x20);
      if (lVar5 == 0) {
LAB_18002bfa5:
        if (*(longlong *)(*(longlong *)(local_res10 + 0x20) + 8) == 0) {
LAB_18002bfe9:
          lVar5 = FUN_18001b0e0((longlong)&local_88);
          if ((char)lVar5 == '\0') {
            FUN_1800197b4(local_68,0x180180948);
            pwVar6 = FUN_18001c490((longlong)&local_88);
            iVar4 = wcscmp(pwVar6,L"number_digit");
            if (iVar4 == 0) {
LAB_18002c191:
              pwVar6 = L"cardinal";
LAB_18002c198:
              pcVar11 = *(code **)(*param_2 + 0xd8);
              puVar9 = FUN_1800197b4(local_48,(longlong)pwVar6);
LAB_18002c1ab:
              uVar3 = (*pcVar11)(param_2,puVar9);
              uVar10 = (ulonglong)uVar3;
            }
            else {
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"number:digit");
              if (iVar4 == 0) goto LAB_18002c191;
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"cardinal");
              if (iVar4 == 0) goto LAB_18002c191;
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"number:cardinal");
              if (iVar4 == 0) goto LAB_18002c191;
              pwVar6 = FUN_18001c490((longlong)&local_88);
              bVar1 = FUN_18003d81c(pwVar6,L"date");
              if ((int)CONCAT71(extraout_var,bVar1) != 0) {
                pwVar6 = L"date";
                goto LAB_18002c198;
              }
              pwVar6 = FUN_18001c490((longlong)&local_88);
              bVar1 = FUN_18003d81c(pwVar6,L"time");
              if ((int)CONCAT71(extraout_var_00,bVar1) != 0) {
                pwVar6 = L"time";
                goto LAB_18002c198;
              }
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"telephone");
              if (iVar4 == 0) {
LAB_18002c188:
                pwVar6 = L"phonenumber";
                goto LAB_18002c198;
              }
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"phone_number");
              if (iVar4 == 0) goto LAB_18002c188;
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"net_email");
              if (iVar4 == 0) {
LAB_18002c17f:
                pwVar6 = L"url";
                goto LAB_18002c198;
              }
              pwVar6 = FUN_18001c490((longlong)&local_88);
              iVar4 = wcscmp(pwVar6,L"net:email");
              if (iVar4 == 0) goto LAB_18002c17f;
              psVar7 = FUN_18001c490((longlong)&local_88);
              uVar8 = FUN_1800720a4(psVar7,(longlong)local_68);
              uVar10 = uVar8 & 0xffffffff;
              if (-1 < (int)uVar8) {
                pcVar11 = *(code **)(*param_2 + 0xd8);
                puVar9 = FUN_18001b878(local_48,local_68);
                goto LAB_18002c1ab;
              }
            }
            FUN_18001d780(local_68);
          }
        }
        else {
          uVar3 = FUN_18002c3e0((longlong *)&local_88,0x18018636c);
          uVar10 = (ulonglong)uVar3;
          if (-1 < (int)uVar3) {
            uVar3 = FUN_18002c3e0((longlong *)&local_88,
                                  *(longlong *)(*(longlong *)(local_res10 + 0x20) + 8));
            uVar10 = (ulonglong)uVar3;
            if (-1 < (int)uVar3) goto LAB_18002bfe9;
          }
        }
      }
      else {
        uVar3 = FUN_18002c3e0((longlong *)&local_88,lVar5);
        uVar10 = (ulonglong)uVar3;
        if (-1 < (int)uVar3) goto LAB_18002bfa5;
      }
      FUN_18001d780(&local_88);
    }
    if (-1 < (int)uVar10) {
      lVar5 = (**(code **)(*param_2 + 0xe0))(param_2,&local_88);
      bVar2 = true;
      if (*(wchar_t **)(lVar5 + 8) == (wchar_t *)0x0) {
        bVar1 = false;
      }
      else {
        iVar4 = wcscmp(*(wchar_t **)(lVar5 + 8),L"none");
        bVar1 = iVar4 == 0;
      }
      if (bVar1) {
        bVar1 = true;
        goto LAB_18002c21c;
      }
    }
  }
  bVar1 = false;
LAB_18002c21c:
  if (bVar2) {
    local_88 = CTTSString::vftable;
    if (local_80 != 0) {
      _o_free();
      local_80 = 0;
    }
    if (lStack_78 != 0) {
      _o_free();
    }
  }
  if (((bVar1) &&
      (pwVar6 = (wchar_t *)(**(code **)(*param_2 + 0xc0))(param_2), pwVar6 != (wchar_t *)0x0)) &&
     (bVar2 = FUN_18003d81c(pwVar6,L"sp:"), (int)CONCAT71(extraout_var_01,bVar2) != 0)) {
    iVar4 = wcscmp(pwVar6,L"sp:cardinal");
    if (iVar4 == 0) {
      pwVar6 = L"cardinal";
    }
    else {
      iVar4 = wcscmp(pwVar6,L"sp:date");
      if (iVar4 == 0) {
        pwVar6 = L"date";
      }
      else {
        iVar4 = wcscmp(pwVar6,L"sp:time");
        if (iVar4 == 0) {
          pwVar6 = L"time";
        }
        else {
          iVar4 = wcscmp(pwVar6,L"sp:phoneNumber");
          if (iVar4 == 0) {
            pwVar6 = L"phonenumber";
          }
          else {
            iVar4 = wcscmp(pwVar6,L"sp:address");
            if (iVar4 == 0) {
              pwVar6 = L"address";
            }
            else {
              iVar4 = wcscmp(pwVar6,L"sp:email");
              if (((iVar4 == 0) || (iVar4 = wcscmp(pwVar6,L"sp:webUrl"), iVar4 == 0)) ||
                 (iVar4 = wcscmp(pwVar6,L"sp:filePath"), iVar4 == 0)) {
                pwVar6 = L"url";
              }
              else {
                iVar4 = wcscmp(pwVar6,L"sp:message");
                if (iVar4 == 0) {
                  pwVar6 = L"message";
                }
                else {
                  iVar4 = wcscmp(pwVar6,L"sp:name");
                  if (iVar4 != 0) {
                    return uVar10;
                  }
                  pwVar6 = L"name";
                }
              }
            }
          }
        }
      }
    }
    pcVar11 = *(code **)(*param_2 + 0xd8);
    puVar9 = FUN_1800197b4(local_48,(longlong)pwVar6);
    uVar3 = (*pcVar11)(param_2,puVar9);
    uVar10 = (ulonglong)uVar3;
  }
  return uVar10;
}


