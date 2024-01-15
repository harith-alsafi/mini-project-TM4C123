#include "logic.h"
#include "clock.h"
#include "lcd.h"
#include "keypad.h"
#include "flash.h"
#include "parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define LOGIC_STATBAR_ROW 0
#define LOGIC_SHORTCUTS_ROW LCD_N_ROW-1
#define LOGIC_INPUT_ROWS (byte[]) {1, 2}

//********************************************

void RunLogin();

void RunChangePassword();

void RunCalculator();

void RunLoginAnimation();

Token GetKeyToken(KeyInfo key);

void ClearAllInput(bool clearData);

void ClearLastInput();

void ShowCurrentData();

void PrintData(void* data, int length, bool isToken);

bool IsCalculatorAvailable();

bool IsPasswordInputAvailable();

SpecialKeyFunctions GetSpecialFunction(KeyInfo key);

void MapFunctions(SpecialKeyFunctions function);

void ShowNumberOperation(KeyInfo key);

void UpdateShift();

bool PasswordMatch(charList password);

void DisplayMessage(char message[]);

void RefreshDisplay();

void RunUserInput(KeyInfo key);

void UpdateRows();

//************GLOBAL VARIABLES****************

bool isShiftOn = false;
bool isLoggedIn = false;
bool isInit = false;
ProgramMode mode = LOGIN_MODE;
TokenList tokenData;
charList inputData;
FlashData flashData = {
    .passwordLength = 3,
    .password = "123"
};

//************GLOBAL FUNCTIONS****************

void InitAll() {
    ClockInit();
	LcdInit();
    KeypadInit();
    FlashInit();
    FlashData tempData = FlashRead();
    if(FlashDataIsRead(tempData)){
        flashData = tempData;
    }
    else{
        FlashWrite(flashData);
    }
    ParserInit();
    isInit = true;
    tokenData = TokenListCreate();
    inputData = charListCreate();
}

//************PASSWORD MODULE****************

void RunUserInput(KeyInfo key){
    Token token = {
        .value = isShiftOn? key.shiftDisplay : key.normalDisplay,
    };
    SpecialKeyFunctions function = GetSpecialFunction(key);
    
    if(function == NORMAL_NUMBER){
        token.type = NUMBER;
    }
    else if (function == OPERATION){
        token.type = OPERATOR;
    }
    else if(function == DECIMAL_POINT){
        token.type = DECIMAL;

    }
    else if(function == PAST_ANSWER){
        token.type = PREVIOUS_ANSWER;
    }

    LcdPrintChar(token.value, true);
    if(mode == CALCULATOR_MODE){
        TokenListPushBack(&tokenData, token);
    }
    else{
        charListPushBack(&inputData, token.value);
    }
}

void RunCalculator(){
    // input exists 
    if(tokenData.length > 0){
        for(int i = 0; i < tokenData.length; i++){
            ParserPushToken(tokenData.values[i]);
        }
        ParserEndInput();
        ParserInfo pi = ParserCompile();
        ParserReset();
        ClearAllInput(false);
        if(pi.error == NO_ERROR){
            ClearAllInput(true); 
            char buffer[LCD_N_COL*2];
            sprintf(buffer, "%.2f", pi.currentResult);
            LcdPrintString(buffer, true);
        }
        // error cccured 
        else{
            LcdPrintString("Error occured",true);
        }
    }
    // No input was given 
    else{
        ClearAllInput(false);
        LcdPrintString("No input was given", true);
    }
}

