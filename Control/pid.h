#ifndef __PID_H
#define __PID_H

#include "stdint.h"

enum
{
  POSITION_PID = 0,  	// 位置式
  DELTA_PID,         		// 增量式
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	uint8_t  mode;
}PID_Struct;

void PID_Init(PID_Struct *pid, uint8_t mode, float p, float i, float d);
void PID_Calculate(PID_Struct *pid);
void PID_OutPutLimit(PID_Struct *pid, float duty);

#endif
