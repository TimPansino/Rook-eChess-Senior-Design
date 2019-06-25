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
#ifndef CHESS_H
#define CHESS_H
#include "drivers.h"

// Function Declarations
int commandLine(void);
void initPiece(Piece* p, char type, char side, char promotion);
void blankBoard(B board);
void blankColors(C board);
void defaultBoard(B board);
void blankMoves(M board);
void movePiece(B board, int row1, int col1, int row2, int col2);
void makeMove(B board, Move m);
int checkStatus(B board, char side);
int possibleMoves(B board, M moves, int row, int col);
int validMoves(B board, M moves, int row, int col);
int isPossible(B newBoard, B oldBoard, int side);
int diffBoards(B newBoard, B oldBoard, M diff);
void copyBoard(B newBoard, B oldBoard);
int canMove(B board, char side);
int gameStatus(B board, char side);
void initMove(Move* move);
int parseState(B newBoard, B oldBoard, int side, C colors, Move* move);
int charToCoord(char c);
char strToMove(char* s, Move* move);
void moveToStr(Move* move, char *s, int promote);
char switchSide(char curSide);
char verifyMove(B curBoard, Move* move);

#endif
