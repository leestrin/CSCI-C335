	.text
	.syntax unified
	.thumb
	.global	fib
	.type fib, %function
fib:
	push {r4-r7}

        /*
	Simon Lee
        fib.s
        HW5
	*/
	
	
	//r2 = prev2
	//r1 = prev1
	//r3 = val
	movs r2, #1	
	movs r1, #1	
	movs r3, #1
	//compare num if it is equal to 0
	cmp r0, #0
	//go to final and return 0
	beq final
	//compare num if it is equal to 1
	cmp r0, #1
	//go to final and return 1
	beq final		
	//set r4 = i = 0
	movs r4, #0
	//keep decrement num by 2
	subs r0, #2
loop:
	//if i is num,
	cmp r4, r0
	//go to result
	beq return
	//not, val = prev1 + prev2
	adds r3, r1, r2
	//let prev2 = prev1
	movs r2, r1
	//let prev1 = val
	movs r1, r3
	//increment i
	adds r4, #1
	//go bakc to loop
	b loop

return:
	//set val to num then go to final
	movs r0, r3

final:
	pop {r4-r7}
	bx	lr
