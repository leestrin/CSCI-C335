/*********************************
 * myprintf.c
 *
 * Continues from base code.
 * printint, printstring and printhex has been added
 *
 * Author: Simon Lee (sijlee)
 * Date Created: 01/28/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 01/28/2016
 * Assignment: Lab 2
 * Part of: C335
 */

#include <stdarg.h>
#include <stdio.h>


void printint(int i) {
  //when negative number,
  if (i < 0) {
    putchar(45);
    //we represent num by taking mul of i by -1
    i = -1 * i;
    //if i is 0, just putchar 0
    if (i == 0) {
      putchar(0);
    } else {
      //we count digit by taking modulo by 10
      int j = 0;
      j = i % 10 + 48;
      //print following ascii
      printint(i / 10);
      putchar(j);
    }
    //same procedure as handling neg num
    //just no multiplying by -1 for pos num
  } else {
    if (i == 0) {
      putchar(0);
    } else {
      int j = 0;
      j = i % 10 + 48;
      printint (i / 10);
      putchar(j);
    }
  }
}

void printstring(char *c) {
  int i = 0;
  while (c[i] != 0){
    putchar(c[i++]);
  }
}

void printhex(int h) {
  if (h ==0){
    putchar(0);
  } else {
    //we move digit by taking modulo by 16
    int pos = h % 16;
    printhex(h/16);
    //pos indicates the digit of hex num
    if (pos == 10) {
      putchar(97);
    } else if(pos == 11) {
      putchar(98);
    } else if(pos == 12) {
      putchar(99);
    } else if(pos == 13) {
      putchar(100);
    } else if(pos == 14) {
      putchar(101);
    } else if(pos == 15) {
      putchar(102);
    } else {
      putchar(pos + 48);
    }
  }
}

// given code
void myprintf(const char *fmt, ...) {
    const char *p;
    va_list argp;
    int i;
    char *s;

    va_start(argp, fmt);

    for (p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
	  putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'c':
            i = va_arg(argp, int);
            putchar(i);
            break;

        case 'd':
            i = va_arg(argp, int);
            printint(i);
            break;

        case 's':
            s = va_arg(argp, char *);
            printstring(s);
            break;

        case 'x':
            i = va_arg(argp, int);
            printhex(i);
            break;

        case '%':
            putchar('%');
            break;
        }
    }
    va_end(argp);
}
