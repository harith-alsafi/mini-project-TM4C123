#ifndef EXPRESSION_PARSER_H // If not defined
#define EXPRESSION_PARSER_H // Define it
#include "keypad.h"
#include <stdbool.h>
#include "helpers.h"

#define SCB_CPACR (*((volatile unsigned long *)0xE000ED88))

typedef enum {
    SYNTAX_ERROR,
    NO_ERROR,
    INVALID_MATH_EXPRESSION,
    MULTIPLE_DECIMAL_POINT,
    MISSING_NUMBER,
    MISSING_BRACKET,
} ParseError;

typedef enum {
    NUMBER,
    EOL,
    OPERATOR,
    DECIMAL,
    PREVIOUS_ANSWER,
} TokenType;

typedef struct {
    char value;
    TokenType type;
} Token;

typedef struct {
    Token token;
    ParseError error;
    float currentResult;
} ParserInfo;

DEFINE_LIST_PROTOTYPE(Token);

/**
 * @brief Pushes new token to the parser can be used after calling @see ParserInit and @see ParserInitWith
 * 
 * @param token 
 */
void ParserPushToken(Token token);

/**
 * @brief Removes last pushed token 
 * 
 */
void ParserPopToken();

/**
 * @brief Initializes the parser
 * 
 */
void ParserInit();

/**
 * @brief Initializes the parser with initial token list 
 * 
 * @param items token list
 * @param length length of the tokens 
 */
void ParserInitWith(Token items[], int length);

/**
 * @brief Stops the parser and clears all tokens 
 * 
 */
void ParserStop();

/**
 * @brief Calls @see ParserInit then @see ParserStop 
 * 
 */
void ParserReset();

/**
 * @brief Compiles the tokens and returns the result
 * 
 * @return `ParserInfo`  <br>
 */
ParserInfo ParserCompile();

/**
 * @brief Ends the input 
 * 
 */
void ParserEndInput();

#endif