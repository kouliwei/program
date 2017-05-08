#include "USER_Sensor.h"


int Yaw = 0;  //偏航角
int Pitch = 0;//俯仰
int	Roll = 0; //滚转
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
	static Uint16 state = 0;
	static Uint16 length = 0;
	static Uint16 lencnt = 0;
	static Uint16 sum_check = 0;
	unsigned char ReceivedChar = 0;

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


	if(ScibRegs.SCIRXST.bit.RXERROR == 1)
	{
		ScibRegs.SCICTL1.bit.SWRESET =0;
		ScibRegs.SCICTL1.bit.SWRESET =1;
	}
	ReceivedChar = ScibRegs.SCIRXBUF.all;


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
		Scib_Xmit(num[i]+48);
	}
}



/*
void sensor1Istr(void)
{

//unsigned char ReceivedChar;
 //msg = "\r\n\n\nGreat Doctor Bian!\0";
 Uint16 ReceivedChar;
 for(;;)
     {

        while(SciaRegs.SCIRXST.bit.RXRDY !=1) { } // wait for XRDY =1 for empty state

        // Get character
        ReceivedChar = SciaRegs.SCIRXBUF.all;
        //scib_xmit(ReceivedChar);
        if(ReceivedChar==0xa5)
            {
          	RC_Flag|=b_uart_head; //如果接收到A5 置位帧头标专位
              rx_buffer[rx_wr_index++]=ReceivedChar; //保存这个字节.
            }
            else if(ReceivedChar==0x5a)
                 {
          	       if(RC_Flag&b_uart_head) //如果上一个字节是A5 那么认定 这个是帧起始字节
          	     { rx_wr_index=0;  //重置 缓冲区指针
          		   RC_Flag&=~b_rx_over; //这个帧才刚刚开始收
                   }
                   else //上一个字节不是A5
          		  rx_buffer[rx_wr_index++]=ReceivedChar;
                   RC_Flag&=~b_uart_head; //清帧头标志
                 }
          	    else
          	   { rx_buffer[rx_wr_index++]=ReceivedChar;
          		 RC_Flag&=~b_uart_head;
          		 if(rx_wr_index==rx_buffer[0]) //收够了字节数.
          	     {
          			RC_Flag|=b_rx_over; //置位 接收完整的一帧数据
          			UART2_decision1(); //立即提取数据。
                    if(rx_buffer[1]==0xA2  && RCsensor_Flag==1)
                    {
                       RCsensor_Flag=0;
                       rx_sensor_index=0;
                       break;
                    }

                  }
          	   }

            if(rx_wr_index==RX_BUFFER_SIZE) //防止缓冲区溢出
            rx_wr_index--;
     }
	//frame(0x03);
}*/

//
//void UART2_decision1()
//{
////
//        int i;
//
//
//		if(RC_Flag&b_rx_over){  //已经接收完一帧?
//				RC_Flag&=~b_rx_over; //清标志先
//				//if(Sum_check()){
//				//校验通过
//				if(rx_buffer[1]==0xA1 && RCsensor_Flag==0){ //UART2_ReportIMU 的数据
//					RCsensor_Flag=1;
//					for(i=0;i<rx_wr_index;i++)
//					rxsensor_buffer[rx_sensor_index++]=rx_buffer[i];	//取数据
//	//			 sensor1Istr();
//				}
////				else
////					sensor1Istr();
//			   if(rx_buffer[1]==0xA2 && RCsensor_Flag==1){
//				   rxsensor_buffer[rx_sensor_index++]=0xa5;
//				   rxsensor_buffer[rx_sensor_index++]=0x5a;
//				   for(i=0;i<rx_wr_index;i++)
//				   {
//				   		 rxsensor_buffer[rx_sensor_index++]=rx_buffer[i];	//取数据
//
//				   }
//
//
//
//				   //UART2_sensor_IMU();
////				   RCsensor_Flag=0;
//			   }
////			   else
////				   sensor1Istr();
//		}

//}



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


//中断接收  每隔500ms去执行一次,500ms推进器控制周期
void ISRTimer0(void)
{
	gl_FlagMotionCycle = 1;
	PieCtrlRegs.PIEACK.all |= PIEACK_GROUP1;
	CpuTimer0Regs.TCR.bit.TIF = 1;
	CpuTimer0Regs.TCR.bit.TRB = 1;
//   //UART2_CommandRoute();
//   //ledToggle();
//   //scib_xmit(1);
//    Sensor_analysis();        //50ms获取一次加速度值 对其进行积分获得速度值 作为PID的反馈信号。注意：对传感器的值进行整定归零
//    sumAx += realAx;
//    sumAx = sumAx / 16;
//
//   loopControlVerticalDown();   //垂直闭环控制

}





//
//void loopControlVerticalDown(void)
//{
////	error = setPoint - sumAx;  //此处的ax需要进行归零处理 通过实际测量来进行整定
////	sumError += error;
////	dError = lastError - prevError;
////	prevError = lastError;
////	lastError = error;
////
////	PWMVaule = Kp*error + Ki*sumError + Kd*dError;
////	if (PWMVaule > 10) PWMVaule = 10;
////	if (PWMVaule < -40) PWMVaule = -40;
////	EPwmSetup2(795+PWMVaule);
////	EPwmSetup4(795+PWMVaule);
//
//}




extern void Sensor_Analysis(void)
{
	int temp = 0;
	temp = Real_AHRSBuff[2];
	temp <<= 8;
	temp |= Real_AHRSBuff[3];
	if(temp&0x8000)
	{
		temp = 0 - (temp&0x7fff);
	}else
	{
		temp = (temp&0x7fff);
	}
	Yaw = temp / 10; //偏航角0-3600 对应0-360度

	temp = 0;
	temp = Real_AHRSBuff[4];
	temp <<= 8;
	temp |= Real_AHRSBuff[5];
	if(temp&0x8000){
		temp = 0-(temp&0x7fff);
	} else temp = (temp&0x7fff);
	Pitch = temp / 10; //俯仰-900---900对应-90度---90度

	temp = 0;
	temp = Real_AHRSBuff[6];
	temp <<= 8;
	temp |= Real_AHRSBuff[7];
	if(temp&0x8000)
	{
		temp = 0-(temp&0x7fff);
	}
	else
	{
		temp = (temp&0x7fff);
	}
	Roll = temp / 10; //横滚-1800---1800对应-180度---180度

	temp = 0;
	temp = Real_AHRSBuff[8];
	temp <<= 8;
	temp |= Real_AHRSBuff[9];
	if(temp&0x8000)
	{
	   temp = 0-(temp&0x7fff);
	}
	else
	{
		temp = (temp&0x7fff);
	}
	Alt = temp / 10;	//高度单位m
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

