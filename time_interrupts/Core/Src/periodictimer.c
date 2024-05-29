/*
 * periodictimer.c
 *
 *  Created on: May 29, 2024
 *      Author: boobathi
 */


#include "stm32f4xx.h"
#define PERIOD 1000
void TIM2_IRQHandler(void);
void periodictimer(void)
{
__disable_irq();
RCC->AHB1ENR |= 1;
GPIOA->MODER &= ~0x00000C00;
GPIOA->MODER |= 0x00000800;
GPIOA->AFR[0] = 0x00100000;
RCC->APB1ENR |= 1; /* enable TIM2 clock */
TIM2->PSC = 16000 - 1; /* divided by 16000 */
TIM2->ARR = 0xFFFF; /* max count */
TIM2->CCR1 = PERIOD;
TIM2->CNT = 0;
TIM2->CCMR1 = 0x30; /* Output compare toggle */
TIM2->CCER = 1; /* CC1 enable */
TIM2->CR1 = 1; /* enable counter */
TIM2->DIER |= 2; /* enable CC1IE */
NVIC_EnableIRQ(TIM2_IRQn); /* enable interrupt in NVIC */
__enable_irq(); /* global enable IRQs */
while(1) { }
}
void TIM2_IRQHandler(void)
{
 TIM2->SR = 0; /* clear UIF */
TIM2->CCR1 = (TIM2->CCR1 + PERIOD) & 0xFFFF; /* update CCR1 */
}
