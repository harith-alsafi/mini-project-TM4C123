#include "test.h"
#include "clock.h"
#include "lcd.h"
#include "keypad.h"
#include "stdbool.h"
#include "flash.h"
#include <stdio.h>

void AfterEach(){
    LcdClearDisplay();
    DelayMilli(3000);
}

void TestLcdClear(){
	LcdPrintChar('S', false);
    LcdClearDisplay();
    DelayMilli(3000);
	LcdPrintChar('A', false);
}

void TestLcdCursor(){
    LcdSetCursor(0, 0, false);
    LcdPrintString("Harith Al-Safi", false);

    LcdSetCursor(1, 0, false);
    LcdPrintString("and Thuraya go", false);

    LcdSetCursor(2, 3, false);
    LcdPrintString("Johnson go", false);
}

void TestLcdMultiLine(){
    LcdPrintString("Karith Al-Sadi aNd tHuraya gO everywhEre", true);
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere", true);

    DelayMilli(3000);

    LcdPrintString("Barith Al-Nadi aNd thuRaya GO eveRywhEre", true);
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere", true);

    DelayMilli(3000);

    LcdClearDisplay();

    LcdPrintString("Jarith Al-Qadi ANd thuRAya Go EveRywhEre", true);
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere", true);

}

void TestLcdAll(){
    // TestLcdClear();
    // AfterEach();
    // TestLcdCursor();
    // AfterEach();
    TestLcdMultiLine();
    // AfterEach();
}

void TestKeypadLcd(){
    LcdPrintString("Press any key", true);
    KeyInfo keyInfo = KeypadWaitForKeyInfo();
    LcdClearDisplay();
    LcdPrintString("You pressed: ", true);
    LcdPrintChar(keyInfo.key, true);
    DelayMilli(3000);
    LcdClearDisplay();
}

void TestFlash(){
    FlashWrite((FlashData){
        .passwordLength = 4,
        .password = "abcd",
    });
    FlashData data = FlashRead();
    bool status = data.passwordLength >= 0;
    char str[10];
    sprintf(str, "%d", data.passwordLength);
    LcdPrintString(str, true);
    LcdPrintString(data.password, true);
    FlashErase();
}

void RunAllTests(){
    // TestLcdAll();
    // TestKeypadLcd();
    // TestFlash();
}