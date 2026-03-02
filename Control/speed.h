#ifndef __SPEED_H
#define __SPEED_H
#include "pid.h"

void SpeedPidCtrl(void);

extern PID_Struct motor_left_pid;
extern PID_Struct motor_right_pid;

#endif
