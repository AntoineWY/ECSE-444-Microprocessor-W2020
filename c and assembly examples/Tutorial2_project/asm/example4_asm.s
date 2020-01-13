	AREA text, CODE, READONLY
	export example4_asm
example4_asm
	
	VMUL.f32 S0, S1, S0
	BX LR
	
	END