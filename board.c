#include "board.h"
#include "stdio.h"
#include "led.h"
#define RE_0_BUFF_LEN_MAX	128

volatile uint8_t  recv0_buff[RE_0_BUFF_LEN_MAX] = {0};
volatile uint16_t recv0_length = 0;
volatile uint8_t  recv0_flag = 0;

//void board_init(void)
//{
//	// SYSCFG��ʼ��
//	SYSCFG_DL_init();
//	//��������жϱ�־
//	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
//	//ʹ�ܴ����ж�
//	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
//	
//	printf("Board Init [[ ** LCKFB ** ]]\r\n");
//}

//����δ�ʱ��ʵ�ֵľ�ȷus��ʱ
void delay_us(unsigned long __us) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;

    // ������Ҫ��ʱ���� = �ӳ�΢���� * ÿ΢���ʱ����
    ticks = __us * (32000000 / 1000000);

    // ��ȡ��ǰ��SysTickֵ
    told = SysTick->VAL;

    while (1)
    {
        // �ظ�ˢ�»�ȡ��ǰ��SysTickֵ
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            // ����ﵽ����Ҫ��ʱ���������˳�ѭ��
            if (tcnt >= ticks)
                break;
        }
    }
}
//����δ�ʱ��ʵ�ֵľ�ȷms��ʱ
void delay_ms(unsigned long ms) 
{
	delay_us( ms * 1000 );
}

void delay_1us(unsigned long __us){ delay_us(__us); }
void delay_1ms(unsigned long ms){ delay_ms(ms); }

//���ڷ��͵����ַ�
void uart0_send_char(char ch)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_0_INST) == true );
	//���͵����ַ�
	DL_UART_Main_transmitData(UART_0_INST, ch);

}
//���ڷ����ַ���
void uart0_send_string(char* str)
{
	//��ǰ�ַ�����ַ���ڽ�β ���� �ַ����׵�ַ��Ϊ��
	while(*str!=0&&str!=0)
	{
		//�����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
		uart0_send_char(*str++);
	}
}


#if !defined(__MICROLIB)
//��ʹ��΢��Ļ�����Ҫ�������ĺ���
#if (__ARMCLIB_VERSION <= 6000000)
//�����������AC5  �Ͷ�����������ṹ��
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
#endif


//printf�����ض���
int fputc(int ch, FILE *stream)
{
	//������0æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);
	
	return ch;
}


// ������ձ���
uint8_t RollL, RollH, PitchL, PitchH, YawL, YawH, VL, VH, SUM;
float Pitch,Roll,Yaw;
// ���ڽ���״̬��ʶ
#define WAIT_HEADER1 0
#define WAIT_HEADER2 1
#define RECEIVE_DATA 2

uint8_t RxState = WAIT_HEADER1;
uint8_t receivedData[9];
uint8_t dataIndex = 0;



//������ƫ������������
void Serial_JY61P_Zero_Yaw(void){
   DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X69);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X88);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XB5);
	delay_ms(100);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X01);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X04);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	delay_ms(100);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	
}


//������x,y����������
void Serial_JY61P_XY_Yaw(void){
   DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X69);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X88);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XB5);
	delay_ms(100);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X01);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X08);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	delay_ms(100);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XFF);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0XAA);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	DL_UART_Main_transmitDataBlocking(UART_JY61P_INST,0X00);
	
}


//���ڵ��жϷ�����
void UART_0_INST_IRQHandler(void)
{
	 uint8_t uartdata = DL_UART_Main_receiveData(UART_0_INST); // ����һ��uint8_t����
		//LED_Toggle();
    switch (RxState) {
    case WAIT_HEADER1:
        if (uartdata == 0x55) {
            RxState = WAIT_HEADER2;
        }
        break;
    case WAIT_HEADER2:
        if (uartdata == 0x53) {
            RxState = RECEIVE_DATA;
            dataIndex = 0;
        } else {
            RxState = WAIT_HEADER1; // ������������ĵڶ���ͷ������״̬
        }
        break;
    case RECEIVE_DATA:
        receivedData[dataIndex++] = uartdata;
        if (dataIndex == 9) {
            // ���ݽ�����ϣ����������ı���
            RollL = receivedData[0];
            RollH = receivedData[1];
            PitchL = receivedData[2];
            PitchH = receivedData[3];
            YawL = receivedData[4];
            YawH = receivedData[5];
            VL = receivedData[6];
            VH = receivedData[7];
            SUM = receivedData[8];

            // У��SUM�Ƿ���ȷ
            uint8_t calculatedSum = 0x55 + 0x53 + RollH + RollL + PitchH + PitchL + YawH + YawL + VH + VL;
            if (calculatedSum == SUM) {
                // У��ɹ������Խ��к�������
                if((float)(((uint16_t)RollH << 8) | RollL)/32768*180>180){
                    Roll = (float)(((uint16_t)RollH << 8) | RollL)/32768*180 - 360;
                }else{
                    Roll = (float)(((uint16_t)RollH << 8) | RollL)/32768*180;
                }

                if((float)(((uint16_t)PitchH << 8) | PitchL)/32768*180>180){
                    Pitch = (float)(((uint16_t)PitchH << 8) | PitchL)/32768*180 - 360;
                }else{
                    Pitch = (float)(((uint16_t)PitchH << 8) | PitchL)/32768*180;
                }

                if((float)(((uint16_t)YawH << 8) | YawL)/32768*180 >180){
                    Yaw = (float)(((uint16_t)YawH << 8) | YawL)/32768*180 - 360;
                }else{
                    Yaw = (float)(((uint16_t)YawH << 8) | YawL)/32768*180;
                }
                //LED_Toggle();
                
            } else {
                // У��ʧ�ܣ��������
							
            }
						//LED_Toggle();
            RxState = WAIT_HEADER1; // ����״̬�Եȴ���һ�����ݰ�
        }
        break;
    }
		NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN); //UART
	/*
	uint8_t receivedData = 0;
	
	//��������˴����ж�
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_RX://����ǽ����ж�
			//LED_Toggle();
			// ���շ��͹��������ݱ���
			receivedData = DL_UART_Main_receiveData(UART_0_INST);

			// ��黺�����Ƿ�����
			if (recv0_length < RE_0_BUFF_LEN_MAX - 1)
			{
				recv0_buff[recv0_length++] = receivedData;

				// ������������ٷ��ͳ�ȥ������ش�����ע�͵�
				uart0_send_char(receivedData);
			}
			else
			{
				recv0_length = 0;
			}

			// ��ǽ��ձ�־
			recv0_flag = 1;
		
			break;
		
		default://�����Ĵ����ж�
			break;
	}*/
}
