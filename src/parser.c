#include "parser.h"
#include <stdbool.h>
#include <math.h>
#include "lcd.h"
#include <stdio.h>
#include "clock.h"

//********************************************

/**
 * @brief Parses only number tokens
 * 
 * @return `ParserInfo`  <br>
 */
ParserInfo ParseNumber();

/**
 * @brief Parses term tokens 
 * 
 * @return `ParserInfo`  <br>
 */
ParserInfo ParseTerm();

/**
 * @brief Parses bracket expression 
 * 
 * @return `ParserInfo`  <br>
 */
ParserInfo ParseBracket();

/**
 * @brief Parses arithematic expression 
 * 
 * @return `ParserInfo`  <br>
 */
ParserInfo ParseExpression();

/**
 * @brief Peeks next token 
 * 
 * @return `Token`  <br>
 */
Token PeekNextToken();

/**
 * @brief Eats the next token 
 * 
 * @return `Token`  <br>
 */
Token GetNextToken();

//********************************************

DEFINE_LIST_IMPLEMENTATION(Token);

TokenList tokens;

float currentResult = 0.0;
float previousResult = 0.0;

Token GetNextToken ()
{
	Token t;           
	t = tokens.values[tokens.currentIndex];
	if(tokens.currentIndex < tokens.length-1){
		tokens.currentIndex++;
	}
	return t;
}

Token PeekNextToken ()
{
	return tokens.values[tokens.currentIndex];
}

void ParserPushToken(Token token){
    TokenListPushBack(&tokens, token);
}

void ParserEndInput(){
    ParserPushToken((Token){
        .type = EOL,
        .value = ' '
    });
}

void ParserPopToken(){
    // if (tokens.values == NULL){
    //     return;
    // }
    
}

void ParserInit(){
    previousResult = currentResult;
    currentResult = 0.0;
    tokens = TokenListCreate();
    SCB_CPACR |= (0xF << 20); // Enable CP10 and CP11
}

void ParserInitWith(Token items[], int length){
    previousResult = currentResult;
    currentResult = 0.0;
    tokens = TokenListCreate();
    TokenListAddRange(&tokens, items, length);
}

void ParserStop(){
    TokenListClear(&tokens);
}

void ParserReset(){
    previousResult = currentResult;
    currentResult = 0.0;
    tokens = TokenListCreate();
    ParserStop();
}

// TODO: fix 5^(-2)
ParserInfo ParserCompile(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentResult = 0.0 
    };
    Token next_token;

    next_token = PeekNextToken();
    while(next_token.type != EOL){
        pi = ParseExpression();
        if(pi.error != NO_ERROR){
            return pi;
        } 

        next_token = GetNextToken();
    }
    currentResult = pi.currentResult;

    return pi;
}

ParserInfo ParseBracket(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentResult = 0.0
    };
    Token next_token;

    next_token = PeekNextToken();
    if(next_token.value != '('){
        pi.error = MISSING_BRACKET;
        return pi;
    }

    GetNextToken(); // eat the '('

    pi = ParseExpression();
    if(pi.error != NO_ERROR){
        return pi;
    }

    next_token = GetNextToken(); // eat the ')'
    if(next_token.value != ')'){
        pi.error = MISSING_BRACKET;
        return pi;
    }

    return pi;
}

ParserInfo ParseExpression(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentResult = 0.0
    };
    Token next_token;

    pi = ParseTerm();
    if(pi.error != NO_ERROR){
        return pi;
    }
    float tempResult = pi.currentResult;

    next_token = PeekNextToken();
    while(next_token.value == '+' || next_token.value == '-' || next_token.value == '('){
        GetNextToken();
        if(next_token.value == '('){
            pi = ParseBracket();
            if(pi.error != NO_ERROR){
                return pi;
            }
        } 
        else {
            pi = ParseTerm();
            if(pi.error != NO_ERROR){
                return pi;
            }
        }

        if(next_token.value == '+'){
            tempResult += pi.currentResult;
        }
        else if (next_token.value == '-'){
            tempResult -= pi.currentResult;
        }

        next_token = PeekNextToken();

    }
    pi.currentResult = tempResult;
    
    return pi;
}

ParserInfo ParseTerm(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentResult = 0.0
    };
    Token next_token;

    pi = ParseNumber();
    if(pi.error != NO_ERROR){
        return pi;
    }
    float tempResult = pi.currentResult;
 
    next_token = PeekNextToken();
    while(next_token.value == 'x' || next_token.value == '/' || next_token.value == 'E' || next_token.value == '^' || next_token.value == '('){
        GetNextToken();
    
        if(next_token.value == '('){
            pi = ParseBracket();
            if(pi.error != NO_ERROR){
                return pi;
            }
        } 
        else {
            pi = ParseNumber();
            if(pi.error != NO_ERROR){
                return pi;
            }
        }


        if(next_token.value == '^'){
            tempResult = pow(tempResult, pi.currentResult);
        }
        else if(next_token.value == 'x'){
            tempResult *= pi.currentResult;
        }
        else if (next_token.value == '/'){
            tempResult /= pi.currentResult;
        }
        else if (next_token.value == 'E'){
            tempResult *= pow(10, pi.currentResult);
        }

        next_token = PeekNextToken();
    }
    pi.currentResult = tempResult;

    return pi;
}

ParserInfo ParseNumber(){
    ParserInfo pi = {
        .error = NO_ERROR,
        .currentResult = 0.0
    };
    Token next_token;

    charList str = charListCreate();

    next_token = PeekNextToken();
    if(next_token.type == PREVIOUS_ANSWER){
        GetNextToken();
        pi.token = next_token;
        pi.currentResult = previousResult;
        return pi;
    }

    if(next_token.value == '('){
        pi = ParseBracket();
        if(pi.error != NO_ERROR){
            return pi;
        }
    } else if(next_token.value == '-' ) {
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

    if (str.length == 0){
        pi.error = MISSING_NUMBER;
        pi.token = next_token;
        return pi;
    }

    pi.token = next_token;
    pi.currentResult = atof(str.values);

    return pi;
}
