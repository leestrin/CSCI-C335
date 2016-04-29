/***********************************************
 * rpn.c
 * rpn calculator that acts like Unix desk calculator or HP post-fix calculator
 *
 * Author: Simon Lee
 * Date Created: Jan 24, 2016
 * Last Modified by: Simon Lee
 * Date Last Modified: Jan 25, 2016
 * Assignment HW0
 * Part of: C335 assognment
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//stack implementation as Link-List form
//Provided as C335 HW0 guide 
typedef struct CELL* LIST;

struct CELL {
  int val;
  LIST next;
};

LIST stack;

void push(int val) {
  LIST c = (LIST) malloc(sizeof(struct CELL));
  if (c) {
    c->val = val;
    c->next = stack;
    stack = c;
  } else {
    //When its not able to push, just exit
    exit(1);
  }
}


int pop() {
  LIST c = stack;
  if (c) {
    //Set pointer to next element (pop)
    stack = stack->next;
    //Store top value to local variable
    int val = c->val;
    free(c);
    //Then return the top value
    return val;
  } else {
    exit(1);
  }
}

int main() {
  //When start, we  make sure the stack (list) is empty
  stack = NULL;
  LIST remainder;
  //Set input to allow 200 char for now
  char input[200];
  //Initializing number variables
  int num;
  int firstNum;
  int secondNum;

  //We quit the program in case of EOF or q input
  while (*input != EOF && *input != 'q') {
    //Scan from keyboard for input
    scanf("%s", input);
    //Cast each number in input
    num = atoi(input);
    //From casting, check if each elements are numbers
    if (strcmp(input, "0") == 0 || num != 0) {
      //If an element is a integer, we push it to stack
      push(atoi(input));
    } else {
      //If not, they are either binary operator or a command
      switch (*input) {
	//If we see q, quit
      case 'q':
	break;
      case 'f':
	//Set remainder list equal to what ever is left in the stack
	remainder = stack;
	while (remainder) {
	  //While there is something in remainder list, we print out all elements
	  printf("%d\n", remainder->val);
	  //Set pointer to allow it to point & show next element
	  remainder = remainder->next;
	}
	break;
      case 'p':
	if (stack) {
	  //Access top of stack, and print
	  printf("%d\n", stack->val);
	} else {
	  //if empty, say so
	  printf("dc: stack empty\n");
	}
	break;
      case 'c':
	//while there is something in the stack,
	//Pop until empty
	while (stack) {
	  pop();
	}
	break;
      case '+':
	//When there are more than two elements in stack,
	if (stack && stack->next) {
	  //bind two number variables by order from top (most right)
	  secondNum = pop();
	  firstNum = pop();
	  //push the addition of two most top elements
	  push(firstNum + secondNum);
	} else {
	  //if there are less than or equal to one elements, we cannot compute
	  printf("dc: stack empty\n");
	}
	break;
      case '-':
	if (stack && stack ->next) {
	  secondNum = pop();
	  firstNum = pop();
	  push(firstNum - secondNum);
	} else {
	  printf("dc: stack empty\n");
	}
	break;
      case '*':
	if (stack && stack ->next) {
	  secondNum = pop();
	  firstNum = pop();
	  push(firstNum * secondNum);
	} else {
	  printf("dc: stack empty\n");
	}
	break;
      case '/':
	if (stack && stack ->next) {
	  secondNum = pop();
	  firstNum = pop();
	  push(firstNum / secondNum);
	} else {
	  printf("dc: stack empty\n");
	}
	break;
      default:
	break;
      }
    }
  }
  return 0;
}
