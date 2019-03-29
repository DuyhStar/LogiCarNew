/*
 * servo.c
 *
 *  Created on: 2019年3月18日
 *      Author: DuYihao
 */
#include "servo.h"

void servo_init(uint16_t *init_angle)
{
    PWM1_2_Init();
    PWM1_3_Init();
    PWM1_4_Init();
    PWM1_5_Init();
    servo_pulse_set(0, init_angle[0]);
    servo_pulse_set(1, init_angle[1]);
    servo_pulse_set(2, init_angle[2]);
    servo_pulse_set(3, init_angle[3]);
}

void servo_pulse_set(uint8_t num, uint16_t us)
{
    uint32_t pulse = PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1);
    pulse = pulse*us/20000;

    switch(num)
    {
    case 0:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, pulse);
        break;
    case 1:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, pulse);
        break;
    case 2:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_4, pulse);
        break;
    case 3:
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, pulse);
        break;
    default:
        break;
    }
}

void servo_n_angle_set(uint8_t n, uint16_t angle)
{
    static uint16_t angle_last[4] = {1500,1500,1500,1130};;//机械臂初始化位置

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
        delay_ms(15);               //延时时间用以控制舵机运行速度
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
//获得抓取的位置
//input:第n次抓取(1~3)
//output:抓什么位置(1~3)
uint8_t get_take_pos(uint8_t n)
{
    extern uint8_t task[3];
    extern uint8_t color[3];
    int i = 0;
    for(;i<3;i++)
    {
        if(task[n-1] == color[i])
        {
            break;
        }
    }
    return i+1;
}
//左右移动：左加右减
void take(uint8_t pos)
{
    extern int forward_speed;
    switch(pos)
    {
    case 1:
        //夹取
        servo_n_angle_set(0, 1690);

        servo_n_angle_set(1, 860);
        servo_n_angle_set(2, 1750);
        car_forward(40);
        delay_ms(100);
        car_stop();
        servo_n_angle_set(3, 2130);
        //归位
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    case 2:
        car_back(40);
        delay_ms(100);
        car_stop();
        //夹取
        servo_n_angle_set(0, 1440);
        servo_n_angle_set(1, 860);
        servo_n_angle_set(2, 1750);
        servo_n_angle_set(3, 2130);
        //归位
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    case 3:
        //夹取
        servo_n_angle_set(0, 1200);
        servo_n_angle_set(1, 860);
        servo_n_angle_set(2, 1750);
        car_forward(40);
        delay_ms(100);
        car_stop();
        servo_n_angle_set(3, 2130);
        //归位
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    default:
        tmp_show('$','$','$');
        break;
    }
}
//左加右减，0
//上，1，2
void place(uint8_t pos)
{
    extern uint8_t red_pos, blue_pos;

    if(pos == red_pos){
        //放下
        servo_n_angle_set(0, 2080);
        servo_n_angle_set(1, 2230);
        servo_n_angle_set(2, 1500);
        servo_n_angle_set(3, 1130);
        //归位
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
    }
    else if(pos == 2){
        //放下
        servo_n_angle_set(0, 1470);
        servo_n_angle_set(1, 2230);
        servo_n_angle_set(2, 1500);
        servo_n_angle_set(3, 1130);
        //归位
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
    }
    else if(pos == blue_pos){
        //放下
        servo_n_angle_set(0, 890);
        servo_n_angle_set(1, 2230);
        servo_n_angle_set(2, 1500);
        servo_n_angle_set(3, 1130);
        //归位
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
    }
    else{
        tmp_show('#','#','#');
    }
}
