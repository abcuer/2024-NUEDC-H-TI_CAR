#ifndef _headfile_h
#define _headfile_h

#pragma once

#include "ti_msp_dl_config.h"
#include "board.h"

#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"

#include "key.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "encoder.h"
#include "timer.h"
#include "gray.h"
#include "jy901s.h"
#include "pid.h"
#include "position.h"
#include "task.h"
#include "distance.h"

extern uint8_t motor_left_dir;
extern uint8_t motor_right_dir;

extern float Get_Encoder_countA;
extern float Get_Encoder_countB;
extern float encoderA_cnt;
extern float encoderB_cnt;
extern float carL_dis;
extern float carR_dis;

extern float basespeed;
extern uint8_t Task;
extern uint8_t first_flag;
extern uint8_t start_flag;
extern int16_t Line_flag;
extern float angle_initial;
extern int16_t baisetime;
extern uint8_t workstep;

//extern float track_kp;
//extern float track_kd;

extern float dis1;
extern float dis2;
extern float dis3;
extern float dis4;

#endif