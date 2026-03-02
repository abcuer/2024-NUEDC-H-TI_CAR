#ifndef _headfile_h
#define _headfile_h

#pragma once

#include "ti_msp_dl_config.h"

#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
/******************* BSP **********************/
#include "timer.h"
#include "uart.h"
#include "delay.h"
/***************** Hardware *******************/
#include "key.h"
#include "led.h"
#include "beep.h"
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

#endif