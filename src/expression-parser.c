#include "expression-parser.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

void InitPasrserWith(Token items[], int length){
    previousResult = currentResult;
    currentResult = 0.0;
    tokens = TokenListCreate();
    TokenListAddRange(&tokens, items, length);
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
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentReuslt = 0.0 
    };
    Token next_token;

    next_token = PeekNextToken();
    while(next_token.type != EOL && pi.token.type != EOL){
        pi = ParseExpression();
        printf("Result: %f\n", pi.currentReuslt);
        if(pi.error != NO_ERROR){
            return pi;
        } 

        next_token = GetNextToken();
    }

    return pi;
}

ParserInfo ParseExpression(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentReuslt = 0.0
    };
    Token next_token;

    pi = ParseTerm();
    if(pi.error != NO_ERROR){
        return pi;
    }
    double tempResult = pi.currentReuslt;

    next_token = PeekNextToken();
    while(next_token.value == '+' || next_token.value == '-'){
        GetNextToken();

        pi = ParseTerm();
        if(pi.error != NO_ERROR){
            return pi;
        }  
        if(next_token.value == '+'){
            tempResult += pi.currentReuslt;
        }
        else if (next_token.value == '-'){
            tempResult -= pi.currentReuslt;
        }

        next_token = PeekNextToken();
    }
    pi.currentReuslt = tempResult;
    
    return pi;
}

ParserInfo ParseTerm(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentReuslt = 0.0
    };
    Token next_token;

    pi = ParseNumber();
    if(pi.error != NO_ERROR){
        return pi;
    }
    double tempResult = pi.currentReuslt;
 
    next_token = PeekNextToken();
    while(next_token.value == '*' || next_token.value == '/' || next_token.value == 'E' || next_token.value == '^'){
        GetNextToken();

        pi = ParseNumber();
        if(pi.error != NO_ERROR){
            return pi;
        }  

        if(next_token.value == '*'){
            tempResult *= pi.currentReuslt;
        }
        else if (next_token.value == '/'){
            tempResult /= pi.currentReuslt;
        }
        else if (next_token.value == 'E'){
            tempResult *= pow(10, pi.currentReuslt);
        }
        else if (next_token.value == '^'){
            tempResult = pow(tempResult, pi.currentReuslt);
        }

        next_token = PeekNextToken();
    }
    pi.currentReuslt = tempResult;
    return pi;
}

ParserInfo ParseFactor(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentReuslt = 0.0
    };
    Token next_token;

    return pi;
}

ParserInfo ParseNumber(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentReuslt = 0.0
    };
    Token next_token;

    charList* str = charListCreate();

    next_token = PeekNextToken();
    if(next_token.type == NEGATIVE){
        charListPushBack(&str, next_token.value);
        GetNextToken(); // eats the token 
    }

    next_token = PeekNextToken();
    int decimalPointCount = 0;
    while(next_token.type == NUMBER || next_token.type == DECIMAL){

        GetNextToken();
        if(next_token.type == EOL){
            pi.token =  next_token;
            return pi;
        }
        if(next_token.type == DECIMAL){
            if(decimalPointCount > 1){
                pi.error = MULTIPLE_DECIMAL_POINT;
                pi.token = next_token;
                return pi;
            }
            decimalPointCount++;
        }
        charListPushBack(&str, next_token.value);
        next_token = PeekNextToken();
    }

    if (str->length == 0){
        pi.error = MISSING_NUMBER;
        pi.token = next_token;
        return pi;
    }

    pi.token = next_token;
    pi.currentReuslt = atof(str->value);
    printf("Result: %f\n", pi.currentReuslt);

    return pi;
}

