#ifndef __ANGLE_H
#define __ANGLE_H
#include "pid.h"

void AnglePidCtrl(float tar);

extern PID_Struct angle_pid;

#endif
