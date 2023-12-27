#include "expression-parser.h"
#include <stdlib.h>
#include <math.h>

DEFINE_LIST_IMPLEMENTATION(Token);

TokenList* tokens;

double currentResult = 0.0;
double previousResult = 0.0;

void PushToken(Token token){
    if(tokens == NULL){
        tokens = TokenListCreate();
    }
    TokenListPushBack(&tokens, token);
}

void InitPasrser(){
    previousResult = currentResult;
    currentResult = 0.0;
    tokens = TokenListCreate();
}

void StopParser(){
    TokenListDestroy(tokens);
}

// Get the next token from the source file
Token GetNextToken ()
{
	Token t;           
	t = tokens->value[tokens->currentIndex];
	if(tokens->currentIndex < tokens->length-1){
		tokens->currentIndex++;
	}
	return t;
}

// peek (look) at the next token in the source file without
// removing it from the stream
Token PeekNextToken ()
{
	return tokens->value[tokens->currentIndex];
}

double GetCurrentResult(){
    return currentResult;
}

ParserInfo Parse(){
    ParserInfo info;

    return info;
}

NumberDefinition ParseNumber(){
    NumberDefinition number = {
        .isNegative = false,
        .isDecimal = false,
        .error = NO_ERROR,
        .string = charListCreate()
    };

    Token token = PeekNextToken();
    if(token.type == NEGATIVE){
        number.isNegative = true;
        charListPushBack(&number.string, token.value);
        GetNextToken(); // eats the token 
    }

    token = PeekNextToken();
    int decimalPointCount = 0;
    while(token.type == NUMBER || token.type == DECIMAL){
        if(token.type == EOL){
            break;
        }
        if(token.type == DECIMAL){
            if(decimalPointCount > 1){
                number.error = MULTIPLE_DECIMAL_POINT;
                return number;
            }
            number.isDecimal = true;
            decimalPointCount++;
        }
        charListPushBack(&number.string, token.value);
        GetNextToken();
        token = PeekNextToken();
    }

    if (number.string->length == 0){
        number.error = MISSING_NUMBER;
        return number;
    }

    number.value = atof(number.string->value);

    return number;
}

