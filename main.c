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

#define STOP while(1);

int      turn_speed    = 45;                            //
int      forward_speed = 40;                            //
uint16_t servoVal[4]   = {1500,1350,680,1100};   //舵机初始化角度值
uint8_t  servoUpdate   = 0;                             //
uint8_t  count_enter   = 0;                             //

uint8_t  f[8];
uint8_t  b[8];

uint8_t  task[3]       = {1,2,3};                       //从二维码中读取的任务信息(1:红. 2:蓝. 3:绿.)
uint8_t  color[3]      = {3,2,1};                       //物块摆放的颜色顺序

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |  SYSCTL_XTAL_16MHZ);

    SysTick_Init_ms(20);                //滴答定时器
    UART0_Init(115200);                 //调试串口
    UART2_Init(9600);                   //与串口屏通信
    UART3_Init(9600);                   //前7路循迹
    UART4_Init(9600);                   //后7路循迹
    key1_init();                        //按键
    car_init();                         //小车所用PWM及IO
    servo_init(servoVal);               //舵机所用4路PWM

    //按下按键,开始工作
    system_waitKey();
    IntMasterEnable();
    SysTickEnable();
    while(1)
    {
        UARTprintf("%d%d%d%d%d%d%d%d %d%d%d%d%d%d%d%d\n",f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);
        delay_ms(40);
    }
    system_waitKey();

    while(1)
    {
        car_back_patrol_line_inside();
    }

    //小车出发至第一条线，然后原地右转90°,行驶至第一个十字交叉点。
    car_begin_goto_first_pos();

    //小车巡线前行，并开始计数，行驶至二维码处
    car_forward_goto_n_black_line(7);

    //扫描二维码，获取任务信息
    //TODO
    delay_s(1);

    //小车从二维码处后退，行驶至物料存放点
    car_back(forward_speed);
    delay_ms(500);
    car_back_goto_n_black_line(3);

    //摆正方向
    car_turn_right_90_degree();

    car_back(forward_speed);
    delay_ms(200);
    car_back_goto_n_black_line_inside(2);

    car_forward(forward_speed);
    delay_ms(200);
    car_forward_goto_n_black_line_inside(2);
    delay_s(5);

    //初始化机械臂控制并设置其初始位置
    //servo_init(servoVal);

    //获取物块摆放的颜色顺序
    //TODO

    //夹取第1个物体
    //take(1);

    car_back(forward_speed);
    delay_ms(200);

    car_back_goto_n_black_line_inside(2);
    //place(1);
    delay_s(5);

    car_forward(forward_speed);
    delay_ms(200);

    car_forward_goto_n_black_line_inside(2);
    delay_s(5);

    //夹取第2个物体
    //take(2);

    car_back(forward_speed);
    delay_ms(200);

    car_back_goto_n_black_line_inside(2);
    //place(2);

    car_forward(forward_speed);
    delay_ms(200);

    car_forward_goto_n_black_line_inside(2);

    //夹取第3个物体
    //take(3);

    car_back(forward_speed);
    delay_ms(200);

    car_back_goto_n_black_line_inside(2);

    //place(3);

    //返程
    car_turn_left(turn_speed);
    delay_s(1);
    while(1){
        if(back_right_black()){
            car_stop_turn_left();
            break;
        }
    }
    car_back_goto_n_black_line(2);

    car_turn_left(turn_speed);
    delay_s(1);
    while(1){
        if(back_right_black()){
            car_stop_turn_left();
            break;
        }
    }
    car_back_goto_n_black_line_inside(2);

    car_stop();
    STOP;
}

//每20ms触发一次循迹模块的采集
void IntHandler_SysTick(void)
{
    UARTCharPut(UART3_BASE, 0x57);
    UARTCharPut(UART4_BASE, 0x57);
}

//获得来自串口屏的信息，来手动调节舵机位置
void IntHandler_UART2(void)
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
//获取前面循迹模块信息
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
            f[i] = bit;
        }
    }
}
//获取后面循迹模块信息
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
            b[i] = bit;
        }
    }
}


