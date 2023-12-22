#ifndef KEYPAD_H   // If not defined
#define KEYPAD_H   // Define it

#include <stdbool.h>

// COL 1 -> PD0
// COL 2 -> PD1
// COL 3 -> PD2
// COL 3 -> PD3
#define KEYPAD_COL_PIN (*((volatile unsigned long *)0x4000703C))

// ROW 1 -> PE0
// ROW 2 -> PE1
// ROW 3 -> PE2
// ROW 3 -> PE3
#define KEYPAD_ROW_PIN (*((volatile unsigned long *)0x4002403C))
#define KEYPAD_N 4

#define KEYPAD_UNKOWN_KEY '\0'
#define KEYPAD_MAX_SPECIAL_KEYS 7

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
    bool isSpecial;
    bool hasDisplay;
    bool hasShiftFunction;
    char normalDisplay;
    SpecialKeyFunctions normalFunction;
    char shiftDisplay;
    SpecialKeyFunctions shiftFunction;
} KeyInfo;

extern const KeyInfo KEYPAD_SPECIAL_KEYS[KEYPAD_MAX_SPECIAL_KEYS];

extern const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N];

extern bool shiftIsOn;

KeyInfo KeypadFindSpecialKey(char key);

void KeypadInit();

KeyInfo KeypadWaitForInput();

#endif