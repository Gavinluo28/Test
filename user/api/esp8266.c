#include "esp8266.h"
#include "uart1.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "delay.h"
#include "MQTT.h"
#include "time.h"
#include <stdlib.h>
#include "dht11.h"
wifi esp8266;
extern time_t lt;
extern DHT11  dht11;
extern uint16_t adc_value[2];
extern float voc;
extern float ch2o;
extern int co2;
extern uint16_t smoke;
extern uint16_t light;


void tonet(void);
//串口3驱动  
//TX--PB10--发送-复用推挽输出？  RX---- PB11 接收--浮空输入   APB1
//PE6  使能引脚    普通推挽输出   初始化置高
void esp8266_config(void)
{
	//初始化GPIO口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE,ENABLE);//开启GPIOB时钟
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PB10 --复用推挽输出
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PB11 --浮空输入
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;;//PE6 --普通推挽输出
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_6);//使能引脚初始化置高
	//初始化串口
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//开启USART1时钟
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=115200;//波特率115200
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//全双工
	USART_InitStruct.USART_Parity= USART_Parity_No;//无校验
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//一个停止位
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8位数据长度
	USART_Init(USART3 ,&USART_InitStruct);//初始化串口
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//使能串口接收中断
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//使能串口空闲中断
	//设置中断优先级
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART3,ENABLE);//使能串口
}
//发送单个字节
void esp8266_sendbyte(uint8_t data)
{
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==0)//上一次发送是否完成
	{};
	USART_SendData(USART3,data);
}
//发送多个字节
void esp8266_sendstr1(uint8_t str[],uint8_t len)
{
 for(uint8_t i=0;i<len;i++)
	{
	 esp8266_sendbyte(str[i]);
	}
}


//发送多个字节
void esp8266_sendstr(uint8_t str[])
{
	uint8_t i=0;
  while(str[i]!='\0')//当发送的字符串数组不等于\0说明当次消息发送完成
	{
	 esp8266_sendbyte(str[i++]);//计数器
	}
	
}


//uint8_t esp8266_recivebuf[10]={0};//接收数据缓冲区
//uint8_t esp8266_recivecnt=0;//接收数据个数
//uint8_t esp8266_reciveflag=0;//接收完成标志位

void USART3_IRQHandler()//中断执行函数，不要自己写，复制粘贴
{
	uint8_t data=0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=0)//接收中断
	{
		data = USART_ReceiveData(USART3);//第三个串口接受数据
		USART_SendData(USART1,data);//发送给串口一
		esp8266.recivebuf[esp8266.recivecnt++]=USART_ReceiveData(USART3);//串口三接收到的数据存放的位置
	}
	if(USART_GetITStatus(USART3,USART_IT_IDLE)!=0)//空闲总线中断，说明中断函数执行完成
	{
	  esp8266.reciveflag=1;//此时标志位为一
		USART3->SR;
		USART3->DR;//清除空闲标志位
	}
}

