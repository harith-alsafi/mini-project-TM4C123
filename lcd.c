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
    DelayMicro(40);

    // Function set
    SendLcdNibble(0x3);
    DelayMicro(40);

    // Function set (Set interface to be 4 bits length)
    SendLcdNibble(0x2);
    DelayMicro(40);

    // Function set (Interface is 4 bits length. Specify the number of the display lines and character font.)
    SendLcdByte(0x28);
    DelayMicro(40);

    // Display off
    SendLcdByte(0x08);
    DelayMicro(40);

    // Display clear
    SendLcdByte(0x01);
    DelayMilli(2);

    // Entry mode set
    SendLcdByte(0x06);
    DelayMicro(40);

    SendLcdByte(0x0E);
    DelayMicro(40);

    SendLcdByte(0x06);
    DelayMicro(40);
}

void LcdPrintChar(char ch) {
    SendLcdRs(1);
    SendLcdByte(ch);
    DelayMicro(40);
}