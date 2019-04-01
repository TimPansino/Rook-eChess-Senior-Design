#ifndef DRIVERS_H
#define DRIVERS_H
#include <stdarg.h>
#include "pieces.h"

// Numeric Definitions
#define RED     4
#define GREEN   2
#define BLUE    1
#define MAGENTA RED|BLUE
#define CYAN    GREEN|BLUE
#define YELLOW  RED|GREEN
#define WHITE   RED|GREEN|BLUE
#define BLACK   0
#define OFF     BLACK

// Aliases
#define PURPLE  MAGENTA
#define GOLD    YELLOW
#define ON      WHITE

// Shifting Amounts
#define R_SHIFT RED/2
#define G_SHIFT GREEN/2
#define B_SHIFT BLUE/2

// Color Choices
#define COLOR_ERROR     RED
#define COLOR_POSSIBLE  BLUE
#define COLOR_CAPTURE   GREEN
#define COLOR_SPECIAL   PURPLE
#define COLOR_ORIGIN    WHITE
#define COLOR_ACCEPTED  GREEN

// Terminal Commands
#define CLEAR_TERMINAL "\033[2J\033[H"
#define NEWLINE_STR "\r\n"
#define BACKSPACE_STR "\b\033[K"

#define CARE 0x0D     // ASCII return 
#define LF 0x0A     // ASCII new line 

// LCD INSTRUCTION CHARACTERS
#define LCDON 0x0C
// LCD initialization command
#define LCDCLR 0x01 // LCD clear display command
#define TWOLINE 0x38    // LCD 2-line enable command
#define CURMOV 0xFE // LCD cursor move instruction
#define LINE1 0x80  // LCD line 1 cursor position
#define LINE2 0xC0  // LCD line 2 cursor position
#define MODE 0x06

// SPI and UART TIMEOUT
#define TIMEOUT 1000

// RFID Defines
#define UID_SIZE 10
#define SCANS_NUMBER 6

// Type Definitions
typedef char Color;
typedef Color C[8][8];
typedef char UID[UID_SIZE];

// RFID Addresses
extern int rfidReaderAddress;
extern int rfidAntennaAddress;

// UID Match Declarations
extern UID W_PAWN_1;
extern UID W_QUEEN;

// Function Declarations
int diffUID(UID uidA, UID uidB);
void blankColors(C board);
void updateLeds(C curBoard, C prevBoard);
void updateSquare(Piece * P, UID id);
void updateBoard(B curBoard);
char pawnPromote(void);
void Print(const char* format, ...);
void Scan(char* s);

#endif
