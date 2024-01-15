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
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '+',
        .normalFunction = OPERATION,
        .shiftDisplay = 'x',
        .shiftFunction = OPERATION
    },
    {
        .key = 'B',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '-',
        .normalFunction = OPERATION,
        .shiftDisplay = '/',
        .shiftFunction = OPERATION
    },
    {
        .key = 'C',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '.',
        .normalFunction = DECIMAL_POINT,
        .shiftDisplay = 'E',
        .shiftFunction = OPERATION

    },
    {
        .key = 'D',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_STATUS,
        .shiftDisplayType = DISPLAY_STATUS,
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
        .normalDisplayType = DISPLAY_NONE,
        .shiftDisplayType = DISPLAY_NONE,
        // .isSpecial = true,
        // .hasDisplay = false,
        // .hasShiftFunction = true,
        .normalDisplay = KEYPAD_UNKOWN_KEY,
        .normalFunction = END_INPUT,
        .shiftDisplay = KEYPAD_UNKOWN_KEY,
        .shiftFunction = OPEN_CHANGE_PASSWORD
    },
    {
        .key = '#',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NONE,
        .shiftDisplayType = DISPLAY_NONE,
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
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '0',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = 'A',
        .shiftFunction = PAST_ANSWER
    },
    {
        .key = '7',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '7',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = '(',
        .shiftFunction = OPERATION
    },
        {
        .key = '5',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '5',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = '^',
        .shiftFunction = OPERATION
    },
        {
        .key = '9',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NORMAL,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '9',
        .normalFunction = NORMAL_NUMBER,
        .shiftDisplay = ')',
        .shiftFunction = OPERATION
    },
            {
        .key = '1',
        .isSpecial = true,
        .normalDisplayType = DISPLAY_NORMAL,
        .shiftDisplayType = DISPLAY_NONE,
        // .isSpecial = true,
        // .hasDisplay = true,
        // .hasShiftFunction = true,
        .normalDisplay = '1',
        .normalFunction = NORMAL_NUMBER,
        .shiftFunction = GO_BACK
    }
};

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
char KeypadWaitForChar() {
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

KeyInfo KeypadCreateDefaulteKey(char key){
    return (KeyInfo) { 
        .isSpecial = false, 
        .normalDisplayType = DISPLAY_NORMAL, 
        .shiftDisplayType = DISPLAY_NORMAL, 
        .key = key, 
        .normalDisplay = key, 
        .normalFunction = NORMAL_NUMBER, 
        .shiftDisplay = key, 
        .shiftFunction = NORMAL_NUMBER, 
    };
}

KeyInfo KeypadWaitForKeyInfo(){
    char key = KeypadWaitForChar();

    KeyInfo specialKey = KeypadFindSpecialKey(key);

    if(KeyIsValid(specialKey)){ // pressed key is a special key
        return specialKey;
    }

    return KeypadCreateDefaulteKey(key);
}