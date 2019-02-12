// Includes
#include <stdio.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"
//#include "micro.h"

int test_chess_library(void);
int test_led_drivers(void);

// Functions
int main(int argc, char** argv) {
  //test_led_drivers();
  test_chess_library();

  return 0;
}

int test_led_drivers(void) {
  C colors;
  B cur_board;
  B prev_board;
  M moves;

  int source_row;
  int source_col;

  blank_board(cur_board);
  default_board(cur_board);
  blank_board(prev_board);
  default_board(prev_board);

  source_row = 0;
  source_col = 4;

  init_piece(&cur_board[source_col][source_row], 0, 0, 0);
  print_board(cur_board);

  blank_colors(colors);
  colors[source_col][source_row] = YELLOW;
  print_colors(colors);
  print_color(colors, source_row, source_col);

  return 0;
}

int test_chess_library(void) {
  B cur_board;
  B prev_board;
  M moves;
  int test_row;
  int test_col;
  int source_row;
  int source_col;
  int origin_row;
  int origin_col;

  blank_board(cur_board);
  //print_board(cur_board);

  default_board(cur_board);
  //copy_board(prev_board, cur_board);
  //print_board(cur_board);

  // Test Chess Library
  origin_row = 0;
  origin_col = 4;
  source_row = 3;
  source_col = 2;
  test_row = 6;
  test_col = 2;
  move_piece(cur_board, 0, 2, 4, 0);

  move_piece(cur_board, origin_row, origin_col, source_row, source_col);
  copy_board(prev_board, cur_board);
  print_board(prev_board);
  prev_board[source_col][source_row].unmoved = 1;

  valid_moves(prev_board, moves, source_row, source_col);
  print_moves(prev_board, moves);

  move_piece(cur_board, source_row, source_col, test_row, test_col);
  print_board(cur_board);
  printf("Valid Move: %d\n\n", is_possible(cur_board, prev_board, White));


  //printf("White Check Status: %d\n", game_status(cur_board, White));
  printf("Black Check Status: %d\n\n", game_status(cur_board, Black));

  return 0;
}
