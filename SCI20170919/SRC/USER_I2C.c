#include "USER_I2C.h"

float Real_Temp=0;
float Real_Pres=0;
float Real_Depth=0;
int Real_Depth_Temp = 0;
float Real_Alti=0;
uint8_t I2C_State = 0;
struct TypeMs5837 Ms5837={0,
						  0,
                          0,
                          0,
                          0,
						  0,
						  0,
						  0,
						  0,
						  0,
						  0,
						  0};                  // Msg Byte 14

struct I2CMSG I2cMsgOut1={I2C_MSGSTAT_SEND_WITHSTOP,
						  I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_EEPROM_HIGH_ADDR,
                          I2C_EEPROM_LOW_ADDR,
                          0x12,                   // Msg Byte 1
                          0x34,                   // Msg Byte 2
                          0x56,                   // Msg Byte 3
                          0x78,                   // Msg Byte 4
                          0x9A,                   // Msg Byte 5
                          0xBC,                   // Msg Byte 6
                          0xDE,                   // Msg Byte 7
                          0xF0,                   // Msg Byte 8
                          0x11,                   // Msg Byte 9
                          0x10,                   // Msg Byte 10
                          0x11,                   // Msg Byte 11
                          0x12,                   // Msg Byte 12
                          0x13,                   // Msg Byte 13
                          0x12};                  // Msg Byte 14




struct I2CMSG I2cMsgIn1={ I2C_MSGSTAT_SEND_NOSTOP,
                          I2C_SLAVE_ADDR,
                          I2C_NUMBYTES,
                          I2C_EEPROM_HIGH_ADDR,
                          I2C_EEPROM_LOW_ADDR};


struct I2CMSG *CurrentMsgPtr;				// Used in interrupts




//interrupt void I2c_int1a_isr(void)
//{
//
//}

void I2CA_Init(void)
{
	// Initialize I2C
	I2caRegs.I2CSAR = 0x0050;		// Slave address - EEPROM control code

	#if (CPU_FRQ_150MHZ)             // Default - For 150MHz SYSCLKOUT
		I2caRegs.I2CPSC.all = 14;   // Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz)
	#endif
	#if (CPU_FRQ_100MHZ)             // For 100 MHz SYSCLKOUT
		I2caRegs.I2CPSC.all = 9;	    // Prescaler - need 7-12 Mhz on module clk (100/10 = 10MHz)
	#endif

	I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero
	I2caRegs.I2CIER.all = 0x24;		// Enable SCD & ARDY interrupts

	I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
									// Stop I2C when suspended

	I2caRegs.I2CFFTX.all = 0x6000;	// Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040;	// Enable RXFIFO, clear RXFFINT,

	return;
}

void Init_Ms5837(void)
{
	uint8_t Err=0;
	ResetForMs5837();
	Delay_Nms(10);
	Err = GetCalibrationData();
	if(Err == FALSE)
	{
		  asm ("      ESTOP0");
	}
}

void Ms5837_Read(void)
{

	D1ForMs5837();
	Delay_Nms(25);
	WriteCommandToMs5837(MS5837_ADC_READ);
	ReadBytesFromMs5837Type(Ms5837.D1);
	while(I2C_State & 0x01);
	D2ForMs5837();
	Delay_Nms(25);
	WriteCommandToMs5837(MS5837_ADC_READ);
	ReadBytesFromMs5837Type1(Ms5837.D2);
	while(I2C_State & 0x02);
	Ms5837_Compensated();
	Ms5837_RealTemp();
	Ms5837_RealPres();
	Ms5837_RealDepth();
	Ms5837_RealAlti();
	Real_Depth_Temp = (int)(Real_Depth*1000);

	Sci_Send_Sing((Real_Depth_Temp & 0xFF00)>>8,'c');
	Sci_Send_Sing((Real_Depth_Temp & 0x00FF),'c');
}



static void Ms5837_RealTemp(void)
{
	Real_Temp=Ms5837.temperature/100.0;
}


//default unit :mbar
static void Ms5837_RealPres(void)
{
	Real_Pres=Ms5837.pressure*1.0;
}


//compute the depth in the fresh water
//change DENSITY_FRESHWATER into DENSITY_SALTWATER to compute the depth in the salt water
static void Ms5837_RealDepth(void)
{
	Real_Depth=(Real_Pres*100-101300)/(DENSITY_FRESHWATER*9.80665);
}


static void Ms5837_RealAlti(void)
{
	Real_Alti=(1-pow((Real_Pres/1013.25),0.190284))*145366.45*0.3048;
}


