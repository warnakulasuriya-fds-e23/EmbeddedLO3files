/*
 * main.c
 *
 * Created: 1/20/2025 2:50:07 PM
 *  Author: Dheera
 */ 
#define F_CPU 16000000UL
//#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 0B00100000; //PORTB:PIN5 as output pin
    while(1)
    {
        PORTB |= 0B00100000; //PORTB:PIN5 made to output high
    }
}