; ARM assembly to copy 32 bit code to data memory

	AREA RESET, DATA, READONLY
	EXPORT __Vectors
_Vectors
	DCD 0X10001000	
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR RO, =SRC	; the location of SRC is stored in GPR R0
	LDR R1, [R0]	; the value at loc in RO (val at SRC) stored in GPR R1
	LDR R2, =DST	
	STR R1, [R2]	; the value in R1 is stored at location in R2 (DST)
STOP B STOP
SRC DCD 8

	AREA mydata DATA, READWRITE
DST DCD 0
	END