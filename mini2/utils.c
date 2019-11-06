#include <string.h>

char* CharToBinary(unsigned char i) {
    static char buf[8];
    memset(buf, '0', sizeof(buf));

    if (i & 1 << 7) {
        buf[0] = '1';
    }

    if (i & 1 << 6) {
        buf[1] = '1';
    }

    if (i & 1 << 5) {
        buf[2] = '1';
    }

    if (i & 1 << 4) {
        buf[3] = '1';
    }

    if (i & 1 << 3) {
        buf[4] = '1';
    }

    if (i & 1 << 2) {
        buf[5] = '1';
    }

    if (i & 1 << 1) {
        buf[6] = '1';
    }

    if (i & 1 << 0) {
        buf[7] = '1';
    }

    return buf;
}
