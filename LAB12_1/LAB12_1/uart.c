/************************************************
* "uart.c":                                     *
* Implementation file for Mega2560 UART driver. *
* Using UART 0.                                 *
* Henning Hargaard                              *
*************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"

// Target CPU frequency
#define XTAL 16000000UL

/*************************************************************************
UART 0 initialization:
    Asynchronous mode.
    Baud rate = 9600.
    Data bits = 8.
    RX and TX enabled.
    No interrupts enabled.
    Number of Stop Bits = 1.
    No Parity.
    Baud rate = 9600.
    Data bits = 8.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_Interrupt)
{
	// 1. Tjek grænser for BaudRate og DataBit
	if (BaudRate < 300 || BaudRate > 115200) return;
	if (DataBit < 5 || DataBit > 8) return;

	// 2. Beregn UBRR og sæt baudrate
	unsigned int ubrr = (XTAL / (16UL * BaudRate)) - 1;
	UBRR0 = ubrr;

	// 3. Aktiver transmitter og receiver
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// 4. Frame format: ingen paritet, 1 stopbit, databit valgt via UCSZ00..UCSZ02
	UCSR0C = 0x00;

	switch (DataBit)
	{
		case 5:
		// UCSZn2:0 = 000 (ingen bits sat)
		break;
		case 6:
		UCSR0C |= (1 << UCSZ00);
		break;
		case 7:
		UCSR0C |= (1 << UCSZ01);
		break;
		case 8:
		UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
		break;
	}
	
	// 5. RX interrupt
	if (RX_Interrupt != 0)
	{
		UCSR0B |= (1 << RXCIE0); // Enable RX Complete interrupt
	}
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
   return (UCSR0A & (1 << RXC0));
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
       while (!CharReady());  // Vent til et tegn er klar
       return UDR0;           // Returner tegnet
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
    // Vent indtil UDR0 er klar til at modtage et nyt tegn
    while (!(UCSR0A & (1 << UDRE0)));

    // Skriv tegnet til dataregisteret
    UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
    while (*Streng != 0)  // Så længe vi ikke er ved 0
    {
        SendChar(*Streng);  // Send tegnet
        Streng++;           // Gå til næste tegn
    }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
    char buffer[7];              // Plads til +-32768 + 0
    itoa(Tal, buffer, 10);       // Konverter til tekst i base 10
    SendString(buffer);          // Send via UART
}

/************************************************************************/