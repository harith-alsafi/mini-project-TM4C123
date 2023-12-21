#ifndef HELPERS_H   // If not defined
#define HELPERS_H   // Define it

#define HIGH 0xFF
#define LOW 0x00
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

typedef unsigned char byte;

/**
 * @brief Gets the length of a string
 * 
 * @param str given string
 * @return `unsigned int` Length of given string <br>
 */
unsigned int Strlen(const char* str);

#endif