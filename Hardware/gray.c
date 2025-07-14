#include "gray.h"

#define LineFlagTime 3000

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t LineFlagCNT = 0;

uint8_t L4,L3,L2,L1,R1,R2,R3,R4;

void Gray_Init(void) 
{
    R4 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R4_PIN) ? 0 : 1;
    R3 = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 0 : 1;
    R2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 0 : 1;
    R1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 0 : 1;
    L1 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 0 : 1;
    L2 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 0 : 1;
    L3 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 0 : 1;
	L4 = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L4_PIN) ? 0 : 1;
}

//void track_mode1(void)
//{
//	if()
//}
uint8_t stop_line, stop_flag;

void Get_Light_TTL(void)
{
    static int full_black_count = 0;
    static int debounce_time = 0;
    static int lap_detected = 0;

    debounce_time++;

    // 检测是否全黑（经过终点线）
    if (L4 && L3 && L2 && L1 && R1 && R2 && R3 && R4)
    {
        full_black_count++;
    }
    else
    {
        full_black_count = 0;
        lap_detected = 0; // 允许重新检测下一圈
    }

    // 连续全黑3次，并且时间隔足够，才认为真正过终点
    if (full_black_count >= 3 && !lap_detected && debounce_time >= 100)
    {
        stop_line++;          // 圈数加1
        lap_detected = 1;     // 防止连续触发
        debounce_time = 0;

        if (stop_line >= 2)   // 达到设定圈数
        {
            stop_flag = 1;    // 标记为终点
        }
    }
}
