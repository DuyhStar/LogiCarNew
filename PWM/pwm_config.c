/*
 * pwm_config.c
 *
 *  Created on: 2019年3月18日
 *      Author: DuYihao
 */
#include "pwm_config.h"


//**********************************************************************************************//
//初始化PWM波，用来控制机械臂上舵机运动
//周期:20ms 频率：50Hz
//初始脉宽：1.5ms
//舵机角度控制：脉冲1ms-2ms为范围
void PWM1_0_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PD0_M1PWM0);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, SysCtlClockGet()/PWM1_DIV/50);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}
void PWM1_1_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PD1_M1PWM1);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, SysCtlClockGet()/PWM1_DIV/50);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}
void PWM1_2_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PA6_M1PWM2);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, SysCtlClockGet()/PWM1_DIV/50);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}
void PWM1_3_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PA7_M1PWM3);
    GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_7);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, SysCtlClockGet()/PWM1_DIV/50);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}
void PWM1_4_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;//解锁
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;//确认
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;//重新锁定

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PF0_M1PWM4);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_0);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, SysCtlClockGet()/PWM1_DIV/50);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_4_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
}
void PWM1_5_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    SysCtlPWMClockSet(PWM1_CLOCK_DIV);

    GPIOPinConfigure(GPIO_PF1_M1PWM5);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, SysCtlClockGet()/PWM1_DIV/50);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_2)*75/1000);//脉宽1.5ms

    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
}


