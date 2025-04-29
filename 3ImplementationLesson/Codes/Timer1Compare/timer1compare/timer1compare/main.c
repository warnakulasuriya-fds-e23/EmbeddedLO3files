/*
 * timer1compare.c
 *
 * Created: 27/01/2025 14:15:38
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

/*note: why we specify volatile int instead of int
answer: if we define it as an int the value may be retrived from the cache instead
of the main memory. This happens because of CPU optimization practices.
So values in cache might not be the latest value.
But if we say volatile int, this int will only be called from main Memory*/
volatile int toggle = 0;

int main(void)
{
	/*Initializing the Timer1 in the compare mode*/
	TIMSK1 |= (1<<OCIE1A); // compare interrupt enabled, only the OCIE1A pin of the TIMSK1 will be changed
	
	/*Even in the compare mode there are many modes of Operation we will use the
	CTC mode. CTC => Clear Timer On Compare Match. To enter this mode we have to 
	set the values of TCCR1B and TCCR1A to the proper values*/
	
	//Setting TCCR1B
	TCCR1B |= (1<<WGM12); //assignment of 1 to WGM12
	TCCR1B &= ~(1<<WGM13); //assignment of 0 to WGM13
	
	//Setting TCCR1A
	TCCR1A &= ~((1<<WGM10)|(1<<WGM11));// assignment of 0 to both WGM10 and WGM11
	 
	/*Now we need to set the pre-scaler value so that Timer Overflow interrupt duration
	(The time taken for the timer register to reach its maximum value and overflow)
	would be in an appropriate value(not too fast)*/
	//setting up the Pre-scaler here also we have to make changes to TCCR1B
	TCCR1B |= (1<<CS12);
	TCCR1B &= ~((1<<CS11)|(1<<CS10)) ;
	
	/*First to set the counter to zero at the start,we do this by setting
	 the timer register to zero. we could do this by typing out 0b 0000 0000 0000 0000
	 thats 16bits or setting the MSB of timer register and the LSB of timer register
	 that also instead of setting it up in binary we could do that quite shortly using
	 hexadecimal as follows. */
	
	//Setting the timer Register to zero by setting the MSB 8 bits and LSB 8 bits
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	
	/*now we need to set the timer compare register so that the interrupt fires every
	second. This value is the number of pulses that would occur after the passing of
	1 second. we can calculate this, and it turns out the it would take 62500 pulse
	for 1 second to pass, given that we are using timer1 and the pre-scaler 256*/
	
	//setting the timer compare register to 62500 (F424 in hex)
	OCR1AH = 0xF4;
	OCR1AL = 0x24;
	
	/*Very important !!!!!
	enable global interrupts or interrupts wont work at all*/
	
	sei(); //Global Interrupt 
	
	
	//DDRB |=(1<<PORTB5); // would this work?
	DDRB |=(1<<PB5); // setting portB pin no 5 as output port
    while (1) 
    {
    }
}

//defining the timer interrupt service routine thing
ISR(TIMER1_COMPA_vect)
{
	if (toggle)
	{
		PORTB |= (1<<PB5);
	} 
	else
	{
		PORTB &= ~(1<<PB5);
	}
	toggle = 1 - toggle;
		

}