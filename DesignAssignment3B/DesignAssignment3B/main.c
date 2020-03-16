#define BAUD 9600
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

//"Global variable"
volatile uint8_t Overflow;
//"Global variable"
volatile float adc_temp_F;
volatile float adc_temp_C;

//FUNCTION TO INITIALIZE USART
void USART_init(void){
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);//8-BIT DATA
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);//ENABLE RX AND TX
}

//FUNCTION TO INITIALIZE ADC
void adc_init(void){
	ADMUX =  (0<<REFS1) | //REFERENCE SELECTION BITS
	(1<<REFS0) | //AVcc -External cap at AREF 5V
	(0<<ADLAR) | //ADC RIGHT ADJUST RESULT
	(1<<MUX2)  | //ANALOG CHANNEL SELECTION BITS
	(0<<MUX1)  | //ADC4 (PC4) CHANNEL 4
	(0<<MUX0);
	
	ADCSRA = (1<<ADEN)  | //ADC ENABLE
	(0<<ADSC)  | //ADC START CONVERSION
	(0<<ADATE) | //ADC auto trigger enable
	(0<<ADIF)  | //ADC interrupt flag
	(0<<ADIE)  | //ADC interrupt enable
	(1<<ADPS2) | //ADC PRESCALAR SELECTION BITS
	(1<<ADPS1) | //128 AS PRESCALAR SEL. BITS
	(1<<ADPS0);
}

//FUNCTION THAT SETS TIMER/INTERRUPT REGISTERS
void set(){
	TCCR0A = 0;//NORMAL MODE OPERATION
	TCCR0B  = 0X05;//THE PRESCALER SET TO 1024
	TCNT0 = 0X00;//COUNTER VALUE = 0
	TIMSK0 = (1<<TOIE0);//ENABLE INTERRUPT
	sei();//ENABLE GLOBAL INTERRUPT
}

//INTERUPT SUBROUTINE FOR TIMER 0
ISR(TIMER0_OVF_vect){
	Overflow++;//INCREMENT OVERFLOW
}

//FUNCTION THAT READS IN 1 CHAR AT A TIME
void USART_tx_string(char*data){
	//CONTROL ENTERS WHILE DATA REG NOT EMPTY
	while((*data!='\0')){
		//WAIT FOR BUFFER REGISTER TO CLEAR
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = *data;//REGESTER EQUALS DATA
		data++;//DATA MOVES POSITION
	}
}

void read_adc_F(void){
	unsigned char i = 10;//Variable for sample amounts
	adc_temp_F = 0;//Initialize adc_temp_F
	while(i--){
		ADCSRA |= (1<<ADSC);//Enable Start Conversion
		while(ADCSRA & (1<<ADSC));//Wait until enable & start conversion
		adc_temp_F += ADC;//LM35 value added & stored into adc_temp_F
	}
	adc_temp_F = (adc_temp_F/10) + 6;//Average of LM35 values
	adc_temp_C = (adc_temp_F - 32) * 5 / 9;
	
}

int main(void){
	USART_init();//Initialize USART
	adc_init();//Initialize ADC
	set();//Initialize Timers/Interrupts
	
	char char_array_F[20];//Character array of 20 for float F
	char char_array_C[20];//Character array of 20 for float C
	
	while (1){
		//CONTROL WILL ENTER IF OVERFLOW >= 30 CYCLES ~.5sec
		if (Overflow == 30){
			read_adc_F();//Call Read Functions
			
			snprintf(char_array_F,sizeof(char_array_F), "%f\r\n", adc_temp_F);
			snprintf(char_array_C,sizeof(char_array_C), "%f\r\n", adc_temp_C);

			//Prints temperature value
			USART_tx_string("\n");
			USART_tx_string("Temp in F: ");
			USART_tx_string(char_array_F);
			USART_tx_string("Temp in C: ");
			USART_tx_string(char_array_C);
			USART_tx_string("\n");
			
			//Overflow reset to 0
			Overflow = 0;
		}
	}
}

