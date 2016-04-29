/* f3d_nunchuk.c --- 
 * 
 * Filename: f3d_nunchuk.c
 * Description: 
 * Author: Bryce Himebaugh, Simon Lee (sijlee), Tim Carlson (dotcarls)
 * Created: Thu Oct 31 09:40:37 2013
 * Last-Updated: march 25, 2016
 *           By: Simon Lee (sijlee), Tim Carlson (dotcarls)
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
#include <f3d_nunchuk.h>
#include <stdio.h>
#include <f3d_lcd_sd.h>
#include <math.h>

#define NUNCHUK_ADDRESS 0xA4

void f3d_nunchuk_init(void) {
  uint8_t realb = 0x00;
  uint8_t buf = 0x55;
  uint8_t buf2 = 0x00;


  // Use for factory Wii Nunchuk controllers
  // f3d_i2c1_write(NUNCHUK_ADDRESS,0x40,&realb);
  // Use for 3 party nunchuks like we have in the lab
  f3d_i2c1_write(NUNCHUK_ADDRESS,0xf0,&buf); 
  f3d_i2c1_write(NUNCHUK_ADDRESS,0xfb,&buf2);
}

void f3d_nunchuk_read(nunchuk_t *n) {
  uint8_t data[6] = {0,0,0,0,0,0};
  int i;
  unsigned short tmp;

  f3d_i2c1_read_nunchuk(0xA5, data, 6);
  n->jx = data[0];
  n->jy = data[1];

  tmp = data[2];
  tmp = tmp << 2;
  n->ax = tmp | ((data[5] & 0x0C) >> 2);

  tmp = data[3];
  tmp = tmp << 2;
  n->ay = tmp | ((data[5] & 0x30) >> 4);

  tmp = data[4];
  tmp = tmp << 2;
  n->az = tmp | ((data[5] & 0xC0) >> 6);

  switch (data[5] & 0x03) {
  case 2:
    n->z = 1;
    n->c = 0;
    break;
  case 1:
    n->z = 0;
    n->c = 1;
    break;
  case 0:
    n->z = 1;
    n->c = 1;
    break;
  case 3:
    n->z = 0;
    n->c = 0;
    break;
  }
}


void nunchukScreen(struct nunchuk_data data){
  char aixsData[9];    
  float pitch;
  float roll;
  int dataPitch;
  int dataRoll;
  //f3d_lcd_fillScreen(RED);
  f3d_lcd_drawString(45, 140, "Nunchuk",BLACK, WHITE);
  //Accel data
  //for tilt angle
  pitch = atan2f(data.ax,(sqrtf (powf(data.ay, 2.0)) + (powf(data.az, 2.0))));
  float pitchCounter = fabsf(pitch) / M_PI;
  pitchCounter *= 100000;
  printf("Pitch: %f\n",pitchCounter);
  roll = atan2f(data.ay, (sqrtf (powf(data.ax, 2.0)) + (powf(data.az, 2.0))));
  float rollCounter = fabsf(roll) / M_PI;
  //roll needs to be multiplied more
  rollCounter *= 100000;
  printf("Roll: %f\n",rollCounter);
  // printf("data.az: %f\n",data.az);

   //Pitch
  //  sprintf(aixsData, "%f", pitch);
   f3d_lcd_drawString(10, 40, "Pitch", RED, WHITE);
   blockGen((int)pitchCounter, 50);
   
   //Roll
   // sprintf(aixsData, "%f", roll);
   f3d_lcd_drawString(10, 60, "Roll", RED, WHITE);
   blockGen((int)rollCounter, 70);
   
}
/* f3d_nunchuk.c ends here */
