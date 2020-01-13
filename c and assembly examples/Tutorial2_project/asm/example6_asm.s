	AREA text, CODE, READONLY
	EXPORT example6_asm
example6_asm
	
	PUSH {R4-R12}
	MOV R4, #0
	
loop
	ADD R5, R0, R4, LSL #2
	VLDR.f32 S0, [R5]
	ADD R5, R1, R4, LSL #2
	VSTR.f32 S0, [R5]
	ADDS R4, R4, #1
	CMP R4, R2
	BLT loop
	
	POP {R4-R12}
	BX LR
	END