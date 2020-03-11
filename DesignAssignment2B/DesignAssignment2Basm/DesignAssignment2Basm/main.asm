JMP DUTY_CYCLE 
.ORG 0X02;LOCATION FOR EXTERNAL INTERRUPT 0
JMP EX0_ISR;JUMP TO EXTERNAL INTERUPT LABEL

	LDI R20, HIGH(RAMEND)
	OUT SPH, R20
	LDI R20, LOW(RAMEND)
	OUT SPL, R20;INITIALIZE STACK

DUTY_CYCLE:
	LDI R20, 0X2;MAKE INT0 INTO FALLING EDGE TRIGGERED 
	STS EICRA, R20;EXTERNAL INTERUPT CONTROL REG 'A' NOW FALLING EDGE
	 
	SBI DDRB, 3;DIRECTION PORTB.3 OUTPUT 
	SBI PORTB, 3;SETTING PORTB.3 BIT "LED ON" 
	CALL DELAY_413ms;CALL DELAY_413ms (.413s)
	CBI PORTB, 3;CLEARING PORTB.3 BIT "LED OFF"
	CALL DELAY_337ms;CALL DELAY_337ms (.337s)
	
	LDI R20, 1 << INT0;ENABLE INTERRUPT 0 
	OUT EIMSK, R20;MAKES MASK REGISTER ENABLED OUTPUT
	SEI;ENABLE GLOBAL INTERRUPT 

RJMP DUTY_CYCLE

EX0_ISR:
	CBI DDRB, 3;CLEARING DIRECTION PORTB.3 OUTPUT 
	SBI DDRB, 2;DIRECTION OF PORTB.2 OUTPUT "LED ON"	
	CALL DELAY_BUTTON;CALL DELAY OF 2s
	CBI DDRB, 2;CLEARING DIRECTION PORTB.2 OUTPUT
	RETI


DELAY_413ms:;DELAY OF .413s
    LDI r18, 34
    LDI r19, 134
    LDI r20, 185
L1: DEC r20
    BRNE L1
    DEC r19
    BRNE L1
    DEC r18
    BRNE L1
    NOP
	RET

DELAY_337ms:;DELAY OF .337s			
    LDI r18, 28
    LDI r19, 91
    LDI r20, 132
L2: DEC r20
    BRNE L2
    DEC r19
    BRNE L2
    DEC r18
    BRNE L2
	RET

DELAY_BUTTON:;DELAY OF 2s
    ldi  r18, 163
    ldi  r19, 87
    ldi  r20, 2
L3: dec  r20
    brne L3
    dec  r19
    brne L3
    dec  r18
    brne L3
	RET