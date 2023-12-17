#include "port_init.h"

// DB4 -> PB0
// DB5 -> PB1
// DB6 -> PB2
// DB7 -> PB3
#define LCD_DB (*((volatile unsigned long *)0x40005042))
#define LCD_EN (*((volatile unsigned long *)0x40004010))
#define LCD_RS (*((volatile unsigned long *)0x40004020))


void SendLcdRs(int rs);

void LcdPulseEn();

/**
 * @brief Sends a nibble to the LCD 
 * 
 * @param nibble RS | R/W | DB4 | DB5 | DB6 | DB7
 */
void SendLcdNibble(unsigned char nibble);

/**
 * @brief Sends a command to the LCD
 * 
 * @param rs RS part of the command
 * @param command DB4 | DB5 | DB6 | DB7
 */
void SendLcdCommand(int rs, unsigned char command);

void SendLcdByte(unsigned char byte);

void SendLcdCommandByte(int rs, unsigned char byte);

/**
 * @brief Initializes the LCD
 * 
 */
void LcdInit();


void LcdPrintChar(char ch);

void ClearDisplayScreen();

void MoveDisplayCursor();

void PrintDisplay();

// N = 2 F = 0