void RunLoginAnimation(){
    // Define the animation frames
    char frames[][21] = {
        "   Logging In...   ",
        "  | Logging In...  ",
        "  / Logging In...  ",
        "  - Logging In...  ",
        "  \\ Logging In... ",
        "  | Logging In...  ",
        "  / Logging In...  ",
        "  - Logging In...  ",
        "  \\ Logging In... ",
        "  | Logging In...  ",
        "  / Logging In...  ",
        "  - Logging In...  ",
        "  \\ Logging In... ",
        "  | Logging In...  ",
        "  / Logging In...  ",
        "  - Logging In...  ",
        "  \\ Logging In... ",
        "   Logged In!      ",
        "   Welcome User!   "
    };

    // Number of frames
    int numFrames = 19;

    // Set initial cursor position
    LcdSetCursor(0, 0, 0);

    // Display animation frames with particle movement
    for (int i = 0; i < numFrames; ++i) {
        // Display particles
        for (int j = 0; j < 5; ++j) {
            LcdSetCursor(RandomRange(1, 4), RandomRange(0, 19), 0);
            LcdPrintChar('*', 0);
        }

        LcdSetCursor(0, 0, 0);
        LcdPrintString(frames[i], 0);
        DelayMilli(500); // Adjust the delay as needed
        LcdSetCursor(0, 0, 0); // Reset cursor position
        LcdPrintString("                    ", 0); // Clear the line
    }
    LcdClearDisplay();
}

void RunLogin(){
    // input data was given 
    if(inputData.length > 0){
        // Login success
        if(PasswordMatch(inputData)){ 
            LcdClearDisplay();
            ClearAllInput(true);
            RunLoginAnimation();
            mode = CALCULATOR_MODE;
            UpdateRows();
        }
        // login failed 
        else{
            LcdClearDisplay();
            LcdPrintString("Wrong password ", true);
            // charListClear(&inputData);
            DelayMilli(2000);
            LcdClearDisplay();
            UpdateRows();
            ShowCurrentData();
        }
    }
    // no input was given error 
    else{

    }
}

void RunChangePassword(){
    // input was given 
    if(inputData.length >= 0){
        flashData.passwordLength = inputData.length;
        for(int i = 0; i < inputData.length; i++){
            flashData.password[i] = inputData.values[i];
        }
        FlashWrite(flashData);
        // show it was a success 
        LcdClearDisplay();
        LcdPrintString("Password changed", true);
        DelayMilli(2000);
        LcdClearDisplay();
        // changing password was a success 
        mode = CALCULATOR_MODE;
        UpdateRows();
    }
    // no input was given error 
    else{
        LcdPrintString("No Input", true);
    }
}

void UpdateShift(){
    LcdPrintCharAt(isShiftOn? LCD_CHAR_S : ' ', LOGIC_STATBAR_ROW, LCD_N_COL-1);
}

void UpdateRows(){
    UpdateShift();
    LcdSetCursor(LOGIC_STATBAR_ROW, 0, true);
    if(mode == LOGIN_MODE){
        LcdPrintString("Enter password:", true);
        LcdSetCursor(LOGIC_SHORTCUTS_ROW, 0, true); 
        char buffer[LCD_N_COL];
        sprintf(buffer, "%c %s",
            '=', "DONE"
        );
        LcdPrintString("= DONE",true);
    }
    else if(mode == CALCULATOR_MODE){
        LcdPrintString("Enter expression:", true);
        LcdSetCursor(LOGIC_SHORTCUTS_ROW, 0, true);
        char buffer[LCD_N_COL];
        sprintf(buffer, "%c%c %s       %c%c %s",  
            LCD_CHAR_S, '=', "PWD",
            LCD_CHAR_S, '0', "ANS"
        );
        LcdPrintString(buffer,true);
    }
    else if(mode == CHANGE_PASSWORD){
        LcdPrintString("Enter new password:", true);
        LcdSetCursor(LOGIC_SHORTCUTS_ROW, 0, true);
        char buffer[LCD_N_COL];
        sprintf(buffer, "%c %s      %c%c %s", 
            '=', "DONE",
            LCD_CHAR_S, '1', "BACK"
        );
        LcdPrintString(buffer,true);
    }
    LcdSetCursor(LOGIC_INPUT_ROWS[0], 0, true);
}

void RefreshDisplay(){
    LcdClearDisplay();
    UpdateRows();
    ShowCurrentData();
}

bool IsCalculatorAvailable(){
    return mode == CALCULATOR_MODE && tokenData.length > 0;
}

bool IsPasswordInputAvailable(){
    return (mode == LOGIN_MODE || mode == CHANGE_PASSWORD) && inputData.length > 0;
}

