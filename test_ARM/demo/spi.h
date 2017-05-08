#ifndef __SPI_H
#define __SPI_H

#include "include.h"

extern void USR_SPIInit(void);
void NVIC_Configuration(void);

static void SPI_RCC_Configuration(void);
static void SPI_GPIO_Configuration(void);
static void USR_SPI_Init(void);
#endif
