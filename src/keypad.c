#include "keypad.h"
#include "ports.h"

unsigned char shiftIsOn = 0;

const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

bool KeypadIsShiftOn(){
    return shiftIsOn;
}

void KeypadInit(){
    PortDInit();
    PortEInit();
}

unsigned char KeypadGetRow(){
    return -1;
}

unsigned char KeypadGetCol(){
    return -1;

}

char KeypadGetChar(){
    return -1;

}