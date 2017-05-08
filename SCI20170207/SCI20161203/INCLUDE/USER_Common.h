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

/**************************   LED  宏定义 **************************/
#define LED1_PORT	GPIO51
#define LED2_PORT	GPIO50
#define LED3_PORT	GPIO49
#define LED4_PORT	GPIO48


#define LED1_On() 		GpioDataRegs.GPBCLEAR.bit.LED1_PORT = 1
#define LED1_Off() 		GpioDataRegs.GPBSET.bit.LED1_PORT = 1
#define LED1_Toggle() 	GpioDataRegs.GPBTOGGLE.bit.LED1_PORT = 1
#define LED2_On() 		GpioDataRegs.GPBCLEAR.bit.LED2_PORT = 1
#define LED2_Off() 		GpioDataRegs.GPBSET.bit.LED2_PORT = 1
#define LED2_Toggle() 	GpioDataRegs.GPBTOGGLE.bit.LED2_PORT = 1
#define LED3_On() 		GpioDataRegs.GPBCLEAR.bit.LED3_PORT = 1
#define LED3_Off() 		GpioDataRegs.GPBSET.bit.LED3_PORT = 1
#define LED3_Toggle() 	GpioDataRegs.GPBTOGGLE.bit.LED3_PORT = 1
#define LED4_On() 		GpioDataRegs.GPBCLEAR.bit.LED4_PORT = 1
#define LED4_Off() 		GpioDataRegs.GPBSET.bit.LED4_PORT = 1
#define LED4_Toggle() 	GpioDataRegs.GPBTOGGLE.bit.LED4_PORT = 1


/**************************   KEY  宏定义 **************************/
#define KEY1_PORT	GPIO26
#define KEY2_PORT	GPIO27
#define KEY3_PORT	GPIO32
#define KEY4_PORT	GPIO33

#define EFF		0
#define NONEFF	1

#define EFF_KEY1()		GpioDataRegs.GPADAT.bit.KEY1_PORT == EFF
#define NONEFF_KEY1()	GpioDataRegs.GPADAT.bit.KEY1_PORT == NONEFF
#define EFF_KEY2()		GpioDataRegs.GPADAT.bit.KEY2_PORT == EFF
#define NONEFF_KEY2()	GpioDataRegs.GPADAT.bit.KEY2_PORT == NONEFF
#define EFF_KEY3()		GpioDataRegs.GPBDAT.bit.KEY3_PORT == EFF
#define NONEFF_KEY3()	GpioDataRegs.GPBDAT.bit.KEY3_PORT == NONEFF
#define EFF_KEY4()		GpioDataRegs.GPBDAT.bit.KEY4_PORT == EFF
#define NONEFF_KEY4()	GpioDataRegs.GPBDAT.bit.KEY4_PORT == NONEFF






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

static void Key_Gpio(void);
static void Led_Gpio(void);
static void Sci_Gpio(void);
static void Scia_Gpio(void);
static void Scib_Gpio(void);
static void Scic_Gpio(void);
static void Sci_485Dir_Gpio(void);

extern void Led_Drive(Uint16 num);

#ifdef __cplusplus
}
#endif


#endif /* USER_COMMON_H_ */
