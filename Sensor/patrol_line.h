/*
 * patrol_line.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */

#ifndef SENSOR_PATROL_LINE_H_
#define SENSOR_PATROL_LINE_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "car_ctrl.h"

void patrol_line_init();

void forward_patrol_line(uint8_t wide);
void back_patrol_line(uint8_t wide);

int8_t f0_black();
int8_t f1_black();
int8_t f2_black();
int8_t f3_black();
int8_t f4_black();
int8_t f5_black();
int8_t f6_black();

int8_t m_black();

int8_t b0_black();
int8_t b1_black();
int8_t b2_black();
int8_t b3_black();
int8_t b4_black();
int8_t b5_black();
int8_t b6_black();


#endif /* SENSOR_PATROL_LINE_H_ */
