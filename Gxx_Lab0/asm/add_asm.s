	AREA text, CODE, READONLY
	export add_asm

add_asm

	vadd.f32 S0,S1,S0
	BX LR
	
	END