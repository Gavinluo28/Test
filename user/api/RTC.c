#include "RTC.h"
#include "stdio.h"
void NVIC_Configuration(void);
void RTC_Configuration(void);
void Time_Adjust(void);
//����RTC
void rtc_config(void)
{
	/* NVIC configuration */
  //NVIC_Configuration();//�ж�����

  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A1)
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    printf("\r\n\n RTC not yet configured....");

    /* RTC Configuration */
    RTC_Configuration();

    printf("\r\n RTC configured....");

    /* Adjust time by values entered by the user on the hyperterminal */
    Time_Adjust();//����ʱ��

    BKP_WriteBackupRegister(BKP_DR1, 0xA5A1);
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      printf("\r\n\n Power On Reset occurred....");
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      printf("\r\n\n External Reset occurred....");
    }

    printf("\r\n No need to configure RTC....");
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}
}	
/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None   �ж����ȼ�����
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure={0};
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */
void RTC_Configuration(void)
{
  /* Enable PWR and BKP clocks *///ʹ��BKP�͵�Դʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);//ʹ�ܻ���ʧ�� RTC �ͺ󱸼Ĵ�������

  /* Reset Backup Domain */
  BKP_DeInit();//������ BKP ��ȫ���Ĵ�������Ϊȱʡֵ

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);//�����ⲿ���پ���LSE��
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}//�ȴ�LSE �������

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//ѡ��RTCʱ����ԴΪLSE

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);//ʹ��RTCʱ��

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();//�ȴ� RTC �Ĵ���(RTC_CNT, RTC_ALR and RTC_PRL)��RTC �� APB ʱ��ͬ��

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//�ȴ����һ�ζ� RTC �Ĵ�����д�������

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);//ʹ�����ж�

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//�ȴ����һ�ζ� RTC �Ĵ�����д�������

  /* Set RTC prescaler: set RTC period to 1sec   ����Ԥ��Ƶֵ*/
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//�ȴ����һ�ζ� RTC �Ĵ�����д�������
}

/**
  * @brief  Adjusts time.//����ʱ��
  * @param  None
  * @retval None
  */
void Time_Adjust(void)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//�ȴ����һ�ζ� RTC �Ĵ�����д�������
  /* Change the current time */
  RTC_SetCounter(0);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();//�ȴ����һ�ζ� RTC �Ĵ�����д�������
}

