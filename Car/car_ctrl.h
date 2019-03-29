/*
 * car_ctrl.h
 *
 *  Created on: 2019��3��18��
 *      Author: DuYihao
 */

#ifndef CAR_CAR_CTRL_H_
#define CAR_CAR_CTRL_H_

#include "pwm_config.h"
#include "delay.h"
#include "patrol_line.h"
#include "timer_config.h"

//С����������PWM����ʼ��
void car_init();

//ǰ������
void car_forward(uint16_t speed);
void car_back(uint16_t speed);

//��ת��ת
void car_turn_left(uint16_t range);
void car_turn_right(uint16_t range);

void car_speed(uint16_t speed);

//ǰ������n������
void car_forward_goto_n_black_line(uint8_t n, uint8_t line_wide);

void car_back_goto_n_black_line(uint8_t n, uint8_t line_wide);
void car_back_goto_n_black_line_right(uint8_t n, uint8_t line_wide);

void car_begin_goto_first_pos();

//һЩֹͣ����
void car_stop();

void car_return();

#endif /* CAR_CAR_CTRL_H_ */
