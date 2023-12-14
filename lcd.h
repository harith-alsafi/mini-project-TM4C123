#include "port_init.h"

#define LCD_DB (*((volatile unsigned long *)0x40005042))
#define LCD_EN (*((volatile unsigned long *)0x40004010))
#define LCD_RS (*((volatile unsigned long *)0x40004020))

void SendDisplayNibble() ;

void SendDisplayByte() ;

void InitDisplayPort();

void SendDisplayByte() ;

void ClearDisplayScreen();

void MoveDisplayCursor();

void PrintDisplay();