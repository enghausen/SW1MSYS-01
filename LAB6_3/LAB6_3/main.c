/*
 * LAB6_3.c
 *
 * Created: 11-03-2025 12:15:06
 * Author : enghausen
 */ 
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>

int main(void)
{
	// Konfigurer PA0-PA3 som input (trykknapper)
	DDRA = 0x00;
	// Konfigurer PB5 som output (lysdiode)
	DDRB |= (1 << PB5);

	while (1)
	{
		if ((PINA & (1 << 0)) == 0) // SW0 - 100ms periode, 5% duty cycle
		{
			PORTB |= (1 << PB5);  // Tænd lysdiode
			_delay_ms(5);         // 5% af 100ms
			PORTB &= ~(1 << PB5); // Sluk lysdiode
			_delay_ms(95);        // 95% af 100ms
		}
		else if ((PINA & (1 << 1)) == 0) // SW1 - 100ms periode, 95% duty cycle
		{
			PORTB |= (1 << PB5);
			_delay_ms(95);
			PORTB &= ~(1 << PB5);
			_delay_ms(5);
		}
		else if ((PINA & (1 << 2)) == 0) // SW2 - 1ms periode, 5% duty cycle
		{
			PORTB |= (1 << PB5);
			_delay_us(50);       // 5% af 1ms (1000 µs)
			PORTB &= ~(1 << PB5);
			_delay_us(950);      // 95% af 1ms
		}
		else if ((PINA & (1 << 3)) == 0) // SW3 - 1ms periode, 95% duty cycle
		{
			PORTB |= (1 << PB5);
			_delay_us(950);
			PORTB &= ~(1 << PB5);
			_delay_us(50);
		}
		else
		{
			PORTB &= ~(1 << PB5); // Ingen knapper trykket, sluk lysdiode
		}
	}
}
