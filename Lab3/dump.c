/*********************************
 * dump.c
 *
 * Divides by memory, shows addresses and value by types
 *
 * Author: Simon Lee (sijlee) / Brandon Burzon (brburzon)
 * Date Created: 01/29/2016
 * Last Modified by: Brandon Burzon (brburzon)
 * Date Last Modified: 02/04/2016
 * Assignment: Lab 3
 * Part of: C335
 */

#include <stdio.h>

typedef enum { FALSE = 0, TRUE } bool;

/**
 * Returns true if the given character is visible, otherwise returns false.
 */
bool isCharVisible(char c) {
  if(c >= 32 && c < 127) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
 * Returns true if the given size is big enough to hold a double, otherwise returns false.
 */
bool hasDouble(int size) {
  return size % sizeof(double) == 0;
}

/**
 * Returns true if the size given is big enough to hold an int or a float, otherwise returns false.
 */
bool hasIntAndFloat(int size) {
  return size % sizeof(float) == 0;
}

/**
 * Return true if the given size is big enough to hold a short, otherwise returns false.
 */
bool hasShort(int size) {
  return size % sizeof(short) == 0;
}

/**
 * Dumps memory one bit at a time and prints it to the screen.
 */
void dump_memory(void *p, int len) {
  void *memAddress;
  unsigned char mChar;
  unsigned short mShort;
  unsigned int mInt;
  float mFloat;
  double mDouble;
  int i;

  printf("%s\t\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n", "address", "char", "hexCh", "short", "integer", "float", "doubleFloat");
  for (i = 0; i < len; i++) {
    memAddress = p + i;
    mChar = *(unsigned char *)(p + i);
    mShort = *(unsigned short *)(p + i);
    mInt = *(unsigned int *)(p + i);
    mFloat = *(float *)(p + i);
    mDouble = *(double *)(p + i);

    if(isCharVisible(mChar))
      printf("%8p:\t%c\t0x%02x\t", memAddress, mChar, mChar);
    else
      printf("%8p:\t?\t0x%02x\t", memAddress, mChar);
    if(hasShort(i))
      printf("%+5hu\t", mShort);
    if(hasIntAndFloat(i))
      printf("%+10d\t%+e\t", mInt, mFloat);
    if(hasDouble(i))
      printf("%+e", mDouble);
    printf("\n");
  }
}
