
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void initHardware(void){
	DDRA = 0B11111111; // setting all A pins to output
	DDRC = 0B11111111; //setting all C pins to output
	

}
void initADC(void){
	//AREF, External
	ADMUX &= ~((1<<REFS1)|(1<<REFS0));
	
	//enabling ADC
	ADCSRA |= (1<<ADEN);
	
	//setting the prescaler to 128 to get optimal clock frequency for ADC
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	
	
	//selecting the AC0
	//ADMUX &= ~((1<<MUX0)|(1<<MUX1)|(1<<MUX2)|(1<<MUX3)|(1<<MUX4));
	//ADCSRB &= ~(1<<MUX5);
}

int readADC(uint8_t adc_channel){
	ADMUX |= (ADMUX & 0xF0)|adc_channel; //Input selection
	ADCSRA |= (1<<ADSC);// Start the ADC conversion
	while(ADCSRA & (1<<ADSC)){
	// loops until ADSC pin becomes zero
	//this will do Polling
	
	}
	
	return ADC;
}

void display(int valueOfADC){
	int ones;
	int tens;
	int hundreds;
	int thousands;
	
	thousands = (valueOfADC/1000)%10;
	hundreds = (valueOfADC/100)%10;
	tens = (valueOfADC/10)%10;
	ones = (valueOfADC/1)%10;
	
	PORTA = ones | (tens<<4);
	PORTC = hundreds | (thousands<<4);
	
}
int main(void)
{
	int adcValue;
	// Initialize hardware and ADC
	initHardware();
	initADC();
	while (1)
	{
		// Read ADC value from channel 0
		adcValue = readADC(0);
		// Display the ADC value
		display(adcValue);
		// Delay for 1 second
		_delay_ms(1000);
	}
	return 0;
}

