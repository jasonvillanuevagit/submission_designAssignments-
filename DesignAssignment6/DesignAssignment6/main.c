#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>

//TW_CONFIG
#define PRESCALER				1U
#define SCL_FREQ_200kH			200000UL
#define SCL_FREQ_400kH			400000UL
#define TW_TWBR					(((F_CPU/SCL_FREQ_400kH) - 16)/(2*PRESCALER))
#define TW_config_SCL_200kH
#define TW_TWCR_TWINT	(1U<<7)
#define TW_TWCR_TWEA	(1U<<6)
#define TW_TWCR_TWSTA   (1U<<5)
#define TW_TWCR_TWSTO	(1U<<4)
#define TW_TWCR_TWWC	(1U<<3)
#define TW_TWCR_TWEN	(1U<<2)
#define TW_TWCR_TWIE	(1U)
#define TW_TWSR_scaler64 (3U<<0)
#define TW_TWSR_scaler4  (1U<<0)
#define TW_TWSR_scaler1  (0U<<0);

//PWM
#define PWM_8Scalar				0x02
#define PWM_noScalar			0x01
#define PWM_WGM_11_10			0x02
#define PWM_WGM_13_12			0x02
#define PWM_nonInvert			0x02
#define PWM_timerOVR			0x01

//Bool
#define bool uint8_t
#define true 0x01U
#define false 0x00U

#define MPU6050_conversion_accel_2g		16384.0
#define MPU6050_conversion_gyro_250dps	131.0
#define MPU6050_conversion_gyro_2000dps 16.4
#define MPU6050_conversion_radians_to_degrees (180.0/acos(-1))

typedef enum{
	MasterTX_Data,
	MasterTX_Done,
}status_t;

typedef struct{
	
	volatile int8_t rx[12];
	volatile uint8_t rxCounter;
	volatile uint8_t tx;
	volatile uint8_t slaveAddr;
	volatile uint8_t regAddr;
	volatile bool busy;
	volatile status_t status;
	
}TW_data_t;

typedef struct{
	
	volatile float X;
	volatile float Y;
	volatile float Z;

}accel_t;

typedef struct{
	
	volatile float X;
	volatile float Y;
	volatile float Z;
	
	volatile float xErr;
	volatile float yErr;
	volatile float zErr;

}gyro_t;

typedef struct{
	volatile float curr_Angle;
	volatile float prev_Angle;
}tilt_angle_t;

TW_data_t TW_data;
accel_t accel_data;
gyro_t gyro_data;
tilt_angle_t roll_angle;
tilt_angle_t pitch_angle;

volatile bool sampleReady = false;

#define MPU6050_FIFO_RegEn	  TW_send(0x68, 35U, ((1U<<6)|(1U<<5)|(1U<<4)|(1U<<3)))
#define MPU6050_FIFO_EN		  TW_send(0x68, 106U, (1U<<6))
#define MPU6050_CLEAR_STATUS  TW_receive(0x68, 58U, 1)
#define MPU6050_FIFO_CLEAR    TW_send(0x68, 106U, (1U<<2));


//Uart
#define rxEN 1
#define txIEN 1
#define drIEN 1
#define txEN 1
#define eightBit 0x03
#define async 0x00
#define sync 0x01
#define noParity 0x00
#define oneStop 0x00
#define twoStop 0x01
#define chSize8 0x03
#define BAUD 300000UL
#define BAUDPRESCALAR ((F_CPU/(BAUD))/16 - 1) //Register Values
static volatile unsigned int usartBUSY;  //ISR variables
static volatile char* dataString;
static char charConversion[20];


void TW_send(uint8_t slaveAddr, uint8_t regAddr, uint8_t dataTx);
void TW_receive(uint8_t slaveAddr, uint8_t regAddr, uint8_t rxCounter);
void initiate_TW();
void TW_Status_Code_TX();
void TW_Status_Code_RX();
float combineRegisters(int16_t high, int16_t low);
float calculateSensorData(int16_t data, int16_t conversion);
void convert_float_to_string(float floatNum);
void sendString_UART();
void initUART(uint8_t umsel, uint8_t upm, uint8_t usbs, uint8_t ucsz);
void UART_Send_Values();
void calculatePosition();
void inititate_MPU6050();
void initiate_INT0();
void storeSensorValues_Accel();
void storeSensorValues_Gyro();
float calculateAngle_Pitch_Accel();
float calculatetAngle_Roll_Accel();
float calculateAngle_Pitch_Gyro();
float calculatetAngle_Roll_Gyro();
float complementaryFilter(float gyro_angle, float accel_angle, tilt_angle_t* angle);
void calculateGyroError();
void storeGyroError();
void initTimer1PWM(unsigned int top);
void startPWM1();
void sendMessage(char* mess);
void send_accel_values(accel_t*);
void send_gyro_values(gyro_t*);

