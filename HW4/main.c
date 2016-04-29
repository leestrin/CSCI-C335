/* main.c --- 
 * 
 * Filename: main.c
 * Description: Homework 4 [Instruction Emulation]
 * Author: Bryce Himebaugh
 * Created: Wed Oct  7 14:14:25 2015
 * Last-Updated: March 22, 2016
 *           By: Simon Lee (sijlee)
 * 
 */

/* Copyright (c) 2015 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stdio.h> 
#include <stddef.h> 
#include <stdint.h> 
#include "testvector.h"
#include "machine.h"
#include "flags.h"

uint32_t reg[16];
uint32_t psr;

int main(int argc, char *argv[]) {
  // Argument to test_instructions can be ALL to run all of tests or a specific
  // instruction can be tested by passing the name. 
  // ADCS, ADDS, SUBS, ANDS, BICS, LSLS, ASRS
  // To run the instruction tests for all of the instructions, pass ALL

  void adcs(int rn, int rm);
  void adds(int rn, int rm);

  char *input;
  uint32_t reg1,reg2,reg3,reg4;
  uint32_t pow;
  int i;
  
  input = argv[1];
  
  reg1 = 0;
  for (i = 9; i >1; i--) {
    if (i == 9) {
      pow = 1;  
    } else {
      pow = 16 * pow;
    }
    
    if (input[i] <= '9') {
      reg1 = reg1 + (input[i]-'0') * pow; 
    } else {
      reg1 = reg1 + (input[i]-'A'+10) * pow;  
    }
  }
  
  reg2 = 0;
  for (i = 17; i >9; i--) {
    if (i == 17) {
      pow = 1;
    } else {
      pow = 16 * pow;
    }

    if (input[i] <= '9') {
      reg2 = reg2 + (input[i]-'0') * pow;
    } else {
      reg2 = reg2 + (input[i]-'A'+10) * pow;
    }
  }
  
  input = argv[2];
  
  reg3 = 0;
  for (i = 9; i >1; i--) {
    if (i == 9) {
      pow = 1;
    } else {
      pow = 16 * pow;
    }

    if (input[i] <= '9')
      {
	reg3 = reg3 + (input[i]-'0') * pow;
      } else {
      reg3 = reg3 + (input[i]-'A'+10) * pow;
    }
  }
  
  reg4 = 0;
  for (i = 17; i >9; i--) {
    if (i == 17) {
      pow = 1;
    } else {
      pow = 16 * pow;
    }
    
    if (input[i] <= '9') {
      reg4 = reg4 + (input[i]-'0') * pow;
    } else {
      reg4 = reg4 + (input[i]-'A'+10) * pow;
    }
  }
  
  reg[2] = reg2;
  reg[4] = reg4;
  adds(2,4);
  reg[1] = reg1;
  reg[3] = reg3;
  adcs(1,3);
  
  printf("0x%08x%08x\n",reg[1],reg[2]);

  test_instructions(ANDS);
  test_instructions(ADCS);
  test_instructions(ADDS);
  test_instructions(BICS);
  test_instructions(LSLS);
  //  test_instructions(ASRS);
 
  return (0);
}

void ands(int rn, int rm) {
  // Include your code to emulate the "and" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  reg[rn] &= reg[rm];

  // Negative Flag 
  if (reg[rn]&0x80000000) SET_N;
  else CLEAR_N;
 
  // Zero Flag 
  if (!reg[rn]) SET_Z;
  else CLEAR_Z;
}

void adcs(int rn, int rm) {
  // Include your code to emulate the "adc" instruction:
  // adcs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  int origRn = reg[rn];
  if (psr == 0x20000000) {
    reg[rn] += reg[rm] + 1;
  } else {
    reg[rn] += reg[rm];
  } 
  
  int tempRn = reg[rn];
  int tempRm = reg[rm];

  //Zero Flag
  psr = 0;
  if (reg[rn] == 0) {
    if (origRn > reg[rn]) {
      SET_C;
      SET_Z;
    } else {
      SET_Z;
    }
  }

  //Negative Flag
  if (reg[rn] & 0x80000000) {
    SET_N;
  }
  
  //Carry Flag
  if(origRn > reg[rn]) {
    SET_C;
  }
 
  //Overflow Flag
  if (origRn > 0 && tempRm > 0 && tempRn < 0)
    SET_V;
}

void adds(int rn, int rm) {
  // Include your code to emulate the "add" instruction:
  // adds rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  psr = 0;
  int origRn = reg[rn];
  reg[rn] += reg[rm];

  //Negative Flag
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //Zero Flag
  if (reg[rn] == 0) {
    if (origRn > reg[rn]) {
      SET_C;
      SET_Z;
    } else {
      SET_Z;
    }
  }
  
  //Carry Flag
  if(origRn > reg[rn]) {
    SET_C;
  }

  //Overflow Flag
  int tempRn = reg[rn];
  int tempRm = reg[rm];
  if (origRn > 0 && tempRm > 0 && tempRn < 0)
    SET_V;
}

void bics(int rn, int rm) {
  // Include your code to emulate the "bics" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]


  int tempRn = reg[rn];
  int tempRm = reg[rm];
  int tempArRn[32];
  int tempArRm[32];
  int index = 0;
  int result[32];

  for (index; index < 32; index++) {
    tempArRn[index] = 0;
    tempArRm[index] = 0;
  }

  //convert rn into binary array for comparison
  if (tempRn >= 0) {
    int indexRev = 31;
    for (indexRev; indexRev >= 0; indexRev--) {
      tempArRn[indexRev] = tempRn % 2;
      tempRn = tempRn / 2;
    }
  } else {
    int indexRev = 31;
    tempRn = -1 * tempRn;
    tempRn = tempRn - 1;
    for(indexRev; indexRev >= 0; indexRev--) {
      tempArRn[indexRev] = tempRn % 2;
      tempRn = tempRn / 2;
    }
    indexRev = 0;
    for(indexRev; indexRev < 32; indexRev++) {
      if (tempArRn[indexRev] == 0)
	tempArRn[indexRev] = 1;
      else
	tempArRn[indexRev] = 0;
    }
  }

  //convert rm into binary array for comparison
  if (tempRm >= 0) {
    int indexRev = 31;
    for (indexRev; indexRev >= 0; indexRev--) {
      tempArRm[indexRev] = tempRm % 2;
      tempRm = tempRm / 2;
    }
  } else {
    int indexRev = 31;
    tempRm = -1 * tempRm;
    tempRm = tempRm - 1;
    for(indexRev; indexRev >= 0; indexRev--) {
      tempArRm[indexRev] = tempRm % 2;
      tempRm = tempRm / 2;
    }
    indexRev = 0;
    for(indexRev; indexRev < 32; indexRev++) {
      if (tempArRm[indexRev] == 0) {
	tempArRm[indexRev] = 1;
      } else {
	tempArRm[indexRev] = 0;
      }
    }
  }

  int indexRev = 0;
  for (indexRev; indexRev < 32; indexRev++) {
    if((tempArRn[indexRev] == 1) && (tempArRm[indexRev] == 0)) {
      result[indexRev] = 1;
    } else {
      result[indexRev] = 0; 
    }
  }       

  int bit = 0;
  int pow = 1;
  indexRev = 31;
  for (indexRev; indexRev >= 0; indexRev--) {
    bit = bit + pow * result[indexRev];
    pow = pow * 2;
  }

  reg[rn] = bit;
  int c = reg[rn];

  //Negative Flag
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //Zero Flag
  if (reg[rn] == 0) {
    if (c > reg[rn]) {
      SET_C;
      SET_Z;
    } else {
      SET_Z;
    }
  }
}
 

void lsls(int rn, int rm) {
  // Include your code to emulate the "lsls" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

  int tempRm = reg[rm];
  int tempRn = reg[rn];
  int temp = 0;
  int remainder = 0;
  int carryOn = 0;
  int carryOff = 0;

  //Positive Shifting
  if (tempRm > 0) {
    if (tempRm % 32 == 0) {
      if (tempRm == 32) {
	temp = 0;
      } else if (tempRm <= 128) {
	carryOff = 1;
	temp = 0;
      } else {
	temp = reg[rn];
      }
    } else {
      remainder = tempRm % 32;
      if (remainder == 31) {
	carryOff = 1;
	temp = 0;
      } else {
	temp = reg[rn] << remainder;
      }
    }
    //Negative Shifting 
  } else {
    if (tempRm == -2147483648) {
      temp = reg[rn];
    } else {
      temp = 0;
      carryOff = 1;
    }
  }

  reg[rn] = temp;
  psr = 0;


  //Negative Flag
  if (reg[rn] & 0x80000000) {
    SET_N;
  }

  //Zero Flag
  if (reg[rn] == 0) {
    if (tempRn > reg[rn]) {
      if (carryOff == 0) {
	SET_C;
      }
      SET_Z;
    } else {
      SET_Z;
    }
  }

  //Carry Flag
  if((carryOn == 1 || tempRn > reg[rn]) && carryOff == 0) {
    SET_C;
  }
}

void asrs(int rn, int rm) {
  // Include your code to emulate the "asrs" instruction:
  // subs rn, rm
  // rn = index where operand1 is located in reg[], also destination for result
  // rm = index where operand2 is located in reg[]

}

/* main.c ends here */