static void Ms5837_Compensated(void)
{
	int32 DT=0;
	int32 TEMP=0;
	int64 OFF[3]={0,0,0};
	int64 SENS[3]={0,0,0};
	int32 Pre=0;
	float Ti=0;

	DT = Ms5837.D2-Ms5837.CaliPara[5]*256;
	SENS[0] = Ms5837.CaliPara[1]*32768+(Ms5837.CaliPara[3]*DT)/256;
	OFF[0] = Ms5837.CaliPara[2]*65536+(Ms5837.CaliPara[4]*DT)/128;
	Pre = (Ms5837.D1*SENS[0]/2097152 -OFF[0])/(8192);
	TEMP = 2000+DT*Ms5837.CaliPara[6]/8388608;

	// Second order compensation
	if ((TEMP/100) < 20)
	{
		Ti = (3*DT*DT)/(8589934592);
		OFF[1] = (3*(TEMP-2000)*(TEMP-2000))/2;
		SENS[1] = (5*(TEMP-2000)*(TEMP-2000))/8;
		if ((TEMP/100) < -15)
		{
			 OFF[1] = OFF[1]+7*(TEMP+1500l)*(TEMP+1500);
			 SENS[1] = SENS[1]+4*(TEMP+1500l)*(TEMP+1500);
		}
	}
	else if ((TEMP/100) >= 20)
	{
        Ti = 2*(DT*DT)/(137438953472);
        OFF[1] = (1*(TEMP-2000)*(TEMP-2000))/16;
        SENS[1] = 0;
	}

	OFF[2] = OFF[0]-OFF[1];
	SENS[2] = SENS[0]-SENS[1];

	Ms5837.temperature = (TEMP-Ti);
	Ms5837.pressure = (((Ms5837.D1*SENS[2])/2097152-OFF[2])/8192)/10.0;
}



void ResetForMs5837(void)
{
	WriteCommandToMs5837(MS5837_RESET);
}

void D1ForMs5837(void)
{
	WriteCommandToMs5837(MS5837_CONVERT_D1_256);
}

void D2ForMs5837(void)
{
	WriteCommandToMs5837(MS5837_CONVERT_D2_256);
}

Uint16 WriteCommandToMs5837(uint8_t command)
{
		I2C_State = 0;

	   // Wait until the STP bit is cleared from any previous master communication.
	   // Clearing of this bit by the module is delayed until after the SCD bit is
	   // set. If this bit is not checked prior to initiating a new message, the
	   // I2C could get confused.
	   if (I2caRegs.I2CMDR.bit.STP == 1)
	   {
	      return I2C_STP_NOT_READY_ERROR;
	   }

	   // Setup slave address
	   I2caRegs.I2CSAR = MS5837_ADDR;

	   // Check if bus busy
	   if (I2caRegs.I2CSTR.bit.BB == 1)
	   {
	      return I2C_BUS_BUSY_ERROR;
	   }

	   // Setup number of bytes to send
	   // MsgBuffer + Address
	   I2caRegs.I2CCNT = 1;
	   I2caRegs.I2CDXR = command;

	   I2caRegs.I2CMDR.bit.BC = 0;  //8位数据发送
	   I2caRegs.I2CMDR.bit.STP = 1;
	   I2caRegs.I2CMDR.bit.MST = 1;
	   I2caRegs.I2CMDR.bit.TRX = 1;
	   I2caRegs.I2CMDR.bit.XA = 0;
	   I2caRegs.I2CMDR.bit.RM = 0;
	   I2caRegs.I2CMDR.bit.DLB = 0;
	   I2caRegs.I2CMDR.bit.FDF = 0;
	   I2caRegs.I2CMDR.bit.STB = 1;


	   // Setup data to send


	   // Send start as master transmitter
//	   I2caRegs.I2CMDR.all = 0x6E20;


	   I2caRegs.I2CMDR.bit.STT = 1;
	   Delay_Nms(10);

//	   while(I2caRegs.I2CISRC.bit.INTCODE != 0x06);
//	   I2caRegs.I2CISRC.bit.INTCODE = 0;
//	   while(I2caRegs.I2CSTR.bit.SCD == 0)
//	   {
//		   if(I2caRegs.I2CISRC.bit.INTCODE == 0x03)
//		   {
//			   if(I2caRegs.I2CSTR.bit.NACK == 1)
//			   {
//				   I2caRegs.I2CMDR.bit.STP = 1;
//				   I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
//			   }
//		   }
//
//	   }
	   while(I2caRegs.I2CSTR.bit.SCD == 0);
	   I2caRegs.I2CSTR.bit.SCD = 1;
	   return I2C_SUCCESS;

}

