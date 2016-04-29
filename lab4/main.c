/*********************************
 * main.c
 *
 * main.c for STM32 
 * calls functions from f3d_led.c to initialize leds
 *
 * Author: Simon Lee (sijlee), Ethan Lawton (elawton2)
 * Date Created: 02/05/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 02/10/2016
 * Assignment: Lab 4
 * Part of: C335
 */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  //button state for initial button state
  int btn_state;
  //int i for button number
  int i=1;    
  //initializing components
  f3d_led_init();
  f3d_user_btn_init();
  //inf. loop
  while (1)
    {
      //check initial button state
      btn_state = user_btn_read();
      //when not pressed
      if (btn_state == 0){
	//go through all the leds and turn on one by one
	//using delay    
	for(i=1; i<=7; i++){
          while(user_btn_read()){
	    f3d_led_on(i);
	    delay();
	  }
	  //when button is pressed, stop for loop and
	  //only turn on led of the turn
          f3d_led_on(i);
          while(user_btn_read()){ 
	    delay();
	  }
          delay();
          f3d_led_off(i);
        }
	//we start from led 0
        f3d_led_on(0);
        delay();
        f3d_led_off(0);
        delay();
	//turn everything on before loop back
        f3d_led_all_on();
        delay();
        f3d_led_all_off();
      }
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
