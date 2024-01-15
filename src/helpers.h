#ifndef HELPERS_H   // If not defined
#define HELPERS_H   // Define it

#include <stdlib.h>

#define HIGH 0xFF
#define LOW 0x00
#define ARRAY_MAX_LENGTH 100

#define DEFINE_LIST_PROTOTYPE(Type) \
    typedef struct { \
        int length; \
        int currentIndex; \
        Type values[ARRAY_MAX_LENGTH]; \
    } Type##List; \
    \
    Type##List Type##ListCreate(); \
    \
    void Type##ListClear(Type##List* list); \
    \
    int Type##ListPushBack(Type##List* list, Type item); \
    \
    int Type##ListAddRange(Type##List* list, Type items[], int length); \
    \
    int Type##ListInsertAt(Type##List* list, int index, Type item); \
    \
    int Type##ListRemoveAt(Type##List* list, int index);

#define DEFINE_LIST_IMPLEMENTATION(Type) \
    Type##List Type##ListCreate() { \
        Type##List list; \
        list.length = 0; \
        list.currentIndex = 0; \
        return list; \
    } \
    \
    void Type##ListClear(Type##List* list) { \
        list->length = 0; \
        list->currentIndex = 0; \
    } \
    \
    int Type##ListPushBack(Type##List* list, Type item) { \
        list->length++; \
        list->values[list->length - 1] = item; \
        return 1; \
    }\
    \
    int Type##ListAddRange(Type##List* list, Type items[], int length) { \
        for(int i = 0; i < length; i++){ \
            if(!Type##ListPushBack(list, items[i])){\
                return 0;\
            }\
        }\
        return 1; \
    } \
    \
    int Type##ListInsertAt(Type##List* list, int index, Type item) { \
        if (index < 0 || index > list->length) { \
            return 0; \
        } \
        list->length++; \
        for (int i = list->length - 1; i > index; i--) { \
            list->values[i] = list->values[i - 1]; \
        } \
        list->values[index] = item; \
        return 1; \
    } \
    \
    int Type##ListRemoveAt(Type##List* list, int index) { \
        if (index < 0 || index >= list->length) { \
            return 0; \
        } \
        for (int i = index; i < list->length - 1; i++) { \
            list->values[i] = list->values[i + 1]; \
        } \
        list->length--; \
        return 1; \
    }  

typedef unsigned char byte;

DEFINE_LIST_PROTOTYPE(char);

/**
 * @brief 
 * 
 * @return `int`  <br>
 */
int Random();

/**
 * @brief 
 * 
 * @param min 
 * @param max 
 * @return `int`  <br>
 */
int RandomRange(int min, int max);

#endif