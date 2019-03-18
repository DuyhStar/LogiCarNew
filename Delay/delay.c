/*
 * delay.c
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */
#include "delay.h"

void delay_s(uint32_t n)
{
    uint32_t i = 0;
    for(;i<n;i++)
        SysCtlDelay(SysCtlClockGet()/3);
}

void delay_ms(uint32_t n)
{
    uint32_t i = 0;
    for(;i<n;i++)
        SysCtlDelay(SysCtlClockGet()/3000);
}

void delay_ns(uint32_t n)
{
    uint32_t i = 0;
    for(;i<n;i++)
        SysCtlDelay(SysCtlClockGet()/3000000);
}
