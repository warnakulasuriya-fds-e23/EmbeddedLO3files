
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_Value F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

void configureUART(void){
	//Setup BAUD Rate
	UBRR0L = UBRR_Value;
	UBRR0H = (UBRR_Value>>8);
	//Asynchronous
	UCSR0A &= ~(1<<U2X0); 
	//Enable Tx
	UCSR0B |= (1<<TXEN0);
	
	//set transmitting character bit size to 8 bit
	UCSR0B &= ~(1<<UCSZ02);
	UCSR0C |=  ((1<<UCSZ00)|(1<<UCSZ01));
	
	//No stop bits (values of the relevant registers are zero when starting)
	//No parity bits (values of the relevant registers are zero when starting)
	
}

bool checkIfTransmitBufferIsFree(){
	if(UCSR0A & (1<<UDRE0)){
		return true;
	}
	return false;
}

void transmit(unsigned char inputChar){
	//check UDR0 (buffer) is free or not
	while(!checkIfTransmitBufferIsFree());
	
	if(checkIfTransmitBufferIsFree()){
	//if UDR0 is free store input character into the UDR0
		UDR0 = inputChar;		
	}



}


int main(void)
{
	configureUART();
	DDRB |= (1<<PORTB5);
	char message[] = {'E','S','D','6','3','5','2'};
    /* Replace with your application code */
    while (1) 
    {
		PORTB = (1<<PORTB5);
		for(int i=0; i<7;i++){
			transmit(message[i]);
		}
	}
	
	return 0;
}

