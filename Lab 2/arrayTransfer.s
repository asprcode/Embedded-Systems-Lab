	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors
	DCD 0X10001000
	DCD Reset_Handler
	ALIGN
	
	AREA mysrc, CODE, READONLY
SRC DCD 1,2,3,4,5,6,7,8,9,10		; an array of integers in memory

	AREA mydst, DATA, READONLY
DST DCD 0

	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler
Reset_Handler
	LDR R0, =SRC
	LDR R1, =DST
	MOV R2, #10
L1	LDR R3, [R0], #4 ; L1 is the label for the loop 
	STR R3, [R1], #4
	SUBS R2, #1	; decrements R2 by 1 (loop counter). SUBS, the 2nd S is for status register (CPSR)
	BNE L1		; branch not equal (compares to the last instr above L1, so R2)
STOP B STOP
	END
