#ifndef EXPRESSION_PARSER_H // If not defined
#define EXPRESSION_PARSER_H // Define it
#include "keypad.h"
#include <stdbool.h>
#include "helpers.h"

typedef enum {
    SYNTAX_ERROR,
    NO_ERROR,
    INVALID_MATH_EXPRESSION,
    MULTIPLE_DECIMAL_POINT,
    MISSING_NUMBER
} ParseError;

typedef enum {
    NUMBER,
    OPERATOR,
    NEGATIVE,
    PARENTHESIS,
    DECIMAL,
    EOL,
    PREVIOUS_ANSWER,
} TokenType;

typedef struct {
    char value;
    TokenType type;
} Token;

DEFINE_LIST_PROTOTYPE(Token);

typedef struct {
    Token token;
    ParseError error;
} ParserInfo;

// 1.234E3.4*1+2/4-5^3+2*(5+1)
typedef struct {
    bool isNegative;
    bool isDecimal;
    double value;
    ParseError error;
    charList* string;
} NumberDefinition;

// (sign?) number Operation (sign?) number
// number => number.number

void PushToken(Token token);

void InitPasrser();

void StopParser();

Token PeekNextToken();

Token GetNextToken();

double GetCurrentResult();

ParserInfo Parse();

void PushNewKey(KeyInfo key);

NumberDefinition ParseNumber();

ParserInfo ParseFactor();

ParserInfo ParseTerm();

ParserInfo ParseExpression();


#endif