/*
 * car_ctrl.c
 *
 *  Created on: 2019��3��18��
 *      Author: DuYihao
 */

/*
 * cal.c
 *
 *  Created on: 2018��7��13��
 *      Author: D
 */
#include "car_ctrl.h"

//С����������PWM����ʼ��
void car_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    PWM0_0_Init();
    PWM0_1_Init();

    car_speed(10);
    car_stop_free();
}

//ǰ��
void car_forward(uint16_t speed)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);

    car_speed(speed);
}

//����
void car_back(uint16_t speed)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);

    car_speed(speed);
}

//ǰ�����˵���ת��ת(����ת����ǰ����˵��ʵһ��)
void car_turn_left(uint16_t range)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);

    car_speed(range);
}
void car_turn_right(uint16_t range)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);

    car_speed(range);
}

void car_speed(uint16_t speed)
{
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, speed*(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)/100));
}

//ǰ�����˲�Ѳ��
void car_forward_patrol_line()
{
}
void car_back_patrol_line()
{
}
void car_forward_patrol_line_inside()
{
}
void car_back_patrol_line_inside()
{
}

//ԭ������ת90��
void car_turn_left_90_degree()
{
}
void car_turn_right_90_degree()
{
}

//ǰ������n������
void car_forward_goto_n_black_line(uint8_t n)
{

}
void car_back_goto_n_black_line(uint8_t n)
{
}
void car_forward_goto_n_black_line_inside(uint8_t n)
{
}
void car_back_goto_n_black_line_inside(uint8_t n)
{
}

void car_begin_goto_first_pos()
{
    extern int forward_speed;
    extern int turn_speed;

    car_forward(forward_speed);
    while(!m_black())
        ;
    car_stop_hurry();

    car_turn_right(turn_speed);
    while(!f[3])
        ;
    car_stop_hurry();
}

//һЩֹͣ����
void car_stop_free(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);
}
void car_stop_hurry(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
}




