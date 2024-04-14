#include "adc.h"
#include "stdio.h"
#include "dma.h"
extern uint16_t adc_value[2];
void adc_config()
{
	//���� ---PA5 --ADC12_CH5   ����---PC1---ADC1_CH11
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 |RCC_APB2Periph_GPIOC,ENABLE);//����GPIO�ں�ADC1ʱ��
	//����GPIO��ģʽ 
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//ģ������ģʽ
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_5;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;//ģ������ģʽ
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_1;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//����ADC 
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);//6��Ƶ   12MHZ
	
	ADC_InitTypeDef ADC_InitStructure={0};
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //ɨ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;//��ʹ���ⲿת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 2;//һ��ͨ��
	ADC_Init(ADC1, &ADC_InitStructure);//��ʼ��ADC1
	ADC_Cmd(ADC1,ENABLE);//ʹ��ADC1
	dma_config();
	ADC_DMACmd(ADC1, ENABLE);//����ADC1��DMA��������
	//��λ��У��
	ADC_TempSensorVrefintCmd(ENABLE);//�����ڲ��¶ȼ��
	ADC_ResetCalibration(ADC1);//����ADCУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1)==1);//�ȴ��������
	ADC_StartCalibration(ADC1);//��ʼУ׼
	while(ADC_GetCalibrationStatus(ADC1)==1);//�ȴ��������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1,ADC_SampleTime_1Cycles5);//����ADC ͨ��  ��������  ����ʱ��
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2,ADC_SampleTime_1Cycles5);//����ADC ͨ��  ��������  ����ʱ��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//�������ת������
} 

void get_smoke_light()
{
  uint16_t smoke =0;
	uint16_t light =0;
	light =adc_value[0];
	smoke =adc_value[1];
	printf("����adcֵ:%d\r\n",light);
  printf("����adcֵ:%d\r\n",smoke);
}