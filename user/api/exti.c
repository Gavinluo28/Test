#include "exti.h"
#include "led.h"
//�ⲿ�ж����ú���  PA0  PC4---EXTI4--   PC5 ---ETXI5--EXTI9-5     PC6---EXTI6----EXTI9-5
void exti0_config(void)
{
	//PA0  �ⲿ�ж�  PC4  PC5  PC6
	RCC->APB2ENR |= (1<<0);//��������ʱ��
	AFIO->EXTICR[0] &= ~(0Xf<<0);//����PA0Ϊ�ⲿ�ж�
	AFIO->EXTICR[1] &= ~(0Xfff<<0);
	AFIO->EXTICR[1] |= (0X222<<0);
  EXTI->IMR |= (1<<0);//�����ж���0����
	EXTI->IMR |= (7<<4);//�����ж���4  5  6����
	EXTI->RTSR |= (1<<0);//���������ش���
	EXTI->FTSR |= (7<<4);//�����½��ش���
	EXTI->FTSR &= ~(1<<0);//�ر������ش���
	EXTI->PR |= (1<<0);//�������λ
	EXTI->PR |= (7<<4);//�������λ
	//�����ж����ȼ�
	NVIC_SetPriority(EXTI0_IRQn,0);//��ռ0   �μ�0
	NVIC_SetPriority(EXTI4_IRQn,1);//��ռ0   �μ�0
	NVIC_SetPriority(EXTI9_5_IRQn,2);//��ռ0   �μ�0
	NVIC_EnableIRQ(EXTI0_IRQn);//ʹ���ж�
	NVIC_EnableIRQ(EXTI4_IRQn);//ʹ���ж�
	NVIC_EnableIRQ(EXTI9_5_IRQn);//ʹ���ж�
}
void exti0_configlib(void)
{
	//PA0  �ⲿ�ж�  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//��������ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);//PA0   --�ж���0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);//PC4   --�ж���1
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);//PC5   --�ж���2
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);//PC6   --�ж���3
	//�ⲿ�ж�����
	EXTI_InitTypeDef   EXTI_InitStruct={0};//����һ���ṹ�����
	EXTI_InitStruct.EXTI_Line = EXTI_Line0 |EXTI_Line4|EXTI_Line5|EXTI_Line6;//�ж���0
	EXTI_InitStruct.EXTI_LineCmd= ENABLE;//ʹ���ж���
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽ
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;//������
	EXTI_Init(&EXTI_InitStruct);//��ʼ���ṹ��
	//�ж����ȼ�
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;//ʹ������
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0;//��ռ0 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;//   �μ�0
	NVIC_Init(&NVIC_InitStruct);//��ʼ���ṹ��

	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0;//��ռ0 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//   �μ�0
	NVIC_Init(&NVIC_InitStruct);//��ʼ���ṹ��

	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 0;//��ռ0 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;//   �μ�0
	NVIC_Init(&NVIC_InitStruct);//��ʼ���ṹ��
}


void EXTI0_IRQHandler()
{
	if((EXTI->PR & (1<<0))!=0)//�����ж�����
	{
	  EXTI->PR |= (1<<0);//�������λ
		led_on(led1port,led1pin);
	}
}


void EXTI4_IRQHandler()
{
	if((EXTI->PR & (1<<4))!=0)//�����ж�����
	{
	  EXTI->PR |= (1<<4);//�������λ
		led_on(led2port,led2pin);
	}
}
void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5)!=0)//�����ж�����
	{
	  EXTI_ClearITPendingBit(EXTI_Line5);//�������λ
		led_turn(led3port,led3pin);
	}
	
		if(EXTI_GetITStatus(EXTI_Line6)!=0)//�����ж�����
	{
	  EXTI_ClearITPendingBit(EXTI_Line6);//�������λ
		led_turn(led4port,led4pin);
	}
}
