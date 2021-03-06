/********************************************************** 
 *   main.c
 *    
 *   Author: Simon Lee (sijlee), Tim Carlson (dotcarls)
 *   Date Created: March 23, 2016
 *   Last Modified by: Simon Lee (sijlee), Tim Carlson (dotcarls)
 *   Date Last Modified: March 25, 2016
 *   Assignment: lab9
 *   Part of: lab9
 * */

/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <f3d_delay.h>
#include <math.h>
#include <f3d_nunchuk.h>
#include <f3d_led.h>
#include <f3d_gyro.h>
//includes necesary libraries/drivers



int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  struct nunchuk_data data;
  int screen = 0;
  //initialization
  delay(10);  
  f3d_lcd_init();
  delay(10);
  //reset & initializing physical screen
  f3d_lcd_fillScreen2(WHITE);
  
  f3d_i2c1_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_uart_init();
  delay(10);
  f3d_gyro_init();
  delay(10);

  f3d_led_init();
  delay(10);

  while (1){
    f3d_nunchuk_read(&data);
    //Selecting screen number
    //reset screen
    if(data.c == 1 || data.jx == 0){    
      while(data.c == 1 || data.jx == 0){
	f3d_nunchuk_read(&data);
      }
      f3d_lcd_fillScreen2(WHITE);
      screen--;
      //Move to left info screen
      if(screen == -1) {
	screen = 3;
      }
      printf("%d", screen); 
    }
    //Selecting screen number
    //reset screen
    if(data.z == 1 || data.jx == 255){    
      while(data.z == 1 || data.jx == 255){
	f3d_nunchuk_read(&data);
      }
      f3d_lcd_fillScreen2(WHITE);
      screen++;
      //Move to left info screen
      if(screen == 4) {
	screen = 0;
      }
    }

    //switch screen
    switch (screen) {
    case 0:
      printf("Nunchuk\n");
      nunchukScreen(data);
      break;
    case 1:
      printf("Gyro\n");
      gyroScreen();
      break;
    case 2:
      printf("Accel\n");
      accelScreen();
      break;
    case 3:
      printf("Compass\n");
      compassScreen();
      break;
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

