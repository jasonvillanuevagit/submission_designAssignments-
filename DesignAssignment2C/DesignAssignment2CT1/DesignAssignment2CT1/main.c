#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void set(){
	TCCR0A = 0;//NORMAL MODE OPERATION
	TCCR0B  = 0X05;//THE PRESCALER SET TO 1024
	TCNT0 = 0X00;//COUNTER VALUE = 0
}

void On_413(){
	int cycle = 25;//CYCLE AMOUNT FOR 413ms
	DDRB |= (1<<3);//SET PORTB.3 "ON"
	while (cycle != 0){
		cycle --;
		while((TIFR0 & 0X01) == 0);
		TIFR0 = 0X01;//RESET OVERFLOW FLAG
	}
}

void Off_337(){
	int cycle = 20;//CYCLE AMOUNT FOR 337ms
	DDRB = (0<<3);//SET PORTB.3 "OFF"
	while (cycle != 0){
		cycle --;
		while ((TIFR0 & 0X01) == 0);
		TIFR0 = 0X01;//RESET OVERFLOW FLAG
	}
}

void Button(){
	int cycle = 122;//CYCLE AMOUNT FOR 2s
	DDRB = (0<<3);//SET PORTB.3 "OFF"
	DDRB |= (1<<2);//SET PORTB.2 "ON"
	while (cycle != 0){
		cycle --;
		while ((TIFR0 & 0X01) == 0);
		TIFR0 = 0X01;//RESET OVERFLOW FLAG
	}
	DDRB = (0<<3);//SET PORTB.3 "OFF"
}

int main(void){
	DDRC &=~ (1<<3);//SET PORTC.3 INPUT
	PORTC |= (1<<3);//PULL-UP RESISTOR ACTIVATE
	while (1){
		set();//CALL SET FCT
		if (!(PINC & (1 <<3))){//IF BUTTON PRESS @ PINC.3
			Button();//CALL BUTTON FCT
		}
		On_413();//CALL On_413 FCT
		Off_337();//CALL Off_337 FCT
	}
	return 1;
}

