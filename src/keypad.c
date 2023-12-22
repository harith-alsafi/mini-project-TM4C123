#include "keypad.h"
#include "ports.h"
#include "clock.h"

const KeyInfo KEYPAD_SPECIAL_KEYS[KEYPAD_MAX_SPECIAL_KEYS] = {
    {
        .key = 'A',
        .isSpecial = true,
        .hasDisplay = true,
        .hasShiftFunction = true,
        .normalDisplay = '+',
        .normalFunction = PLUS,
        .shiftDisplay = 'x',
        .shiftFunction = MULTIPLY
    },
    {
        .key = 'B',
        .isSpecial = true,
        .hasDisplay = true,
        .hasShiftFunction = true,
        .normalDisplay = '-',
        .normalFunction = MINUS,
        .shiftDisplay = '/',
        .shiftFunction = DIVIDE
    },
    {
        .key = 'C',
        .isSpecial = true,
        .hasDisplay = true,
        .hasShiftFunction = true,
        .normalDisplay = '.',
        .normalFunction = DECIMAL_POINT,
        .shiftDisplay = 'E',
        .shiftFunction = EXPONENTIAL

    },
    {
        .key = 'D',
        .isSpecial = true,
        .hasDisplay = false,
        .hasShiftFunction = true,
        .normalFunction = SHIFT_ON,
        .shiftFunction = SHIFT_OFF
    },
    {
        .key = '*',
        .isSpecial = true,
        .hasDisplay = false,
        .hasShiftFunction = false,
        .normalFunction = END_INPUT,
    },
    {
        .key = 'D',
        .isSpecial = true,
        .hasDisplay = false,
        .hasShiftFunction = true,
        .normalFunction = SHIFT_ON,
        .shiftFunction = SHIFT_OFF 
    }
};

bool shiftIsOn = false;

const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

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

    if(specialKey.key != KEYPAD_UNKOWN_KEY){ // pressed key is a special key
        return specialKey;
    }

    return (KeyInfo) {
        .key = key,
        .isSpecial = false,
    };
}