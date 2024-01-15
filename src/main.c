#include "logic.h"
#include <stdbool.h>
#include "test.h"
#include "lcd.h"
#include "clock.h"
#include "helpers.h"
#include "flash.h"
#include "parser.h"
#include <stdio.h>

// #define RUN_HARDWARE_TEST

int main() {
    InitAll();
    RunAllTests();

    // ParserPushToken((Token){
    //     .type = NUMBER, 
    //     .value = '5'
    // });
    // ParserPushToken((Token){
    //     .type = OPERATOR, 
    //     .value = '+'
    // });
    // ParserPushToken((Token){
    //     .type = NUMBER, 
    //     .value = '2'
    // });
    // ParserEndInput();
    // LcdPrintString("started ", true);
    // ParserInfo pi = ParserCompile();
    // ParserStop();
    // LcdPrintString("done ", true);
    // DelayMilli(1000);
    // LcdClearDisplay();
    // char buffer[10];
    // snprintf(buffer, 10, "%2.f", pi.currentResult);
    // buffer[9] = '\0';  // Ensure null-termination
    // LcdPrintString(buffer, true);



    // LcdClearDisplay();
    // RunAllTests();
    // LcdPrintChar('H', false);
        // RunMain();
    // ClockInit();
	// LcdInit();
    // KeypadInit();
    // FlashInit();
    // FlashData flashData = {
    //     .passwordLength = 3,
    //     .password = "123"
    // };
    // FlashWrite(flashData);
    // LcdPrintString(flashData.password, true);
    // DelayMilli(3000);
    // LcdClearDisplay();
    // FlashData flashData2 = FlashRead();
    // LcdPrintString(flashData2.password, true);
    // while (1){
        // LcdPrintChar('a', true);
        // KeyInfo key = KeypadWaitForKeyInfo();
        // RunUserInput(key);
        // LcdPrintChar(key.key, true);
        RunMain();
        // DelayMilli(200);s
    // }
}