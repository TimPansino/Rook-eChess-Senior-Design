// Includes
#include <stdio.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"

// Functions
void printBoard(B board) {
  char c;

  printf(" ");
  if (PRINT_TYPE) {
    for (int i = 0; i < 8; i++) {
      printf("  %c", 'A' + i);
    }
  }
  else {
    for (int i = 0; i < 8; i++) {
      printf("  %d", i);
    }
  }
  printf("\n");

  for (int k = 0; k < 8; k++) {
    int j;

    switch (PRINT_TYPE) {
      case 0: 
        j = k;
        break;
      case 1:
        j = 7 - k;
        break;
    }

    printf("%d:", j + PRINT_TYPE);
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

void printMoves(B board, M moves) {
  char c;

  printf(" ");
  if (PRINT_TYPE) {
    for (int i = 0; i < 8; i++) {
      printf("  %c", 'A' + i);
    }
  }
  else {
    for (int i = 0; i < 8; i++) {
      printf("  %d", i);
    }
  }
  printf("\n");

  for (int k = 0; k < 8; k++) {
    int j;

    switch (PRINT_TYPE) {
      case 0:
        j = k;
        break;
      case 1:
        j = 7 - k;
        break;
    }

    printf("%d:", j + PRINT_TYPE);
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

void printColors(C board) {
  char c;

  printf(" ");
  if (PRINT_TYPE) {
    for (int i = 0; i < 8; i++) {
      printf("  %c", 'A' + i);
    }
  }
  else {
    for (int i = 0; i < 8; i++) {
      printf("  %d", i);
    }
  }
  printf("\n");

  for (int k = 0; k < 8; k++) {
    int j;

    switch (PRINT_TYPE) {
      case 0:
        j = k;
        break;
      case 1:
        j = 7 - k;
        break;
    }

    printf("%d:", j + PRINT_TYPE);
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

void printColor(C c, int x, int y) {
  char red = (c[y][x] & RED) >> R_SHIFT;
  char green = (c[y][x] & GREEN) >> G_SHIFT;
  char blue = (c[y][x] & BLUE) >> B_SHIFT;

  printf("Address (%d, %d): %d%d%d\n", x, y, red, green, blue);
}

void printTurn(int side) {
  switch (side) {
    case White:
      printf("Current Turn: White\n");
      break;
    case Black:
      printf("Current Turn: Black\n");
      break;
    default:
      printf("Current Turn: INVALID\n");
      break;
  }
}

int charToCoord(char c) {
  if (c >= 'A' && c <= 'H') {
    return c - 'A';
  }
  else if (c >= 'a' && c <= 'h') {
    return c - 'a';
  }
  else if (c >= '1' && c <= '8') {
    return c - '1';
  }
  else {
    return -1;
  }
}
