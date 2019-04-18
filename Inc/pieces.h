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
