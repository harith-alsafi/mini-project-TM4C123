#include "port_init.h"
#include "clock.h"

void PortEInit() {
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010; // 1) E clock
  delay = SYSCTL_RCGC2_R;       // delay
  // GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
  GPIO_PORTE_CR_R |= 0xF;          // allow changes to PE4-0
  GPIO_PORTE_AMSEL_R &= 0x00;      // 3) disable analog function
  GPIO_PORTE_PCTL_R &= 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTE_DIR_R |= 0x0;         // 5.2) PE4-PE0 input
  GPIO_PORTE_AFSEL_R &= 0x0;       // 6) no alternate function
  GPIO_PORTE_PUR_R |= 0x0;         // disable pullup resistors on PE4-PE0
  GPIO_PORTE_PDR_R |= 0xF;         // enable pulldown resistors on PE4-PE0
  GPIO_PORTE_DEN_R |= 0xF;         // 7) enable digital pins PE4-PE0
}

void PortDInit() {
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000008; // 1) D clock
  delay = SYSCTL_RCGC2_R;       // delay
  // GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
  GPIO_PORTD_CR_R |= 0xF;          // allow changes to PD4-0
  GPIO_PORTD_AMSEL_R &= 0x00;      // 3) disable analog function
  GPIO_PORTD_PCTL_R &= 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTD_DIR_R |= 0xF;         // 5.2) PD4-PD0 ouput
  GPIO_PORTD_AFSEL_R &= 0x0;       // 6) no alternate function
  GPIO_PORTD_DEN_R |= 0xF;         // 7) enable digital pins PD4-PD0
}

void PortBInit() {}

void PortAInit() {}