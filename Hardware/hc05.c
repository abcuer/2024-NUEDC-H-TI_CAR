#include "headfile.h"
uint8_t hc05_data = 0, hc05_flag = 0;

void HC05_Init(void)
{
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
}

#define HEADER1 0xAA
#define HEADER2 0x55
#define TAIL1   0x0D
#define TAIL2   0x0A
#define MAX_FRAME_LEN 256

/*  AA 55 01 00 01 0D 0A  */
typedef enum {
    WAIT_HEADER1,
    WAIT_HEADER2,
    WAIT_CMD, // �����
    WAIT_LEN,
    WAIT_DATA,
    WAIT_CHECKSUM,
    WAIT_TAIL1,
    WAIT_TAIL2
} RxState_t;

volatile RxState_t rx_state = WAIT_HEADER1;
volatile uint8_t rx_buf[MAX_FRAME_LEN];
volatile uint8_t rx_index = 0;
volatile uint8_t data_len = 0;

void uart_send_bytes(uint8_t *buf, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        while (DL_UART_isBusy(UART_0_INST))
        {
            // �ȴ�ֱ�����ڿ���
        }

        DL_UART_Main_transmitData(UART_0_INST, buf[i]);
    }
}

void send_cmd(uint8_t cmd, uint8_t *data, uint8_t len)
{
    uint8_t buf[260];
    buf[0] = HEADER1;
    buf[1] = HEADER2;
    buf[2] = cmd;
    buf[3] = len;

    for(uint8_t i=0; i<len; i++)
        buf[4+i] = data[i];

    uint8_t checksum = cmd ^ len;
    for(uint8_t i=0; i<len; i++)
        checksum ^= data[i];

    buf[4+len] = checksum;
    buf[5+len] = TAIL1;
    buf[6+len] = TAIL2;

    uart_send_bytes(buf, 7 + len);
}

void process_cmd(uint8_t cmd, uint8_t *data, uint8_t len)
{
    switch(cmd)
    {
        case 0x01:  // ����ָ��ʾ��
            // ִ����������
            LED_Blue_ON();
            break;

        case 0x02:  // ָֹͣ��ʾ��
            LED_Blue_OFF();
            break;

        case 0x03:  // �����ٶȣ�data[0]Ϊ�ٶ�ֵ
            speed_tar = data[0];
			pid_flag = SPEED_PID;
            break;

        // ���������...

        default:
            // δ֪����
            break;
    }
}

void UART_0_INST_IRQHandler(void)
{
    if(DL_UART_getPendingInterrupt(UART_0_INST) == DL_UART_IIDX_RX)
    {
        uint8_t byte = DL_UART_Main_receiveData(UART_0_INST);

        switch(rx_state)
        {
            case WAIT_HEADER1:
                if(byte == HEADER1) rx_state = WAIT_HEADER2;
                break;

            case WAIT_HEADER2:
                if(byte == HEADER2) rx_state = WAIT_CMD;
                else rx_state = WAIT_HEADER1;
                break;

            case WAIT_CMD:
                rx_buf[0] = byte; // cmd
                rx_state = WAIT_LEN;
                break;

            case WAIT_LEN:
                data_len = byte;
                if(data_len > MAX_FRAME_LEN - 6)
                    rx_state = WAIT_HEADER1; // �����쳣����
                else
                {
                    rx_index = 0;
                    rx_state = (data_len > 0) ? WAIT_DATA : WAIT_CHECKSUM;
                }
                break;

            case WAIT_DATA:
                rx_buf[1 + rx_index++] = byte;
                if(rx_index >= data_len) rx_state = WAIT_CHECKSUM;
                break;

            case WAIT_CHECKSUM:
            {
                uint8_t checksum = rx_buf[0] ^ data_len;
                for(uint8_t i=0; i<data_len; i++)
                    checksum ^= rx_buf[1 + i];

                if(checksum == byte)
                    rx_state = WAIT_TAIL1;
                else
                    rx_state = WAIT_HEADER1; // У��ʧ�ܶ���
                break;
            }

            case WAIT_TAIL1:
                if(byte == TAIL1) rx_state = WAIT_TAIL2;
                else rx_state = WAIT_HEADER1;
                break;

            case WAIT_TAIL2:
                if(byte == TAIL2)
                {
                    // ����֡���ճɹ������������
                    process_cmd(rx_buf[0], (uint8_t *)&rx_buf[1], data_len);
                }
                rx_state = WAIT_HEADER1; // ׼����һ֡
                break;

            default:
                rx_state = WAIT_HEADER1;
                break;
        }
    }
}




//RxState_t rx_state = WAIT_HEADER1;

//void uart_rx_handler(uint8_t byte)
//{
//    switch(rx_state)
//    {
//        case WAIT_HEADER1:
//            if(byte == HEADER1)
//            {
//                rx_state = WAIT_HEADER2;
//            }
//            break;

//        case WAIT_HEADER2:
//            if(byte == HEADER2)
//            {
//                rx_state = WAIT_CMD;
//            }
//            else
//            {
//                rx_state = WAIT_HEADER1;
//            }
//            break;

//        case WAIT_CMD:
//            rx_buf[0] = byte;
//            rx_state = WAIT_LEN;
//            break;

//        case WAIT_LEN:
//            data_len = byte;
//            if(data_len > MAX_FRAME_LEN - 6) // ���ռ��ͷβ��У��
//            {
//                rx_state = WAIT_HEADER1; // ���ȷǷ�������
//            }
//            else
//            {
//                rx_index = 0;
//                rx_state = (data_len > 0) ? WAIT_DATA : WAIT_CHECKSUM;
//            }
//            break;

//        case WAIT_DATA:
//            rx_buf[1 + rx_index++] = byte;
//            if(rx_index >= data_len)
//            {
//                rx_state = WAIT_CHECKSUM;
//            }
//            break;

//        case WAIT_CHECKSUM:
//        {
//            uint8_t checksum = rx_buf[0] ^ data_len;
//            for(uint8_t i=0; i < data_len; i++)
//                checksum ^= rx_buf[1 + i];

//            if(checksum == byte)
//            {
//                rx_state = WAIT_TAIL1; // У����ȷ���ȴ�֡β
//            }
//            else
//            {
//                rx_state = WAIT_HEADER1; // У����󣬶���
//            }
//            break;
//        }

//        case WAIT_TAIL1:
//            if(byte == TAIL1)
//                rx_state = WAIT_TAIL2;
//            else
//                rx_state = WAIT_HEADER1;
//            break;

//        case WAIT_TAIL2:
//            if(byte == TAIL2)
//            {
//                // ��֡���ճɹ�����������
//                process_cmd(rx_buf[0], &rx_buf[1], data_len);
//            }
//            // �����Ƿ�ɹ���״̬������׼����һ֡
//            rx_state = WAIT_HEADER1;
//            break;

//        default:
//            rx_state = WAIT_HEADER1;
//            break;
//    }
//}


//
//void UART_0_INST_IRQHandler(void)
//{
//    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
//    {
//        case DL_UART_IIDX_RX:
//            hc05_data = DL_UART_Main_receiveData(UART_0_INST);
//			hc05_flag = 1;
//            break;

//		default:
//            break;
//    }
//}

