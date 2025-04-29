#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_Value ((F_CPU/16/BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>


void ConfigureUART(void){
	
	// Setting the BAUD rate
	UBRR0L = UBRR_Value;
	UBRR0H = (UBRR_Value>>8);
	
	//Enable transmitter
	UCSR0B |= (1<<TXEN0);
	
	//Enable Receiver
	UCSR0B |= (1<<RXEN0);
	
	// set 8 bits as the transmit frame
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
	
}

void UARTTransmit(unsigned char data){
	// Check transmit buffer free or not
	// if that is free write your data to transmit buffer
	//buffer register
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char UARTReceiver(){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

int main(void)
{
	ConfigureUART();
	DDRB |= 0x20;  //or 0B00100000
	PORTB |= 0x20;
	
	while (1)
	{
		UARTTransmit(UARTReceiver());
		_delay_ms(250);
	}
}





