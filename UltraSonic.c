/*
 * UltraSonic.c
 *
 * Created: 9/28/2020 1:14:06 AM
 *  Author: monad
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UltraSonic.h"
#define F_CPU 8000000UL
#include <util/delay.h>
void UltraSonic_Init(void)
{
	TCCR1A =0x00;
	TIMSK |=(1<<TOIE1);
	sei();
}
int TimerOverflow = 0;
float UltraSonic_Func(void)
{
	long count;
	float distance;
	PORTA |= (1<<0);
	_delay_us(10);
	PORTA &= (~(1<<0));
	TCNT1=0;  //reseting counter 
	TCCR1B =0x41;
	TIFR |=(1<<ICF1);
	TIFR |=(1<<TOV1);
	while(((TIFR>>ICF1)&1)==0);
	TimerOverflow = 0;
	TCNT1=0;  //reseting counter
	TCCR1B =0x01;
	TIFR |=(1<<ICF1);
	TIFR |=(1<<TOV1);
	while(((TIFR>>ICF1)&1)==0);
	count = ICR1 + (65535 * TimerOverflow);
	distance = (float)count / 466.47;
	distance /=100;
	return distance;
	
}