#ifndef LOGIC_H   // If not defined
#define LOGIC_H   // Define it
#include "keypad.h"

#define LOGIC_STATBAR_ROW 0
#define LOGIC_SHORTCUTS_ROW LCD_N_ROW-1
#define LOGIC_INPUT_ROWS (byte[]) {1, 2}

typedef enum {
    LOGIN_MODE,
    CALCULATOR_MODE,
    CHANGE_PASSWORD
} ProgramMode;

/**
 * @brief Initializes all components 
 * 
 */
void InitAll();

/**
 * @brief Runs the main loop 
 * 
 */
void RunMain();

#endif