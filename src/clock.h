#ifndef CLOCK_H   // If not defined
#define CLOCK_H   // Define it

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

/**
 * @brief Initializes sys tick
 * 
 */
void SysTickInit();

/**
 * @brief Initalizes the PLL to 80 MHz
 * 
 */
void PLLInit();

/**
 * @brief Uses the 80 MHz PLL to create a delay in units of 12.5ns
 * 
 * @param delay delay in units of 12.5ns
 */
void SysTickWait(unsigned long delay);

/**
 * @brief Uses @see SysTickWait() to create a delay in units of nanoseconds
 * 
 * @param nanoseconds delay of nanoseconds
 */
void DelayNano(unsigned long nanoseconds);

/**
 * @brief Uses @see DelayNano() to create a delay in units of microseconds
 * 
 * @param microseconds delay of microseconds
 */
void DelayMicro(unsigned long microseconds);

/**
 * @brief Uses @see DelayMicro() to create a delay in units of milliseconds
 * 
 * @param millisecond delay of milliseconds
 */
void DelayMilli(unsigned long milliseconds);

#endif