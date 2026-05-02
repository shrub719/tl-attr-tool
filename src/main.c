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

void extract(char *msbtFilename, char *outputFilename) {
    FILE *msbtPtr = fopen(msbtFilename, "r");
    FILE *outPtr = fopen(outputFilename, "w");
    int setID = 0;

    char previousBuff[200];
    char buff[200];

    while (fgets(buff, 200, msbtPtr)) {
        if (strlen(buff) >= 10 && ( strncmp("attribute:", buff, 10) == 0 )) {
            char* label = previousBuff + 7;
            label[strlen(label) - 1] = '\0';
            char* attrStr = buff + 13;
            
            fprintf(outPtr, "[%s]\n", label);
            for (int i = 0; i < attributeSets[setID].len; i++) {
                Attr attr = attributeSets[setID].attributes[i];

                switch (attr.type) {
                    case UINT16_T:
                        fprintf(outPtr, "%s = %d\n", attr.name,
                            (uint16_t)getBytes(attrStr, attr.start, 2)
                        );
                        break;
                    case INT32_T:
                        fprintf(outPtr, "%s = %d\n", attr.name, 
                            (int32_t)getBytes(attrStr, attr.start, 4)
                        );
                        break;
                    case BYTE:
                        fprintf(outPtr, "%s = %d\n", attr.name, 
                            (uint8_t)getBytes(attrStr, attr.start, 1)
                        );
                        break;
                }
            }

            fprintf(outPtr, "\n");
        }
        strcpy(previousBuff, buff);
    };

    fclose(msbtPtr);
}

void replace(char *attrFilename, char *msbtFilename, char *outputFilename) {

}

int main(int argc, char **argv) {
    char *command = argv[1];

    if (strlen(command) >= 7 && (strncmp("extract", command, 7) == 0)) {
        char *msbtFilename = argv[2];
        char *outputFilename = argv[3];
        extract(msbtFilename, outputFilename);
    } else if (strlen(command) >= 7 && (strncmp("replace", command, 7) == 0)) {
        char *attrFilename = argv[2];
        char *msbtFilename = argv[3];
        char *outputFilename = argv[4];
        replace(attrFilename, msbtFilename, outputFilename);
    }

    return 0;
}
