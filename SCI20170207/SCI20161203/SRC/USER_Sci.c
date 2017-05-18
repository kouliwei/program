#include "USER_Sci.h"

//通过GPIO49的电平来控制485芯片的接收和发送：high-level代表发送；low-level代表接收

#define RX_EN       GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
#define TX_EN       GpioDataRegs.GPBSET.bit.GPIO49 = 1;



#if DEBUG != 0
//接收上位机的数据
//A5 5A 12 A1 08 83 80 43 06 9A 80 03 01 50 27 3E 02 41 1D AA
//A5 5A 16 A2 87 CB 0C 00 BE CB 00 00 00 00 00 00 81 14 00 B6 01 3B 26 AA
/******************************************************************
 	 Function :Uart_Rx
 	 Description:data from PC can be preserved in the Array PC_Rx_Buffer[];
 	 Calls:
 	 Called By:
 	 Input: none
 	 Output:none
 	 Return:none
 	 Others:preserving datas from PC to the Array PC_Rx_Buffer[]
 *****************************************************************/



// A5 5A 05 02 move1 check AA
interrupt void Uart_Rx(void)
{
	static volatile  uint8_t state = 0;
	static volatile  uint8_t length = 0;
	static volatile  uint8_t lencnt = 0;
	static volatile  Uint16 sum_check = 0;
	uint8_t ReceivedChar = 0;


#if PC_SCI == 'A'
	ReceivedChar = SciaRegs.SCIRXBUF.all;
#elif PC_SCI == 'B'
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
		length = ReceivedChar;
		PC_Rx_Buffer[0] = ReceivedChar;
		lencnt = 1;
		sum_check += ReceivedChar;
		state = 3;
		break;
	case 3:
		PC_Rx_Buffer[lencnt++] = ReceivedChar;
		sum_check += ReceivedChar;
		if(lencnt == length - 2)
		{
			state = 4;
		}
		break;
	case 4:
		if(ReceivedChar == (sum_check & 0x00FF))  //接收完一帧数据
		{
			PC_RX_Flag = 1;
		}
		state = 0;
		break;
	}

#if PC_SCI == 'A'
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
#elif PC_SCI == 'B'
	ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
#endif
	PieCtrlRegs.PIEACK.all |= 0x0100;    //
}
#endif

extern void DataInter_AHRS(void)
{
	//保存陀螺仪数据，并且将数据保存在特定的数组中，以便上位机查询返回
   if(AHRS_RX_Flag  == 1)   //data have bee received from the sensor.
   {
	   AHRS_RX_Flag = 0;
	   Store_SensorData();
//		   temp = (AHRS_Rx_Buffer[1]<<8) + AHRS_Rx_Buffer[2];
//		   temp = temp / 10;
//		   scic_msg("yaw_angle:");
//		   TXD_USART_DEC(temp);
//		   scic_msg("\t");
//		   temp1 = 0;
//		   temp1 = AHRS_Rx_Buffer[3];
//		   temp1 <<= 8;
//		   temp1 |= AHRS_Rx_Buffer[4];
//		   if(temp1 & 0x8000)
//		   {
//			   temp = (temp1&0x7fff) / 10;
//			   temp1 = 0-(temp1&0x7fff);
//			   scic_msg("pitch_angle:-");
//		   }else
//		   {
//			   temp1 = (temp1&0x7fff);
//			   temp = temp1 / 10;
//			   scic_msg("pitch_angle:");
//		   }
//		   temp1 = temp1 / 10;   //俯仰
//		   TXD_USART_DEC(temp);
//		   scic_msg("\t");
////
//		   temp1 = 0;
//		   temp1 = AHRS_Rx_Buffer[5];
//		   temp1 <<= 8;
//		   temp1 |= AHRS_Rx_Buffer[6];
//		   if(temp1 & 0x8000)
//		   {
//			   temp = (temp1&0x7fff) / 10;
//			   temp1 = 0-(temp1&0x7fff);
//			   scic_msg("roll_angle:-");
//		   }else
//		   {
//			   temp1 = (temp1&0x7fff);
//			   temp = temp1 / 10;
//			   scic_msg("roll_angle:");
//		   }
//		   temp1 = temp1 / 10;   //俯仰
//		   TXD_USART_DEC(temp);
   }
}

