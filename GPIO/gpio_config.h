/*
 * gpio_config.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */

#ifndef GPIO_GPIO_CONFIG_H_
#define GPIO_GPIO_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "delay.h"

void    key1_init();
uint8_t Key1_Read();
void    system_waitKey();


#endif /* GPIO_GPIO_CONFIG_H_ */
