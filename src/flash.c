#include "flash.h"
#include <stdlib.h>
#include <string.h>

int	flashWriteKey = 0;

void FlashInit(){
	if (FLASH_BOOTCFG_R & 0x10) {
		flashWriteKey =	0xA442;
	}
	else {
		flashWriteKey = 0x71D5;
	} 
}

int FlashErase()
{
	for (int i = 0; i < FLASH_NUMBER_BLOCKS; i++) {
		FLASH_FMA_R &= 0xFFFC0000;  
		
		FLASH_FMA_R |= (volatile unsigned long)FLASH_BASE_ADDR + (i*FLASH_KB);
		
		FLASH_FMC_R = (flashWriteKey << 16) | 0x2; 

		while (FLASH_FMC_R & 0x2) {}
	}
	
	return 1;
}

bool FlashDataIsRead(FlashData data){
	return 
	data.passwordLength >= 0 && 
	strlen(data.password) == data.passwordLength;
}

int FlashWrite(FlashData data){
	FlashErase();
	
	for (int i = 0; i < FLASH_BLOCK_SIZE; i++) {
	
		FLASH_FMD_R = ((volatile unsigned long*)&data)[i];
		
		FLASH_FMA_R &= 0xFFFC0000;  
		FLASH_FMA_R |= (volatile unsigned long)FLASH_BASE_ADDR + (i * sizeof(unsigned long));
		
		FLASH_FMC_R = (flashWriteKey << 16) | 0x1; 

		while (FLASH_FMC_R & 0x1) {}
	}
	
	return 1;

}

FlashData FlashRead(){
    FlashData data = {
        .passwordLength  = 0,
        .password = NULL,
    };
	for (int i = 0; i < FLASH_BLOCK_SIZE; i++) {
		((unsigned long*)&data)[i] = FLASH_BASE_ADDR[i];
	}
    return data;
}

	