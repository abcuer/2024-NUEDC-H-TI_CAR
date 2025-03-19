#include "board.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "key.h"
#include "led.h"
#include "motor.h"
#include "Sensor.h"
#include "PID.h"
#include "JY901P.h"
#include "OLED.h"
#include "OLED_Data.h"
#include "MYIIC.h"


int32_t Get_Encoder_countA,encoderA_cnt,PWMA,Get_Encoder_countB,encoderB_cnt,PWMB;
uint8_t Key_Num = 0;

extern tPid PID_Link;               //定义一个循迹结构体
int deviation = 0;

int PWML=0;					
int PWML_Base=1000;

int PWMR=0;				
int PWMR_Base=1000;
int PWML_MAX = 1200;
int PWMR_MAX = 1200;
int TrackFlag=1;		//定义循迹标志位，为0停止循迹，为1开始循迹
int read_flag = 1; 	//读取灰度传感器
extern uint8_t sensor_arr[8];
extern int error;
int track_err = 0;
extern int Yaw_err;
extern int Yaw_err2;
float imu_err = 0;
float imu_err2 = 0;


#define PI 3.14159265

int One_Wheel_len = 204;		 //mm  一轮长度
int One_Wheel_Mai = 730;   	//一圈脉冲数
float Wheel_count = 0.2794; //mm 一个脉冲数转长度
float carL_dis = 0;
float carR_dis = 0;


float dis_Q1 = 980;
float distance = 940;	//mm 
float distance2 = 1000;	//mm 
float dis1=905;
float dis2=950;


int move_flag = 1;
int RunMode = 0;       // 运行模式

extern float Pitch,Roll,Yaw;
int imu_read_flag = 1;

int time_flag = 0;
int time_count = 0;



int L_B_flag = 0;
int quan_num =0;
int Q4_flag = 0;
int readKey_flag = 1;

/**按键Flag**/
int key_count = 0;

int key2_count = 0;

int Task_Num = 1; //要求1、2、3、4

int Task_Flag = 0; //0无效

