/*
 * LEDBlinkWihtPushButton.c
 *
 * Created: 20/01/2025 15:17:40
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= 0B00100000; //PORTB:PIN5 as output pin
	DDRD &= 0B11110111; //PORTD:PIN3 as input pin
	while (1){
		if(PIND & 0B00001000){
			/*if condition will be evaluated true only if "PIND & 0B00001000" 
			returns a non zero value, and irrespective of the other pin values of PIND
			"PIND & 0B00001000" will only give a non zero value only when the PIND3 is 1*/
			
			PORTB |= 0B00100000; //PORTB:PIN5 made to output high
		}else{
			PORTB &= 0B11011111; //PORTB:PIN5 made to output low
		}		
		
		
	}

	
}


