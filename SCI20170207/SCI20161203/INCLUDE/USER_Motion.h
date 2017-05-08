#ifndef USER_MOTION_H
#define USER_MOTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSPTotal.h"

extern void Set_PID(void);
extern void SingleMotor_Control(void);
extern void TotalMotor_Control(void);
extern void Motion_Type(void);
extern void Motion_Control(void);

static void Advance_Control(void);
static void Back_Control(void);
static void Up_Control(void);
static void Down_Control(void);
static void ShangYang_Control(void);
static void XiaYang_Control(void);
static void Right_Control(void);
static void Left_Control(void);
static void Stop_Control(void);
static Uint16 Num_Change(Uint16 s);

#ifdef __cplusplus
}
#endif
#endif
