#include "gpio.h"

static void GPIO_SetClock(GPIO_Regs* GPIOx)
{
    // 开启对应端口电源
    DL_GPIO_enablePower(GPIOx);
}

/**
 * @brief  通用的推挽输出初始化
 */
void GPIO_Output(GPIO_Regs* GPIOx, uint32_t GPIO_Pin, GPIO_Speed_e speed)
{
    // 1. 开启对应端口电源
    GPIO_SetClock(GPIOx);

    // 2. 确定驱动强度
    DL_GPIO_DRIVE_STRENGTH driveStrength = (speed == BSP_GPIO_SPEED_HIGH) ? 
                                            DL_GPIO_DRIVE_STRENGTH_HIGH : 
                                            DL_GPIO_DRIVE_STRENGTH_LOW;

    // 3. 使用功能集初始化函数 (一步到位配置 MUX, 驱动能力和方向)
    DL_GPIO_initDigitalOutputFeatures(GPIO_Pin, 
                                     DL_GPIO_INVERSION_DISABLE, 
                                     DL_GPIO_RESISTOR_NONE, 
                                     driveStrength, 
                                     DL_GPIO_HIZ_DISABLE);

    // 4. 使能输出模式
    DL_GPIO_enableOutput(GPIOx, GPIO_Pin);
}

/**
 * @brief  通用的输入初始化
 */
void GPIO_Input(GPIO_Regs* GPIOx, uint32_t GPIO_Pin, uint32_t mode)
{
    // 1. 开启对应端口电源
    GPIO_SetClock(GPIOx);

    // 2. 初始化为数字输入并配置电阻
    DL_GPIO_initDigitalInputFeatures(GPIO_Pin,
                                    DL_GPIO_INVERSION_DISABLE,
                                    (DL_GPIO_RESISTOR)mode,
                                    DL_GPIO_HYSTERESIS_DISABLE,
                                    DL_GPIO_WAKEUP_DISABLE);
}
