/*
 * LAB12_1.c
 *
 * Created: 29-04-2025 13:53:27
 * Author : enghausen
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "led.h"
#include "lm75.h"

int temperatur;

int main(void)
{
    // Initialiser LED-driver
    initLEDport();

    // Initialiser UART0: 9600 baud, 8 databits, RX interrupt enabled
    InitUART(9600, 8, 1);

    // Enable global interrupts
    sei();

    // Uendelig løkke – alt sker i ISR
    while (1) 
    {
		temperatur = LM75_temperature(0);  // Læs temp fra sensor 0
		SendString("Temperatur: ");
		SendInteger(temperatur / 2);       // Heltalsdel
		SendString(",");
		if (temperatur % 2)
			SendChar('5');                 // Halv grad
		else
			SendChar('0');
		SendString(" C\r\n");
		_delay_ms(1000);
    }
}

// UART modtage-interrupt (UART0)
ISR(USART0_RX_vect)
{
    char tegn = UDR0;

    // Hvis modtaget tegn er '0'–'7'
    if (tegn >= '0' && tegn <= '7')
    {
        unsigned char led_nr = tegn - '0';
        toggleLED(led_nr);

        // Send besked tilbage til terminalen
        SendString("LED nummer ");
        SendChar(tegn);
        SendString(" er toggled\r\n");
    }
}