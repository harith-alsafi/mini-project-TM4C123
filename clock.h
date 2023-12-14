//GPIO clocks
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

//PLL related Defines
#define SYSCTL_RIS_R          (*((volatile unsigned long *)0x400FE050))	
#define SYSCTL_RCC_R          (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R         (*((volatile unsigned long *)0x400FE070))	

//SysTick related Defines	
#define NVIC_ST_CTRL_R        (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R     (*((volatile unsigned long *)0xE000E018))

void SysTickInit();

void PLLInit();

void SysTickWait(unsigned long delay);

void DelayMicro(unsigned long microseconds);

void DelayMilli(unsigned long millisecond);