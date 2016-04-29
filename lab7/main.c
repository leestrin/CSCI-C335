/* main.c ---
*
* Filename: main.c
* Part of: C335 Lab7
* Authors: Austin Moore (aulmoore) & Simon Lee (sijlee)
* Created on: 2/26/2016
* Last modified by: Austin Moore & Simon Lee
* Last modified on: 3/1/2016
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>


#define TIMER 20000

//Delay function
void delay2(int count)
{
  while(count-- > 0)
    {
      int i = 10000;
      while(i-- > 0)
	{
	  asm("nop"); // Stops optimization
	}
    }
}
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
  // Set buffer to protect initializations
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  //Initialize peripherals
  f3d_gyro_init();
  f3d_uart_init();
  f3d_lcd_init();

  int chW = 6;
  int chH = 10;
  int width = ST7735_width;
  char data[8];
  int i, j;
  int dataX;
  int dataY;
  int dataZ;

  //Array to store gyro data
  float axis[3];

  //Fill background to RED
  f3d_lcd_fillScreen2(BLUE);

  //Set up data labels
  f3d_lcd_drawString(chW,0,"X: ",BLACK,BLUE);
  f3d_lcd_drawString(chW,chH,"Y: ",BLACK,BLUE);
  f3d_lcd_drawString(chW,2*chH,"Z: ",BLACK,BLUE);

  //Create bar graph labels
  f3d_lcd_drawString(width/2-18, 45, "X-Axis", WHITE, BLUE);
  f3d_lcd_drawString(width/2-18, 65, "Y-Axis", WHITE, BLUE);
  f3d_lcd_drawString(width/2-18, 85, "Z-Axis", WHITE, BLUE);

  //Labels to show which color is which value
  f3d_lcd_drawString(chW, 110, "Positive", RED, BLUE);
  f3d_lcd_drawString(width-9*chW, 110, "Negative", GREEN, BLUE);

  //Create the bar graph box
  int top;
  int side;
  f3d_lcd_drawString(3, 130, "Loading...",WHITE, BLUE);
  for (top = 3; top < ST7735_width-3; top++) {
    for (side = 40; side < 103; side++) {
      f3d_lcd_drawPixel(top, 40, WHITE);
      f3d_lcd_drawPixel(top, 41, WHITE);
      f3d_lcd_drawPixel(top, 101, WHITE);
      f3d_lcd_drawPixel(top, 102, WHITE);

      f3d_lcd_drawPixel(2, side, WHITE); 
      f3d_lcd_drawPixel(3, side, WHITE);
      f3d_lcd_drawPixel(ST7735_width-2, side, WHITE);
      f3d_lcd_drawPixel(ST7735_width-3, side, WHITE);
    }
  }
  f3d_lcd_drawString(64, 130, "Done!",WHITE, BLUE);
  
  //Loop, collecting gyro data
  while(1)
    {
      f3d_gyro_getdata(axis);
      printf("X: %f\n", axis[0]);

      sprintf(data, "%f", axis[0]);
      f3d_lcd_drawString(4*chW,0,data,BLACK,BLUE);

      sprintf(data, "%f", axis[1]);
      f3d_lcd_drawString(4*chW,chH,data,BLACK,BLUE);

      sprintf(data, "%f", axis[2]);
      f3d_lcd_drawString(4*chW,2*chH,data,BLACK,BLUE);
      
      //360/120 = 3 so we divided magnitude by 3
      //X-axis point graph
      dataX = (int)axis[0] / 3.0;
      blockGen(dataX, 55);
      // Y-axis point graph
      dataY = (int)axis[1] / 3.0;
      blockGen(dataY, 75);
      // Z-axis point graph
      dataZ = (int)axis[2] / 3.0;
      blockGen(dataZ, 95);    
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
