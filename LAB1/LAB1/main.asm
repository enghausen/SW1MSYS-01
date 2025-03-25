;********** MSYS, LAB1 **********
;********************************
;********** INITIERING **********
    LDI   R16,HIGH(RAMEND)   ; Initialize Stack Pointer (høj byte)
    OUT   SPH,R16
    LDI   R16,LOW(RAMEND)    ; Initialize Stack Pointer (lav byte)
    OUT   SPL,R16           
    SER   R16              ; Sætter alle bits i R16 til 1
    OUT   DDRB,R16         ; Konfigurerer PORTB som output (alle 8 pins)

    LDI   R16,0x01         ; Start med første LED tændt (0x01 = 00000001)
    LDI   R20,14          ; Sæt initial delay-faktor (250 svarer til ca. 2 s delay pr. LED)
                             ; (Eksakt tid afhænger af antallet af cyklusser i delay-loopen)

;********** PROGRAM-LOOP ********
LOOP:
    CALL  DISP_AND_DELAY   ; Vis LED-mønsteret med delay (brug R20 til delay)
    LSL   R16              ; Venstreforskyd R16 – flyt den tændte bit til næste position
    BREQ  CYCLE_COMPLETE   ; Hvis R16 bliver 0 (vi har flyttet forbi 0x80), så er cyklussen slut
    RJMP  LOOP             ; Ellers fortsæt med næste LED

; Når vi er kommet ud af cyklussen (alle 8 LED’er vist)
CYCLE_COMPLETE:
    ; Her har vi kørt én hel cyklus med fast hastighed.
    ; Nu reducerer vi delay-faktoren, så næste cyklus kører hurtigere.
    SUBI  R20, 1          ; Reducer delay-faktoren (dette gør hele cyklussen hurtigere)
    CPI   R20, 1         ; Hvis R20 er under 1 (altså for kort delay)…
    BRLO  RESET_DELAY     ; …nulstil delay-faktoren til udgangsværdien
    LDI   R16,0x01        ; Genstart LED-mønsteret (første LED)
    RJMP  LOOP

RESET_DELAY:
    LDI   R20,14         ; Nulstil delay-faktoren til den oprindelige værdi (ca. 2 s delay pr. LED)
    LDI   R16,0x01        ; Genstart LED-mønsteret
    RJMP  LOOP

;********** DISPLAY LED-MØNSTER & DELAY ***********
DISP_AND_DELAY:
    MOV   R17, R16        ; Kopier LED-mønsteret (R16) til R17
    OUT   PORTB,R17       ; Send R17 ud på PORTB – LED’erne opdateres
    CLR   R17             ; Nulstil R17 (bruges som tæller i delay-loopen)
    CLR   R18             ; Nulstil R18 (anden tæller)
    MOV   R19, R20        ; Brug den dynamiske delay-faktor (R20) til den ydre loop
AGAIN:
    DEC   R17
    BRNE  AGAIN           ; Indre loop: kører 256 gange (når R17 starter fra 0, underflower den til 0xFF)
    DEC   R18
    BRNE  AGAIN           ; Mellemliggende loop
    DEC   R19
    BRNE  AGAIN           ; Ydre loop: antallet bestemmes af R20
    RET
;********************************
