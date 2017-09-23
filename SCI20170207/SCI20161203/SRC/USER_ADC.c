/*
 * USER_Spi.c
 *
 *  Created on: 2017-2-3
 *      Author: kou
 */
#include "USER_ADC.h"



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



