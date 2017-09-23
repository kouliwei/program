#ifndef USER_SENSOR_H
#define USER_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSPTotal.h"

extern float Real_Yaw ;  //偏航角
extern float Real_Pitch ;//俯仰
extern float Real_Roll ; //滚转
extern int	Alt ;  //高度
extern int	Tempr ;//温度
extern int	Press ;//气压

#if DEBUG !=0
interrupt void Uart_AHRS(void);
#endif

interrupt void ISRTimer0(void);


extern void Sensor_Analysis(void);
//void sensor1Istr(void);



//void UART2_decision1();

//void loopControlVerticalDown(void);





#ifdef __cplusplus
}
#endif

#endif
