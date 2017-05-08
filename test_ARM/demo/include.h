#ifndef __INCLUDE_H
#define __INCLUDE_H




#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include <stdio.h>
	 


	 
#include "led.h"
#include "uart.h"
#include "spi.h"
	 
	 
extern 	uint8_t SPI1_Buffer_Rx[10];

#ifdef __cplusplus
}
#endif

#endif

