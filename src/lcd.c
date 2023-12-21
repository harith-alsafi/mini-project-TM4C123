#include "lcd.h"
#include "clock.h"
#include "helpers.h"
#include "ports.h"
#include "stdbool.h"

int currentRow = 0;
int currentCol = 0;

void LcdSetRs(byte rs){
    LCD_RS = rs;
}

void LcdPulseEn(){
    LCD_EN = HIGH;
    DelayNano(450);
    LCD_EN = LOW;
    DelayNano(450);
}

void LcdSendNibble(byte nibble) {
    LCD_DB = nibble&0xF;
    LcdPulseEn();
}

void LcdSendByte(byte byte){
    LcdSendNibble(byte >> 4);
    LcdSendNibble(byte & 0xF);
}

void LcdClearDisplay(){
    currentRow = 0;
    currentCol = -1;

    LcdSetRs(LOW);

    // Display clear
    LcdSendByte(0x01);
    DelayMilli(2);
}

// ?
void LcdCursorShift(byte sc, byte rl){
    sc &= 0x01; // Ensure id is only one bit
    rl &= 0x01;  // Ensure s is only one bit

    // Construct the byte variable using bitwise operations
    byte byte = 0;
    byte |= (1 << 4); // Set bit 4 to 1
    byte |= (sc << 3); // Set bit 3 to sc
    byte |= (rl << 2); // Set bit 2 to rl
    byte |= (0 << 1);  // Set bit 1 to 0
    byte |= (0 << 0);  // Set bit 0 to 0

    LcdSetRs(HIGH);
    LcdSendByte(byte);
    DelayMicro(40);
}

void LcdEntryModeSet(byte id, byte s){
    id &= 0x01; // Ensure id is only one bit
    s &= 0x01;  // Ensure s is only one bit

    // Construct the byte variable using bitwise operations
    byte byte = 0;
    byte |= (1 << 2); // Set bit 2 to 1
    byte |= (id << 1); // Set bit 1 to the value of id
    byte |= (s << 0);  // Set bit 0 to the value of s

    LcdSetRs(LOW);
    LcdSendByte(byte);
    DelayMicro(40);
}

void LcdDisplayControl(byte d, byte c, byte b){
    d &= 0x01; // Ensure d is only one bit
    c &= 0x01;  // Ensure c is only one bit
    b &= 0x01;  // Ensure b is only one bit

    // Construct the byte variable using bitwise operations
    byte byte = 0;
    byte |= (1 << 3); // Set bit 3 to 1
    byte |= (d << 2); // Set bit 2 to the value of d
    byte |= (c << 1);  // Set bit 1 to the value of c
    byte |= (b << 0);  // Set bit 0 to the value of b

    LcdSetRs(LOW);
    LcdSendByte(byte);
    DelayMicro(40);
}

void LcdReturnHome(){
    LcdSetRs(LOW);
    LcdSendByte(0x02);
    DelayMicro(40);
}

void LcdFunctionSet(byte dl, byte n, byte f){
    dl &= 0x01; // Ensure dl is only one bit
    n &= 0x01;  // Ensure n is only one bit
    f &= 0x01;  // Ensure f is only one bit

    // Construct the byte variable using bitwise operations
    byte byte = 0;
    byte |= (1 << 5); // Set bit 5 to 1
    byte |= (dl << 4); // Set bit 4 to the value of dl
    byte |= (n << 3);  // Set bit 3 to the value of n
    byte |= (f << 2);  // Set bit 2 to the value of f

    LcdSetRs(LOW);
    LcdSendByte(byte);
    DelayMicro(40);

}

void LcdInit() {
    PortAInit();
    PortBInit();

    // Power On
    // Wait time > 40 ms after VDD > 4.5V
    DelayMilli(40);

    // Sets LCD Rs to 0;
    LcdSetRs(LOW);

    // Function set
    LcdSendNibble(0x3);

    // Wait time > 4.1 ms
    DelayMilli(5);

    // Function set
    LcdSendNibble(0x3);

    // Wait time > 100 us
    DelayMicro(40);

    // Function set
    LcdSendNibble(0x3);
    DelayMicro(40);

    // Function set (Set interface to be 4 bits length)
    LcdSendNibble(0x2);
    DelayMicro(40);

    // Function set (Interface is 4 bits length. Specify the number of the display lines and character font.)
    LcdFunctionSet(0, 1, 0);
    // LcdSendByte(0x28);
    // DelayMicro(40);

    // Display off
    LcdDisplayControl(0, 0, 0);
    // LcdSendByte(0x08);
    // DelayMicro(40);

    // 0x01 Display clear
    LcdClearDisplay();
    // LcdSendByte(0x01);
    // DelayMilli(2);

    // 0x06 Entry mode set
    LcdEntryModeSet(1, 0);

    // INIT finishes

    // 0x0E Display on, cursor appears
    LcdDisplayControl(1, 1, 0);
}

void LcdSetDdram(byte addr){
    addr = addr & 0x7F;
    addr |= (1 << 7);
    LcdSetRs(LOW);
    LcdSendByte(addr);
    DelayMicro(40);
}

void LcdSetCursor(byte row, byte col){
    currentCol = col;
    currentRow = row;
    byte addr = 0;
    if(row == 0){
        addr = 0x00;
    } else if(row == 1){
        addr = 0x40;
    } else if(row == 2){
        addr = 0x14;
    } else if(row == 3){
        addr = 0x54;
    }
    addr += col;
    LcdSetDdram(addr);
}

void LcdIncrementCursorRow(){
    if(currentRow < LCD_N_ROW - 1){
        currentRow++;
    } else {
        currentRow = 0;

    }
    currentCol = 0;
    LcdSetCursor(currentRow, currentCol);
}

void LcdIncrementCursorCol(){
    if(currentCol < LCD_N_COL - 1){
        currentCol++;
    } else {
        LcdIncrementCursorRow();
    }
}

void LcdPrintChar(char ch, bool cursorTrack){
    if(cursorTrack){
        if(ch == '\n'){   
            LcdIncrementCursorRow();
            return;
        }
        else{
            LcdIncrementCursorCol();
        }
    }
    LcdSetRs(HIGH);
    LcdSendByte(ch);
    DelayMicro(40);
}

void LcdPrintCharAt(char ch, byte row, byte col){
    LcdSetCursor(row, col);
    LcdPrintChar(ch, false);
}

void LcdPrintString(char str[]){
    int i; 
    for(i = 0; i < Strlen(str); i++){
        LcdPrintChar(str[i], true);
    }
}