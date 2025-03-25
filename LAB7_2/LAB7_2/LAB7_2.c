/*********************************************
* MSYS, LAB7, Part 2                         *
* Testprogram for Switch port driver         *
* Henning Hargaard                           *
**********************************************/
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include "switch.h"
#include "led.h"

int main()
{
	unsigned char i;

	// Klargøring af SWITCH-porten
	initSwitchPort();
	// Klargøring af LED-porten
	initLEDport();
	
	// Test af switchStatus():
	// Resultatet skrives til hele lysdiodeporten
	// Testen afsluttes, når man samtidigt
	// trykker på SW7 og SW0
	i = 0;
	while (i != 0b10000001)
	{
		i = switchStatus();
		writeAllLEDs(i);
	}

	// Tænd alle lysdioder i 2 sekunder
	// og sluk så alle lysdioder
	// Så kan vi se, at næste test starter
	writeAllLEDs(0xFF);
	_delay_ms(2000);
	writeAllLEDs(0);
	_delay_ms(2000);

	// Test af switchOn():
	// Læs efter tur hver enkelt switch
	// og tænd tilsvarende lysdiode, hvis der trykkes på tasten
	// - ellers slukkes lysdiden
	while (1)
	{
		for (i=0; i<=7; i++)
		{
			if (switchOn(i))
			turnOnLED(i);
			else
			turnOffLED(i);
		}
	}
}