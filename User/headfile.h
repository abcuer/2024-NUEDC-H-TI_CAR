#ifndef _headfile_h
#define _headfile_h

#pragma once

#include "ti_msp_dl_config.h"

#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
/******************* BSP **********************/
#include "board.h"
#include "timer.h"
#include "uart.h"
#include "delay.h"
/***************** Hardware *******************/
#include "key.h"
#include "led.h"
#include "buzzer.h"
#include "motor.h"
#include "encoder.h"
#include "gray.h"
#include "jy901s.h"
/***************** Control *******************/
#include "angle.h"
#include "track.h"
#include "speed.h"
#include "dist.h"
#include "pid.h"
/***************** App ***********************/
#include "utils.h"
#include "task.h"
#include "soundlight.h"

extern uint8_t motor_left_dir;
extern uint8_t motor_right_dir;

extern float Get_Encoder_countA;
extern float Get_Encoder_countB;
extern float carL_dis;
extern float carR_dis;

extern float basespeed;
extern uint8_t task_num;
extern uint8_t first_flag;
extern uint8_t start_flag;
extern int16_t Line_flag;

extern int16_t baisetime;
extern uint8_t workstep;

extern float dis3;
extern float dis4;

#endif