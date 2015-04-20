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

#define SPI_Read			0x03
#define SPI_Write			0x02
#define SPI_WriteEnable		0x06
#define SPI_ResetWrEnable	0x04
#define SPI_ReadStatusReg	0x05
#define SPI_WriteStatusReg	0x01

#include <avr/io.h>
#include <util/delay.h>

unsigned char ADC_Data, *ADC_DataAddress;

void _Init_Mem();
void _Init_Peripheral();
void _Init_ADC();
void _EEPROM_Send_Data(unsigned int Address, unsigned char Data);
unsigned char _EEPROM_Receive_Data(unsigned int Address);
void _Enable_SPI();
void _ADC_Start();
void EnableInterrupts();
void DisableInterrupts();
void _SPI_Transmit(unsigned char Data);
void _SPI_Send_Data(unsigned int Address, unsigned char Data);
unsigned char _SPI_Receive_Data(unsigned int Address);

#endif /* MEM_H_ */
