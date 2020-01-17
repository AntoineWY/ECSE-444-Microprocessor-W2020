		AREA test, CODE, READONLY
		export stdev_s  
			
			
		;r0 is address of the array to calculate, r1 is length and r2 is the answer address	
stdev_s  
		push{r4-r12}
		vsub.f32 s0,s0,s0
		vsub.f32 s1,s1,s1
		vsub.f32 s2,s2,s2
		vmov.f32 s2, r1
		VCVT.F32.U32 S2,s2	
		
		mov r4,r0
		mov r5,r1
		
sum_loop ;might be wrong for array of length 0, but can easily fixed
		vldr.f32 s0,[r4]
		add r4, r4,#4
		
		vadd.f32 s1, s1, s0

		sub r5, r5, #1
		cmp r5, #0
		bgt sum_loop

;---------------------------------
		vdiv.f32 s0, s1,s2 ; this step calculate the mean
		mov r5, r1 ; restore counter
		mov r4, r0 ; restore array head
		
stdev_loop
		vldr.f32 s1,[r4]
		add r4, r4, #4
		
		vsub.f32 s1, s1, s0 ; difference = value - mean
		vmul.f32 s1, s1, s1 ; difference square
		vadd.f32 s2, s2, s1; variance += difference
		
		sub r5, r5, #1
		cmp r5, #0
		bgt stdev_loop
		
;----------------------------------

		sub r1, r1, #1 ; n-1
		vmov.f32 s1, r1 ; intermediate step loading the integer into float reg
		VCVT.F32.U32 S1, S1
		
		vdiv.f32 s2, s2, s1 ; variance/(n-1)
		vsqrt.f32 s0, s2; square root(variance/(n-1))
		vstr.f32 s0, [r2]

DONE
		pop{r4-r12}
		bx lr
		end
		