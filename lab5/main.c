/* main.c --- 
 * 
 * Filename: main.c
 * Description: main for Uart driver to make STM32 work with WC function
 * Author: Simon Lee (sijlee), Romaan Ahmed (roahmed)
 * Maintainer: Simon Lee (sijlee)
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: Simon Lee (sijlee)
 *     Update #: 2
 * Keywords: lab5
 * Compatibility: STM32
 * 
 */

/* Commentary: 
 * 
 * imports f3d_uart driver for serial connection
 * prints the result of mywc through serial
 */

/* Change log:
 * 
 * 
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  /*
  while (1) {
    putchar(getchar());
  }
  */
  while (1){
    //initiate counter variables by 1
    //because we will be counting from 0
    int lineCount = 1;
    int wordCount = 1;
    int charCount = 1;
    //current char
    int c;
    //while there is some char
    while((c = getchar()) != 0x1b) {
      //there will be a char, so add 1 
      charCount = charCount + 1;
      if (c == '\n') {
	//when we see a new line while going through text,
	//add 1 to line counter and word counter
	lineCount = lineCount + 1;
	wordCount= wordCount + 1;
      }
      //misc. whitespace handling
      if (c == ' ' || c == '\f' || c == '\t'|| c == '\r' || c == '\v') {
	//we add 1 to word counter
	wordCount = wordCount + 1;
      }
    }

    //after while loop, we print out the result
    printf("%d %d %d\n", lineCount, wordCount, charCount);
    return 0;
  } 
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
