#include "drivers.h"
#include "pieces.h"
#include "debug.h"

// Function Definitions
void blank_colors(C board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j] = OFF;
    }
  }
}

void update_leds(C cur_board, C prev_board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (cur_board[i][j] != prev_board[i][j]) {
        print_color(cur_board, j, i);
        prev_board[i][j] = cur_board[i][j];
        // Update LED with driver
      }
    }
  }
}
