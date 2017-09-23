/*
 * USER_Common.c
 *
 *  Created on: 2016-5-16
 *      Author: koukou
 */
#include "USER_Common.h"

static void Led_Gpio(void)
{

	EALLOW;
	GpioCtrlRegs.GPBMUX2.bit.LED1_PORT = 0;
	GpioCtrlRegs.GPBDIR.bit.LED1_PORT = 1;
	GpioCtrlRegs.GPBMUX2.bit.LED2_PORT = 0;
	GpioCtrlRegs.GPBDIR.bit.LED2_PORT = 1;
	GpioCtrlRegs.GPBMUX2.bit.LED3_PORT = 0;
	GpioCtrlRegs.GPBDIR.bit.LED3_PORT = 1;
	GpioCtrlRegs.GPBMUX2.bit.LED4_PORT = 0;
	GpioCtrlRegs.GPBDIR.bit.LED4_PORT = 1;
	EDIS;
}

static void Key_Gpio(void)
{

	EALLOW;
	GpioCtrlRegs.GPAMUX2.bit.KEY1_PORT = 0;
	GpioCtrlRegs.GPADIR.bit.KEY1_PORT = 0;
	GpioCtrlRegs.GPAMUX2.bit.KEY2_PORT = 0;
	GpioCtrlRegs.GPADIR.bit.KEY2_PORT = 0;
	GpioCtrlRegs.GPBMUX1.bit.KEY3_PORT = 0;
	GpioCtrlRegs.GPBDIR.bit.KEY3_PORT = 0;
	GpioCtrlRegs.GPBMUX1.bit.KEY4_PORT = 0;
	GpioCtrlRegs.GPBDIR.bit.KEY4_PORT = 0;
	EDIS;
}



extern void Led_Drive(Uint16 num)
{
    if(num & 0x01)
    	LED1_On();
    else
    	LED1_Off();
    if(num & 0x02)
    	LED2_On();
    else
    	LED2_Off();
    if(num & 0x04)
    	LED3_On();
    else
        LED3_Off();
    if(num & 0x08)
    	LED4_On();
    else
        LED4_Off();

}

extern void Circle_Led(void)
{
	uint8_t i = 1,j = 0;
	while(1)
	{
		Led_Drive(i);
		if(i == 8)
		{
			j = 1;
		}
		else if (i == 1)
		{
			j = 0 ;
		}
		if (j == 0)
		{
			i = i<<1;
		}
		else
		{
			i = i>>1;
		}
		Delay_Nms(1000);
	}
}

#if DEBUG != 0

extern void IntTime_Config(void)
{
	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	InitPieCtrl();
	InitPieVectTable();

	EALLOW;
	PieVectTable.TINT0 = &ISRTimer0;
#if PC_SCI == 'A'
	PieVectTable.SCIRXINTA = &Uart_Rx;
    PieVectTable.SCIRXINTB = &Uart_AHRS;
#else
	PieVectTable.SCIRXINTA = &Uart_AHRS;
    PieVectTable.SCIRXINTB = &Uart_Rx;
#endif
    PieVectTable.SCIRXINTC = &DistanceIstr;    //测距，SCIC接收中断


	EDIS;

	InitCpuTimers();
	ConfigCpuTimer(&CpuTimer0,150,50000);  //500000us=500ms
	//StartCpuTimer0();
	StopCpuTimer0();  //停止定时器工作

//	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
//	InitFlash();

	IER |= M_INT9;
	IER |= M_INT1;
	IER |= M_INT8;

	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;    	//TIM0中断
	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;    	//SCIB接收中断
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		//SCIA接收中断
	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;		//SCIC接收中断

	EINT;  //开启总中断
}
#endif

extern void Para_Init(void)
{
	uint8_t i = 0,j = 0;
	for(i = 0; i<100; i++)
	{
		Real_PcBuff[i] = 0;
		Real_AHRSBuff[i] = 0;
	}
	for(i=0;i<4;i++)
	{
		Force[i] = 0;
	}
	for(i = 0;i<200;i++)
	{
		for(j = 0;j<18;j++)
		{
			Buff_Total[i][j] = 0;
		}
	}
}

extern void Store_PcData(Uint16* Data_To,Uint16* Data2_From)
{
	Uint16 i = 0;
	for(i = 0;i<Data2_From[0] - 2;i++)
	{
		Data_To[i] = Data2_From[i];
	}
}

