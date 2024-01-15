#ifndef LOGIC_H   // If not defined
#define LOGIC_H   // Define it
#include "keypad.h"

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