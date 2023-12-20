#include "helpers.h"

unsigned int Strlen(const char* str) {
    unsigned int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}