extern void Store_SensorData(void)
{
	Uint16 i = 0;
	uint8_t j = 0,k = 0;
	int16 temp = 0;
	for(i = 0;i < 36;i++)
	{
		Real_AHRSBuff[i] = AHRS_Rx_Buffer[i];
	}
	temp = (Real_AHRSBuff[2] <<8 ) + Real_AHRSBuff[3];    //yaw 角
	Real_Yaw = (float)temp/10;

	//store the yaw, pitch and roll angle into the AHRS_Data[0],[1],[2]
	k = 2;
	for(j=0;j<=2;j++)
	{
		temp = 0;
		temp = (Real_AHRSBuff[k] <<8 ) + Real_AHRSBuff[k+1];
		if(temp&0x8000)
		{
			temp = 0 - temp&0x7fff;
		}
		else
		{
			temp = (temp&0x7fff);
		}
		AHRS_Data[j]=(float)temp/10;
		k = k+2;
	}


	//18 3 20 4 22 5 24 6 26 7 28 8 30 9 32 10 34 11
	/*store the ax, ay, az into the AHRS_Data[3],[4],[5]
	 *store the GYx, GYy, GYz into the AHRS_Data[6],[7],[8]
	 *store the Mx, My, Mz into the AHRS_Data[9],[10],[11]
	 */
	k = 18;
	for(j=3;j<=11;j++)
	{
		temp = 0;
		temp = (Real_AHRSBuff[k] <<8 ) + Real_AHRSBuff[k+1];    //ax 角
		if(temp&0x8000)
		{
			temp = 0 - temp&0x7fff;
		}
		else
		{
			temp = (temp&0x7fff);
		}
		AHRS_Data[j]=(float)temp;
		k = k+2;
	}
}



extern void Gpio_Init(void)
{
	Led_Gpio();
	Key_Gpio();
	Sci_Gpio();
	InitMcbspbGpio();
//	Sci_485Dir_Gpio();
}


extern void Delay_1ms(void)
{
  int i,j;
  for(i = 0; i < 50; i++)
  {
  for(j = 0; j < 230; j++);
  }
}

extern void Delay_Nms(Uint16 num)
{
	while(num--)
	{
		Delay_1ms();
	}
}


///**********Initial the GPIO49 pin which can control the rx/tx function of 485*************/
//
//static void Sci_485Dir_Gpio(void)
//{
//    EALLOW;
//    GpioCtrlRegs.GPBPUD.bit.GPIO49 = 0;
//    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;
//    GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
//    EDIS;
//}




/****************** DSP-SCI-GPIO初始化********************/
static void Sci_Gpio(void)
{
	Scia_Gpio();
	Scib_Gpio();
	Scic_Gpio();
}

static void Scia_Gpio(void)
{
	EALLOW;

	//GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	//GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)
	GpioCtrlRegs.GPBPUD.bit.GPIO36 = 0;	   // Enable pull-up for GPIO36 (SCIRXDA)
	GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;	   // Enable pull-up for GPIO35 (SCITXDA)

	//GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPBQSEL1.bit.GPIO36 = 3;  // Asynch input GPIO28 (SCIRXDA)

	//GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	//GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1;   // Configure GPIO36 for SCIRXDA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1;   // Configure GPIO35 for SCITXDA operation

	EDIS;
}


static void Scib_Gpio(void)
{
   EALLOW;

   GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;     // Enable pull-up for GPIO9  (SCITXDB)
   GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;    // Enable pull-up for GPIO11 (SCIRXDB)
   //GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;    // Enable pull-up for GPIO14 (SCITXDB)
   //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;    // Enable pull-up for GPIO15 (SCIRXDB)
   //GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;	   // Enable pull-up for GPIO18 (SCITXDB)
   //GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	   // Enable pull-up for GPIO19 (SCIRXDB)
   //GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;    // Enable pull-up for GPIO22 (SCITXDB)
   //GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)

   GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  // Asynch input GPIO11 (SCIRXDB)
   //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3;  // Asynch input GPIO15 (SCIRXDB)
   //GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO19 (SCIRXDB)
   //GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;  // Asynch input GPIO23 (SCIRXDB)

   GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 2;    // Configure GPIO9 for SCITXDB operation
   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 2;   // Configure GPIO11 for SCIRXDB operation
   //GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 2;   // Configure GPIO14 for SCITXDB operation
   //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;   // Configure GPIO15 for SCIRXDB operation
   //GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 2;   // Configure GPIO18 for SCITXDB operation
   //GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 2;   // Configure GPIO19 for SCIRXDB operation
   //GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 3;   // Configure GPIO22 for SCITXDB operation
   //GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 3;   // Configure GPIO23 for SCIRXDB operation

   EDIS;
}

static void Scic_Gpio(void)
{
	EALLOW;

	GpioCtrlRegs.GPBPUD.bit.GPIO62 = 0;    // Enable pull-up for GPIO62 (SCIRXDC)
	GpioCtrlRegs.GPBPUD.bit.GPIO63 = 0;	   // Enable pull-up for GPIO63 (SCITXDC)

	GpioCtrlRegs.GPBQSEL2.bit.GPIO62 = 3;  // Asynch input GPIO62 (SCIRXDC)

	GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 1;   // Configure GPIO62 for SCIRXDC operation
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 1;   // Configure GPIO63 for SCITXDC operation

    EDIS;
}

