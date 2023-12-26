#include "keypad.h"
#include "ports.h"
#include "clock.h"
#include "stdbool.h"

const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

const KeyInfo KEYPAD_SPECIAL_KEYS[KEYPAD_MAX_SPECIAL_KEYS] = {
    {
        .key = 'A',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '+',
        .normalFunction = PLUS,
        .shiftDisplay = 'x',
        .shiftFunction = MULTIPLY
    },
    {
        .key = 'B',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '-',
        .normalFunction = MINUS,
        .shiftDisplay = '/',
        .shiftFunction = DIVIDE
    },
    {
        .key = 'C',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '.',
        .normalFunction = DECIMAL_POINT,
        .shiftDisplay = 'E',
        .shiftFunction = EXPONENTIAL

    },
    {
        .key = 'D',
        .isSpecial = true,
        .displayOnInput = false,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = false,
        // .hasShiftFunction = true,
        .normalDisplay = SHIFT_CHAR,
        .normalFunction = SHIFT_ON,
        .shiftDisplay = ' ',
        .shiftFunction = SHIFT_OFF
    },
    {
        .key = '*',
        .isSpecial = true,
        .displayOnInput = false,
        .hasAnyDisplay = false,
        // .isSpecial = true,
        // .hasDisplay = false,
        // .hasShiftFunction = true,
        .normalDisplay = KEYPAD_UNKOWN_KEY,
        .normalFunction = END_INPUT,
        .shiftDisplay = KEYPAD_UNKOWN_KEY,
        .shiftFunction = OPEN_SETTINGS
    },
    {
        .key = '#',
        .isSpecial = true,
        .displayOnInput = false,
        .hasAnyDisplay = false,
        // .isSpecial = true,
        // .hasDisplay = false,
        // .hasShiftFunction = true,
        .normalDisplay = KEYPAD_UNKOWN_KEY,
        .normalFunction = CLEAR_LAST,
        .shiftDisplay = KEYPAD_UNKOWN_KEY,
        .shiftFunction = CLEAR_ALL
    },
    {
        .key = '0',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '0',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = 'A',
        .shiftFunction = LAST_ANSWER
    },
    {
        .key = '7',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '7',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = '(',
        .shiftFunction = OPEN_PARENTHESIS
    },
        {
        .key = '5',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '5',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = '^',
        .shiftFunction = POWER_TO
    },
        {
        .key = '9',
        .isSpecial = true,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '9',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = ')',
        .shiftFunction = CLOSE_PARENTHESIS
    }
};

bool shiftIsOn = false;

bool KeyIsValid(KeyInfo key){
    return key.key != KEYPAD_UNKOWN_KEY;
}

KeyInfo KeypadFindSpecialKey(char key){
    for(int i = 0; i < KEYPAD_MAX_SPECIAL_KEYS; i++){
        if(KEYPAD_SPECIAL_KEYS[i].key == key){
            return KEYPAD_SPECIAL_KEYS[i];
        }
    }

    return (KeyInfo){.key = KEYPAD_UNKOWN_KEY};
}

void KeypadInit(){
    PortDInit();
    PortEInit();
}

// Function to read the pressed key's position
char KeypadGetChar() {
    while (1) {
        for (int col = 0; col < 4; col++) {
            // Set the current column to HIGH
            KEYPAD_COL_PIN = (1 << col);
            DelayMicro(2);

            // Check each row
            for (int row = 0; row < 4; row++) {
                if (KEYPAD_ROW_PIN & (1 << row)) {
                    return KEYPAD_KEYS[row][col];
                }
            }

            KEYPAD_COL_PIN = 0x00;
        }
    }
}

KeyInfo KeypadWaitForInput(){
    char key = KeypadGetChar();

    KeyInfo specialKey = KeypadFindSpecialKey(key);

    if(KeyIsValid(specialKey)){ // pressed key is a special key
        return specialKey;
    }

    return (KeyInfo) {
        .isSpecial = false,
        .displayOnInput = true,
        .hasAnyDisplay = true,
        .key = key,
        .normalDisplay = key,
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = key,
        .shiftFunction = NORMAL_NUMBER,
    };
}