/**
  ******************************************************************************
  * @file    peripheral.c
  * @author  ��֮��
  * @date    2018��5��16��
  * @brief   ������������ö��ڴ��ļ���
  ******************************************************************************
  * @attention
  *    ע������:
  *
  *
  *
  *                COPYRIGHT 2018 ��֮���������豸�з�����
  ******************************************************************************
  */

#include "peripheral.h"
#include "user.h"




/************************************************
*������ :       LED_Config

*�������� :      ��

*��������ֵ :     ��

*������������ :

*ע�� :    DS0 -- LED0 -- PB5 ; DS1 -- LED1 -- PE5
*************************************************/
void LED_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�����ǵ͵�ƽ
    GPIO_Init(GPIOE, &GPIO_InitStructure); //��ʼ�����ǵ͵�ƽ

    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);
}


/************************************************
*������ :       MotorAndLimitConfig

*�������� :      ��

*��������ֵ :     ��

*������������ :   ����̵�������λ������  �̵����͵�ƽ��ͨ


*ע�� :   PB3 he PB4 ��Ҫ��ӳ��
*************************************************/
void MotorAndLimitConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*
          GPIO_Remap_SWJ_JTAGDisable ����JTAG   ST-LINK����
          GPIO_Remap_SWJ_Disable ��ȫ������
          �ο��ֲ� P122
          */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //PB3  PB4 ��Ҫ��ӳ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*�ȹر����� ȡ���Ĵ�����ʼ�������Ӱ��~*/
    GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
    GPIO_SetBits(GPIOD, GPIO_Pin_2);

    /****************************************************************************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/************************************************
*������ :       Key4_IT_Config

*�������� :      ��

*��������ֵ :     ��

*������������ :   ����һ������Ϊ�жϵķ�ʽ ���ѧϰһ���жϴ���  ;
 * ��ʵ�����жϷ�ʽ�İ��������� ��Ϊ������Ե��

*ע�� :
*************************************************/
void Key4_IT_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    EXTI_InitTypeDef  EXTI_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    /*GPIO�����ⲿ�ж�EXTI��ʱ�򣬱��뿪��AFIOʱ�ӣ�������*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //GPIO_Mode_IN_FLOATING;
//   GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; ����ģʽ ������������

    GPIO_Init(GPIOC, &GPIO_InitStructure);


    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3); //��PC3�����ⲿ�ж�

    EXTI_InitStructure.EXTI_Line = EXTI_Line3; //PC3���ⲿ�ж��ߣ���Ӧ����EXTI3
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_Init(&EXTI_InitStructure);





    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel =
        EXTI3_IRQn; //PC3���ⲿ�ж��ߣ���Ӧ����EXTI3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
        0x00; //��ռ���ȼ�  ����Խ�� ���ȼ�Խ��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =
        0x01; //��Ӧ���ȼ�   ����Խ�� ���ȼ�Խ��

    NVIC_Init(&NVIC_InitStructure);
}


/************************************************
*������ :       USART1_Config

*�������� :      ��

*��������ֵ :     ��

*������������ :   ���ô���1

*************************************************/
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;


    NVIC_InitTypeDef
    NVIC_InitStructure; //�����ô��ڽ����ж��õģ��������Ҫ�����жϣ���ע�ͣ���

    //GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE); //����1 ��Ҫ��ӳ��


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //  USART1_TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���츴�����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /*    PA10 ��RX�ˣ��������ø���������������롣����Ϊ��ʼ�ź��ǵ͵�ƽ���������������ǿ��еģ����� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //  USART1_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /*
     * ����Ϊ���ڵĽṹ���һЩ����������
     * */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //˫��ȫ˫��
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;


    USART_Init(USART1, &USART_InitStructure);




    USART_Cmd(USART1, ENABLE); //ʹ�����裬�漦�ͷѾ� ʹ����ʱ�ӻ�����ʹ������ ����

    /**************************************************************
    ��ע�⡿ ���ˣ����ϵ����þͿ���ȷ���˴���ͨ�ŵ������������������������
    ���͵���Ϣ֮��ľͿ����ˣ�����

    ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^

    ��������������� �����Ҫ���ô��ڵ��жϷ�ʽ������Ҫ�жϽ��գ���ô�����������ã���Ȼ
    �������Ҫ�Ļ���ע�͵��Ϳ����ˣ�����
    **************************************************************/

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //���ڽ����ж�ʹ��

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //û������������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//1λ����������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2λ����������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//3λ����������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4λ����������ռ���ȼ�


    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
        0x01; //��ռ���ȼ�����ֵԽС�����ȼ�Խ�ߡ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =
        0x05; //��Ӧ���ȼ�����ֵԽС�����ȼ�Խ��.
    //��ռ���ȼ��������ж�Ƕ�׵ģ����ߵ����ȼ����Դ�ϵ͵����ȼ��жϡ�����
    //����Ӧ���ȼ�����������ռ���ȼ����ж�ͬ�µ���ʱ�����ȴ�����Ӧ���ȼ��ߵ��жϡ�����
    NVIC_Init(&NVIC_InitStructure);

}


