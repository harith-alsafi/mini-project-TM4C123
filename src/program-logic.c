#include "program-logic.h"
#include "clock.h"
#include "lcd.h"
#include "keypad.h"

void InitAll() {
    ClockInit();
    KeypadInit();
	LcdInit();
}
