/********************************************
* MSYS, LAB 11, Part 2                      *
* Test program for Mega2560 UART driver.    *
* Using UART 0.                             *
* The LEDs will indicate test progress      *
*********************************************/
#include <avr/io.h>
#include "uart.h"
#include "led.h"

int main()
{
	char tegn;
	char TestStreng[] = "This is string number 1\r\n";
	int8_t i;

	// Initialize LED port
	initLEDport();
	// Initialize UART: Baud = 9600, 8 data bits, No Parity
	InitUART(9600, 8);

	while (1)
	{
		// Testing SendChar
		writeAllLEDs(1);
		SendChar('A');
		SendChar('B');
		SendChar('C');
		SendChar('\r');
		SendChar('\n');

		// Testing ReadChar() : Read and echo
		writeAllLEDs(2);
		tegn = ReadChar();
		SendChar(tegn);
		SendChar('\r');
		SendChar('\n');

		// Testing CharReady() : Wait, read and echo
		writeAllLEDs(3);
		while ( !CharReady() )
		{}
		SendChar( ReadChar() );
		SendChar('\r');
		SendChar('\n');

		// Testing SendString(): Sending string number 1 (SRAM memory)
		writeAllLEDs(4);
		SendString(TestStreng);

		// Testing SendString(): Sending string number 2 (Flash memory)
		writeAllLEDs(5);
		SendString("This is string number 2\r\n");
		
		// Testing SendInteger()
		writeAllLEDs(6);
		SendInteger(12345); //Positive number
		SendChar('\r');
		SendChar('\n');
		SendInteger(-1000); //negative number
		SendChar('\r');
		SendChar('\n');
		
		for (i=-5; i<5; i++)
		{
			SendInteger(i);	SendChar(' ');
		}
		SendChar('\r');
		SendChar('\n');
	}
}