extern void DataInter_Pc(void)
{
	if(PC_RX_Flag == 1)    //data have bee received from the computer.
	{
		//Delay_Nms(50);
		LED1_Toggle();
		PC_RX_Flag = 0;
		Store_PcData(Real_PcBuff,PC_Rx_Buffer);
		if(Real_PcBuff[2] == 2)
		{
			gl_MotionFlag = 0;
		}
		else
		{
			gl_MotionFlag = 1;
		}

		switch(Real_PcBuff[1])
		{
		case 1:                      //单推进器测试
			SingleMotor_Control();
			break;
		case 2: 						//运动类型选择
			Motion_Type();
			break;
		case 3:      				//请求距离信息
			UART_SendDis();
			break;
		case 4:						//推进器整体测试
			TotalMotor_Control();
			break;
		case 6:                     //PID参数设置
			Set_PID();
			break;
		case 0xb1:                   //请求传感器数据
			UART_SendSensor();
			break;
		}
   }
}

extern void UART_SendSensor(void)
{
	Uint16 checksum = 0,i = 0;
	Sci_Send_Sing(0xA5,PC_SCI);
	Sci_Send_Sing(0x5A,PC_SCI);
	for(i = 0;i < 16;i++)
	{
		Sci_Send_Sing(Real_AHRSBuff[i],PC_SCI);
		checksum += Real_AHRSBuff[i];
	}
	checksum &= 0x00FF;
	Sci_Send_Sing(checksum,PC_SCI);
	Sci_Send_Sing(0xAA,PC_SCI);
	checksum = 0;


//	Sci_Send_Sing(0xA5,PC_SCI);
//	Sci_Send_Sing(0x5A,PC_SCI);
//	for(i = 16;i < 36;i++)
//	{
//		Sci_Send_Sing(Real_AHRSBuff[i],PC_SCI);
//		checksum += Real_AHRSBuff[i];
//	}
//	checksum &= 0x00FF;
//	Sci_Send_Sing(checksum,PC_SCI);
//	Sci_Send_Sing(0xAA,PC_SCI);
}


extern void UART_SendDis(void)
{
	Uint16 checksum = 0;
	Sci_Send_Sing(0xA5,PC_SCI);
	Sci_Send_Sing(0x5A,PC_SCI);
	Sci_Send_Sing(0x05,PC_SCI);
	Sci_Send_Sing(0x03,PC_SCI);
	Sci_Send_Sing(gl_Distance,PC_SCI);
	checksum=0x05+0x03+gl_Distance;
	checksum=checksum%256;
	Sci_Send_Sing(checksum,PC_SCI);
	Sci_Send_Sing(0xAA,PC_SCI);
}


extern void UART_Send(void)
{
	Uint16 sum_check = 0,i = 0;
	Sci_Send_Sing(0xA5,PC_SCI);
	Sci_Send_Sing(0x5A,PC_SCI);
	for(i = 0;i < Real_PcBuff[0] - 2;i++)
	{
		Sci_Send_Sing(Real_PcBuff[i],PC_SCI);
		sum_check += Real_PcBuff[i];
	}
	sum_check &= 0x00FF;
	Sci_Send_Sing(sum_check,PC_SCI);
	Sci_Send_Sing(0xAA,PC_SCI);
}



/**********************串口波特率等配置********************/
extern void Sci_Init(void)
{
	Scia_Init();
	Scib_Init();
	Scic_Init();
}
/**************select baud*******************
***************7A0h:2400********************
***************3D0h:4800********************
***************1E7h:9600********************
***************F3h:19200********************
***************79h:38400*********************
***************28h:115200********************/


static void Scia_Init(void)
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
	//SciaRegs.SCICTL1.bit.SWRESET =0;
 	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	//SciaRegs.SCICTL2.all =0x0003;
	SciaRegs.SCICTL2.bit.TXINTENA = 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	#if (CPU_FRQ_150MHZ)
	      SciaRegs.SCIHBAUD    =0x0000;  // 115200 baud @LSPCLK = 37.5MHz.
	      SciaRegs.SCILBAUD    =0x0028;
	#endif
	#if (CPU_FRQ_100MHZ)
      SciaRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
      SciaRegs.SCILBAUD    =0x0044;
	#endif
	SciaRegs.SCICTL1.all =0x0063;  // Relinquish SCI from Reset

}

static void Scib_Init(void)
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    ScibRegs.SCICTL1.bit.SWRESET =0;
 	ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE

	ScibRegs.SCICTL2.bit.TXINTENA =1; //发送中断使能
	ScibRegs.SCICTL2.bit.RXBKINTENA =1;//接收中断使能

	#if (CPU_FRQ_150MHZ)
	      ScibRegs.SCIHBAUD    =0x0000;  // 9600 baud @LSPCLK = 37.5MHz.
	      ScibRegs.SCILBAUD    =0x0028;
	#endif
	#if (CPU_FRQ_100MHZ)
      ScibRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
      ScibRegs.SCILBAUD    =0x0044;
	#endif
	ScibRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}

