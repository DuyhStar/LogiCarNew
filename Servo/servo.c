/*
 * servo.c
 *
 *  Created on: 2019��3��18��
 *      Author: DuYihao
 */
#include "servo.h"

void servo_init(uint16_t *init_angle)
{
    PWM1_2_Init();
    PWM1_3_Init();
    PWM1_4_Init();
    PWM1_5_Init();
    int i = 0;
    for(;i<4;i++)
        servo_pulse_set(i, init_angle[i]);
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
    static uint16_t angle_last[4] = {1500,1500,1500,1130};;//��е�۳�ʼ��λ��

    uint16_t t = angle_last[n];
    //����5��ʾ����ķֱ���
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
        delay_ms(15);               //��ʱʱ�����Կ��ƶ�������ٶ�
    }

    //����˴ζ��λ��
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
//���ץȡ��λ��
//input:��n��ץȡ(1~3)
//output:ץʲôλ��(1~3)
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
//�����ƶ�������Ҽ�
void take(uint8_t pos)
{
    extern int forward_speed;
    switch(pos)
    {
    case 1:
        //��ȡ
        servo_n_angle_set(0, 1660);

        servo_n_angle_set(1, 860);
        servo_n_angle_set(2, 1750);
        car_forward(40);
        delay_ms(100);
        car_stop();
        servo_n_angle_set(3, 2130);
        //��λ
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    case 2:
        car_back(40);
        delay_ms(100);
        car_stop();
        //��ȡ
        servo_n_angle_set(0, 1440);
        servo_n_angle_set(1, 860);
        servo_n_angle_set(2, 1750);
        servo_n_angle_set(3, 2130);
        //��λ
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    case 3:
        //��ȡ
        servo_n_angle_set(0, 1200);
        servo_n_angle_set(1, 860);
        servo_n_angle_set(2, 1750);
        car_forward(40);
        delay_ms(100);
        car_stop();
        servo_n_angle_set(3, 2130);
        //��λ
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    default:
        tmp_show('$','$','$');
        break;
    }
}
void place(uint8_t pos)
{
    switch(pos)
    {
    case 1:
        //����
        servo_n_angle_set(0, 1990);
        servo_n_angle_set(1, 2230);
        servo_n_angle_set(2, 1370);
        servo_n_angle_set(3, 1130);
        //��λ
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    case 2:
        //����
        servo_n_angle_set(0, 1440);
        servo_n_angle_set(1, 2230);
        servo_n_angle_set(2, 1370);
        servo_n_angle_set(3, 1130);
        //��λ
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    case 3:
        //����
        servo_n_angle_set(0, 890);
        servo_n_angle_set(1, 2230);
        servo_n_angle_set(2, 1370);
        servo_n_angle_set(3, 1130);
        //��λ
        servo_n_angle_set(1, 1500);
        servo_n_angle_set(2, 1570);
        servo_n_angle_set(0, 1440);
        break;
    default:
        tmp_show('#','#','#');
        break;
    }
}
