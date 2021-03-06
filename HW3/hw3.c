/*********************************
 * hw3.c
 *
 * disassemblr for Arm Thumb-2 instruction
 *
 * Author: Simon Lee (sijlee)
 * Date Created: 03/01/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 03/01/2016
 * Assignment: HW3
 * Part of: C335
 */

#include<stdio.h>

#define types(x) (((x) >> 10) & 0x1f)
#define opc(x) (((x) >> 9) & 0x1)
#define rd(x) (((x) >> 0) & 0x7)
#define rn(x) (((x) >> 3) & 0x7)
#define rm(x) (((x) >> 6) & 0x7)
#define opcode(x) (((x) >> 6) & 0xf)

//register names 
char *regnames[] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "lr", "pc"};
//data processing opnames & condition names 
char *opname[] = {"ands", "eors", "lsls", "lsrs", "asrs", "adcs", "sbcs", "rors", "tst", "tsbs", "cmp", "cmn", "orrs", "muls", "bics", "mvns"};


void printAsm(int inst){
  //Add/subtract register
  if(types(inst) == 6) {
    if(opc(inst) == 0) {
      printf("adds %s, %s, %s\n", regnames[rd(inst)], regnames[rn(inst)], regnames[rm(inst)]);
    } else if (opc(inst) == 1) {
      printf("subs %s, %s, %s\n", regnames[rd(inst)], regnames[rn(inst)], regnames[rm(inst)]);
    }
  //Data-processing register
  } else if (types(inst) == 16){
    printf("%s %s, %s\n", opname[opcode(inst)],regnames[rd(inst)], regnames[rn(inst)]);
  } else {
    printf(".hword 0x%x\n", inst);
  }

}

int main() {
  int inst;
  printf(".text\n.syntax unified\n.thumb\n");
  while (scanf("%x", &inst)==1){
    printAsm(inst);
  }
}

