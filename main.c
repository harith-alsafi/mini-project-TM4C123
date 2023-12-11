#include "port_init.h"

// LCD Port and Pin Definitions
#define LCD_DATA_PORT GPIO_PORTB_DATA_R  
#define LCD_EN_PORT   GPIO_PORTA_DATA_R
#define LCD_EN_PIN    (1<<2)
#define LCD_RS_PORT   GPIO_PORTA_DATA_R   
#define LCD_RS_PIN    (1<<3)
// LCD Instruction Codes
#define LCD_CLEAR           0x01 
#define LCD_RETURN_HOME     0x02
#define LCD_ENTRY_MODE      0x06
#define LCD_DISPLAY_ON      0x0C

void Delay1ms(unsigned long milliseconds){
	unsigned long volatile time = milliseconds*(72724*2/91);
  while(time){
     time--;
  }
}


void SendDisplayNibble(unsigned char nibble, unsigned char mode) {

  LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (nibble & 0xF0);
  
  if(mode == 0) {
    LCD_RS_PORT &= ~LCD_RS_PIN; 
  } else {
    LCD_RS_PORT |= LCD_RS_PIN;  
  }
  
  LCD_EN_PORT |= LCD_EN_PIN;  
  Delay1ms(1); 
  LCD_EN_PORT &= ~LCD_EN_PIN;
  Delay1ms(1);  
}

void InitDisplay() {

	
  // Initialization sequence
  Delay1ms(30); 
  
  SendDisplayNibble(0x03, 0);
  Delay1ms(5); 
  
  SendDisplayNibble(0x03, 0);
  Delay1ms(1); 
  
  SendDisplayNibble(0x03, 0); 
  Delay1ms(1); 
   
  SendDisplayNibble(0x02, 0); 
  
  // Function set  
  SendDisplayNibble(0x28, 0);   
  SendDisplayNibble(0x08, 0);
   
  // Display clear
  SendDisplayNibble(0x01, 0); 
  Delay1ms(2); 
   
  // Entry mode  
  SendDisplayNibble(0x06, 0);
  
  // Display on
  SendDisplayNibble(0x0C, 0); 
}

void PrintString(char *str) {
  while(*str) {
    SendDisplayNibble((*str>>4)&0x0F, 1); // Send upper nibble
    SendDisplayNibble(*str&0x0F, 1);      // Send lower nibble   
    str++; 
  }
}


int main() { 
	PortAInit();
	PortBInit();
  
	InitDisplay(); // Initialize LCD
  
  SendDisplayNibble(LCD_CLEAR, 0); // Clear display
  Delay1ms(2);
   
  SendDisplayNibble(LCD_RETURN_HOME, 0); // Return cursor to home 
  Delay1ms(2);

  PrintString("hi"); // Print "hi" on LCD

  while(1);
}