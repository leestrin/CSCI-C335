	.text
	.syntax unified
	.thumb
	.global	gcd	
	.type gcd, %function
gcd:
	push {r4-r7}

        /*
        Simon Lee
        gcd.s
        HW5
	Won yong Ha (woha) helped me solving gcd.s
        */
		
	//r2 = d = 0
	movs r2, #0
whilea1:
	movs r4, #1
	//(a & 1)
	ands r4, r0, r4
	movs r3, #0
	//not 
	cmp r4, r3
	beq whileb1
	bne elif1
whileb1:
	movs r4, #1
	//(b & 1)
	ands r4, r1, r4
	movs r3, #0
	//not
	cmp r4, r3
	beq anotb
	bne elif1
anotb:
	//we use r4 for shift
	movs r4, #1
	//a >>= 1;
	asrs r0, r0, r4
	//b >>= 1;
	asrs r1, r1, r4
	//d += 1
	adds r2, r2, r4
	b whilea1
elif1:
	//(a != b)
	cmp r0, r1
	beq final
	bne elif2
elif2:
	//(a & 1)
	ands r4, r0, r4
	movs r3, #0
	cmp r3, r4
	beq elif2_true
	bne elif3

elif2_true:
	movs r4, #1
	asrs r0, r0, r4
	b elif1

elif3:
	movs r4, #1
	ands r4, r1, r4
	movs r3, #0
	cmp r4, r3
	beq elif3_true
	bne elif4

elif3_true:
	movs r4, #1
	asrs r1, r1, r4
	b elif1

elif4:
	cmp r0, r1
	bge elif4_true
	bls else

elif4_true:
	movs r4, #1
	subs r0, r0, r1
	asrs r0, r0, r4
	b elif1
else:
	movs r4, #1
	subs r1, r1, r0
	asrs r1, r1, r4
	b elif1
final:
	lsls r0, r0, r2
	pop {r4-r7}
	bx	lr
	
