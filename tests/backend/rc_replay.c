/* rc_replay: replay the CRateChanger calls ('RSPD', 'RPRC' records) of zbtap logs through zb_ratechg.c and compare the
 * outputs sample by sample (one rate changer per log, persisting across the log's utterances).
 * Usage: rc_replay log.bin [log.bin ...] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/zb_ratechg.h"
int main(int argc, char **argv)
{
    int a, calls = 0, bad = 0;
    for (a = 1; a < argc; a++) {
        FILE *f = fopen(argv[a], "rb");
        ZbRateChg *r;
        long sz, o = 0;
        unsigned char *d;
        if (!f) continue;
        r = zb_rc_create(16000);
        fseek(f, 0, SEEK_END); sz = ftell(f); fseek(f, 0, SEEK_SET);
        d = (unsigned char *)malloc((size_t)sz);
        if (fread(d, 1, (size_t)sz, f) != (size_t)sz) sz = 0;
        fclose(f);
        while (o + 8 <= sz) {
            unsigned n = *(unsigned *)(d + o + 4);
            unsigned char *b = d + o + 8;
            if (!memcmp(d + o, "RSPD", 4)) { double sp; memcpy(&sp, b, 8); zb_rc_set_speed(r, sp); }
            else if (!memcmp(d + o, "RPRC", 4)) {
                int *h = (int *)b, nin = h[0], fl = h[1], nout = h[2], got, k, first = -1;
                short *in = (short *)(b + 12), *ref = in + (nin > 0 ? nin : 0);
                short *buf = (short *)malloc(sizeof(short) * (size_t)(zb_rc_max_out(r, nin) + 16));
                got = zb_rc_process(r, nin > 0 ? in : NULL, nin, buf, fl);
                for (k = 0; k < got && k < nout; k++) if (buf[k] != ref[k]) { first = k; break; }
                calls++;
                if (got != nout || first >= 0) { bad++; printf("%s call %d: nin %d fl %d nout %d got %d first diff %d\n", argv[a], calls, nin, fl, nout, got, first); }
                free(buf);
            }
            o += 8 + n;
        }
        zb_rc_free(r);
        free(d);
    }
    printf("%d/%d CRateChanger calls match\n", calls - bad, calls);
    return bad != 0;
}
