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
#ifndef DEBUG_H
#define DEBUG_H
// Defines
#define PRINT_TYPE 1
// 0: Print C Array Indexes
// 1: Print Chess Board Standard Indexes
#define DEBUG 1

// Terminal Colors
#define TRED   "\x1B[31m"
#define TGRN   "\x1B[32m"
#define TYEL   "\x1B[33m"
#define TBLU   "\x1B[34m"
#define TMAG   "\x1B[35m"
#define TCYN   "\x1B[36m"
#define TWHT   "\x1B[37m"
#define TRESET "\x1B[0m"

// Function Definitions
void printBoard(B board);
void printMoves(B board, M moves);
void printColors(C board);
void printColor(C c, int x, int y);
void printTurn(int side);

#endif
