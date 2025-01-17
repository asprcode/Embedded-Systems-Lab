; Code to transfer 32 bit no from one loc to another

	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD REset_Handler
	ALIGN
	
	AREA mysrc DATA, READONLY
SRC DCD 0X12345678
	
	AREA mydest DATA, READWRITE
DST DCD 0
	
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT REset_Handler
Reset_Handler
	LDR R0, =SRC	; location of src in R0
	LDR R1, [R0]	; value of R0 in R1
	LDR R2, =DST	; location of DST in R2
	STR R1, [R2]	; value in R1 (og value of SRC) stored in location in R2(DST)
	END