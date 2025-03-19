/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA1
#define PWM_0_INST_IRQHandler                                   TIMA1_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_4
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM17)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM17_PF_TIMA1_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOB
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_1
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM13)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM13_PF_TIMA1_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (999U)




/* Defines for I2C_1 */
#define I2C_1_INST                                                          I2C1
#define I2C_1_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_1_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_1_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_1_SDA_PORT                                                GPIOB
#define GPIO_I2C_1_SDA_PIN                                         DL_GPIO_PIN_3
#define GPIO_I2C_1_IOMUX_SDA                                     (IOMUX_PINCM16)
#define GPIO_I2C_1_IOMUX_SDA_FUNC                      IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_1_SCL_PORT                                                GPIOB
#define GPIO_I2C_1_SCL_PIN                                         DL_GPIO_PIN_2
#define GPIO_I2C_1_IOMUX_SCL                                     (IOMUX_PINCM15)
#define GPIO_I2C_1_IOMUX_SCL_FUNC                      IOMUX_PINCM15_PF_I2C1_SCL

/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                        DL_GPIO_PIN_28
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM3)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM3_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                         DL_GPIO_PIN_1
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM2)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM2_PF_I2C0_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                 (19200)
#define UART_0_IBRD_4_MHZ_19200_BAUD                                        (13)
#define UART_0_FBRD_4_MHZ_19200_BAUD                                         (1)
/* Defines for UART_JY61P */
#define UART_JY61P_INST                                                    UART2
#define UART_JY61P_INST_IRQHandler                              UART2_IRQHandler
#define UART_JY61P_INST_INT_IRQN                                  UART2_INT_IRQn
#define GPIO_UART_JY61P_RX_PORT                                            GPIOB
#define GPIO_UART_JY61P_TX_PORT                                            GPIOB
#define GPIO_UART_JY61P_RX_PIN                                    DL_GPIO_PIN_16
#define GPIO_UART_JY61P_TX_PIN                                    DL_GPIO_PIN_17
#define GPIO_UART_JY61P_IOMUX_RX                                 (IOMUX_PINCM33)
#define GPIO_UART_JY61P_IOMUX_TX                                 (IOMUX_PINCM43)
#define GPIO_UART_JY61P_IOMUX_RX_FUNC                  IOMUX_PINCM33_PF_UART2_RX
#define GPIO_UART_JY61P_IOMUX_TX_FUNC                  IOMUX_PINCM43_PF_UART2_TX
#define UART_JY61P_BAUD_RATE                                             (19200)
#define UART_JY61P_IBRD_32_MHZ_19200_BAUD                                  (104)
#define UART_JY61P_FBRD_32_MHZ_19200_BAUD                                   (11)





/* Port definition for Pin Group LED1 */
#define LED1_PORT                                                        (GPIOA)

/* Defines for PIN_0: GPIOA.0 with pinCMx 1 on package pin 33 */
#define LED1_PIN_0_PIN                                           (DL_GPIO_PIN_0)
#define LED1_PIN_0_IOMUX                                          (IOMUX_PINCM1)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOB)

/* Defines for PIN_21: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEY_PIN_21_PIN                                          (DL_GPIO_PIN_21)
#define KEY_PIN_21_IOMUX                                         (IOMUX_PINCM49)
/* Port definition for Pin Group RGB_Red */
#define RGB_Red_PORT                                                     (GPIOB)

/* Defines for PIN_26: GPIOB.26 with pinCMx 57 on package pin 28 */
#define RGB_Red_PIN_26_PIN                                      (DL_GPIO_PIN_26)
#define RGB_Red_PIN_26_IOMUX                                     (IOMUX_PINCM57)
/* Port definition for Pin Group GPIO_GRP_0 */
#define GPIO_GRP_0_PORT                                                  (GPIOB)

/* Defines for PIN_1: GPIOB.13 with pinCMx 30 on package pin 1 */
#define GPIO_GRP_0_PIN_1_PIN                                    (DL_GPIO_PIN_13)
#define GPIO_GRP_0_PIN_1_IOMUX                                   (IOMUX_PINCM30)
/* Port definition for Pin Group KEY2 */
#define KEY2_PORT                                                        (GPIOB)

/* Defines for PIN_2: GPIOB.0 with pinCMx 12 on package pin 47 */
#define KEY2_PIN_2_PIN                                           (DL_GPIO_PIN_0)
#define KEY2_PIN_2_IOMUX                                         (IOMUX_PINCM12)
/* Port definition for Pin Group BEEF */
#define BEEF_PORT                                                        (GPIOA)

