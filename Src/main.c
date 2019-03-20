// Includes
#include <stdio.h>
#include <string.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"

int testChessLibrary(void);
int testLedDrivers(void);
int testCastling(void);
int testCheck(void);
int inputTest(void);

// Functions
int main(int argc, char** argv) {
  //testLedDrivers();
  //testChessLibrary();
  //testCastling();
  //ledTest();
  //testCheck();
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
  Print("Valid Move: %d\n\n", parseState(curBoard, prevBoard, White, colors, &move));


  //Print("White Check Status: %d\n", gameStatus(curBoard, White));
  Print("Black Check Status: %d\n\n", gameStatus(curBoard, Black));

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
    Print("Castling failed.\n");
  }

  return 0;
}

int testCheck(void) {
  B curBoard;
  B prevBoard;
  M moves;
  C colors;
  Move move;
  int side = White;

  defaultBoard(prevBoard);
  prevBoard[3][6].side = 0;
  prevBoard[4][6].side = 0;
  movePiece(prevBoard, 0, 3, 2, 4, 1);
  copyBoard(curBoard, prevBoard);
  printBoard(curBoard);
  side = Black;

  possibleMoves(curBoard, moves, 7, 4);
  printMoves(curBoard, moves);
  validMoves(curBoard, moves, 7, 4);
  printMoves(curBoard, moves);
}

int inputTest(void) {
  char c[20];
  C colors;
  B curBoard;
  B prevBoard;
  M moves;
  Move move;
  Piece tempPiece;
  char side = White;
  int check = 0;
  int status = 0;

  defaultBoard(curBoard);
  defaultBoard(prevBoard);
  blankColors(colors);

  Print("\nWelcome to my half-baked chess simulator.\nType \"help\" for options!\n");
  Print("\n");
  printBoard(curBoard);

  while (1) {
    printTurn(side);
    status = gameStatus(curBoard, side);
    Print("Game Status: %d\n", status);
    Print(">");
    scanf("%s", c);
    if (strcmp(c, "exit") == 0) {
      Print("Exiting...\n");
      break;
    }
    else if (strcmp(c, "help") == 0) {
      Print("help: This menu.\n");
      Print("b2c2: Movement example.\n");
      Print("d4: Lift piece example (replaces in same spot afterwards).\n");
      Print("dela1: Delete piece example.\n");
      Print("pute5: Replace last deleted piece example.\n");
      Print("skip: Ends current turn.\n");
      Print("force: Ends current turn and accepts board state.\n");
      Print("reset: Put the board back to the last accepted state.\n");
      Print("newgame: Start a new game.\n");
      Print("exit: Leave the simulator.\n");
    }
    else if (strcmp(c, "reset") == 0) {
      Print("Reset board to last state.\n");
      copyBoard(curBoard, prevBoard);
    }
    else if (strcmp(c, "force") == 0) {
      Print("Forced the board to accept current state.\n");
      copyBoard(prevBoard, curBoard);
      check = 0;
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

      if ((status = gameStatus(curBoard, side)) > 1) {
        break;
      }
    }
    else if (strcmp(c, "skip") == 0) {
      Print("Skipping current turn.\n");
      check = 0;
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

      if ((status = gameStatus(curBoard, side)) > 1) {
        break;
      }
    }
    else if (strcmp(c, "newgame") == 0) {
      check = 0;
      status = 0;
      side = White;

      defaultBoard(curBoard);
      defaultBoard(prevBoard);
      blankColors(colors);

      Print("New Game Started.\n");
    }
    else if ((strlen(c) == 5) && (c[0] == 'd') && (c[1] == 'e') && (c[2] == 'l')) {
      // Delete a piece
      int x, y;
      int flag = 0;

      if ((x = charToCoord(c[3])) == -1) flag = 1;
      if ((y = charToCoord(c[4])) == -1) flag = 1;
      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else {
        tempPiece.type = curBoard[x][y].type;
        tempPiece.side = curBoard[x][y].side;
        tempPiece.promotion = curBoard[x][y].promotion;
        tempPiece.unmoved = 0;

        curBoard[x][y].type = 0;
        curBoard[x][y].side = 0;
        check = 1;
      }
    }
    else if ((strlen(c) == 5) && (c[0] == 'p') && (c[1] == 'u') && (c[2] == 't')) {
      // Delete a piece
      int x, y;
      int flag = 0;

      if ((x = charToCoord(c[3])) == -1) flag = 1;
      if ((y = charToCoord(c[4])) == -1) flag = 1;
      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else if (tempPiece.side == 0) {
        Print("Error: No piece to replace.\n");
      }
      else {
        curBoard[x][y].type = tempPiece.type;
        curBoard[x][y].side = tempPiece.side;
        curBoard[x][y].promotion = tempPiece.promotion;
        curBoard[x][y].unmoved = 0;
        tempPiece.side = 0;

        check = 1;
      }
    }
    else if (strlen(c) == 2) {
      // Lift a piece to view colors
      int x, y;
      int flag = 0;

      if ((x = charToCoord(c[0])) == -1) flag = 1;
      if ((y = charToCoord(c[1])) == -1) flag = 1;
      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else {
        // Lift Piece
        tempPiece.type = curBoard[x][y].type;
        tempPiece.side = curBoard[x][y].side;
        curBoard[x][y].type = 0;
        curBoard[x][y].side = 0;

        // Display Status
        check = parseState(curBoard, prevBoard, side, colors, &move);
        printColors(colors);

        // Replace Piece
        curBoard[x][y].type = tempPiece.type;
        curBoard[x][y].side = tempPiece.side;

        // Display Moves
        if (side == curBoard[x][y].side) {
          validMoves(curBoard, moves, y, x);
          //printMoves(curBoard, moves);
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
        Print("Error: Move could not be parsed.\n");
      }
      else {
        movePiece(curBoard, y, x, yy, xx, 0);
        check = 1;
      }
    }
    else {
      Print("Error: Could not parse command.\n");
    }

    if (check) {
      check = parseState(curBoard, prevBoard, side, colors, &move);
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

        Print("Move Accepted.\n");
        Print("Move: %c%c-%c%c\n", move.sourceCol+'A', move.sourceRow+'1', move.destCol+'A', move.destRow+'1');
        printColors(colors);
        printBoard(curBoard);
        if ((status = gameStatus(curBoard, side)) > 1) {
          break;
        }
      }
      else {
        Print("Board State Invalid.\n");
        printColors(colors);
        printBoard(curBoard);
        Print("Use \"reset\" to go back.\n");
      }
      check = 0;
    }
    else {
      Print("\n");
      printBoard(curBoard);
    }
  }

  switch (status) {
    case 0:
      Print("Game Quit.\n");
      break;
    case 1:
      Print("Game Quit While in Check.\n");
      break;
    case 2:
      Print("Game Over: Stalemate.\n");
      break;
    case 3:
      if (side == White) {
        Print("Game Over: Black Wins!\n");
      }
      else {
        Print("Game Over: White Wins!\n");
      }
      break;
    default:
      Print("Error: Invalid game state.\n");
      break;
  }

  return 0;
}
