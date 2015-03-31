/*
 * mem.c
 *
 * Created: 2/23/2015 9:38:36 PM
 *  Author: Victor Accarini
 */ 

#include "mem.h"
#include <avr/interrupt.h>

#define SPI_Read			0x03
#define SPI_Write			0x02
#define SPI_WriteEnable		0x06
#define SPI_ResetWrEnable	0x04
#define SPI_ReadStatusReg	0x05
#define SPI_WriteStatusReg	0x01

void _Init_Mem()
{
	MCUCR = MCUCR | (1 << SRE);
}

void _Init_Peripheral()
{
	unsigned char *address;
	address = (unsigned char*) 0x4003;
	(*address) = (unsigned char)0b10000010; //Set all the peripherals as outputs except B
}

void _Init_ADC()
{
	PORTB = PORTB & ~(1 << ADC_Output);
	PORTB = PORTB & ~(1 << ADC_Start);
	// Enable Timer0  to generate clock
	PORTB = PORTB | (1 << PB0); // Enable pull-up resistor
	DDRB = (1 << PB0); // Set PB0 as output
	TCCR0 |= (1 << 4) | (1 << 0); // Toggle pin on match
	//TCCR1B |= (1 << 0); // No prescaler
	OCR0 = 0x80;	// Compare value
	TIMSK |= (1 << 0); // Enable Interrupt
}

void _EEPROM_Send_Data(unsigned int Address, unsigned char Data)
{
	/* Wait until last bit is writen */
	while (EECR & (1 << EEWE));
	/* Set up address and data to be sent */	
	EEAR = Address;
	EEDR = Data;
	/* Set EEMWE(Write Enable) */
	EECR |= (1 << EEMWE);
	/* Start writing */
	EECR |= (1 << EEWE);
	_delay_ms(5);
}	

unsigned char _EEPROM_Receive_Data(unsigned int Address){
	/* Wait for completion of previous write */
	while (EECR & (1 << EEWE));
	/* Set up address */
	EEAR = Address;
	/* Start reading */
	EECR |= (1 << EERE);
	_delay_ms(10);
	/* Return data */
	return EEDR;
}

void _Enable_SPI()
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<PB5)|(1<<PB7);
	/* Enable SPI, Master, set clock rate fck/4 */
	SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR0);
}

void _Disable_SPI()
{//??????? TODO: See if this function is necessary
	/* Set MOSI and SCK output, all others input */
	DDRB &= ~((1<<PB5)|(1<<PB7));
	/* Enable SPI, Master, set clock rate fck/4 */
	SPCR &= ~((1<<SPE)|(1<<MSTR)|(0<<SPR0));
}

void _ADC_Start()
{
	PORTB |= ( 1 << PB3 );
	DDRB |= (1 << PB3); //Start and ALE
	PORTB &= ~(1 << PB3);	
}

void EnableInterrupts()
{
	MCUCR = MCUCR | (1 << ISC01) | (1 << ISC00); // Rising Edge interrupt
	GICR = GICR | (1 << INT0);
	sei();
}

void DisableInterrupts()
{
	cli();
}

void _SPI_Transmit(unsigned char Data)
{
	/* Start transmission */
	SPDR = Data;
	/* Wait for transmission complete */
	while
	(!(SPSR & (1<<SPIF)))
	;
}

void _SPI_Send_Data(unsigned int Address, unsigned char Data)
{
	//Chip Select Down
	_SPI_Transmit(SPI_WriteEnable);	
	//Chip Sleect up
	//Delay
	//Chip Select Down
	//WriteCommand
	//Address
	//Data
	//Chip Select up
}
