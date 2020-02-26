;designed for clock frequency of 16MHz
DUTY_CYCLE:
 
	SBI DDRB, 3					;DIRECTION PORTB.3 OUTPUT 
	SBI PORTB, 3				;SETTING PORTB.3 BIT "LED ON" 
	CALL DELAY_413ms			;CALL DELAY_413ms (.413s)
	CBI PORTB, 3				;CLEARING PORTB.3 BIT "LED OFF"
	CALL DELAY_337ms			;CALL DELAY_337ms (.337s)

RJMP DUTY_CYCLE

DELAY_413ms:			;DELAY OF .413s
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

DELAY_337ms:			;DELAY OF .337s			
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