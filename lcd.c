#include "lcd.h"


#define LCD_DB GPIO_PORTB_DATA_R
#define LCD_EN GPIO_PORTB_DATA_R&0x4;
#define LCD_RS GPIO_PORTB_DATA_R&0x8;