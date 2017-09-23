#ifndef USER_SENSOR_H
#define USER_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSPTotal.h"

extern float Real_Yaw ;  //ƫ����
extern float Real_Pitch ;//����
extern float Real_Roll ; //��ת
extern int	Alt ;  //�߶�
extern int	Tempr ;//�¶�
extern int	Press ;//��ѹ

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
