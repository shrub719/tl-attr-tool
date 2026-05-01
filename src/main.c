#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

long getBytes(char *str, size_t start, size_t len) {
    char byteString[2];
    long attr = 0;

    for (int i = 0; i < len; i ++) {
        char *byteStart = str + (start + i) * 2;
        memcpy(byteString, byteStart, 2);
        //printf("byte %d: %s (shifted %d)\n", i, byteString, (int)(i));
        attr += strtol(byteString, NULL, 16) << (i * 3);
    }

    return attr;
}

int main(int argc, char **argv) {
    FILE *fptr = fopen(argv[1], "r");

    char buff[200];

    while (fgets(buff, 200, fptr)) {
        if (strlen(buff) >= 4 && ( strncmp("attr", buff, 4) == 0 )) {
            char* attrStr = buff + 13;

            uint16_t startTick = (uint16_t)getBytes(attrStr, 0, 2);
            printf("StartTick: %d\n", startTick);

            uint32_t offsetTick = (int32_t)getBytes(attrStr, 2, 4);
            printf("OffsetTick: %d\n", offsetTick);

            printf("\n");
        }
    };

    fclose(fptr);

    return 0;
}
