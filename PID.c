#include "pid.h"


//����һ���ṹ�����ͱ���
tPid PID_Link;               //����һ��ѭ���ṹ��


//���ṹ�����ͱ�������ֵ �ṹ�������趨ֵ��Kp,Ki,Kd,����޷�ֵ����С�޷�ֵ
void PID_init(tPid *pid,float target_val,float Kp,float Ki,float Kd,float MAX,float MIN)
{
    pid->target_val = target_val;   //Ŀ��ֵ�趨
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->MAX = MAX;
    pid->MIN = MIN;

    pid->err = 0;                 //�������
    pid->err_last = 0;
    pid->err_pre = 0;
    pid->err_sum = 0;
    pid->actual_val = 0;//ʵ�����ֵ    
}



// λ��ʽPID���ƺ���
float PID_realize(tPid * pid,float actual_val)
{
    pid->actual_val = actual_val;//������ʵֵ
    pid->err = pid->target_val - pid->actual_val;	//��ǰ���=Ŀ��ֵ-��ʵֵ
    pid->err_sum += pid->err;//����ۼ�ֵ = ��ǰ����ۼƺ�
    //ʹ��PID���� ��� = Kp*��ǰ���  +  Ki*����ۼ�ֵ + Kd*(��ǰ���-�ϴ����)
    pid->actual_val = pid->Kp*pid->err + pid->Ki*pid->err_sum + pid->Kd*(pid->err - pid->err_last);
    //�����ϴ����: �����ֵ���ϴ����
    pid->err_last = pid->err;

    //PID�޷�
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




