#include "../src/parser.h"
#include <math.h>
#include <stdio.h>
#include "../lib/minunit/minunit.h"

MU_TEST(TestBracket){
    printf("TestBracket \n");
    // (2^(2+1)-2)x0.5 = 3
    Token tokens[] = {
        {
            .type = OPERATOR, 
            .value = '('
        },
        {
            .type = NUMBER, 
            .value = '2'
        },
        {
            .type = OPERATOR, 
            .value = '^'
        },
        {
            .type = OPERATOR, 
            .value = '('
        },
        {
            .type = NUMBER,
            .value = '2'
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
            .type = OPERATOR,
            .value = ')'
        },
        {
            .type = OPERATOR,
            .value = '-'
        },
        {
            .type = NUMBER,
            .value = '2'
        },
        {
            .type = OPERATOR,
            .value = ')'
        },
        {
            .type = OPERATOR,
            .value = 'x'
        },
        {
            .type = NUMBER,
            .value = '0'
        },
        {
            .type = DECIMAL,
            .value = '.'
        },
        {
            .type = NUMBER,
            .value = '5'
        }
    };
    ParserInitWith(tokens, 15);
    ParserInfo pi = ParserCompile();
    ParserStop();
    mu_assert_double_eq(3.0, pi.currentResult);
}

MU_TEST(TestParse){
    printf("TestParse \n");
    // 15.2E-3.4+2/4-5^3+2x5+1
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
            .type = OPERATOR,
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
            .value = 'x'
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
    ParserInitWith(tokens, 23);
    ParserInfo pi = ParserCompile();
    ParserStop();
    mu_assert_double_eq(-113.5, pi.currentResult);
}

MU_TEST(TestNumberParser){
    printf("TestNumberParser \n");
   ParserInit();
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = '-'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '1'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '2'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '3'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '5'
    });
    ParserPushToken((Token){
        .type = DECIMAL, 
        .value = '.'
    });
    ParserPushToken((Token){
        .type = DECIMAL, 
        .value = '2'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '4'
    });
    ParserPushToken((Token){
        .type = EOL, 
        .value = ' '
    });
    ParserInfo number = ParserCompile();
    ParserStop();
    mu_assert_double_eq((float)-1235.24, number.currentResult);
}

MU_TEST(TestSimple){
printf("TestSimple \n");
   ParserInit();
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '5'
    });
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = '+'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '2'
    });
    ParserEndInput();
    ParserInfo number = ParserCompile();
    ParserReset();
    mu_assert_double_eq(7.0, number.currentResult);

    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '2'
    });
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = 'x'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '5'
    });
    ParserEndInput();
    number = ParserCompile();
    ParserReset();
    mu_assert_double_eq(10.0, number.currentResult);
}

MU_TEST(TestNegativePower){
    printf("TestNegativePower \n");
   ParserInit();
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '5'
    });
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = '^'
    });
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = '('
    });
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = '-'
    });
    ParserPushToken((Token){
        .type = NUMBER, 
        .value = '2'
    });
    ParserPushToken((Token){
        .type = OPERATOR, 
        .value = ')'
    });
    ParserEndInput();
    ParserInfo number = ParserCompile();
    ParserStop();
    printf("E:%i \n", number.error);
    mu_assert_double_eq((float)0.04, number.currentResult);
}

MU_TEST_SUITE(TestSuite) {
	MU_RUN_TEST(TestNumberParser);
    MU_RUN_TEST(TestParse);
    MU_RUN_TEST(TestBracket);
    MU_RUN_TEST(TestSimple);
    MU_RUN_TEST(TestNegativePower);
}

int main() {
	MU_RUN_SUITE(TestSuite);
	MU_REPORT();
    return 0;
}
