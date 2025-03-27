/*************************************
* MSYS, LAB8, Part 2                 *
* Timer 1 in Normal Mode             *
* "Binary Clock" (seconds)           *
* PC:[7..4] = Sec.10  [3..0] = Sec.1 *
**************************************/
#include <avr/io.h>
#include "led.h"

// Prototype
void T1Delay();

int main()
{
	unsigned char tiere = 0;
	unsigned char enere = 0;
	unsigned char bcd;
	// Klargør LED port
	initLEDport();
	while(1)
	{
		// Vent 1 sekund
		T1Delay();
		// Juster enere og tiere (BCD format)

		//---> Skriv kode her, der på rette vis
		//     justerer enere og tiere.
		//     Derefter skal tiere og enere skrives
		//     ud til lysdioderne.
		//     [7..4] = 10'ere  [3..0] = 1'ere
		enere++;
        if (enere > 9)
        {
            enere = 0;
            tiere++;
        }
        if (tiere > 5)
        {
            tiere = 0;
            enere = 0;
        }

        bcd = (tiere << 4) | enere;  // Kombinér til BCD-format
        writeAllLEDs(bcd);           // Vis på LED'er

	}
}

void T1Delay()
{
	//---> Skriv kode her, der anvender timer 1
	//     i normal mode til at lave en forsinkelse
	//     på 1 sekund.
	// 16000000 Hz / 1024 = 15625 ticks/sekund og tid for et overflow er 65536 ticks / 15625 ticks/s = 4,194304s
	// Da vi ønsker 1s kan vi beregne vores TCNT1 til følgende 65536 - 15625 = 49911
    TCCR1A = 0;                                 // Normal mode
    TCNT1 = 49911;                                  // Startværdi
    TCCR1B = (1 << CS12) | (1 << CS10);         // Prescaler 1024

    while ((TIFR1 & (1 << TOV1)) == 0);         // Vent på overflow
    TIFR1 |= (1 << TOV1);                       // Clear overflow-flag
}