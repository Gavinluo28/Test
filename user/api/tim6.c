#include "tim6.h"
#include "led.h"
void tim6_config(uint16_t Period,uint16_t Prescaler)
{
	//���ö�ʱ��6  APB1  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);//������ʱ��6ʱ��
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = Period-1;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler =Prescaler-1;//Ԥ��Ƶ��ֵ
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStruct); 
	TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);//ʹ�ܶ�ʱ�������ж�
	//�����ж����ȼ�
	NVIC_InitTypeDef  NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel=TIM6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM6, ENABLE);//ʹ�ܶ�ʱ��6
}
//�жϷ�����
void TIM6_IRQHandler()
{
  if(TIM_GetITStatus(TIM6,TIM_IT_Update) == SET)//�ж��Ƿ��������ж�
  {
	 TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		led_turn(led1port,led1pin);
	}
}
