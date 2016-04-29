/**********************************************************
 * mywc.c
 *
 * mywc reads texts from std in
 * and prints out number of words, char, and line in input
 *
 * Author: Simon Lee (sijlee)
 * Date Created: 01/28/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 01/28/2016
 * Assignment: Lab 2
 * Part of: C335
 */

#include <stdio.h>

int main() {
  //initiate counter variables by 1
  //because we will be counting from 0
  int lineCount = 1;
  int wordCount = 1;
  int charCount = 1;
  //current char
  int c;
  //while there is some char
  while((c = getchar()) != EOF) {
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
