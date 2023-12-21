#include "user-interaction.h"

const SpecialKey KEYPAD_SPECIAL_KEYS[MAX_SPECIAL_KEYS] = {
    {
        .key = 'A',
        .has_display = true,
        .has_shift_function = true,
        .normal_display = '+',
        .normal_function = PLUS,
        .shift_display = 'x',
        .shift_function = MULTIPLY
    },
    {
        .key = 'B',
        .has_display = true,
        .has_shift_function = true,
        .normal_display = '-',
        .normal_function = MINUS,
        .shift_display = '/',
        .shift_function = DIVIDE
    },
    {
        .key = 'C',
        .has_display = true,
        .has_shift_function = true,
        .normal_display = '.',
        .normal_function = DECIMAL_POINT,
        .shift_display = 'E',
        .shift_function = EXPONENTIAL

    },
    {
        .key = 'D',
        .has_display = false,
        .has_shift_function = true,
        .normal_function = SHIFT_ON,
        .shift_function = SHIFT_OFF
    },
    {
        .key = '*',
        .has_display = false,
        .has_shift_function = false,
        .normal_function = END_INPUT,
    },
    {
        .key = 'D',
        .has_display = false,
        .has_shift_function = true,
        .normal_function = SHIFT_ON,
        .shift_function = SHIFT_OFF 
    }
};

SpecialKey KeypadFindSpecialKey(char key){
    for(int i = 0; i < MAX_SPECIAL_KEYS; i++){
        if(KEYPAD_SPECIAL_KEYS[i].key == key){
            return KEYPAD_SPECIAL_KEYS[i];
        }
    }

    return UKNOWN_SPECIAL_KEY;
}