void  USART2_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;


    NVIC_InitTypeDef
    NVIC_InitStructure; //�����ô��ڽ����ж��õģ��������Ҫ�����жϣ���ע�ͣ���

    //GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE); //����1 ��Ҫ��ӳ��


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //  USART2_TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���츴�����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /*    PA3 ��RX�ˣ��������ø���������������롣����Ϊ��ʼ�ź��ǵ͵�ƽ���������������ǿ��еģ����� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //  USART2_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure);


    /*
     * ����Ϊ���ڵĽṹ���һЩ����������
     * */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //˫��ȫ˫��
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;


    USART_Init(USART2, &USART_InitStructure);




    USART_Cmd(USART2, ENABLE); //ʹ�����裬�漦�ͷѾ� ʹ����ʱ�ӻ�����ʹ������ ����

    /**************************************************************
    ��ע�⡿ ���ˣ����ϵ����þͿ���ȷ���˴���ͨ�ŵ������������������������
    ���͵���Ϣ֮��ľͿ����ˣ�����

    ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^

    ��������������� �����Ҫ���ô��ڵ��жϷ�ʽ������Ҫ�жϽ��գ���ô�����������ã���Ȼ
    �������Ҫ�Ļ���ע�͵��Ϳ����ˣ�����
    **************************************************************/

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //���ڽ����ж�ʹ��

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //û������������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//1λ����������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2λ����������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//3λ����������ռ���ȼ�
    //      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4λ����������ռ���ȼ�


    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
        0x01; //��ռ���ȼ�����ֵԽС�����ȼ�Խ�ߡ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =
        0x04; //��Ӧ���ȼ�����ֵԽС�����ȼ�Խ��.
    //��ռ���ȼ��������ж�Ƕ�׵ģ����ߵ����ȼ����Դ�ϵ͵����ȼ��жϡ�����
    //����Ӧ���ȼ�����������ռ���ȼ����ж�ͬ�µ���ʱ�����ȴ�����Ӧ���ȼ��ߵ��жϡ�����
    NVIC_Init(&NVIC_InitStructure);


}

