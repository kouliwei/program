#ifndef USER_I2C_H
#define USER_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DSPTotal.h"





#define I2C_SLAVE_ADDR        0x76
#define I2C_NUMBYTES          4
#define I2C_EEPROM_HIGH_ADDR  0x00
#define I2C_EEPROM_LOW_ADDR   0x30

#define		MS5837_ADDR             0x76
#define    	MS5837_RESET            0x1E
#define    	MS5837_ADC_READ         0x00
#define    	MS5837_PROM_READ        0xA0
#define    	MS5837_CONVERT_D1_256   0x40
#define    	MS5837_CONVERT_D2_256   0x50

// Oversampling options
#define		OSR_256		0
#define		OSR_512   	1
#define		OSR_1024  	2
#define		OSR_2048  	3
#define		OSR_4096  	4
#define     OSR_8192  	5

//define the density of water

#define		DENSITY_FRESHWATER  997
#define		DENSITY_SALTWATER   1029


struct TypeMs5837 {
  Uint32 D1;	//read the raw value of temperature
  Uint32 D2;	//read the raw value of pressure
  float  temperature;	//the post-processed value of temperature
  float  pressure;		//the post-processed value of pressure
  Uint16 CaliPara[8];	//the calibration coefficients
};

extern struct TypeMs5837 Ms5837;
extern struct I2CMSG I2cMsgOut1;
extern struct I2CMSG I2cMsgIn1;
extern struct I2CMSG *CurrentMsgPtr;
extern uint8_t I2C_State;

//interrupt void I2c_int1a_isr(void);
extern void I2CA_Init(void);
//Uint16 I2CA_ReadData(struct I2CMSG *msg);
//Uint16 I2CA_WriteData(struct I2CMSG *msg);
Uint16 WriteCommandToMs5837(uint8_t command);
Uint16 ReadBytesFromMs5837(uint8_t i);
Uint16 GetCalibrationData(void);
void ResetForMs5837(void);
uint8_t Compute_Crc(void);
void Init_Ms5837(void);
void D1ForMs5837(void);
void D2ForMs5837(void);
void Ms5837_Read(void);
Uint16 ReadBytesFromMs5837Type(Uint32 num);
Uint16 ReadBytesFromMs5837Type1(Uint32 num);
static void Ms5837_Compensated(void);
static void Ms5837_RealTemp(void);
static void Ms5837_RealPres(void);
static void Ms5837_RealDepth(void);
static void Ms5837_RealAlti(void);
interrupt void I2c_int1a_isr(void);



#ifdef __cplusplus
}
#endif
#endif
