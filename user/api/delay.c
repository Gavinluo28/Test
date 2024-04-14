#include  "delay.h"
uint16_t ledtime[2]={0,500};
uint16_t keytime[2]={0,20};
uint16_t cnt=0;
uint16_t dht11time[2]={0,2000};
uint16_t  ADCtime[2]={0,2000};
uint16_t kqm6600time[2]={0,1000};
uint16_t  su_03ttime[2]={0,2000};
uint16_t  esp8266time[2]={0,10000};
uint16_t  RTCtime[2]={0,900};
//系统定时器中断服务函数
//void SysTick_Handler(void)
//{
// ledtime[0]++;
//	keytime[0]++;
//	cnt++;
//	dht11time[0]++;
//	 ADCtime[0]++;
//	kqm6600time[0]++;
//	su_03ttime[0]++;
//	esp8266time[0]++;
//	RTCtime[0]++;
//	
//	
//	
//	
//	
//	
//}
//构造微秒延时函数
void delay_us(uint32_t t)
{
  while(t--)
	{
	  delay_1us();
	}
}


//构造毫秒延时函数
void delay_ms(uint32_t t)
{
	t=t*1000;
  while(t--)
	{
	  delay_1us();
	}
}

//构造微秒延时函数
void Delay_us(uint32_t t)
{
  while(t--)
	{
	  delay_1us();
	}
}


//构造毫秒延时函数
void Delay_ms(uint32_t t)
{
	t=t*1000;
  while(t--)
	{
	  delay_1us();
	}
}


