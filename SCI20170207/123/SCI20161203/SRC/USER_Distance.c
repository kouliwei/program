#include "USER_Distance.h"





void distanceframe(void)
{

}

interrupt void DistanceIstr(void)
{
	static volatile  uint8_t length = 0;
	static uint8_t i = 0;
	uint8_t ReceivedChar = 0;
	if(ScicRegs.SCIRXST.bit.RXERROR == 1)
	{
		ScicRegs.SCICTL1.bit.SWRESET =0;
		ScicRegs.SCICTL1.bit.SWRESET =1;
	}

	ReceivedChar = ScicRegs.SCIRXBUF.all;


	if(i == 0)
	{
		gl_Dis[i] = ReceivedChar;//将PC机发送来的数据存在ReceivedChar中
		i = 1;
	}
	else
	{
		gl_Dis[i] = ReceivedChar;//将PC机发送来的数据存在ReceivedChar中
		LED3_Toggle();
		i = 0;
	}

	ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP8;

}


