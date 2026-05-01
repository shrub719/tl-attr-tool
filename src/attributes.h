typedef enum {
    UINT16_T,
    INT32_T,
    BYTE
} AttrType;

typedef struct {
    char* name;
    size_t start;
    AttrType type;
} Attr;

typedef struct {
    char* name;
    size_t len;
    Attr attributes[32];
} AttrSet;

extern const AttrSet attributeSets[];

