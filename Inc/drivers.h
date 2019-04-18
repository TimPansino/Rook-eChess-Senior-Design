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
#define LCDON 0x0C  	// LCD initialization command
#define LCDCLR 0x01 	// LCD clear display command
#define TWOLINE 0x38    // LCD 2-line enable command
#define CURMOV 0xFE 	// LCD cursor move instruction
#define LINE1 0x80  	// LCD line 1 cursor position
#define LINE2 0xC0  	// LCD line 2 cursor position
#define MODE 0x06

// SPI and UART TIMEOUT
#define TIMEOUT 100

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
void updateLeds(C curBoard, C prevBoard);
void updateSquare(Piece * P, UID id);
void updateBoard(B curBoard);
void printUIDArray(UID id, int size);
char pawnPromote(void);
void Print(const char* format, ...);
void Scan(char* s);

#endif
