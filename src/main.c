#include "clock.h"
#include "lcd.h"
#include "ports.h"

void InitAll() {
    PortAInit();
    PortBInit();
    PLLInit();
    SysTickInit();
	LcdInit();
}

int main() {
    InitAll();
	// DelayMilli(5000);
	// DelayMilli(100);
	// LcdPrintChar('S');
	// LcdPrintChar('A');

    LcdPrintString("Karith Al-Sadi aNd tHuraya gO everywhEre");
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere");

    DelayMilli(3000);

    LcdPrintString("Barith Al-Nadi aNd thuRaya GO eveRywhEre");
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere");

    DelayMilli(3000);

    LcdClearDisplay();

    LcdPrintString("Jarith Al-Qadi ANd thuRAya Go EveRywhEre");
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere");


    // LcdSetCursor(0, 0);
    // LcdPrintString("Harith Al-Safi");

    // LcdSetCursor(1, 0);
    // LcdPrintString("and Thuraya go");

    // LcdSetCursor(2, 3);
    // LcdPrintString("Johnson go");

    // LcdCursorShift(0, 1);
    // DelayMilli(3000);
    // LcdSetCursor(3, 10);
    // LcdPrintString("Khajo");

    while (1)
        ;
}