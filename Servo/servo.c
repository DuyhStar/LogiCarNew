/*
 * servo.c
 *
 *  Created on: 2019年3月18日
 *      Author: DuYihao
 */
#include "servo.h"

void servo_init(uint16_t *init_angle)
{
    PWM1_0_Init();
    PWM1_1_Init();
    PWM1_2_Init();
    PWM1_3_Init();
    int i = 0;
    for(;i<4;i++)
        servo_pulse_set(i, init_angle[i]);
}

void servo_pulse_set(uint8_t num, uint16_t us)
{
    uint32_t pulse = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*us/20000;

    switch(num)
    {
    case 0:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, pulse);
        break;
    case 1:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_1, pulse);
        break;
    case 2:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, pulse);
        break;
    case 3:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, pulse);
        break;
    default:
        break;
    }
}

void servo_n_angle_set(uint8_t n, uint16_t angle)
{
    static uint16_t angle_last[4] = {1500,1350,680,1100};;//机械臂初始化位置

    uint16_t t = angle_last[n];
    //步进5表示舵机的分辨率
    while(1)
    {
        if(t - angle < -5)
            t+=5;
        else if(t - angle > 5)
            t-=5;
        else
        {
            servo_pulse_set(n, t);
            break;
        }
        servo_pulse_set(n, t);
        delay_ms(10);               //延时时间用以控制舵机运行速度
    }

    //保存此次舵机位置
    angle_last[n] = angle;
}

void hand_set_servo()
{
    extern uint8_t  servoUpdate;//global variables, defined in main.c
    extern uint16_t servoVal[4];//

    while(1){
        while(!servoUpdate)
            ;
        servoUpdate = 0;

        servo_n_angle_set(0, servoVal[0]);
        servo_n_angle_set(1, servoVal[1]);
        servo_n_angle_set(2, servoVal[2]);
        servo_n_angle_set(3, servoVal[3]);
    }
}
