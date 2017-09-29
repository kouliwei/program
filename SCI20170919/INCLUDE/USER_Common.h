/*
 * USER_Common.h
 *
 *  Created on: 2016-5-16
 *      Author: koukou
 */

#ifndef USER_COMMON_H_
#define USER_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "DSPTotal.h"

/**************************   LED  ∫Í∂®“Â **************************/
#define LED1_PORT	GPIO10
#define LED2_PORT	GPIO8
#define LED3_PORT	GPIO7
#define LED4_PORT	GPIO5


#define LED1_On() 		GpioDataRegs.GPACLEAR.bit.LED1_PORT = 1
#define LED1_Off() 		GpioDataRegs.GPASET.bit.LED1_PORT = 1
#define LED1_Toggle() 	GpioDataRegs.GPATOGGLE.bit.LED1_PORT = 1
#define LED2_On() 		GpioDataRegs.GPACLEAR.bit.LED2_PORT = 1
#define LED2_Off() 		GpioDataRegs.GPASET.bit.LED2_PORT = 1
#define LED2_Toggle() 	GpioDataRegs.GPATOGGLE.bit.LED2_PORT = 1
#define LED3_On() 		GpioDataRegs.GPACLEAR.bit.LED3_PORT = 1
#define LED3_Off() 		GpioDataRegs.GPASET.bit.LED3_PORT = 1
#define LED3_Toggle() 	GpioDataRegs.GPATOGGLE.bit.LED3_PORT = 1
#define LED4_On() 		GpioDataRegs.GPACLEAR.bit.LED4_PORT = 1
#define LED4_Off() 		GpioDataRegs.GPASET.bit.LED4_PORT = 1
#define LED4_Toggle() 	GpioDataRegs.GPATOGGLE.bit.LED4_PORT = 1







extern void Circle_Led(void);
extern void Store_SensorData(void);
extern void Store_PcData(Uint16* Data_To,Uint16* Data2_From);
extern void Para_Init(void);
extern void Gpio_Init(void);
extern void Delay_1ms(void);
extern void Delay_Nms(Uint16 num);
#if DEBUG != 0
extern void IntTime_Config(void);
#endif

static void Led_Gpio(void);
static void Sci_Gpio(void);
static void Scia_Gpio(void);
static void Scib_Gpio(void);
static void Scic_Gpio(void);
//static void Sci_485Dir_Gpio(void);

extern void Led_Drive(Uint16 num);

#ifdef __cplusplus
}
#endif


#endif /* USER_COMMON_H_ */
