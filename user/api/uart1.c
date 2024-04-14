#include "uart1.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
//����1����  
//TX--PA9--����-�������������  RX---- PA10 ����--��������   APB2
void uart_config(void)
{
	//��ʼ��GPIO��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOAʱ��
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PA9 --�����������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PA10 --��������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//��ʼ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//����USART1ʱ��
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=115200;//������115200
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//ȫ˫��
	USART_InitStruct.USART_Parity= USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//һ��ֹͣλ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8λ���ݳ���
	USART_Init(USART1 ,&USART_InitStruct);//��ʼ������
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//ʹ�ܴ��ڿ����ж�
	//�����ж����ȼ�
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
}
//���͵����ֽ�
void uart_sendbyte(uint8_t data)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0)//��һ�η����Ƿ����
	{}
	USART_SendData(USART1,data);
}
//���Ͷ���ֽ�
void uart_sendstr(uint8_t str[],uint8_t len)
{
 for(uint8_t i=0;i<len;i++)
	{
	 uart_sendbyte(str[i]);
	}
}

//��������
uint8_t recive_data()//�����͵Ľ���
{
 uint8_t data=0;
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==0)
  {}
	data = USART_ReceiveData(USART1);
  return data;
}
uint8_t recivebuf[10]={0};//�������ݻ�����
uint8_t recivecnt=0;//�������ݸ���
uint8_t reciveflag=0;//������ɱ�־λ
void USART1_IRQHandler()
{
	uint8_t data=0;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=0)
	{
		data = USART_ReceiveData(USART1);
		USART_SendData(USART3,data);
//	  recivebuf[recivecnt++]=USART_ReceiveData(USART1);//��������
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=0)
	{
	  reciveflag=1;
		USART1->SR;
		USART1->DR;//������б�־λ
	}
}
//�����������麯��
void  analysis(void)
{
	if(reciveflag==1)//�ж��Ƿ�������
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
				printf("�������\r\n");
			}
			else
			{
			memset(recivebuf,0,10);
			recivecnt=0;
				printf("У��ֵ����\r\n");
			}
		}
		else
		{
			memset(recivebuf,0,10);
			recivecnt=0;
			printf("������5\r\n");
		}
	}
	reciveflag=0;
}
//����printf����
int fputc(int ch, FILE *f)
{
//	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//  {}
//   USART_SendData(USART1, (uint8_t) ch);
   uart_sendbyte(ch);
 


  return ch;
}