#define dt 0.0100
#define scale_gyro   .96
#define scale_accel  .02

volatile float temp;

int main(void){
	TW_data.rx[0] = 0xFF;
	DDRB = (1U << 1); //DDRB.1 out OC1A
	initiate_TW();
	initUART(async, noParity, oneStop, eightBit); //initiate UART 8-N-1
	initiate_INT0();
	initTimer1PWM(20000);
	sei();
	
	startPWM1(); //start PWM
	inititate_MPU6050();
	calculateGyroError();

	while (1){
		
		if(sampleReady){
			sampleReady = false;
			storeSensorValues_Accel();
			storeSensorValues_Gyro();
			send_accel_values(&accel_data);
			send_gyro_values(&gyro_data);
			pitch_angle.curr_Angle = complementaryFilter(calculateAngle_Pitch_Gyro(), calculateAngle_Pitch_Accel(), &pitch_angle);
			convert_float_to_string(pitch_angle.curr_Angle);
			sendString_UART();
			sendMessage(" ");
			roll_angle.curr_Angle  = complementaryFilter(calculatetAngle_Roll_Gyro(), calculatetAngle_Roll_Accel(), &roll_angle);
			convert_float_to_string(roll_angle.curr_Angle);
			sendString_UART();
			sendMessage(" ");
			sendMessage("\r\n");
			TW_receive(0x68, 58U, 1);
		}
	}
}

