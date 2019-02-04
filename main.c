// Includes
#include <stdio.h>
#include "pieces.h"
#include "chess.h"
#include "debug.h"

// Functions
int main(int argc, char** argv) {
  B cur_board;
  M moves;

  // TEMP
  int test_row;
  int test_col;
  int source_row;
  int source_col;

  blank_board(cur_board);
  //print_board(cur_board);

  default_board(cur_board);
  //print_board(cur_board);

  source_row = 0;
  source_col = 1;
  test_row = 0;
  test_col = 1;

  move_piece(cur_board, source_row, source_col, test_row, test_col);
  print_board(cur_board);

  valid_moves(cur_board, moves, test_row, test_col);
  print_moves(cur_board, moves);

  printf("White Check Status: %d\n\n", check_status(cur_board, White));
  printf("Black Check Status: %d\n\n", check_status(cur_board, Black));
}
