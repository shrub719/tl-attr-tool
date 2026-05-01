#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

long getBytes(char *str, size_t start, size_t len) {
    char byteString[2];
    long attr = 0;

    for (int i = 0; i < len; i ++) {
        char *byteStart = str + (start + i) * 2;
        memcpy(byteString, byteStart, 2);
        attr += strtol(byteString, NULL, 16) << ((len - i - 1) * 3);
    }

    return attr;
}

int main(int argc, char **argv) {
    char *attStr = argv[1] + 2;

    uint16_t startTick = (uint16_t)getBytes(attStr, 0, 2);
    printf("StartTick: %d\n", startTick);

    uint32_t offsetTick = (uint32_t)getBytes(attStr, 2, 4);
    printf("OffsetTick: %d\n", offsetTick);

    return 0;
}