void TW_Status_Code_TX(){
	switch(TWSR0 & 0xF8){
		case 0x08:
		(TWDR0 = (TW_data.slaveAddr<<1));
		(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		break;
		case 0x18:
		(TWDR0 = TW_data.regAddr);
		TW_data.status = MasterTX_Data;
		(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		break;
		case 0x28:
		if(TW_data.status == MasterTX_Data){
			(TWDR0 = TW_data.tx);
			TW_data.status = MasterTX_Done;
			(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		}
		else{
			(TWCR0 = TW_TWCR_TWSTO|TW_TWCR_TWEN | TW_TWCR_TWINT);
			TW_data.busy = false;
		}
		break;
		default:
		TW_data.busy = false;
		
	}
}

void TW_Status_Code_RX(){
	switch((TWSR0 & 0xF8)){
		case 0x08:
		(TWDR0 = (TW_data.slaveAddr<<1));
		(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		break;
		case 0x18:
		(TWDR0 = TW_data.regAddr);
		(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		break;
		case 0x28:
		(TWCR0 = TW_TWCR_TWSTA|TW_TWCR_TWEN | TW_TWCR_TWINT);
		break;
		case 0x10:
		(TWDR0 = ((TW_data.slaveAddr<<1) | 0x01));
		(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		break;
		case 0x40:
		if(TW_data.rxCounter == 0){
			(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		}
		else{
			(TWCR0 = TW_TWCR_TWEA|TW_TWCR_TWEN | TW_TWCR_TWINT);
		}
		break;
		case 0x50:
		if(TW_data.rxCounter == 1){
			TW_data.rx[TW_data.rxCounter] = (TWDR0);
			(TWCR0 = TW_TWCR_TWEN|TW_TWCR_TWINT);
		}
		else{
			TW_data.rx[TW_data.rxCounter] = (TWDR0);
			TW_data.rxCounter--;
			(TWCR0 = TW_TWCR_TWEA|TW_TWCR_TWEN | TW_TWCR_TWINT);
		}
		break;
		case 0x58:
		TW_data.rx[0] =  (TWDR0);
		(TWCR0 = TW_TWCR_TWSTO|TW_TWCR_TWEN | TW_TWCR_TWINT);
		TW_data.busy = false;
		break;
		default:
		TW_data.busy = false;
	}
}

void sendMessage(char* mess){
	dataString = mess;
	sendString_UART();
}

void send_gyro_values(gyro_t* gyro){
	convert_float_to_string(gyro->X);
	sendString_UART();
	sendMessage(" ");
	convert_float_to_string(gyro->Y);
	sendString_UART();
	sendMessage(" ");
	convert_float_to_string(gyro->Z);
	sendString_UART();
	sendMessage(" ");
	
}

void send_accel_values(accel_t* accel){
	convert_float_to_string(accel->X);
	sendString_UART();
	sendMessage(" ");
	convert_float_to_string(accel->Y);
	sendString_UART();
	sendMessage(" ");
	convert_float_to_string(accel->Z);
	sendString_UART();
	sendMessage(" ");
}

void calculatePosition(){
	if(pitch_angle.curr_Angle < 0){
		OCR1A = (uint16_t)(1500 + pitch_angle.curr_Angle*7.5);
	}
	else{
		OCR1A = (uint16_t)(1500 + pitch_angle.curr_Angle*7.5);
	}
}

void initiate_INT0(){
	DDRD &= ~(1<<2);
	PORTD &= ~(1<<2);
	EICRA = 0x03;
	EIMSK = 0x01;
}

void inititate_MPU6050(){
	sampleReady = false;
	pitch_angle.prev_Angle = 0;
	roll_angle.prev_Angle = 0;
	gyro_data.X = 0;
	gyro_data.Y = 0;
	gyro_data.Z = 0;
	TW_send(0x68, 27U, (3U<<3));
	TW_send(0x68, 25U, 47U);
	TW_send(0x68, 55U, 0x20);
	TW_send(0x68, 56U, 0x01);
	TW_send(0x68, 0x6B, 0x00);
	TW_receive(0x68, 58U, 1);
}

void storeSensorValues_Gyro(){
	volatile uint8_t sensorValH;
	volatile uint8_t sensorValL;
	TW_receive(0x68, 0x43, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x44, 1);
	sensorValL = TW_data.rx[0];
	gyro_data.X = calculateSensorData(combineRegisters(sensorValH, sensorValL)-gyro_data.xErr, MPU6050_conversion_gyro_2000dps);
	TW_receive(0x68, 0x45, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x46, 1);
	sensorValL = TW_data.rx[0];
	gyro_data.Y = calculateSensorData(combineRegisters(sensorValH, sensorValL)-gyro_data.yErr, MPU6050_conversion_gyro_2000dps);
	TW_receive(0x68, 0x47, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x48, 1);
	sensorValL = TW_data.rx[0];
	gyro_data.Z = calculateSensorData(combineRegisters(sensorValH, sensorValL)-gyro_data.zErr, MPU6050_conversion_gyro_2000dps);
}


void calculateGyroError(){
	for(unsigned int i = 0; i < 200; i++){
		while(!sampleReady);
		sampleReady = false;
		storeGyroError();
		TW_receive(0x68, 58U, 1);
	}
	
	gyro_data.xErr = gyro_data.X/200;
	gyro_data.yErr = gyro_data.Y/200;
	gyro_data.zErr = gyro_data.Z/200;
	gyro_data.X = 0;
	gyro_data.Y = 0;
	gyro_data.Z = 0;
	TW_receive(0x68, 58U, 1);
}

void storeGyroError(){
	volatile uint8_t sensorValH;
	volatile uint8_t sensorValL;
	TW_receive(0x68, 0x43, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x44, 1);
	sensorValL = TW_data.rx[0];
	gyro_data.X += combineRegisters(sensorValH, sensorValL);
	
	TW_receive(0x68, 0x45, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x46, 1);
	sensorValL = TW_data.rx[0];
	gyro_data.Y += combineRegisters(sensorValH, sensorValL);
	
	TW_receive(0x68, 0x47, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x48, 1);
	sensorValL = TW_data.rx[0];
	gyro_data.Z += combineRegisters(sensorValH, sensorValL);
	
	
}

void storeSensorValues_Accel(){
	
	volatile uint8_t sensorValH;
	volatile uint8_t sensorValL;
	
	TW_receive(0x68, 0x3B, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x3C, 1);
	sensorValL = TW_data.rx[0];
	accel_data.X = calculateSensorData(combineRegisters(sensorValH, sensorValL), MPU6050_conversion_accel_2g);
	TW_receive(0x68, 0x3D, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x3E, 1);
	sensorValL = TW_data.rx[0];
	accel_data.Y = calculateSensorData(combineRegisters(sensorValH, sensorValL), MPU6050_conversion_accel_2g);
	TW_receive(0x68, 0x3F, 1);
	sensorValH = TW_data.rx[0];
	TW_receive(0x68, 0x40, 1);
	sensorValL = TW_data.rx[0];
	accel_data.Z = calculateSensorData(combineRegisters(sensorValH, sensorValL), MPU6050_conversion_accel_2g);
	
}

float combineRegisters(int16_t high, int16_t low){
	return ((high<<8) | low);
}

float calculateSensorData(int16_t data, int16_t conversion){
	return ((float)data/(float)conversion);
	
}

float calculateAngle_Pitch_Accel(){
	return (float)(atan(accel_data.Y/sqrt(accel_data.X*accel_data.X + accel_data.Z*accel_data.Z))*MPU6050_conversion_radians_to_degrees);
}

float calculatetAngle_Roll_Accel(){
	return (float)(atan(accel_data.X/(sqrtf(accel_data.Y*accel_data.Y + accel_data.Z*accel_data.Z)))*MPU6050_conversion_radians_to_degrees);
}

float calculateAngle_Pitch_Gyro(){
	return (gyro_data.X * dt);
}

float calculatetAngle_Roll_Gyro(){
	return (gyro_data.Y * dt);
}

float complementaryFilter(float gyro_angle, float accel_angle, tilt_angle_t* angle){
	angle->prev_Angle = (float)(((gyro_angle + angle->prev_Angle) * scale_gyro) + (accel_angle * scale_accel));
	return angle->prev_Angle;
}

void TW_send(uint8_t slaveAddr, uint8_t regAddr, uint8_t dataTx){
	TW_data.busy = true;
	TW_data.slaveAddr = slaveAddr;
	TW_data.tx = dataTx;
	TW_data.regAddr = regAddr;
	(TWCR0 = TW_TWCR_TWSTA|TW_TWCR_TWEN);
	while(TW_data.busy){
		while(!(TWCR0 & (1U<<TWINT))){};
		TW_Status_Code_TX();
		
	}
	(TWCR0 = 0x00);
}

void TW_receive(uint8_t slaveAddr, uint8_t regAddr, uint8_t rxCounter){
	
	TW_data.busy = true;
	TW_data.slaveAddr = slaveAddr;
	TW_data.regAddr = regAddr;
	TW_data.rxCounter = rxCounter - 1;
	(TWCR0 = TW_TWCR_TWSTA|TW_TWCR_TWEN);
	while(TW_data.busy){
		while(!(TWCR0 & (1<<TWINT))){};
		TW_Status_Code_RX();
	}
	(TWCR0 = 0x00);
}

void initiate_TW(){
	TWBR0 = TW_TWBR;
	TWSR0 |= TW_TWSR_scaler1;
}

void convert_float_to_string(float floatNum){
	snprintf(charConversion, sizeof(charConversion), "%f ", floatNum);
	dataString = charConversion;
}

void sendString_UART(){
	//USART busy, enable TX and interrupts
	usartBUSY = 0x01;
	UCSR0B |= ((txIEN << TXCIE0) |
	(drIEN << UDRIE0) |
	(txEN  << TXEN0));
	while(usartBUSY);
}


void initUART(uint8_t umsel, uint8_t upm, uint8_t usbs, uint8_t ucsz){
	//initiates UART Baud and sets it to a 8-N-1 setting
	UBRR0H = (uint8_t)(0x00);
	UBRR0L = (uint8_t)(BAUDPRESCALAR);
	UCSR0C = (umsel << UMSEL00) |
	(upm   << UPM00)	|
	(usbs  << USBS0)	|
	(ucsz  << UCSZ00);
}

void initTimer1PWM(unsigned int top){
	//inititate PWM
	TCCR1A |= (PWM_nonInvert << COM1A0);
	ICR1    = (top);
}

void startPWM1(){
	//start PWM
	TCNT1L = 0x00;
	TCNT1H = 0x00;
	TCCR1A |= (PWM_WGM_11_10 << WGM10);
	TCCR1B |= (PWM_WGM_13_12 << WGM12);
	TIMSK1 |= (PWM_timerOVR << TOIE1);
	TCCR1B |= (PWM_8Scalar  << CS10);
}

ISR(USART0_UDRE_vect){
	//if datastring is not empty send character
	//else send disable interrupt and signal when usart is done
	if(*dataString != '\0'){
		UDR0 = *dataString;
		dataString++;
	}
	else{
		UCSR0B &= ~(drIEN << UDRIE0);
		usartBUSY = 0x00;
	}
}

ISR(TIMER1_OVF_vect){
	calculatePosition();
}

ISR(USART0_TX_vect){
	//disables TX and
	UCSR0B &= ~((txIEN << TXCIE0) |
	(txEN  << TXEN0));
}

ISR(INT0_vect){
	sampleReady = true;
}

