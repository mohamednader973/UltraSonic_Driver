/*
 * UltraSonic_Driver.c
 *
 * Created: 9/27/2020 11:43:49 PM
 * Author : monad
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include "UltraSonic.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	char string[10];	
	DDRA = 0x01;		/* Make trigger pin as output */
	UltraSonic_Init();
	LCD_Init();
	float Dist;
    /* Replace with your application code */
    while (1) 
    {
		Dist=UltraSonic_Func();
		itoa(Dist,string,10);
		LCD_String(string);
		_delay_ms(200);
		LCD_CMD(0x01);
    } 
}
ISR(TIMER1_OVF_vect)
{
	extern int TimerOverflow ;
	TimerOverflow++;	/* Increment Timer Overflow count */
}

