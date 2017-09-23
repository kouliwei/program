#include "DSPTotal.h"

//#define UART_PRINTF


#ifdef UART_PRINTF
//int     fgetc(register FILE *_fp);
int     fputc(int _c, register FILE *_fp);
#endif

uint8_t Control_Time = 10;
int8_t	Buff_Total[200][20];
uint8_t gl_TimeFlag[5]  = {0,0,0,0,0};
uint8_t	gl_TempFlag[10] = {0,0,0,0,0,0,0,0,0,0};
uint8_t gl_Dis[2] = {0,0};
float	AHRS_Data[12]={0,0,0,0,0,0,0,0,0,0,0,0};  //yaw,pitch,roll,ax ay az gx gy gz 实测数值
uint8_t gl_MotionFlag = 0;
int Force[4] = {0,0,0,0};
Uint16 SPI_Tx_Buffer[10]= {0,1,2,3,4,5,6,7,8,9};//接收数据缓冲区
Uint16 SPI_Rx_Buffer[10]= {9,8,7,6,5,4,3,2,1,0};//接收数据缓冲区
float KP = 40;
float KI = 0.5;
float KD = 0;
Uint16 PC_Rx_Buffer[RX_BUFFER_SIZE]; //接收数据缓冲区
Uint16 AHRS_Rx_Buffer[RX_BUFFER_SIZE]; //接收数据缓冲区
Uint16 gl_FlagMotionCycle = 0;
Uint16 Real_PcBuff[RX_BUFFER_SIZE] = {0};
Uint16 Real_AHRSBuff[RX_BUFFER_SIZE] = {0};
Uint16 AHRS_RX_Flag = 0;
Uint16 PC_RX_Flag = 0;
Uint16 AUV_State = 1;
Uint16 Last_AUV_State = 1;

#if	DEBUG == 0
int sum(int cnt,...){
    int sum1=0;
    int i;
    va_list ap;
    va_start(ap,cnt);
    for(i=0;i<cnt;++i)
    	sum1+=va_arg(ap,int);
    va_end(ap);
    return sum1;
}
#endif

void main(void)
{
 	InitSysCtrl();
	Gpio_Init();
	Sci_Init();
//	USER_SPIInit();
	EPwm_Init();
	IntTime_Config();
	Para_Init();
	StartCpuTimer0();



#if	DEBUG == 0

#elif	DEBUG == 1
	while(1)
    {

		//Led_Drive(0x0C);
//		if(index >= 10)
//		{
//			index = 0;
//		}
//		while(SpiaRegs.SPISTS.bit.INT_FLAG == SPI_RECEICEING);
//		SPI_Rx_Buffer[index] = SpiaRegs.SPIRXBUF;
//		while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == SPI_SENDING);  //正在发送中
//		SpiaRegs.SPITXBUF = SPI_Tx_Buffer[index];
//		index++;


		DataInter_AHRS();
		DataInter_Pc();
		if(AUV_State != 1)
		{
			Motion_Control();
			if(AUV_State == 8 || AUV_State == 9)
			{
				MOTOR_TRAN();
			}
			else
			{
				Motor_Out();
			}
		}
    }
#endif
}





#ifdef UART_PRINTF
int   fputc(int _c, register FILE *_fp)
{
	Scic_Xmit(_c);
	return _c;
}

//int   fgetc(register FILE *_fp)
//{
//	while(ScicRegs.SCIRXST.bit.RXRDY !=1)
//	{
//
//	}
//	return ScicRegs.SCIRXBUF.all;
//
//}
#endif




