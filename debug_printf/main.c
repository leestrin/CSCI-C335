/*********************************
 * File: main.c
 * Part of: C335 Lab 7
 * Author: Simon Lee (sijlee), Ben Borders (btborder)
 * Date Created: 02/16/2016
 * Last Modified by: Simon Lee (sijlee) & Austin Moore (aulmoore)
 * Date Last Modified: 03/1/2016
 */

//main.c for lab7
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void delay(void) {
  int i = 200000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void){
  //initializing drivers
  f3d_uart_init();
  f3d_gyro_init();
  f3d_led_init();
  f3d_user_btn_init();

  /////////////////// data ///////////////////
  /*
  //axis from gyro
  float axis[3];
  //to select X Y Z
  int position;
  //getcharHelper does not wait until RESET
  char tempChar = getcharHelper();
  */
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  int buttonState = 1;

  while(1){
    //The loop alternates between LED 0 and 1 by pressing the button.
    f3d_led_on(buttonState + 1);
    delay();

    //On one state, we print a few printf statements before blinking
    if(buttonState){
      printf("A");
      printf("B");
      printf("C");
      printf("D");
      printf("A");
      printf("B");
      printf("C");
      printf("D");
      printf("A");
      printf("B");
      printf("C");
      printf("D");
      printf("A");
      printf("B");
      printf("C");
      printf("D");
    }

    f3d_led_all_off();
    delay();
    if (user_btn_read()){
      buttonState = (buttonState + 1) % 2;
      while(user_btn_read());
    }
 
    /*
    // printf("%d", putchar(getchar()));
    f3d_gyro_getdata(axis);

    if (user_btn_read()) {
      position = (position + 1) % 3;
      printf("Current axis %c \n", position + 88);
      //to stop the cycle
      while(user_btn_read());
    }
    //assign getcharHelper to make sure we are receiving input everytime  
    tempChar = getcharHelper();
    if (tempChar  == 'x'){
      position = 0;
      printf("X-AXIS");
    } else if (tempChar == 'y'){
      position = 1;
      printf("Y-AXIS");
    } else if (tempChar == 'z'){
      position = 2;
      printf("Z-AXIS");
    }
    
    f3d_led_all_off();
    //for west side
    if (axis[position] < 0) {
      //get angular velocity
      switch((int)((axis[position] * -1) / 72.0)){
      case 0: 
	f3d_led_on(1);
	break;
      case 1:
	f3d_led_on(1); 
	f3d_led_on(2);
	break;
      case 2:
	f3d_led_on(1);
	f3d_led_on(2);
	f3d_led_on(3);
	break;
      case 3:
	f3d_led_on(1);
	f3d_led_on(2);
	f3d_led_on(3); 
	f3d_led_on(4);
	break;
      case 4:
	f3d_led_on(1);
	f3d_led_on(2);
	f3d_led_on(3); 
	f3d_led_on(4);
	f3d_led_on(5);
	break;
      default:
	//f3d_led_on(5);
	break;
  
      }
      delay();
      delay();
      delay();
    } else {
      //for east side
      f3d_led_all_off();
      switch((int)(axis[position] / 72.0)){
      case 0: 
	f3d_led_on(1);
	break;
      case 1:
	f3d_led_on(1);
	f3d_led_on(0);
	break;
      case 2:
	f3d_led_on(1);
	f3d_led_on(0); 
	f3d_led_on(7);
	break;
      case 3:
	f3d_led_on(1);
	f3d_led_on(0); 
	f3d_led_on(7); 
	f3d_led_on(6);
	break;
      case 4:
	f3d_led_on(1);
	f3d_led_on(0); 
	f3d_led_on(7); 
	f3d_led_on(6);
	f3d_led_on(5);
	break;
      
      default:
	//f3d_led_on(5);
	break;

      }
      delay();
      delay();
      delay();
    }
    */
    /*
    if (axis[0] < 0 && axis[1] < 0) {
      f3d_led_on(0);
    
    }
    */
    //printing out  current axis
    // printf("X: %f Y: %f Z:%f \n", axis[0], axis[1], axis[2]);
   
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
