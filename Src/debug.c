// Includes
#include <stdio.h>
#include <stdarg.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"

// Functions
void Print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  //va_start(args, argc);
  vprintf(format, args);
  va_end(args);
}

void printBoard(B board) {
  char c;

  Print(" ");
  if (PRINT_TYPE) {
    for (int i = 0; i < 8; i++) {
      Print("  %c", 'A' + i);
    }
  }
  else {
    for (int i = 0; i < 8; i++) {
      Print("  %d", i);
    }
  }
  Print("\n");

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

    Print("%d:", j + PRINT_TYPE);
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
      Print(" %c ", c);
    }
    Print("\n");
  }
  Print("\n");
  return;
}

void printMoves(B board, M moves) {
  char c;

  Print(" ");
  if (PRINT_TYPE) {
    for (int i = 0; i < 8; i++) {
      Print("  %c", 'A' + i);
    }
  }
  else {
    for (int i = 0; i < 8; i++) {
      Print("  %d", i);
    }
  }
  Print("\n");

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

    Print("%d:", j + PRINT_TYPE);
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
      Print(" %c ", c);
    }
    Print("\n");
  }
  Print("\n");
  return;
}

void printColors(C board) {
  Print(" ");
  if (PRINT_TYPE) {
    for (int i = 0; i < 8; i++) {
      Print("  %c", 'A' + i);
    }
  }
  else {
    for (int i = 0; i < 8; i++) {
      Print("  %d", i);
    }
  }
  Print("\n");

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

    Print("%d:", j + PRINT_TYPE);
    for (int i = 0; i < 8; i++) {
      switch(board[i][j]) {
        case RED:
          Print(TRED " R " TRESET);
          break;
        case GREEN:
          Print(TGRN " G " TRESET);
          break;
        case BLUE:
          Print(TBLU " B " TRESET);
          break;
        case YELLOW:
          Print(TYEL " Y " TRESET);
          break;
        case MAGENTA:
          Print(TMAG " M " TRESET);
          break;
        case CYAN:
          Print(TCYN " C " TRESET);
          break;
        case WHITE:
          Print(" W ");
          break;
        case OFF:
          Print(" - ");
          break;
        default:
          Print(" ? ");
          break;
      }
    }
    Print("\n");
  }
  Print("\n");
  return;
}

void printColor(C c, int x, int y) {
  char red = (c[y][x] & RED) >> R_SHIFT;
  char green = (c[y][x] & GREEN) >> G_SHIFT;
  char blue = (c[y][x] & BLUE) >> B_SHIFT;

  Print("Address (%d, %d): %d%d%d\n", x, y, red, green, blue);
}

void printTurn(int side) {
  switch (side) {
    case White:
      Print("Current Turn: White\n");
      break;
    case Black:
      Print("Current Turn: Black\n");
      break;
    default:
      Print("Current Turn: INVALID\n");
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
      Print("Error: Can only promote to Q, B, R, or N.\n");
    }
    Print("Promote Pawn: ");
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
