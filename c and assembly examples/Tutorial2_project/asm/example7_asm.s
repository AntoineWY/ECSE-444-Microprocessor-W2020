	AREA text, CODE, READONLY
	EXPORT example7_asm
example7_asm
	
	MOV R1, R0
	MOV R2, #0
	
loop
	MOV R0, R2
	ADDS R2, R2, #1
	ASR R0, R1, R0
	CMP R0, #1
	BNE loop
	
	SUBS R0, R2, #1
	BX LR
	END