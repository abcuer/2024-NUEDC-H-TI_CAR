#include "distance.h"

int One_Wheel_len = 204;		 //mm  һ�ֳ���
int One_Wheel_Mai = 730;   	//һȦ������
//  С��һȦʵ������1456  (���ٱ� 1:28)
float Wheel_count = 0.2794; //mm һ��������ת����
float carL_dis = 0;
float carR_dis = 0;

float dis3 = 1000;  // 1149 - 1151
float dis4 = 1070; 


void distance(void)
{
	carR_dis = Wheel_count * fabs(Get_Encoder_countB);
	carL_dis = Wheel_count * fabs(Get_Encoder_countA);
}