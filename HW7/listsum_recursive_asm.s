	.text
	.syntax unified
	.thumb
	.global	listsum_recursive_asm	
	.type listsum_recursive_asm, %function
listsum_recursive_asm:
/*
	Simon Lee (sijlee)
	I worked with Brandon Burzon, Wonyong Ha
	C335 HW7
*/
	
/*
	Your implementation goes here. 
*/
	push {r4, lr}
	//setting r1 = p->item
	ldr r1, [r0]   
	//load r5 to be pointer for p->next
	ldr r5	, [r0, 4]
	//compare if r1 is null
	cmp r1, #0
        //if r1 is null, go to final
	beq Final            
	sub sp, 8
	movs r4, r1
	str r1, [sp, 4]
	movs r0, r5
	//recursion, return 0
	bl listsum_recursive_asm 
	ldr r1, [sp, 4]
	adds r0, r1
	add sp, 8
	bl Final
Final:
	pop {r4, pc}
	bx	lr
