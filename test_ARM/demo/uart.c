#include "uart.h"



//#define _GNUG__

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
	
extern void USART_InitALL()
{
	USART1_Init();
	USART2_Init();
	USART3_Init();
	USART4_Init();
	USART5_Init();
}
	
	
	
extern void USART1_Init()
{
	RCC_USART1();
	GPIO_InitStruct_USART1();
	USART1_InitStruct();
}



static void RCC_USART1(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);
}

static void GPIO_InitStruct_USART1(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void USART1_InitStruct(void)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStruct);
	USART_Cmd(USART1, ENABLE);
}


extern void USART2_Init()
{
	RCC_USART2();
	GPIO_InitStruct_USART2();
	USART2_InitStruct();
}

static void RCC_USART2(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);
}

static void GPIO_InitStruct_USART2(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void USART2_InitStruct(void)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART2, &USART_InitStruct);
	USART_Cmd(USART2, ENABLE);
}

extern void USART3_Init()
{
	RCC_USART3();
	GPIO_InitStruct_USART3();
	USART3_InitStruct();
}

static void RCC_USART3(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,  ENABLE);
}

static void GPIO_InitStruct_USART3(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

static void USART3_InitStruct(void)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART3, &USART_InitStruct);
	USART_Cmd(USART3, ENABLE);
}

extern void USART4_Init()
{
	RCC_USART4();
	GPIO_InitStruct_USART4();
	USART4_InitStruct();
}

static void RCC_USART4(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,  ENABLE);
}

static void GPIO_InitStruct_USART4(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

static void USART4_InitStruct(void)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(UART4, &USART_InitStruct);
	USART_Cmd(UART4, ENABLE);
}

extern void USART5_Init()
{
	RCC_USART5();
	GPIO_InitStruct_USART5();
	USART5_InitStruct();
}

static void RCC_USART5(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,  ENABLE);
}

static void GPIO_InitStruct_USART5(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

static void USART5_InitStruct(void)
{
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(UART5, &USART_InitStruct);
	USART_Cmd(UART5, ENABLE);
}





















extern void TXD_USART(USART_TypeDef* USARTx,uint16_t data,int8_t type)
{
	switch(type)
	{
		case 0:
			TXD_USART_CHAR(USARTx,data);
			break;
		case 2:
			TXD_USART_BIN(USARTx,data);
			break;
		case 10:
			TXD_USART_DEC(USARTx,data);
			break;
		case 16:
			TXD_USART_HEX(USARTx,data);
			break;
		default:
			TXD_USART_DEC(USARTx,data);
			break;
	}
}


static void TXD_USART_DEC(USART_TypeDef* USARTx,uint16_t data)
{
	uint16_t num[5]={0},m=0;
	int8_t i=0;
	for(i=0;;)  //将data的每一位倒序存入num[5]的数组中，例如data=3456,则num[5]={6,5,4,3,0};for循环后i=3
	{
		m=data/10;
		num[i]=data%10;
		data=m;
		if(data==0)
			break;
		else
			i++;
	}
	for(;i>=0;i--)
	{
		USART_SendData(USARTx,num[i]+48);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	}
}

static void TXD_USART_HEX(USART_TypeDef* USARTx,uint16_t data)
{
	uint16_t num[5]={0},m=0;
	int8_t i=0;
	for(i=0;;)  
	{
		m=data/16;
		num[i]=data%16;
		data=m;
		if(data==0)
			break;
		else
			i++;
	}
	for(;i>=0;i--)
	{
		if(num[i]>9)
		{
			num[i]=num[i]+7;
		}
		USART_SendData(USARTx,num[i]+48);
		while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
	}
	printf("\r\n");
}



/**
  * @brief  output the data as binary system
  * @param  USARTx:Specifies the USART
  * @param  data:
            This parameter must be a number between 0x0000 and 0xFFFF.
  * @retval None
  */

static void TXD_USART_BIN(USART_TypeDef* USARTx,uint16_t data)
{
	uint8_t i;
	for(i=0;i<16;i++)
	{
		if(data&(1<<(15-i)))
		{
			USART_SendData(USARTx,'1');
			while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
		}
		else
		{
			USART_SendData(USARTx,'0');
			while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
		}
			
	}
	printf("\r\n");

}

static void TXD_USART_CHAR(USART_TypeDef* USARTx,uint16_t data)
{
	USART_SendData(USARTx,data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == RESET);
	printf("\r\n");
}


PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    {
    }
    return ch;
}