Uint16 ReadBytesFromMs5837(uint8_t i)
{
	// Wait until the STP bit is cleared from any previous master communication.
	// Clearing of this bit by the module is delayed until after the SCD bit is
	// set. If this bit is not checked prior to initiating a new message, the
	// I2C could get confused.
	if (I2caRegs.I2CMDR.bit.STP == 1)
	{
	  return I2C_STP_NOT_READY_ERROR;
	}

	I2caRegs.I2CSAR = MS5837_ADDR;

	I2caRegs.I2CCNT = 2;	// Setup how many bytes to expect
//	I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver
	I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver

//	while(I2caRegs.I2CSTR.bit.SCD == 0)
//	{
//		if(I2caRegs.I2CISRC.bit.INTCODE == 0x03)
//		{
//		   if(I2caRegs.I2CSTR.bit.NACK == 1)
//		   {
//			   I2caRegs.I2CMDR.bit.STP = 1;
//			   I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
//		   }
//		}
//	}
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;
	Ms5837.CaliPara[i] = I2caRegs.I2CDRR;
	Ms5837.CaliPara[i] = (Ms5837.CaliPara[i]<<8) + I2caRegs.I2CDRR;
	return I2C_SUCCESS;
}

Uint16 ReadBytesFromMs5837Type(Uint32 num)
{
	I2C_State = 1;

	// Wait until the STP bit is cleared from any previous master communication.
	// Clearing of this bit by the module is delayed until after the SCD bit is
	// set. If this bit is not checked prior to initiating a new message, the
	// I2C could get confused.
	if (I2caRegs.I2CMDR.bit.STP == 1)
	{
	  return I2C_STP_NOT_READY_ERROR;
	}

	I2caRegs.I2CSAR = MS5837_ADDR;

	I2caRegs.I2CCNT = 3;	// Setup how many bytes to expect
	I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver
	return I2C_SUCCESS;
//	while(I2caRegs.I2CSTR.bit.SCD == 0);
//	I2caRegs.I2CSTR.bit.SCD = 1;
//	num = I2caRegs.I2CDRR;
//	num = (num<<8) + I2caRegs.I2CDRR;
//	num = (num<<8) + I2caRegs.I2CDRR;
//	return I2C_SUCCESS;
}

Uint16 ReadBytesFromMs5837Type1(Uint32 num)
{
	I2C_State = 2;

	// Wait until the STP bit is cleared from any previous master communication.
	// Clearing of this bit by the module is delayed until after the SCD bit is
	// set. If this bit is not checked prior to initiating a new message, the
	// I2C could get confused.
	if (I2caRegs.I2CMDR.bit.STP == 1)
	{
	  return I2C_STP_NOT_READY_ERROR;
	}

	I2caRegs.I2CSAR = MS5837_ADDR;

	I2caRegs.I2CCNT = 3;	// Setup how many bytes to expect
	I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver

	return I2C_SUCCESS;
//	while(I2caRegs.I2CSTR.bit.SCD == 0);
//	I2caRegs.I2CSTR.bit.SCD = 1;
//	num = I2caRegs.I2CDRR;
//	num = (num<<8) + I2caRegs.I2CDRR;
//	num = (num<<8) + I2caRegs.I2CDRR;
//	return I2C_SUCCESS;
}

