#ifndef DSPTotal_H
#define DSPTotal_H


#ifdef __cplusplus
extern "C" {
#endif


typedef unsigned char uint8_t;
typedef signed char   int8_t;

typedef struct{
	int8_t data[11];
	int data1[3];
}SLiding_Para;//滑膜控制器参数






#ifndef	DEBUG
	#define DEBUG   1
#endif

#ifndef	DEBUG_SHOW
	#define	DEBUG_SHOW	'A'
#endif

//*******PC_SCI	和   AHRS_SCI 必须互斥************//
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




#define  RX_BUFFER_SIZE 100 //接收缓冲区字节数


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
#include "USER_Sliding.h"
#include "USER_ADC.h"


extern uint8_t  Buff_Real[20];
extern uint8_t  Control_Time;
extern uint8_t	Buff_Total[200][20];
extern uint8_t 	gl_TimeFlag[5];
extern uint8_t	gl_TempFlag[10];
extern uint8_t 	gl_Dis[2];
extern float    AHRS_Data[12];
extern uint8_t gl_MotionFlag;
extern int Force[4];
extern float KP ;
extern float KI ;
extern float KD ;
extern Uint16 AHRS_Rx_Buffer[RX_BUFFER_SIZE]; //接收数据缓冲区
extern Uint16 PC_Rx_Buffer[RX_BUFFER_SIZE]; //接收数据缓冲区
extern Uint16 gl_FlagMotionCycle;
extern Uint16 Real_PcBuff[100];
extern Uint16 Real_AHRSBuff[100];
extern Uint16 AHRS_RX_Flag;
extern Uint16 PC_RX_Flag;
extern Uint16 AUV_State;
extern Uint16 Last_AUV_State;

#ifdef __cplusplus
}
#endif
#endif
