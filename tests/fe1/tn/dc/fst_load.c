// FUN_1800dc268 @ 1800dc268

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulonglong FUN_1800dc268(char *param_1,longlong *param_2)

{
  undefined8 uVar1;
  longlong *plVar2;
  undefined1 auStack_108 [32];
  char *local_e8;
  undefined8 local_d8 [12];
  undefined8 local_78 [12];
  ulonglong local_18;
  
  local_18 = DAT_1801c0240 ^ (ulonglong)auStack_108;
  if (*param_1 == '\0') {
    local_e8 = param_1;
    uVar1 = FUN_1800dbde0((longlong)param_1,param_2);
    if ((param_1[0x4a3] != '\0') && (param_1[0x4a2] != '\0')) {
      plVar2 = FUN_180072478(local_d8,"Contains both an empty (\"\") and \"MAIN\" top network.");
      FUN_1800d2524(local_78,plVar2);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_78,(ThrowInfo *)&DAT_1801b66d8);
    }
    *param_1 = '\x01';
    local_18 = CONCAT71((int7)((ulonglong)uVar1 >> 8),1);
  }
  else {
    local_18 = local_18 & 0xffffffffffffff00;
  }
  return local_18;
}


