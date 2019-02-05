// Includes
#include <stdio.h>
#include "pieces.h"
#include "chess.h"
#include "debug.h"
//#include "micro.h"

// Functions
int main(int argc, char** argv) {
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

  origin_row = 1;
  origin_col = 4;
  source_row = 3;
  source_col = 4;
  test_row = 6;
  test_col = 4;

  move_piece(cur_board, origin_row, origin_col, source_row, source_col);
  copy_board(prev_board, cur_board);
  print_board(prev_board);
  prev_board[source_col][source_row].unmoved = 1;

  valid_moves(prev_board, moves, source_row, source_col);
  print_moves(prev_board, moves);

  move_piece(cur_board, source_row, source_col, test_row, test_col);
  print_board(cur_board);
  printf("Valid Move: %d\n\n", is_possible(cur_board, prev_board, White));


  printf("White Check Status: %d\n", check_status(cur_board, White));
  printf("Black Check Status: %d\n\n", check_status(cur_board, Black));

  return 0;
}
