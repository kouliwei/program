#include "USER_Sensor.h"


float Real_Yaw = 0;  //偏航角
float Real_Pitch = 0;//俯仰
float Real_Roll = 0; //滚转
int	Alt = 0;  //高度
int	Tempr = 0;//温度
int	Press = 0;//气压

//陀螺仪数据类型
//A5 5A 12 A1 08 83 80 43 06 9A 80 03 01 50 27 3E 02 41 1D AA
//A5 5A 16 A2 87 CB 0C 00 BE CB 00 00 00 00 00 00 81 14 00 B6 01 3B 26 AA
/******************************************************************
 	 Function :Uart_AHRS
 	 Description:data from AHRS can be preserved in the Array AHRS_Rx_Buffer[];
 	 Calls:
 	 Called By:
 	 Input: none
 	 Output:none
 	 Return:none
 	 Others:preserving datas from AHRS to the Array Rx_Buffer[]
 *****************************************************************/

#if DEBUG !=0

interrupt void Uart_AHRS(void)
{
	static volatile  uint8_t state = 0;
	static volatile  uint8_t length = 0;
	static volatile  uint8_t lencnt = 0;
	static volatile  Uint16 sum_check = 0;
	uint8_t ReceivedChar = 0;

#if	AHRS_SCI == 'A'
	if(SciaRegs.SCIRXST.bit.RXERROR == 1)
	{
		SciaRegs.SCICTL1.bit.SWRESET =0;
		SciaRegs.SCICTL1.bit.SWRESET =1;
	}
	ReceivedChar = SciaRegs.SCIRXBUF.all;
#elif AHRS_SCI == 'B'
	if(ScibRegs.SCIRXST.bit.RXERROR == 1)
	{
		ScibRegs.SCICTL1.bit.SWRESET =0;
		ScibRegs.SCICTL1.bit.SWRESET =1;
	}
	ReceivedChar = ScibRegs.SCIRXBUF.all;
#endif



	switch(state)
	{
	case 0:
		if(ReceivedChar == 0xA5)
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
		length = 0;
		lencnt = 0;
		sum_check = 0;
		break;
	case 1:
		if(ReceivedChar == 0x5A)
		{
			state = 2;
		}
		else
		{
			state = 0;
		}
		break;
	case 2:
		if(ReceivedChar == 0x12)
		{
			state = 3;
			length = ReceivedChar;
			AHRS_Rx_Buffer[lencnt++] = ReceivedChar;
			sum_check += ReceivedChar;
		}
		else
		{
			state = 0;
		}
		break;
	case 3:
		AHRS_Rx_Buffer[lencnt++] = ReceivedChar;
		sum_check += ReceivedChar;
		if(lencnt == length - 2)
		{
			state = 4;
		}
		break;
	case 4:
		if(ReceivedChar == (sum_check & 0x00FF))  //累加和校验
		{
			state = 5;
		}
		else
		{
			state = 0;
		}
		break;
	case 5:
		if(ReceivedChar == 0xAA)
		{
			state = 6;
		}
		else
		{
			state = 0;
		}
		break;
	case 6:
		if(ReceivedChar == 0xA5)
		{
			state = 7;
		}
		else
		{
			state = 0;
		}
		length = 0;
		lencnt = 0;
		sum_check = 0;
		break;
	case 7:
		if(ReceivedChar == 0x5A)
		{
			state = 8;
		}
		else
		{
			state = 0;
		}
		break;
	case 8:
		if(ReceivedChar == 0x16)
		{
			state = 9;
			length = ReceivedChar;
			AHRS_Rx_Buffer[lencnt+16] = ReceivedChar;
			lencnt++;
			sum_check += ReceivedChar;
		}
		else
		{
			state = 0;
		}
		break;
	case 9:
		AHRS_Rx_Buffer[lencnt+16] = ReceivedChar;
		lencnt++;
		sum_check += ReceivedChar;
		if(lencnt == length - 2)
		{
			state = 10;
		}
		break;
	case 10:
		if(ReceivedChar == (sum_check & 0x00FF))  //累加和校验
		{
			AHRS_RX_Flag = 1;
			LED2_Toggle();
		}
		state = 0;
		length = 0;
		lencnt = 0;
		sum_check = 0;
		break;
	}

#if	AHRS_SCI == 'A'
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
#elif AHRS_SCI == 'B'
	ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
#endif
	PieCtrlRegs.PIEACK.all |= 0x0100;
}

#endif

