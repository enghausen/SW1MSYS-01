/*
 * LAB9_1.c
 *
 * Created: 07-04-2025 10:24:57
 * Author : enghausen
 */ 

#include <avr/io.h>

int main(void)
{
    // S�t PB5 (OC1A) som output
    DDRB |= (1 << PB5);

    // Sluk alle lysdioder p� PORTB
    PORTB = 0x00;

    // S�t Compare Match Output mode til "Toggle OC1A on Compare Match"
    TCCR1A = (1 << COM1A0);

    // S�t CTC mode (WGM12 = 1), og v�lg prescaler 1024 (CS12 og CS10 = 1)
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

    // Indstil compare-v�rdien til at give 0.5 Hz toggle (1 Hz blink) - OCR1A = (16.000.000 / (2 * 1024 * 0.5)) - 1 = 15624
    OCR1A = 15624;

    while (1)
    {
        // Tom l�kke - hardware timer styrer blink
    }
}