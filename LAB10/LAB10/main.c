/*
 * LAB10.c
 *
 * Created: 15-04-2025 22:53:28
 * Author : enghausen
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"

// Punkt 3 (Timer 0) reuse:
volatile unsigned int overflow_count = 0;

void initInterrupts(void)
{
    // INT2: Falling edge (ISC21 = 1, ISC20 = 0)
    EICRA |= (1 << ISC21);
    EICRA &= ~(1 << ISC20);

    // INT3: Rising edge (ISC31 = 1, ISC30 = 1)
    EICRA |= (1 << ISC31) | (1 << ISC30);

    // Enable INT2 og INT3
    EIMSK |= (1 << INT2) | (1 << INT3);
}

void initTimer0(void)
{
    TCCR0A = 0x00;          // Normal mode
    TCCR0B = (1 << CS00);   // Prescaler = 1
    TIMSK0 = (1 << TOIE0);  // Enable Timer0 overflow interrupt
}

void initTimer1_CTC(void)
{
    TCCR1A = 0x00;                         // Normal port operation
    TCCR1B = (1 << WGM12) | (1 << CS12);   // CTC mode (WGM12 = 1), prescaler = 256
    OCR1A = 7811;                          // Compare match hver 0.25s (4 gange pr. sek.) - (16000000/(2*256*4))-1=7811
    TIMSK1 = (1 << OCIE1A);                // Enable Timer1 Compare Match A interrupt
}

int main(void)
{
    initLEDport();
    initInterrupts();
    initTimer0();        // For LED6
    initTimer1_CTC();    // For LED5
    sei();

    while (1) 
    {
        toggleLED(7);         // LED7 – software delay
        _delay_ms(1000);
    }
}

// INT2 interrupt – toggle LED2
ISR(INT2_vect)
{
    toggleLED(2);
}

// INT3 interrupt – toggle LED3
ISR(INT3_vect)
{
    toggleLED(3);
}

// Timer 0 overflow interrupt – toggle LED6 hver sekund
ISR(TIMER0_OVF_vect)
{
    overflow_count++;
    if (overflow_count >= 62500)
    {
        toggleLED(6);
        overflow_count = 0;
    }
}

// Timer1 Compare Match A interrupt – toggle LED5 4 gange/sek
ISR(TIMER1_COMPA_vect)
{
    toggleLED(5);
}