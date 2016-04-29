/* f3d_mag.c --- 
 * 
 * Filename: f3d_mag.c
 * Description: magnetic sensor driver for SMT32
 * Author: Bryce Himebaugh, Simon Lee (sijlee), Ethan Lawton (elawton2)
 * Created: Thu Oct 31 09:27:11 2013
 * Last-Updated: 03/10/2016
 *           By: Simon Lee
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
#include <f3d_mag.h>
#include <f3d_lcd_sd.h>
#include <math.h>
#include <f3d_led.h>

void f3d_mag_init() {
  // MAG I2C Address = 0x3C 

  uint8_t value = 0; 
 
  value = 0x14;                  //Temp sensor disable,30Hz Output Rate 
  f3d_i2c1_write(0x3C, 0x00,  &value); // Mag (0x3C), CRA (0x00) 

  value = 0xE0;                      // +/- 8.1 Gauss Full Scale
  f3d_i2c1_write(0x3C, 0x01, &value); // Mag (0x3C), CRB (0x01)

  value = 0x00;                      // Continuous Conversion
  f3d_i2c1_write(0x3C, 0x02, &value); // Mag (0x3C), MR  (0x23)
}

void f3d_mag_read(float *mag_data) {
  uint8_t buffer[6];
  int i;
  
  f3d_i2c1_read(0x3C, 0x03, buffer,2);   // Read X Axis
  f3d_i2c1_read(0x3C, 0x07, buffer+2,2); // Read Y Axis
  f3d_i2c1_read(0x3C, 0x05, buffer+4,2); // Read Z Axis (notice that Z is out of order in the chip). 
  
  for (i=0; i<2; i++) {
    mag_data[i]=(float)((int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]))/230;
  }
  mag_data[2]=(float)((int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]))/205;
}

void compassScreen(){
  f3d_lcd_drawString(20, 140, "Compass Heading",BLACK, WHITE);
  f3d_lcd_drawString(5, 25, "Check LEDs" , RED, WHITE);
  
  float axis[3];
  
  float pitch;
  float roll;
  
  float heading;
  char i2cData[8];
  int i2cDataPitch;
  int i2cDataRoll;
  
  f3d_mag_read(axis);
  heading = atan2f(((axis[0] * sinf(roll) * sinf(pitch)) + (axis[1] * cosf(roll)) - (axis[2] * sinf(roll) * cosf(pitch))), ((axis[0] * cosf(pitch)) + (axis[2] * sinf(pitch))));
  printf("Heading: %f\n", heading);
  
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
}



/* f3d_mag.c ends here */
