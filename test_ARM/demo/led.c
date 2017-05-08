/******************** (C) COPYRIGHT  Դ�ع����� ********************************
 * �ļ���  ��led.c
 * ����    ��LED����������     
 * ����    ��zhuoyingxingyu
 * �Ա�    ��Դ�ع�����http://vcc-gnd.taobao.com/
 * ��̳��ַ������԰��-Ƕ��ʽ������̳http://vcc-gnd.com/
 * �汾����: 2016-01-16
 * Ӳ������: 
 * ���Է�ʽ��J-Link-OB
**********************************************************************************/	

//ͷ�ļ�
#include "led.h"

 /**
  * @file   LED_GPIO_Config
  * @brief  LED����������
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{	
    //����һ��GPIO_InitTypeDef ���͵Ľṹ��
    GPIO_InitTypeDef  GPIO_InitStructure;	
    RCC_APB2PeriphClockCmd(LED1_GPIO_RCC|LED2_GPIO_RCC|LED3_GPIO_RCC,ENABLE);//ʹ��GPIO������ʱ��
    /*D1*/
    GPIO_InitStructure.GPIO_Pin =LED1_GPIO_PIN;//ѡ��Ҫ�õ�GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��������ģʽΪ�������ģʽ						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���������ٶ�Ϊ50MHZ         
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);//���ÿ⺯������ʼ��GPIO
    /*D2*/
    GPIO_InitStructure.GPIO_Pin =LED2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
    /*D4*/
    GPIO_InitStructure.GPIO_Pin =LED3_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 			 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
}

 /**
  * @file   LEDXToggle
  * @brief  LED����ת
  * @param  ledx:1--PC13;2--PB0;1--PB1
  * @retval ��
  */
void LEDXToggle(uint8_t ledx)
{
  if(ledx==1)
  {
    LED1_GPIO_PORT->ODR^=LED1_GPIO_PIN;
  }
  else if(ledx==2)
  {
    LED2_GPIO_PORT->ODR^=LED2_GPIO_PIN;
  }
  else
  {
    LED3_GPIO_PORT->ODR^=LED3_GPIO_PIN;
  }

	
	
	
	
/*******************************delay function****************************/
}
 void Delay_1ms(void)
{
    __IO uint16_t index = 0;
    for(index = 10000;index != 0;index--)
    {
    }
}

void Delay_Nms(__IO uint16_t nCount)
{
    uint16_t i = 0;
    for(i = 0;i<nCount;i++)
    {
        Delay_1ms();
    }
}

