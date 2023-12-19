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
	DelayMilli(100);

	SendLcdCommandByte(1, 0x53);
	DelayMilli(5000);
	LcdPrintChar('A');
    while (1)
        ;
}