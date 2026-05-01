#include <stdlib.h>
#include "attributes.h"

const AttrSet attributeSets[] = {
    { "Song", 5, {
        { "StartTick", 0, UINT16_T },
        { "OffsetTick", 2, INT32_T },
        { "Speed", 6, UINT16_T },
        { "WordNum", 8, BYTE },
        { "PhraseLength", 64, UINT16_T }
    }},
    { "Food", 3, {
        { "FileID", 0, UINT16_T },
        { "Shop", 22, BYTE },
        { "FoodQuantity", 30, BYTE }
    }}
};

