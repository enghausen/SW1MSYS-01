/*
 * LAB6_1.c
 *
 * Created: 11-03-2025 10:53:29
 * Author : enghausen
 */ 

#include <avr/io.h>

int main()
{
	unsigned char i = 0;

	DDRA = 0xFF; //port A as output
	DDRB = 0xFF; //port B as output
	DDRC = 0xFF; //port C as output
	PORTA = 0xAA;
	while (1)
	{
		PORTC = PORTC ^ 0b00000001; //toggle PORTC.0
		PORTB = i;
		i++;
	}
}