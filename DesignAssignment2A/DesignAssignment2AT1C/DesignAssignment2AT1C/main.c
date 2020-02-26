#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>


int main(void)
{
    DDRB |= (1<<3);//MAKING PORTB.3 OUTPUT
	PORTB &= ~(1<<3);//MAKING PORTB.3 OUTPUT "OFF"

    while (1) 
    {
		PORTB |=(1<<3);//OUTPUT "LED ON"
		_delay_ms(413);//DELAY FOR 413ms @16MHz
		PORTB &=~(1<<3);//OUTPUT "LED OFF"
		_delay_ms(337);//DELAY FOR 337ms @16MHz
    }
	return 1;
}
