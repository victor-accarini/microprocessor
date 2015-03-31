/*
 * util.c
 *
 * Created: 2/9/2015 2:00:14 PM
 *  Author: Victor Accarini
 */ 
#include "util.h"

void putChar(unsigned char ch)
{
	_USART_Transmit(ch);
}

unsigned char getChar()
{
	return _USART_Receive();
}

void putLine(unsigned char *string)
{
	int i = 0;
	while(string[i] != '\n' && string[i] != '\0' && string[i] != '\r'){
		_USART_Transmit(string[i]);
		i++;
	}
	_USART_Transmit('\r');
	_USART_Transmit('\n');
}

void getLine(unsigned char* str)
{
	unsigned char ch;
	int i = 0;
	ch = _USART_Receive();
	while(ch != '\n' && ch != '\r'){
		if (ch != '\b')
		{
			str[i] = ch;
			i++;
		} 
		else
		{
			if (i != 0)
			i--;
		}
		ch = _USART_Receive();
	}
	str[i] = '\0';
}

unsigned int Asc2Hex(unsigned char* str)
{
	unsigned int number = 0, i, min;
	if (str[1] != 'x')
	{
		min = 0;
	}
	else
	{
		min = 2;
	}
	i = min;
	while (str[i] != '\0'){
		if (str[i] >= 'a')
		{
			number = number<<4;
			number += (str[i] - 87);
		}
		else if (str[i] >= 'A')
		{
			number = number<<4;
			number += (str[i] - 55);
		}
		else
		{
			number = number<<4;
			number += (str[i] - 48);
		}
		i++;
	}
	return number;
}

void Hex2Asc(unsigned int number, unsigned char *string)
{
	unsigned char *ch;
	unsigned int i;
	
	string[0] = AscTable[0];
	string[1] = 'x';
	ch = (unsigned char*) (&number) + 1;
	for (i = 1; i < 3; i++)
	{
		string[2*i] = AscTable[( (*ch)>>4 ) & 0x0F];
		string[2*i+1] = AscTable[( *ch ) & 0x0F];
		ch--;
	}
	string[6] = '\0';
}
