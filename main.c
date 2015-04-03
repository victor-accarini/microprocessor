/*
 * main.c
 *
 * Created: 2/4/2015 1:58:00 PM
 *  Author: Victor Accarini
 */ 

#define F_CPU 4000000UL
#define BAUD 9600
#define MYBAUD F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <string.h>
#include "util.h"
#include "functions.h"
#include "mem.h"

//Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	unsigned char *ADC = (unsigned char *)ADC_PB_Address;
	
	//Enable Output
	PORTB |= (1 << ADC_Output);
	DDRB |= (1 << PB2); //Output Enable
	_delay_us(1);
	//Read data from 8255 PORTB
	ADC_Data = (*ADC);
	//Send Data to LEDs
	//ADC = ADC_PA_Address;
	//(*ADC_DataAddress) = (unsigned char)~(ADC_Data);
	//Disable Output
	PORTB &= ~(1 << ADC_Output);
}

// Clock Generation for ADC
ISR(TIMER0_COMP_vect)
{
	TCNT0 = 0;
}

// Main program
int main(void)
{	

	unsigned char *cp;
	
	//unsigned int i, off1, off2, off3;
	//unsigned char str[160], arg1[15], arg2[15], arg3[15];
	//unsigned int hexnum;
	
	
	// Systems Initializations
	_Init_Mem();
	_Init_UART(MYBAUD);
	_Init_Peripheral();
	_Init_ADC();
	
	EnableInterrupts();
	
	ADC_DataAddress = (unsigned char*)0x2000;

	//while(1)
	//{
		_ADC_Start();
		_delay_ms(2000);
		cp = (unsigned char*)0x4000;	
		DisableInterrupts();
		_EEPROM_Send_Data(0x001,ADC_Data);
		(*cp) = _EEPROM_Receive_Data(0x001);
		EnableInterrupts();
		if (ADC_Data == 0x33)
			putLine((unsigned char*)"YES");	
		//Input command
		//getLine(str);
		//putLine(str);
		
		/*//Read the input looking for a valid command
		if (str[0] == 'F') //Fill function
		{
			i = 2;
			off1 = i;
			while (str[i] != ' ') //Get first argument
			{
				arg1[i-off1] = str[i];
				i++;
			}
			arg1[i-off1] = '\0';
			i++;
			off2 = i;
			while (str[i] != ' ') //Get second argument
			{
				arg2[i-off2] = str[i];
				i++;
			}
			arg2[i-off2] = '\0';
			i++;
			off3 = i;
			while (str[i] != '\r' && str[i] != '\n') //Get second argument
			{
				arg3[i-off3] = str[i];
				i++;
			}
			arg3[i-off3] = '\0';
	
			F(arg1,arg2,arg3);
		}
		else if (str[0] == 'D') //Display function
		{
			i = 2;
			off1 = i;
			while (str[i] != ' ') //Get first argument
			{
				arg1[i-off1] = str[i];
				i++;
			}
			arg1[i-off1] = '\0';
			i++;
			off2 = i;
			while (str[i] != ' ') //Get second argument
			{
				arg2[i-off2] = str[i];
				i++;
			}
			arg2[i-off2] = '\0';
			D(arg1,arg2);
		}//*/
	//}//End while loop
	
	/*
	if (strcmp(str, "Start") == 0){
		PORTB = 0x00;
	}
	putLine("Microprocessor - Lab");
	putLine("Nailed it");
	putLine("---------------------");
	putLine("Wait for it.");
	putLine("LED Blinking in....");
	putLine("5");
	_delay_ms(1000);
	putLine("4");
	_delay_ms(1000);
	putLine("3");
	_delay_ms(1000);
	putLine("2");
	_delay_ms(1000);
	putLine("1");
	_delay_ms(1000);
	while(1)
	{
		PORTB = 0x00;
		_delay_ms(500);
		PORTB = 0x01;
		_delay_ms(500);
	}
	*/
	return 0;
}
