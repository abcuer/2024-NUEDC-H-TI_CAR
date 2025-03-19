#ifndef __PID_H__
#define __PID_H__

typedef struct 
{
    float target_val;//目标值
    float actual_val;//实际输出值
    float err;//当前偏差
    float err_last;//上次偏差
    float err_pre; //上上次偏差
    float err_sum;//误差累计值
    float Kp,Ki,Kd;//比例，积分，微分系数

    float MAX;    //最大限幅值
    float MIN;    //最小限幅值

}tPid;

void PID_init(tPid *pid,float target_val,float Kp,float Ki,float Kd,float MAX,float MIN);
float PID_realize(tPid * pid,float actual_val);

#endif
