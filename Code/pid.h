#ifndef __PID_h_
#define __PID_h_
#include "headfile.h"

enum
{
  POSITION_PID = 0,  // λ��ʽ
  DELTA_PID,         // ����ʽ
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;

extern pid_t motorA;
extern pid_t motorB;
extern pid_t trackLine;
extern pid_t angle;

void speed_pid_control(void);
void motor_target_set(int tarA, int tarB);
void track_pid_control(void);
void angle_pid_control(float tar);
void angle_correction(void);

void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d);
void pid_cal(pid_t *pid);
void pidout_limit(pid_t *pid, float duty);


#endif
