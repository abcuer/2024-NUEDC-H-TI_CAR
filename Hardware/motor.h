#ifndef _motor_h
#define _motor_h

#include "stdint.h"

#define AIN1_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_left_PORT,Motor_left_AIN1_PIN)) : (DL_GPIO_clearPins(Motor_left_PORT,Motor_left_AIN1_PIN)) )
#define AIN2_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_left_PORT,Motor_left_AIN2_PIN)) : (DL_GPIO_clearPins(Motor_left_PORT,Motor_left_AIN2_PIN)) )

#define BIN1_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_right_PORT,Motor_right_BIN1_PIN)) : (DL_GPIO_clearPins(Motor_right_PORT,Motor_right_BIN1_PIN)) )
#define BIN2_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_right_PORT,Motor_right_BIN2_PIN)) : (DL_GPIO_clearPins(Motor_right_PORT,Motor_right_BIN2_PIN)) )

void Motor_LeftDuty(uint8_t dir, uint32_t speed);
void Motor_RightDuty(uint8_t dir, uint32_t speed);

void Motor_LeftCtrl(float speed);
void Motor_RightCtrl(float speed);
void Motor_Stop(void);

#endif