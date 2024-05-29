/*
 * uart.h
 *
 *  Created on: May 29, 2024
 *      Author: boobathi
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void uart2_tx_init(void);
char uart2_read(void);
void uart2_rxtx_init(void);

#endif /* SRC_UART_H_ */
