/*
 * Filename: main.c
 * Part of lab 10
 * Created by Gabi Watson(gabwatso) and Simon Lee (sijlee)
 * Created on 3/25/2016
 * Last modified by gabwatso and Simon Lee (sijlee)
 * Last Modified on 3/31/2016
*/

/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <math.h>

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;	/* File system object */
FIL Fil;	/* File object */

typedef struct bmpp{
  uint8_t b;
  uint8_t g;
  uint8_t r;
} pix24;

pix24 Buff[128];	/* File read buffer */
uint8_t junk[54];
float farray[3];
float roll, pitch;
nunchuk_t nun;
float acc[3];
float mag[3];

int main(void) {
  char footer[20];
  int count=0;
  int i,j,c,cpast,header;
  double pi = 3.14;
  int pastC = 1;

  FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_delay_init();
  delay(10);
  f3d_rtc_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);


  f_mount(0, &Fatfs);	/* Register volume work area (never fails) */
  
  f3d_lcd_fillScreen(BLACK);
  c = 0;

  while(1){
    f3d_nunchuk_read(&nun);
    f3d_accel_read(acc);
    f3d_mag_read(mag);
    delay(100);

    //solves for roll pitch and yaw
    roll  = atan(acc[0]/sqrt(pow(acc[1],2) + pow(acc[2],2)));
    pitch =  atan(acc[1]/sqrt(pow(acc[0],2) + pow(acc[2],2))); 

    printf("roll: %f pitch: %f\n", (roll*180/pi), (pitch*180/pi));
    //scroll
    if(nun.jx == 255) {
      c++;
    }
    if(nun.jx == 0) {
      c--;
    }
    //when orientation get changed
    if (c == 0 && (pitch*180/pi) > 40) {
      c = 3;
    }
    if (c == 1 && (pitch*180/pi) > 40) {
      c = 4;
    }
    if (c == 2 && (pitch*180/pi) > 40) {
      c = 5;
    }
    //vertical orientation
    if(c > 2 && (pitch*180/pi) < 40) {
      c = 0;
    }
    if(c < 0 && (pitch*180/pi) < 40) {
      c = 2;
    }
    
    if(pastC != c){
      switch(c){
      case 0:
	rc = f_open(&Fil, "window.bmp", FA_READ);
	break;
      case 1:
	rc = f_open(&Fil, "apple.bmp", FA_READ);	
	break;
      case 2:
	rc = f_open(&Fil, "bacon.bmp", FA_READ);	
	break;
	//orientation change
      case 3:
	rc = f_open(&Fil, "wilo.bmp", FA_READ);
	break;
      case 4:
	rc = f_open(&Fil, "aplo.bmp", FA_READ);
	break;
      case 5:
	rc = f_open(&Fil, "balo.bmp", FA_READ);
	break;
      }

      if (rc) die(rc);

      rc = f_read(&Fil, junk, 54, &br);		

      if (rc) die(rc);
      //writing pixel to lcd
      for(j = 160; j >0; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	//printf("Read col\n");
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].r >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].b >> 3);
	  // printf("%c \n", color);
	  f3d_lcd_drawPixel(i, j, color);
	}
      }
      rc = f_close(&Fil);
    }
    
    pastC = c;
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

