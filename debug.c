// Includes
#include <stdio.h>
#include "pieces.h"
#include "chess.h"
#include "debug.h"

// Functions
void print_board(B board) {
  char c;

  printf("   0  1  2  3  4  5  6  7\n");
  for (int j = 0; j < 8; j++) {
    printf("%d:", j);
    for (int i = 0; i < 8; i++) {
      if (board[i][j].side == 1) {
        c = board[i][j].type;
      }
      else if (board[i][j].side == 2) {
        c = board[i][j].type + 32;
      }
      else {
        c = '-';
      }
      printf(" %c ", c);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void print_moves(B board, M moves) {
  char c;

  printf("   0  1  2  3  4  5  6  7\n");
  for (int j = 0; j < 8; j++) {
    printf("%d:", j);
    for (int i = 0; i < 8; i++) {
      switch(moves[i][j]) {
        case -1:
          c = board[i][j].type;
          break;
        case 1:
          c = 'O';
          break;
        case 2:
        case 3:
          c = board[i][j].type + 32;
          break;
        default:
          c = '-';
          break;
      }
      printf(" %c ", c);
    }
    printf("\n");
  }
  printf("\n");
  return;
}
