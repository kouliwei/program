/*
 * USER_Spi.c
 *
 *  Created on: 2017-2-3
 *      Author: kou
 */
#include "USER_ADC.h"

Uint16 Voltage[2]={0,0};

void USER_ADC_Init(void)
{
	InitAdc();         // For this example, init the ADC

	// Specific ADC setup for this example:
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0xff;  // Sequential mode: Sample rate   = 1/[(2+ACQ_PS)*ADC clock in ns]
						//                     = 1/(3*40ns) =8.3MHz (for 150 MHz SYSCLKOUT)
						//                     = 1/(3*80ns) =4.17MHz (for 100 MHz SYSCLKOUT)
						// If Simultaneous mode enabled: Sample rate = 1/[(3+ACQ_PS)*ADC clock in ns]
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x1;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run

	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;       // Enable Sequencer override feature
	//	   AdcRegs.ADCCHSELSEQ1.all = 0x0;         // Initialize all ADC channel selects to A0
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x00;
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x01;
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x02;
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x03;
	AdcRegs.ADCCHSELSEQ2.all = 0x0;
	AdcRegs.ADCCHSELSEQ3.all = 0x0;
	AdcRegs.ADCCHSELSEQ4.all = 0x0;
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x4;  // convert and store in 8 results registers
}


void Read_Voltage(void)
{
	while(AdcRegs.ADCST.bit.INT_SEQ1 == 0);
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	Voltage[0]= ( (AdcRegs.ADCRESULT2)>>4);
	Voltage[1] = ( (AdcRegs.ADCRESULT3)>>4);
	DELAY_US(10);
}

void PC_ReadVol(void)
{
	Uint16 checksum = 0;
	Sci_Send_Sing(0xA5,PC_SCI);
	Sci_Send_Sing(0x5A,PC_SCI);
	Sci_Send_Sing(0x08,PC_SCI);
	Sci_Send_Sing(0x08,PC_SCI);
	Sci_Send_Sing(Voltage[0] >> 8 ,PC_SCI);
	Sci_Send_Sing(Voltage[0] & (0x00FF),PC_SCI);
	Sci_Send_Sing(Voltage[1] >> 8 ,PC_SCI);
	Sci_Send_Sing(Voltage[1] & (0x00FF),PC_SCI);
	checksum=0x08+0x08+ Voltage[0] + Voltage[1];
	checksum=checksum%256;
	Sci_Send_Sing(checksum,PC_SCI);
	Sci_Send_Sing(0xAA,PC_SCI);
}




