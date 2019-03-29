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

int      turn_speed    = 30;                            //
int      forward_speed = 40;                            //
uint16_t servoVal[4]   = {1500,1500,1500,1130};         //舵机初始化角度值
uint8_t  servoUpdate   = 0;                             //
uint8_t  count_enter   = 0;                             //
uint8_t  qr_code_get   = 0;
uint8_t  color_get     = 0;
uint8_t  f[8];
uint8_t  b[8];
uint8_t  red_pos = 1, blue_pos = 3;
uint8_t  exchange_cnt  = 0, exchange_ctl = 1;

uint8_t  task[3]       = {1,2,3};                       //从二维码中读取的任务信息(1:红. 2:绿. 3:蓝.)
uint8_t  color[3]      = {1,2,3};                       //物块摆放的颜色顺序

uint8_t compare(uint8_t *t, char* p);


int main(void){
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);

    UART0_Init(115200);                 //调试
    UART1_Init(9600);                   //openMV
    UART7_Init(9600);                   //扫码
    patrol_line_init();                 //巡线所用串口3,4 PD3
    UART2_Init(9600);                   //串口屏
    key1_init();                        //按键
    car_init();                         //小车所用PWM及IO
    timer0_init();                      //定时器初始化,用来控制计数循迹

    IntMasterEnable();
    {//调整放置的红蓝位置
        system_waitKey();
        TimerEnable(TIMER0_BASE, TIMER_A);
        while(1){
            if(exchange_cnt > 3*10)
            {
                exchange_ctl = 0;
                break;
            }
            if(Key1_Read() == 1)
            {
                delay_ms(100);
                if(Key1_Read() == 1){
                    red_pos = 3;
                    blue_pos = 1;
                }
            }
        }
        TimerDisable(TIMER0_BASE, TIMER_A);
    }
    tmp_show(red_pos+48,blue_pos+48,'!');
    //按下按键,开始工作
    system_waitKey();
    tmp_show(' ',' ',' ');
    servo_init(servoVal);
    delay_s(3);

    car_begin_goto_first_pos();             //小车出发至第一条线，然后原地右转90°,行驶至第一个十字交叉点
    car_forward_goto_n_black_line(6, 1);    //小车巡线前行,并开始计数，行驶至二维码处


    //读取二维码
    while(1){
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

    car_back_goto_n_black_line(2, 2);       //小车从二维码处后退,行驶至物料存放点

    {//摆正方向, 获取物块摆放的颜色顺序
        car_turn_right(turn_speed);
        while(!b[6])
            ;
        while(!b[5])
            ;
        while(!b[4])
            ;
        while(!b[3])
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
LOOP:   car_back_goto_n_black_line(1, 0);
        delay_s(1);
        car_forward(forward_speed);
        while(1){
            forward_patrol_line(0);
            if(f[6] || f[0])
            {
                car_stop();
                break;
            }
        }
        //如果获取到正确的颜色顺序
        if(color_get){
            color_get = 0;
            IntDisable(INT_UART1);
            color_show();
        }
        else{
            goto LOOP;
        }
    }

    //搬运过程
    int i = 1;
    for(;i<=3;i++){

        take(get_take_pos(i));//抓取物块

        {//根据放置位置的不同行驶至不同位置
            if(task[i-1] == 1){
                car_back_goto_n_black_line_right(2, 0);
            }
            else if(task[i-1] == 2){
                car_back_goto_n_black_line(1, 0);
                car_back(forward_speed);
                while(1){
                    back_patrol_line(0);
                    if(f[6] || f[0]){
                        car_stop();
                        break;
                    }
                }
            }
            else if(task[i-1] == 3){
                car_back_goto_n_black_line(2, 0);
            }
            else{
                ;
            }
        }

        place(task[i-1]);//放置物块

        //当放完第三个的时候返程
        if(i == 3){
            if(task[i-1] == 2){
                car_back(forward_speed);
                while(!m_black())
                    ;
            }
            car_return();
        }
        //否则行驶至取物块位置
        else{
            if( (task[i-1] == 1) || (task[i-1] == 3) ){
                car_forward(forward_speed);
                delay_ms(300);
            }
            car_forward_goto_n_black_line(1, 0);
            car_forward(forward_speed);
            while(1){
                forward_patrol_line(0);
                if(f[6] || f[0]){
                    car_stop();
                    break;
                }
            }
        }
    }
    while(1)
    {
    }
}

//每20ms触发一次循迹模块的采集
void IntHandler_SysTick(void)
{
    UARTCharPut(UART3_BASE, 0x57);
    UARTCharPut(UART4_BASE, 0x57);
}
void Timer0IntHandler()
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static uint32_t count = 0;

    if(exchange_ctl == 1){
        exchange_cnt++;
    }
    else{
        count++;
        if(count == 3)//600ms
        {
            count = 0;

            count_enter = 1;

            TimerDisable(TIMER0_BASE, TIMER_A);
        }
    }
}
void IntHandler_UART1()
{
    uint32_t ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);

    uint8_t c = 0, i= 0, temp[3] = {4,4,4};;
    while(UARTCharsAvail(UART1_BASE))
    {
        c = UARTCharGetNonBlocking(UART1_BASE);
        if(i == 3)
            break;
        temp[i] = c;
        i++;
    }
    uint8_t s0 = compare(temp,"123");
    uint8_t s1 = compare(temp,"132");
    uint8_t s2 = compare(temp,"213");
    uint8_t s3 = compare(temp,"231");
    uint8_t s4 = compare(temp,"321");
    uint8_t s5 = compare(temp,"312");
    if(s0 || s1 || s2 || s3 ||s4 || s5)
    {
        color[0] = temp[0];
        color[1] = temp[1];
        color[2] = temp[2];
        color_get = 1;
    }
}
//获得来自串口屏的信息，来调节舵机位置
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
//获取前循迹模块信息
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
            f[i] = !bit;//在此处取反，使黑线为1
        }
    }
}
//获取后循迹模块信息
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
            b[i] = !bit;//在此处取反，使黑线为1
        }
    }
}
//获取扫码枪信息
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

