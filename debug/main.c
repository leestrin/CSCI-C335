/*********************************
 * main.c
 *
 * main.c for debug
 *
 * Author: Simon Lee (sijlee), Ben Borders (btborder)
 * Date Created: 02/19/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 02/25/2016
 * Assignment: Lab 6
 * Part of: C335
 */
/* main.c 
   debug this function using gdb*/


/*
  The expected performace of the program is as follows:
  We want to print out the actual bits of numbers! What a great
  way to understand how number representation works

 */

//The libraries to include
#include <f3d_uart.h>
#include <stdio.h> 
#include <stdint.h>
//The arrays that store the bits

int gitBitsChar(unsigned char c, char answer[]){
  int i=7;
  while(i>-1){
    if(c&1) answer[i] = '1';
    else answer[i] = '0';
    c=c>>1;
    i--;
  }
  //8-bit
  answer[8]=0;
  return 0;
}

int gitBitsShort(unsigned short s, char answer[]){
  //starts from 0 to  15
  int i = 15;
  while(i>=0){
    if(s&1) answer[i] = '1';
    else answer[i] = '0';
    s=s>>1;
    //we want to start from the end of array
    i--;
  }
  answer[16]=0;
  return 0;
}

int gitBitsInt(int yikes, char answer[]){
  //32 bits start from 0 to 31
  int i = 31;
  while(i>=0){
    if(yikes&1) answer[i] = '1';
    else answer[i] = '0';
    //we decrement since we want the reverse of array
    yikes=yikes>>1;
    i--;
  }
  answer[32]=0;
  return 0;
}

//runs some test on our program
int main(){
  f3d_uart_init();
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  char ans1[33];
  char ans2[33];
  char ans3[33];
  char ans4[33];
  while (1){
    gitBitsShort((unsigned short) 3200, ans1);
    gitBitsChar((unsigned char) 'a', ans2);
    gitBitsInt(-94, ans3);
    gitBitsInt((unsigned int) 234, ans4);
    printf("unsigned short 3200= %s\n", ans1);
    printf("unsigned a = %s\n", ans2);
    printf("-94 = %s\n", ans3);
    printf("unsigned 234 = %s\n", ans4);
  }
 
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
