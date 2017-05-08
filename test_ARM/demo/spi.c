#include "spi.h"



extern void USR_SPIInit(void)
{
	SPI_RCC_Configuration();
	SPI_GPIO_Configuration();
	USR_SPI_Init();
}


void SPI_RCC_Configuration(void)
{
  /* PCLK2 = HCLK/2 */
  RCC_PCLK2Config(RCC_HCLK_Div2);

  /* Enable peripheral clocks --------------------------------------------------*/
  /* GPIOA, GPIOB and SPI1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_SPI1, ENABLE);

  /* SPI2 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
}


//SPI1:PA5 PA6 PA7  			PA5:SCK PA6:MISO  PA7:MOSI
//SPI2:PB13 PB14 PB15			PB13:SCK PB14:MISO  PB15:MOSI
void SPI_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
  /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Confugure MISO pin as Input Floating  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Configure SPI2 pins: SCK, MISO and MOSI ---------------------------------*/
  /* Confugure SCK and MOSI pins as Input Floating */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  /* Confugure MISO pin as Alternate Function Push Pull */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
}

void USR_SPI_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	SPI_Cmd(SPI1, DISABLE);

  /* SPI1 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
	
	//SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_RXNE);
//	SPI_I2S_ClearFlag(SPI1,SPI_I2S_FLAG_TXE);
	
	//SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_RXNE,ENABLE);
//	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_TXE,ENABLE);
  /* SPI2 configuration ------------------------------------------------------*/
//  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
//  SPI_Init(SPI2, &SPI_InitStructure);

  /* Enable SPI1 CRC calculation */
  //SPI_CalculateCRC(SPI1, ENABLE);
  /* Enable SPI2 CRC calculation */
  //SPI_CalculateCRC(SPI2, ENABLE);

  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
  /* Enable SPI2 */
//  SPI_Cmd(SPI2, ENABLE);
	
}

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef	NVIC_InitStruction;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruction.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStruction.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruction.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruction.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruction);
}

