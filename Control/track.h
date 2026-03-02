#ifndef __TRACK_H
#define __TRACK_H
#include "pid.h"

typedef struct{
	int8_t left[4];
	int8_t right[4];	
}Gray_Weight_s; // 灰度权重

void TrackPidCtrl(void);

extern PID_Struct track_pid;

#endif
