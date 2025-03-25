;********** MSYS, LAB1 **********
;********************************
;********** INITIERING **********
    LDI   R16,HIGH(RAMEND)   ; Initialize Stack Pointer (h�j byte)
    OUT   SPH,R16
    LDI   R16,LOW(RAMEND)    ; Initialize Stack Pointer (lav byte)
    OUT   SPL,R16           
    SER   R16              ; S�tter alle bits i R16 til 1
    OUT   DDRB,R16         ; Konfigurerer PORTB som output (alle 8 pins)

    LDI   R16,0x01         ; Start med f�rste LED t�ndt (0x01 = 00000001)
    LDI   R20,14          ; S�t initial delay-faktor (250 svarer til ca. 2 s delay pr. LED)
                             ; (Eksakt tid afh�nger af antallet af cyklusser i delay-loopen)

;********** PROGRAM-LOOP ********
LOOP:
    CALL  DISP_AND_DELAY   ; Vis LED-m�nsteret med delay (brug R20 til delay)
    LSL   R16              ; Venstreforskyd R16 � flyt den t�ndte bit til n�ste position
    BREQ  CYCLE_COMPLETE   ; Hvis R16 bliver 0 (vi har flyttet forbi 0x80), s� er cyklussen slut
    RJMP  LOOP             ; Ellers forts�t med n�ste LED

; N�r vi er kommet ud af cyklussen (alle 8 LED�er vist)
CYCLE_COMPLETE:
    ; Her har vi k�rt �n hel cyklus med fast hastighed.
    ; Nu reducerer vi delay-faktoren, s� n�ste cyklus k�rer hurtigere.
    SUBI  R20, 1          ; Reducer delay-faktoren (dette g�r hele cyklussen hurtigere)
    CPI   R20, 1         ; Hvis R20 er under 1 (alts� for kort delay)�
    BRLO  RESET_DELAY     ; �nulstil delay-faktoren til udgangsv�rdien
    LDI   R16,0x01        ; Genstart LED-m�nsteret (f�rste LED)
    RJMP  LOOP

RESET_DELAY:
    LDI   R20,14         ; Nulstil delay-faktoren til den oprindelige v�rdi (ca. 2 s delay pr. LED)
    LDI   R16,0x01        ; Genstart LED-m�nsteret
    RJMP  LOOP

;********** DISPLAY LED-M�NSTER & DELAY ***********
DISP_AND_DELAY:
    MOV   R17, R16        ; Kopier LED-m�nsteret (R16) til R17
    OUT   PORTB,R17       ; Send R17 ud p� PORTB � LED�erne opdateres
    CLR   R17             ; Nulstil R17 (bruges som t�ller i delay-loopen)
    CLR   R18             ; Nulstil R18 (anden t�ller)
    MOV   R19, R20        ; Brug den dynamiske delay-faktor (R20) til den ydre loop
AGAIN:
    DEC   R17
    BRNE  AGAIN           ; Indre loop: k�rer 256 gange (n�r R17 starter fra 0, underflower den til 0xFF)
    DEC   R18
    BRNE  AGAIN           ; Mellemliggende loop
    DEC   R19
    BRNE  AGAIN           ; Ydre loop: antallet bestemmes af R20
    RET
;********************************
