#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define state uint8_t
#define idleState 0x00U
#define helpState 0x01U
#define tempState 0x02U
#define ledControlState 0x03U
#define ledDelayState 0x04U
#define stringState 0x05U
#define BAUD 9600
#define BAUDPRESCALAR ((F_CPU/(BAUD))/16 - 1)
#define ADC_conversion (110.0/1024.0)
#define bool unsigned int
#define true  0x01
#define false 0x00

void initTimer1CTC();
void startTimer1CTC_OC();
void stopTimer1CTC_OC();
void waitForInput();

void initADC(uint8_t adcCh, uint8_t adcRef);
void adcStartConversion();
uint16_t readADC();

void initUART(uint8_t umsel, uint8_t upm, uint8_t usbs, uint8_t ucsz);
float convert_adc_to_c(uint16_t adcValue);
float convert_c_to_f(float celsius);
void convert_float_to_string(float floatNum);
void sendString_UART();

uint8_t convertToState();

volatile static uint8_t dataRegister;
volatile static uint16_t adcRegister;
volatile static uint8_t OC_Second;

//declaring bools

volatile static bool flashingTOGGLE = true;
volatile static bool uartBUSY = false;
volatile static bool adcDATA_READY = true;
volatile static bool adcBUSY = false;
volatile static bool flashingREADY = true;
volatile static bool newInput = false;
volatile static char* dataString;

static char charConversion[20];

//main loop

int main(void){
	volatile state currentState = idleState;
	volatile state nextState = helpState;
	volatile state stateRegister;
	DDRB = 0xFF;
	PORTB = 0xFF;
	initADC(0x04, 0x03);
	initTimer1CTC();
	initUART(0x00, 0x00, 0x00, 0x03);
	sei();
	while (1){
		currentState = nextState;
		
		//hanndle input
		
		if(currentState == idleState){
			if(newInput == true){
				newInput = false;
				nextState = convertToState();
			}
		}
		
		else if(currentState == helpState){
			nextState = idleState;
			//only way strings would output correctly
			dataString = "help menu \nenter key \nh : help menu \nt : temperature in C \nT : temperature in F \no : turn on LED at port B2 \nO : turn off LED at port B2 \ns : send a string delay for LED at port B3 \ni : send an integer delay for LED at port B3 \n\r";
			sendString_UART();
		}
		
		else if(currentState == tempState){
			nextState = idleState;
			adcStartConversion();
			if((char)dataRegister == 't'){
				dataString = "\n";
				sendString_UART();
				convert_float_to_string(convert_adc_to_c(readADC()));
				sendString_UART();
			}
			else if((char)dataRegister == 'T'){
				dataString = "\n";
				sendString_UART();
				convert_float_to_string(convert_c_to_f(convert_adc_to_c(readADC())));
				sendString_UART();
			}
		}
		
		else if(currentState == ledControlState){
			nextState = idleState;
			if((char)dataRegister == 'o'){
				PORTB &= ~(1<<2);
			}
			else if((char)dataRegister == 'O'){
				PORTB |=  (1<<2);
			}
		}
		
		else if(currentState == ledDelayState){
			nextState = idleState;
			waitForInput();
			if((char)dataRegister == 's'){
				OC_Second = OC_Second - 48;
				if(OC_Second == 0){
					stopTimer1CTC_OC();
					PORTB  |= (1U<<3);
				}
				else{
					OCR1A = (uint16_t)((F_CPU)/(1024)*OC_Second - 1);
					startTimer1CTC_OC();
				}
			}
			else if((char)dataRegister == 'i'){
				if(OC_Second == 0){
					stopTimer1CTC_OC();
					PORTB  |= (1U<<3);
				}
				else{
					OCR1A = (uint16_t)((F_CPU)/(1024)*OC_Second - 1);
					startTimer1CTC_OC();
				}
			}
		}
	}
}

//state transitions

uint8_t convertToState(){
	
	if(dataRegister == 'O' || dataRegister == 'o' ){
		return ledControlState;
	}
	else if(dataRegister == 'h'){
		return helpState;
	}
	else if(dataRegister == 'i' || dataRegister == 's'){
		return ledDelayState;
	}
	else if(dataRegister == 'T' || dataRegister == 't'){
		return tempState;
	}
	else return idleState;
}

//initialize adc

void initADC(uint8_t adcCh, uint8_t adcRef){
	ADMUX  |= (adcCh << 0) | (adcRef << 6);
	ADCSRA |= (0x07<<0);
}

//start conversion

void adcStartConversion(){
	adcBUSY = true;
	ADCSRA |= (1U<<7) | (1U<<6) | (1U<<3);
	while(adcBUSY){};
}

//read adc

uint16_t readADC(){
	return (ADCL | (ADCH<<8));
}

//initialize UART

void initUART(uint8_t umsel, uint8_t upm, uint8_t usbs, uint8_t ucsz){
	UBRR0H = (uint8_t)(0x00);
	UBRR0L = (uint8_t)(BAUDPRESCALAR);
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0);
	UCSR0C = (umsel << UMSEL00) | (upm   << UPM00) | (usbs  << USBS0) | (ucsz  << UCSZ00);
}

//converting adc reading to float

float convert_adc_to_c(uint16_t adcValue){
	return ((ADC_conversion) * (float)(adcValue));
}

//C to F

float convert_c_to_f(float celsius){
	return ((celsius * 9.0/5.0) + 32);
}

//float to string

void convert_float_to_string(float floatNum){
	snprintf(charConversion, sizeof(charConversion), "%f\n\r", floatNum);
	dataString = charConversion;
}

//send string

void sendString_UART(){
	UCSR0B |= ((1 << TXCIE0) |
	(1 << UDRIE0) |
	(1  << TXEN0));  //Enable interrupts and tx
}

//initialize timer 1 CTC

void initTimer1CTC(){
	TCCR1B |= (1U<<3);
}

//start timer

void startTimer1CTC_OC(){
	TCNT1 = 0x00;
	TIMSK1 |= (1U<<1);
	TCCR1B |= (0x05<<0);
}

//stop timer

void stopTimer1CTC_OC(){
	TCCR1B &= ~(0x07<<0);
	TIMSK1 &= ~(1U<<1);
}

//sub-idle in delay state

void waitForInput(){
	dataString = "\n enter delay in seconds (1-4), 0 to remove delay. \n\r";
	sendString_UART();
	flashingREADY = false;
	while(!flashingREADY){};
}

//flash

ISR (TIMER1_COMPA_vect){
	flashingTOGGLE = !flashingTOGGLE;
	if(flashingTOGGLE == true) PORTB |=  (1U<<3);
	else   PORTB &= ~(1U<<3);
}

ISR(ADC_vect){
	ADCSRA &= ~((1U<<3) | (1U<<7));
	adcBUSY = false;
}

//wait to deactivate TX until buffer is empty

ISR(USART0_TX_vect){
	UCSR0B &= ~((1 << TXCIE0) | (1  << TXEN0));
}

ISR(USART0_RX_vect){
	if(!flashingREADY){
		flashingREADY = true;
		OC_Second = UDR0;
	}
	else{
		dataRegister = UDR0;
		newInput = true;
	}
}

//send date until array empty, increase string location, else disable interrupts

ISR(USART0_UDRE_vect){
	if(*dataString != '\0'){
		UDR0 = *dataString;
		dataString++;
	}
	else{
		UCSR0B &= ~(1 << UDRIE0);
	}
}