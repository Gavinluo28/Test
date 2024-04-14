#include "kqm6600.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

extern SemaphoreHandle_t xSemaphore;
BaseType_t xReturn = pdPASS;
float voc;
float ch2o;
int co2;
//串口2驱动  
//TX--PA2--发送-复用推挽输出？  RX---- PA3 接收--浮空输入   APB2
void uart2_config(void)
{
	//初始化GPIO口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PA9 --复用推挽输出
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PA10 --浮空输入
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//初始化串口
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//开启USART1时钟
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=9600;//波特率115200
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//全双工
	USART_InitStruct.USART_Parity= USART_Parity_No;//无校验
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//一个停止位
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8位数据长度
	USART_Init(USART2 ,&USART_InitStruct);//初始化串口
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//使能串口接收中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//使能串口空闲中断
	//设置中断优先级
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART2,ENABLE);//使能串口
}

uint8_t recivebuf2[10]={0};//接收数据缓冲区
uint8_t recivecnt2=0;//接收数据个数
uint8_t reciveflag2=0;//接收完成标志位
void USART2_IRQHandler()
{
	uint8_t data=0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=0)
	{
//		data = USART_ReceiveData(USART2);
//		USART_SendData(USART1,data);
	  recivebuf2[recivecnt2++]=USART_ReceiveData(USART2);//接收数据
		if(recivecnt2>8)
		{
		recivecnt2=0;
		}
	}
	if(USART_GetITStatus(USART2,USART_IT_IDLE)!=0)
	{
	  reciveflag2=1;
		
//		xReturn=xSemaphoreGiveFromISR(xSemaphore,NULL);
		USART2->SR;
		USART2->DR;//清除空闲标志位
	}
}


//分析接收数组函数
void  analysis2(void)
{
		if(recivecnt2==8)
		{
			if(recivebuf2[0]==0x5F)
			{
				if((uint8_t)(recivebuf2[0]+recivebuf2[1]+recivebuf2[2]+recivebuf2[3]+recivebuf2[4]+recivebuf2[5]+recivebuf2[6])==recivebuf2[7])
				{
				 voc=((recivebuf2[1]*256)|recivebuf2[2])*0.1;
					ch2o=((recivebuf2[3]<<8)|recivebuf2[4])*0.01;
					co2=((recivebuf2[5]<<8)|recivebuf2[6])*1;
					printf("voc:%.1f\r\n",voc);
					printf("ch2o:%.1f\r\n",ch2o);
					printf("co2:%d\r\n",co2);
				}
			}
			else
			{
			 memset(recivebuf2,0,10);
			 recivecnt2=0;
				printf("首地址不对\r\n");
			}
		}
		else
		{
			memset(recivebuf2,0,10);
			recivecnt2=0;
//			printf("不等于8\r\n");
		}
	reciveflag2=0;
}

