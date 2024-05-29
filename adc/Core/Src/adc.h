/*
 * adc.h
 *
 *  Created on: May 29, 2024
 *      Author: boobathi
 */

#ifndef SRC_ADC_H_
#define SRC_ADC_H_

#include <stdint.h>
void pa1_adc_init(void);
uint32_t adc_read(void);
void start_converstion(void);

#endif /* SRC_ADC_H_ */
