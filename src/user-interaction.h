#ifndef USER_INTERACTION_H   // If not defined
#define USER_INTERACTION_H   // Define it

#include <stdbool.h>

typedef enum {
    PLUS,
    MULTIPLY,
    MINUS,
    DIVIDE,
    DECIMAL_POINT,
    EXPONENTIAL,
    SHIFT_ON,
    SHIFT_OFF,
    END_INPUT,
    UNDO_LAST,
    CLEAR,
} SpecialKeyFunctions;

typedef struct {
    char key;
    bool has_display;
    bool has_shift_function;
    char normal_display;
    SpecialKeyFunctions normal_function;
    char shift_display;
    SpecialKeyFunctions shift_function;
} SpecialKey;


#define KEYPAD_UNKOWN_KEY '\0'
#define MAX_SPECIAL_KEYS 7
#define UKNOWN_SPECIAL_KEY ((SpecialKey){KEYPAD_UNKOWN_KEY})

extern const SpecialKey KEYPAD_SPECIAL_KEYS[MAX_SPECIAL_KEYS];


SpecialKey KeypadFindSpecialKey(char key);


#endif