//中断接收  每隔500ms去执行一次,500ms推进器控制周期
void ISRTimer0(void)
{
	LED3_Toggle();
	gl_FlagMotionCycle = 1;
	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
	CpuTimer0Regs.TCR.bit.TIF = 1;
	CpuTimer0Regs.TCR.bit.TRB = 1;
}


////传感器X轴标定  -16038~16814
//void Sensor_analysis()
//{
////	int temp = 0;
////	temp = rxsensor_buffer[22];
////	temp <<= 8;
////	temp |= rxsensor_buffer[23];
////	if(temp&0x8000)
////	{
////		temp = 0-(temp&0x7fff);
////		realAx = temp / 100;
////	}
////	else
////	{
////		 temp = (temp&0x7fff);
////		 realAx = temp / 100;
////	}
//
//}








extern void Sensor_Analysis(void)
{
//	int temp = 0;
//	temp = Real_AHRSBuff[2];
//	temp <<= 8;
//	temp |= Real_AHRSBuff[3];
//	if(temp&0x8000)
//	{
//		temp = 0 - (temp&0x7fff);
//	}else
//	{
//		temp = (temp&0x7fff);
//	}
//	Yaw = temp / 10; //偏航角0-3600 对应0-360度
//
//	temp = 0;
//	temp = Real_AHRSBuff[4];
//	temp <<= 8;
//	temp |= Real_AHRSBuff[5];
//	if(temp&0x8000){
//		temp = 0-(temp&0x7fff);
//	} else temp = (temp&0x7fff);
//	Pitch = temp / 10; //俯仰-900---900对应-90度---90度
//
//	temp = 0;
//	temp = Real_AHRSBuff[6];
//	temp <<= 8;
//	temp |= Real_AHRSBuff[7];
//	if(temp&0x8000)
//	{
//		temp = 0-(temp&0x7fff);
//	}
//	else
//	{
//		temp = (temp&0x7fff);
//	}
//	Roll = temp / 10; //横滚-1800---1800对应-180度---180度
//
//	temp = 0;
//	temp = Real_AHRSBuff[8];
//	temp <<= 8;
//	temp |= Real_AHRSBuff[9];
//	if(temp&0x8000)
//	{
//	   temp = 0-(temp&0x7fff);
//	}
//	else
//	{
//		temp = (temp&0x7fff);
//	}
//	Alt = temp / 10;	//高度单位m
//
//	temp = 0;
//	temp = Real_AHRSBuff[10];
//	temp <<= 8;
//	temp |= Real_AHRSBuff[11];
//	if(temp&0x8000)
//	{
//		temp = 0-(temp&0x7fff);
//	}else
//	{
//		temp = (temp&0x7fff);
//		//tempr=(float)temp / 10.0f;//温度
//	}
//	tempr = temp / 10;
//
//	temp = 0;
//	temp = Real_AHRSBuff[12];
//	temp <<= 8;
//	temp |= Real_AHRSBuff[13];
//	if(temp&0x8000)
//	{
//		temp = 0-(temp&0x7fff);
//	}
//	else
//	{
//		temp = (temp&0x7fff);
//	}
//		//press=(float)temp * 10.0f;//气压
//	press = temp;

//	temp = 0;
//	temp = rx_buffer[22];
//	temp <<= 8;
//	temp |= rx_buffer[23];
//	if(temp&0x8000){
//		temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	ax=temp;//加速度计 X轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[24];
//	temp <<= 8;
//	temp |= rx_buffer[25];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	ay=temp;//加速度计 Y轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[26];
//	temp <<= 8;
//	temp |= rx_buffer[27];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	az=temp;//加速度计 Z轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[28];
//	temp <<= 8;
//	temp |= rx_buffer[29];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	gx=temp;//陀螺仪 X轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[30];
//	temp <<= 8;
//	temp |= rx_buffer[31];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	gy=temp;//陀螺仪 Y轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[32];
//	temp <<= 8;
//	temp |= rx_buffer[33];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	gz=temp;//陀螺仪 Z轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[34];
//	temp <<= 8;
//	temp |= rx_buffer[35];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	hx=temp;//磁力计 X轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[36];
//	temp <<= 8;
//	temp |= rx_buffer[37];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	hy=temp;//磁力计 Y轴的ADC值
//
//	temp = 0;
//	temp = rx_buffer[18];
//	temp <<= 8;
//	temp |= rx_buffer[19];
//	if(temp&0x8000){
//	temp = 0-(temp&0x7fff);
//	}else temp = (temp&0x7fff);
//	hz=temp;//磁力计 Z轴的ADC值
}

