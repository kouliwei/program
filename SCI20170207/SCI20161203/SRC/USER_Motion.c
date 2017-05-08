#include "USER_Motion.h"

unsigned int number=0;
unsigned int speed=0;
unsigned int motion=0;



extern void Set_PID(void)
{
	Kp = Real_PcBuff[2];
	Ki = Real_PcBuff[3];
	Kd = Real_PcBuff[4];
	UART_Send();
}

extern void SingleMotor_Control(void)
{
	Uint16 position = 0,speed = 0,sp = 0;
	position = Real_PcBuff[2];
	speed  = Real_PcBuff[3];
	sp = Num_Change(speed);
	switch(position)
	{
		case 0x01:
			EPwmSetup1(sp);
			EPwmSetup2(PWM_STOP);
			EPwmSetup3(PWM_STOP);
			EPwmSetup4(PWM_STOP);
			break;
		case 0x02:
			EPwmSetup2(sp);
			EPwmSetup1(PWM_STOP);
			EPwmSetup3(PWM_STOP);
			EPwmSetup4(PWM_STOP);

			break;
		case 0x03:
			EPwmSetup3(sp);
			EPwmSetup1(PWM_STOP);
			EPwmSetup2(PWM_STOP);
			EPwmSetup4(PWM_STOP);
			break;
		case 0x04:
			EPwmSetup4(sp);
			EPwmSetup1(PWM_STOP);
			EPwmSetup2(PWM_STOP);
			EPwmSetup3(PWM_STOP);
			break;
		default :
			EPwmSetup1(sp);
			EPwmSetup2(PWM_STOP);
			EPwmSetup3(PWM_STOP);
			EPwmSetup4(PWM_STOP);
			break;
	}
	AUV_State = 1;
	UART_Send(); //A5 5A 06 01 01 32 38 AA //A5 5A 06 01 02 64 6D AA //A5 5A 06 01 03 00 0A AA // A5 5A 06 01 04 19 24 AA
}


extern void TotalMotor_Control(void)
{
	Uint16 rotor[4] = {0,0,0,0},i = 0;
	for(i = 0; i < 4;i++)
	{
		rotor[i] = Num_Change(Real_PcBuff[i+2]);
	}

	EPwmSetup1(rotor[0]);
	EPwmSetup2(rotor[1]);
	EPwmSetup3(rotor[2]);
	EPwmSetup4(rotor[3]);
	AUV_State = 1;
	UART_Send();
}



extern void Motion_Type(void)
{
	Uint16 type = 0;
	type = Real_PcBuff[2];
	switch(type)
	{
	case 0x36://qianjin
		AUV_State = 2;
		break;
	case 0x34://houtui
		AUV_State = 3;
		break;
	case 0x38://shang
		AUV_State = 4;
		break;
	case 0x32://xia
		AUV_State = 5;
		break;
	case 0x31://shangyang,henggunzuoxian
		AUV_State = 6;
		break;
	case 0x33://xiayang,henggunyouxian
		AUV_State = 7;
		break;
	case 0x39://youzhuan
		AUV_State = 8;
		break;
	case 0x37://zuozhuan
		AUV_State = 9;
		break;
	case 0x35://悬浮
		AUV_State = 10;
		break;
	}
	UART_Send();
//	switch(type)
//	{
//	case 0x36://qianjin
// 		duty1=450;
// 		duty2=795;
// 		duty3=735;
// 		duty4=450;
//		break;
//	case 0x34://houtui
// 		duty1=750;
// 		duty2=405;
// 		duty3=450;
// 		duty4=800;
//		break;
//	case 0x38://shang
//		duty1=450;
//		duty2=405;
//		duty3=450;
//		duty4=450;
//		break;
//	case 0x32://xia
// 		duty1=750;
// 		duty2=795;
// 		duty3=735;
// 		duty4=800;
// 		StartCpuTimer0();
//		break;
//	case 0x31://shangyang,henggunzuoxian
//		duty1=750;
//		duty2=405;
//		duty3=735;
//		duty4=450;
//		break;
//	case 0x33://xiayang,henggunyouxian
//		duty1=450;
//		duty2=795;
//		duty3=450;
//		duty4=800;
//		break;
//	case 0x39://youzhuan
//		duty1=450;
// 		duty2=405;
// 		duty3=735;
// 		duty4=800;
//		break;
//	case 0x37://zuozhuan
// 		duty1=750;
// 		duty2=795;
// 		duty3=450;
// 		duty4=450;
//		break;
//	case 0x35://tingzhi
//  		duty1=700;
//  		duty2=700;
//  		duty3=700;
//  		duty4=700;
//  		StopCpuTimer0();
//		break;
//	}
//	EPwmSetup1(duty1);
//	EPwmSetup2(duty2);
//	EPwmSetup3(duty3);
//	EPwmSetup4(duty4);
}

extern void Motion_Control(void)
{
	while(gl_FlagMotionCycle == 1)
	{
		gl_FlagMotionCycle = 0;
		Sensor_Analysis();        //查询当前状态下AUV的姿态角。
		switch(AUV_State)
		{
		case 2:
			Advance_Control();
			break;
		case 3:
			Back_Control();
			break;
		case 4:
			Up_Control();
			break;
		case 5:
			Down_Control();
			break;
		case 6:
			ShangYang_Control();
			break;
		case 7:
			XiaYang_Control();
			break;
		case 8:
			Right_Control();
			break;
		case 9:
			Left_Control();
			break;
		case 10:
			Stop_Control();
			break;
		}
	}
}


static void Advance_Control(void)
{

}
static void Back_Control(void)
{

}
static void Up_Control(void)
{

}
static void Down_Control(void)
{
	int16 Yaw_Ref = 0;
	float32 u = 0, error = 0,KI = 0,KP = 0;
	static float32 error_sum = 0;
	error = Yaw_Ref - Yaw;
	if(error < -180)
	{
		error = error + 360;
	}
	error = - error/(float)180;



	error_sum += error;
	//积分限幅
	if(error_sum > 10)
	{
		error_sum = 10;
	}
	else if(error_sum < -10)
	{
		error_sum = -10;
	}


	if(error > -0.17 && error < 0.17)
	{
		KI = 50;
		KP = 100;

	}
	else
	{
		KI = 0;
		KP = 150;
	}
	u = KP*error + KI*error_sum;

	//输出限幅
	if(u > 300)
	{
		u = 300;
	}
	else if(u < -300)
	{
		u = -300;
	}

	EPwmSetup1(3000 + (int)u);
	EPwmSetup2(3000);
	EPwmSetup3(3000);
	EPwmSetup4(3000 + (int)u);
}


static void ShangYang_Control(void)
{

}
static void XiaYang_Control(void)
{

}
static void Right_Control(void)
{

}
static void Left_Control(void)
{

}
static void Stop_Control(void)
{

}




static Uint16 Num_Change(Uint16 s)
{
	Uint16 sp;

	if(s<=50)
	{
		sp=PWM_STOP - (PWM_STOP - PWM_BACK_MAX)/50*(50-s);
	}
	else
	{
		sp=PWM_STOP + (PWM_FORWARD_MAX - PWM_STOP)/50*(s-50);
	}

	//****对sp限幅保护*******
	if(sp <= PWM_BACK_MAX)
	{
		sp = PWM_BACK_MAX;
	}
	if(sp >= PWM_FORWARD_MAX)
	{
		sp = PWM_FORWARD_MAX;
	}
	return sp;
}
