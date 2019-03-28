/*
 * servo.h
 *
 *  Created on: 2019Äê3ÔÂ18ÈÕ
 *      Author: DuYihao
 */
#include <stdint.h>
#include <stdbool.h>
#include "pwm_config.h"
#include "delay.h"
#include "display.h"
#include "car_ctrl.h"

void servo_init(uint16_t *init_angle);
void servo_pulse_set(uint8_t num, uint16_t us);
void servo_n_angle_set(uint8_t n, uint16_t angle);

uint8_t get_take_pos(uint8_t n);

void place(uint8_t pos);
void take(uint8_t pos);
