;**********************************
;******** MSYS LAB4,DEL 1  ********
;******** Henning Hargaard ********
;**********************************

;*********** INITIERING ***********
   LDI  R16,HIGH(RAMEND)  ;Initier Stack Pointer
   OUT  SPH,R16
   LDI  R16,LOW(RAMEND)
   OUT  SPL,R16
   SER  R16
   OUT  DDRB,R16          ;PB benene er udgange 

;---> Skriv kode her, der konfigurer PA benene til INDGANGE
   LDI R17,0b00000000
   OUT DDRA,R17
 
;********** PROGRAM LOOP **********
;---> Skriv kode her, der aftaster de 8 trykknapper og
;     spiller den korrekte tone, mens en knap holdes nede. 
;     Når ingen knap holdes nede, skal lydgiveren være tavs. 
HERE: 
	SBIS PINA,7
	LDI R18,239 ;c
	SBIS PINA, 6
	LDI R18,213 ;D
	SBIS PINA,5
	LDI R18,190 ;E
	SBIS PINA,4
	LDI R18,179 ;F
	SBIS PINA,3
	LDI R18,160 ;G
	SBIS PINA,2
	LDI R18,142 ;A
	SBIS PINA,1
	LDI R18,127 ;H
	SBIS PINA,0
	LDI R18,120 ;C
	IN R19,PINA
	CPI R19,0xFF
	BREQ HERE
	COM R16
	OUT PORTB,R16
	CALL DELAY
    RJMP HERE

;********* DELAY (R18*4us) ********
DELAY:
   LDI  R17,20
AGAIN:
   DEC  R17
   BRNE AGAIN
   DEC  R18
   BRNE DELAY
   RET	
;**********************************