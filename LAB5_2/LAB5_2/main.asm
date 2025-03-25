;**********************************
;******** MSYS, LAB5,DEL 2 ********
;***** Morten Rode Enghausen ******
;**********************************
;*********** INITIERING ***********
	LDI  R16, HIGH(RAMEND)
	OUT  SPH, R16
	LDI  R16, LOW(RAMEND)
	OUT  SPL, R16

	; Benene PA konfigureres alle til indgange (trykknapperne er forbundet til porten PA)
	LDI R17, 0b00000000
	OUT DDRA, R17

	; Benene PB konfigureres alle til udgange (lysdioderne er forbundet til porten PB).
	LDI R17, 0b11111111
	OUT DDRB, R17

	; Alle lysdioderne slukkes.
	COM R17
	OUT PORTB, R17

	; Det undersøges, om brugeren trykker på en af ”Mega2560 I/O shield”s trykknapper.
	; Hvis en af de 8 trykknapper er aktiveret, kaldes for hver enkelt af dem en subrutine.
	; Følgende skal ske: 
MAIN_LOOP:
	; Hvis trykknap SW7-0 aktiveres: 
	; Talværdien på PORTB inkrementeres.
	SBIS PINA,7
	CALL INKREMENT_PORTB
	; Talværdien på PORTB dekrementeres
	SBIS PINA,6
	CALL DEKREMENT_PORTB
	; Værdien på [LED7,LED6,LED5,LED4] ”bytter plads med” [LED3,LED2,LED1,LED0]. 
	SBIS PINA,5
	CALL SWAP_PORTB
	; Alle lysdioderne skifter tilstand (fra tændt til slukket og omvendt).
	SBIS PINA,4
	CALL COM_PORTB
	; Talværdien på PORTB divideres med 8. 
	SBIS PINA,3
	CALL DIVIDE_BY_8
	; Talværdien på PORTB divideres med 7.
	SBIS PINA,2
	CALL DIVIDE_BY_7
	; LED7 og LED0 slukkes, mens de andre LEDs skal være uændrede.
	SBIS PINA,1
	CALL AND_PORTB
	; LED7 og LED0 tændes, mens de andre LEDs skal være uændrede.
	SBIS PINA,0
	CALL OR_PORTB
	; Der holdes en tidsforsinkelse på ”et par sekunder”
	CALL DELAY_2S
	; Der hoppes til punkt 5 (MAIN LOOP)
	RJMP MAIN_LOOP
    
INKREMENT_PORTB:
	IN R18, PORTB
	INC R18
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

DEKREMENT_PORTB:
	IN R18, PORTB
	DEC R18
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

SWAP_PORTB:
	IN R18, PORTB
	SWAP R18
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

COM_PORTB:
	IN R18, PORTB
	COM R18
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

DIVIDE_BY_8:
	IN R18, PORTB
	LSR R18
	LSR R18
	LSR R18
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

DIVIDE_BY_7:
    IN R18, PORTB
    LDI R19, 7
    CLR R20
    CPI R18, 0       ; Hvis input er 0, skal vi ikke dividere
    BREQ DIVIDE_DONE ; Spring til afslutning, hvis R18 allerede er 0
DIVIDE_LOOP:
    INC R20
    SUB R18, R19
    BRCC DIVIDE_LOOP
    DEC R20          ; Korrektion: sidste iteration trak for meget
    ADD R18, R19     ; Tilføj 7 igen for at få den korrekte rest
DIVIDE_DONE:
    OUT PORTB, R20   ; Gem kvotienten i PORTB
	CALL WAIT_RELEASE
    RET

AND_PORTB:
	IN R18, PORTB
	ANDI R18, 0b01111110
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

OR_PORTB:
	IN R18, PORTB
	ORI R18, 0b10000001
	OUT PORTB, R18
	CALL WAIT_RELEASE
	RET

DELAY_2S:
    LDI R16, 250
DELAY_OUTER_LOOP:
    LDI R17, 255
DELAY_INNER_LOOP:
    DEC R17
    BRNE DELAY_INNER_LOOP
    DEC R16
    BRNE DELAY_OUTER_LOOP
    RET

WAIT_RELEASE:
	IN R18, PINA   ; Læs hele PINA (alle knapper)
	CPI R18, 0xFF  ; Er alle bits sat til 1? (dvs. ingen knapper trykket)
	BRNE WAIT_RELEASE  ; Hvis ikke (dvs. hvis mindst én knap stadig trykkes), gentag
	RET