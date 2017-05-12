#include "USER_Pwm.h"


const double Eff_Matrix[6][4] = {{CA,	   -CA,	    CA,		-CA},\
						   {0,        0,	     0,       0},\
						   {SA,	   SA,	    SA,	     SA},\
						   {Y0*SA,   Y0*SA,  -Y0*SA,   -Y0*SA},\
						   {-X0*CA,  X0*CA,   X0*CA,   -X0*CA},\
						   {-Y0*CA,  Y0*CA,   Y0*CA,   -Y0*CA}};

const double T_Matrix[4][4]= {{1/(4*CA),	   1/(4*SA),	    1/(4*Y0*SA),		-1/(4*X0*SA)},\
		                {-1/(4*CA),	   1/(4*SA),	    1/(4*Y0*SA),		1/(4*X0*SA)},\
		                {1/(4*CA),	   1/(4*SA),	    -1/(4*Y0*SA),		1/(4*X0*SA)},\
		                {-1/(4*CA),	   1/(4*SA),	    -1/(4*Y0*SA),		-1/(4*X0*SA)}};


extern void  EPwm_Init(void)
{
	EPwm1_Init();
	EPwm2_Init();
	EPwm3_Init();
	EPwm4_Init();
}


static void EPwm1_Init(void)
{
	EPwm1_Gpio();
	EPWM1_Regs_Init();
}

static void EPwm2_Init(void)
{
	EPwm2_Gpio();
	EPWM2_Regs_Init();

}

static void EPwm3_Init(void)
{
	EPwm3_Gpio();
	EPWM3_Regs_Init();
}

static void EPwm4_Init(void)
{
	EPwm4_Gpio();
	EPWM4_Regs_Init();
}
static void EPWM1_Regs_Init(void)
{
	EPwm1Regs.TBPHS.half.TBPHS=0x0000;
	EPwm1Regs.TBCTR=0x0000;
	EPwm1Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
	EPwm1Regs.TBCTL.bit.PHSEN=TB_DISABLE;//定时器相位使能位关闭
	EPwm1Regs.TBCTL.bit.HSPCLKDIV=2;
	EPwm1Regs.TBCTL.bit.CLKDIV=4;//Fre=150000000/(2*2   *   2^4);   //分频后的频率
	EPwm1Regs.TBPRD = 46874;

	EPwm1Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;
	EPwm1Regs.CMPA.half.CMPA= 3500;
	//EPwm1Regs.CMPA.half.CMPA= 2343 对应1ms
	//EPwm1Regs.CMPA.half.CMPA= 4687 对应2ms
	//EPwm1Regs.CMPA.half.CMPA= 3515 对应1.5ms
	//近似计算
	//EPwm1Regs.CMPA.half.CMPA= 2500 对应1ms   	//1.067ms
	//EPwm1Regs.CMPA.half.CMPA= 4500 对应2ms		//1.920ms
	//EPwm1Regs.CMPA.half.CMPA= 3500 对应1.5ms 	//1.494ms


	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;

}

