/**************************8
 * test.c
 *
 * test for myprintf.c 
 * 
 * Author: Simon Lee (sijlee)
 * Date Created: 01/28/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 01/28/2016
 * Assignment: Lab 2
 * Part of: C335
 */

#include <stdio.h>

//declare & initialize myprintf function from other c file
extern void myprintf(const char *, ...);
//running actual test
//should print out the contents
int main() {
  myprintf("Nothing much\n"); 
  myprintf("The letter %c\n", 'A'); 
  myprintf("A string: %s\n", "Splash!"); 
  myprintf("The number %d\n", 11); 
  myprintf("The number %x in hexadecimal\n", 11); 
  myprintf("%d is a negative number\n", -5); 
  myprintf("The number %d\n", 'A'); 
  myprintf("The number %x in hexadecimal\n", 'A');
  return 0;
}
