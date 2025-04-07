/*
 * LAB9_2.c
 *
 * Created: 07-04-2025 10:53:24
 * Author : enghausen
 */ 

#include <avr/io.h>
#include "Switch.h"

int main(void)
{
    // Initier switch-port og PB5 (OC1A) som output
    initSwitchPort();
    DDRB |= (1 << PB5);
    PORTB = 0x00;

    // Sæt Timer 1 i Phase Correct PWM, 10-bit mode
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B = (1 << CS10);  // Ingen prescaler

    // Startværdi (50 % lysstyrke) - 100% er 1023
    OCR1A = 512;

    while (1) 
    {
        if (switchOn(0)) {
            OCR1A = 51;     // ca. 5 % duty cycle
        }
        else if (switchOn(1)) {
            OCR1A = 512;    // ca. 50 % duty cycle
        }
        else if (switchOn(2)) {
            OCR1A = 972;    // ca. 95 % duty cycle
        }
    }
}