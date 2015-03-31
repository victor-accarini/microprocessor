#ifndef _UTIL_FUNCTIONS
#define _UTIL_FUNCTIONS

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

static const char AscTable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

void putChar(unsigned char ch);
unsigned char getChar();
void putLine(unsigned char *string);
void getLine(unsigned char *str);
unsigned int Asc2Hex(unsigned char* str);
void Hex2Asc(unsigned int number, unsigned char *string);

#endif