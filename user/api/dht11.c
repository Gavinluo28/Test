#include "dht11.h"
#include "delay.h"
#include  "stdio.h"
//dth11---PG11 -  ���������ִ�����  -����--��������  ���--�������
//1   ���ģʽ   0   ����ģʽ
DHT11   dht11;
void dht11_config(uint8_t mode)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);//����ʱ��
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
//��ʼ�ź�
void start(void)
{
	dht11_config(1);//�������ģʽ
	DHT11_L;//��������͵�ƽ
	delay_ms(20);//��ʱ20ms
}
//��Ӧ�ź�  ����0  ��ȷ   ��������  ����
uint8_t check()
{
	uint8_t cnt=0;
  dht11_config(0);//��������ģʽ
	while(DHT11_STATE==1)//�ȴ��͵�ƽ�ĵ���
	{
		delay_1us();
		cnt++;
		if(cnt>8)
		{
		 return 1;
		}
	}
	cnt=0;//����ִ�е�����˵�����ߴ��ڵ͵�ƽ
	while(DHT11_STATE==0)//�ȴ��ߵ�ƽ�ĵ���
	{
		delay_1us();
		cnt++;
		if(cnt>100)
		{
		 return 2;
		}
	}
	return 0;  //��Ӧ�ɹ�
}
//��ȡһλ���� 
uint8_t readonebit()
{
	uint8_t cnt=0;
	while(DHT11_STATE==1)//�ȴ��͵�ƽ�ĵ���
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
	while(DHT11_STATE==0)//�ȴ��ߵ�ƽ�ĵ���
	{
		delay_1us();
		cnt++;
		if(cnt>60)
		{
		 return 4;
		}
	}
  delay_us(30);//��ʱ30΢���жϵ�ƽ״̬
	if(DHT11_STATE==0)
	{
		return 0;
	}
	else
		return 1;
}

//���ն���ֽ�
uint8_t readonebyte()
{
	uint8_t data=0;
	for(uint8_t i=0;i<8;i++)
	{
	 data<<=1;//����һλ
	 data|=readonebit();
	}
  return data;
}
//��ȡ��ʪ��
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
			printf("ʪ�ȣ�%.2f\r\n",dht11.hum);
			printf("�¶ȣ�%.2f\r\n",dht11.tem);
		}
		else
		{
		 printf("dht11У��ʧ��\r\n");
		}
	}
	else
	{
	 printf("dht11��Ӧʧ��\r\n");
	}
}
