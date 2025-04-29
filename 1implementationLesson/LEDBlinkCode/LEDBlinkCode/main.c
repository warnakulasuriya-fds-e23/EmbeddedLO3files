/*
 * LEDBlinkCode.c
 *
 * Created: 20/01/2025 15:07:16
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= 0B00100000; //PORTB:PIN5 as output pin

    /* Replace with your application code */
    while (1) 
    {
		 PORTB |= 0B00100000; //PORTB:PIN5 made to output high
		 _delay_ms(1000);
		 
		 PORTB &= 0B11011111;
		 _delay_ms(1000);
    }
}

