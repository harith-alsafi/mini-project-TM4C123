// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>

// #define DEFINE_LIST_PROTOTYPE(Type) \
//     typedef struct { \
//         int length; \
//         int currentIndex; \
//         Type* values; \
//     } Type##List; \
//     \
//     Type##List Type##ListCreate(); \
//     \
//     void Type##ListClear(Type##List* list); \
//     \
//     int Type##ListPushBack(Type##List* list, Type item); \
//     \
//     int Type##ListAddRange(Type##List* list, Type items[], int length); \
//     \
//     int Type##ListInsertAt(Type##List* list, int index, Type item); \
//     \
//     int Type##ListRemoveAt(Type##List* list, int index);

// #define DEFINE_LIST_IMPLEMENTATION(Type) \
//     typedef struct { \
//         int length; \
//         int currentIndex; \
//         Type* values; \
//     } Type##List; \
//     \
//     Type##List Type##ListCreate() { \
//         Type##List list; \
//         list.length = 0; \
//         list.values = NULL; \
//         list.currentIndex = 0; \
//         return list; \
//     } \
//     \
//     void Type##ListClear(Type##List* list) { \
//         free(list->values); \
//         list->values = NULL; \
//         list->length = 0; \
//     } \
//     \
//     int Type##ListPushBack(Type##List* list, Type item) { \
//         list->length++; \
//         list->values = realloc(list->values, list->length * sizeof(Type)); \
//         if (list->values == NULL) { \
//             return -1; \
//         } \
//         list->values[list->length - 1] = item; \
//         return 0; \
//     }\
//     \
//     int Type##ListAddRange(Type##List* list, Type items[], int length) { \
//         for(int i = 0; i < length; i++){ \
//             if(!Type##ListPushBack(list, items[i])){\
//                 return 0;\
//             }\
//         }\
//         return 1; \
//     } \
//     \
//     int Type##ListInsertAt(Type##List* list, int index, Type item) { \
//         if (index < 0 || index > list->length) { \
//             return -1; \
//         } \
//         list->length++; \
//         list->values = realloc(list->values, list->length * sizeof(Type)); \
//         if (list->values == NULL) { \
//             return -1; \
//         } \
//         for (int i = list->length - 1; i > index; i--) { \
//             list->values[i] = list->values[i - 1]; \
//         } \
//         list->values[index] = item; \
//         return 0; \
//     } \
//     \
//     int Type##ListRemoveAt(Type##List* list, int index) { \
//        if (index < 0 || index >= list->length) { \
//             return -1; \
//         } \
//         for (int i = index; i < list->length - 1; i++) { \
//             list->values[i] = list->values[i + 1]; \
//         } \
//         list->length--; \
//         Type *temp = realloc(list->values, list->length * sizeof(Type)); \
//         if (temp != NULL) { \
//             list->values = temp; \
//         } \
//         return 0; \
//     }  

// typedef struct{
//     int value;
//     char key;
// } Token;

// DEFINE_LIST_IMPLEMENTATION(Token);
// DEFINE_LIST_IMPLEMENTATION(int);

// // int main(){
// //     intList list = intListCreate();
// //     intListPushBack(&list, 1);
// //     intListPushBack(&list, 2);
// //     intListPushBack(&list, 3);
// //     intListPushBack(&list, 4);
// //     intListInsertAt(&list, 1, 5);
// //     intListRemoveAt(&list, 2);
// //     intListRemoveAt(&list, list.length-1);
// //     for(int i = 0; i < list.length; i++){
// //         printf("%i", list.values[i]);
// //     }

// //     printf("\n%ls \n", list.values);
// //     // printf("%c \n", list.values[0]);
// // }