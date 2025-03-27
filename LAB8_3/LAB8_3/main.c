/*
 * LAB8_3.c
 *
 * Created: 27-03-2025 12:07:52
 * Author : enghausen
 */ 

#include <avr/io.h>
#include "led.h"

int main(void)
{
	initLEDport();           // Klargør LED-porten (PORTB som output)

	DDRD &= ~(1 << PD7);     // Sæt PD7 som input (T0)

	// Initier Timer 0 som counter med ekstern clock, falling edge
	TCCR0A = 0;                                  // Normal mode
	TCCR0B = (1 << CS02) | 1 << CS01 | (1 << CS00);          // External clock source on T0, rising edge

	while (1)
	{
		writeAllLEDs(TCNT0);  // Vis tællerværdi på LED'erne
	}
}

