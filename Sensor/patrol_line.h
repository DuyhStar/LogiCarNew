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
#include "uart_config.h"

void patrol_line_init();

void forward_patrol_line(uint8_t wide);

void back_patrol_line(uint8_t wide);
void back_patrol_line_right();


uint8_t m_black();

#endif /* SENSOR_PATROL_LINE_H_ */
