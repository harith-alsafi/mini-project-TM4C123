#ifndef FLASH_STORAGE_H   // If not defined
#define FLASH_STORAGE_H   // Define it

#define FLASH_BOOTCFG_R         (*((volatile unsigned long *)0x400FE1D0))
#define FLASH_FMA_R             (*((volatile unsigned long *)0x400FD000))
#define FLASH_FMD_R             (*((volatile unsigned long *)0x400FD004))
#define FLASH_FMC_R             (*((volatile unsigned long *)0x400FD008))
#define FLASH_BASE_ADDR         (((volatile unsigned long *)0x00020000))
#define FLASH_KB 1024

#include <stdbool.h>
#include "helpers.h"

typedef struct {
    int passwordLength;
    char password[ARRAY_MAX_LENGTH];
} FlashData;

#define FLASH_BLOCK_SIZE sizeof(FlashData) / sizeof(unsigned long)
#define FLASH_NUMBER_BLOCKS (((FLASH_BLOCK_SIZE * sizeof(unsigned long)) / 1024) + 1)

/**
 * @brief Initializes flash storage
 * 
 */
void FlashInit();

/**
 * @brief Writes data to flash
 * 
 * @param data 
 * @return int 
 */
int FlashWrite(FlashData data);

/**
 * @brief Reads data from flash
 * 
 * @return FlashData 
 */
FlashData FlashRead();

/**
 * @brief Erases flash
 * 
 * @return int 
 */
int FlashErase();

/**
 * @brief Checks if flash data is read
 * 
 * @param data 
 * @return true 
 * @return false 
 */
bool FlashDataIsRead(FlashData data);

#endif