void USART3_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;


    NVIC_InitTypeDef
    NVIC_InitStructure; //�����ô��ڽ����ж��õģ��������Ҫ�����жϣ���ע�ͣ���


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // PB10Ϊ USART3_TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���츴�����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);


    /*    PA10 ��RX�ˣ��������ø���������������롣����Ϊ��ʼ�ź��ǵ͵�ƽ���������������ǿ��еģ����� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // PA10Ϊ USART1_RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOB, &GPIO_InitStructure);


    /*
     * ����Ϊ���ڵĽṹ���һЩ����������
     * */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl =
        USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //˫��ȫ˫��
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;


    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE); //ʹ�����裬�漦�ͷѾ� ʹ����ʱ�ӻ�����ʹ������ ����

    /**************************************************************
    ��ע�⡿ ���ˣ����ϵ����þͿ���ȷ���˴���ͨ�ŵ������������������������
    ���͵���Ϣ֮��ľͿ����ˣ�����

    ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^

    ��������������� �����Ҫ���ô��ڵ��жϷ�ʽ������Ҫ�жϽ��գ���ô�����������ã���Ȼ
    �������Ҫ�Ļ���ע�͵��Ϳ����ˣ�����
    **************************************************************/

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //���ڽ����ж�ʹ��
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//���������ж�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); //û������������ռ���ȼ�
//      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//1λ����������ռ���ȼ�
//      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2λ����������ռ���ȼ�
//      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);//3λ����������ռ���ȼ�
//      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4λ����������ռ���ȼ�


    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =
        0x00; //��ռ���ȼ�����ֵԽС�����ȼ�Խ�ߡ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =
        0x00; //��Ӧ���ȼ�����ֵԽС�����ȼ�Խ��.
    //��ռ���ȼ��������ж�Ƕ�׵ģ����ߵ����ȼ����Դ�ϵ͵����ȼ��жϡ�����
    //����Ӧ���ȼ�����������ռ���ȼ����ж�ͬ�µ���ʱ�����ȴ�����Ӧ���ȼ��ߵ��жϡ�����
    NVIC_Init(&NVIC_InitStructure);
}
/************************************************
*������ :       TIM4_Config

*�������� :      ��

*��������ֵ :     ��

*������������ :   ͨ�ö�ʱ��4�����������ҳ����ܵ�ʱ���׼��2.5ms�ж�һ��

*ע�� :
*************************************************/
void TIM4_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

//     TIM_DeInit (TIM7);//Deinitializes the TIMx peripheral registers to their default reset values.

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitStructure.TIM_Period = 5;
    TIM_TimeBaseInitStructure.TIM_Prescaler =
        35999; //72000000/36000=2000HZ Ҳ����0.5msһ����������

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);


    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;

    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //���һ���Ѿ������ĸ����жϱ�־λ
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //Enables the  TIM4 interrupts
    TIM_Cmd(TIM4, ENABLE); //������ʱ����ʼ��ʱ    ��1����
//       TIM4->CR1 |=0x01;//������ʱ����ʼ��ʱ     ��2����
//       TIM_Cmd(TIM4,DISABLE);//�رն�ʱ����ʱ    ��1����
//       TIM4->CR1 &=~0x01;//�رն�ʱ����ʱ        ��2����
}

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


    GPIO_Init(GPIOB, &GPIO_InitStructure);
}




/************************************************
*������ :       PVD_Init

*�������� :

*��������ֵ :     ��

*������������ :   ���õ������жϺ���

*ע�� :   stm32 �ο��ֲ� P39
*************************************************/
void PVD_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    EXTI_InitTypeDef EXTI_InitStructure;

    NVIC_InitStruct.NVIC_IRQChannel = PVD_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;


    NVIC_Init(&NVIC_InitStruct); //�����ж�

    EXTI_StructInit(&EXTI_InitStructure);
    /*       EXTI_ClearITPendingBit(EXTI_Line16); */
    EXTI_InitStructure.EXTI_Line = EXTI_Line16;  //PVD���ӵ��ж���16��
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger =
        EXTI_Trigger_Rising; //�������ֲ� ���������ǵ��� �½������ϵ�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);


    PWR_PVDLevelConfig(
        PWR_PVDLevel_2V9); //�趨��ط�ֵ   ������� ��2.5���� �Ҹ�Ϊ2.9 �Ϳ�����
    PWR_PVDCmd(ENABLE);
}


void KeyPadConfig(void)
{
    //��������ģʽ  �����������ģʽ
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_12|GPIO_Pin_0|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_SetBits(GPIOA, GPIO_Pin_7 | GPIO_Pin_12|GPIO_Pin_6|GPIO_Pin_8);
	
	
//	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	  GPIO_Init(GPIOF, &GPIO_InitStructure);
//	   
//		GPIO_SetBits(GPIOF, GPIO_Pin_6 | GPIO_Pin_7);
}


void  SendDataBy_USART1(int8_t data)
{
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_SendData(USART1, (int8_t)data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}


void  SendStringBy_USART1(char *data)
{
   while(*data!=0)
	 {
	   SendDataBy_USART1(*data);
	   data++;
	 }
}


