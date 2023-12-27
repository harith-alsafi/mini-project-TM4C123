#include "program-logic.h"
#include "hardware-test.h"
// #include <stdio.h>
#include "ports.h"


int main() {
    InitAll();


    while (1){
        RunAll();
    
        // printf("%ld\n", GPIO_PORTE_DATA_R);
        
    }
}