char number[]="1";

	
int main(void)
{
	SYSCFG_DL_init();
  DL_Timer_startCounter(PWM_0_INST); //PWM
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN); //UART
	NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);//TIMER_INT
	NVIC_ClearPendingIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);	//使能串口中断
	NVIC_EnableIRQ(UART_JY61P_INST_INT_IRQN);           //使能中断
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//使能定时器中断
	NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);
	//DL_GPIO_clearPins(GPIOB, RGB_Red_PIN_26_PIN);// RGB红灯 0灭
	DL_GPIO_setPins(LED1_PORT,LED1_PIN_0_PIN); // 绿灯 1灭
	DL_GPIO_clearPins(GPIOB, RGB_Red_PIN_26_PIN);// RGB红灯 1亮
	DL_GPIO_clearPins(GPIOA, BEEF_PIN_27_PIN );//BEEF 1响
	
	delay_ms(1000);
	Set_PWM(0,0);
	PID_init(&PID_Link,0,70,0,200,1000,-1000);   //循迹PID初始化
	OLED_Init();   

	
   while (1) 
   {
     OLED_ShowString(8,0*16,number,OLED_8X16);
     OLED_Update();
		 
		 if(Task_Flag == 1) //任务1
		 {	
			 switch(RunMode)
			 {
				 case 0:
				 {
						Get_Encoder_countA=0;
						Get_Encoder_countB=0;
						carL_dis=0,carR_dis=0;
						RunMode++;
						break;
				 }
				 case 1:
				 {
					readKey_flag = 0;
					carR_dis = Wheel_count * -Get_Encoder_countB;
					carL_dis = Wheel_count * Get_Encoder_countA;
					if((fabsf(carL_dis) >= distance) && (fabsf(carR_dis) >= distance))
					{
						move_flag = 0;
					}
					
					if(move_flag ==1)
					{
						 if(imu_read_flag == 1)
							{
								imu_err = Yaw_error(0,Yaw);
							}			
							
							deviation = (int32_t)PID_realize(&PID_Link,imu_err/1.8); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation ;
										
										
							if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
								 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
							 else if(PWMR < 0)
									PWMR=0;
							Set_PWM(PWML,PWMR);
					}
					else
					{
							Set_PWM(0,0);
							time_flag = 1;
							Task_Flag = 0;
							readKey_flag = 1;
					}	
					break;
				}
			}				
		 }
	 
		 if(Task_Flag == 2)  //任务2
		 {
			  readKey_flag = 0;
			 	switch(RunMode)
				{
					 case 0:
					 {
							Get_Encoder_countA=0;
							Get_Encoder_countB=0;
							carL_dis=0,carR_dis=0;
							RunMode++;
							break;
				  }
					case 1:
					{
						carR_dis = Wheel_count * -Get_Encoder_countB;
						carL_dis = Wheel_count * Get_Encoder_countA;
						if((fabsf(carL_dis) >= distance) && (fabsf(carR_dis) >= distance))
						{
							move_flag = 0;
						}
						
						if(move_flag ==1)
						{
							 if(imu_read_flag == 1)
								{
									imu_err = Yaw_error(0,Yaw);
								}
								deviation = (int32_t)PID_realize(&PID_Link,imu_err/1.8); //获取PID的计算结果
								PWML = PWML_Base - deviation;
								PWMR = PWMR_Base + deviation ;
								
								
								if(PWML > PWML_MAX)
										PWML = PWML_MAX;
								 else if(PWML < 0)
										PWML=0;
									 
								 if(PWMR > PWMR_MAX)
										PWMR = PWMR_MAX;
								 else if(PWMR < 0)
										PWMR=0;
								Set_PWM(PWML,PWMR);
						}
						else
						{
								Set_PWM(0,0);
								TrackFlag=1;
								time_flag = 1;
								RunMode++;
						}	
						break;	
				}
					
				case 2:
				{
					if(TrackFlag==1)	//1开启循迹功能,0关闭
					{				
						if(read_flag == 1)
						{
							sensor_read();
							track_err = track_error();         //获取循迹的偏差  
						}
						
						
						if(track_err < 30000)
						{
							deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation;
							
							
							 if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
							 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
								else if(PWMR < 0)
									PWMR=0;
							Set_PWM(PWML,PWMR);
						}
						else
						{
							Set_PWM(0,0);	
							TrackFlag = 0;
							
							//PID_init(&PID_Link,0,70,0,400,800,-800);   //循迹PID初始化
						}
					}
					else
					{
						move_flag=1;
						time_flag = 1;
						RunMode++;
					}		
					break;	
				}
				
				case 3:
				{
					Get_Encoder_countA=0;
					Get_Encoder_countB=0;
					carL_dis=0,carR_dis=0;
					RunMode++;
					break;
				}
				case 4:
				{
					carR_dis = Wheel_count * -Get_Encoder_countB;
					carL_dis = Wheel_count * Get_Encoder_countA;
					if((fabsf(carL_dis) >= distance) && (fabsf(carR_dis) >= distance))
					{
						//move_flag = 0;
					}
					
					sensor_read();
					for(int i=0;i<8;i++)
					{
						if(sensor_arr[i] == 0)
						{
								move_flag = 0;
						}
					}
					
					if(move_flag ==1)
					{
						 if(imu_read_flag == 1)
							{
								imu_err = -Yaw_error(-178,Yaw);//
							}
							//printf("Yaw:%f,Yawerr:%d\r\n",Yaw,Yaw_err);
							deviation = (int32_t)PID_realize(&PID_Link,imu_err/2.8); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation ;
										
										
							if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
								 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
							 else if(PWMR < 0)
									PWMR=0;
							//printf("Yaw_err2:%f",Yaw_err2);
							//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
							Set_PWM(PWMR,PWML);
					}
					else
					{	
						
							Set_PWM(0,0);
							TrackFlag=1;
							time_flag = 1;
							RunMode++;
					}	
					break;
				}
				
				case 5:
				{
					if(TrackFlag==1)	//1开启循迹功能,0关闭
					{				
						if(read_flag == 1)
						{
							sensor_read();
							track_err = track_error();         //获取循迹的偏差  
						}
						
						
						if(track_err < 30000)
						{
							deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation;
							
							
							 if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
							 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
								else if(PWMR < 0)
									PWMR=0;
							//printf("track_err:%f",track_err);
							//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
							Set_PWM(PWML,PWMR);
						}
						else
						{
							Set_PWM(0,0);
							TrackFlag = 0;
						}
					}
					else
					{
							move_flag=1;
							time_flag = 1;
							RunMode++;
							Task_Flag = 0;
							readKey_flag = 1;
					}		
					break;
				}					
			}
		}
		
		if(Task_Flag == 3 || Task_Flag == 4)
		{
		  readKey_flag = 0;
			switch(RunMode)
			{ 
				case 0:
				{
						Get_Encoder_countA=0;
						Get_Encoder_countB=0;
						carL_dis=0,carR_dis=0;
						RunMode++;
						break;
				}
				case 1:
				{
					carR_dis = Wheel_count * -Get_Encoder_countB;
					carL_dis = Wheel_count * Get_Encoder_countA;
					if((fabsf(carL_dis) >= dis1) && (fabsf(carR_dis) >= dis1))
					{
						move_flag = 0;
					}
					
					if(move_flag ==1)
					{
							if(imu_read_flag == 1)
							{
								if(quan_num == 0)
									imu_err = Yaw_error(-53,Yaw);//
								else
								{
									dis1 = 905;
									imu_err = Yaw_error(-53,Yaw);//
								}
							}
							deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.2); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation ;
										
										
							if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
								 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
							 else if(PWMR < 0)
									PWMR=0;
							//printf("Yaw_err:%f",Yaw_err);
							//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
							Set_PWM(PWML,PWMR);
					}
					else
					{
							Set_PWM(0,0);
							TrackFlag=0;					
							RunMode++;					
					}	
					break;
				}
				
				case 2:
				{
					if(TrackFlag==0)	//1开启循迹功能,0关闭
					{	
						imu_err = Yaw_error(0,Yaw);
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.6); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
						
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
					 else if(PWML < 0)
								PWML=0;
							 
					 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
					 else if(PWMR < 0)
							 PWMR=0;
						Set_PWM(PWML,PWMR);
					 
						sensor_read();	 
						for(int i=0;i<8;i++)
						{
							if((sensor_arr[i] == 0))
							{
									TrackFlag = 1;
									time_flag = 1;
							}
						}
					}
					
					if(TrackFlag==1)	//1开启循迹功能,0关闭
					{				
						if(read_flag == 1)
						{
							sensor_read();
							track_err = track_error();         //获取循迹的偏差  
						}
						
						if(track_err < 30000)
						{
							deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation;
							
							
							 if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
							 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
								else if(PWMR < 0)
									PWMR=0;
							//printf("track_err:%f",track_err);
							//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
							Set_PWM(PWML,PWMR);
						}
						else
						{
							Set_PWM(0,0);
							TrackFlag = 2;
							move_flag=1;
							time_flag = 1;
							RunMode++;
						}
					}
					break;
				}
				
				case 3:
				{
					Get_Encoder_countA=0;
					Get_Encoder_countB=0;
					carL_dis=0,carR_dis=0;
					//PID_init(&PID_Link,0,70,0,200,1000,-1000);   //循迹PID初始化
					RunMode++;
					break;
				}
				
				case 4:
				{
					carR_dis = Wheel_count * -Get_Encoder_countB;
					carL_dis = Wheel_count * Get_Encoder_countA;
					if((fabsf(carL_dis) >= dis2) && (fabsf(carR_dis) >= dis2))
					{
						move_flag = 0;
					}
					
					if(move_flag ==1)
					{
							if(imu_read_flag == 1)
							{
								if(quan_num == 0)
									imu_err = Yaw_error(-134,Yaw);//
								else
								{
									imu_err = Yaw_error(-134,Yaw);//
									dis1 = 950;
								}
							}
							
							//printf("Yaw:%f,Yawerr:%f\r\n",Yaw,imu_err);
							
							deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.5); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation ;
										
										
							if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
								 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
							 else if(PWMR < 0)
									PWMR=0;
							//printf("Yaw_err:%f",Yaw_err);
							//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
							Set_PWM(PWML,PWMR);
					}
					else
					{
							Set_PWM(0,0);
							TrackFlag=0;
							RunMode++;
					}	
					break;
				}
				
				case 5:
				{
					if(TrackFlag==0)	//1开启循迹功能,0关闭
					{	
						imu_err = Yaw_error(-180,Yaw);
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.5); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
						
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
					 else if(PWML < 0)
								PWML=0;
							 
					 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
					 else if(PWMR < 0)
							 PWMR=0;
						Set_PWM(PWML,PWMR);
					 
						sensor_read();	 
						for(int i=0;i<8;i++)
						{
							if((sensor_arr[i] == 0))
							{
									TrackFlag = 1;
									time_flag = 1;
							}
						}
				 }
					
					if(TrackFlag==1)	//1开启循迹功能,0关闭
					{				
						if(read_flag == 1)
						{
							sensor_read();
							track_err = track_error();         //获取循迹的偏差  
						}
						
						
						if(track_err < 30000)
						{
							deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
							PWML = PWML_Base - deviation;
							PWMR = PWMR_Base + deviation;
							
							
							 if(PWML > PWML_MAX)
									PWML = PWML_MAX;
							 else if(PWML < 0)
									PWML=0;
							 
							 if(PWMR > PWMR_MAX)
									PWMR = PWMR_MAX;
								else if(PWMR < 0)
									PWMR=0;
							//printf("track_err:%f",track_err);
							//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
							Set_PWM(PWML,PWMR);
						}
						else
						{
							if(Task_Flag == 3)
							{
									Set_PWM(0,0);
									TrackFlag = 2;			
									move_flag=1;
									time_flag = 1;
									Task_Flag = 0;
									readKey_flag = 1;
							}
							if(Task_Flag == 4)
							{
									TrackFlag = 2;			
									move_flag=1;
									time_flag = 1;
									quan_num++;
									RunMode=0;
									if(quan_num >= 4)
									{
										quan_num = 0;
										Set_PWM(0,0);
										Task_Flag = 0;
										readKey_flag = 1;
									}
									
							}
						}
					}
					break;
				}
			}	
		}	
		
		

		 if(0)
		 {
		 switch(RunMode)
		 {
			 //要求1
			case 0:
				readKey_flag = 1;
				
				break;
			case 1:
				carR_dis = Wheel_count * -Get_Encoder_countB;
				carL_dis = Wheel_count * Get_Encoder_countA;
				if((fabsf(carL_dis) >= distance) && (fabsf(carR_dis) >= distance))
				{
					move_flag = 0;
				}
				
				if(move_flag ==1)
				{
					 if(imu_read_flag == 1)
						{
							imu_err = Yaw_error(0,Yaw);//
						}
						
						//printf("Yaw:%f,Yawerr:%f\r\n",Yaw,imu_err);
						
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/1.8); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
									
									
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
							 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
						 else if(PWMR < 0)
								PWMR=0;
						//printf("Yaw_err:%f",Yaw_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
				}
				else
				{
						Set_PWM(0,0);
						TrackFlag=1;
						time_flag = 1;
						RunMode++;
				}	
				break;
	
			case 2:
				Get_Encoder_countA=0;
				Get_Encoder_countB=0;
				carL_dis=0;
				carR_dis=0;
				move_flag =1;
				readKey_flag = 1;
				
				//RunMode++;
				//Set_PWM(1000,1000);
				//printf("%d  %d\n\r",encoderA_cnt,encoderB_cnt);
			break;		
			//要求1
			case 3:
				//	Serial_JY61P_Zero_Yaw();
				//	delay_ms(1000);
					//Serial_JY61P_Zero_Yaw();
					//delay_ms(3000);
					RunMode++;
				
				break;
			
			//要求2
			case 4:
				carR_dis = Wheel_count * -Get_Encoder_countB;
				carL_dis = Wheel_count * Get_Encoder_countA;
				if((fabsf(carL_dis) >= distance) && (fabsf(carR_dis) >= distance))
				{
					move_flag = 0;
				}
				
				if(move_flag ==1)
				{
					 if(imu_read_flag == 1)
						{
							imu_err = Yaw_error(0,Yaw);//
						}
						
						//printf("Yaw:%f,Yawerr:%f\r\n",Yaw,imu_err);
						
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/1.8); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
						
						
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
							 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
						 else if(PWMR < 0)
								PWMR=0;
						//printf("Yaw_err:%f",Yaw_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
				}
				else
				{
						Set_PWM(0,0);
						TrackFlag=1;
						time_flag = 1;
						RunMode++;
				}	
				break;
				
			case 5:
				if(TrackFlag==1)	//1开启循迹功能,0关闭
				{				
					if(read_flag == 1)
					{
						sensor_read();
						track_err = track_error();         //获取循迹的偏差  
					}
					
					
					if(track_err < 30000)
					{
						deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation;
						
						
						 if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
						 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
							else if(PWMR < 0)
								PWMR=0;
						//printf("track_err:%f",track_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
					}
					else
					{
						Set_PWM(0,0);
						//TrackFlag = 0;
						
						move_flag=1;
						time_flag = 1;
						
						RunMode++;
						//PID_init(&PID_Link,0,70,0,400,800,-800);   //循迹PID初始化
					}
				}
				else
				{
						Set_PWM(0,0);
				}		
				break;	
			case 6:
				//Get_Encoder_countA=0;
				//Get_Encoder_countB=0;
				//carL_dis=0,carR_dis=0;
				Get_Encoder_countA=0;
				Get_Encoder_countB=0;
				carL_dis=0,carR_dis=0;
				RunMode++;
				break;
			
			case 7:
				carR_dis = Wheel_count * -Get_Encoder_countB;
				carL_dis = Wheel_count * Get_Encoder_countA;
				if((fabsf(carL_dis) >= distance) && (fabsf(carR_dis) >= distance))
				{
					//move_flag = 0;
				}
				
				sensor_read();
				for(int i=0;i<8;i++)
				{
					if(sensor_arr[i] == 0)
					{
							move_flag = 0;
					}
				}
				
				if(move_flag ==1)
				{
					 if(imu_read_flag == 1)
						{
							imu_err = -Yaw_error(-178,Yaw);//
						}
						//printf("Yaw:%f,Yawerr:%d\r\n",Yaw,Yaw_err);
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/2.8); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
									
									
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
							 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
						 else if(PWMR < 0)
								PWMR=0;
						//printf("Yaw_err2:%f",Yaw_err2);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWMR,PWML);
				}
				else
				{	
					
						Set_PWM(0,0);
						TrackFlag=1;
						time_flag = 1;
						RunMode++;
				}	
				
				break;
			case 8:
				if(TrackFlag==1)	//1开启循迹功能,0关闭
				{				
					if(read_flag == 1)
					{
						sensor_read();
						track_err = track_error();         //获取循迹的偏差  
					}
					
					
					if(track_err < 30000)
					{
						deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation;
						
						
						 if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
						 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
							else if(PWMR < 0)
								PWMR=0;
						//printf("track_err:%f",track_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
					}
					else
					{
						Set_PWM(0,0);
						TrackFlag = 0;
						
						move_flag=1;
						time_flag = 1;
						RunMode++;
					}
				}
				else
				{
						Set_PWM(0,0);
				}		
				break;
			//要求2
				
				
			case 9:
				PID_init(&PID_Link,0,70,0,200,1000,-1000);   //循迹PID初始化
			
			
				readKey_flag = 1;
				
				break;
			
			case 10:
				

				RunMode++;
				Get_Encoder_countA=0;
				Get_Encoder_countB=0;
				carL_dis=0,carR_dis=0;
				break;
			
				
			//要求3 
			case 11:
				carR_dis = Wheel_count * -Get_Encoder_countB;
				carL_dis = Wheel_count * Get_Encoder_countA;
				if((fabsf(carL_dis) >= dis1) && (fabsf(carR_dis) >= dis1))
				{
					move_flag = 0;
				}
				/*
				sensor_read();
				for(int i=0;i<8;i++)
				{
					if(sensor_arr[i] == 0 )
					{
							//move_flag = 0;
					}
				}
				if(sensor_arr[0] == 0 )
					{
							move_flag = 0;
					}
				*/
				
				if(move_flag ==1)
				{
					  if(imu_read_flag == 1)
						{
							if(quan_num == 0)
								
								imu_err = Yaw_error(-53,Yaw);//
							else
							{
								dis1 = 930;
								imu_err = Yaw_error(-53,Yaw);//
							}
						}
						
						//printf("Yaw:%f,Yawerr:%f\r\n",Yaw,imu_err);
						
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/2.9); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
									
									
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
							 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
						 else if(PWMR < 0)
								PWMR=0;
						//printf("Yaw_err:%f",Yaw_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
				}
				else
				{
						Set_PWM(0,0);
						TrackFlag=0;
					
						RunMode++;
					
				}	
				break;
				
				
				
			case 12:
				if(TrackFlag==0)	//1开启循迹功能,0关闭
				{	
					imu_err = Yaw_error(0,Yaw);
					deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.2); //获取PID的计算结果
					PWML = PWML_Base - deviation;
					PWMR = PWMR_Base + deviation ;
					
					if(PWML > PWML_MAX)
							PWML = PWML_MAX;
				 else if(PWML < 0)
							PWML=0;
						 
				 if(PWMR > PWMR_MAX)
							PWMR = PWMR_MAX;
				 else if(PWMR < 0)
						 PWMR=0;
					Set_PWM(PWML,PWMR);
				 
				 	sensor_read();	 
					for(int i=0;i<8;i++)
					{
						if((sensor_arr[i] == 0))
						{
								TrackFlag = 1;
								time_flag = 1;
						}
					}
			 }
				
				if(TrackFlag==1)	//1开启循迹功能,0关闭
				{				
					if(read_flag == 1)
					{
						sensor_read();
						track_err = track_error();         //获取循迹的偏差  
					}
					
					
					if(track_err < 30000)
					{
						deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation;
						
						
						 if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
						 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
							else if(PWMR < 0)
								PWMR=0;
						//printf("track_err:%f",track_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
					}
					else
					{
						Set_PWM(0,0);
						TrackFlag = 0;
						Get_Encoder_countA=0;
						Get_Encoder_countB=0;
						carL_dis=0,carR_dis=0;
						move_flag=1;
						time_flag = 1;
						PID_init(&PID_Link,0,70,0,200,1000,-1000);   //循迹PID初始化
						RunMode++;
					}
				}
				
				break;	
				
			case 13:
				carR_dis = Wheel_count * -Get_Encoder_countB;
				carL_dis = Wheel_count * Get_Encoder_countA;
				if((fabsf(carL_dis) >= dis2) && (fabsf(carR_dis) >= dis2))
				{
					move_flag = 0;
				}
				/*
				sensor_read();
				for(int i=0;i<8;i++)
				{
					if(sensor_arr[i] == 0 )
					{
							//move_flag = 0;
					}
				}
				if(sensor_arr[0] == 0 )
					{
							move_flag = 0;
					}
				*/
				
				if(move_flag ==1)
				{
					  if(imu_read_flag == 1)
						{
							if(quan_num == 0)
								imu_err = Yaw_error(-134,Yaw);//
							else
							{
								imu_err = Yaw_error(-134,Yaw);//
								dis1 = 960;
							}
						}
						
						//printf("Yaw:%f,Yawerr:%f\r\n",Yaw,imu_err);
						
						deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.5); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation ;
									
									
						if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
							 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
						 else if(PWMR < 0)
								PWMR=0;
						//printf("Yaw_err:%f",Yaw_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
				}
				else
				{
						Set_PWM(0,0);
						TrackFlag=0;
					
						RunMode++;

				}	
				break;
			case 14:
				if(TrackFlag==0)	//1开启循迹功能,0关闭
				{	
					imu_err = Yaw_error(-180,Yaw);
					deviation = (int32_t)PID_realize(&PID_Link,imu_err/3.5); //获取PID的计算结果
					PWML = PWML_Base - deviation;
					PWMR = PWMR_Base + deviation ;
					
					if(PWML > PWML_MAX)
							PWML = PWML_MAX;
				 else if(PWML < 0)
							PWML=0;
						 
				 if(PWMR > PWMR_MAX)
							PWMR = PWMR_MAX;
				 else if(PWMR < 0)
						 PWMR=0;
					Set_PWM(PWML,PWMR);
				 
				 	sensor_read();	 
					for(int i=0;i<8;i++)
					{
						if((sensor_arr[i] == 0))
						{
								TrackFlag = 1;
								time_flag = 1;
						}
					}
			 }
				
				if(TrackFlag==1)	//1开启循迹功能,0关闭
				{				
					if(read_flag == 1)
					{
						sensor_read();
						track_err = track_error();         //获取循迹的偏差  
					}
					
					
					if(track_err < 30000)
					{
						deviation = (int32_t)PID_realize(&PID_Link,track_err); //获取PID的计算结果
						PWML = PWML_Base - deviation;
						PWMR = PWMR_Base + deviation;
						
						
						 if(PWML > PWML_MAX)
								PWML = PWML_MAX;
						 else if(PWML < 0)
								PWML=0;
						 
						 if(PWMR > PWMR_MAX)
								PWMR = PWMR_MAX;
							else if(PWMR < 0)
								PWMR=0;
						//printf("track_err:%f",track_err);
						//printf("PWML:%d,PWMR:%d\r\n",PWML,PWMR);
						Set_PWM(PWML,PWMR);
					}
					else
					{
						Set_PWM(0,0);
						TrackFlag = 0;
						Get_Encoder_countA=0;
						Get_Encoder_countB=0;
						carL_dis=0,carR_dis=0;
						move_flag=1;
						time_flag = 1;
						
						
						RunMode++;
						if(Q4_flag == 1)
						{
							quan_num++;
							if(quan_num < 4)
							{
								
									RunMode=10;
							}
							else
							{
								quan_num=0;
								Q4_flag=0;
								 RunMode=0;
							}
							
						}
					}
				}
				
				break;	
			/*第三问*/
			
			/*第四*/
			case 15:
				
				readKey_flag = 1;
			break;
				
			case 16:
				RunMode = 10;
				Q4_flag = 1;
				
				//Set_PWM(1000,1000);
				//printf("%d  %d\n\r",encoderA_cnt,encoderB_cnt);
				break;	
			case 17:
				
				
				break;
		}
  }	
	}
}


