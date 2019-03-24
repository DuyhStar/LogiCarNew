/*
 * display.c
 *
 *  Created on: 2019Äê3ÔÂ23ÈÕ
 *      Author: DuYihao
 */
#include "display.h"


void task_show(void)
{
    extern uint8_t task[3];

    uint8_t t[12] = "t1.txt=\"000\"";

    t[8]  = task[0] + 48;
    t[9]  = task[1] + 48;
    t[10] = task[2] + 48;

    int i = 0;
    for(;i<12;i++)
        UARTCharPut(UART2_BASE, t[i]);
    UARTCharPut(UART2_BASE, 0xFF);
    UARTCharPut(UART2_BASE, 0xFF);
    UARTCharPut(UART2_BASE, 0xFF);
}

void color_show(void)
{
    extern uint8_t color[3];

    uint8_t t[12] = "t3.txt=\"000\"";

    t[8]  = color[0] + 48;
    t[9]  = color[1] + 48;
    t[10] = color[2] + 48;

    int i = 0;
    for(;i<12;i++)
        UARTCharPut(UART2_BASE, t[i]);
    UARTCharPut(UART2_BASE, 0xFF);
    UARTCharPut(UART2_BASE, 0xFF);
    UARTCharPut(UART2_BASE, 0xFF);
}

void tmp_show(char c0, char c1, char c2)
{
     uint8_t t[12] = "t3.txt=\"000\"";

     t[8]  = c0;
     t[9]  = c1;
     t[10] = c2;

     int i = 0;
     for(;i<12;i++)
         UARTCharPut(UART2_BASE, t[i]);
     UARTCharPut(UART2_BASE, 0xFF);
     UARTCharPut(UART2_BASE, 0xFF);
     UARTCharPut(UART2_BASE, 0xFF);
}
