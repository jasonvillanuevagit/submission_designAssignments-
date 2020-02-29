#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1<<3);//SET PORTB.3 OUTPUT
	PORTB &=~(1<<3);//TURN LED @ PORTB.3 OFF
	EICRA = 0X02;//EXTERNAL INTERRUPT CONTROL
	//REG "A" FALLING EDGE ENABLED
	
	EIMSK = (1<<INT0);//ENABLE EXTERNAL INTERRUPT 0
	sei ();//GLOBAL INTERRUPT ENABLE
	
	while(1)
	{
		PORTB |= (1<<3);//TURN "LED ON" @ PORTB.3
		_delay_ms(413);//DELAY FOR 413ms
		PORTB &= ~(1<<3);//TURN "LED OFF" @ PORTB.3
		_delay_ms(337);//DELAY FOR 337ms
	}
}

ISR (INT0_vect)//ISR FOR EXTERNAL INTERUPT 0
{
	DDRB &= ~(1<<3);//CLEAR DIRECTION PORTB.3
	DDRB |= (1<<2);//DIRECTION PORTB.2 OUTPUT "LED ON"
	_delay_ms(2000);//DELAY FOR 2s
	PORTB &=~(1<<2);//CLEAR PORTB.2 "LED OFF"
	DDRB &=~(1<<2);//CLEAR DIRECTION PORTB.2
	DDRB |= (1<<3);//DIRECTION PORTB.3 OUTPUT
}
