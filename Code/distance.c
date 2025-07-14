#include "distance.h"

int One_Wheel_len = 204;		 //mm  һ�ֳ���
int One_Wheel_Mai = 730;   	//һȦ������
//  С��һȦʵ������1456  (���ٱ� 1:28)
float Wheel_count = 0.2797; //mm һ���������ߵľ���
float carL_dis = 0;
float carR_dis = 0;

float dis3 = 1000;  // 1149 - 1151
float dis4 = 1070; 


void distance(void)
{
	carR_dis = Wheel_count * abs(Get_Encoder_countB);
	carL_dis = Wheel_count * abs(Get_Encoder_countA);
}

static int lastCountA = 0;
static int lastCountB = 0;

float get_distance(void)
{
    int currentCountA = Get_Encoder_countA;
    int currentCountB = Get_Encoder_countB;

    int deltaA = abs(currentCountA - lastCountA);
    int deltaB = abs(currentCountB - lastCountB);

    lastCountA = currentCountA;
    lastCountB = currentCountB;

    float deltaDis_mm = Wheel_count * ((float)deltaA + (float)deltaB) / 2.0f;

    return deltaDis_mm / 10.0f; // ���ص�λ����
}

