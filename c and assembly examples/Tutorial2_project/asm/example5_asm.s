	AREA text, CODE, READONLY
	EXPORT example5_asm
example5_asm
	
	PUSH {R4-R12}
	
	MOV R4, #0
loop
	LDR R5, [R0, R4, LSL #2]
	STR R5, [R1, R4, LSL #2]
	ADDS R4, R4, #1
	CMP R4, R2
	BLT loop
	
	POP {R4-R12}
	BX LR
	END