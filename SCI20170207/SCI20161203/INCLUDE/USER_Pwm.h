#ifndef USER_PWM_H
#define USER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "DSPTotal.h"

#define PWM_STOP			3500
#define PWM_FORWARD_MAX		4500
#define PWM_BACK_MAX		2500

extern void EPwmSetup1(Uint16 duty11);
extern void EPwmSetup2(Uint16 duty22);
extern void EPwmSetup3(Uint16 duty33);
extern void EPwmSetup4(Uint16 duty44);

extern void EPwm_Init(void);
static void EPwm1_Init(void);
static void EPwm2_Init(void);
static void EPwm3_Init(void);
static void EPwm4_Init(void);
static void EPwm1_Gpio(void);
static void EPwm2_Gpio(void);
static void EPwm3_Gpio(void);
static void EPwm4_Gpio(void);
static void EPWM1_Regs_Init(void);
static void EPWM2_Regs_Init(void);
static void EPWM3_Regs_Init(void);
static void EPWM4_Regs_Init(void);

#ifdef __cplusplus
}
#endif
#endif