//1.发送相应的AT指令   2.判断wifi是否正确响应 正常---0   异常--1
uint8_t sendcmdcheck(char * cmd,char * str,uint16_t ms)
{
//	uint8_t data=2;
	memset(esp8266.recivebuf,0,2048);//清空接收缓冲区
	esp8266.recivecnt =0;//清空接收计数器
  esp8266_sendstr((uint8_t *)cmd);//发送at指令
	while(ms--)
	{
	if(esp8266.reciveflag==1)
	{
	 esp8266.reciveflag=0;
		if(strstr((char *)esp8266.recivebuf,str)!=NULL)
		{
		  return 0;//返回数据正常
		}
	}
	delay_ms(1);
  }
  return 1;
}
//void connect(void)
//{
//	if(Sendcmdcheck("AT\r\n","OK",1000)==0)//发送AT过去，收到的字符串如果有OK就说明执行成功
//	{
//		if(Sendcmdcheck("AT+CWMODE=1\r\n","OK",1000)==0)
//		{
//			if(Sendcmdcheck("AT+CWJAP=\"sxlsxl\",\"6081703.\"\r\n","OK",10000)==0)
//			{
//				
//			  if(Sendcmdcheck("AT+CIPSTART=\"TCP\",\"iot-06z00efd6u8q668.mqtt.iothub.aliyuncs.com\",1883\r\n","OK",1000)==0)
//				{
//				  if(Sendcmdcheck("AT+CIPMODE=1\r\n","OK",1000)==0)
//					{
//					 if(Sendcmdcheck("AT+CIPSEND\r\n","OK",1000)==0)
//					 {
//						 if(mqtt_connect()==0)
//							{
//					     printf("连接成功！\r\n");//注意：双引号套双引号被套的前面需要加
//								mqtt_pulish("{\"id\":1689856202433,\"params\":{\"temperature\":56,\"Humidity\":89},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}");
//					    }
//					   
//					 }
//					}		
//				}
//			}
//		}
//  }
//}
void connect(void)
{
//char * buf=NULL;
//sprintf(buf,"{\"id\":1689736975893,\"params\":{\"temperature\":%f,\"Humidity\":%f},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}",dht11.tem,dht11.hum);
if(sendcmdcheck("AT\r\n","OK",1000)==0)
{
	if(sendcmdcheck("AT+CWMODE=1\r\n","OK",1000)==0)
	{
		if(sendcmdcheck("AT+CWJAP=\"sxlsxl\",\"6081703.\"\r\n","OK",10000)==0)
		//if(sendcmdcheck("AT+CWJAP=\"013\",\"syq15981832268\"\r\n","OK",10000)==0)
		{
			if(sendcmdcheck("AT+CIPSTART=\"TCP\",\"iot-06z00efd6u8q668.mqtt.iothub.aliyuncs.com\",1883\r\n","OK",10000)==0)
			{
				if(sendcmdcheck("AT+CIPMODE=1\r\n","OK",1000)==0)
				{
					if(sendcmdcheck("AT+CIPSEND\r\n","OK",1000)==0)
					{

	//						printf("连接成功!\r\n");
						if(mqtt_connect()==0)
							{
									printf("连接成功!\r\n");
//									mqtt_subscribe();
//									return 1;
							}
					}
				}
			}
		}
	
	}
	
}

//return 0;
}

extern time_t lt;
void get_nettime(void)
{

	if(sendcmdcheck("AT\r\n","OK",1000)==0)
	{
		if(sendcmdcheck("AT+CWMODE=1\r\n","OK",1000)==0)
		{
			if(sendcmdcheck("AT+CWJAP=\"sxlsxl\",\"6081703.\"\r\n","OK",10000)==0)
			{
				if(sendcmdcheck("AT+CIPSTART=\"TCP\",\"api.m.taobao.com\",80\r\n","OK",10000)==0)
				{
					if(sendcmdcheck("AT+CIPMODE=1\r\n","OK",1000)==0)
					{
						if(sendcmdcheck("AT+CIPSEND\r\n","OK",1000)==0)
						{
							
							esp8266_sendstr((uint8_t *)"GET http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp\r\n");
							
						}
					}
				}
			}
		}		
	}	
}

void  analysis_nettime(void)
{
	
	if(esp8266.reciveflag==1)//判断是否接收完成
	{
		const char nettime[10]={0};
		char * len=0;
		len=strstr((const char *)esp8266.recivebuf,"\"t\":");
		strncpy((char *)nettime,len+5, 13);
		printf("%s\r\n",nettime);
		lt=(atoll(nettime)/1000+(8*3600));
	}
	esp8266.reciveflag=0;
  	
}


char buf[500]={0};
void tonet(void)
{
	sprintf(buf,"{\"id\":1690969048195,\"params\":{\"temperature\":%.2f,\"Humidity\":%.2f,\"LightLux\":%d,\"co2\":%d,\"HCHO\":%.2f,\"TVOC\":%.2f,\"SmokeSensorState\":%d},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}",dht11.tem,dht11.hum,adc_value[0],co2,ch2o,voc,adc_value[1]);
//		sprintf(buf,"{\"id\":1690969048195,\"params\":{\"temperature\":12,\"Humidity\":13,\"LightLux\":123,\"co2\":123,\"HCHO\":45,\"TVOC\":22,\"SmokeSensorState\":12},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}");

	mqtt_pulish(buf);
	memset(buf,0,500);
}



