#ifndef FLASH_STORAGE_H   // If not defined
#define FLASH_STORAGE_H   // Define it

#define FLASH_FMC 
#define FLASH_FMD 
#define FLASH_FMA 

typedef struct {
    int passwordLength;
    char password[];
} FlashData;

void FlashInit();

void FlashWrite(FlashData data);

FlashData FlashRead();

void FlashErase();

#endif