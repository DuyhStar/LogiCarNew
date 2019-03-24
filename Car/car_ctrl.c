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

    car_speed(5);
    car_stop();
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

//ǰ������n������
void car_forward_goto_n_black_line(uint8_t n, uint8_t line_wide)
{
    extern uint8_t count_enter;//ȫ�ֱ���

    TimerEnable(TIMER0_BASE, TIMER_A);
    uint8_t count = 0;
    while(1)
    {
        forward_patrol_line(line_wide);

        //ÿ��500ms����һ�κ��߼��
        if(m_black()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            TimerEnable(TIMER0_BASE, TIMER_A);
        }

        //������n������
        if(count == n){
            TimerDisable(TIMER0_BASE, TIMER_A);
            count_enter = 0;
            car_stop();
            break;
        }
    }
}
void car_back_goto_n_black_line(uint8_t n, uint8_t line_wide)
{
    extern uint8_t count_enter;//ȫ�ֱ���

    TimerEnable(TIMER0_BASE, TIMER_A);
    uint8_t count = 0;
    while(1)
    {
        back_patrol_line(line_wide);

        //ÿ��500ms����һ�κ��߼��
        if(m_black()&&(count_enter == 1)){
            count++;
            count_enter = 0;
            TimerEnable(TIMER0_BASE, TIMER_A);
        }

        //������n������
        if(count == n){
            TimerDisable(TIMER0_BASE, TIMER_A);
            count_enter = 0;
            car_stop();
            break;
        }
    }
}

void car_begin_goto_first_pos()
{
    extern uint8_t f[8];
    extern int forward_speed;
    extern int turn_speed;

    car_forward(forward_speed);
    while(!m_black())
        ;
    car_stop();

    car_turn_right(turn_speed);
    while(!f[3])
        ;
    car_stop();
}

//ɲ��
void car_stop(void)
{
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
}

void car_return()
{
    extern int turn_speed, forward_speed;
    extern uint8_t b[8], f[8];
    car_turn_left(turn_speed);
    while(!(b[5]||b[6]))
        ;
    car_back_goto_n_black_line(2, 1);

    car_turn_left(turn_speed);
    while(!b[0])
        ;
    car_turn_left(turn_speed);
    delay_ms(500);

    car_back_goto_n_black_line(2, 0);

    while(1)
    {
        back_patrol_line(0);
        if(f[0]||f[6]){
            car_stop();
            break;
        }
    }
    car_turn_right(turn_speed);
    delay_ms(1000);
    car_back(forward_speed);
    delay_ms(800);
    car_stop();
    while(1)
    {
    }
}