Uint16 GetCalibrationData(void)
{
	uint8_t crc=0,crc_temp=0;
	volatile uint8_t i=0;
	for(i=0; i< 7; i++)
	{
		WriteCommandToMs5837(MS5837_PROM_READ + 2*i);
		ReadBytesFromMs5837(i);
		Delay_Nms(100);
	}

	crc = (Ms5837.CaliPara[0]&0xF000)>>12;
	crc_temp = Compute_Crc();
	if(crc == crc_temp)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

uint8_t Compute_Crc(void)
{
	uint8_t 	cnt; // simple counter
	Uint16 		n_rem=0; // crc reminder
	uint8_t 	n_bit;
	Ms5837.CaliPara[0]=((Ms5837.CaliPara[0]) & 0x0FFF); // CRC byte is replaced by 0
	for (cnt = 0; cnt < 16; cnt++) // operation is performed on bytes
	{ // choose LSB or MSB
		if (cnt%2==1)
			n_rem ^= (unsigned short) ((Ms5837.CaliPara[cnt>>1]) & 0x00FF);
		else
			n_rem ^= (unsigned short) (Ms5837.CaliPara[cnt>>1]>>8);
		for (n_bit = 8; n_bit > 0; n_bit--)
		{
			if (n_rem & (0x8000))
				n_rem = (n_rem << 1) ^ 0x3000;
			else
				n_rem = (n_rem << 1);
		}
	}
	n_rem= ((n_rem >> 12) & 0x000F); // final 4-bit reminder is CRC code
	return (n_rem ^ 0x00);
}

interrupt void I2c_int1a_isr(void)
{
	Uint16 IntSource;
	if(I2C_State == 1)
	{
		IntSource = I2caRegs.I2CISRC.all;
		if(IntSource == I2C_SCD_ISRC)
		{
			Ms5837.D1 = I2caRegs.I2CDRR;
			Ms5837.D1 = (Ms5837.D1 <<8) + I2caRegs.I2CDRR;
			Ms5837.D1 = (Ms5837.D1 <<8) + I2caRegs.I2CDRR;

		}

	}
	else if (I2C_State == 2)
	{
		IntSource = I2caRegs.I2CISRC.all;
		if(IntSource == I2C_SCD_ISRC)
		{
			Ms5837.D2 = I2caRegs.I2CDRR;
			Ms5837.D2 = (Ms5837.D2 <<8) + I2caRegs.I2CDRR;
			Ms5837.D2 = (Ms5837.D2 <<8) + I2caRegs.I2CDRR;
		}
	}
	I2C_State = 0;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}


//Uint16 I2CA_WriteData(struct I2CMSG *msg)
//{
//   Uint16 i;
//
//   // Wait until the STP bit is cleared from any previous master communication.
//   // Clearing of this bit by the module is delayed until after the SCD bit is
//   // set. If this bit is not checked prior to initiating a new message, the
//   // I2C could get confused.
//   if (I2caRegs.I2CMDR.bit.STP == 1)
//   {
//      return I2C_STP_NOT_READY_ERROR;
//   }
//
//   // Setup slave address
//   I2caRegs.I2CSAR = msg->SlaveAddress;
//
//   // Check if bus busy
//   if (I2caRegs.I2CSTR.bit.BB == 1)
//   {
//      return I2C_BUS_BUSY_ERROR;
//   }
//
//   // Setup number of bytes to send
//   // MsgBuffer + Address
//   I2caRegs.I2CCNT = msg->NumOfBytes+2;
//
//   // Setup data to send
//   I2caRegs.I2CDXR = msg->MemoryHighAddr;
//   I2caRegs.I2CDXR = msg->MemoryLowAddr;
//// for (i=0; i<msg->NumOfBytes-2; i++)
//   for (i=0; i<msg->NumOfBytes; i++)
//
//   {
//      I2caRegs.I2CDXR = *(msg->MsgBuffer+i);
//   }
//
//   // Send start as master transmitter
//   I2caRegs.I2CMDR.all = 0x6E20;
//
//   return I2C_SUCCESS;
//}




//Uint16 I2CA_ReadData(struct I2CMSG *msg)
//{
//   // Wait until the STP bit is cleared from any previous master communication.
//   // Clearing of this bit by the module is delayed until after the SCD bit is
//   // set. If this bit is not checked prior to initiating a new message, the
//   // I2C could get confused.
//   if (I2caRegs.I2CMDR.bit.STP == 1)
//   {
//      return I2C_STP_NOT_READY_ERROR;
//   }
//
//   I2caRegs.I2CSAR = msg->SlaveAddress;
//
//   if(msg->MsgStatus == I2C_MSGSTAT_SEND_NOSTOP)
//   {
//      // Check if bus busy
//      if (I2caRegs.I2CSTR.bit.BB == 1)
//      {
//         return I2C_BUS_BUSY_ERROR;
//      }
//      I2caRegs.I2CCNT = 2;
//      I2caRegs.I2CDXR = msg->MemoryHighAddr;
//      I2caRegs.I2CDXR = msg->MemoryLowAddr;
//      I2caRegs.I2CMDR.all = 0x2620;			// Send data to setup EEPROM address
//   }
//   else if(msg->MsgStatus == I2C_MSGSTAT_RESTART)
//   {
//      I2caRegs.I2CCNT = msg->NumOfBytes;	// Setup how many bytes to expect
//      I2caRegs.I2CMDR.all = 0x2C20;			// Send restart as master receiver
//   }
//
//   return I2C_SUCCESS;
//}


