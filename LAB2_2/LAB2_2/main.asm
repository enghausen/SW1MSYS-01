;********** MSYS, LAB2_2 **********
;******** Henning Hargaard ********
;**********************************

;*********** INITIERING ***********
   LDI  R16,HIGH(RAMEND) ;Initialize Stack Pointer
   OUT  SPH,R16
   LDI  R16,LOW(RAMEND)
   OUT  SPL,R16 
   SER  R16              ;PB pins = outputs
   OUT  DDRB,R16

;*********** PROGRAM LOOP *********
LOOP:
   INC  R16
   OUT  PORTB,R16
   CALL DELAY    ;Tidsforsinkelse
   JMP  LOOP

;*********** DELAY ****************
DELAY:
   CLR  R17
   LDI  R18,255  ;Stort tal = lang forsinkelse
AGAIN:
   DEC  R17
   BRNE AGAIN
   DEC  R18
   BRNE AGAIN
   RET	
;**********************************