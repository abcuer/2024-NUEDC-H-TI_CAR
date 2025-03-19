#ifndef _MOTOR_H
#define _MOTOR_H
#include "ti_msp_dl_config.h"
#include "board.h"

int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);
void Set_PWM(int pwma,int pwmb);
#endif