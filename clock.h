#define NVIC_ST_CTRL_R (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile unsigned long *)0xE000E018))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

	


void SysTickInit();

void PLLInit();

void DelayMicro(unsigned long millisecond);

void DelayMilli(unsigned long microseconds);
