#ifndef KEYPAD_H   // If not defined
#define KEYPAD_H   // Define it

#include <stdbool.h>

// COL 1 -> PD0
// COL 2 -> PD1
// COL 3 -> PD2
// COL 3 -> PD3
#define KEYPAD_COL (*((volatile unsigned long *)0x4000703C))

// ROW 1 -> PE0
// ROW 2 -> PE1
// ROW 3 -> PE2
// ROW 3 -> PE3
#define KEYPAD_ROW (*((volatile unsigned long *)0x4002403C))
#define KEYPAD_N 4

extern const char KEYPAD_KEYS[KEYPAD_N][KEYPAD_N];

void KeypadInit();

char KeypadGetChar();

char KeypadWaitForInput();

bool KeypadIsShiftOn();

#endif