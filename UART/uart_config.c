/*
 * uart_config.c
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */
#include "uart_config.h"


void UART2_Init(uint32_t Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), Baud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTIntRegister(UART2_BASE, IntHandler_UART2);
    UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART2);
}
