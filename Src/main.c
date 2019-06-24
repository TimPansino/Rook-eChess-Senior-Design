/*   MIT License
*
*    Copyright (c) 2019 Timothy Pansino, Adam Behnke, Zachary Neumann, Mitchell Keeney
*
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/

// Defines
#define LOCAL_ONLY 1

// Includes
#include <stdio.h>
#include <string.h>

#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"
#include "ai.h"
#include "ui.h"
#include "defs.h"
#include "data.h"
#include "protos.h"

// Function Declarations
int testChessLibrary(void);
int testLedDrivers(void);
int testCastling(void);
int testCheck(void);
int testAI(void);
void testUI(void);
void Print(const char* format, ...);
void Scan(char* s);


// Function Definitions
int main(int argc, char** argv) {
  Print("Testing UI...\n");
  testUI();

  return 0;
}

void testUI(void) {
  Print("%c", pawnPromote());

  return;
}

int testAI(void) {
  char s[100];
  s[0] = '\0';

  aiInit(LIGHT);

  while (1) {
    s[0] = '\0';
    aiMakeMove(s);
    if (strlen(s) > 0) {
      Print("AI Move: %s\n", s);
    }

    Print(">");
    Scan(s);

    if (strcmp("exit", s) == 0) {
      break;
    }
    else {
      aiParseCommand(s);
    }
  }

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

void Print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

void Scan(char* s) {
  scanf("%s", s);
}
