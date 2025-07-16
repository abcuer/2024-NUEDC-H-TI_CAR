/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-26     LCKFB     first version
 */
#include "board.h"
#include "stdio.h"
#include "jy901s.h"

#define RE_0_BUFF_LEN_MAX 128

volatile uint8_t recv0_buff[RE_0_BUFF_LEN_MAX] = {0};

void board_init(void)
{
    // SYSCFG��ʼ��
    SYSCFG_DL_init();
    // ��������жϱ�־
    NVIC_ClearPendingIRQ(UART_2_INST_INT_IRQN);
    // ʹ�ܴ����ж�
    NVIC_EnableIRQ(UART_2_INST_INT_IRQN);

    //	//UART0->printf
    //	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    //	//ʹ�ܴ����ж�
    //	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    // printf("Board Init Success\r\n");
}

void delay_us(unsigned long __us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;
	
    ticks = __us * (32000000 / 1000000);


    told = SysTick->VAL;

    while (1)
    {
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            if (tcnt >= ticks)
                break;
        }
    }
}

void delay_ms(unsigned long ms)
{
    delay_us(ms * 1000);
}

void delay_1us(unsigned long __us) { delay_us(__us); }
void delay_1ms(unsigned long ms) { delay_ms(ms); }


void uart0_send_char(char ch)
{

    while (DL_UART_isBusy(UART_2_INST) == true);

    DL_UART_Main_transmitData(UART_2_INST, ch);
}

void uart0_send_string(char *str)
{

    while (*str != 0 && str != 0)
    {
        // �����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
        uart0_send_char(*str++);
    }
}

#if !defined(__MICROLIB)
// ��ʹ��΢��Ļ�����Ҫ��������ĺ���
#if (__ARMCLIB_VERSION <= 6000000)
// �����������AC5  �Ͷ�����������ṹ��
struct __FILE
{
    int handle;
};
#endif

FILE __stdout;

// ����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
    x = x;
}
#endif

// printf�����ض���
int fputc(int ch, FILE *stream)
{
    // ������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
    while (DL_UART_isBusy(UART_2_INST) == true)
        ;

    DL_UART_Main_transmitData(UART_2_INST, ch);

    return ch;
}

// ���ڵ��жϷ�����
void UART_2_INST_IRQHandler(void)
{
    uint8_t uart_data = 0;

    switch (DL_UART_getPendingInterrupt(UART_2_INST))
    {
    case DL_UART_IIDX_RX:

        uart_data = DL_UART_Main_receiveData(UART_2_INST);
        jy901s_ReceiveData(uart_data);
        break;

    default:
        break;
    }
}

// void UART_0_INST_IRQHandler(void)
//{
//	uint8_t uart_data = 0;
//
//     switch( DL_UART_getPendingInterrupt(UART_0_INST) )
//     {
//         case DL_UART_IIDX_RX:
//
//
//             uart_data = DL_UART_Main_receiveData(UART_0_INST);
//
//             uart0_send_char(uart_data);
//             break;

//        default:
//            break;
//    }
//}
