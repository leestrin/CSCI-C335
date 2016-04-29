/* main.c ---
 *
 * Filename: main.c
 * Description: Main logic of stacker game
 * Author:
 * Maintainer:
 * Created: Thu April 15, 2016
 * Last-Updated: Sunday April 24, 2016
 *           By: Brandon Burzon, Simon Lee
 *     Update #: 30
 * Keywords:
 * Compatibility: Backward complatible
 *
 */

/* Commentary: nO comments
 *
 *
 *
 */

/* Change log: lots
 *
 *
 */
/* Code: */


#include <stm32f30x.h>  // Pull in include files for F30x standard drivers
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_dac.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <f3d_systick.h>
#include <f3d_delay.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "view.h"
#include "audio.h"

#define WIN 1
#define LOST 2
#define Z_BUTTON 1
#define C_BUTTON 2

void initialize();

nunchuk_t nunchuk_data;
nunchuk_t *nunchuk_pointer = &nunchuk_data;

int is_over(square);
int on_click();
square create_flag();
square create_start_block();
square block_from_left(square);
square block_from_right(square);
square ask_play_again();
square create_new_block(square);
square event_handler(square);

int main(void) {
  initialize();
  draw_background();

  square flag = create_flag();
  square block = create_start_block();
  draw_square(block);

  f_mount(0, &Fatfs);/* Register volume work area */

  while (1){
    block = event_handler(block);
    block = move_square(block);
    flag = move_square(flag);
    delay(10);
  }

}

square event_handler(square old_block) {
  square new_block;
  if(on_click() == Z_BUTTON) {
    if(is_over(old_block) == LOST ) {
      draw_lost_message();
      play_selected_file("lost.wav");
      new_block = ask_play_again();
      draw_square(new_block);
    } else if(is_over(old_block) == WIN) {
      draw_win_message();
      play_selected_file("won.wav");
      new_block = ask_play_again();
      draw_square(new_block);
    } else {
      new_block = create_new_block(old_block);
    }
  } else {
    new_block = old_block;
  }
  return new_block;
}

int on_click() {
  int button = 0;
  if(nunchuk_pointer->z) {
    button = Z_BUTTON;
    while(nunchuk_pointer->z) f3d_nunchuk_read(nunchuk_pointer);
  }

  if(nunchuk_pointer->c) {
    button = C_BUTTON;
  }
  f3d_nunchuk_read(nunchuk_pointer);
  return button;
}

int is_over(square block) {
  if(block.ul.x < block.old_xl && block.lr.x < block.old_xl ||
     block.ul.x > block.old_xr && block.lr.x > block.old_xr)
    return LOST;
  if(block.ul.y <= FINISH_LINE + 9)
    return WIN;
}

square ask_play_again() {
  square block;
  while(1) {
    if(on_click() == C_BUTTON) {
      draw_background();
      block = create_start_block();
      break;
    }
  }
  return block;
}

square block_from_left(square old_block) {
  int side = (old_block.lr.y - old_block.ul.y) / 2;
  int upper_left = old_block.velocity+12;
  int lower_right = upper_left + (old_block.lr.x - old_block.ul.x) -1;
  int top = old_block.ul.y - (side*2) -1;
  int bottom = top + (side*2);

  return make_square(upper_left, top, lower_right, bottom, old_block.ul.x, old_block.lr.x, old_block.velocity, old_block.color);
}

square block_from_right(square old_block) {
  int side = (old_block.lr.y - old_block.ul.y) / 2;
  int upper_left = WIDTH - old_block.velocity - (old_block.lr.x - old_block.ul.x)-12;
  int lower_right = upper_left + (old_block.lr.x - old_block.ul.x)-1;
  int top = old_block.ul.y - (side*2) -1;
  int bottom = top + (side*2);

  return make_square(upper_left, top, lower_right, bottom, old_block.ul.x, old_block.lr.x, old_block.velocity, old_block.color);
}

void initialize() {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_timer2_init();
  delay(10);
  f3d_dac_init();
  delay(10);
  f3d_delay_init();
  delay(10);
  f3d_rtc_init();
  delay(10);
  f3d_systick_init();
}


square create_flag() {
  int flag_side = 5;
  int flag_block_size = 4;
  int flag_velocity = 1;
  int flag_left = 6;//WIDTH - (side*2 * block_size);
  int flag_right = 6*flag_side*flag_block_size;//WIDTH;
  int flag_top = 5;
  int flag_bottom = 2*(flag_side*2)-2;

  return make_square(flag_left, flag_top, flag_right, flag_bottom, 0, 128, flag_velocity, RED);
}

square create_start_block() {
  int side = 5;
  int block_size = 3;
  int velocity = 5;
  int upper_left = velocity+1;
  int lower_right = upper_left+ (side*2*block_size);
  int top = HEIGHT-(side*2);
  int bottom = HEIGHT-1;

  return make_square(upper_left, top, lower_right, bottom, 0, 128, velocity, RED);
}

square create_new_block(square block) {
  if(rand() % 2) {
    return block_from_left(block);
  } else {
    return block_from_right(block);
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