/* Defines for PIN_27: GPIOA.27 with pinCMx 60 on package pin 31 */
#define BEEF_PIN_27_PIN                                         (DL_GPIO_PIN_27)
#define BEEF_PIN_27_IOMUX                                        (IOMUX_PINCM60)
/* Port definition for Pin Group ENCODERA */
#define ENCODERA_PORT                                                    (GPIOA)

/* Defines for E1A: GPIOA.15 with pinCMx 37 on package pin 8 */
// groups represented: ["ENCODERB","ENCODERA"]
// pins affected: ["E2A","E2B","E1A","E1B"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define ENCODERA_E1A_IIDX                                   (DL_GPIO_IIDX_DIO15)
#define ENCODERA_E1A_PIN                                        (DL_GPIO_PIN_15)
#define ENCODERA_E1A_IOMUX                                       (IOMUX_PINCM37)
/* Defines for E1B: GPIOA.16 with pinCMx 38 on package pin 9 */
#define ENCODERA_E1B_IIDX                                   (DL_GPIO_IIDX_DIO16)
#define ENCODERA_E1B_PIN                                        (DL_GPIO_PIN_16)
#define ENCODERA_E1B_IOMUX                                       (IOMUX_PINCM38)
/* Port definition for Pin Group ENCODERB */
#define ENCODERB_PORT                                                    (GPIOA)

/* Defines for E2A: GPIOA.17 with pinCMx 39 on package pin 10 */
#define ENCODERB_E2A_IIDX                                   (DL_GPIO_IIDX_DIO17)
#define ENCODERB_E2A_PIN                                        (DL_GPIO_PIN_17)
#define ENCODERB_E2A_IOMUX                                       (IOMUX_PINCM39)
/* Defines for E2B: GPIOA.22 with pinCMx 47 on package pin 18 */
#define ENCODERB_E2B_IIDX                                   (DL_GPIO_IIDX_DIO22)
#define ENCODERB_E2B_PIN                                        (DL_GPIO_PIN_22)
#define ENCODERB_E2B_IOMUX                                       (IOMUX_PINCM47)
/* Port definition for Pin Group Sensor */
#define Sensor_PORT                                                      (GPIOA)

/* Defines for Sensor1: GPIOA.3 with pinCMx 8 on package pin 43 */
#define Sensor_Sensor1_PIN                                       (DL_GPIO_PIN_3)
#define Sensor_Sensor1_IOMUX                                      (IOMUX_PINCM8)
/* Defines for Sensor2: GPIOA.4 with pinCMx 9 on package pin 44 */
#define Sensor_Sensor2_PIN                                       (DL_GPIO_PIN_4)
#define Sensor_Sensor2_IOMUX                                      (IOMUX_PINCM9)
/* Defines for Sensor3: GPIOA.5 with pinCMx 10 on package pin 45 */
#define Sensor_Sensor3_PIN                                       (DL_GPIO_PIN_5)
#define Sensor_Sensor3_IOMUX                                     (IOMUX_PINCM10)
/* Defines for Sensor4: GPIOA.6 with pinCMx 11 on package pin 46 */
#define Sensor_Sensor4_PIN                                       (DL_GPIO_PIN_6)
#define Sensor_Sensor4_IOMUX                                     (IOMUX_PINCM11)
/* Defines for Sensor5: GPIOA.29 with pinCMx 4 on package pin 36 */
#define Sensor_Sensor5_PIN                                      (DL_GPIO_PIN_29)
#define Sensor_Sensor5_IOMUX                                      (IOMUX_PINCM4)
/* Defines for Sensor6: GPIOA.30 with pinCMx 5 on package pin 37 */
#define Sensor_Sensor6_PIN                                      (DL_GPIO_PIN_30)
#define Sensor_Sensor6_IOMUX                                      (IOMUX_PINCM5)
/* Defines for Sensor7: GPIOA.31 with pinCMx 6 on package pin 39 */
#define Sensor_Sensor7_PIN                                      (DL_GPIO_PIN_31)
#define Sensor_Sensor7_IOMUX                                      (IOMUX_PINCM6)
/* Defines for Sensor8: GPIOA.2 with pinCMx 7 on package pin 42 */
#define Sensor_Sensor8_PIN                                       (DL_GPIO_PIN_2)
#define Sensor_Sensor8_IOMUX                                      (IOMUX_PINCM7)
/* Port definition for Pin Group KEY3 */
#define KEY3_PORT                                                        (GPIOB)

/* Defines for PIN_3: GPIOB.24 with pinCMx 52 on package pin 23 */
#define KEY3_PIN_3_PIN                                          (DL_GPIO_PIN_24)
#define KEY3_PIN_3_IOMUX                                         (IOMUX_PINCM52)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_I2C_1_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_JY61P_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
