/*
 * delay.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

void delay_us(uint32_t n);
void delay_ms(uint32_t n);
void delay_s(uint32_t n);


#endif /* DELAY_DELAY_H_ */
