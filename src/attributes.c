#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "attributes.h"

// this cannot be the way to return it
AttrSet getDefinitions(char *msbpFilename) {
    FILE *msbpPtr = fopen(msbpFilename, "r");

    AttrSet attrSet;

    strcpy(attrSet.name, "Generated");
    attrSet.len = 0;
    char buff[300];
    char nextBuff[300];
    bool reachedDefinitions = false;
    bool reachedEnd = false;

    fgets(buff, 300, msbpPtr);

    while (fgets(nextBuff, 300, msbpPtr) && !reachedEnd) {
        if (!reachedDefinitions) {
            if (strlen(buff) >= 21 && (strncmp("Attribute Definitions", buff, 21) == 0)) {
                reachedDefinitions = true;
            }
        } else {
            if (strlen(buff) >= 1 && (strncmp("\n", buff, 1) == 0)) {
                reachedEnd = true;
            } else if (strlen(buff) >= 1 && (strncmp("=", buff, 1) != 0)) {
                int i = attrSet.len;
                char name[50];
                char type[50];
                size_t start;

                // what the hell is sscanf
                sscanf(buff, "%49s [%49[^]]][%zu]", name, type, &start);
                
                strcpy(attrSet.attributes[i].name, name);
                attrSet.attributes[i].start = start;

                if (strcmp("Int16", type) == 0) {
                    attrSet.attributes[i].type = INT16;
                // } else if (strcmp("Enum", type) == 0) {
                //     attrSet.attributes[i].type = BYTE;
                } else if (strcmp("Byte", type) == 0) {
                    attrSet.attributes[i].type = BYTE;
                } else if (strcmp("UInt32", type) == 0) {
                    attrSet.attributes[i].type = UINT32;
                } else if (strcmp("UInt16", type) == 0) {
                    attrSet.attributes[i].type = UINT16;
                } else if (strcmp("Int32", type) == 0) {
                    attrSet.attributes[i].type = INT32;
                // } else if (strcmp("String", type) == 0) {
                //     attrSet.attributes[i].type = INT32;
                } else {
                    // should probably handle strings properly
                    // maybe even enums! altho they're p much always bytes
                    size_t end;
                    sscanf(nextBuff, "%49s [%49[^]]][%zu]", name, type, &end);
                    size_t len = end - start;

                    attrSet.attributes[i].type = getType(len);
                }

                attrSet.len++;
            }
        }
        strcpy(buff, nextBuff);
    }

    fclose(msbpPtr);

    return attrSet;
}

size_t getLength(AttrType type) {
    switch (type) {
        case UINT32: return 4;
        case INT32: return 4;
        case UINT16: return 2;
        case INT16: return 2;
        case BYTE: return 1;
        case IDK4: return 4;
        case IDK2: return 2;
        case IDK1: return 1;
        default: return 1;
    }
}

AttrType getType(size_t length) {
    switch (length) {
        case 1: return IDK1;
        case 2: return IDK2;
        case 4: return IDK4;
        default: return IDK1;
    }
}

