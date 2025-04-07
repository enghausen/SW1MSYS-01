/*
 * LAB9_3.c
 *
 * Created: 07-04-2025 11:24:00
 * Author : enghausen
 */ 

#include <avr/io.h>
#include "Switch.h"

int main(void)
{
    // Initier switch port og OC1A (PB5) som output
    initSwitchPort();
    DDRB |= (1 << PB5);
    PORTB = 0x00;

    // Sæt Timer 1 i CTC mode og toggle OC1A på match
    TCCR1A = (1 << COM1A0);                 // Toggle OC1A on compare match
    TCCR1B = (1 << WGM12) | (1 << CS11);    // CTC mode, prescaler 8

    while (1)
    {
        if (switchOn(0))
            OCR1A = 1909; // C5
        else if (switchOn(1))
            OCR1A = 1701; // D5
        else if (switchOn(2))
            OCR1A = 1515; // E5
        else if (switchOn(3))
            OCR1A = 1430; // F5
        else if (switchOn(4))
            OCR1A = 1275; // G5
        else if (switchOn(5))
            OCR1A = 1135; // A5
        else if (switchOn(6))
            OCR1A = 1009; // B5
        else if (switchOn(7))
            OCR1A = 953;  // C6
        else
            OCR1A = 0;     // Stop tone
    }
}