;**********************************
;********   MSYS, LAB3_1   ********
;******** Henning Hargaard ********
;**********************************

;*********** INITIERING ***********
;***** Klargoer SP og PORTB *******
  LDI  R16,HIGH(RAMEND) ;Klargoer Stack Pointer
  OUT  SPH,R16
  LDI  R16,LOW(RAMEND)
  OUT  SPL,R16 
  SER  R16              ;PORT B er udgang
  OUT  DDRB,R16
  CLR  R16              ;Sluk alle lysdioder
  OUT  PORTB,R16
 
;*********** PROGRAM LOOP *********
  LDI  R20,239   ;c      Spil C dur skalaen
  CALL TONE 
  LDI  R20,213   ;D
  CALL TONE
  LDI  R20,190   ;E
  CALL TONE
  LDI  R20,179   ;F
  CALL TONE
  LDI  R20,160   ;G
  CALL TONE 
  LDI  R20,142   ;A 
  CALL TONE 
  LDI  R20,127   ;H
  CALL TONE 
  LDI  R20,120   ;C
  CALL TONE 
HERE:
  JMP  HERE      ;Bliv her "altid"
  
;**********************************
;*  DELAY (R18*4us)               *
;*  Laver en tidsforsinkelse paa  *
;* "Det der er i R18" gange 4 us  *
;**********************************
DELAY:
  LDI  R17,20   ;<--- OPGAVE (del 1): Find xxx og skriv det her
AGAIN:
  DEC  R17
  BRNE AGAIN
  DEC  R18
  BRNE DELAY
  RET
   	
;**********************************
;******** SPILLER EN TONE  ********
;******** 250 HALVPERIODER ********
;******** T/2 = (R20)*4 us ********
;********************************** 
  LDI  R21,250
TONE:             ;<--- HER MANGLER KODE (del 2)
  COM  R22
  OUT  PORTB, R22
  MOV  R18, R20
  CALL DELAY      ;Delay = (R18) * 4 mikrosekunder
  DEC  R21
  BRNE TONE
                  ;<--- HER MANGLER KODE (del 2)
  RET             ;Retur til program loop