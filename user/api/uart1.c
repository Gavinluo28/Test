#include "uart1.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
//串口1驱动  
//TX--PA9--发送-复用推挽输出？  RX---- PA10 接收--浮空输入   APB2
void uart_config(void)
{
	//初始化GPIO口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA时钟
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PA9 --复用推挽输出
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PA10 --浮空输入
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//初始化串口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//开启USART1时钟
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=115200;//波特率115200
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用硬件流控制
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//全双工
	USART_InitStruct.USART_Parity= USART_Parity_No;//无校验
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//一个停止位
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8位数据长度
	USART_Init(USART1 ,&USART_InitStruct);//初始化串口
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能串口接收中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//使能串口空闲中断
	//设置中断优先级
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART1,ENABLE);//使能串口
}
//发送单个字节
void uart_sendbyte(uint8_t data)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0)//上一次发送是否完成
	{}
	USART_SendData(USART1,data);
}
//发送多个字节
void uart_sendstr(uint8_t str[],uint8_t len)
{
 for(uint8_t i=0;i<len;i++)
	{
	 uart_sendbyte(str[i]);
	}
}

//接收数据
uint8_t recive_data()//阻塞型的接收
{
 uint8_t data=0;
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==0)
  {}
	data = USART_ReceiveData(USART1);
  return data;
}
uint8_t recivebuf[10]={0};//接收数据缓冲区
uint8_t recivecnt=0;//接收数据个数
uint8_t reciveflag=0;//接收完成标志位
void USART1_IRQHandler()
{
	uint8_t data=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=0)
	{
		data = USART_ReceiveData(USART1);
		USART_SendData(USART3,data);
//	  recivebuf[recivecnt++]=USART_ReceiveData(USART1);//接收数据
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=0)
	{
	  reciveflag=1;
		USART1->SR;
		USART1->DR;//清除空闲标志位
	}
}
//分析接收数组函数
void  analysis(void)
{
	if(reciveflag==1)//判断是否接收完成
	{
		if(recivecnt==5)
		{
			if((recivebuf[0]==0xAA)&&(recivebuf[1]==0x55)&&(recivebuf[3]==0x55)&&(recivebuf[4]==0xAA))
			{
				switch(recivebuf[2])
				{
					case 0: led_on(led1port,led1pin);break;
					case 1: led_off(led1port,led1pin);break;
				  case 2: GPIO_SetBits(GPIOC, GPIO_Pin_0);break;
				  case 3: GPIO_ResetBits(GPIOC, GPIO_Pin_0);break;
				}
			memset(recivebuf,0,10);
			recivecnt=0;
				printf("完成任务\r\n");
			}
			else
			{
			memset(recivebuf,0,10);
			recivecnt=0;
				printf("校验值不对\r\n");
			}
		}
		else
		{
			memset(recivebuf,0,10);
			recivecnt=0;
			printf("不等于5\r\n");
		}
	}
	reciveflag=0;
}
//构造printf函数
int fputc(int ch, FILE *f)
{
//	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//  {}
//   USART_SendData(USART1, (uint8_t) ch);
   uart_sendbyte(ch);
 


  return ch;
}