void TIMER_0_INST_IRQHandler(void)
{
	if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
	{
		if(DL_TIMER_IIDX_ZERO)
		{
				encoderA_cnt = Get_Encoder_countA;//两个电机安装相反，所以编码器值也要相反
			  encoderB_cnt = -Get_Encoder_countB;
				
				if(DL_GPIO_readPins(KEY2_PORT,KEY2_PIN_2_PIN )==0) //确定任务
				{
						key2_count++;
						if(key2_count >= 4)
						{
								key2_count = 0;	
								if(DL_GPIO_readPins(KEY2_PORT,KEY2_PIN_2_PIN )==0 && readKey_flag == 1)
								{
									while(DL_GPIO_readPins(KEY2_PORT,KEY2_PIN_2_PIN)==0);
									//DL_GPIO_togglePins(LED1_PORT,LED1_PIN_0_PIN);
								  if(Task_Num == 1)
										Task_Flag = 1;
									if(Task_Num == 2)
										Task_Flag = 2;
									if(Task_Num == 3)
										Task_Flag = 3;
									if(Task_Num == 4)
										Task_Flag = 4;
									
									
								}
						}
					
				}
				
				if(DL_GPIO_readPins(KEY_PORT,KEY_PIN_21_PIN )==0) //选任务
				{
						key_count++;
						if(key_count >= 4)
						{
								key_count = 0;
								
								if(DL_GPIO_readPins(KEY_PORT,KEY_PIN_21_PIN )==0 )
								{
									
									while(DL_GPIO_readPins(KEY_PORT,KEY_PIN_21_PIN)==0);
									//DL_GPIO_togglePins(LED1_PORT,LED1_PIN_0_PIN);
									Task_Num ++;
									if(Task_Num >4)
									{
										Task_Num = 1;
									}
									sprintf(number,"%d",Task_Num);
								}
						}		
				}
				//carR_dis = Wheel_count * -Get_Encoder_countB;
				//carL_dis = Wheel_count * Get_Encoder_countA;
				
				if(time_flag == 1)
				{		
						time_count++;
						DL_GPIO_setPins(GPIOB, RGB_Red_PIN_26_PIN);// RGB红灯 1亮
						DL_GPIO_clearPins(LED1_PORT,LED1_PIN_0_PIN); // 绿灯 1灭
						DL_GPIO_setPins(GPIOA, BEEF_PIN_27_PIN );//BEEF 1响
						if(time_count >= 15) //50*
						{
								time_count=0;
								time_flag = 0;
								DL_GPIO_setPins(LED1_PORT,LED1_PIN_0_PIN); // 绿灯 1灭
								DL_GPIO_clearPins(GPIOB, RGB_Red_PIN_26_PIN);// RGB红灯 1亮
								DL_GPIO_clearPins(GPIOA, BEEF_PIN_27_PIN );//BEEF 1响
		
						}
				}
		}
		       
	}
}





