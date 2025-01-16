;sample program to add 2 no.s

	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0x10001000
	DCDC Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	MOV R0, #2
	MOV R1, #7
	ADD R2, R0, R1	;adding 2 and 7
	END
