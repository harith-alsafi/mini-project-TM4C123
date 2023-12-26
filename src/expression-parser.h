#ifndef EXPRESSION_PARSER_H // If not defined
#define EXPRESSION_PARSER_H // Define it
#include "keypad.h"
#include <stdbool.h>

typedef enum {
    NUMBER,
    OPERATOR,
    PARENTHESIS,
    POINT,
} TokenType;

typedef struct {
    char value;
    TokenType type;
} Token;

typedef struct {
    int currentIndex;
    size_t size;
    Token value[];
} TokenList;

typedef struct {
    size_t size;
    KeyInfo value[];
} KeyInfoList;


// 1.234E3.4*1+2/4-5^3+2*(5+1)


// (sign?) number Operation (sign?) number
// number => number.number

typedef struct {
    bool isNegative;
    bool isDecimal;
    char *number;
} NumberDefinition;

typedef struct {
    NumberDefinition leftSide;
    NumberDefinition rightSide;
    SpecialKeyFunctions operation;
} TermDefinition;

typedef struct {
    TermDefinition leftSide;
    TermDefinition rightSide;
    SpecialKeyFunctions operation;
} ExpressionDefinition;

int PushBackKey(KeyInfoList **list, KeyInfo value);

int PushBackToken(TokenList **list, Token value);

Token GetToken(KeyInfo key);

Token PeekNextToken();

Token GetNextToken();

KeyInfo PopBackKey(KeyInfoList **list);


#endif