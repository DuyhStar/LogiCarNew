/*
 * patrol_line.c
 *
 *  Created on: 2019年3月18日
 *      Author: DuYihao
 */
#include "patrol_line.h"

void patrol_line_init()
{
    uint32_t A_pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    uint32_t B_pin = GPIO_PIN_4 | GPIO_PIN_5;
    uint32_t D_pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    uint32_t E_pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIODirModeSet(GPIO_PORTA_BASE, A_pin, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTB_BASE, B_pin, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTD_BASE, D_pin, GPIO_DIR_MODE_IN);
    GPIODirModeSet(GPIO_PORTE_BASE, E_pin, GPIO_DIR_MODE_IN);

    GPIOPadConfigSet(GPIO_PORTA_BASE, A_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTB_BASE, B_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTD_BASE, D_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(GPIO_PORTE_BASE, E_pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

//wide为线宽,取0,1,2
void forward_patrol_line(uint8_t wide)
{
    extern int forward_speed, turn_speed;
    int8_t left = 0, right = 0;

    switch(wide)
    {
    case 0:
        left  = f2_black();
        right = f4_black();
        break;
    case 1:
        left  = f1_black();
        right = f5_black();
        break;
    case 2:
        left  = f0_black();
        right = f6_black();
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
    extern int forward_speed, turn_speed;
    int8_t left = 0, right = 0;

    switch(wide)
    {
    case 0:
        left  = b2_black();
        right = b4_black();
        break;
    case 1:
        left  = b1_black();
        right = b5_black();
        break;
    case 2:
        left  = b0_black();
        right = b6_black();
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

int8_t f0_black()
{
    uint32_t port = GPIO_PORTA_BASE;
    uint32_t pin  = GPIO_PIN_2;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t f1_black()
{
    uint32_t port = GPIO_PORTA_BASE;
    uint32_t pin  = GPIO_PIN_3;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t f2_black()
{
    uint32_t port = GPIO_PORTA_BASE;
    uint32_t pin  = GPIO_PIN_4;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t f3_black()
{
    uint32_t port = GPIO_PORTA_BASE;
    uint32_t pin  = GPIO_PIN_5;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t f4_black()
{
    uint32_t port = GPIO_PORTB_BASE;
    uint32_t pin  = GPIO_PIN_4;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t f5_black()
{
    uint32_t port = GPIO_PORTB_BASE;
    uint32_t pin  = GPIO_PIN_5;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t f6_black()
{
    uint32_t port = GPIO_PORTD_BASE;
    uint32_t pin  = GPIO_PIN_2;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}

int8_t m_black()
{
    uint32_t port = GPIO_PORTD_BASE;
    uint32_t pin  = GPIO_PIN_3;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}

int8_t b0_black()
{
    uint32_t port = GPIO_PORTE_BASE;
    uint32_t pin  = GPIO_PIN_4;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t b1_black()
{
    uint32_t port = GPIO_PORTE_BASE;
    uint32_t pin  = GPIO_PIN_3;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t b2_black()
{
    uint32_t port = GPIO_PORTE_BASE;
    uint32_t pin  = GPIO_PIN_2;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t b3_black()
{
    uint32_t port = GPIO_PORTE_BASE;
    uint32_t pin  = GPIO_PIN_1;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t b4_black()
{
    uint32_t port = GPIO_PORTE_BASE;
    uint32_t pin  = GPIO_PIN_0;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t b5_black()
{
    uint32_t port = GPIO_PORTD_BASE;
    uint32_t pin  = GPIO_PIN_5;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}
int8_t b6_black()
{
    uint32_t port = GPIO_PORTD_BASE;
    uint32_t pin  = GPIO_PIN_4;

    int32_t s = GPIOPinRead(port, pin);
    if( (s&pin) ==  pin)
        return 1;
    else
        return 0;
}


