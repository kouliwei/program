#ifndef __UART_H
#define __UART_H

#include "include.h"


#ifdef __cplusplus
 extern "C" {
#endif
	 
	 




	 
	 
	 
	 
/******************USART  发送数据定时中断相关宏定义***************************/
#define Tx_TIM                      TIM4
#define Tx_CLK                      100
#define Tx_IRQHandler               TIM4_IRQHandler
#define Tx_Enable()                 TIM_ITConfig(Tx_TIM,TIM_IT_Update,ENABLE)           //定时发送中断使能
#define Tx_Cmd() 										TIM_Cmd(Tx_TIM,ENABLE)
#define Tx_Disable()                TIM_ITConfig(Tx_TIM,TIM_IT_Update,DISABLE)          //定时发送中断禁能   
#define Rx_Enable()                 USART_ITConfig(EVAL_COM2,USART_IT_RXNE,ENABLE)      //串口接收中断使能
#define Rx_Disable()                USART_ITConfig(EVAL_COM2,USART_IT_RXNE,DISABLE)      //串口接收中断禁能


extern void USART_InitALL(void);

extern void USART1_Init(void);
static void GPIO_InitStruct_USART1(void);
static void USART1_InitStruct(void);
static void RCC_USART1(void);

extern void USART2_Init(void);
static void GPIO_InitStruct_USART2(void);
static void USART2_InitStruct(void);
static void RCC_USART2(void);

extern void USART3_Init(void);
static void GPIO_InitStruct_USART3(void);
static void USART3_InitStruct(void);
static void RCC_USART3(void);

extern void USART4_Init(void);
static void GPIO_InitStruct_USART4(void);
static void USART4_InitStruct(void);
static void RCC_USART4(void);

extern void USART5_Init(void);
static void GPIO_InitStruct_USART5(void);
static void USART5_InitStruct(void);
static void RCC_USART5(void);




///*****************DEBUG   mode*************************/

extern void TXD_USART(USART_TypeDef* USARTx,uint16_t data,int8_t type);
static void TXD_USART_DEC(USART_TypeDef* USARTx,uint16_t data);
static void TXD_USART_HEX(USART_TypeDef* USARTx,uint16_t data);
static void TXD_USART_BIN(USART_TypeDef* USARTx,uint16_t data);
static void TXD_USART_CHAR(USART_TypeDef* USARTx,uint16_t data);

#ifdef __cplusplus
}
#endif

#endif

