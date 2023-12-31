#include "../src/expression-parser.h"
#include <stdio.h>
#include "../lib/minunit/minunit.h"

MU_TEST(TestParse){
    // 15.2E-3.4+2/4-5^3+2*5+1
    Token tokens[] = {
        {
            .type = NUMBER, 
            .value = '1'
        },
        {
            .type = NUMBER, 
            .value = '5'
        },
        {
            .type = DECIMAL, 
            .value = '.'
        },
        {
            .type = DECIMAL, 
            .value = '2'
        },
        {
            .type = OPERATOR,
            .value = 'E'
        },
        {
            .type = NEGATIVE,
            .value = '-'
        },
        {
            .type = NUMBER,
            .value = '3'
        },
        {
            .type = NUMBER,
            .value = '4'
        },
        {
            .type = OPERATOR,
            .value = '+'
        },
        {
            .type = NUMBER,
            .value = '2'
        },
        {
            .type = OPERATOR,
            .value = '/'
        },
        {
            .type = NUMBER,
            .value = '4'
        },
        {
            .type = OPERATOR,
            .value = '-'
        },
        {
            .type = NUMBER,
            .value = '5'
        },
        {
            .type = OPERATOR,
            .value = '^'
        },
        {
            .type = NUMBER,
            .value = '3'
        },
        {
            .type = OPERATOR,
            .value = '+'
        },
        {
            .type = NUMBER,
            .value = '2'
        },
        {
            .type = OPERATOR,
            .value = '*'
        },
        {
            .type = NUMBER,
            .value = '5'
        },
        {
            .type = OPERATOR,
            .value = '+'
        },
        {
            .type = NUMBER,
            .value = '1'
        },
        {
            .type = EOL, 
            .value = ' '
        }
    };
    InitPasrserWith(tokens, 23);
    ParserInfo pi = Parse();
    StopParser();
    mu_assert_double_eq(-113.5, pi.currentReuslt);
    printf("Result: %f\n", pi.currentReuslt);
}

MU_TEST(TestNumberParser){
   InitPasrser();
    PushToken((Token){
        .type = NEGATIVE, 
        .value = '-'
    });
    PushToken((Token){
        .type = NUMBER, 
        .value = '1'
    });
    PushToken((Token){
        .type = NUMBER, 
        .value = '2'
    });
    PushToken((Token){
        .type = NUMBER, 
        .value = '3'
    });
    PushToken((Token){
        .type = NUMBER, 
        .value = '5'
    });
    PushToken((Token){
        .type = DECIMAL, 
        .value = '.'
    });
    PushToken((Token){
        .type = DECIMAL, 
        .value = '2'
    });
    PushToken((Token){
        .type = NUMBER, 
        .value = '4'
    });
    PushToken((Token){
        .type = EOL, 
        .value = ' '
    });
    ParserInfo number = Parse();
    StopParser();
    mu_assert_double_eq(-1235.24, number.currentReuslt);
}

MU_TEST_SUITE(TestSuite) {
	MU_RUN_TEST(TestNumberParser);
    MU_RUN_TEST(TestParse);
}


int main() {
	MU_RUN_SUITE(TestSuite);
	MU_REPORT();
    return 0;
}
