/*
 * uart_config.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */

#ifndef UART_UART_CONFIG_H_
#define UART_UART_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "utils/uartstdio.h"


void UART2_Init(uint32_t Baud);
void IntHandler_UART2(void);

#endif /* UART_UART_CONFIG_H_ */
