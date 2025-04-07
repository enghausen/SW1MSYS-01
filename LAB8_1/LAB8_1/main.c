<<<<<<< HEAD
/*
 * LAB8_1.c
 *
 * Created: 25-03-2025 15:54:18
 * Author : enghausen
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

=======
/*************************************
* MSYS, LAB8, Part 1                 *
* Timer 0 in Normal Mode             *
* Led port increments 125 times/sec. *
**************************************/
#include <avr/io.h>
#include "led.h"

// Prototype
void T0Delay();

int main()
{
	// Sæt system clock til 62.5 kHz (16 MHz / 256)
	CLKPR = (1 << CLKPCE);        // Enable clock change
	CLKPR = (1 << CLKPS3);        // Set prescaler to 256
	unsigned char x = 0;
	// Klargør LED port
	initLEDport();
	while(1)
	{
		// Vent 1/125 sekund
		T0Delay();
		// Inkrementer og vis variablen x
		x++;
		writeAllLEDs(x);
	}
}

void T0Delay()
{
	// 256 - 125 pga. vi ønsker et delay på 1/125s (8ms) og derfor 16000000 Hz / 1024 = 15625 ticks/sekund og tid for et overflow er 256 ticks / 15625 ticks/s = 0.016384 s = 16.384 ms
	// Da vi ønsker 8 ms, beregner vi 8 ms × 15625 ticks/s = 125 ticks
    TCCR0A = 0;                              // Normal mode
    TCNT0 = 131;                             // Preload: 256 - 125 = 131
    TCCR0B = (1 << CS02) | (1 << CS00);      // Prescaler = 1024

    while ((TIFR0 & (1 << TOV0)) == 0);      // Vent på overflow
    TIFR0 |= (1 << TOV0);                    // Clear overflow-flag
}
>>>>>>> c2ff37146716cf6e6526a5dc5c31588df07febe2
