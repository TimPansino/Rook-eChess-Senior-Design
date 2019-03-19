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
        if ((board[i][j].type == 'P') && (board[i][j].promotion)) {
          c = board[i][j].promotion;
        }
        else {
          c = board[i][j].type;
        }
      }
      else if (board[i][j].side == 2) {
        if ((board[i][j].type == 'P') && (board[i][j].promotion)) {
          c = board[i][j].promotion + 32;
        }
        else {
          c = board[i][j].type + 32;
        }
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
        case 3:
          c = 'O';
          break;
        case 2:
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
          printf(TRED " R " TRESET);
          break;
        case GREEN:
          printf(TGRN " G " TRESET);
          break;
        case BLUE:
          printf(TBLU " B " TRESET);
          break;
        case YELLOW:
          printf(TYEL " Y " TRESET);
          break;
        case MAGENTA:
          printf(TMAG " M " TRESET);
          break;
        case CYAN:
          printf(TCYN " C " TRESET);
          break;
        case WHITE:
          printf(" W ");
          break;
        case OFF:
          printf(" - ");
          break;
        default:
          printf(" ? ");
          break;
      }
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

char pawnPromote(void) {
  char c = 1;
  while (1) {
    if (c == 0) {
      printf("Error: Can only promote to Q, B, R, or N.\n");
    }
    printf("Promote Pawn: ");
    scanf(" %c", &c);

    switch(c) {
      case 'q':
      case 'r':
      case 'b':
      case 'n':
        return c + ('A' - 'a'); // Converts to uppercase
        break;

      case 'Q':
      case 'R':
      case 'B':
      case 'N':
        return c;
        break;

      default:
        c = 0;
        break;
    }
  }
}

void updateLeds(C curBoard, C prevBoard) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (curBoard[i][j] != prevBoard[i][j]) {
        printColor(curBoard, j, i);
        prevBoard[i][j] = curBoard[i][j];
        // Update LED with driver
      }
    }
  }
}
