#include "USER_Distance.h"





void distanceframe(void)
{

}

interrupt void DistanceIstr(void)
{
	static volatile  uint8_t state = 0;
	static volatile	 uint8_t i = 0;
	static volatile  Uint16 sum_check = 0;
	uint8_t ReceivedChar = 0;

	if(ScicRegs.SCIRXST.bit.RXERROR == 1)
	{
		ScicRegs.SCICTL1.bit.SWRESET =0;
		ScicRegs.SCICTL1.bit.SWRESET =1;
	}

	ReceivedChar = ScicRegs.SCIRXBUF.all;


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
		sum_check = 0;
		i = 0;
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
		gl_Dis[i] = ReceivedChar;
		sum_check += ReceivedChar;
		i++;
		if(i == 2)
		{
			state = 3;
		}
		break;
	case 3:
		if(ReceivedChar == (sum_check & 0x00FF))  //接收完一帧数据
		{
			LED3_Toggle();
		}
		//if error occurs, reset the distance
		else
		{
			gl_Dis[0] = 0;
			gl_Dis[1] = 0;
		}
		state = 0;
		break;
	}


	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP8;

}


