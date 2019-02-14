// Includes
#include <stdio.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"
//#include "micro.h"

int testChessLibrary(void);
int testLedDrivers(void);

// Functions
int main(int argc, char** argv) {
  //testLedDrivers();
  testChessLibrary();

  return 0;
}

int testLedDrivers(void) {
  C colors;
  B curBoard;
  B prevBoard;
  M moves;

  int sourceRow;
  int sourceCol;

  blankBoard(curBoard);
  defaultBoard(curBoard);
  blankBoard(prevBoard);
  defaultBoard(prevBoard);

  sourceRow = 0;
  sourceCol = 4;

  initPiece(&curBoard[sourceCol][sourceRow], 0, 0, 0);
  printBoard(curBoard);

  blankColors(colors);
  colors[sourceCol][sourceRow] = YELLOW;
  printColors(colors);
  printColor(colors, sourceRow, sourceCol);

  return 0;
}

int testChessLibrary(void) {
  B curBoard;
  B prevBoard;
  M moves;
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

  // Test Chess Library
  originRow = 0;
  originCol = 4;
  sourceRow = 3;
  sourceCol = 2;
  testRow = 6;
  testCol = 2;
  movePiece(curBoard, 0, 2, 4, 0);

  movePiece(curBoard, originRow, originCol, sourceRow, sourceCol);
  copyBoard(prevBoard, curBoard);
  printBoard(prevBoard);
  prevBoard[sourceCol][sourceRow].unmoved = 1;

  validMoves(prevBoard, moves, sourceRow, sourceCol);
  printMoves(prevBoard, moves);

  movePiece(curBoard, sourceRow, sourceCol, testRow, testCol);
  printBoard(curBoard);
  printf("Valid Move: %d\n\n", isPossible(curBoard, prevBoard, White));


  //printf("White Check Status: %d\n", gameStatus(curBoard, White));
  printf("Black Check Status: %d\n\n", gameStatus(curBoard, Black));

  return 0;
}
