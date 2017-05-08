#include "include.h"


 typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define BufferSize  10


//uint16_t SPI1_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C,
//                                  0x0D0E, 0x0F10, 0x1112, 0x1314, 0x1516, 0x1718,
//                                  0x191A, 0x1B1C, 0x1D1E, 0x1F20, 0x2122, 0x2324,
//                                  0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
//                                  0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C,
//                                  0x3D3E, 0x3F40};
// uint8_t SPI1_Buffer_Tx[BufferSize] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
//																			 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
//																			 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,
//																			 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37};
uint8_t SPI1_Buffer_Tx[BufferSize] = {0,1,2,3,4,5,6,7,8,9};

uint8_t SPI1_Buffer_Rx[10], SPI2_Buffer_Rx[BufferSize];
uint16_t TxIdx = 0, RxIdx = 0;
__IO uint16_t CRC1Value = 0, CRC2Value = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
uint16_t SPI1_SendRecv(uint16_t data);
 
//TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

int main(void)
{
	uint8_t i = 0;
	SystemInit();
  /*初始化LED端口*/
  LED_GPIO_Config();
	LED3_OFF();
//	USART_InitALL();
	USR_SPIInit();
	NVIC_Configuration();

	
//	for(TxIdx = 0 ;TxIdx < 10; TxIdx++)
//	{
//		SPI1_Buffer_Rx[TxIdx] = SPI1_SendRecv(SPI1_Buffer_Tx[TxIdx]);
//	}
//	
//	//打印输出结果
//	for(TxIdx = 0 ;TxIdx < 10; TxIdx++)
//	{
//		TXD_USART(USART1,SPI1_Buffer_Rx[TxIdx],10);
//	}
	while(1)
	{
		if (TxIdx >0x5ff)
		{
			TxIdx = 0;
			LEDXToggle(3);
			Delay_Nms(1000);
		}
//		if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == SET)
//		{
//			
//			SPI_I2S_SendData(SPI1, 0xfffe);
//			Delay_Nms(1000);
//			LEDXToggle(3);
//			//SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx]);
//		}
//		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		i = SPI1_SendRecv(TxIdx);
		TxIdx++;
	}


	
//	  /* Transfer procedure */
//  while (TxIdx < BufferSize - 1)
//  {
//    /* Wait for SPI1 Tx buffer empty */
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//    /* Send SPI2 data */
//    SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
//    /* Send SPI1 data */
//    SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx++]);
//    /* Wait for SPI2 data reception */
//    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//    /* Read SPI2 received data */
//    SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);
//    /* Wait for SPI1 data reception */
//    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//    /* Read SPI1 received data */
//    SPI1_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
//  }

//  /* Wait for SPI1 Tx buffer empty */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
//  /* Wait for SPI2 Tx buffer empty */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

//  /* Send last SPI2_Buffer_Tx data */
//  SPI_I2S_SendData(SPI2, SPI2_Buffer_Tx[TxIdx]);
//  /* Enable SPI2 CRC transmission */
//  //SPI_TransmitCRC(SPI2);
//  /* Send last SPI1_Buffer_Tx data */
//  SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx]);
//  /* Enable SPI1 CRC transmission */
//  //SPI_TransmitCRC(SPI1);

//  /* Wait for SPI1 last data reception */
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//  /* Read SPI1 last received data */
//  SPI1_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI1);

//  /* Wait for SPI2 last data reception */
//  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
//  /* Read SPI2 last received data */
//  SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);

//  /* Wait for SPI1 data reception: CRC transmitted by SPI2 */
////  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
//  /* Wait for SPI2 data reception: CRC transmitted by SPI1 */
////  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

//  /* Check the received data with the send ones */
//  TransferStatus1 = Buffercmp(SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
//  TransferStatus2 = Buffercmp(SPI1_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
//  /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
//     are correct */
//  /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
//     are different */

//  /* Test on the SPI1 CRC Error flag */
//	if (TransferStatus1 == PASSED)
//	{
//		LED3_ON();
//	}
//	else
//	{
//		LED3_OFF();
//	}
//	Delay_Nms(1000);
//	
//	
//  if ((SPI_I2S_GetFlagStatus(SPI1, SPI_FLAG_CRCERR)) == SET)
//  {
//    TransferStatus2 = FAILED;
//  }

//  /* Test on the SPI2 CRC Error flag */
//  if ((SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_CRCERR)) == SET)
//  {
//    TransferStatus1 = FAILED;
//  }
//	

//  /* Read SPI1 received CRC value */
//  CRC1Value = SPI_I2S_ReceiveData(SPI1);
//  /* Read SPI2 received CRC value */
//  CRC2Value = SPI_I2S_ReceiveData(SPI2);
  while(1)
  {	 
		LED3_ON();

  }		
}

uint16_t SPI1_SendRecv(uint16_t data)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET); 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, data);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);  //判断从机接受是否为非空
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET); 
	return SPI1->DR;
}




//TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
//{
//  while (BufferLength--)
//  {
//    if (*pBuffer1 != *pBuffer2)
//    {
//      return FAILED;
//    }

//    pBuffer1++;
//    pBuffer2++;
//  }

//  return PASSED;
//}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}

#endif

