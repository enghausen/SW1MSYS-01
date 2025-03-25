;**********************************
;******** MSYS, LAB4,DEL 2 ********
;******** Henning Hargaard ********
;**********************************
;*********** INITIERING ***********
   LDI  R16,HIGH(RAMEND)
   OUT  SPH,R16
   LDI  R16,LOW(RAMEND)
   OUT  SPL,R16

;---> Skriv kode her, der konfigurerer PB, ben 0 (LED0) til udgang
   SBI DDRB,0
;---> Skriv kode her, der konfigurerer hele PA til indgange
   LDI R19,0b00000000
   OUT DDRA,R19

;*********** PROGRAM LOOP *********
 HERE:

;---> Skriv kode her, der aftaster de 8 trykknapper og
;     styrer duty cycle på LED0 i henhold til
;     hvilken knap, der trykkes på
   SBIS PINA,7
   LDI R20, 255
   SBIS PINA,6
   LDI R20, 128
   SBIS PINA,5
   LDI R20, 64
   SBIS PINA,4
   LDI R20, 32
   SBIS PINA,3
   LDI R20, 16
   SBIS PINA,2
   LDI R20, 8
   SBIS PINA,1
   LDI R20, 4
   SBIS PINA,0
   LDI R20, 2
   SBI PORTB,0
   MOV R18,R20
   CALL DELAY
   CBI PORTB,0
   LDI R18,128
   CALL DELAY

   JMP  HERE       ;Gentag loop

;********* DELAY (R18*4us) ********
DELAY:
   LDI  R17,255
AGAIN:
   DEC  R17
   BRNE AGAIN
   DEC  R18
   BRNE DELAY
   RET	
;**********************************