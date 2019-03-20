/*
 * gpio_config.c
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */
#include "gpio_config.h"

void key1_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

uint8_t Key1_Read()
{
    uint8_t s;
    s = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

    if(s != GPIO_PIN_4)
        return 1;
    else
        return 0;
}

void system_waitKey()
{
    while(1)
    {
        if(Key1_Read() == 1)
        {
            delay_ms(20);
            if(Key1_Read() == 1)
                break;
        }
    }
}
