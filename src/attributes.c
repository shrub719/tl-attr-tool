#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "attributes.h"

// this cannot be the way to return it
AttrSet getDefinitions(char *msbpFilename) {
    FILE *msbpPtr = fopen(msbpFilename, "r");

    AttrSet attrSet;

    // segfault between here
    char *nameEnd = strchr(msbpFilename, '.');
    size_t nameLen = (nameEnd - msbpFilename) / sizeof(char);
    strncpy(attrSet.name, msbpFilename, nameLen);
    attrSet.name[nameLen] = '\0';
    // and here

    attrSet.len = 0;
    char buff[200];
    bool reachedDefinitions = false;
    bool reachedEnd = false;

    while (fgets(buff, 200, msbpPtr) && !reachedEnd) {
        if (!reachedDefinitions) {
            if (strlen(buff) >= 21 && (strncmp("Attribute Definitions", buff, 21) == 0)) {
                reachedDefinitions = true;
            }
        } else {
            if (strlen(buff) >= 1 && (strncmp("\n", buff, 1) == 0)) {
                reachedEnd = true;
            } else {
                int i = attrSet.len;
                char name[50];
                char type[50];
                size_t start;

                // what the hell is sscanf
                sscanf(buff, "%49s [%49[^]]][%zu]", name, type, &start);
                
                attrSet.attributes[i].name = name;
                attrSet.attributes[i].start = start;

                if (strcmp("Int16", type) == 0) {
                    attrSet.attributes[i].type = UINT16_T;
                } else if (strcmp("Enum", type) == 0) {
                    attrSet.attributes[i].type = BYTE;
                } else if (strcmp("Byte", type) == 0) {
                    attrSet.attributes[i].type = BYTE;
                } else if (strcmp("UInt32", type) == 0) {
                    attrSet.attributes[i].type = INT32_T;
                } else if (strcmp("UInt16", type) == 0) {
                    attrSet.attributes[i].type = UINT16_T;
                } else if (strcmp("Int32", type) == 0) {
                    attrSet.attributes[i].type = INT32_T;
                } else if (strcmp("String", type) == 0) {
                    attrSet.attributes[i].type = INT32_T;
                } else {
                    // um!
                    attrSet.attributes[i].type = BYTE;
                }

                attrSet.len++;
            }
        }
    }

    fclose(msbpPtr);

    return attrSet;
}

const AttrSet attributeSets[] = {
    { "Song", 32, {
        { "StartTick", 0, UINT16_T },
        { "OffsetTick", 2, INT32_T },
        { "Speed", 6, UINT16_T },
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
        { "WordDefault0", 19, UINT16_T },
        { "WordDefault1", 21, UINT16_T },
        { "WordDefault2", 23, UINT16_T },
        { "WordDefault3", 25, UINT16_T },
        { "WordDefault4", 27, UINT16_T },
        { "WordDefault5", 29, UINT16_T },
        { "WordDefault6", 31, UINT16_T },
        { "WordDefault7", 33, UINT16_T },
        { "WordDefault8", 35, UINT16_T },
        { "WordDefault9", 37, UINT16_T },
        { "Line", 39, BYTE },
        { "Singer2", 40, INT32_T }, // actually String, not this
        { "Singer3", 44, INT32_T },
        { "Singer4", 48, INT32_T },
        { "Singer5", 52, INT32_T },
        { "Singer6", 56, INT32_T },
        { "Singer7", 60, INT32_T },
        { "PhraseLength", 64, UINT16_T }
    }},
    { "Item", 88, {  // i don't know why i made this
        { "FileID", 0, UINT16_T },
        { "RegionJP", 2, BYTE },
        { "RegionUS", 3, BYTE },
        { "RegionEU", 4, BYTE },
        { "RegionKR", 5, BYTE },
        { "Price", 6, INT32_T },
        { "PriceUS", 10, INT32_T },
        { "PriceEU", 14, INT32_T },
        { "PriceKR", 18, INT32_T },
        { "Shop", 22, BYTE },
        { "Mii", 23, BYTE },
        { "Food_FirstDaily", 24, BYTE },
        { "BoxSize", 25, BYTE }, // {BoxSize_None,BoxSize_Nomral,BoxSize_Small,BoxSize_Big}
        { "Effect", 26, BYTE }, // {None,Steam00,Steam01,Steam02}
        { "Food_Type_JP", 27, BYTE }, // {Japanese,Western,Alacarte,Dessert,Drink}
        { "Food_Type_USEU", 28, BYTE }, // {MainDishes,SmallDishes,Refreshments,Drinks}
        { "Food_Type_KR", 29, BYTE }, // {Korean,Foreign,Refreshments,Drink}
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
        { "Food_NTR_ID", 62, UINT16_T },
        { "Food_Taste_A", 64, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Food_Taste_B", 65, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Food_Taste_C", 66, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Food_Taste_D", 67, BYTE }, // {00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15}
        { "Food_Se_Type", 68, BYTE }, // {SE_MII_DRINK,SE_MII_EAT_01,SE_MII_EAT_02,SE_MII_EAT_03,SE_MII_EAT_04,SE_MII_EAT_05,SE_MII_EAT_06,SE_MII_EAT_07}
        { "RatioA", 69, BYTE },
        { "RatioB", 70, BYTE },
        { "RatioC", 71, BYTE },
        { "RatioD", 72, BYTE },
        { "Treasure_Type", 73, BYTE }, // {TreasureToken,TreasureSouvenir,TreasureDream,TreasureRare}
        { "Catalog", 74, BYTE }, // {false,true}
        { "Food_Date_Month_JP", 75, BYTE },
        { "Food_Date_Day_JP", 76, BYTE },
        { "Food_Date_Month_US", 77, BYTE },
        { "Food_Date_Day_US", 78, BYTE },
        { "Food_Date_Month_EU", 79, BYTE },
        { "Food_Date_Day_EU", 80, INT32_T },
        { "Food_Date_Month_KR", 84, BYTE },
        { "Food_Date_Day_KR", 85, INT32_T },
        { "Food_FirstCatalog", 89, BYTE },
        { "ForIslanderOnly", 90, BYTE },
        { "FPriceEU_UK", 91, INT32_T },
        { "FPriceEU_AN", 95, INT32_T },
        { "FPriceEU_Other", 99, INT32_T },
        { "FPriceEU_FR", 103, INT32_T },
        { "FPriceEU_IT", 107, INT32_T },
        { "FPriceEU_GE", 111, INT32_T },
        { "FPriceEU_SP", 115, INT32_T },
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