static void EPWM2_Regs_Init(void)
{
	EPwm2Regs.TBPHS.half.TBPHS=0x0000;
	EPwm2Regs.TBCTR=0x0000;
	EPwm2Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
	EPwm2Regs.TBCTL.bit.PHSEN=TB_DISABLE;//定时器相位使能位关闭
	EPwm2Regs.TBCTL.bit.HSPCLKDIV=2;
	EPwm2Regs.TBCTL.bit.CLKDIV=4;//Fre=150000000/(2*2   *   2^4);   //分频后的频率
	EPwm2Regs.TBPRD = 46874;

	EPwm2Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;
	EPwm2Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;
	EPwm2Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;
	EPwm2Regs.CMPA.half.CMPA= 3500;
	//EPwm2Regs.CMPA.half.CMPA= 2343 对应1ms
	//EPwm2Regs.CMPA.half.CMPA= 4687 对应2ms
	//EPwm2Regs.CMPA.half.CMPA= 3515 对应1.5ms
	//近似计算
	//EPwm2Regs.CMPA.half.CMPA= 2500 对应1ms   	//1.067ms
	//EPwm2Regs.CMPA.half.CMPA= 4500 对应2ms		//1.920ms
	//EPwm2Regs.CMPA.half.CMPA= 3500 对应1.5ms 	//1.494ms


	EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
}
static void EPWM3_Regs_Init(void)
{
	EPwm3Regs.TBPHS.half.TBPHS=0x0000;
	EPwm3Regs.TBCTR=0x0000;
	EPwm3Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
	EPwm3Regs.TBCTL.bit.PHSEN=TB_DISABLE;//定时器相位使能位关闭
	EPwm3Regs.TBCTL.bit.HSPCLKDIV=2;
	EPwm3Regs.TBCTL.bit.CLKDIV=4;//Fre=150000000/(2*2   *   2^4);   //分频后的频率
	EPwm3Regs.TBPRD = 46874;

	EPwm3Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;
	EPwm3Regs.CMPA.half.CMPA= 3500;
	//EPwm3Regs.CMPA.half.CMPA= 2343 对应1ms
	//EPwm3Regs.CMPA.half.CMPA= 4687 对应2ms
	//EPwm3Regs.CMPA.half.CMPA= 3515 对应1.5ms
	//近似计算
	//EPwm3Regs.CMPA.half.CMPA= 2500 对应1ms   	//1.067ms
	//EPwm3Regs.CMPA.half.CMPA= 4500 对应2ms		//1.920ms
	//EPwm3Regs.CMPA.half.CMPA= 3500 对应1.5ms 	//1.494ms


	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
}
static void EPWM4_Regs_Init(void)
{
	EPwm4Regs.TBPHS.half.TBPHS=0x0000;
	EPwm4Regs.TBCTR=0x0000;
	EPwm4Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
	EPwm4Regs.TBCTL.bit.PHSEN=TB_DISABLE;//定时器相位使能位关闭
	EPwm4Regs.TBCTL.bit.HSPCLKDIV=2;
	EPwm4Regs.TBCTL.bit.CLKDIV=4;//Fre=150000000/(2*2   *   2^4);   //分频后的频率
	EPwm4Regs.TBPRD = 46874;

	EPwm4Regs.CMPCTL.bit.SHDWAMODE=CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.SHDWBMODE=CC_SHADOW;
	EPwm4Regs.CMPCTL.bit.LOADAMODE=CC_CTR_ZERO;
	EPwm4Regs.CMPCTL.bit.LOADBMODE=CC_CTR_ZERO;
	EPwm4Regs.CMPA.half.CMPA= 3500;
	//EPwm4Regs.CMPA.half.CMPA= 2343 对应1ms
	//EPwm4Regs.CMPA.half.CMPA= 4687 对应2ms
	//EPwm4Regs.CMPA.half.CMPA= 3515 对应1.5ms
	//近似计算
	//EPwm4Regs.CMPA.half.CMPA= 2500 对应1ms   	//1.067ms
	//EPwm4Regs.CMPA.half.CMPA= 4500 对应2ms		//1.920ms
	//EPwm4Regs.CMPA.half.CMPA= 3500 对应1.5ms 	//1.494ms


	EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
}

static void EPwm1_Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    //GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    //GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

static void EPwm2_Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    //GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO0 as EPWM1A
    //GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

static void EPwm3_Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    //GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO0 as EPWM1A
    //GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

static void EPwm4_Gpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO0 (EPWM1A)
    //GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;    // Enable pull-up on GPIO1 (EPWM1B)

/* Configure ePWM-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be ePWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO0 as EPWM1A
    //GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}




void EPwmSetup1(Uint16 duty11)
{
   EPwm1Regs.CMPA.half.CMPA= duty11;
}

void EPwmSetup2(Uint16 duty22)
{
	EPwm2Regs.CMPA.half.CMPA=duty22;
}

void EPwmSetup3(Uint16 duty33)
{
	EPwm3Regs.CMPA.half.CMPA=duty33;
}

void EPwmSetup4(Uint16 duty44)
{
	EPwm4Regs.CMPA.half.CMPA=duty44;
}

void Motor_Out(int*	Force)
{
	uint8_t i = 0,j = 0;
	double Temp[4]={0,0,0,0};
	int8_t Temp2[4]={0,0,0,0};
	for(i=0;i<4;i++)
	{
		Temp[i] = 0;
		for(j=0;j<4;j++)
		{
			Temp[i] = Temp[i] + T_Matrix[i][j]*Force[j];
		}
		if(Temp[i] > 40)
		{
			Temp[i]  = 40;
		}
		else if(Temp[i] < -40)
		{
			Temp[i]  = -40;
		}
		Temp2[i]= (int8_t)Temp[i];
	}

	EPwm1Regs.CMPA.half.CMPA = PWM_STOP + 25 * Temp2[0];
	EPwm2Regs.CMPA.half.CMPA = PWM_STOP + 25 * Temp2[1];
	EPwm3Regs.CMPA.half.CMPA = PWM_STOP + 25 * Temp2[2];
	EPwm4Regs.CMPA.half.CMPA = PWM_STOP + 25 * Temp2[3];

}
