#include <stdio.h>
#include <stdarg.h>
#include "pieces.h"
#include "chess.h"
#include "micro.h"

void ledTest(void) {
  B curBoard;
  B prevBoard;
  Move move;
  C colors;
  int state;
  int check;

  // Default Setup
  defaultBoard(prevBoard);

  // Delete Pawn
  prevBoard[3][1].side = 0;
  prevBoard[3][1].type = 0;
  copyBoard(curBoard, prevBoard);

  // Move Queen Out
  movePiece(curBoard, 0, 3, 3, 3, 1);

  // Test Board State
  state = parseState(curBoard, prevBoard, White, colors, &move);
  check = gameStatus(curBoard, Black);

  //Print("State: %d\n", state);
  //Print("Check: %d\n", check);

  return;
}

void Print(const char* format, ...) {
  va_list args;
  char s[1024];

  va_start(args, format);
  //va_start(args, argc);
  vsprintf(s, format, args);
  transmitString(s);
  va_end(args);
}