;**********************************
;******** MSYS, LAB5,DEL 1 ********
;***** Morten Rode Enghausen ******
;**********************************
;*********** INITIERING ***********
	LDI  R16,HIGH(RAMEND)
	OUT  SPH,R16
	LDI  R16,LOW(RAMEND)
	OUT  SPL,R16

	LDI R16, 0b00000000
	LDI R17, 0b11001010
	LDI R18, 0b10011010
	LDI R19, 0b00111011

	LDI R20, 0b00000000
	LDI R21, 0b10010100
	LDI R22, 0b00110101
	LDI R23, 0b01110111

	ADD R16, R20
	ADC R17, R21
	ADC R18, R22
	ADC R19, R23


