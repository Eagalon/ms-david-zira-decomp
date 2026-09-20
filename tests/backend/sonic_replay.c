/* sonic_replay: replay the CRateChangerSonic calls ('SSPD', 'SPRC' records) of zbtap logs through zb_sonic.c and
 * compare the outputs sample by sample.  Usage: sonic_replay log.bin [log.bin ...] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/zb_sonic.h"
int main(int argc, char **argv)
{
    int a, calls = 0, bad = 0;
    for (a = 1; a < argc; a++) {
        FILE *f = fopen(argv[a], "rb");
        ZbSonic *s = zb_sonic_create(16000);
        long sz;
        unsigned char *d;
        long o = 0;
        if (!f) continue;
        fseek(f, 0, SEEK_END); sz = ftell(f); fseek(f, 0, SEEK_SET);
        d = malloc(sz); fread(d, 1, sz, f); fclose(f);
        while (o + 8 <= sz) {
            unsigned n = *(unsigned *)(d + o + 4);
            unsigned char *b = d + o + 8;
            if (!memcmp(d + o, "SSPD", 4)) zb_sonic_set_speed(s, *(float *)b);
            else if (!memcmp(d + o, "SPRC", 4)) {
                int *h = (int *)b, nin = h[0], fl = h[1], nout = h[2], got, k, first = -1;
                short *in = (short *)(b + 12), *ref = in + (nin > 0 ? nin : 0), buf[1 << 16];
                if (nin > 0) zb_sonic_write(s, in, nin);
                if (fl == 2) zb_sonic_flush(s);
                got = zb_sonic_read(s, buf, 1 << 16);
                for (k = 0; k < got && k < nout; k++) if (buf[k] != ref[k]) { first = k; break; }
                calls++;
                if (got != nout || first >= 0) { bad++; printf("%s call %d: nin %d fl %d nout %d got %d first diff %d\n", argv[a], calls, nin, fl, nout, got, first); }
            }
            o += 8 + n;
        }
        zb_sonic_free(s);
        free(d);
    }
    printf("%d/%d Sonic calls match\n", calls - bad, calls);
    return bad != 0;
}
