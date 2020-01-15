AREA text, CODE, READONLY
	EXPORT ma_Filter

ma_Filter
    push{R4, R12}
    mov R4, #0 // loop counter 
    mov R5, #0 // filer average array index

    mov s0, #0 // a buffer for sum to calculate average


Main_loop
    asr R7, R3, #2 // divide depth by 2, integer division!
    sub R8, R5, R7
    bl is_depth_odd
    // lower bound in R8, higher in R10


    mov R9, R8  // R9 will be counter of add_loop, starting at the lower bound
    bl Add_loop

    
    vdiv.f32 s0, s0, R3 // divide sum with Depth
    vStr.f32 s0, [r1, R5, lsl#2]
    vsub.f32 s0, s0, s0 // clear the current avg for a new calculation


    add r5,r5,#1
    CMP R5, R2
    BLT Main_loop

    pop{R4, r12}
    BX lr



is_depth_odd //based on whether the depth is odd, adjust the higher bound
    add R10, R7, R5
    mov R9, #0x00000001
    and R9, R9, R3 //is R3, the depth odd or even?
    cmp R9, #0
    subeq R10, #1 // now we have the upper bound 
    bx lr

//--------------------------------------------------------------------------------------
Add_loop

    cmp r9,#0
    bLT after_add//is the index is smaller than 0, jump the add(equals to add zero)

    cmp r9, r2 // compare with length, the highest index of the array
    bGE after_add

    vldr.f32 s0, [R0, R9, lsl #2] 
    vadd.f32 s0, s0, s1
   
after_add
    add r9, r9, #1
    cmp r9, r10
    bLE Add_loop
    bx LR





    