#include "motor.h"
#define offset 30

#include "ti_msp_dl_config.h"

void Motor_LeftDuty(uint8_t dir, uint32_t speed)
{
    if(dir)
    {
        AIN1_OUT(1);
        AIN2_OUT(0);
    }
    else
    {
        AIN1_OUT(0);
        AIN2_OUT(1);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,speed ,GPIO_PWM_C0_IDX);
}

void Motor_RightDuty(uint8_t dir, uint32_t speed)
{
    if(dir)
    {
        BIN1_OUT(1);
        BIN2_OUT(0);
    }
    else
    {
        BIN1_OUT(0);
        BIN2_OUT(1);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,speed + offset,GPIO_PWM_C1_IDX);
}

void Motor_LeftCtrl(float speed)
{
	AIN1_OUT(1);
	AIN2_OUT(0);
	
    DL_TimerG_setCaptureCompareValue(PWM_INST,(uint32_t)speed + offset, GPIO_PWM_C0_IDX);
}

void Motor_RightCtrl(float speed)
{
	BIN1_OUT(1);
	BIN2_OUT(0);
	
    DL_TimerG_setCaptureCompareValue(PWM_INST,(uint32_t)speed + offset,GPIO_PWM_C1_IDX);
}

void Motor_Stop(void)
{
	AIN1_OUT(1);
    AIN2_OUT(1);
	
	BIN1_OUT(1);
    BIN2_OUT(1);
}
