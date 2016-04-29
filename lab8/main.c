/*********************************
 * main.c
 *
 * main.c for STM32 
 * calls functions from I2C drivers to initialize I2C, display pitch & roll and compass data
 *
 * Author: Simon Lee (sijlee), Ethan Lawton (elawton2)
 * Date Created: 03/10/2016
 * Last Modified by: Simon Lee (sijlee)
 * Date Last Modified: 03/04/2016
 * Assignment: Lab 8
 * Part of: C335
 */
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_led.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000

//making block of pixels
void blockGen(int mag, int y){
  int start;
  if (mag >= 0){
    for (start = 5; start <= 123; start++){
      if (start <= mag){
	//draw block
	f3d_lcd_drawPixel(start, y, RED);
	f3d_lcd_drawPixel(start, y+1, RED);
	f3d_lcd_drawPixel(start, y+2, RED);
	f3d_lcd_drawPixel(start, y+3, RED);
	f3d_lcd_drawPixel(start, y+4, RED);
      } else {
	//remove block by BG color
	f3d_lcd_drawPixel(start, y, BLUE);
	f3d_lcd_drawPixel(start, y+1, BLUE);
	f3d_lcd_drawPixel(start, y+2, BLUE);
	f3d_lcd_drawPixel(start, y+3, BLUE);
	f3d_lcd_drawPixel(start, y+4, BLUE);
	}
    }
  }

  //For negative magnitudes
  if (mag <= 0){
    mag = mag * -1;
    for (start = 5; start <= 123; start++){
      if (start <= mag){
	f3d_lcd_drawPixel(start, y, GREEN);
	f3d_lcd_drawPixel(start, y+1, GREEN);
	f3d_lcd_drawPixel(start, y+2, GREEN);
	f3d_lcd_drawPixel(start, y+3, GREEN);
	f3d_lcd_drawPixel(start, y+4, GREEN);
      } else {
	f3d_lcd_drawPixel(start, y, BLUE);
	f3d_lcd_drawPixel(start, y+1, BLUE);
	f3d_lcd_drawPixel(start, y+2, BLUE);
	f3d_lcd_drawPixel(start, y+3, BLUE);
	f3d_lcd_drawPixel(start, y+4, BLUE);
	}
    }
  }
}

int main(void) {
   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);
   //to stroe pitch and roll data
   float axis[3];
   
   float pitch;
   float roll;

   float heading;
   char data[8];
   int dataPitch;
   int dataRoll;


  // Set up your inits before you go ahead
   f3d_uart_init();
   f3d_led_init();
   f3d_user_btn_init();
   f3d_lcd_init();
   
   f3d_i2c1_init();
   delay(10);
   f3d_accel_init();
   delay(10);
   f3d_mag_init();
   delay(10);

   int buttonState;
   //drawing before loop for performance
   f3d_lcd_fillScreen2(BLUE);
   f3d_lcd_drawString(6,0,"Pitch: ",BLACK,BLUE);
   f3d_lcd_drawString(6,10,"Roll: ",BLACK,BLUE);

   f3d_lcd_drawString(ST7735_width/2-18, 45, "Pitch", WHITE, BLUE);
   f3d_lcd_drawString(ST7735_width/2-18, 65, "Roll", WHITE, BLUE);
   
   while(1){
     //use accel sensor
     f3d_accel_read(axis);
     pitch = atan2f(axis[0],(sqrtf (powf(axis[1], 2.0)) + (powf(axis[2], 2.0))));
     printf("Pitch: %f\n", pitch);

     roll = atan2f(axis[1],(sqrtf (powf(axis[0], 2.0)) + (powf(axis[2], 2.0))));
     printf("Roll: %f\n", roll);
     //use magnetic sensor
     f3d_mag_read(axis);
     heading = atan2f(((axis[0] * sinf(roll) * sinf(pitch)) + (axis[1] * cosf(roll)) - (axis[2] * sinf(roll) * cosf(pitch))), ((axis[0] * cosf(pitch)) + (axis[2] * sinf(pitch))));
     printf("Heading: %f\n", heading);
     //when button is pressed, change mode and store button information
     if (user_btn_read()) {
       buttonState = (buttonState +1) % 2;
       printf("Mode changed");
       while(user_btn_read());
     }
     //in compass mode,
     //LED always points to north
     if (buttonState == 0) {
       f3d_led_all_off();
       //east-side LEDs
       if (heading <= 0.375 && heading >= -0.375){
	 f3d_led_on(5);
       }
       if (heading <= -0.375 && heading >=-1.5){
	 f3d_led_on(6);//4
       }
       if (heading <= -1.5 && heading >= -1.875){
	 f3d_led_on(7);//3
       }
       if (heading <= -1.875 && heading >= -2.25){
	 f3d_led_on(0);//2
       }
       if (heading <= -2.25 && heading >= -3){
	 f3d_led_on(1);
       }
       //west-side LEDs
       if (heading >= 0.375 && heading <= 1.5){
	 f3d_led_on(4);//6
       }
       if (heading >= 1.5 && heading <= 1.875){
	 f3d_led_on(3);//7
       }
       if (heading >= 1.875 && heading <= 2.25){
	 f3d_led_on(2);//0
       }
       if (heading >= 2.25 && heading <= 3){
	 f3d_led_on(1);
       }
       
       if(heading < -3)
	 heading = 3;
     } else {
       //when in accel mode,
       f3d_led_all_off();
       //draw pitch info on LCD
       sprintf(data, "%f", axis[0]);
       f3d_lcd_drawString(6*6,0,data,BLACK,BLUE);

       dataPitch = (int)(axis[0] * 100);
       blockGen(dataPitch, 55);
       //draw roll info on LCD
       sprintf(data, "%f", axis[1]);
       f3d_lcd_drawString(6*6,10,data,BLACK,BLUE);

       dataRoll = (int)(axis[1] * 100);
       blockGen(dataRoll, 75);
       
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

