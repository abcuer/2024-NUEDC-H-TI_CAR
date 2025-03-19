#include "pid.h"


//定义一个结构体类型变量
tPid PID_Link;               //定义一个循迹结构体


//给结构体类型变量赋初值 结构体名，设定值，Kp,Ki,Kd,最大限幅值，最小限幅值
void PID_init(tPid *pid,float target_val,float Kp,float Ki,float Kd,float MAX,float MIN)
{
    pid->target_val = target_val;   //目标值设定
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->MAX = MAX;
    pid->MIN = MIN;

    pid->err = 0;                 //误差清零
    pid->err_last = 0;
    pid->err_pre = 0;
    pid->err_sum = 0;
    pid->actual_val = 0;//实际输出值    
}



// 位置式PID控制函数
float PID_realize(tPid * pid,float actual_val)
{
    pid->actual_val = actual_val;//传递真实值
    pid->err = pid->target_val - pid->actual_val;	//当前误差=目标值-真实值
    pid->err_sum += pid->err;//误差累计值 = 当前误差累计和
    //使用PID控制 输出 = Kp*当前误差  +  Ki*误差累计值 + Kd*(当前误差-上次误差)
    pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
    //保存上次误差: 这次误差赋值给上次误差
    pid->err_last = pid->err;

    //PID限幅
    if(pid->actual_val > pid->MAX)
    {
        pid->actual_val = pid -> MAX;
    }
  else if(pid->actual_val < pid->MIN)
    {
        pid->actual_val = pid -> MIN;
    }

   // printf("%f\r\n",actual_val);

    return pid->actual_val;
}




