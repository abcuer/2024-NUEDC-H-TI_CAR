#include "headfile.h"

/*   ����ͨѶ����
void test(void)
{
    if(hc05_flag)
    {
        switch(hc05_data)
        {
            case '1': LED_Blue_ON(); break;
            case '2': LED_Blue_OFF(); break;
            case '3': LED_Green_ON(); break;
            case '4': LED_Green_OFF(); break;
        }
        uart0_send_char(hc05_data);  // ���ڷ���Ҳ��������ѭ�������
        hc05_flag = 0;
    }
}
*/
/*   PID��ʱ��ѡ���Բ���
void test(void)
{
	printf("%.2f, %.2f, %.2f\r\n", speedA, speedB, Yaw);
	speed_tar = 30;
	pid_flag = SPEED_PID;
}
*/
void test(void)
{
	OLED_ShowString(0,0,(uint8_t *)"ABC",8,1);//6*8 ��ABC��
	OLED_ShowString(0,8,(uint8_t *)"ABC",12,1);//6*12 ��ABC��
	OLED_ShowString(0,20,(uint8_t *)"ABC",16,1);//8*16 ��ABC��
	OLED_ShowString(0,36,(uint8_t *)"I LOVE YOU",24,1);//12*24 ��ABC��
	OLED_Refresh();
	delay_ms(20);
}