/*
const AttrSet attributeSets[] = {
    { "Song", 32, {
        { "StartTick", 0, UINT16 },
        { "OffsetTick", 2, INT32 },
        { "Speed", 6, UINT16 },
        { "WordNum", 8, BYTE },
        { "WordType0", 9, BYTE },
        { "WordType1", 10, BYTE },
        { "WordType2", 11, BYTE },
        { "WordType3", 12, BYTE },
        { "WordType4", 13, BYTE },
        { "WordType5", 14, BYTE },
        { "WordType6", 15, BYTE },
        { "WordType7", 16, BYTE },
        { "WordType8", 17, BYTE },
        { "WordType9", 18, BYTE },
        { "WordDefault0", 19, UINT16 },
        { "WordDefault1", 21, UINT16 },
        { "WordDefault2", 23, UINT16 },
        { "WordDefault3", 25, UINT16 },
        { "WordDefault4", 27, UINT16 },
        { "WordDefault5", 29, UINT16 },
        { "WordDefault6", 31, UINT16 },
        { "WordDefault7", 33, UINT16 },
        { "WordDefault8", 35, UINT16 },
        { "WordDefault9", 37, UINT16 },
        { "Line", 39, BYTE },
        { "Singer2", 40, INT32 }, // actually String, not this
        { "Singer3", 44, INT32 },
        { "Singer4", 48, INT32 },
        { "Singer5", 52, INT32 },
        { "Singer6", 56, INT32 },
        { "Singer7", 60, INT32 },
        { "PhraseLength", 64, UINT16 }
    }},
    { "Item", 88, {  // i don't know why i made this
        { "FileID", 0, UINT16 },
        { "RegionJP", 2, BYTE },
        { "RegionUS", 3, BYTE },
        { "RegionEU", 4, BYTE },
        { "RegionKR", 5, BYTE },
        { "Price", 6, INT32 },
        { "PriceUS", 10, INT32 },
        { "PriceEU", 14, INT32 },
        { "PriceKR", 18, INT32 },
        { "Shop", 22, BYTE },
        { "Mii", 23, BYTE },
        { "Food_FirstDaily", 24, BYTE },
        { "BoxSize", 25, BYTE }, // {BoxSize_None,BoxSize_Nomral,BoxSize_Small,BoxSize_Big}
        { "Effect", 26, BYTE }, // {None,Steam00,Steam01,Steam02}
        { "Foodype_JP", 27, BYTE }, // {Japanese,Western,Alacarte,Dessert,Drink}
        { "Foodype_USEU", 28, BYTE }, // {MainDishes,SmallDishes,Refreshments,Drinks}
        { "Foodype_KR", 29, BYTE }, // {Korean,Foreign,Refreshments,Drink}
        { "Food_Quantity", 30, BYTE }, // {Quantity_None,Quantity_Low,Quantity_Mid,Quantity_High}
        { "Food_Season", 31, BYTE }, // {Season_None,Season_Spring,Season_Summer,Season_Autumn,Season_Winter}
        { "Food_Attr_Sweet", 32, BYTE },
        { "Food_Attr_Spicy", 33, BYTE },
        { "Food_Attr_Salty", 34, BYTE },
        { "Food_Attr_Sour", 35, BYTE },
        { "Food_Attr_Oily", 36, BYTE },
        { "Food_Attr_Cool", 37, BYTE },
        { "Food_Attr_Hot", 38, BYTE },
        { "Food_Attr_Awful", 39, BYTE },
        { "Food_Attr_Confectionery", 40, BYTE },
        { "Food_Attr_Fruit", 41, BYTE },
        { "Food_Attr_Vegetable", 42, BYTE },
        { "Food_Attr_Rice", 43, BYTE },
        { "Food_Attr_Bread", 44, BYTE },
        { "Food_Attr_Meat", 45, BYTE },
        { "Food_Attr_Fish", 46, BYTE },
        { "Food_Attr_Egg", 47, BYTE },
        { "Food_Attr_Japanese", 48, BYTE },
        { "Food_Attr_Western", 49, BYTE },
        { "Food_Attr_Chinese", 50, BYTE },
        { "Food_Attr_Italian", 51, BYTE },
        { "Food_Attr_Noodle", 52, BYTE },
        { "Food_Attr_Luxury", 53, BYTE },
        { "Food_Attr_American", 54, BYTE },
        { "Food_Attr_Asian", 55, BYTE },
        { "Food_Attr_British", 56, BYTE },
        { "Food_Attr_French", 57, BYTE },
        { "Food_Attr_German", 58, BYTE },
        { "Food_Attr_Spanish", 59, BYTE },
        { "Food_Attr_Junk", 60, BYTE },
        { "Food_Attr_Korean", 61, BYTE },
        { "Food_NTR_ID", 62, UINT16 },
        { "Foodaste_A", 64, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Foodaste_B", 65, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Foodaste_C", 66, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Foodaste_D", 67, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Food_Seype", 68, BYTE }, // {SE_MII_DRINK,SE_MII_EAT_01,SE_MII_EAT_02,SE_MII_EAT_03,SE_MII_EAT_04,SE_MII_EAT_05,SE_MII_EAT_06,SE_MII_EAT_07}
        { "RatioA", 69, BYTE },
        { "RatioB", 70, BYTE },
        { "RatioC", 71, BYTE },
        { "RatioD", 72, BYTE },
        { "Treasureype", 73, BYTE }, // {TreasureToken,TreasureSouvenir,TreasureDream,TreasureRare}
        { "Catalog", 74, BYTE }, // {false,true}
        { "Food_Date_Month_JP", 75, BYTE },
        { "Food_Date_Day_JP", 76, BYTE },
        { "Food_Date_Month_US", 77, BYTE },
        { "Food_Date_Day_US", 78, BYTE },
        { "Food_Date_Month_EU", 79, BYTE },
        { "Food_Date_Day_EU", 80, INT32 },
        { "Food_Date_Month_KR", 84, BYTE },
        { "Food_Date_Day_KR", 85, INT32 },
        { "Food_FirstCatalog", 89, BYTE },
        { "ForIslanderOnly", 90, BYTE },
        { "FPriceEU_UK", 91, INT32 },
        { "FPriceEU_AN", 95, INT32 },
        { "FPriceEU_Other", 99, INT32 },
        { "FPriceEU_FR", 103, INT32 },
        { "FPriceEU_IT", 107, INT32 },
        { "FPriceEU_GE", 111, INT32 },
        { "FPriceEU_SP", 115, INT32 },
        { "Food_FirstDaily_US_En", 119, BYTE },
        { "Food_FirstDaily_EU_En", 120, BYTE },
        { "Food_FirstDaily_EU_Fr", 121, BYTE },
        { "Food_FirstDaily_EU_Ge", 122, BYTE },
        { "Food_FirstDaily_EU_It", 123, BYTE },
        { "Food_FirstDaily_EU_Sp", 124, BYTE },
        { "Food_FirstDaily_KR_Kr", 125, BYTE },
        { "Throw_US", 126, BYTE }, // {Disable,Enable}
        { "Throw_EU", 127, BYTE }, // {Disable,Enable}
        { "Throw_KR", 128, BYTE }, // {Disable,Enable}
    }}
};
*/

