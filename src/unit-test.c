#include "unit-test.h"
#include "clock.h"
#include "lcd.h"
#include "keypad.h"
#include "stdbool.h"

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
    LcdSetCursor(0, 0);
    LcdPrintString("Harith Al-Safi");

    LcdSetCursor(1, 0);
    LcdPrintString("and Thuraya go");

    LcdSetCursor(2, 3);
    LcdPrintString("Johnson go");
}

void TestLcdMultiLine(){
    LcdPrintString("Karith Al-Sadi aNd tHuraya gO everywhEre");
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere");

    DelayMilli(3000);

    LcdPrintString("Barith Al-Nadi aNd thuRaya GO eveRywhEre");
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere");

    DelayMilli(3000);

    LcdClearDisplay();

    LcdPrintString("Jarith Al-Qadi ANd thuRAya Go EveRywhEre");
    LcdPrintString("Harith Al-Safi and Thuraya go everywhere");

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
    LcdPrintString("Press any key");
    KeyInfo keyInfo = KeypadWaitForInput();
    LcdClearDisplay();
    LcdPrintString("You pressed: ");
    LcdPrintChar(keyInfo.key, true);
    DelayMilli(3000);
    LcdClearDisplay();
}

void RunAll(){
    // TestLcdAll();
    TestKeypadLcd();
}