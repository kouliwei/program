/*
 * USER_ADC.h
 *
 *  Created on: 2017-9-18
 *      Author: koukou
 */

#ifndef USER_ADC_H_
#define USER_ADC_H_


#include "DSPTotal.h"

// Determine when the shift to right justify the data takes place
// Only one of these should be defined as 1.
// The other two should be defined as 0.
#define POST_SHIFT   0  // Shift results after the entire sample table is full
#define INLINE_SHIFT 1  // Shift results as the data is taken from the results regsiter
#define NO_SHIFT     0  // Do not shift the results

// ADC start parameters
#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif
#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                  = 2 ADC cycle
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   100  // Sample buffer size

#define	StartADCTrans()	AdcRegs.ADCTRL2.all = 0x2000
#define rate_vol 3.00

extern Uint16 Voltage[2];


void USER_ADC_Init(void);
void Read_Voltage(void);
void PC_ReadVol(void);

#endif /* USER_ADC_H_ */
