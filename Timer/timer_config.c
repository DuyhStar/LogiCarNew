/*
 * timer_config.c
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */
#include "timer_config.h"

void SysTick_Init_ms(uint8_t ui8IntTime)
{
    SysTickPeriodSet((SysCtlClockGet()/1000)*ui8IntTime);

    SysTickIntRegister(IntHandler_SysTick);
    SysTickIntEnable();
    //SysTickEnable();
    SysTickDisable();
    IntMasterDisable();
}

