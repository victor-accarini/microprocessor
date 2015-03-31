/*
 * uart.h
 *
 * Created: 2/9/2015 2:01:38 PM
 *  Author: VICTOR ACCARINI
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void _Init_UART(unsigned int baud);
unsigned char _USART_Receive(void);
void _USART_Transmit(unsigned char data);


#endif /* UART_H_ */