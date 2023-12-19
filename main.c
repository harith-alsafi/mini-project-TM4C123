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
	LcdPrintChar('S');
	LcdPrintChar('A');
    while (1)
        ;
}