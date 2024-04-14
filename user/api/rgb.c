#include "rgb.h"
void rgb_config()
{
	//PA6 ---B-TIM3-CH1  PA7--G-TIM3-CH2  PA8--R-TIM1-CH1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//����GPIO�ںͶ�ʱ��ʱ��
	//����GPIO��ģʽ 
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//���ö�ʱ������
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct={0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 1000-1;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler =72-1;//Ԥ��Ƶ��ֵ
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct); //��ʼ����ʱ��1  
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //��ʼ����ʱ��3
	
	//����PWM
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����pwmģʽ
	TIM_OCInitStructure.TIM_Pulse  = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//������Ч��ƽΪ�͵�ƽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ�����
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//ʹ�ܶ�ʱ��3��1ͨ��
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);//ʹ�ܶ�ʱ��3��2ͨ��

//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//����pwmģʽ
//	TIM_OCInitStructure.TIM_Pulse  = 0;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//������Ч��ƽΪ�͵�ƽ
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ�����
//	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//ʹ�ܶ�ʱ��3��1ͨ��
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);//ʹ�ܶ�ʱ��1��1ͨ��
  TIM_CtrlPWMOutputs(TIM1,ENABLE);//ʹ�ܶ�ʱ��1�����
	TIM_Cmd(TIM1,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

void setlight(uint16_t r,uint16_t g, uint16_t b)
{
  TIM_SetCompare1(TIM3,b);
	TIM_SetCompare2(TIM3,g);
	TIM_SetCompare1(TIM1,r);
}