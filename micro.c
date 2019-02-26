#include <stdio.h>
#include "pieces.h"
#include "chess.h"
#include "micro.h"

void validMovesTest(void) {
  B curBoard;
  B prevBoard;
  M moves;
  Move move;
  C colors;
  int testRow;
  int testCol;
  int sourceRow;
  int sourceCol;
  int originRow;
  int originCol;

  blankBoard(curBoard);
  //printBoard(curBoard);

  defaultBoard(curBoard);
  //copyBoard(prevBoard, curBoard);
  //printBoard(curBoard);

  originRow = 0;
  originCol = 4;
  sourceRow = 3;
  sourceCol = 4;
  testRow = 6;
  testCol = 1;

  movePiece(curBoard, originRow, originCol, sourceRow, sourceCol);
  copyBoard(prevBoard, curBoard);
  //printBoard(prevBoard);

  validMoves(prevBoard, moves, sourceRow, sourceCol);
  //printMoves(prevBoard, moves);

  movePiece(curBoard, sourceRow, sourceCol, testRow, testCol);
  //printBoard(curBoard);
  //printf("Valid Move: %d\n\n", isPossible(curBoard, prevBoard, 1));

  //printf("White Check Status: %d\n", checkStatus(curBoard, White));
  //printf("Black Check Status: %d\n\n", checkStatus(curBoard, Black));

  parseState(curBoard, prevBoard, White, colors, &move);
  checkStatus(curBoard, White);
  checkStatus(curBoard, Black);

  return;
}
