#include "gray.h"

#define LineFlagTime 4400

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t LineFlagCNT = 0;

int8_t R3,R2,R1,M,L1,L2,L3;

void Gray_Init(void) 
{
    R3 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R3_PIN) ? 1 : 0;
    R2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 1 : 0;
    R1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 1 : 0;
    M = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_M_PIN) ? 1 : 0;
    L1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 1 : 0;
    L2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 1 : 0;
    L3 = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_L3_PIN) ? 1 : 0;
}

void Get_Light_TTL(void)
{
	baisetime++;
	if(R3 == 1 || R2== 1 || R1 == 1 || M == 1 || L1 == 1 || L2 == 1 || L3 == 1)
	{
		LineFlagCNT++;
		// 空白识别
		if(LineFlagCNT > 5)
		{
			Line_flag = 1;
			baisetime = 0;
			LineFlagCNT = 0;
		}
	}
	if(baisetime >= LineFlagTime)
	{
		Line_flag = 0;
		baisetime = 0;
	}
}