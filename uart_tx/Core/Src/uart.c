/*
 * uart.c
 *
 *  Created on: May 29, 2024
 *      Author: boobathi
 */


#include "uart.h"

#define GPIOAEN     (1U<<0)
#define PA2MOD      (2U<<4)
#define PA2AF       (7U<<8)
#define APB1EN      (1U<<17)
#define USART2_TX   (1U<<3)
#define USART2EN    (1U<<13)
#define SR_TXE      (1U<<7)


#define SYS_FREQ        16000000
#define APB1_CLK        SYS_FREQ
#define UART_BAUDRATE   115200



static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);



void delayMs(int n)
{
    for (; n > 0; n--)
        for (int i = 0; i < 5000; i++);

}

void uart2_init(void)
{
    // Enable clock access to GPIOA
    RCC->AHB1ENR |= GPIOAEN;

    // Set PA2 mode to alternate function mode
    GPIOA->MODER |= PA2MOD;
    // Set PA2 alternate function type to UART_TX (AF07)
    GPIOA->AFR[0] |= PA2AF;

    // Enable clock access to USART2
    RCC->APB1ENR |= APB1EN;

    // Configure baudrate
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    // Configure the transfer direction
    USART2->CR1 = USART2_TX;

    // Enable USART2 module
    USART2->CR1 |= USART2EN;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
    return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

void uart2_write(int ch)
{
    // Make sure the transmit data register is empty
    while(!(USART2->SR & SR_TXE));

    // Write to transmit data register
    USART2->DR = (ch & 0xFF);
}
