/*
 * car_ctrl.h
 *
 *  Created on: 2019年3月18日
 *      Author: DuYihao
 */

#ifndef CAR_CAR_CTRL_H_
#define CAR_CAR_CTRL_H_

#include "pwm_config.h"
#include "delay.h"
#include "patrol_line.h"
#include "timer_config.h"

//小车所用驱动PWM波初始化
void car_init();

//前进后退
void car_forward(uint16_t speed);
void car_back(uint16_t speed);

//左转右转
void car_turn_left(uint16_t range);
void car_turn_right(uint16_t range);

void car_speed(uint16_t speed);

//前进后退n个黑线
void car_forward_goto_n_black_line(uint8_t n, uint8_t line_wide);

void car_back_goto_n_black_line(uint8_t n, uint8_t line_wide);
void car_back_goto_n_black_line_right(uint8_t n, uint8_t line_wide);

void car_begin_goto_first_pos();

//一些停止函数
void car_stop();

void car_return();

#endif /* CAR_CAR_CTRL_H_ */
