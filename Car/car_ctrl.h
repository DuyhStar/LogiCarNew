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

//小车所用驱动PWM波初始化
void car_init();

//前进后退
void car_forward(uint16_t speed);
void car_back(uint16_t speed);

//左转右转
void car_turn_left(uint16_t range);
void car_turn_right(uint16_t range);

void car_speed(uint16_t speed);

//前进后退并巡线
void car_forward_patrol_line();
void car_back_patrol_line();
void car_forward_patrol_line_inside();
void car_back_patrol_line_inside();

//原地左右转90度
void car_turn_left_90_degree();
void car_turn_right_90_degree();

//前进后退n个黑线
void car_forward_goto_n_black_line(uint8_t n);
void car_back_goto_n_black_line(uint8_t n);
void car_forward_goto_n_black_line_inside(uint8_t n);
void car_back_goto_n_black_line_inside(uint8_t n);

void car_begin_goto_first_pos();

//一些停止函数
void car_stop_free();
void car_stop_hurry();

#endif /* CAR_CAR_CTRL_H_ */
