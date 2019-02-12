// Includes
#include <stdio.h>
#include "pieces.h"
#include "drivers.h"
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

void print_colors(C board) {
  char c;

  printf("   0  1  2  3  4  5  6  7\n");
  for (int j = 0; j < 8; j++) {
    printf("%d:", j);
    for (int i = 0; i < 8; i++) {
      switch(board[i][j]) {
        case RED:
          c = 'R';
          break;
        case GREEN:
          c = 'G';
          break;
        case BLUE:
          c = 'B';
          break;
        case YELLOW:
          c = 'Y';
          break;
        case MAGENTA:
          c = 'M';
          break;
        case CYAN:
          c = 'C';
          break;
        case WHITE:
          c = 'W';
          break;
        case OFF:
          c = '-';
          break;
        default:
          c = '?';
          break;
      }
      printf(" %c ", c);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void print_color(C c, int x, int y) {
  char red = (c[y][x] & RED) >> R_SHIFT;
  char green = (c[y][x] & GREEN) >> G_SHIFT;
  char blue = (c[y][x] & BLUE) >> B_SHIFT;

  printf("Address (%d, %d): %d%d%d\n", x, y, red, green, blue);
}
