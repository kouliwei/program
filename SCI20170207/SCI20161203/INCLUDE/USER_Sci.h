#ifndef USER_SCI_H
#define USER_SCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSPTotal.h"

#if DEBUG != 0
interrupt void Uart_Rx(void);
#endif

extern void DataInter_AHRS(void);
extern void DataInter_Pc(void);
extern void UART_SendSensor(void);
extern void UART_SendDis(void);
extern void UART_Send(void);



extern void Sci_Init(void);
static void Scia_Init(void);
extern void Scia_Xmit(uint8_t a);
extern void Scia_Msg(char *msg);

static void Scib_Init(void);
extern void Scib_Xmit(uint8_t a);
extern void Scib_Msg(char *msg);

static void Scic_Init(void);
extern void Scic_Xmit(uint8_t a);
extern void Scic_Msg(char *msg);

extern void Sci_Send_Sing(uint8_t temp,...);
extern void	Sci_Send(char *msg,...);

extern void TXD_USART_BIN(char temp,uint8_t data);

#ifdef __cplusplus
}
#endif
#endif
