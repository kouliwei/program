/*
 * USER_SPI.h
 *
 *  Created on: 2017-2-3
 *      Author: kou
 */

#ifndef USER_SPI_H
#define USER_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSPTotal.h"

#define SPI_Mode_Master	1
#define SPI_Mode_Slave	0

#define SPI_CPOL_Low	0
#define SPI_CPOL_high	1
#define	SPI_CPHA_1Edge	0
#define	SPI_CPHA_2Edge	1

#define SPI_DataSize_16b	0x0f
#define SPI_DataSize_8b		0x07

#define	SPI_RECEICEING		0
#define	SPI_RECEICEED		1
#define	SPI_SENDING			1
#define	SPI_SENDED			0


void USER_SPIInit(void);
void USER_SPI_Init(void);
void SD_Ready(void);


#ifdef __cplusplus
}
#endif
#endif
