/*
 * timer_config.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */

#ifndef TIMER_TIMER_CONFIG_H_
#define TIMER_TIMER_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
void SysTick_Init_ms(uint8_t ui8IntTime);
void IntHandler_SysTick(void);

void timer0_init();
void Timer0IntHandler();


#endif /* TIMER_TIMER_CONFIG_H_ */
