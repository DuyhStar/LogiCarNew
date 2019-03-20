/*
 * patrol_line.c
 *
 *  Created on: 2019年3月18日
 *      Author: DuYihao
 */
#include "patrol_line.h"

void patrol_line_init()
{
    UART3_Init(9600);                   //前7路循迹
    UART4_Init(9600);                   //后7路循迹

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIODirModeSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

//wide为线宽,取0,1,2
void forward_patrol_line(uint8_t wide)
{
    extern int forward_speed, turn_speed, f[8];
    int8_t left = 0, right = 0;

    switch(wide)
    {
    case 0:
        left  = f[2] || f[1] || f[0];
        right = f[4] || f[5] || f[6];
        break;
    case 1:
        left  = f[1] || f[0];
        right = f[5] || f[6];
        break;
    case 2:
        left  = f[0];
        right = f[6];
        break;
    default:
        break;
    }

    if( left && right )
        car_forward(forward_speed);
    else if(right)
        car_turn_right(turn_speed);
    else if(left)
        car_turn_left(turn_speed);
    else
        car_forward(forward_speed);
}


void back_patrol_line(uint8_t wide)
{
    extern int forward_speed, turn_speed, b[8];
    int8_t left = 0, right = 0;

    switch(wide)
    {
    case 0:
        left  = b[2] || b[1] || b[0];
        right = b[4] || b[5] || b[6];
        break;
    case 1:
        left  = b[1] || b[0];
        right = b[5] || b[6];
        break;
    case 2:
        left  = b[0];
        right = b[6];
        break;
    default:
        break;
    }

    if( left && right )
        car_back(forward_speed);
    else if(right)
        car_turn_right(turn_speed);
    else if(left)
        car_turn_left(turn_speed);
    else
        car_back(forward_speed);
}

uint8_t m_black()
{
    int32_t ui32state = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3);
    if( (ui32state&GPIO_PIN_3) ==  GPIO_PIN_3)
        return 1;
    else
        return 0;
}
