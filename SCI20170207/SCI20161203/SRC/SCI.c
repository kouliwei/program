#include "DSPTotal.h"

//#define UART_PRINTF


#ifdef UART_PRINTF
//int     fgetc(register FILE *_fp);
int     fputc(int _c, register FILE *_fp);
#endif

Uint16 SPI_Tx_Buffer[10]= {0,1,2,3,4,5,6,7,8,9};//�������ݻ�����
Uint16 SPI_Rx_Buffer[10]= {9,8,7,6,5,4,3,2,1,0};//�������ݻ�����
int Kp = 4;
int Ki = 3;
int Kd = 0;
Uint16 gl_Distance = 0;
Uint16 PC_Rx_Buffer[RX_BUFFER_SIZE]; //�������ݻ�����
Uint16 AHRS_Rx_Buffer[RX_BUFFER_SIZE]; //�������ݻ�����
Uint16 gl_FlagMotionCycle = 0;
Uint16 Real_PcBuff[RX_BUFFER_SIZE] = {0};
Uint16 Real_AHRSBuff[RX_BUFFER_SIZE] = {0};
Uint16 ReceivedChar = 0;
Uint16 AHRS_RX_Flag = 0;
Uint16 PC_RX_Flag = 0;
Uint16 AUV_State = 1;

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

void main(void)
{
	InitSysCtrl();
	Gpio_Init();
	Sci_Init();
//	USER_SPIInit();
	EPwm_Init();
//	IntTime_Config();
//	Para_Init();
//	StartCpuTimer0();




#if	DEBUG == 0
	Led_Drive(0x01);
	Test();
	Circle_Led();





#elif	DEBUG == 1
	while(1)
    {
		Led_Drive(0x0C);

//		if(index >= 10)
//		{
//			index = 0;
//		}
//		while(SpiaRegs.SPISTS.bit.INT_FLAG == SPI_RECEICEING);
//		SPI_Rx_Buffer[index] = SpiaRegs.SPIRXBUF;
//		while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == SPI_SENDING);  //���ڷ�����
//		SpiaRegs.SPITXBUF = SPI_Tx_Buffer[index];
//		index++;


//		DataInter_AHRS();
//		DataInter_Pc();
//		if(AUV_State != 1)
//		{
//			Motion_Control();
//		}


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




