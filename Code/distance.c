#include "distance.h"
#define PI 3.14159265

int One_Wheel_len = 204;		 //mm  һ�ֳ���
int One_Wheel_Mai = 730;   	//һȦ������
float Wheel_count = 0.2794; //mm һ��������ת����
float carL_dis = 0;
float carR_dis = 0;
float dis1 = 1151;  // 1149 - 1151
float dis2 = 1134; 

void distance(void)
{
	carR_dis = Wheel_count * -Get_Encoder_countB;
	carL_dis = Wheel_count * Get_Encoder_countA;
}