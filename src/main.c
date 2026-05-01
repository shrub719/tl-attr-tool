#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "attributes.h"

long getBytes(char *str, size_t start, size_t len) {
    char byteString[2];
    long attr = 0;

    for (int i = 0; i < len; i ++) {
        char *byteStart = str + (start + i) * 2;
        memcpy(byteString, byteStart, 2);
        // printf("byte %d: %s (shifted %d)\n", i, byteString, (int)(i));
        attr += strtol(byteString, NULL, 16) << (i * 8);
    }

    // printf("attribute: %lx\n", attr);
    return attr;
}

int main(int argc, char **argv) {
    FILE *fptr = fopen(argv[1], "r");
    int setID = atoi(argv[2]);

    char buff[200];

    while (fgets(buff, 200, fptr)) {
        if (strlen(buff) >= 10 && ( strncmp("attribute:", buff, 10) == 0 )) {
            char* attrStr = buff + 13;
            
            for (int i = 0; i < attributeSets[setID].len; i++) {
                Attr attr = attributeSets[setID].attributes[i];

                switch (attr.type) {
                    case UINT16_T:
                        printf("%s: %d\n", attr.name,
                            (uint16_t)getBytes(attrStr, attr.start, 2)
                        );
                        break;
                    case INT32_T:
                        printf("%s: %d\n", attr.name, 
                            (int32_t)getBytes(attrStr, attr.start, 4)
                        );
                        break;
                    case BYTE:
                        printf("%s: %d\n", attr.name, 
                            (uint8_t)getBytes(attrStr, attr.start, 1)
                        );
                        break;
                }
            }

            printf("\n");
        }
    };

    fclose(fptr);

    return 0;
}
