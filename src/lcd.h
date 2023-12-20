#ifndef LCD_H   // If not defined
#define LCD_H   // Define it

#include "ports.h"

// DB4 -> PB0
// DB5 -> PB1
// DB6 -> PB2
// DB7 -> PB3
#define LCD_DB (*((volatile unsigned long *)0x4000503C))
// EN -> PA2
#define LCD_EN (*((volatile unsigned long *)0x40004010))
// RS -> PA3
#define LCD_RS (*((volatile unsigned long *)0x40004020))

#define LCD_N_COL 20
#define LCD_N_ROW 4

/**
 * @brief Sets the rs flag to the given value
 * 
 * @param rs rs == 1 -> data RS = HIGH, rs == 0 -> command RS = LOW
 */
void LcdSetRs(unsigned char rs);

/**
 * @brief Pulses the EN pin HIGH wait 450ns and then LOW wait 450ns
 * 
 */
void LcdPulseEn();

/**
 * @brief Sends a nibble to the LCD 
 * 
 * @param nibble RS | R/W | DB4 | DB5 | DB6 | DB7
 */
void LcdSendNibble(unsigned char nibble);

/**
 * @brief Sends a byte to the LCD
 * 
 * @param byte the byte to be sent
 */
void LcdSendByte(unsigned char byte);

/**
 * @brief Clears the display
 * 
 */
void LcdClearDisplay();

/**
 * @brief Sets the LCD cursor position 
 * 
 * @param sc Display shift sc = 1, Cursor move sc = 0
 * @param rl Right shift rl = 1, Left shift rl = 0
 */
void LcdCursorShift(int sc, int rl);

/**
 * @brief Sets the entry mode of the LCD
 * 
 * @param id I / D = 1: Increment, I / D = 0: Decrement.
 * @param s S = 1: The display shift, S = 0: The display does not shift.
 */
void LcdEntryModeSet(int id, int s);

/**
 * @brief Controls the display, cursor, and blinking
 * 
 * @param d D = 1: Display on, D = 0: Display off 
 * @param c C = 1: Cursor on, C = 0: Cursor off
 * @param b B = 1: Blinks on, B= 0: Blinks off
 */
void LcdDisplayControl(int d, int c, int b);

/**
 * @brief Resets cursor to original position 
 * 
 */
void LcdReturnHome();

/**
 * @brief 
 * 
 * @param dl DL = 1: 8-bit length (DB7 - 0). DL = 0:  4-bit length (DB7 - 4).
 * @param n N = 0: One-line display. N = 1: Two-line display
 * @param f F = 0: 5 x 8 dots character font. F = 1: 5 x 10 dots character font.
 */
void LcdFunctionSet(int dl, int n, int f);

/**
 * @brief Initializes the LCD
 * 
 */
void LcdInit();

/**
 * @brief Sets the DDRAM address (cursor position)
 * 
 * @param addr 7-bit address to be set 
 */
void LcdSetDdram(unsigned char addr);

/**
 * @brief Sets the cursor position
 * 
 * @param row row to be set
 * @param col column to be set
 */
void LcdSetCursor(unsigned char row, unsigned char col);

/**
 * @brief Prints a character to the LCD
 * 
 * @param ch character to be printed
 * @param cursorShift 1 -> shift cursor, 0 -> don't shift cursor
 */
void LcdPrintChar(char ch, unsigned char cursorShift);

/**
 * @brief Prints a string to the LCD
 * 
 * @param str string to be printed
 */
void LcdPrintString(char str[]);

/**
 * @brief Prints a character to the LCD at a given position
 *  
 * @param ch character to be printed
 * @param row row to be printed at
 * @param col column to be printed at
 */
void LcdPrintCharAt(char ch, unsigned char row, unsigned char col);

void LcdClearRow(unsigned char row);

void LcdClearCol(unsigned char col);

void LcdDrawLine(unsigned char row, unsigned char col, unsigned char length, unsigned char is_vertical);

void LcdDrawBox(unsigned char row, unsigned char col, unsigned char length, unsigned char width);

#endif