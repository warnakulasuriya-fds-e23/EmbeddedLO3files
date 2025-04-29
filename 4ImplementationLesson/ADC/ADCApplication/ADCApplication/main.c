/*
 * ADCApplication.c
 *
 * Created: 28/01/2025 10:25:41
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>


int main(void)
{
	//AREF, External
	ADMUX &= ~((1<<REFS1)|(1<<REFS0));
	
	//A0 Selection
	ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));
	
	// enabling analog to digital convertion
	ADCSRA |= (1<<ADEN);
	//setting the pre-scaler value to 128
	ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)); 
	
	/*About Setting ADLAR pin to zero to get the right alignment and 10 bit resolution.
	Right at the start ADLAR is most likely to be zero. But we can anyways set it
	to zero just to be sure
	*/
	ADCSRA &= ~(1<<ADLAR);
	
	/*making all the pins of the port D into output mode*/
	DDRD |= 0xFF;
    while (1) 
    {
		ADCSRA |= (1<<ADSC); // we start the A/D conversion
		while(ADCSRA & (1<<ADSC)){
			PORTD = ADC; // ADC is the value of the ADC Output (value after conversion)
			// PORTB = ADC>>8; //try this to get the remaining two bits to LEDs.
		}
		
    }
}

