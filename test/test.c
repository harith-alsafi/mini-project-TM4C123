#include "../src/expression-parser.h"
#include <stdio.h>
#include "../lib/minunit/minunit.h"


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
    NumberDefinition number = ParseNumber();
    StopParser();
    mu_assert_double_eq(-1235.24, number.value);
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(TestNumberParser);
}


int main() {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
    return 0;
}
