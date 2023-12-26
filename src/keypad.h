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
#define SHIFT_CHAR 0xEF

#define KEYPAD_UNKOWN_KEY '\0'
#define KEYPAD_MAX_SPECIAL_KEYS 10


typedef enum {
    NORMAL_NUMBER = 0,
    DECIMAL_POINT = 1,
    EXPONENTIAL = 2,
    POWER_TO = 3,
    MULTIPLY = 4,
    DIVIDE = 5,
    PLUS = 6,
    MINUS = 7,
    SHIFT_ON = 8,
    SHIFT_OFF = 9,
    END_INPUT = 10,
    CLEAR_LAST = 11,
    CLEAR_ALL = 12,
    LAST_ANSWER = 13,
    OPEN_PARENTHESIS = 14,
    CLOSE_PARENTHESIS = 15,
    OPEN_SETTINGS = 16,
    CURSOR_LEFT = 17,
    CURSOR_RIGHT = 18,
    CURSOR_UP = 19,
    CURSOR_DOWN = 20,
} SpecialKeyFunctions;

typedef struct {
    char key;
    bool displayOnInput;
    bool isSpecial;
    bool hasAnyDisplay;
    bool hasStatusDisplay;
    char normalDisplay; // display character
    SpecialKeyFunctions normalFunction; // function when shift is off
    char shiftDisplay; // display character when shift is on
    SpecialKeyFunctions shiftFunction; // function when shift is on
} KeyInfo;

extern const KeyInfo KEYPAD_SPECIAL_KEYS[KEYPAD_MAX_SPECIAL_KEYS];

extern const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N];

extern bool shiftIsOn;

bool KeyIsValid(KeyInfo key);

KeyInfo KeypadFindSpecialKey(char key);

void KeypadInit();

KeyInfo KeypadWaitForInput();

#endif