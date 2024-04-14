#include "key.h"
#include "delay.h"
//����I/O���ú���
void key_config(void)
{
	//PA0   PC4  5  6   ��������  
	RCC->APB2ENR |= (0x5<<2);//���õڶ�λ  ��4λ��һ
	GPIOA->CRL &= ~(0xF<<0);//����
	GPIOA->CRL |= (0x4<<0);//��������
	
	GPIOC->CRL &= ~(0xFFF<<16);//����
	GPIOC->CRL |= (0x444<<16);//��������
}

void key_configlib(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
}
//��ȡ��������ֵ
uint8_t get_value(void)
{
	uint8_t value=0;
	if((GPIOA->IDR &(1<<0))==1)//��������
	{
		delay_ms(10);
		if((GPIOA->IDR &(1<<0))==1)//��������
		{
	 while((GPIOA->IDR &(1<<0))==1)//�ȴ�����̧��
	 {   
	 }
	 value=1;
	}
  }
	
	if((GPIOC->IDR &(1<<4))==0)//��������
	{
		delay_ms(10);
		if((GPIOC->IDR &(1<<4))==0)//��������
		{
	 while((GPIOC->IDR &(1<<4))==0)//�ȴ�����̧��
	 {   
	 }
	 value=2;
	}
  }
  return value;
}

extern uint16_t cnt;
//��ȡ��������ֵ
uint8_t get_valuelib(void)
{
	uint8_t value=0;

	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)//��������
	{
		delay_ms(10);
		if((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1))//��������
		{
			cnt=0;
	 while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)//�ȴ�����̧��
	 {   
	 }
	 if(cnt>3000)
	 {
	  value=5;//����
	 }
	 else value=1;//�̰�
	}
  }
	
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)==0)//��������
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)==0)//��������
		{
	 while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)==0)//�ȴ�����̧��
	 {   
	 }
	 value=2;
	}
  }
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)==0)//��������
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)==0)//��������
		{
	 while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5)==0)//�ȴ�����̧��
	 {   
	 }
	 value=3;
	}
  }
	if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0)//��������
	{
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0)//��������
		{
	 while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6)==0)//�ȴ�����̧��
	 {   
	 }
	 value=4;
	}
  }
  return value;
}
