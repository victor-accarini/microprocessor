/*
 * uart.c
 *
 * Created: 2/10/2015 2:06:17 PM
 *  Author: Victor Accarini
 */ 

#include "uart.h"

void _Init_UART(unsigned int baud)
{
	/* Set baud rate */
	UBRRH = (unsigned char) (baud>>8); /* Move the contents 8 bits to the right - taking the value of UBRRL out */
	UBRRL = (unsigned char) (baud);
	/* Enable receiver and transmitter */
	UCSRB = (1 << RXEN | 1 << TXEN);
	/* Set frame format: 8data, 2stop bit */
	/* Enable URSEL to access UCSRC - if URSEL is 0 goes to UBRRx Registers - same I/0 address*/
	UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);
}

unsigned char _USART_Receive(void)
{
	unsigned char ch;
	/* Wait to receive data */
	/* While the Receive Complete Flag is not set then wait*/
	while ( !(UCSRA & 1 << RXC) )
	{}
	ch = UDR;
	while ( !(UCSRA & 1 << UDRE) )
	{}
	UDR = ch;
	if (ch == '\r')
	{
		while ( !(UCSRA & 1 << UDRE) )
		{}
		UDR = '\n';	
	}
	/* Return the received data stored in the UDR register */
	return ch;
}

void _USART_Transmit(unsigned char data)
{
	/* See if the transmit buffer is empty */
	while ( !(UCSRA & 1 << UDRE) )
	{}
	
	UDR = data;
}
