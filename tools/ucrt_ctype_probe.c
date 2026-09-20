#include <stdio.h>
#include <wctype.h>
#include <wchar.h>
#include <ctype.h>
int main(void){ static unsigned char d[8192], s[8192]; FILE*f=fopen("probe.bin","wb");
 for(unsigned c=0;c<65536;c++){ if(iswdigit((wint_t)c)) d[c>>3]|=1<<(c&7); if(iswspace((wint_t)c)) s[c>>3]|=1<<(c&7);}
 fwrite(d,1,8192,f); fwrite(s,1,8192,f); fclose(f);
 printf("wcsnicmp E-acute %d, tolower(0xC9)=%x toupper(0xe9)=%x\n", _wcsnicmp(L"\xC9",L"\xE9",1), tolower(0xC9), toupper(0xe9));
 int n=0; for(unsigned c=128;c<65536;c++) if(iswdigit(c)) n++; printf("nonascii digits %d\n",n);
 n=0; for(unsigned c=128;c<65536;c++) if(iswspace(c)) {n++; printf("%x ",c);} printf("\nnonascii spaces %d\n",n); return 0;}
