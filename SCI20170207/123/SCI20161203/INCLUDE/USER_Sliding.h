/*
 *
 *
 *  Created on: 2016-5-16
 *      Author: koukou
 */

#ifndef USER_SLIDING_H_
#define USER_SLIDING_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "DSPTotal.h"

extern SLiding_Para sliding_para;
extern volatile float T[4];
extern volatile float u,w,x,z,tt;
void  spacecontrol1(void);
void  spacecontrol2(void);
extern void Set_SlidingPara(void);


#ifdef __cplusplus
}
#endif


#endif
