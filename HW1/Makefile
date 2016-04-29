######################################
# Makefile
# Combines test.c and t1.s to generate HW1.elf and output.txt
# Author: Simon Lee
# Date Created: Feb 07, 2016
# Date Last Modified: Feb 08, 2016
# Assignment HW1
# Part of: C335 assignment
#

#making .elf file in the name of directory (HW1.elf)
ELF=$(notdir $(CURDIR)).elf
#macro for compiler
CC=arm-none-eabi-gcc
AS=arm-none-eabi-as

CFLAGS = -g -O1 -mcpu=cortex-m0 -mthumb 

all : test.o t1.o HW1.elf
#test.o from test.c
test.o : 
	$(CC) $(CFLAGS) -c test.c -c -o test.o
#t1.o from 1.s
t1.o : 
	$(AS) -g -mcpu=cortex-m0 -mthumb t1.s -o t1.o 
#generating main.s
main.s : test.c
	arm-none-eabi-gcc -c -S -g -Wa,-a,-ad -O1 -mcpu=cortex-m0 -mthumb test.c -o main.s
#from object files, we generate HW1.elf (ARM executable)
HW1.elf :
	$(CC) $(CFLAGS) --specs=rdimon.specs -lc -lrdimon t1.o test.o -o HW1.elf  

#given test
#I added > output.txt to output in txt format
test : HW1.elf
	qemu-system-arm  -cpu cortex-m3 -M versatilepb -nographic \
                   -monitor null -serial null \
                   -semihosting -kernel HW1.elf > output.txt
#clean for testing purpose
clean: 
	rm  HW1.elf
	rm t1.o
	rm test.o
