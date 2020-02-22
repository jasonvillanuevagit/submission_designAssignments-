.ORG 0X0000
	
.EQU STARTADDS = 0X0300;memory location for the 200 numbers

LDI XL,LOW(STARTADDS);pointer to initial set of numbers
LDI XH,HIGH(STARTADDS)
LDI YL,LOW(0X0700);	;pointer to numbers from initial set that are divisible by 7 and 3
LDI YH,HIGH(0X0700)
LDI ZL,LOW(0X0800);pointer to numbers not divisible by 7 and 3
LDI ZH,HIGH(0X0800)
LDI R22, 0;initialize r22 for holding current number being tested
LDI R21, 200;store iteration count
LDI R20, 25	;where to start the loop
CLR r26	;r26 for carry
CLR r25	;registers to store numbers after tested conditions
CLR r24						
CLR r23						
CLR r22					

STORE: 
	INC R20					
	ST X+, R20;storing intial numbers to memory							
	MOV R22, R20			
	MOV R19, R20
	JMP check_div7			

LOOP_COUNTER:;loop to parse through each number in initial set
	DEC R21					
	BRNE STORE			
	JMP DONE				
	
check_div7:;loop to check if number is divisible by 7
	CPI R22, 7				
	BRLO Ndiv_7				
	SUBI R22, 7				
	CPI R22, 0				
	BREQ div_7					
	JMP check_div7 					
		
check_div3:	; check if number is divisible by 3 (if not divisible by 7)
	CPI r19, 3				
	BRLO Ndiv_3				
	SUBI r19, 3			
	CPI r19, 0				
	BREQ div_3							
	JMP check_div3 			 		
		
div_7:;if divisible by 7 store to memory
	ST Y+, R20				
	ADD r22, R20			
	ADC r23, r26				
	JMP LOOP_COUNTER		
div_3:;store in memory if divisible by 3
	ST Y+, R20				
	ADD r19, R20			
	ADC r23, r26			
	JMP LOOP_COUNTER			
	
Ndiv_7:;if not divisible by 7 store to memory 
	ST Z+, R20              						
	ADD r24, R20			
	ADC r25, r26			
	JMP check_div3		
	
Ndiv_3:	;if not divisible by 3 store to memory

	;ST Z+, R20              
	ADD r24, R20			
	ADC r25, r26			
	JMP LOOP_COUNTER			
	
DONE: JMP DONE;end of program
