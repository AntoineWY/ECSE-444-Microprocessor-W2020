		AREA test, CODE, READONLY
	
		export asm_arrayProduct          
			
asm_arrayProduct  
		push {r4-r12}
		sub r4, r4, r4 ;set r4 =0 ,r4 is the counter and the index
		vsub.f32 s0,s0,s0 ;s0 will hold the float product
		
		
		mov r5, r0 ;r5 hold the address of the first array
		mov r6, r1 ; r6 address of the second array
		mov r7, r3 ; r7 address of the result array
product_loop
		
	
		vldr.f32 s1,[r5]
		add r5, r5, #4
		
		vldr.f32 s2,[r6]
		add r6, r6, #4
		
		vmul.f32 s0, s1, s2
		vstr.f32 s0, [r7]
		add r7, r7, #4
		
		subs r2, r2, #1
		bgt product_loop
		
Done
		pop{r4-r12}
		bx lr
		
		
		END