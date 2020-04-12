#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

//global Variable
volatile float adc_value;

//prototypes
void adc_init(void);
void read_adc(void);

//main function 
int main(void){
	adc_init();//initialize ADC
	PORTC |=  (1<<0);//pull Up Resistor Activated PC0
	DDRB = (1<<1);//output PB1
	DDRD = 0x0F;//outputs PD3, PD2, PD1, PD0
	
	
	//configuration of timer1
	ICR1 = 4999;  //freq = 50Hz, period = 20ms
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
	TCCR1A |= (1<<WGM11);//CTC Mode
	TCCR1B |= (1<<WGM12)|(1<<WGM13);//CTC Mode
	TCCR1B |= (1<<CS10) |(1<<CS11);//prescaler 64
	
	while (1){
		read_adc();//call Read function
		_delay_ms(50);
		
		//stepper motor configurations
		PORTD = 0x66;
		_delay_ms(50);
		
		PORTD = 0xCC;
		_delay_ms(50);
		
		PORTD = 0x99;
		_delay_ms(50);
		
		PORTD = 0x33;
		_delay_ms(50);
		
		//PWM at 95% to max
		if ((adc_value >= 973) && (adc_value < 1024 )){
			_delay_ms(10);//create small delay
		}
		//decreasing PWM As resistor val decreases
		else if ((adc_value < 972) && (adc_value >= 768)){
			_delay_ms(50);  //create delay
		}
		//decreasing PWM As resistor value decreases
		else if ((adc_value < 767) && (adc_value >= 51)){
			_delay_ms(100); //create delay
		}
		//PWM is 0% If Resistor Value < 5%
		else{
			PORTD = 0x00;
			_delay_ms(100); //create delay
		}
	}
	return 0;
}

//adc initialize function
void adc_init(void){
	ADMUX =  (0<<REFS1) | (1<<REFS0) | (1<<ADLAR) | (0<<MUX2)  | (0<<MUX1)  | (0<<MUX0);
	ADCSRA = (1<<ADEN)  | (0<<ADSC)  | (0<<ADATE) | (0<<ADIF)  | (0<<ADIE)  | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
}

//read adc function
void read_adc(void){
	unsigned char i = 10;		   	 //variable for sample amounts
	adc_value = 0;			       	 //initialize adc_value
	while(i--)
	{
		ADCSRA |= (1<<ADSC);	     //enable Start Conversion
		while(ADCSRA & (1<<ADSC));   //wait until enable & start conversion
		adc_value += ADC;            //PC0 value added & stored into adc_value
	}
	adc_value = adc_value/10;	     //average of values
}

