	.text
	.syntax unified
	.thumb
	.global	abs	
	.type abs, %function
abs:
	push {r4-r7}

	/*
	Simon Lee
	abs.s
	HW5
	*/
	
	//let r1 0 to calculate neg. num
	movs r1, #0
	//0 - num
	subs r1, r0
	//if num > 0 go to final
	blo final
	//otherwise let num to be r1
	movs r0, r1
final:
	pop {r4-r7}	
	bx	lr
