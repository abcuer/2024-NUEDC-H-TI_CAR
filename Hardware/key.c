#include "key.h"
#include "delay.h"

uint8_t Key_GetNum1(void)
{
    uint8_t KeyNum = 0;
    
    if (DL_GPIO_readPins(KEY_PORT, KEY_TASK_PIN) == 0) 
    {
		delay_ms(40);
		while(DL_GPIO_readPins(KEY_PORT, KEY_TASK_PIN) == 0);
		delay_ms(40);
        KeyNum = 1; 
    }
    return KeyNum; 
}

uint8_t Key_GetNum2(void)
{
    uint8_t KeyNum = 0;
    
    if (DL_GPIO_readPins(KEY_PORT, KEY_START_PIN) == 0) 
    {
		delay_ms(40);
		while(DL_GPIO_readPins(KEY_PORT, KEY_START_PIN) == 0);
		delay_ms(40);
        KeyNum = 1; 
    }
    return KeyNum; 
}

