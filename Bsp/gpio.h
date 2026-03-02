#ifndef _GPIO_H
#define _GPIO_H

#include "ti_msp_dl_config.h"

// 适配 STM32 的速度枚举
typedef enum {
    BSP_GPIO_SPEED_LOW = 0,
    BSP_GPIO_SPEED_MED,
    BSP_GPIO_SPEED_HIGH
} GPIO_Speed_e;

/* 函数声明 */
void GPIO_Output(GPIO_Regs* GPIOx, uint32_t GPIO_Pin, GPIO_Speed_e speed);
void GPIO_Input(GPIO_Regs* GPIOx, uint32_t GPIO_Pin, uint32_t mode);

#endif