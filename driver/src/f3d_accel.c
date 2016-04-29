/* f3d_accel.c --- 
 * 
 * Filename: f3d_accel.c
 * Description: accel sensor driver for STM32
 * Author: Bryce Himebaugh, Simon Lee (sijlee), Ethan Lawton (elawton2)
 * Created: Thu Oct 31 09:14:43 2013
 * Last-Updated: 03/10/2016
 *           By: Simon Lee (sijlee)
 *     Update #: 2
 * Compatibility: STM32
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <math.h>
#include <f3d_lcd_sd.h>
void f3d_accel_init() {
  // Accelerometer I2C Address = 0x32 

  uint8_t value = 0; 
 
  value = 0x40|0x07;                 // Normal Power Mode, All Axis Enable (X,Y,Z)
  f3d_i2c1_write(0x32, 0x20, &value); // Accel (0x32), Ctrl Reg1 (0x20) 

  value = 0x08;                      // Continuous Update, Little Endian, 2G Sensitivity, High Resolution Mode
  f3d_i2c1_write(0x32, 0x23, &value); // Accel (0x32, Ctrl Reg4  (0x23)


  value = 0x10 | 0x80;               // HPF Cutoff 16, High Pass Filter Normal Mode, AO1/AO1 Disable
  f3d_i2c1_write(0x32, 0x21, &value); // Accel (0x32, Ctrl Reg2  (0x21)
}

void f3d_accel_read(float *accel_data) {
  int16_t raw_data[3];
  uint8_t buffer[6];
  int i;

  f3d_i2c1_read(0x32, 0x28, buffer, 6); // Read 6 bytes starting from accel (0x32), starting at register 0x28. 
  for (i=0; i<3; i++) {
    raw_data[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i])/(uint8_t)16;
    accel_data[i]=(float)raw_data[i]/1000.0;
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


void accelScreen(){
  f3d_lcd_drawString(40, 140, "Board Tilt",BLACK, WHITE);
  float axis[3];
   
  float pitch;
  float roll;

  float heading;
  char data[8];
  int dataPitch;
  int dataRoll;


  // f3d_lcd_fillScreen2(BLUE);
  f3d_lcd_drawString(6,0,"Pitch: ",BLACK,WHITE);
  f3d_lcd_drawString(6,10,"Roll: ",BLACK,WHITE);

  f3d_lcd_drawString(ST7735_width/2-15, 45, "Pitch", BLACK, WHITE);
  f3d_lcd_drawString(ST7735_width/2-15, 65, "Roll", BLACK, WHITE);

  f3d_accel_read(axis);
  pitch = atan2f(axis[0],(sqrtf (powf(axis[1], 2.0)) + (powf(axis[2], 2.0))));
  printf("Pitch:   %f\n", pitch);

  roll = atan2f(axis[1],(sqrtf (powf(axis[0], 2.0)) + (powf(axis[2], 2.0))));
  printf("Roll:   %f\n", roll);

  //when in accel mode,
  //draw pitch info on LCD
  sprintf(data, "%f", axis[0]);
  f3d_lcd_drawString(6*6,0,data,BLACK,WHITE);

  dataPitch = (int)(axis[0] * 100);
  blockGen(dataPitch, 55);
  //draw roll info on LCD
  sprintf(data, "%f", axis[1]);
  f3d_lcd_drawString(6*6,10,data,BLACK,WHITE);

  dataRoll = (int)(axis[1] * 100);
  blockGen(dataRoll, 75);
}

/* f3d_accel.c ends here */
