#ifndef DSPTotal_H
#define DSPTotal_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char uint8_t;
typedef signed char   int8_t;
/*****************DEBUG  definition************************/
/****************if DEBUG == 0:  motor test****************/
/****************if DEBUG == 1:  Led test******************/
/****************if DEBUG == 2:  senser test*************8*/
/****************if DEBUG == 3:  I2C    test***************/
/****************if DEBUG == 4:  normal mode  but Hyper termial ***************/
/****************if DEBUG == 5:  normal mode  and normal terminal ***************/




#ifndef	DEBUG
	#define DEBUG   1
#endif

#ifndef	DEBUG_SHOW
	#define	DEBUG_SHOW	'A'
#endif

//*******PC_SCI	��   AHRS_SCI ���뻥��************//
#ifndef	PC_SCI
	#define	PC_SCI		'B'
#endif

#ifndef	AHRS_SCI
	#if PC_SCI == 'B'
		#define	AHRS_SCI	'A'
	#else
		#define	AHRS_SCI	'B'
	#endif
#endif



#define  RX_BUFFER_SIZE 100 //���ջ������ֽ���


/**************system include ******************/
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#include "math.h"



/***************user-define include*************/
#include "USER_Distance.h"
#include "USER_Pwm.h"
#include "USER_Sci.h"
#include "USER_Sensor.h"
#include "USER_Motion.h"
#include "USER_Common.h"
#include "USER_SPI.h"



extern uint8_t gl_MotionFlag;
extern int Force[4];
extern float KP ;
extern float KI ;
extern float KD ;
extern Uint16 gl_Distance ;
extern Uint16 AHRS_Rx_Buffer[RX_BUFFER_SIZE]; //�������ݻ�����
extern Uint16 PC_Rx_Buffer[RX_BUFFER_SIZE]; //�������ݻ�����
extern Uint16 gl_FlagMotionCycle;
extern Uint16 Real_PcBuff[100];
extern Uint16 Real_AHRSBuff[100];
extern Uint16 ReceivedChar;
extern Uint16 AHRS_RX_Flag;
extern Uint16 PC_RX_Flag;
extern Uint16 AUV_State;
extern Uint16 Last_AUV_State;

#ifdef __cplusplus
}
#endif
#endif
