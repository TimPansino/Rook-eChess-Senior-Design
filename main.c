// Includes
#include <stdio.h>
#include <string.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"
//#include "micro.h"

int testChessLibrary(void);
int testLedDrivers(void);
int inputTest(void);

// Functions
int main(int argc, char** argv) {
  //testLedDrivers();
  //testChessLibrary();
  inputTest();

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

int inputTest(void) {
  char c[20];
  C colors;
  B curBoard;
  B prevBoard;
  M moves;
  char side = White;
  int check = 0;

  defaultBoard(curBoard);
  defaultBoard(prevBoard);

  printf("\nWelcome to my half-baked chess simulator.\nType \"help\" for options!\n");
  printf("\n");
  printBoard(curBoard);

  while (1) {
    printTurn(side);
    printf(">");
    scanf("%s", c);
    if (strcmp(c, "exit") == 0) {
      printf("Exiting...\n");
      break;
    }
    else if (strcmp(c, "help") == 0) {
      printf("help: This menu.\n");
      printf("exit: Leave the simulator.\n");
      printf("b2c2: Example move. \n");
    }
    else if (strcmp(c, "reset") == 0) {
      printf("Reset board to last state.\n");
      copyBoard(curBoard, prevBoard);
    }
    else if (strcmp(c, "force") == 0) {
      printf("Forced the board to accept current state.\n");
      copyBoard(prevBoard, curBoard);
      switch(side) {
        case White: {
          side = Black;
          break;
        }
        case Black: {
          side = White;
          break;
        }
      }
    }
    else if (strcmp(c, "skip") == 0) {
      printf("Skipping current turn.\n");
      switch(side) {
        case White: {
          side = Black;
          break;
        }
        case Black: {
          side = White;
          break;
        }
      }
    }
    else if (strlen(c) == 4) {
      int x, y, xx, yy;
      int flag = 0;
      if ((x = charToCoord(c[0])) == -1) flag = 1;
      if ((y = charToCoord(c[1])) == -1) flag = 1;
      if ((xx = charToCoord(c[2])) == -1) flag = 1;
      if ((yy = charToCoord(c[3])) == -1) flag = 1;

      if (flag) {
        printf("Error: Move could not be parsed.\n");
      }
      else {
        movePiece(curBoard, y, x, yy, xx);
        check = 1;
      }
    }
    else if (strlen(c) == 9) {
      printf("Unhandled delete.\n");
    }
    else {
      printf("Error: Could not parse command.\n");
    }

    if (check) {
      if (isPossible(curBoard, prevBoard, side)) {
        check = 0;
        copyBoard(prevBoard, curBoard);
        switch(side) {
          case White:
            side = Black;
            break;
          case Black:
            side = White;
            break;
        }

        printf("Move Accepted.\n");
        printBoard(curBoard);
      }
      else {
        printf("Board State Invalid.\n");
        printBoard(curBoard);
        printf("Use \"reset\" to go back.\n");
      }
    }
    else {
      printf("\n");
      printBoard(curBoard);
    }
  }
  return 0;
}
