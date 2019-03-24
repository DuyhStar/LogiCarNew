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
    SysTickEnable();
    //SysTickDisable();
    IntMasterDisable();
}

void timer0_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    TimerPrescaleSet(TIMER0_BASE, TIMER_A, 100);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/10);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0IntHandler);

    TimerDisable(TIMER0_BASE, TIMER_A);
    //TimerEnable(TIMER0_BASE, TIMER_A);
}
