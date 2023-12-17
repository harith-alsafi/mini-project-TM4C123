#include "lcd.h"
#include "clock.h"

void SendLcdRs(int rs){
    LCD_RS = rs > 0 ? 0xFF : 0x00;
}

void LcdPulseEn(){
    LCD_EN = 0xFF;
    DelayNano(450);
    LCD_EN = 0x00;
    DelayNano(450);
}

void SendLcdNibble(unsigned char nibble) {
    LCD_DB = nibble&0xF;
    LcdPulseEn();
}

void SendLcdCommand(int rs, unsigned char command){
    SendLcdRs(rs);
    SendLcdNibble(command);
}

void SendLcdByte(unsigned char byte){
    SendLcdNibble(byte >> 4);
    SendLcdNibble(byte & 0xF);
}

void SendLcdCommandByte(int rs, unsigned char byte){
    SendLcdRs(rs);
    SendLcdByte(byte);
}

void LcdInit() {
    // Power On
    // Wait time > 40 ms after VDD > 4.5V
    DelayMilli(40);

    // Sets LCD Rs to 0;
    SendLcdRs(0);

    // Function set
    SendLcdNibble(0x3);

    // Wait time > 4.1 ms
    DelayMilli(5);

    // Function set
    SendLcdNibble(0x3);

    // Wait time > 100 us
    DelayMicro(110);

    // Function set
    SendLcdNibble(0x3);

    // Function set (Set interface to be 4 bits length)
    SendLcdNibble(0x2);

    // Function set (Interface is 4 bits length. Specify the number of the display lines and character font.)
    SendLcdByte(0x28);

    // Display off
    SendLcdByte(0x08);

    // Display clear
    SendLcdByte(0x01);

    // Entry mode set
    SendLcdByte(0x06);
}

void LcdPrintChar(char ch) {
    // Send higher nibble
    SendLcdCommand(1, ch >> 4);

    // Send lower nibble
    SendLcdCommand(1, ch & 0xF);

    DelayMicro(40);
}