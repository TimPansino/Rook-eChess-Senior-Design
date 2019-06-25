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
#ifndef DRIVERS_H
#define DRIVERS_H
#include <stdarg.h>
#include "pieces.h"

// Numeric Definitions
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_BLUE    4
#define COLOR_MAGENTA COLOR_RED | COLOR_BLUE
#define COLOR_CYAN    COLOR_GREEN | COLOR_BLUE
#define COLOR_YELLOW  COLOR_RED | COLOR_GREEN
#define COLOR_WHITE   COLOR_RED | COLOR_GREEN | COLOR_BLUE
#define COLOR_BLACK   0
#define COLOR_OFF     COLOR_BLACK
#define COLOR_BLANK   COLOR_BLACK

// Aliases
#define COLOR_PURPLE  COLOR_MAGENTA
#define COLOR_GOLD    COLOR_YELLOW
#define COLOR_ON      COLOR_WHITE

// Shifting Amounts
#define R_SHIFT COLOR_RED / 2
#define G_SHIFT COLOR_GREEN / 2
#define B_SHIFT COLOR_BLUE / 2

// Color Choices
#define COLOR_ERROR     COLOR_RED
#define COLOR_POSSIBLE  COLOR_BLUE
#define COLOR_CAPTURE   COLOR_GREEN
#define COLOR_SPECIAL   COLOR_PURPLE
#define COLOR_ORIGIN    COLOR_WHITE
#define COLOR_ACCEPTED  COLOR_GREEN

// Terminal Commands
#define CLEAR_TERMINAL "\033[2J\033[H"
#define NEWLINE_STR "\r\n"
#define BACKSPACE_STR "\b\033[K"

#define CARE 0x0D     // ASCII return 
#define LF 0x0A     // ASCII new line 

// LCD INSTRUCTION CHARACTERS
#define LCDON 0x0C  	// LCD initialization command
#define LCDCLR 0x01 	// LCD clear display command
#define TWOLINE 0x38    // LCD 2-line enable command
#define CURMOV 0xFE 	// LCD cursor move instruction
#define LINE1 0x80  	// LCD line 1 cursor position
#define LINE2 0xC0  	// LCD line 2 cursor position
#define MODE 0x06

// SPI and UART TIMEOUT
#define TIMEOUT 10

// RFID Defines
#define UID_SIZE 10
#define SCANS_NUMBER 6

// Type Definitions
typedef char Color;
typedef Color C[8][8];
typedef unsigned char UID[UID_SIZE];

// RFID Addresses
extern int rfidReaderAddress;
extern int rfidAntennaAddress;

// UID Match Declarations
extern UID BAD_UID;
extern UID EMPTY_UID;
extern UID WHITE_KING;
extern UID WHITE_QUEEN;
extern UID WHITE_KNIGHT_1;
extern UID WHITE_BISHOP_1;
extern UID WHITE_ROOK_1;
extern UID WHITE_KNIGHT_2;
extern UID WHITE_BISHOP_2;
extern UID WHITE_ROOK_2;
extern UID WHITE_PAWN_1;
extern UID WHITE_PAWN_2;
extern UID WHITE_PAWN_3;
extern UID WHITE_PAWN_4;
extern UID WHITE_PAWN_5;
extern UID WHITE_PAWN_6;
extern UID WHITE_PAWN_7;
extern UID WHITE_PAWN_8;
extern UID BLACK_KING;
extern UID BLACK_QUEEN;
extern UID BLACK_KNIGHT_1;
extern UID BLACK_BISHOP_1;
extern UID BLACK_ROOK_1;
extern UID BLACK_KNIGHT_2;
extern UID BLACK_BISHOP_2;
extern UID BLACK_ROOK_2;
extern UID BLACK_PAWN_1;
extern UID BLACK_PAWN_2;
extern UID BLACK_PAWN_3;
extern UID BLACK_PAWN_4;
extern UID BLACK_PAWN_5;
extern UID BLACK_PAWN_6;
extern UID BLACK_PAWN_7;
extern UID BLACK_PAWN_8;

// Function Declarations
int diffUID(UID uidA, UID uidB);
void blankColors(C board);
void updateColors(C color);
void updateLED(int ledAddress, char color);
void updateSquare(Piece * P, UID id);
void updateBoard(B curBoard);
void antennaSelect(void);
void printUIDArray(UID id, int size);
char pawnPromote(void);

void Print(const char* format, ...);
void Scan(char* s);

#endif