SpecialKeyFunctions GetSpecialFunction(KeyInfo key){
    return isShiftOn ? key.shiftFunction : key.normalFunction; 
}

void ClearAllInput(bool clearData){
    LcdClearRow(1);
    LcdClearRow(2);
    LcdSetCursor(1, 0, true);
    if(clearData){    
        if(mode == CALCULATOR_MODE){
            TokenListClear(&tokenData);
        }
        else{
            charListClear(&inputData);
        }   
    }
}

void ClearLastInput(){
    if(tokenData.length > 0 || inputData.length > 0){
        LcdClearLastChar(0);
        if(IsCalculatorAvailable()){
            TokenListRemoveAt(&tokenData, tokenData.length-1);
        }
        else if(IsPasswordInputAvailable()){
            charListRemoveAt(&inputData, inputData.length -1);
        }
    }
}

void DisplayMessage(char message[]){
    UpdateRows();
    LcdPrintString(message, true);
}

void PrintData(void* data, int length, bool isToken){
    LcdSetCursor(1, 0, true);
    for(int i = 0; i < length; i++){
        char key;
        if (isToken) {
            Token* token = ((Token*)data) + i;
            key = token->value;
        } else {
            char* charData = ((char*)data) + i;
            key = *charData;
        }
        LcdPrintChar(key, true);
    }

}

void ShowCurrentData(){
    if(IsCalculatorAvailable()){
        PrintData(&tokenData.values, tokenData.length, true);
    }
    else if(IsPasswordInputAvailable()){
        PrintData(&inputData.values, inputData.length, false);
    }
}

bool PasswordMatch(charList password){
    if(password.length != flashData.passwordLength){
        return false;
    }
    for(int i = 0; i < password.length; i++){
        if(password.values[i] != flashData.password[i]){
            return false;
        }
    }
    return true;
}

void RunMain(){
    LcdClearDisplay();
    KeyInfo key = KeypadCreateDefaulteKey(' ');
    UpdateRows();
    while(1){
        DelayMilli(200);
        key = KeypadWaitForKeyInfo();
        SpecialKeyFunctions function = GetSpecialFunction(key);
        // shift is on 
        if(function == SHIFT_ON){
            isShiftOn = true;
            UpdateShift();
            continue;
        }
        // shift is off 
        else if(function == SHIFT_OFF){
            isShiftOn = false;
            UpdateShift();
            continue;
        }
        // display normally 
        else if(!isShiftOn && key.normalDisplayType == DISPLAY_NORMAL || isShiftOn && key.shiftDisplayType == DISPLAY_NORMAL){
            RunUserInput(key);
            continue;
        }
        // clear input 
        else if(function == CLEAR_ALL){
            ClearAllInput(true);
            continue;
        }
        // clear last input
        else if(function == CLEAR_LAST){
            ClearLastInput();
            continue;
        }
        // // end input 
        else if(function == END_INPUT){
            // calculate input 
            if(mode == CALCULATOR_MODE){
                RunCalculator();
                continue;
            }
            // try to login / confirm change password 
            else if(mode == LOGIN_MODE){
                RunLogin();
                continue;
            }
            // change the password and go back 
            else if(mode == CHANGE_PASSWORD) {
                RunChangePassword();
                continue;
            }
        }
        // go back to calculator mode 
        else if(function == GO_BACK && mode == CHANGE_PASSWORD){
            mode = CALCULATOR_MODE;
            isShiftOn = false;
            RefreshDisplay();
        }
        // open change password
        else if(function == OPEN_CHANGE_PASSWORD && mode == CALCULATOR_MODE){
            mode = CHANGE_PASSWORD;
            isShiftOn = false;
            RefreshDisplay();
        }
        
    }
}




// ***********GENERAL UI***************************





//************CHANGE PASSWORD MODULE****************

void RunChangePasswordModule(){

}

//************CALCULATOR MODULE****************


//************GRAPH MODULE****************

void RunGraphModule(){

}

//************MAIN MODULE****************

