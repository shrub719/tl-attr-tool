#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

long getBytes(char *str, size_t start, size_t len) {
    char byteString[len*2];
    long attr;

    memcpy(byteString, str+start*2, len*2);
    attr = strtol(byteString, NULL, 16);

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

