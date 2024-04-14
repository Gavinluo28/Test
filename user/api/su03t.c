#include "uart1.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "dht11.h"
#include "adc.h"
#include "time.h"
////����4���� TX--PC10--����-�������������  RX---- PC11 ����--��������   APB2
extern DHT11  dht11;
extern uint16_t adc_value[2];
extern float voc;
extern float ch2o;
extern int co2;
extern uint16_t smoke;
extern uint16_t light;
extern struct tm  *localtimess;



void uart_config4(void)
{
	//��ʼ��GPIO��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//����GPIOCʱ��
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//PC10 --�����������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//PC11 --��������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//��ʼ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//����USART4ʱ��
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate=9600;//������9600
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
	USART_InitStruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//ȫ˫��
	USART_InitStruct.USART_Parity= USART_Parity_No;//��У��
	USART_InitStruct.USART_StopBits=USART_StopBits_1;//һ��ֹͣλ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//8λ���ݳ���
	USART_Init(UART4 ,&USART_InitStruct);//��ʼ������
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//ʹ�ܴ��ڽ����ж�
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);//ʹ�ܴ��ڿ����ж�
	//�����ж����ȼ�
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=UART4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	USART_Cmd(UART4,ENABLE);//ʹ�ܴ���
}
//���͵����ֽ�
void uart_sendbyte4(uint8_t data)
{
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC)==0)//��һ�η����Ƿ����
	{}
	USART_SendData(UART4,data);
}
//���Ͷ���ֽ�
void uart_sendstr4(uint8_t str[],uint8_t len)
{
 for(uint8_t i=0;i<len;i++)
	{
	 uart_sendbyte4(str[i]);
	}
}


uint8_t recivebuf4[10]={0};//�������ݻ�����
uint8_t recivecnt4=0;//�������ݸ���
uint8_t reciveflag4=0;//������ɱ�־λ
uint8_t sentbuf4[10]={0};//������ɱ�־λ
void UART4_IRQHandler()
{
//	uint8_t data=0;
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=0)
	{
	  recivebuf4[recivecnt4++]=USART_ReceiveData(UART4);//��������
	}
	if(USART_GetITStatus(UART4,USART_IT_IDLE)!=0)
	{
	  reciveflag4=1;
		UART4->SR;
		UART4->DR;//������б�־λ
	}
}

extern float ch2o;

//uint16_t data100=0;
//uint16_t  data101=0;
//(uint16_t) data100=adc_value[0]/256;
//data101=adc_value[0]-data100*256;
//�����������麯��
void  analysis4(void)
{
	if(reciveflag4==1)//�ж��Ƿ�������
	{
		if(recivecnt4==6)
		{
			if((recivebuf4[0]==0xAA)&&(recivebuf4[1]==0x55)&&(recivebuf4[2]==0x00)&&(recivebuf4[4]==0x55)&&(recivebuf4[5]==0xAA))
			{
				switch(recivebuf4[3])
				{
					case 1:led_on(led1port,led1pin);//���¶����ݷ��͸�����ģ��
					break;
					case 2:led_off(led1port,led1pin);//���¶����ݷ��͸�����ģ��
					break;
          case 3:GPIO_SetBits(GPIOC, GPIO_Pin_0);
					break;
					case 4:GPIO_ResetBits(GPIOC, GPIO_Pin_0);
					break;
					case 5: sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x01;
								 sentbuf4[3]=(int)dht11.tem;//�¶�
								 sentbuf4[4]=(int)(dht11.tem*100)%100;
								 sentbuf4[5]=0x55;
								 sentbuf4[6]=0xAA;
					       uart_sendstr4(sentbuf4,7);		
					break;
					case 6:sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x02;
								 sentbuf4[3]=dht11.hum;//湿度
								 sentbuf4[4]=0x55;
								 sentbuf4[5]=0xAA;
					       uart_sendstr4(sentbuf4,6);
								 break;
				  case 7:
 					       sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[3]=0x55;
                 if(ch2o>0.1)
								 {	
									 sentbuf4[2]=0x03;
								 }		
                 else if((ch2o<=0.1)&&((ch2o>=0.01)))	
								 {
									 sentbuf4[2]=0x04;
								 }
                 else if(ch2o<0.01)	
								 {
								  sentbuf4[2]=0x05;
								 }					
                 sentbuf4[3]=0x55;								 
								 sentbuf4[4]=0xAA;
								 uart_sendstr4(sentbuf4,5);	
								 break;	
					case 8:sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x04;
								 sentbuf4[3]=adc_value[0]%256;//光照强度
								 sentbuf4[4]=adc_value[0]/256;
								 sentbuf4[5]=0x00;
								 sentbuf4[6]=0x00;
								 sentbuf4[7]=0x55;
								 sentbuf4[8]=0xAA;
					       uart_sendstr4(sentbuf4,9);
								 break;
				 case 9:sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x05;
								 sentbuf4[3]=adc_value[1];//烟雾浓度
								 sentbuf4[4]=0x55;
								 sentbuf4[5]=0xAA;
					       uart_sendstr4(sentbuf4,6);
								 break;
				 case 10:sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x06;
								 sentbuf4[3]=co2%256;//二氧化碳浓度
								 sentbuf4[3]=co2/256;
								 sentbuf4[5]=0x00;
								 sentbuf4[6]=0x00;
								 sentbuf4[7]=0x55;
								 sentbuf4[8]=0xAA;
					       uart_sendstr4(sentbuf4,9);
				   break;
					 	case 11:sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x07;
								 sentbuf4[3]=voc;//�л���Ũ��
								 sentbuf4[4]=0x55;
								 sentbuf4[5]=0xAA;
					       uart_sendstr4(sentbuf4,6);
								 break;
//					case 11:sentbuf4[0]=0xAA;
//					       sentbuf4[1]=0x55;
//								 sentbuf4[2]=0x02;
//								 sentbuf4[3]=dht11.hum;//48%
//								 sentbuf4[4]=0x55;
//								 sentbuf4[5]=0xAA;
//					       uart_sendstr4(sentbuf4,6);
						case 12:
							sentbuf4[0]=0xAA;
					       sentbuf4[1]=0x55;
								 sentbuf4[2]=0x08;
								 sentbuf4[3]=localtimess->tm_hour;
								 sentbuf4[4]=localtimess->tm_min;
						     sentbuf4[5]=localtimess->tm_sec;
								 sentbuf4[6]=0x55;
								 sentbuf4[7]=0xAA;
					       uart_sendstr4(sentbuf4,8);
							break; 				
			
				}
			memset(recivebuf4,0,10);
			memset(sentbuf4,0,10);
			recivecnt4=0;
				printf("�������\r\n");
			}
			else
			{
			memset(recivebuf4,0,10);
			recivecnt4=0;
			printf("У��ֵ����\r\n");
			}
		}
		else
		{
			memset(recivebuf4,0,10);
			recivecnt4=0;
			printf("������6\r\n");
		}
	}
	reciveflag4=0;
}
