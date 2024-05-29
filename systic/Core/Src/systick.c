/*
 * systick.c
 *
 *  Created on: May 29, 2024
 *      Author: boobathi
 */


#include"stm32f4xx.h"
#define SYSTICK_LOAD_VAL			             16000
#define CTRL_ENABLE				            (1U<<0)
#define CTRL_CLKSRC					(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)
void systickDelayMs(int delay);
void systick(void){
	RCC->AHB1ENR |= 1; /* enable GPIOA clock */
	GPIOA->MODER &= ~0x00000C00; /* clear pin mode */
	GPIOA->MODER |= 0x00000400; /* set pin to output mode */
	while(1)
	{
	GPIOA->ODR |= 0x00000020; /* turn on LED */
	systickDelayMs(500);
	GPIOA->ODR &= ~0x00000020; /* turn off LED */
	systickDelayMs(500);
	}
	}
	/* 16 MHz SYSCLK */
	void systickDelayMs(int delay)
	{
                 	SysTick->LOAD	= SYSTICK_LOAD_VAL;
		SysTick->VAL = 0;
		SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
		for(int i=0; i<delay ; i++){
			while((SysTick->CTRL &  CTRL_COUNTFLAG) == 0){}
	}
	SysTick->CTRL = 0;
}
