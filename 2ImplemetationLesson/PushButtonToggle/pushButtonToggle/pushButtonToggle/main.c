/*
 * pushButtonToggle.c
 *
 * Created: 21/01/2025 10:22:36
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int toggle = 1;
int main(void)
{
    /* Replace with your application code */
	DDRB |= 0B00100000; // PORTB : PIN5 set to output
	//EICRA |= 0B00001100; //ISC 11 = 1, ISC110 = 1(Rising Edge Interrupt)
	EICRA |= (1 << ISC11) | (1 << ISC10); //same thing as above commented line (to find out that ISC11 and ISC10 works for EICRA refer the data sheet)
	EIMSK |= 0B00000010;// INT1 is selected
	
	sei(); //Global Interrupt 
    while (1) 
    {
    }
}

ISR(INT1_vect){
	if (toggle)
	{
		//PORTB |= 0B00100000; 	
		PORTB |= (1<<PB5); // same thing as above commented line
	} 
	else
	{
		//PORTB &= 0B11011111;
		PORTB &= ~(1<<PB5); //same thing as above commented line
	}
	
	toggle = 1-toggle; //if toggle was 1 previously it will now become 1 and vice versa
}