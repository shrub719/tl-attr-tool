#include <stdlib.h>
#include "attributes.h"

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
    { "Food", 3, {  // i don't know why i made this
        { "FileID", 0, UINT16_T },
        { "Shop", 22, BYTE },
        { "FoodQuantity", 30, BYTE }    // FoodQuantity doesnt seem to work?
    }}
};

