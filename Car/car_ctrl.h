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

//С����������PWM����ʼ��
void car_init();

//ǰ������
void car_forward(uint16_t speed);
void car_back(uint16_t speed);

//��ת��ת
void car_turn_left(uint16_t range);
void car_turn_right(uint16_t range);

void car_speed(uint16_t speed);

//ǰ�����˲�Ѳ��
void car_forward_patrol_line();
void car_back_patrol_line();
void car_forward_patrol_line_inside();
void car_back_patrol_line_inside();

//ԭ������ת90��
void car_turn_left_90_degree();
void car_turn_right_90_degree();

//ǰ������n������
void car_forward_goto_n_black_line(uint8_t n);
void car_back_goto_n_black_line(uint8_t n);
void car_forward_goto_n_black_line_inside(uint8_t n);
void car_back_goto_n_black_line_inside(uint8_t n);

void car_begin_goto_first_pos();

//һЩֹͣ����
void car_stop_free();
void car_stop_hurry();

#endif /* CAR_CAR_CTRL_H_ */
