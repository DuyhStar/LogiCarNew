#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "gpio_config.h"
#include "i2c_config.h"
#include "pwm_config.h"
#include "uart_config.h"
#include "timer_config.h"
#include "patrol_line.h"
#include "car_ctrl.h"
#include "servo.h"
#include "delay.h"
#include "display.h"

#define STOP while(1);

int      turn_speed    = 25;                            //
int      forward_speed = 40;                            //
uint16_t servoVal[4]   = {1500,1500,1500,1130};          //�����ʼ���Ƕ�ֵ
uint8_t  servoUpdate   = 0;                             //
uint8_t  count_enter   = 0;                             //
uint8_t  qr_code_get   = 0;
uint8_t  color_get     = 0;
uint8_t  f[8];
uint8_t  b[8];

uint8_t  task[3]       = {2,1,3};                       //�Ӷ�ά���ж�ȡ��������Ϣ(1:��. 2:��. 3:��.)
uint8_t  color[3]      = {3,2,1};                       //���ڷŵ���ɫ˳��

int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);

    UART0_Init(115200);                 //����
    UART1_Init(9600);                   //openMV
    IntDisable(INT_UART1);
    UART7_Init(9600);                   //ɨ��
    patrol_line_init();                 //Ѳ�����ô���3,4 PD3
    UART2_Init(9600);                   //������
    key1_init();                        //����
    car_init();                         //С������PWM��IO
    timer0_init();                      //��ʱ����ʼ��,�������Ƽ���ѭ��

    //���°���,��ʼ����
    system_waitKey();
    IntMasterEnable();
    servo_init(servoVal);               //�������4·PWM
    delay_s(3);


    car_begin_goto_first_pos();             //С����������һ���ߣ�Ȼ��ԭ����ת90��,��ʻ����һ��ʮ�ֽ����
    car_forward_goto_n_black_line(7, 1);    //С��Ѳ��ǰ��,����ʼ��������ʻ����ά�봦

    //��ȡ��ά��
    while(1)
    {
        servo_n_angle_set(0,1300);
        servo_n_angle_set(0,1700);
        if(qr_code_get){
            qr_code_get = 0;
            IntDisable(INT_UART7);
            task_show();
            servo_n_angle_set(0,1500);
            break;
        }
    }

    car_back_goto_n_black_line(3, 1);       //С���Ӷ�ά�봦����,��ʻ�����ϴ�ŵ�

    {//��������, ��ȡ���ڷŵ���ɫ˳��
        car_turn_right(turn_speed);
        delay_ms(500);
        car_turn_right(turn_speed);
        while(!b[5])
            ;
        car_stop();

        int dir = 0;
        while(1){
            back_patrol_line(0);
            delay_ms(20);
            dir++;
            if(dir > 25)
                break;
        }
        car_back_goto_n_black_line(1, 0);

        car_forward(forward_speed);
        while(1)
        {
            forward_patrol_line(0);
            if(f[6]||f[0])
            {
                car_stop();
                break;
            }
        }
    }

    //��ȡ
    int i = 1;
    for(;i<=3;i++){
        take(get_take_pos(i));

        {//���ݷ���λ�õĲ�ͬ��ʻ����ͬλ��
            if(task[i-1] == 2){
                car_back_goto_n_black_line(1, 0);
                car_back(forward_speed);
                while(1){
                    back_patrol_line(0);
                    if(b[6]||b[0]){
                        car_stop();
                        break;
                    }
                }
            }
            else{
                car_back_goto_n_black_line(2, 0);
            }
        }

        place(task[i-1]);

        //����
        if(i == 3)
            car_return();

        {//��ʻ��ȡ���λ��
            car_forward_goto_n_black_line(1, 0);
            car_forward(forward_speed);
            while(1){
                forward_patrol_line(0);
                if(f[6]||f[0]){
                    car_stop();
                    break;
                }
            }
        }
    }
    STOP
}

