#include "USER_Motion.h"

unsigned int number=0;
unsigned int speed=0;
unsigned int motion=0;



extern void Set_PID(void)
{
	KP = (float)Real_PcBuff[2];			//比例系数0-255
	KI = (float)Real_PcBuff[3]/255;		//积分系数0-1
	KD = (float)Real_PcBuff[4];
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
	Last_AUV_State = AUV_State;
	switch(type)
	{
	case 0x36://qianjin
		if(Real_PcBuff[0] == 8)		//通过数据长度校验，增加容错
			AUV_State = 2;
		else
			AUV_State = 1;
		break;
	case 0x34://houtui
		AUV_State = 3;
		break;
	case 0x38://shang
		AUV_State = 4;
		break;
	case 0x32://xia
		if(Real_PcBuff[0] == 8)    //通过数据长度校验，增加容错
			AUV_State = 5;
		else
			AUV_State = 1;
		break;
	case 0x31://shangyang,henggunzuoxian
		AUV_State = 6;
		break;
	case 0x33://xiayang,henggunyouxian
		if(Real_PcBuff[0] == 9)		//通过数据长度校验，增加容错
			AUV_State = 7;
		else
			AUV_State = 1;
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
}

extern void Motion_Control(void)
{
	while(gl_FlagMotionCycle == 1)
	{
		gl_FlagMotionCycle = 0;
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
	Motor_Out(Force);
}


static void Advance_Control(void)
{
	static float Ref_Yaw = 0;
	static Uint16 temp = 0;
	static int Forcex = 0;
	if(gl_MotionFlag == 0)
	{
		gl_MotionFlag = 1;
		temp = (Real_PcBuff[4] <<8 ) + Real_PcBuff[5];    //yaw 角
		Saturation(&temp,0,360);
		Ref_Yaw = (float)temp;
		Forcex = Real_PcBuff[3];
	}
	Force[0] = Forcex_Change(Forcex);
	Force[1] = 0;
	Force[2] = 0;                                //暂时不考虑横滚控制；
	Force[3] = Yaw_Control(Ref_Yaw);

}
static void Back_Control(void)
{

}
static void Up_Control(void)
{

}



static void Down_Control(void)
{
	static float Ref_Yaw = 0;
	static Uint16 temp = 0;
	static int Forcez = 0;
	if(gl_MotionFlag == 0)
	{
		gl_MotionFlag = 1;
		temp = (Real_PcBuff[4] <<8 ) + Real_PcBuff[5];    //yaw 角
		Saturation(&temp,0,360);
		Ref_Yaw = (float)temp;
		Forcez = Real_PcBuff[3];
	}
	Force[0] = 0;
	Force[1] = Forcez_Change(Forcez);
	Force[2] = 0;                                //暂时不考虑横滚控制；
	Force[3] = Yaw_Control(Ref_Yaw);
}


static void ShangYang_Control(void)
{

}
static void XiaYang_Control(void)    //既前进又下沉又保证yaw角稳定
{
	static float Ref_Yaw = 0;
	static Uint16 temp = 0;
	static int Forcex = 0;
	static int Forcez = 0;
	if(gl_MotionFlag == 0)
	{
		gl_MotionFlag = 1;
		temp = (Real_PcBuff[5] <<8 ) + Real_PcBuff[6];    //yaw 角
		Saturation(&temp,0,360);
		Ref_Yaw = (float)temp;
		Forcex = Real_PcBuff[3];
		Forcez = Real_PcBuff[4];
	}
	Force[0] = Forcez_Change(Forcex);
	Force[1] = Forcez_Change(Forcez);
	Force[2] = 0;                                //暂时不考虑横滚控制；
	Force[3] = Yaw_Control(Ref_Yaw);
}
static void Right_Control(void)
{

}
static void Left_Control(void)
{

}
static void Stop_Control(void)
{
	Force[0] = 0;
	Force[1] = 0;
	Force[2] = 0;
	Force[3] = 0;
}





static int Yaw_Control(float Ref_Yaw)
{
	float u_temp = 0, error = 0;
	static float error_sum = 0;
	int u = 0;

	error = Ref_Yaw - Real_Yaw;


	if(error < -180)
	{
		error = error + 360;
	}
	else if(error > 180)
	{
		error = error - 360;
	}
	error = error/(float)180;  //归一化
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
		error_sum += error;
	}
	else
	{
		error_sum = 0;
	}

	u_temp = KP*error + KI*error_sum;

	//输出限幅
	if(u_temp > MAX_YAWF)
	{
		u_temp = MAX_YAWF;
	}
	if(u_temp < MIN_YAWF)
	{
		u_temp = MIN_YAWF;
	}
	u = (int)u_temp;
	return u;
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

static int	Forcez_Change(Uint16 s)
{
	float temp = 0;
	temp = (float)s/255*80;
	return (int)temp;
}


static int	Forcex_Change(Uint16 s)
{
	float temp = 0;
	temp = (float)s/255*130;
	return (int)temp;
}

static void Saturation(Uint16 *temp,Uint16 min,Uint16 max)
{
	if(*temp < min)
	{
		*temp = min;
	}
	else if(*temp > max)
	{
		*temp = max;
	}
}
