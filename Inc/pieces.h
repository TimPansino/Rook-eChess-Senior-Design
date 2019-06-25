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
#ifndef PIECES_H
#define PIECES_H

// Numeric Definitions
#define Knight 'N'
#define King 'K'
#define Queen 'Q'
#define Rook 'R'
#define Bishop 'B'
#define Pawn 'P'
#define White 1
#define Black 2

// Type Declarations
typedef struct Piece_S {
  char type;
  char side;
  char promotion;
  char unmoved;
} Piece;
typedef Piece B[8][8];
typedef char M[8][8];
typedef struct Move_S {
  int sourceRow;
  int sourceCol;
  int destRow;
  int destCol;
} Move;

#endif
