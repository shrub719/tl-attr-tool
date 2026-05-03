#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "attributes.h"

long getBytes(char *str, size_t start, size_t len) {
    char byteString[2];
    long attr = 0;

    for (int i = 0; i < len; i++) {
        char *byteStart = str + (start + i) * 2;
        memcpy(byteString, byteStart, 2);
        // printf("byte %d: %s (shifted %d)\n", i, byteString, (int)(i));
        attr += strtol(byteString, NULL, 16) << (i * 8);
    }

    // printf("attribute: %lx\n", attr);
    return attr;
}

void writeBytes(char *str, long data, size_t len) {
    char dataStr[50];
    uint8_t byte;
    
    for (int i = 0; i < len; i++) {
        byte = (data >> (i * 8)) % 0x100;
        sprintf(dataStr + (i * 2), "%02X", byte);
    }

    dataStr[len*2] = '\0';

    strcpy(str, dataStr);
}

void extract(char *msbpFilename, char *msbtFilename, char *outputFilename) {
    FILE *msbtPtr = fopen(msbtFilename, "r");
    FILE *outPtr = fopen(outputFilename, "w");

    AttrSet attrSet = getDefinitions(msbpFilename);
    char previousBuff[200];
    char buff[200];

    while (fgets(buff, 200, msbtPtr)) {
        if (strlen(buff) >= 10 && (strncmp("attribute:", buff, 10) == 0)) {
            char* label = previousBuff + 7;
            label[strlen(label) - 1] = '\0';
            char* attrStr = buff + 13;
            
            fprintf(outPtr, "[%s]\n", label);
            for (int i = 0; i < attrSet.len; i++) {
                Attr attr = attrSet.attributes[i];

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
    }

    fclose(msbtPtr);
    fclose(outPtr);
}

void replace(char *msbpFilename, char *attrFilename, char *msbtFilename, char *outputFilename) {
    FILE *attrPtr = fopen(attrFilename, "r");
    FILE *msbtPtr = fopen(msbtFilename, "r");
    FILE *outPtr = fopen(outputFilename, "w");

    AttrSet attrSet = getDefinitions(msbpFilename);
    char previousBuff[200];
    char buff[200];
    char attrStr[200];
    char attrBuff[200];

    while (fgets(buff, 200, msbtPtr)) {
        if (strlen(buff) >= 10 && ( strncmp("attribute:", buff, 10) == 0 )) {
            /* check labels?
            char* label = previousBuff + 7;
            label[strlen(label) - 1] = '\0';
            */
            char *attrStrPtr = attrStr; // fuckk
            fgets(attrBuff, 200, attrPtr);  // skip label

            for (int i = 0; i < attrSet.len; i++) {
                Attr attr = attrSet.attributes[i];

                fgets(attrBuff, 200, attrPtr);
                char *dataStr = strchr(attrBuff, '=') + 1;

                switch (attr.type) {
                    case UINT16_T:
                        /* could also check name
                        fprintf(outPtr, "%s = %d\n", attr.name,
                            (uint16_t)getBytes(attrStr, attr.start, 2)
                        );
                        */
                        // i don't think i can just do atoi on all of these forever
                        writeBytes(attrStrPtr, atoi(dataStr), 2);
                        attrStrPtr += 4;
                        break;
                    case INT32_T:
                        writeBytes(attrStrPtr, atoi(dataStr), 4);
                        attrStrPtr += 8;
                        break;
                    case BYTE:
                        writeBytes(attrStrPtr, atoi(dataStr), 1);
                        attrStrPtr += 2;
                        break;
                }
            }

            fgets(attrBuff, 200, attrPtr);  // skip newline

            fprintf(outPtr, "attribute: 0x%s\n", attrStr);
        } else {
            fprintf(outPtr, "%s", buff);
        }
        
        strcpy(previousBuff, buff);
    }

    fclose(attrPtr);
    fclose(msbtPtr);
    fclose(outPtr);
}

int main(int argc, char **argv) {
    char *command = argv[1];

    if (strlen(command) >= 7 && (strncmp("extract", command, 7) == 0)) {
        char *msbpFilename = argv[2];
        char *msbtFilename = argv[3];
        char *outputFilename = argv[4];
        extract(msbpFilename, msbtFilename, outputFilename);
    } else if (strlen(command) >= 5 && (strncmp("merge", command, 5) == 0)) {
        char *msbpFilename = argv[2];
        char *attrFilename = argv[3];
        char *msbtFilename = argv[4];
        char *outputFilename = argv[5];
        replace(msbpFilename, attrFilename, msbtFilename, outputFilename);
    }

    return 0;
}
