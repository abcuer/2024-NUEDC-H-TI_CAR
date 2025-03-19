#include "board.h"
#include "stdio.h"
#include "led.h"
#define RE_0_BUFF_LEN_MAX	128

volatile uint8_t  recv0_buff[RE_0_BUFF_LEN_MAX] = {0};
volatile uint16_t recv0_length = 0;
volatile uint8_t  recv0_flag = 0;

//void board_init(void)
//{
//	// SYSCFG初始化
//	SYSCFG_DL_init();
//	//清除串口中断标志
//	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
//	//使能串口中断
//	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
//	
//	printf("Board Init [[ ** LCKFB ** ]]\r\n");
//}

//搭配滴答定时器实现的精确us延时
void delay_us(unsigned long __us) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;

    // 计算需要的时钟数 = 延迟微秒数 * 每微秒的时钟数
    ticks = __us * (32000000 / 1000000);

    // 获取当前的SysTick值
    told = SysTick->VAL;

    while (1)
    {
        // 重复刷新获取当前的SysTick值
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            // 如果达到了需要的时钟数，就退出循环
            if (tcnt >= ticks)
                break;
        }
    }
}
//搭配滴答定时器实现的精确ms延时
void delay_ms(unsigned long ms) 
{
	delay_us( ms * 1000 );
}

void delay_1us(unsigned long __us){ delay_us(__us); }
void delay_1ms(unsigned long ms){ delay_ms(ms); }

//串口发送单个字符
void uart0_send_char(char ch)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_0_INST) == true );
	//发送单个字符
	DL_UART_Main_transmitData(UART_0_INST, ch);

}
//串口发送字符串
void uart0_send_string(char* str)
{
	//当前字符串地址不在结尾 并且 字符串首地址不为空
	while(*str!=0&&str!=0)
	{
		//发送字符串首地址中的字符，并且在发送完成之后首地址自增
		uart0_send_char(*str++);
	}
}


#if !defined(__MICROLIB)
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif


//printf函数重定义
int fputc(int ch, FILE *stream)
{
	//当串口0忙的时候等待，不忙的时候再发送传进来的字符
	while( DL_UART_isBusy(UART_0_INST) == true );
	
	DL_UART_Main_transmitData(UART_0_INST, ch);
	
	return ch;
}


// 定义接收变量
uint8_t RollL, RollH, PitchL, PitchH, YawL, YawH, VL, VH, SUM;
float Pitch,Roll,Yaw;
// 串口接收状态标识
#define WAIT_HEADER1 0
#define WAIT_HEADER2 1
#define RECEIVE_DATA 2

uint8_t RxState = WAIT_HEADER1;
uint8_t receivedData[9];
uint8_t dataIndex = 0;



//发送置偏航角置零命令
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


//发送置x,y角置零命令
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


//串口的中断服务函数
void UART_0_INST_IRQHandler(void)
{
	 uint8_t uartdata = DL_UART_Main_receiveData(UART_0_INST); // 接收一个uint8_t数据
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
            RxState = WAIT_HEADER1; // 如果不是期望的第二个头，重置状态
        }
        break;
    case RECEIVE_DATA:
        receivedData[dataIndex++] = uartdata;
        if (dataIndex == 9) {
            // 数据接收完毕，分配给具体的变量
            RollL = receivedData[0];
            RollH = receivedData[1];
            PitchL = receivedData[2];
            PitchH = receivedData[3];
            YawL = receivedData[4];
            YawH = receivedData[5];
            VL = receivedData[6];
            VH = receivedData[7];
            SUM = receivedData[8];

            // 校验SUM是否正确
            uint8_t calculatedSum = 0x55 + 0x53 + RollH + RollL + PitchH + PitchL + YawH + YawL + VH + VL;
            if (calculatedSum == SUM) {
                // 校验成功，可以进行后续处理
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
                // 校验失败，处理错误
							
            }
						//LED_Toggle();
            RxState = WAIT_HEADER1; // 重置状态以等待下一个数据包
        }
        break;
    }
		NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN); //UART
	/*
	uint8_t receivedData = 0;
	
	//如果产生了串口中断
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_RX://如果是接收中断
			//LED_Toggle();
			// 接收发送过来的数据保存
			receivedData = DL_UART_Main_receiveData(UART_0_INST);

			// 检查缓冲区是否已满
			if (recv0_length < RE_0_BUFF_LEN_MAX - 1)
			{
				recv0_buff[recv0_length++] = receivedData;

				// 将保存的数据再发送出去，不想回传可以注释掉
				uart0_send_char(receivedData);
			}
			else
			{
				recv0_length = 0;
			}

			// 标记接收标志
			recv0_flag = 1;
		
			break;
		
		default://其他的串口中断
			break;
	}*/
}
