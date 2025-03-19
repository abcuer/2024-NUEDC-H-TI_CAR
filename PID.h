#ifndef __PID_H__
#define __PID_H__

typedef struct 
{
    float target_val;//Ŀ��ֵ
    float actual_val;//ʵ�����ֵ
    float err;//��ǰƫ��
    float err_last;//�ϴ�ƫ��
    float err_pre; //���ϴ�ƫ��
    float err_sum;//����ۼ�ֵ
    float Kp,Ki,Kd;//���������֣�΢��ϵ��

    float MAX;    //����޷�ֵ
    float MIN;    //��С�޷�ֵ

}tPid;

void PID_init(tPid *pid,float target_val,float Kp,float Ki,float Kd,float MAX,float MIN);
float PID_realize(tPid * pid,float actual_val);

#endif
