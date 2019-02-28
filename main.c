// Includes
#include <stdio.h>
#include <string.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"
#include "micro.h"

int testChessLibrary(void);
int testLedDrivers(void);
int testCastling(void);
int inputTest(void);

// Functions
int main(int argc, char** argv) {
  //testLedDrivers();
  //testChessLibrary();
  //testCastling();
  //ledTest();
  inputTest();

  return 0;
}

int testLedDrivers(void) {
  C colors;
  B curBoard;
  B prevBoard;
  //M moves;

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

  // Test Chess Library
  originRow = 0;
  originCol = 4;
  sourceRow = 3;
  sourceCol = 2;
  testRow = 6;
  testCol = 2;
  movePiece(curBoard, 0, 2, 4, 0, 1);

  movePiece(curBoard, originRow, originCol, sourceRow, sourceCol, 1);
  copyBoard(prevBoard, curBoard);
  printBoard(prevBoard);
  prevBoard[sourceCol][sourceRow].unmoved = 1;

  validMoves(prevBoard, moves, sourceRow, sourceCol);
  printMoves(prevBoard, moves);

  movePiece(curBoard, sourceRow, sourceCol, testRow, testCol, 1);
  printBoard(curBoard);
  printf("Valid Move: %d\n\n", parseState(curBoard, prevBoard, White, colors, &move));


  //printf("White Check Status: %d\n", gameStatus(curBoard, White));
  printf("Black Check Status: %d\n\n", gameStatus(curBoard, Black));

  return 0;
}

int testCastling(void) {
  B curBoard;
  B prevBoard;
  M moves;
  C colors;
  Move move;
  int side = 1;

  defaultBoard(curBoard);
  blankColors(colors);

  initPiece(&curBoard[1][0], 0, 0, 0);
  initPiece(&curBoard[2][0], 0, 0, 0);
  initPiece(&curBoard[3][0], 0, 0, 0);
  initPiece(&curBoard[5][0], 0, 0, 0);
  initPiece(&curBoard[6][0], 0, 0, 0);

  copyBoard(prevBoard, curBoard);

  printBoard(curBoard);

  curBoard[4][0].side = 0;
  parseState(prevBoard, curBoard, side, colors, &move);
  printColors(colors);
  curBoard[4][0].side = 1;

  validMoves(curBoard, moves, 0, 4);
  printMoves(curBoard, moves);

  if (moves[5][0] != 0) {
    movePiece(curBoard, 0, 4, 0, 6, 1);
    printBoard(curBoard);
    parseState(curBoard, prevBoard, side, colors, &move);
    printColors(colors);
  }
  else {
    printf("Castling failed.\n");
  }

  return 0;
}

int inputTest(void) {
  char c[20];
  C colors;
  B curBoard;
  B prevBoard;
  M moves;
  Piece tempPiece;
  Move curMove;
  char side = White;
  int check = 0;
  int status = 0;

  defaultBoard(curBoard);
  defaultBoard(prevBoard);
  blankColors(colors);

  printf("\nWelcome to my half-baked chess simulator.\nType \"help\" for options!\n");
  printf("\n");
  printBoard(curBoard);

  while (1) {
    printTurn(side);
    status = gameStatus(curBoard, side);
    printf("Game Status: %d\n", status);
    printf(">");
    scanf("%s", c);
    if (strcmp(c, "exit") == 0) {
      printf("Exiting...\n");
      break;
    }
    else if (strcmp(c, "help") == 0) {
      printf("help: This menu.\n");
      printf("b2c2: Movement example. \n");
      printf("d4: Lift piece example (replaces in same spot afterwards). \n");
      printf("dela1: Delete piece example. \n");
      printf("skip: Ends current turn.\n");
      printf("force: Ends current turn and accepts board state.\n");
      printf("reset: Put the board back to the last accepted state.\n");
      printf("newgame: Start a new game.\n");
      printf("exit: Leave the simulator.\n");

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
    else if (strcmp(c, "newgame") == 0) {
      check = 0;
      status = 0;
      side = White;

      defaultBoard(curBoard);
      defaultBoard(prevBoard);
      blankColors(colors);

      printf("New Game Started.\n");
    }
    else if ((strlen(c) == 5) && (c[0] == 'd') && (c[1] == 'e') && (c[2] == 'l')) {
      // Delete a piece
      int x, y;
      int flag = 0;

      if ((x = charToCoord(c[3])) == -1) flag = 1;
      if ((y = charToCoord(c[4])) == -1) flag = 1;
      if (flag) {
        printf("Error: Move could not be parsed.\n");
      }
      else {
        curBoard[x][y].type = 0;
        curBoard[x][y].side = 0;

        // Display Status
        check = parseState(curBoard, prevBoard, side, colors, &curMove);
        printf("Parse Ret: %d\n", check);
        printColors(colors);

        // Display Moves
        if (side == curBoard[x][y].side) {
          validMoves(curBoard, moves, y, x);
          printMoves(curBoard, moves);
        }
        check = 0;
      }
    }
    else if (strlen(c) == 2) {
      // Lift a piece to view colors
      int x, y;
      int flag = 0;

      if ((x = charToCoord(c[0])) == -1) flag = 1;
      if ((y = charToCoord(c[1])) == -1) flag = 1;
      if (flag) {
        printf("Error: Move could not be parsed.\n");
      }
      else {
        // Lift Piece
        tempPiece.type = curBoard[x][y].type;
        tempPiece.side = curBoard[x][y].side;
        curBoard[x][y].type = 0;
        curBoard[x][y].side = 0;

        // Display Status
        check = parseState(curBoard, prevBoard, side, colors, &curMove);
        printf("Parse Ret: %d\n", check);
        printColors(colors);

        // Replace Piece
        curBoard[x][y].type = tempPiece.type;
        curBoard[x][y].side = tempPiece.side;

        // Display Moves
        if (side == curBoard[x][y].side) {
          validMoves(curBoard, moves, y, x);
          printMoves(curBoard, moves);
        }
        check = 0;
      }
    }
    else if (strlen(c) == 4) {
      // Move a piece
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
        movePiece(curBoard, y, x, yy, xx, 0);
        check = 1;
      }
    }
    else {
      printf("Error: Could not parse command.\n");
    }

    if (check) {
      check = parseState(curBoard, prevBoard, side, colors, &curMove);
      printf("Parse Ret: %d\n", check);
      if (check == 1) {
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
        if ((status = gameStatus(curBoard, side)) > 1) {
          break;
        }
      }
      else {
        printf("Board State Invalid.\n");
        printBoard(curBoard);
        printf("Use \"reset\" to go back.\n");
      }
      check = 0;
    }
    else {
      printf("\n");
      printBoard(curBoard);
    }
  }

  switch (status) {
    case 0:
      printf("Error: Somehow exited prematurely.\n");
      break;
    case 1:
      printf("Error: Exited when only in check.\n");
      break;
    case 2:
      printf("Game Over: Stalemate.\n");
      break;
    case 3:
      if (side == White) {
        printf("Game Over: Black Wins!\n");
      }
      else {
        printf("Game Over: White Wins!\n");
      }
      break;
    default:
      printf("Error: Invalide game state.\n");
      break;
  }

  return 0;
}
