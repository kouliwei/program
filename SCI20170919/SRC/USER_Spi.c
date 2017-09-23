/*
 * USER_Spi.c
 *
 *  Created on: 2017-2-3
 *      Author: kou
 */
#include "USER_Spi.h"


void USER_SPIInit(void)
{
	InitSpiGpio();
	USER_SPI_Init();

}

void USER_SPI_Init(void)
{
	SpiaRegs.SPICCR.bit.SPISWRESET=0;
	SpiaRegs.SPICCR.bit.CLKPOLARITY=SPI_CPOL_Low;
	SpiaRegs.SPICTL.bit.TALK=1;				//��������
	SpiaRegs.SPICTL.bit.CLK_PHASE=SPI_CPHA_2Edge;
	SpiaRegs.SPICTL.bit.MASTER_SLAVE=SPI_Mode_Slave;
	SpiaRegs.SPICCR.bit.SPICHAR=SPI_DataSize_16b;
	//SpiaRegs.SPICCR.bit.SPILBK = 1;		 					//����SPI_LOOP�ػ�����,ֻ��master����
	SpiaRegs.SPIBRR =0x007F;								//���ò����ʣ����ڴӻ���˵û��
	SpiaRegs.SPICCR.bit.SPISWRESET=1;
	SpiaRegs.SPIPRI.bit.FREE=1;

}