//ÿ20ms����һ��ѭ��ģ��Ĳɼ�
void IntHandler_SysTick(void)
{
    UARTCharPut(UART3_BASE, 0x57);
    UARTCharPut(UART4_BASE, 0x57);
}
void Timer0IntHandler()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static uint32_t count = 0;

    count++;

    if(count == 6)//600ms
    {
        count = 0;

        count_enter = 1;

        TimerDisable(TIMER0_BASE, TIMER_A);
    }
}
void IntHandler_UART1()
{
    uint32_t ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);

    uint8_t c = 0, i= 0;
    while(UARTCharsAvail(UART1_BASE))
    {
        c = UARTCharGetNonBlocking(UART1_BASE);
        if(i == 3)
            break;
        color[i] = c;
        i++;
    }
    color_get = 1;
}
//������Դ���������Ϣ�������ڶ��λ��
void IntHandler_UART2()
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32Status);

    uint8_t i = 0, begin = 0;
    char ch, buffer[7];
    while(UARTCharsAvail(UART2_BASE))
    {
        ch = UARTCharGetNonBlocking(UART2_BASE);
        if(ch == '{')
        {
            begin = 1;
        }
        if(begin == 1)
        {
            buffer[i]  = ch;
            i++;
            if(i == 7)
                break;
        }
    }
    if( (buffer[0] == '{')&&(buffer[6] == '}') )
    {
        servoVal[buffer[1]-48] = 1000*(buffer[2]-48)+100*(buffer[3]-48)+10*(buffer[4]-48)+(buffer[5]-48);
        servoUpdate = 1;
    }
}
//��ȡǰѭ��ģ����Ϣ
void IntHandler_UART3()
{
    uint32_t ui32Status = UARTIntStatus(UART3_BASE, true);
    UARTIntClear(UART3_BASE, ui32Status);

    uint8_t c=0,i=0,bit=0;
    while(UARTCharsAvail(UART3_BASE))
    {
        c = UARTCharGetNonBlocking(UART3_BASE);
        for(;i<8;i++)
        {
            bit = c&0x01;
            c = c>>1;
            f[i] = !bit;//�ڴ˴�ȡ����ʹ����Ϊ1
        }
    }
}
//��ȡ��ѭ��ģ����Ϣ
void IntHandler_UART4()
{
    uint32_t ui32Status = UARTIntStatus(UART4_BASE, true);
    UARTIntClear(UART4_BASE, ui32Status);

    uint8_t c=0,i=0,bit=0;
    while(UARTCharsAvail(UART4_BASE))
    {
        c = UARTCharGetNonBlocking(UART4_BASE);
        for(;i<8;i++)
        {
            bit = c&0x01;
            c = c>>1;
            b[i] = !bit;//�ڴ˴�ȡ����ʹ����Ϊ1
        }
    }
}
uint8_t compare(uint8_t *t, char* p)
{
    uint8_t s0 = 0,s1 = 0,s2 = 0;
    s0 = (t[0]==(p[0]-48));
    s1 = (t[1]==(p[1]-48));
    s2 = (t[2]==(p[2]-48));
    if(s0&&s1&&s2)
        return 1;
    else
        return 0;
}
//��ȡɨ��ǹ��Ϣ
void IntHandler_UART7()
{
    uint32_t ui32Status = UARTIntStatus(UART7_BASE, true);
    UARTIntClear(UART7_BASE, ui32Status);

    uint8_t c = 0, i= 0, temp[3] = {4,4,4};
    while(UARTCharsAvail(UART7_BASE))
    {
        c = UARTCharGetNonBlocking(UART7_BASE);
        if(i == 3)
            break;
        temp[i] = c - 48;
        i++;
    }
    tmp_show(temp[0]+48,temp[1]+48,temp[2]+48);
    uint8_t s0 = compare(temp,"123");
    uint8_t s1 = compare(temp,"132");
    uint8_t s2 = compare(temp,"213");
    uint8_t s3 = compare(temp,"231");
    uint8_t s4 = compare(temp,"321");
    uint8_t s5 = compare(temp,"312");
    if(s0 || s1 || s2 || s3 ||s4 || s5)
    {
        task[0] = temp[0];
        task[1] = temp[1];
        task[2] = temp[2];
        qr_code_get = 1;
    }
}
