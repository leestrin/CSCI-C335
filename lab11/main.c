
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <stdio.h>
#include <stdint.h>
/*
Author: James Mantz, Simon Lee
Partner: 
Data Created:2/5/16
Last Modified by: James Mantz
Data Last Modified: 4/07/16
Assignment: Boards
Part of: Lab 11
*/ 

// Simple looping delay function
/*  void delay(void) { */
/*   int i = 2000000; */
/*   while (i-- > 0) { */
/*     asm("nop");  This stops it optimising code out  */
/*   } */
/* } */

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  f3d_led_init();
  f3d_systick_init();

  while (1) {
    putchar(getchar());
  }

}



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while(1);
}
#endif

/* main.c ends here */
