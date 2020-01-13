	AREA text, CODE, READONLY
	export example2_asm
example2_asm
	
	VADD.f32 S0, S1, S0
	BX LR
	
	END