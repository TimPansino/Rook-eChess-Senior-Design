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
  movePiece(curBoard, 0, 3, 3, 3);

  // Test Board State
  state = parseState(curBoard, prevBoard, White, colors, &move);
  check = gameStatus(curBoard, Black);

  //Print("State: %d\n", state);
  //Print("Check: %d\n", check);

  return;
}
