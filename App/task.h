#ifndef __TASK_H
#define __TASK_H

#include "stdint.h"

#define CAR_STRAIGHT_SPEED 	400
#define CAR_TURN_SPEED 	385

void FirstTask(void);
void SecondTask(void);
void ThirdTask(void);
void FourthTask(void);

extern uint8_t workstep;
extern float basespeed;

#endif