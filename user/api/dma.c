#include "dma.h"
uint16_t adc_value[2]={0};
void dma_config(void)
{
	//DMA ---- AHB����   DMA1_CH1 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);//ʹ��DMAʱ��
	DMA_InitTypeDef DMA_InitStruct={0};
	DMA_InitStruct.DMA_BufferSize=2;//��������С
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;//������������Դ
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;//�������ڴ浽�ڴ�
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)adc_value;//���ô洢����ַ
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;//����
	DMA_InitStruct.DMA_MemoryInc= DMA_MemoryInc_Enable;//����
	DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;//ѭ��ģʽ
	DMA_InitStruct.DMA_Priority= DMA_Priority_Medium;//�����ȼ�
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;//������
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&(ADC1->DR);//������������Դ��ַ
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);//��ʼ��DMA
  DMA_Cmd(DMA1_Channel1,ENABLE);//ʹ��DMA
}