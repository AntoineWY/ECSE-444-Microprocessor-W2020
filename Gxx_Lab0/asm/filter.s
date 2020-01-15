	AREA text, CODE, READONLY
	export ma_Filter_asm

ma_Filter_asm
    push{R4-R12}
    mov R4, #0 ; loop counter 
    mov R5, #0 ; filer average array index

    vsub.f32 s0, s0 ; a buffer for sum to calculate average


Main_loop
    asr R7, R3, #2 ; divide depth by 2, integer division!
    sub R8, R5, R7
    bl is_depth_odd
    ; lower bound in R8, higher in R10


    mov R9, R8  ; R9 will be counter of add_loop, starting at the lower bound
    bl Add_loop

    vmov.f32 s3, r3
    vdiv.f32 s0, s0, s3 ; divide sum with Depth
	push{r10}
	mov r10, r1
	add r10,r10, r5, lsl#2
    vstr.f32 s0, [r10]
	pop{r10}
    vsub.f32 s0, s0, s0 ; clear the current avg for a new calculation


    add r5,r5,#1
    CMP R5, R2
    BLT Main_loop

    pop{R4-r12}
    bx lr
	


is_depth_odd ;based on whether the depth is odd, adjust the higher bound
    add R10, R7, R5
    mov R9, #0x00000001
    and R9, R9, R3 ;is R3, the depth odd or even?
    cmp R9, #0
    subeq R10, #1 ; now we have the upper bound 
    bx lr

;--------------------------------------------------------------------------------------
Add_loop

    cmp r9,#0
    BLT after_add;is the index is smaller than 0, jump the add(equals to add zero)

    cmp r9, r2 ; compare with length, the highest index of the array
    BGE after_add
	
	push{r10}
	mov r10, r0
	add r10,r10, r9, lsl#2
    vldr.f32 s0, [r10]
	pop{r10}
    vadd.f32 s0, s0, s1
   
after_add
    add r9, r9, #1
    cmp r9, r10
    BLE Add_loop
    bx LR

END

    