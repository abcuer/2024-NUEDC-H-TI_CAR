#include "key.h"
/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：V1.0
修改时间：2024-07-019

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update：2024-07-019

All rights reserved
***********************************************/
uint8_t click(void)
{
	uint8_t key_num=0;
	if(DL_GPIO_readPins(KEY_PORT,KEY_PIN_21_PIN)==0)
	{
		delay_ms(50);
		while(DL_GPIO_readPins(KEY_PORT,KEY_PIN_21_PIN)==0);
		delay_ms(50);
		key_num=1;
	}
	return key_num;
}



