#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

//global variable
volatile float adc_value;

//function prototypes
void adc_init(void);
void read_adc(void);

//main
int main(void){
	adc_init();//initialize adc
	DDRC  |=  (0<<3);//port c3 input
	PORTC |=  (1<<3);//activate pullup resistors
	PORTC |=  (1<<0);
	DDRB  |=  (1<<DDB1);//port pb1 output
	PCICR = (1<<PCIE1);//pin change interrupt control register
	PCMSK1 = (1<<PCINT11);//enable mask register c3
	sei ();//enable global interrupts
	ICR1 = 0XFFFF;
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12)|(1<<WGM13);
	TCCR1B |= (1<<CS10);
	while (1 ){
		read_adc();
		_delay_ms(50);
		//PWM at 95% max
		if ((adc_value >= 62258) && (adc_value < 65535 )){
			OCR1A = 62258;
			_delay_ms(20);
		}
		//increasing PWM as resistor value increases
		else if ((adc_value < 62257) && (adc_value >= 3277)){
			OCR1A = adc_value + 30000;
			_delay_ms(20);
		}
		//PWM is 0%
		else
		OCR1A = 0x00;
	}
	return 0;
}

//interrupt subroutine
ISR(PCINT1_vect){
	DDRC ^= (1<<0);
}

//initializes adc
void adc_init(void){
	ADMUX =  (0<<REFS1) | (1<<REFS0) | (1<<ADLAR) | (0<<MUX2)  | (0<<MUX1)  | (0<<MUX0);
	ADCSRA = (1<<ADEN)  | (0<<ADSC)  | (0<<ADATE) | (0<<ADIF)  | (0<<ADIE)  | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
}

//read adc pins
void read_adc(void){
	unsigned char i = 10;//variable for sample amounts
	adc_value = 0;//initialize adc_value
	while(i--){
		ADCSRA |= (1<<ADSC);//enable start conversion
		while(ADCSRA & (1<<ADSC));//wait until enable & start conversion
		adc_value += ADC;//PC0 value added & stored into adc_value
	}
	adc_value = adc_value/10;//average of values
}


