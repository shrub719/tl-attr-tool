typedef enum {
    UINT32,
    INT32,
    UINT16,
    INT16,
    BYTE,
    IDK4,   // unknown with length 4
    IDK2,   // default to int repr i guess
    IDK1,
} AttrType;

typedef struct {
    char name[50];
    size_t start;
    AttrType type;
} Attr;

typedef struct {
    char name[50];
    size_t len;
    Attr attributes[100];
} AttrSet;

AttrSet getDefinitions(char *msbpFilename);

size_t getLength(AttrType type);

AttrType getType(size_t len);

