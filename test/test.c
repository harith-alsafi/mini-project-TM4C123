#include "../src/expression-parser.h"
#include <stdio.h>

int main() {
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
    printf("String: %s\n", number.string->value);
    printf("Number: %f\n", number.value);
    StopParser();
    return 0;
}
