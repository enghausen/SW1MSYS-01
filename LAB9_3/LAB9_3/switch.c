/************************************
* "Switch.c"                        *
* Implementation for SWITCH driver. *
* Henning Hargaard                  *
************************************/
#include <avr/io.h>

// Klargør switch-porten
void initSwitchPort()
{
	DDRA = 0x00;
	PORTA = 0xFF;
}

// Læser alle switches samtidigt
unsigned char switchStatus()
{
	return ~PINA;
}

// Returnerer TRUE, hvis switchen med nummeret
// "switch_nr" er aktiveret - ellers returneres FALSE
unsigned char switchOn(unsigned char switch_nr)
{
	if (switch_nr > 7)
	{
		return 0;
	}
	return !(PINA & (1 << switch_nr));
}