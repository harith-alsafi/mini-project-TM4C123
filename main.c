#include "clock.h"
#include "lcd.h"
#include "port_init.h"

void InitAll() {
    PortAInit();
    PortBInit();
    SysTickInit();
    PLLInit();
	LcdInit();
}

int main() {
    InitAll();
	DelayMilli(100);
	SendLcdCommandByte(1, 0x57);
	DelayMilli(100);
	LcdPrintChar('A');
    while (1)
        ;
}