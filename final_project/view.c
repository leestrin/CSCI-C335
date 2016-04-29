/* veiw.c ---
 *
 * Filename: view.c
 * Description: Main logic of lcd
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
#include "view.h"


void init() {
  f3d_lcd_init();
}

void draw_background() {
  f3d_lcd_fillScreen(WHITE);
  f3d_lcd_drawString((WIDTH/2)-23, 7, "STACK IT", BLUE, WHITE);
  f3d_lcd_drawString((WIDTH/2)-24, HEIGHT/2 - 2, "PRESS \"Z\"", BLACK, WHITE);
  draw_rect(0, FINISH_LINE, WIDTH, 2, BLUE);
}

void draw_win_message() {
  draw_rect(0, HEIGHT/2-25, 128, 50, BLUE);
  f3d_lcd_drawString((WIDTH/2)-24, HEIGHT/2-20, "YOU WIN!", WHITE, BLUE);
  f3d_lcd_drawString((WIDTH/2)-23, HEIGHT/2, "Press \"C\"", WHITE, BLUE);
  f3d_lcd_drawString((WIDTH/2)-39, HEIGHT/2+10, "to play again.", WHITE, BLUE);
}

void draw_lost_message() {
  draw_rect(0, HEIGHT/2-25, 128, 50, RED);
  f3d_lcd_drawString((WIDTH/2)-24, HEIGHT/2-20, "YOU SUCK!", WHITE, RED);
  f3d_lcd_drawString((WIDTH/2)-23, HEIGHT/2, "Press \"C\"", WHITE, RED);
  f3d_lcd_drawString((WIDTH/2)-39, HEIGHT/2+10, "to play again.", WHITE, RED);
}

void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t depth, uint16_t color) {
  int i;
  uint16_t buf[width*depth];
  f3d_lcd_setAddrWindow(x, y, x+width-1, y+depth-1, MADCTLGRAPHICS);
  for (i = 0; i < width*depth; i++) {
    buf[i] = color;
  }
  f3d_lcd_pushColor(buf,width*depth);
}

void draw_square(square s) {
  int x_pos = s.ul.x;
  int y_pos = s.ul.y;
  int side = s.lr.y - s.ul.y;
  uint16_t color = s.color;
  draw_rect(x_pos, y_pos, side, side, color);
}

square move_square(square block) {
  int depth = block.lr.y - block.ul.y;
  int new_left = block.ul.x;
  int new_right = block.lr.x;

  if(new_right > 128 - abs(block.velocity) || new_left < 0 + abs(block.velocity))
    block.velocity *= -1;

  int velocity = block.velocity;

  new_left = block.ul.x + velocity;
  new_right = block.lr.x + velocity;

  if(velocity > 0) {
    draw_rect(block.lr.x, block.ul.y, velocity, depth, block.color);
    draw_rect(block.ul.x, block.ul.y, velocity, depth, WHITE);
  } else {
    velocity = abs(velocity);
    draw_rect(new_left, block.ul.y, velocity, depth, block.color);
    draw_rect(new_right, block.ul.y, velocity, depth, WHITE);
  }

  return make_square(new_left,
                     block.ul.y,
                     new_right,
                     block.lr.y,
                     block.old_xl,
                     block.old_xr,
                     block.velocity,
                     block.color);
}

square make_square(int x1, int y1, int x2, int y2, int old_xl, int old_xr, int velocity, uint16_t color) {
  point upper_left = { .x = x1, .y = y1};
  point lower_right = { .x = x2, .y = y2};
  square s = { .ul = upper_left,
               .lr = lower_right,
               .old_xl = old_xl,
               .old_xr = old_xr,
               .velocity = velocity,
               .color = color };
  return s;
}

/* void draw_square_buddies(square_buddies bunch_of_squares) { */
/*   square* blocks = bunch_of_squares.blocks; */
/*   int i; */
/*   int length = sizeof(blocks)/sizeof(square); */

/*   for(i = 0; i < length; i++) { */
/*     draw_square(blocks[i]); */
/*   } */
/* } */


/* square_buddies make_square_buddies(square block, int cunt) { */
/*   int i; */
/*   for(i = 0; i < cunt; i++) { */
/*     make_square(block.ul.x * i, block.ul.y, block.lr.x * i, block.lr.y, color) */
/*   } */
/*   return square_buddies; */
/*   /\* square result[cunt]; *\/ */
/*   /\* int upper_left_y = block.ul.y; *\/ */
/*   /\* int lower_right_y = block.lr.y; *\/ */
/*   /\* int color = block.color; *\/ */
/*   /\* int side = block.lr.x - block.ul.x; *\/ */
/*   /\* int i; *\/ */

/*   /\* for(i = 0; i < cunt; i++) { *\/ */
/*   /\*   int upper_left_x = block.ul.x + (side * i) + 1; *\/ */
/*   /\*   int lower_right_x = block.lr.x + (side * i) + 1; *\/ */
/*   /\*   square new_block = make_square(upper_left_x, upper_left_y, lower_right_x, lower_right_y, color); *\/ */
/*   /\*   result[i] = new_block; *\/ */
/*   /\* } *\/ */

/*   /\* square_buddies buddies = { .blocks = result }; *\/ */

/*   /\* return buddies; *\/ */
/* } */
