#include "led.h"
void led_config(void)
{
	//����led1 ��    PE2 ����͵�ƽ
  // PE2  GPIOE  ���  ��ͨ  ����
	RCC->APB2ENR |= (1<<6);//����GPIOE��ʱ��
	GPIOE->CRL &= ~(0XFFFF<<8);//��8-23  ��Ӧλ����
	GPIOE->CRL |=(0X3333<<8); //��8-21 ���0x03//�������
  //GPIOE->ODR &= ~(0XF<<2);//PE2����͵�ƽ
	GPIOE->ODR |= (0XF<<2);//PE2����ߵ�ƽ

}

void led_configlib(void)
{
// //����ʱ��  GPIOE   
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//
//	GPIO_InitTypeDef GPIO_InitStructure = {0};//����һ���ṹ�����
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��ͨ�������
//	GPIO_Init(GPIOE, &GPIO_InitStructure);//
//	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_4 |GPIO_Pin_5);
	GPIO_ResetBits(GPIOC, GPIO_Pin_0);
}
//����
void led_on(GPIO_TypeDef *ledport,uint16_t ledpin)
{
   ledport->ODR &= ~(ledpin);
}

//���
void led_off(GPIO_TypeDef *ledport,uint16_t ledpin)
{
   ledport->ODR |= (ledpin);
}

//��ת
void led_turn(GPIO_TypeDef *ledport,uint16_t ledpin)
{
   ledport->ODR ^= (ledpin);
}
