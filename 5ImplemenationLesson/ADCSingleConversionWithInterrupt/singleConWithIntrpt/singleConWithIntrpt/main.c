#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define CHANNEL 5

void configADC(void);

int main(void)
{
	configADC();
	
	/*making all the pins of the port D into output mode*/
	DDRD |= 0xFF;
	
	/*gonna make the Port B pins 0 and 1 to output mode to use them for the remaining
	LEDS that will represent the two MSB which Port D wont have enough space to hold*/
	/*additionally going to also set the B5 pin to output mode so that it can be used to show that main program is
	running*/
	DDRB |= ((1<<PORTB0)|(1<<PORTB1)|(1<<PORTB5));
	
	/*additionally going to also set the B5 pin to output mode so that it can be used to show that main program is
	running*/
	//DDRB |= (1<<PORTB5);
    while (1) 
    {
		ADCSRA |= (1<<ADSC); // we start the A/D conversion
		//while(ADCSRA & (1<<ADSC)){
			//// loops until ADSC pin becomes zero
			////this will do Polling
		//}
		
		//next part is to blink the led connected to the B 5 pin
		PORTB |= (1<<PB5);
		_delay_ms(500);
		PORTB &= ~(1<<PB5);
		_delay_ms(500);
		
		
    }
}

void configADC(void){
	//AREF, External
	ADMUX &= ~((1<<REFS1)|(1<<REFS0));
	
	//A0 Selection
	//ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3));
	
	//following is a better way to select the analog input pin
	/*(ADMUX & 0xF0) returns the binary value such that the last four bits of ADMUX are zero and the rest of the bits
	are exactly as they are (because 0 AND X = 0, 1 AND X = X). then this return value undergoes bit wise OR with
	the binary form of the CHANNEL constant then MUX 0 1 2 3 are set up properly (because MUX3:0 will be 5 for ADC5,
	0 for ADC0,etc)*/
	ADMUX = (ADMUX & 0xF0)| CHANNEL;
	
	// enabling analog to digital convertion
	ADCSRA |= (1<<ADEN);
	//setting the pre-scaler value to 128
	ADCSRA |= ((1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)); 
	
	/*About Setting ADLAR pin to zero to get the right alignment and 10 bit resolution.
	Right at the start ADLAR is most likely to be zero. But we can anyways set it
	to zero just to be sure
	*/
	ADCSRA &= ~(1<<ADLAR);
	
	/*now we are going to enable the analog to digital interrupt, so that we can implement this in a free running
	manner.*/
	ADCSRA |= (1<<ADIE);
	
	//enabling global interrupt
	sei();
	
}

ISR (ADC_vect){
		PORTD = ADC; // ADC is the value of the ADC Output (value after conversion)
		PORTB |= ADC>>8; //trying this to get the remaining two bits to LEDs that will connect to pB0 and PB1
}

