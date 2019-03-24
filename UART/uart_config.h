/*
 * uart_config.h
 *
 *  Created on: 2019��3��18��
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

void UART0_Init(uint32_t Baud);

void UART1_Init(uint32_t Baud);
void IntHandler_UART1();

void UART2_Init(uint32_t Baud);
void IntHandler_UART2();

void UART3_Init(uint32_t Baud);
void IntHandler_UART3();

void UART4_Init(uint32_t Baud);
void IntHandler_UART4();

//void UART5_Init(uint32_t Baud);
//void IntHandler_UART5();

void UART7_Init(uint32_t Baud);
void IntHandler_UART7();

#endif /* UART_UART_CONFIG_H_ */
