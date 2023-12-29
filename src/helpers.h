#ifndef HELPERS_H   // If not defined
#define HELPERS_H   // Define it

#include <stdlib.h>

#define HIGH 0xFF
#define LOW 0x00
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define DEFINE_LIST_PROTOTYPE(Type) \
    typedef struct { \
        int length; \
        int currentIndex; \
        Type value[]; \
    } Type##List; \
    \
    Type##List* Type##ListCreate(); \
    \
    void Type##ListDestroy(Type##List* list); \
    \
    int Type##ListPushBack(Type##List** list, Type item) ;\
    \
    int Type##ListAddRange(Type##List** list, Type items[], int length); 

#define DEFINE_LIST_IMPLEMENTATION(Type) \
    Type##List* Type##ListCreate() { \
        Type##List* list = (Type##List*)malloc(sizeof(Type##List)); \
        list->length = 0; \
        list->currentIndex = 0; \
        return list; \
    } \
    \
    void Type##ListDestroy(Type##List* list) { \
        free(list); \
    } \
    \
    int Type##ListPushBack(Type##List** list, Type item) { \
        int x = *list ? list[0]->length : 0, y = x + 1; \
        \
        if ((x & y) == 0) { \
            void* temp = realloc(*list, sizeof **list + (x + y) * sizeof list[0]->value[0]); \
            if (!temp) { \
                return 0; \
            } \
            *list = temp; \
        } \
        \
        list[0]->value[x] = item; \
        list[0]->length = y; \
        return 1; \
    }\
    \
    int Type##ListAddRange(Type##List** list, Type items[], int length) { \
        for(int i = 0; i < length; i++){ \
            if(!Type##ListPushBack(list, items[i])){\
                return 0;\
            }\
        }\
        return 1; \
    }



typedef unsigned char byte;

DEFINE_LIST_PROTOTYPE(char);


#endif