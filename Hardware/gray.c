#include "gray.h"

#include "ti_msp_dl_config.h"

int16_t white_time = 0;
uint8_t black_line = 0;
uint8_t line_flag = 0;

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
    white_time++;
    
    if(gray.right[0] || gray.right[1] || gray.right[2] || gray.right[3] || 
       gray.left[0]  || gray.left[1]  || gray.left[2]  || gray.left[3])
    {
        black_line++;
        // 连续识别到多次，确认检测到黑线
        if(black_line >= 3)
        {
            line_flag = 1;
            white_time = 0;
            black_line = 0;
        }
    }
    else if(white_time >= MAXCNT)
    {
        // 超过一定时间没检测到，判定为丢线
        white_time = 0;
        black_line = 0; 
		line_flag = 0;
    }
}