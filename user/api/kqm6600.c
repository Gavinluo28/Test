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
//����2����  
//TX--PA2--����-�������������  RX---- PA3 ����--��������   APB2
void uart2_config(void)
{
	//��ʼ��GPIO��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PA9 --�����������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PA10 --��������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//��ʼ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//����USART1ʱ��
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=9600;//������115200
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//ȫ˫��
	USART_InitStruct.USART_Parity= USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//һ��ֹͣλ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8λ���ݳ���
	USART_Init(USART2 ,&USART_InitStruct);//��ʼ������
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//ʹ�ܴ��ڿ����ж�
	//�����ж����ȼ�
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART2,ENABLE);//ʹ�ܴ���
}

uint8_t recivebuf2[10]={0};//�������ݻ�����
uint8_t recivecnt2=0;//�������ݸ���
uint8_t reciveflag2=0;//������ɱ�־λ
void USART2_IRQHandler()
{
	uint8_t data=0;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=0)
	{
//		data = USART_ReceiveData(USART2);
//		USART_SendData(USART1,data);
	  recivebuf2[recivecnt2++]=USART_ReceiveData(USART2);//��������
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
		USART2->DR;//������б�־λ
	}
}


//�����������麯��
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
				printf("�׵�ַ����\r\n");
			}
		}
		else
		{
			memset(recivebuf2,0,10);
			recivecnt2=0;
//			printf("������8\r\n");
		}
	reciveflag2=0;
}

