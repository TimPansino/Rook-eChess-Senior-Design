// Includes
#include <stdio.h>
#include "pieces.h"

// Type Declarations
typedef char B[8][8];

// Function Declarations
void blank_board(B board);
void print_board(B board);
void default_board(B board);
char piece_side(char piece);


// Functions
int main(int argc, char** argv) {
  B cur_board;
  blank_board(cur_board);
  print_board(cur_board);

  blank_board(cur_board);
  print_board(cur_board);

  default_board(cur_board);
  print_board(cur_board);

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      printf("%d,%d: %d\n", i, j, piece_side(cur_board[i][j]));
    }
  }
  
}

void default_board(B board) {
  blank_board(board);

  board[0][0] = White_Rook;
  board[1][0] = White_Knight;
  board[2][0] = White_Bishop;
  board[3][0] = White_King;
  board[4][0] = White_Queen;
  board[5][0] = White_Bishop;
  board[6][0] = White_Knight;
  board[7][0] = White_Rook;
  board[0][1] = White_Pawn;
  board[1][1] = White_Pawn;
  board[2][1] = White_Pawn;
  board[3][1] = White_Pawn;
  board[4][1] = White_Pawn;
  board[5][1] = White_Pawn;
  board[6][1] = White_Pawn;
  board[7][1] = White_Pawn;
  board[0][6] = Black_Pawn;
  board[1][6] = Black_Pawn;
  board[2][6] = Black_Pawn;
  board[3][6] = Black_Pawn;
  board[4][6] = Black_Pawn;
  board[5][6] = Black_Pawn;
  board[6][6] = Black_Pawn;
  board[7][6] = Black_Pawn;
  board[0][7] = Black_Rook;
  board[1][7] = Black_Knight;
  board[2][7] = Black_Bishop;
  board[3][7] = Black_King;
  board[4][7] = Black_Queen;
  board[5][7] = Black_Bishop;
  board[6][7] = Black_Knight;
  board[7][7] = Black_Rook;

  return;
}

void fill_board(B board, char c) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j] = c;
    }
  }
}

void blank_board(B board) {
  fill_board(board, 'O');
}


void print_board(B board) {
  printf("   0  1  2  3  4  5  6  7\n");
  for (int j = 0; j < 8; j++) {
    printf("%d:", j);
    for (int i = 0; i < 8; i++) {
      printf(" %c ", board[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

char piece_side(char piece) {
  char color; 

  switch(piece) {
    case 'K': color = 1; break;
    case 'N': color = 1; break;
    case 'R': color = 1; break;
    case 'P': color = 1; break;
    case 'Q': color = 1; break;
    case 'B': color = 1; break;
    case 'k': color = 2; break;
    case 'n': color = 2; break;
    case 'r': color = 2; break;
    case 'p': color = 2; break;
    case 'q': color = 2; break;
    case 'b': color = 2; break;
    default: color = 0;
  }

  return color;
}
