#include "Sensor.h"

uint8_t sensor_arr[8];



void sensor_read()
{
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor1_PIN )==0)
						sensor_arr[0] = 0;
				else
						sensor_arr[0] = 1;
				
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor2_PIN )==0)
						sensor_arr[1] = 0;
				else
						sensor_arr[1] = 1;
				
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor3_PIN )==0)
						sensor_arr[2] = 0;
				else
						sensor_arr[2] = 1;				
			
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor4_PIN )==0)
						sensor_arr[3] = 0;
				else
						sensor_arr[3] = 1;
				
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor5_PIN )==0)
						sensor_arr[4] = 0;
				else
						sensor_arr[4] = 1;		
				
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor6_PIN )==0)
						sensor_arr[5] = 0;
				else
						sensor_arr[5] = 1;		
				
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor7_PIN )==0)
						sensor_arr[6] = 0;
				else
						sensor_arr[6] = 1;
				
				if(DL_GPIO_readPins(Sensor_PORT,Sensor_Sensor8_PIN )==0)
						sensor_arr[7] = 0;
				else
						sensor_arr[7] = 1;
}

int error = 0 ;
int pause_falg = 0;
extern int TrackFlag;
	

float track_error(void)
{	
		//Ö±Ïß¡¢Ô²»¡
		//011 111
	  if(sensor_arr[1]==0&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error =  8;       
		}
		//001 111
	  else if(sensor_arr[1]==0&&sensor_arr[2]==0&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error =  8;       
		}
		//101 111
	  else if(sensor_arr[1]==1&&sensor_arr[2]==0&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error = 6;       
		}
		//100 111
	  else if(sensor_arr[1]==1&&sensor_arr[2]==0&&sensor_arr[3]==0&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error =  4;       
		}	
		//110 111
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==0&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error =  2;       
		}
		
		//110 011
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==0&&sensor_arr[4]==0&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error = 0;       
		}
		
		//111 011
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==0&&sensor_arr[5]==1&&sensor_arr[6]==1)  
    {
         error = -2;       
		}
		//111 001
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==0&&sensor_arr[5]==0&&sensor_arr[6]==1)  
    {
         error = -4;       
		}
		//111 101
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==0&&sensor_arr[6]==1)  
    {
         error = -6;       
		}
		//111 100
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==0&&sensor_arr[6]==0)  
    {
         error = -8;       
		}
		//111 110
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==0)  
    {
         error = -8;       
		}
		
		//111 000
	  else if(sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==0)  
    {
         error = -4;       
		}
		
		//xxxx xxx0
	  else if( sensor_arr[7]==0)  
    {
         error = -8;       
		}
		
		//0xxx xxxx
	  else if(sensor_arr[0]==0)  
    {
         error = 8;       
		}
		
		

			if(sensor_arr[0]==1&&sensor_arr[1]==1&&sensor_arr[2]==1&&sensor_arr[3]==1&&sensor_arr[4]==1&&sensor_arr[5]==1&&sensor_arr[6]==1&&sensor_arr[7]==1) 
			{
					error=30000;
					return error;
				
			}
		
    return error;
}





