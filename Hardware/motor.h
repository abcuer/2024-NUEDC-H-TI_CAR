#ifndef _motor_h
#define _motor_h
#include "headfile.h"

//void DL_GPIO_writePinVal(GPIO_Regs* gpio, uint32_t pinNum, uint32_t pinVal);
//void Motor_left_duty(uint8_t motor_left_dir ,uint32_t duty);
//void Motor_right_duty(uint8_t motor_left_dir ,uint32_t duty);

#define AIN1_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_left_PORT,Motor_left_AIN1_PIN)) : (DL_GPIO_clearPins(Motor_left_PORT,Motor_left_AIN1_PIN)) )
#define AIN2_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_left_PORT,Motor_left_AIN2_PIN)) : (DL_GPIO_clearPins(Motor_left_PORT,Motor_left_AIN2_PIN)) )

#define BIN1_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_right_PORT,Motor_right_BIN1_PIN)) : (DL_GPIO_clearPins(Motor_right_PORT,Motor_right_BIN1_PIN)) )
#define BIN2_OUT(X)  ( (X) ? (DL_GPIO_setPins(Motor_right_PORT,Motor_right_BIN2_PIN)) : (DL_GPIO_clearPins(Motor_right_PORT,Motor_right_BIN2_PIN)) )

void Motor_left_duty(uint8_t motor_left_dir, uint32_t speed);
void Motor_right_duty(uint8_t motor_left_dir, uint32_t speed);

void Motor_left_Control(float speed);
void Motor_right_Control(float speed);
void motor_stop(void);

#endif