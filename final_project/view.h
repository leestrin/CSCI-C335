#ifndef MY_VIEW_HEADER

#define MY_VIEW_HEADER

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers
#include <f3d_lcd_sd.h>
#include <diskio.h>
#include <stdio.h>
#include <math.h>

#define HEIGHT 160
#define WIDTH 128
#define FINISH_LINE 20

typedef struct {
  uint8_t x;
  uint8_t y;
} point;

typedef struct {
  point ul;
  point lr;
  int old_xl;
  int old_xr;
  uint16_t color;
  int velocity;
} square;

/* typedef struct { */
/*   square* blocks; */
/*   /\* int speed; *\/ */
/*   /\* point ul; *\/ */
/*   /\* point lr; *\/ */
/* } square_buddies; */

void init();
void draw_rect(uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
void draw_square(square);
void draw_background();
void draw_win_message();
void draw_lost_message();
square move_square(square);
square make_square(int, int, int, int, int, int, int, uint16_t);
/* void draw_square_buddies(square_buddies); */
/* square_buddies make_square_buddies(square, int); */
#endif
