/*
 * patrol_line.c
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */
#include "patrol_line.h"

void patrol_line_init()
{
    uint32_t A_pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    uint32_t B_pin = GPIO_PIN_4 | GPIO_PIN_5;
    uint32_t D_pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    uint32_t E_pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIODirModeSet(GPIO_PORTA_BASE, A_pin, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTB_BASE, B_pin, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTD_BASE, D_pin, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTE_BASE, E_pin, GPIO_DIR_MODE_IN);

    GPIOPadConfigSet(GPIO_PORTA_BASE, A_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTB_BASE, B_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, D_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE, E_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

