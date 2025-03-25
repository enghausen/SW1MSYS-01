/*
 * LAB6_2.c
 *
 * Created: 11-03-2025 11:19:27
 * Author : enghausen
 */ 

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>

// Definerer toner (T/2 værdier i mikrosekunder)
#define TONE_c  956
#define TONE_D  851
#define TONE_E  758
#define TONE_F  716
#define TONE_G  638
#define TONE_A  568
#define TONE_H  506
#define TONE_C  478

int main(void)
{
    DDRA = 0x00;
    DDRB = 0xFF;
   
    while (1) 
    {
        if ((PINA & (1 << PA0)) == 0) 
        { 
            _delay_us(TONE_c); 
        }

        if ((PINA & (1 << PA1)) == 0) 
        { 
            _delay_us(TONE_D); 
        }

        if ((PINA & (1 << PA2)) == 0) 
        { 
            _delay_us(TONE_E); 
        }

        if ((PINA & (1 << PA3)) == 0) 
        { 
            _delay_us(TONE_F); 
        }

        if ((PINA & (1 << PA4)) == 0) 
        { 
            _delay_us(TONE_G); 
        }

        if ((PINA & (1 << PA5)) == 0) 
        { 
            _delay_us(TONE_A); 
        }

        if ((PINA & (1 << PA6)) == 0) 
        { 
            _delay_us(TONE_H); 
        }

        if ((PINA & (1 << PA7)) == 0) 
        { 
            _delay_us(TONE_C); 
        }

        // Inverterer PORTB, hvis mindst én knap er trykket
        if ((PINA & 0xFF) != 0xFF) 
        { 
            PORTB = ~PORTB; 
        }
    }
}