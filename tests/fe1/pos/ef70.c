// FUN_18002ef70 @ 18002ef70

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 * FUN_18002ef70(longlong param_1,undefined8 *param_2)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  wchar_t wVar4;
  wchar_t wVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  uint uVar8;
  wchar_t *pwVar9;
  wchar_t *pwVar10;
  wchar_t *pwVar11;
  ulonglong uVar12;
  undefined8 *puVar13;
  longlong lVar14;
  short *psVar15;
  ushort *puVar16;
  int iVar17;
  undefined8 *puVar18;
  undefined8 *puVar19;
  undefined8 *puVar20;
  longlong *plVar21;
  undefined8 *puVar22;
  wchar_t *pwVar23;
  short sVar24;
  bool bVar25;
  undefined1 auStack_1f8 [48];
  uint local_1c8;
  longlong *local_1c0;
  undefined8 *local_1b8;
  undefined8 *local_1b0;
  wchar_t *local_1a8;
  undefined8 *local_1a0;
  undefined8 *local_190;
  undefined8 *local_188;
  undefined8 *local_180;
  undefined8 *local_178;
  longlong local_170;
  undefined **local_168;
  wchar_t *local_160;
  uint local_158;
  wchar_t local_150 [132];
  ulonglong local_48;
  
  local_48 = DAT_1801c0240 ^ (ulonglong)auStack_1f8;
  if ((param_2 == (undefined8 *)0x0) ||
     (plVar21 = *(longlong **)(param_1 + 0x30), plVar21 == (longlong *)0x0)) {
    puVar13 = (undefined8 *)0x0;
  }
  else {
    local_178 = (undefined8 *)param_2[10];
    puVar13 = (undefined8 *)0x0;
    local_1c8 = 0;
    local_180 = puVar13;
    if (local_178 == (undefined8 *)0x0) {
      local_190 = (undefined8 *)0x0;
    }
    else {
      local_190 = (undefined8 *)local_178[10];
      if (local_190 != (undefined8 *)0x0) {
        local_180 = (undefined8 *)local_190[10];
      }
    }
    local_170 = *(longlong *)(param_1 + 0x20);
    local_188 = param_2;
    do {
      puVar18 = (undefined8 *)0x0;
      lVar14 = *plVar21 - DAT_1801809a8;
      if (lVar14 == 0) {
        lVar14 = (ulonglong)*(uint *)(plVar21 + 1) - (ulonglong)DAT_1801809b0;
      }
      if (lVar14 == 0) {
        return puVar13;
      }
      pwVar23 = (wchar_t *)((ulonglong)*(uint *)(plVar21 + 1) + local_170);
      local_1a0 = (undefined8 *)0x0;
      local_1b0 = (undefined8 *)0x0;
      puVar6 = local_188;
      puVar7 = local_180;
      puVar20 = local_190;
      local_1c0 = plVar21;
      local_1b8 = local_178;
      local_1a8 = pwVar23;
      while (puVar22 = puVar20, puVar20 = puVar7, puVar19 = puVar6, puVar7 = local_1a0,
            puVar19 != (undefined8 *)0x0) {
        if ((*(int *)((longlong)puVar19 + 0xc) == 3) ||
           (sVar24 = *(short *)(puVar19 + 1), sVar24 != *(short *)((longlong)plVar21 + 2)))
        goto LAB_18002f084;
        if (*(int *)((longlong)puVar19 + 0xc) != 2) {
          psVar15 = (short *)puVar19[2];
          uVar12 = 0;
          bVar25 = false;
          if (psVar15 != (short *)0x0) {
            for (; bVar25 = false, uVar12 < (ulonglong)puVar19[3]; uVar12 = uVar12 + 1) {
              sVar1 = *psVar15;
              psVar15 = psVar15 + 1;
              if (sVar1 == *(short *)((longlong)plVar21 + 4)) {
                bVar25 = true;
                break;
              }
            }
          }
          puVar13 = (undefined8 *)0x0;
          local_1c8 = 0;
          plVar21 = local_1c0;
          if (bVar25) goto LAB_18002f150;
          goto LAB_18002f08e;
        }
LAB_18002f150:
        sVar1 = (short)*plVar21;
        if (sVar1 == 0x218) {
          if (local_1b8 == (undefined8 *)0x0) {
            if (*(short *)((longlong)plVar21 + 6) == -2) goto LAB_18002f3c2;
          }
          else if (*(short *)(local_1b8 + 1) == *(short *)((longlong)plVar21 + 6)) {
LAB_18002f3c2:
            puVar16 = &DAT_1801810bc;
            if ((ushort *)*puVar19 != (ushort *)0x0) {
              puVar16 = (ushort *)*puVar19;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)puVar16;
            do {
              uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
              iVar17 = *puVar16 - uVar8;
              if (iVar17 != 0) goto LAB_18002f4b7;
              puVar16 = puVar16 + 1;
            } while (uVar8 != 0);
            bVar25 = true;
            goto LAB_18002f40a;
          }
          goto switchD_18002f1a8_caseD_208;
        }
        if (sVar1 == 0x215) {
          psVar15 = &DAT_1801810bc;
          if ((short *)*puVar19 != (short *)0x0) {
            psVar15 = (short *)*puVar19;
          }
          pwVar9 = L"";
          if (pwVar23 + *(ushort *)((longlong)plVar21 + 6) != (wchar_t *)0x0) {
            pwVar9 = pwVar23 + *(ushort *)((longlong)plVar21 + 6);
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) {
            local_160 = local_150;
            local_158 = 0x80000000;
            local_150[0] = L'\0';
            local_168 = CQuickStringW<128>::vftable;
            uVar12 = FUN_1801441e8((longlong)&local_168,pwVar23,
                                   (ulonglong)*(ushort *)((longlong)plVar21 + 6),0x80);
            local_1c8 = (uint)uVar12;
            puVar13 = (undefined8 *)(uVar12 & 0xffffffff);
            pwVar9 = local_160;
            if (-1 < (int)local_1c8) {
              if (puVar7 == (undefined8 *)0x0) {
LAB_1800301ff:
                pwVar9 = local_160;
                pwVar11 = L"";
                if (local_160 != (wchar_t *)0x0) {
                  pwVar11 = local_160;
                }
                iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
                puVar13 = (undefined8 *)(ulonglong)local_1c8;
              }
              else {
                puVar16 = &DAT_1801810bc;
                if ((ushort *)*puVar7 != (ushort *)0x0) {
                  puVar16 = (ushort *)*puVar7;
                }
                pwVar11 = L"";
                if (local_160 != (wchar_t *)0x0) {
                  pwVar11 = local_160;
                }
                lVar14 = (longlong)pwVar11 - (longlong)puVar16;
                do {
                  uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
                  iVar17 = *puVar16 - uVar8;
                  if (iVar17 != 0) break;
                  puVar16 = puVar16 + 1;
                } while (uVar8 != 0);
              }
joined_r0x000180030219:
              if (iVar17 == 0) {
                sVar24 = *(short *)((longlong)local_1c0 + 4);
              }
            }
            goto joined_r0x00018002fc0c;
          }
          goto switchD_18002f1a8_caseD_208;
        }
        if (sVar1 == 0x216) {
          if (((local_1a0 != (undefined8 *)0x0) &&
              (*(short *)(local_1a0 + 1) == *(short *)((longlong)plVar21 + 6))) ||
             ((*(short *)((longlong)plVar21 + 6) == -2 && (local_1a0 == (undefined8 *)0x0)))) {
            puVar16 = &DAT_1801810bc;
            if ((ushort *)*puVar19 != (ushort *)0x0) {
              puVar16 = (ushort *)*puVar19;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)puVar16;
            do {
              uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
              iVar17 = *puVar16 - uVar8;
              if (iVar17 != 0) goto LAB_18002f4b7;
              puVar16 = puVar16 + 1;
            } while (uVar8 != 0);
            bVar25 = true;
            goto LAB_18002f40a;
          }
          goto switchD_18002f1a8_caseD_208;
        }
        if (sVar1 == 0x208) {
          if (((local_1a0 != (undefined8 *)0x0) &&
              (*(short *)(local_1a0 + 1) == *(short *)((longlong)plVar21 + 6))) ||
             (((local_1b0 != (undefined8 *)0x0 &&
               (*(short *)(local_1b0 + 1) == *(short *)((longlong)plVar21 + 6))) ||
              ((puVar18 != (undefined8 *)0x0 &&
               (*(short *)(puVar18 + 1) == *(short *)((longlong)plVar21 + 6)))))))
          goto LAB_18002f5be;
          if (*(short *)((longlong)plVar21 + 6) == -2) {
            bVar25 = puVar18 == (undefined8 *)0x0;
            goto LAB_18002f40a;
          }
          goto switchD_18002f1a8_caseD_208;
        }
        switch(sVar1) {
        case 0x201:
          if (local_1b8 == (undefined8 *)0x0) {
LAB_18002f5ae:
            if (*(short *)((longlong)plVar21 + 6) == -2) goto LAB_18002f5be;
          }
          else if (*(short *)(local_1b8 + 1) == *(short *)((longlong)plVar21 + 6))
          goto LAB_18002f5be;
          break;
        case 0x202:
          if (puVar22 == (undefined8 *)0x0) goto LAB_18002f5ae;
          if (*(short *)(puVar22 + 1) == *(short *)((longlong)plVar21 + 6)) goto LAB_18002f5be;
          break;
        case 0x203:
          if (((local_1b8 == (undefined8 *)0x0) ||
              (*(short *)(local_1b8 + 1) != *(short *)((longlong)plVar21 + 6))) &&
             ((puVar22 == (undefined8 *)0x0 ||
              (*(short *)(puVar22 + 1) != *(short *)((longlong)plVar21 + 6))))) {
            if ((*(short *)((longlong)plVar21 + 6) == -2) && (puVar22 == (undefined8 *)0x0)) {
              sVar24 = *(short *)((longlong)plVar21 + 4);
            }
            break;
          }
          goto LAB_18002f5be;
        case 0x204:
          if ((((local_1b8 != (undefined8 *)0x0) &&
               (*(short *)(local_1b8 + 1) == *(short *)((longlong)plVar21 + 6))) ||
              ((puVar22 != (undefined8 *)0x0 &&
               (*(short *)(puVar22 + 1) == *(short *)((longlong)plVar21 + 6))))) ||
             ((puVar20 != (undefined8 *)0x0 &&
              (*(short *)(puVar20 + 1) == *(short *)((longlong)plVar21 + 6))))) goto LAB_18002f5be;
          if ((*(short *)((longlong)plVar21 + 6) == -2) && (puVar20 == (undefined8 *)0x0)) {
            sVar24 = *(short *)((longlong)plVar21 + 4);
          }
          break;
        case 0x205:
          if ((local_1a0 != (undefined8 *)0x0) &&
             (*(short *)(local_1a0 + 1) == *(short *)((longlong)plVar21 + 6))) goto LAB_18002f5be;
          if ((*(short *)((longlong)plVar21 + 6) == -2) && (local_1a0 == (undefined8 *)0x0)) {
            sVar24 = *(short *)((longlong)plVar21 + 4);
          }
          break;
        case 0x206:
          goto joined_r0x00018002f700;
        case 0x207:
          if ((local_1a0 != (undefined8 *)0x0) &&
             (*(short *)(local_1a0 + 1) == *(short *)((longlong)plVar21 + 6))) goto LAB_18002f5be;
joined_r0x00018002f700:
          if ((local_1b0 == (undefined8 *)0x0) ||
             (*(short *)(local_1b0 + 1) != *(short *)((longlong)plVar21 + 6))) {
            if (*(short *)((longlong)plVar21 + 6) == -2) {
              bVar25 = local_1b0 == (undefined8 *)0x0;
LAB_18002f40a:
              if (bVar25) {
                sVar24 = *(short *)((longlong)plVar21 + 4);
              }
            }
          }
          else {
LAB_18002f5be:
            sVar24 = *(short *)((longlong)plVar21 + 4);
          }
          break;
        case 0x209:
          puVar16 = &DAT_1801810bc;
          if ((ushort *)*puVar19 != (ushort *)0x0) {
            puVar16 = (ushort *)*puVar19;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)puVar16;
          do {
            uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
            iVar17 = *puVar16 - uVar8;
            if (iVar17 != 0) break;
            puVar16 = puVar16 + 1;
          } while (uVar8 != 0);
LAB_18002f4b7:
          bVar25 = iVar17 == 0;
          goto LAB_18002f40a;
        case 0x20a:
          if (local_1b8 == (undefined8 *)0x0) {
LAB_18002fa85:
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            iVar17 = wcscmp(pwVar9,L"S-T-A-R-T");
            bVar25 = iVar17 == 0;
            puVar13 = (undefined8 *)(ulonglong)local_1c8;
            plVar21 = local_1c0;
            goto LAB_18002f40a;
          }
          psVar15 = &DAT_1801810bc;
          if ((short *)*local_1b8 != (short *)0x0) {
            psVar15 = (short *)*local_1b8;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x20b:
          if (puVar22 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*puVar22 != (short *)0x0) {
            psVar15 = (short *)*puVar22;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x20c:
          if (local_1b8 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*local_1b8 != (short *)0x0) {
              psVar15 = (short *)*local_1b8;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002f5be;
          }
          if (puVar22 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*puVar22 != (short *)0x0) {
            psVar15 = (short *)*puVar22;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) {
            sVar24 = *(short *)((longlong)plVar21 + 4);
          }
          break;
        case 0x20d:
          if (local_1b8 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*local_1b8 != (short *)0x0) {
              psVar15 = (short *)*local_1b8;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002f5be;
          }
          if (puVar22 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*puVar22 != (short *)0x0) {
              psVar15 = (short *)*puVar22;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002f5be;
          }
          if (puVar20 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*puVar20 != (short *)0x0) {
            psVar15 = (short *)*puVar20;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x20e:
          if (local_1a0 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*local_1a0 != (short *)0x0) {
            psVar15 = (short *)*local_1a0;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x20f:
          if (local_1b0 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*local_1b0 != (short *)0x0) {
            psVar15 = (short *)*local_1b0;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x210:
          if (local_1a0 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*local_1a0 != (short *)0x0) {
              psVar15 = (short *)*local_1a0;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002f5be;
          }
          if (local_1b0 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*local_1b0 != (short *)0x0) {
            psVar15 = (short *)*local_1b0;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x211:
          if (local_1a0 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*local_1a0 != (short *)0x0) {
              psVar15 = (short *)*local_1a0;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002f5be;
          }
          if (local_1b0 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*local_1b0 != (short *)0x0) {
              psVar15 = (short *)*local_1b0;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002f5be;
          }
          if (puVar18 == (undefined8 *)0x0) goto LAB_18002fa85;
          psVar15 = &DAT_1801810bc;
          if ((short *)*puVar18 != (short *)0x0) {
            psVar15 = (short *)*puVar18;
          }
          pwVar9 = L"";
          if (pwVar23 != (wchar_t *)0x0) {
            pwVar9 = pwVar23;
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) goto LAB_18002f5be;
          break;
        case 0x212:
          if (((local_1a0 != (undefined8 *)0x0) &&
              (*(short *)(local_1a0 + 1) == *(short *)((longlong)plVar21 + 6))) ||
             ((*(short *)((longlong)plVar21 + 6) == -2 && (local_1a0 == (undefined8 *)0x0)))) {
            if (local_1b8 == (undefined8 *)0x0) {
              bVar25 = *local_1a8 == L'\xfffe';
              goto LAB_18002f40a;
            }
            if (*(wchar_t *)(local_1b8 + 1) == *local_1a8) goto LAB_18002f5be;
          }
          break;
        case 0x213:
          if (local_1a0 == (undefined8 *)0x0) {
            if (*local_1a8 == L'\xfffe') goto LAB_18002fc80;
          }
          else if (*(wchar_t *)(local_1a0 + 1) == *local_1a8) {
LAB_18002fc80:
            if (local_1b0 == (undefined8 *)0x0) {
              bVar25 = *(short *)((longlong)plVar21 + 6) == -2;
              goto LAB_18002f40a;
            }
            if (*(short *)(local_1b0 + 1) == *(short *)((longlong)plVar21 + 6)) goto LAB_18002f5be;
          }
          break;
        case 0x214:
          if (local_1b8 == (undefined8 *)0x0) {
            if (*(short *)((longlong)plVar21 + 6) == -2) goto LAB_18002fe1b;
          }
          else if (*(short *)(local_1b8 + 1) == *(short *)((longlong)plVar21 + 6)) {
LAB_18002fe1b:
            if (puVar22 == (undefined8 *)0x0) {
              bVar25 = *local_1a8 == L'\xfffe';
              goto LAB_18002f40a;
            }
            if (*(wchar_t *)(puVar22 + 1) == *local_1a8) goto LAB_18002f5be;
          }
          break;
        case 0x217:
          uVar3 = *(ushort *)((longlong)plVar21 + 6);
          pwVar9 = pwVar23 + uVar3;
          if (local_1b8 != (undefined8 *)0x0) {
            psVar15 = &DAT_1801810bc;
            if ((short *)*local_1b8 != (short *)0x0) {
              psVar15 = (short *)*local_1b8;
            }
            pwVar11 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar11 = pwVar9;
            }
            lVar14 = (longlong)pwVar11 - (longlong)psVar15;
            do {
              sVar1 = *psVar15;
              sVar2 = *(short *)((longlong)psVar15 + lVar14);
              if (sVar1 != sVar2) break;
              psVar15 = psVar15 + 1;
            } while (sVar2 != 0);
            if (sVar1 == sVar2) goto LAB_18002fe5e;
            break;
          }
          pwVar11 = L"";
          if (pwVar9 != (wchar_t *)0x0) {
            pwVar11 = pwVar9;
          }
          iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
          if (iVar17 == 0) {
LAB_18002fe5e:
            local_160 = local_150;
            local_158 = 0x80000000;
            local_150[0] = L'\0';
            local_168 = CQuickStringW<128>::vftable;
            uVar12 = FUN_1801441e8((longlong)&local_168,pwVar23,(ulonglong)uVar3,0x80);
            local_1c8 = (uint)uVar12;
            puVar13 = (undefined8 *)(uVar12 & 0xffffffff);
            pwVar9 = local_160;
            if ((int)local_1c8 < 0) goto joined_r0x00018002fc0c;
            puVar16 = &DAT_1801810bc;
            if ((ushort *)*puVar19 != (ushort *)0x0) {
              puVar16 = (ushort *)*puVar19;
            }
            pwVar9 = L"";
            if (local_160 != (wchar_t *)0x0) {
              pwVar9 = local_160;
            }
            lVar14 = (longlong)pwVar9 - (longlong)puVar16;
            do {
              uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
              iVar17 = *puVar16 - uVar8;
              if (iVar17 != 0) break;
              puVar16 = puVar16 + 1;
            } while (uVar8 != 0);
            goto LAB_18002fedb;
          }
          goto LAB_18002fc21;
        case 0x219:
          psVar15 = &DAT_1801810bc;
          if ((short *)*puVar19 != (short *)0x0) {
            psVar15 = (short *)*puVar19;
          }
          pwVar9 = L"";
          if (pwVar23 + *(ushort *)((longlong)plVar21 + 6) != (wchar_t *)0x0) {
            pwVar9 = pwVar23 + *(ushort *)((longlong)plVar21 + 6);
          }
          lVar14 = (longlong)pwVar9 - (longlong)psVar15;
          do {
            sVar1 = *psVar15;
            sVar2 = *(short *)((longlong)psVar15 + lVar14);
            if (sVar1 != sVar2) break;
            psVar15 = psVar15 + 1;
          } while (sVar2 != 0);
          if (sVar1 == sVar2) {
            local_160 = local_150;
            local_158 = 0x80000000;
            local_150[0] = L'\0';
            local_168 = CQuickStringW<128>::vftable;
            uVar12 = FUN_1801441e8((longlong)&local_168,pwVar23,
                                   (ulonglong)*(ushort *)((longlong)plVar21 + 6),0x80);
            local_1c8 = (uint)uVar12;
            puVar13 = (undefined8 *)(uVar12 & 0xffffffff);
            pwVar9 = local_160;
            if (-1 < (int)local_1c8) {
              if (local_1b0 == (undefined8 *)0x0) goto LAB_1800301ff;
              puVar16 = &DAT_1801810bc;
              if ((ushort *)*local_1b0 != (ushort *)0x0) {
                puVar16 = (ushort *)*local_1b0;
              }
              pwVar11 = L"";
              if (local_160 != (wchar_t *)0x0) {
                pwVar11 = local_160;
              }
              lVar14 = (longlong)pwVar11 - (longlong)puVar16;
              do {
                uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
                iVar17 = *puVar16 - uVar8;
                if (iVar17 != 0) break;
                puVar16 = puVar16 + 1;
              } while (uVar8 != 0);
              goto joined_r0x000180030219;
            }
            goto joined_r0x00018002fc0c;
          }
          break;
        case 0x21a:
          if (((local_1b0 != (undefined8 *)0x0) &&
              (*(short *)(local_1b0 + 1) == *(short *)((longlong)plVar21 + 6))) ||
             ((*(short *)((longlong)plVar21 + 6) == -2 && (local_1b0 == (undefined8 *)0x0)))) {
            puVar16 = &DAT_1801810bc;
            if ((ushort *)*puVar19 != (ushort *)0x0) {
              puVar16 = (ushort *)*puVar19;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)puVar16;
            do {
              uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
              iVar17 = *puVar16 - uVar8;
              if (iVar17 != 0) goto LAB_18002f4b7;
              puVar16 = puVar16 + 1;
            } while (uVar8 != 0);
            bVar25 = true;
            goto LAB_18002f40a;
          }
          break;
        case 0x21b:
          uVar3 = *(ushort *)((longlong)plVar21 + 6);
          pwVar9 = pwVar23 + uVar3;
          if (puVar22 == (undefined8 *)0x0) {
            pwVar11 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar11 = pwVar9;
            }
            iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
            if (iVar17 != 0) goto LAB_18002fc21;
          }
          else {
            pwVar11 = L"";
            if ((wchar_t *)*puVar22 != (wchar_t *)0x0) {
              pwVar11 = (wchar_t *)*puVar22;
            }
            pwVar10 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar10 = pwVar9;
            }
            lVar14 = (longlong)pwVar10 - (longlong)pwVar11;
            do {
              wVar4 = *pwVar11;
              wVar5 = *(wchar_t *)((longlong)pwVar11 + lVar14);
              if (wVar4 != wVar5) break;
              pwVar11 = pwVar11 + 1;
            } while (wVar5 != L'\0');
            if (wVar4 != wVar5) break;
          }
          local_160 = local_150;
          local_158 = 0x80000000;
          local_150[0] = L'\0';
          local_168 = CQuickStringW<128>::vftable;
          uVar12 = FUN_1801441e8((longlong)&local_168,pwVar23,(ulonglong)uVar3,0x80);
          local_1c8 = (uint)uVar12;
          puVar13 = (undefined8 *)(uVar12 & 0xffffffff);
          pwVar9 = local_160;
          if (-1 < (int)local_1c8) {
            puVar16 = &DAT_1801810bc;
            if ((ushort *)*puVar19 != (ushort *)0x0) {
              puVar16 = (ushort *)*puVar19;
            }
            pwVar9 = L"";
            if (local_160 != (wchar_t *)0x0) {
              pwVar9 = local_160;
            }
            lVar14 = (longlong)pwVar9 - (longlong)puVar16;
            do {
              uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
              iVar17 = *puVar16 - uVar8;
              if (iVar17 != 0) break;
              puVar16 = puVar16 + 1;
            } while (uVar8 != 0);
LAB_18002fedb:
            pwVar9 = local_160;
            if (iVar17 == 0) {
              sVar24 = *(short *)((longlong)local_1c0 + 4);
            }
          }
          goto joined_r0x00018002fc0c;
        case 0x21c:
          if (puVar22 == (undefined8 *)0x0) {
            if (*(short *)((longlong)plVar21 + 6) == -2) goto LAB_18003012e;
          }
          else if (*(short *)(puVar22 + 1) == *(short *)((longlong)plVar21 + 6)) {
LAB_18003012e:
            puVar16 = &DAT_1801810bc;
            if ((ushort *)*puVar19 != (ushort *)0x0) {
              puVar16 = (ushort *)*puVar19;
            }
            pwVar9 = L"";
            if (pwVar23 != (wchar_t *)0x0) {
              pwVar9 = pwVar23;
            }
            lVar14 = (longlong)pwVar9 - (longlong)puVar16;
            do {
              uVar8 = (uint)*(ushort *)((longlong)puVar16 + lVar14);
              iVar17 = *puVar16 - uVar8;
              if (iVar17 != 0) goto LAB_18002f4b7;
              puVar16 = puVar16 + 1;
            } while (uVar8 != 0);
            bVar25 = true;
            goto LAB_18002f40a;
          }
          break;
        case 0x21d:
          uVar3 = *(ushort *)((longlong)plVar21 + 6);
          pwVar9 = pwVar23 + uVar3;
          if (local_1b0 == (undefined8 *)0x0) {
            pwVar11 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar11 = pwVar9;
            }
            iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
            if (iVar17 != 0) goto LAB_18002fc21;
          }
          else {
            pwVar11 = L"";
            if ((wchar_t *)*local_1b0 != (wchar_t *)0x0) {
              pwVar11 = (wchar_t *)*local_1b0;
            }
            pwVar10 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar10 = pwVar9;
            }
            lVar14 = (longlong)pwVar10 - (longlong)pwVar11;
            do {
              wVar4 = *pwVar11;
              wVar5 = *(wchar_t *)((longlong)pwVar11 + lVar14);
              if (wVar4 != wVar5) break;
              pwVar11 = pwVar11 + 1;
            } while (wVar5 != L'\0');
            if (wVar4 != wVar5) break;
          }
          local_160 = local_150;
          local_158 = 0x80000000;
          local_150[0] = L'\0';
          local_168 = CQuickStringW<128>::vftable;
          uVar12 = FUN_1801441e8((longlong)&local_168,pwVar23,(ulonglong)uVar3,0x80);
          pwVar9 = local_160;
          local_1c8 = (uint)uVar12;
          puVar13 = (undefined8 *)(uVar12 & 0xffffffff);
          if (-1 < (int)local_1c8) {
            if (puVar7 == (undefined8 *)0x0) {
              pwVar11 = L"";
              if (local_160 != (wchar_t *)0x0) {
                pwVar11 = local_160;
              }
              iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
              puVar13 = (undefined8 *)(ulonglong)local_1c8;
              if (iVar17 == 0) goto LAB_18002fc4c;
            }
            else {
              pwVar11 = L"";
              if ((wchar_t *)*puVar7 != (wchar_t *)0x0) {
                pwVar11 = (wchar_t *)*puVar7;
              }
              pwVar10 = L"";
              if (local_160 != (wchar_t *)0x0) {
                pwVar10 = local_160;
              }
              lVar14 = (longlong)pwVar10 - (longlong)pwVar11;
              do {
                wVar4 = *pwVar11;
                wVar5 = *(wchar_t *)((longlong)pwVar11 + lVar14);
                if (wVar4 != wVar5) break;
                pwVar11 = pwVar11 + 1;
              } while (wVar5 != L'\0');
              if (wVar4 == wVar5) {
LAB_18002fc4c:
                sVar24 = *(short *)((longlong)local_1c0 + 4);
              }
            }
          }
          goto joined_r0x00018002fc0c;
        case 0x21e:
          uVar3 = *(ushort *)((longlong)plVar21 + 6);
          pwVar9 = pwVar23 + uVar3;
          if (puVar22 == (undefined8 *)0x0) {
            pwVar11 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar11 = pwVar9;
            }
            iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
            if (iVar17 != 0) goto LAB_18002fc21;
          }
          else {
            pwVar11 = L"";
            if ((wchar_t *)*puVar22 != (wchar_t *)0x0) {
              pwVar11 = (wchar_t *)*puVar22;
            }
            pwVar10 = L"";
            if (pwVar9 != (wchar_t *)0x0) {
              pwVar10 = pwVar9;
            }
            lVar14 = (longlong)pwVar10 - (longlong)pwVar11;
            do {
              wVar4 = *pwVar11;
              wVar5 = *(wchar_t *)((longlong)pwVar11 + lVar14);
              if (wVar4 != wVar5) break;
              pwVar11 = pwVar11 + 1;
            } while (wVar5 != L'\0');
            if (wVar4 != wVar5) break;
          }
          local_160 = local_150;
          local_158 = 0x80000000;
          local_150[0] = L'\0';
          local_168 = CQuickStringW<128>::vftable;
          uVar12 = FUN_1801441e8((longlong)&local_168,pwVar23,(ulonglong)uVar3,0x80);
          pwVar9 = local_160;
          local_1c8 = (uint)uVar12;
          puVar13 = (undefined8 *)(uVar12 & 0xffffffff);
          if (-1 < (int)local_1c8) {
            if (local_1b8 == (undefined8 *)0x0) {
              pwVar11 = L"";
              if (local_160 != (wchar_t *)0x0) {
                pwVar11 = local_160;
              }
              iVar17 = wcscmp(L"S-T-A-R-T",pwVar11);
              puVar13 = (undefined8 *)(ulonglong)local_1c8;
              if (iVar17 == 0) goto LAB_18002fde3;
            }
            else {
              pwVar11 = L"";
              if ((wchar_t *)*local_1b8 != (wchar_t *)0x0) {
                pwVar11 = (wchar_t *)*local_1b8;
              }
              pwVar10 = L"";
              if (local_160 != (wchar_t *)0x0) {
                pwVar10 = local_160;
              }
              lVar14 = (longlong)pwVar10 - (longlong)pwVar11;
              do {
                wVar4 = *pwVar11;
                wVar5 = *(wchar_t *)((longlong)pwVar11 + lVar14);
                if (wVar4 != wVar5) break;
                pwVar11 = pwVar11 + 1;
              } while (wVar5 != L'\0');
              if (wVar4 == wVar5) {
LAB_18002fde3:
                sVar24 = *(short *)((longlong)local_1c0 + 4);
              }
            }
          }
joined_r0x00018002fc0c:
          local_168 = CQuickStringTBase::vftable;
          plVar21 = local_1c0;
          if ((local_158 & 0x80000000) == 0) {
            local_168 = CQuickStringTBase::vftable;
            _o_free(pwVar9);
LAB_18002fc21:
            puVar13 = (undefined8 *)(ulonglong)local_1c8;
            plVar21 = local_1c0;
          }
        }
switchD_18002f1a8_caseD_208:
        if (sVar24 != *(short *)(puVar19 + 1)) {
          *(short *)(puVar19 + 1) = sVar24;
        }
LAB_18002f084:
        if ((int)puVar13 < 0) break;
LAB_18002f08e:
        puVar18 = local_1b0;
        puVar6 = local_1b8;
        local_1b0 = puVar7;
        local_1b8 = puVar22;
        local_1a0 = puVar19;
        if (puVar20 == (undefined8 *)0x0) {
          puVar7 = (undefined8 *)0x0;
        }
        else {
          puVar7 = (undefined8 *)puVar20[10];
        }
      }
      plVar21 = (longlong *)((longlong)plVar21 + 0xc);
    } while (-1 < (int)puVar13);
  }
  return puVar13;
}


