#include "uart.h"
#include "stdio.h"
#include "jy901s.h"
#include "ti_msp_dl_config.h"

#if !defined(__MICROLIB)
#if (__ARMCLIB_VERSION <= 6000000)
struct __FILE
{
    int handle;
};
#endif

FILE __stdout;

void _sys_exit(int x)
{
    x = x;
}
#endif

// printf
int fputc(int ch, FILE *stream)
{
    while (DL_UART_isBusy(UART_2_INST) == true);
        
    DL_UART_Main_transmitData(UART_2_INST, ch);

    return ch;
}

void UartDeviceInit(void)
{
	NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);
}

void UART_2_INST_IRQHandler(void)
{
    switch (DL_UART_getPendingInterrupt(UART_2_INST))
    {
		uint8_t uart_data = 0;
		case DL_UART_IIDX_RX:
			uart_data = DL_UART_Main_receiveData(UART_2_INST);
			IMU_ParseData(uart_data);

			break;

		default:
			break;
    }
}

