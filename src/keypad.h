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
#define KEYPAD_MAX_SPECIAL_KEYS 11

typedef enum {
    NORMAL_NUMBER = 0,
    OPERATION = 1,
    DECIMAL_POINT = 2,
    PAST_ANSWER = 3,
    SHIFT_ON = 8,
    SHIFT_OFF = 9,
    END_INPUT = 10,
    CLEAR_LAST = 11,
    CLEAR_ALL = 12,
    OPEN_CHANGE_PASSWORD = 16,
    GO_BACK = 21
} SpecialKeyFunctions;

typedef enum {
    DISPLAY_STATUS,
    DISPLAY_NONE,
    DISPLAY_NORMAL
} KeyDisplayType;

typedef struct {
    char key;
    KeyDisplayType normalDisplayType;
    KeyDisplayType shiftDisplayType;
    bool isSpecial;
    char normalDisplay; // display character
    SpecialKeyFunctions normalFunction; // function when shift is off
    char shiftDisplay; // display character when shift is on
    SpecialKeyFunctions shiftFunction; // function when shift is on
} KeyInfo;

extern const KeyInfo KEYPAD_SPECIAL_KEYS[KEYPAD_MAX_SPECIAL_KEYS];

extern const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N];

/**
 * @brief Creates a default key with default values
 * 
 * @param key 
 * @return `KeyInfo`  <br>
 */
KeyInfo KeypadCreateDefaulteKey(char key);

/**
 * @brief Initializes the keypad 
 * 
 */
void KeypadInit();

/**
 * @brief Finds the KeyInfo of a given key
 * 
 * @param key 
 * @return `KeyInfo`  <br>
 */
KeyInfo KeypadFindSpecialKey(char key);

/**
 * @brief Checks if a given key is valid
 * 
 * @param key 
 * @return `true`  <br>
 * @return `false`  <br>
 */
bool KeyIsValid(KeyInfo key);

/**
 * @brief Gets the character from the keypad
 * 
 * @return `char`  <br>
 */
char KeypadWaitForChar();

/**
 * @brief Waits for a key to be pressed
 * 
 * @return `KeyInfo`  <br>
 */
KeyInfo KeypadWaitForKeyInfo();

#endif