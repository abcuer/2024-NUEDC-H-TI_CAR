#include "jy901s.h"
#include "delay.h"
#include "led.h"
#include "utils.h"
#include "task.h"

EulerAngle_Struct jy901s = {0.0f};

void IMU_ParseData(uint8_t data)
{
	static uint8_t buffer[11];
	static volatile uint8_t state = 0;
	static uint8_t index = 0;
	uint8_t i = 0, sum=0;
	
	if (state == 0)	
	{
		if (data == 0x55)	
		{
			buffer[index] = data;
			state = 1;
			index = 1;	
		}
	}
	else if (state == 1)
	{
		if (data == 0x53)
		{
			buffer[index] = data;
			state = 2;
			index = 2;	
		}
	}
	else if (state == 2)
	{
		buffer[index++] = data;
		if(index == 11)	
		{
			for(i=0;i<10;i++)
			{
				sum = sum + buffer[i];	
			}
			if(sum == buffer[10])		
			{
				jy901s.roll = ((int16_t) ((int16_t) buffer[3] << 8 | (int16_t) buffer[2])) / 32768.0f * 180.0f;
				jy901s.pitch = ((int16_t) ((int16_t) buffer[5] << 8 | (int16_t) buffer[4])) / 32768.0f * 180.0f;
				jy901s.yaw = ((int16_t) ((int16_t) buffer[7] << 8 | (int16_t) buffer[6])) / 32768.0f * 180.0f ;
 			}
			state = 0;
			index = 0;	
		}
	}
}

float ang_offset = 0.0f;

/**
 * @brief IMU 偏航角校准，计算初始偏移量
 * @note  增加采样次数以滤除随机噪声，并优化了内存使用
 */
void IMU_YawCalibrate(void) 
{
    const uint8_t sample_count = 50; 
    float sum = 0.0f;
    // 视觉反馈：开始校准
    SetLedMode(LED_BLUE, LED_ON);
    delay_ms(100);
    SetLedMode(LED_BLUE, LED_OFF);
    SetLedMode(LED_GREEN, LED_ON);

    for (uint8_t i = 0; i < sample_count; i++) 
    {
        sum += jy901s.yaw;
        delay_ms(2); 
    }

    // 计算平均值作为偏移量
    ang_offset = sum / (float)sample_count;
    first_flag = 1;
    // 视觉反馈：校准结束
    SetLedMode(LED_GREEN, LED_OFF);
}

