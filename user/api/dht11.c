#include "dht11.h"
#include "delay.h"
#include  "stdio.h"
//dth11---PG11 -  单总线数字传感器  -输入--浮空输入  输出--推挽输出
//1   输出模式   0   输入模式
DHT11   dht11;
void dht11_config(uint8_t mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//开启时钟
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	if(mode==1)
	{
	 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;//
	 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	}
	else if(mode==0)
	{
	GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(GPIOG,&GPIO_InitStruct);
}
//起始信号
void start(void)
{
	dht11_config(1);//设置输出模式
	DHT11_L;//主机输出低电平
	delay_ms(20);//延时20ms
}
//响应信号  返回0  正确   返回其它  错误
uint8_t check()
{
	uint8_t cnt=0;
  dht11_config(0);//设置输入模式
	while(DHT11_STATE==1)//等待低电平的到来
	{
		delay_1us();
		cnt++;
		if(cnt>8)
		{
		 return 1;
		}
	}
	cnt=0;//程序执行到这里说明总线处于低电平
	while(DHT11_STATE==0)//等待高电平的到来
	{
		delay_1us();
		cnt++;
		if(cnt>100)
		{
		 return 2;
		}
	}
	return 0;  //响应成功
}
//读取一位数据 
uint8_t readonebit()
{
	uint8_t cnt=0;
	while(DHT11_STATE==1)//等待低电平的到来
	{
		delay_1us();
		cnt++;
		if(cnt>100)
		{
		 return 3;
		}
	}
	cnt=0;
//  printf("55555\r\n");
	while(DHT11_STATE==0)//等待高电平的到来
	{
		delay_1us();
		cnt++;
		if(cnt>60)
		{
		 return 4;
		}
	}
  delay_us(30);//延时30微秒判断电平状态
	if(DHT11_STATE==0)
	{
		return 0;
	}
	else
		return 1;
}

//接收多个字节
uint8_t readonebyte()
{
	uint8_t data=0;
	for(uint8_t i=0;i<8;i++)
	{
	 data<<=1;//左移一位
	 data|=readonebit();
	}
  return data;
}
//获取温湿度
void get_tem_hum(void)
{
	float value[5]={0};
	start();
	if(check()==0)
	{
		for(uint8_t i=0;i<5;i++)
		{
		 value[i]=readonebyte();
		}
		if(value[0]+value[1]+value[2]+value[3]==value[4])
		{
		 dht11.hum=value[0];
		 dht11.tem=value[2]+value[3]/10;
			printf("湿度：%.2f\r\n",dht11.hum);
			printf("温度：%.2f\r\n",dht11.tem);
		}
		else
		{
		 printf("dht11校验失败\r\n");
		}
	}
	else
	{
	 printf("dht11响应失败\r\n");
	}
}
