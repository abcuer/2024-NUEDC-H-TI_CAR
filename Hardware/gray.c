#include "gray.h"

#define MAXCNT 3000

int16_t baisetime = 0;
int16_t Line_flag = 0;
int16_t white_line = 0;

GRAY_Struct gray = {0};

void Gray_Update(void) 
{
    gray.right[3] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R4_PIN) ? 0 : 1;
    gray.right[2] = DL_GPIO_readPins(Gray_IOB_PORT, Gray_IOB_R3_PIN) ? 0 : 1;
    gray.right[1] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R2_PIN) ? 0 : 1;
    gray.right[0] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_R1_PIN) ? 0 : 1;
    gray.left[0] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L1_PIN) ? 0 : 1;
    gray.left[1] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L2_PIN) ? 0 : 1;
    gray.left[2] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L3_PIN) ? 0 : 1;
	gray.left[3] = DL_GPIO_readPins(Gray_IOA_PORT, Gray_IOA_L4_PIN) ? 0 : 1;
}

void Gray_ProcessLine(void)
{
    baisetime++;
    
    if(gray.right[0] || gray.right[1] || gray.right[2] || gray.right[3] || 
       gray.left[0]  || gray.left[1]  || gray.left[2]  || gray.left[3])
    {
        white_line++;
        // 连续识别到多次，确认检测到线
        if(white_line >= 3)
        {
            Line_flag = 1;
            baisetime = 0;
            white_line = 0;
        }
    }
    else if(baisetime >= MAXCNT)
    {
        // 超过一定时间没检测到，判定为丢线
        Line_flag = 0;
        baisetime = 0;
        white_line = 0; 
    }
}