static void Scic_Init(void)
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

 	ScicRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
	ScicRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
	ScicRegs.SCICTL2.all =0x0003;
	ScicRegs.SCICTL2.bit.TXINTENA = 1;
	ScicRegs.SCICTL2.bit.RXBKINTENA =1;
	#if (CPU_FRQ_150MHZ)
	      ScicRegs.SCIHBAUD    =0x0000;  // 115200 baud @LSPCLK = 37.5MHz.
	      ScicRegs.SCILBAUD    =0x0028;
	#endif
	#if (CPU_FRQ_100MHZ)
      SciaRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
      SciaRegs.SCILBAUD    =0x0044;
	#endif
	ScicRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}

// Transmit a character from the SCI
extern void Scia_Xmit(uint8_t a)
{
    while (SciaRegs.SCICTL2.bit.TXRDY == 0) {}
    SciaRegs.SCITXBUF=a;
}
extern void Scia_Msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        Scia_Xmit(msg[i]);
        i++;
    }
}
extern void Scib_Xmit(uint8_t a)
{
	TX_EN;
	while (ScibRegs.SCICTL2.bit.TXRDY == 0) {}
    ScibRegs.SCITXBUF=a;
    RX_EN;
}

extern void Scib_Msg(char * msg)
{
    int i;
    i = 0;
//	TX_EN;
    while(msg[i] != '\0')
    {
        Scib_Xmit(msg[i]);
        i++;
    }
//	RX_EN;
}

extern void Scic_Xmit(uint8_t a)
{
    while (ScicRegs.SCICTL2.bit.TXRDY == 0) {}
    ScicRegs.SCITXBUF=a;

}

extern void Scic_Msg(char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        Scic_Xmit(msg[i]);
        i++;
    }
}

extern void Sci_Send_Sing(uint8_t temp,...)
{
	char num = 0;
	va_list arg;
	va_start(arg, temp);
	num = va_arg(arg,char);

	switch(num)
	{
	case 'A':
	case 'a':
		Scia_Xmit(temp);
		break;
	case 'B':
	case 'b':
		Scib_Xmit(temp);
		break;
	case 'C':
	case 'c':
		Scic_Xmit(temp);
		break;
	default :
		Scic_Xmit(temp);
		break;
	}

}


extern void	Sci_Send(char *msg,...)
{
	char num = 0;
	va_list arg;
	va_start(arg, msg);
	num = va_arg(arg,char);

	switch(num)
	{
	case 'A':
	case 'a':
		Scia_Msg(msg);
		break;

	case 'B':
	case 'b':
		Scib_Msg(msg);
		break;
	case 'C':
	case 'c':
		Scic_Msg(msg);
		break;
	default :
		Scic_Msg(msg);
		break;
	}
}


extern void TXD_USART_BIN(char temp,uint8_t data)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		if(data&(1<<(7-i)))
		{
			if(temp == 'A' || temp == 'a')
			{
				Sci_Send_Sing('1','A');
			}
			else if(temp == 'B' || temp == 'b')
			{
				Sci_Send_Sing('1','B');
			}
			else
			{
				if(temp == 'C' || temp == 'c')
				{
					Sci_Send_Sing('1','C');
				}
			}
		}
		else
		{
			if(temp == 'A' || temp == 'a')
			{
				Sci_Send_Sing('0','A');
			}
			else if(temp == 'B' || temp == 'b')
			{
				Sci_Send_Sing('0','B');
			}
			else
			{
				if(temp == 'C' || temp == 'c')
				{
					Sci_Send_Sing('0','C');
				}
			}
		}

	}

	switch(temp)
	{
	case 'A':
	case 'a':
		Sci_Send("\r\n",'A');
		break;
	case 'B':
	case 'b':
		Sci_Send("\r\n",'B');
		break;
	case 'C':
	case 'c':
		Sci_Send("\r\n",'C');
		break;
	default :
		Sci_Send("\r\n");
	}

}


void TXD_USART_DEC(Uint16 data)
{
	Uint16 num[5]={0},m=0;
	int16 i=0;
	for(i=0;;)  //将data的每一位倒序存入num[5]的数组中，例如data=3456,则num[5]={6,5,4,3,0};for循环后i=3
	{
		m=data/10;
		num[i]=data%10;
		data=m;
		if(data==0)
			break;
		else
			i++;
	}

	for(;i>=0;i--)
	{
		Sci_Send_Sing(num[i]+48,PC_SCI);
	}
}





