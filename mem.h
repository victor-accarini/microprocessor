/*
 * mem.h
 *
 * Created: 2/23/2015 9:37:53 PM
 *  Author: Victor Accarini
 */ 


#ifndef MEM_H_
#define MEM_H_

#define F_CPU 4000000UL
#define ADC_PA_Address 0x4000
#define ADC_PB_Address 0x4001
#define ADC_Start	3
#define ADC_Output	2

#include <avr/io.h>
#include <util/delay.h>

unsigned char ADC_Data, *ADC_DataAddress;

void _Init_Mem();
void _Init_Peripheral();
void _Init_ADC();
void _Init_SPI();
void _ADC_Start();
void EnableInterrupts();
void DisableInterrupts();
void _SPI_Transmit(unsigned char Data);
void _SPI_Send_Data(unsigned int Address, unsigned char Data);

#endif /* MEM_H_ */