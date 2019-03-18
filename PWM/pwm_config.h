/*
 * pwm_config.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */

#ifndef PWM_PWM_CONFIG_H_
#define PWM_PWM_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"

#define PWM0_CLOCK_DIV SYSCTL_PWMDIV_1
#define PWM1_CLOCK_DIV SYSCTL_PWMDIV_16
#define PWM0_DIV 1
#define PWM1_DIV 16

void PWM1_0_Init();
void PWM1_1_Init();
void PWM1_2_Init();
void PWM1_3_Init();
void PWM1_4_Init();
void PWM1_5_Init();

#endif /* PWM_PWM_CONFIG_H_ */
