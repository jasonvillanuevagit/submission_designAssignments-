#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>


int main(void)
{
	DDRB |= (1<<3);	//MAKING PORTB.3 OUTPUT
	PORTB &= ~(1<<3);//MAKING PORTB.3 OUTPUT "OFF"
	DDRC &=~(1<<3);	//MAKING PORTC.3 INPUT
	PORTC |= (1<<3);//PULL UP RESISTOR ACTIVATED PINC.3 BUTTON
	while (1)
	{
		PORTB |=(1<<3);//OUTPUT "LED ON"
		_delay_ms(413);//DELAY FOR 413ms @16MHz
		PORTB &=~(1<<3);//OUTPUT "LED OFF"
		_delay_ms(337);	//DELAY FOR 337ms @16MHz
		
		if(!(PINC & (1<<3)))
		{
			DDRB &=~(1<<3);//MAKING PORTB.3 OUTPUT "LED OFF"
			DDRB |= (1<<2);//MAKING PORTB.2 OUTPUT "LED ON"
			_delay_ms(2000);//DELAY FOR 3s
			DDRB &=~(1<<2);	//MAKING PORTB.2 OUTPUT "OFF"
			PORTB &=~(1<<2);//PORTB.2 OUTPUT "LED OFF"
			DDRB |= (1<<3);	//MAKING PORTB.3 OUTPUT "ON"
		}
	}
	return 1;
}

