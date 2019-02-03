// Includes
#include <stdio.h>
#include "pieces.h"

// Type Declarations
typedef struct Piece_S {
  char type;
  char side;
  char promotion;
} Piece;
typedef Piece B[8][8];
typedef char M[8][8];

// Function Declarations
void init_piece(Piece* p, char type, char side, char promotion);
void blank_board(B board);
void blank_moves(M board);
void print_board(B board);
void print_moves(B board, M moves);
void default_board(B board);
char piece_side(char piece);
void move_piece(B board, int row1, int col1, int row2, int col2);
int check_status(B board);
void possible_moves(B board, M moves, int row, int col);

// Functions
int main(int argc, char** argv) {
  B cur_board;
  M moves;

  blank_board(cur_board);
  print_board(cur_board);

  default_board(cur_board);
  print_board(cur_board);

  move_piece(cur_board, 6, 4, 1, 2);
  print_board(cur_board);
  printf("Check Status: %d\n\n", check_status(cur_board));

  possible_moves(cur_board, moves, 6, 4);
  print_moves(cur_board, moves);
}

void default_board(B board) {
  blank_board(board);

  init_piece(&board[0][0], Rook, White, 0);
  init_piece(&board[1][0], Knight, White, 0);
  init_piece(&board[2][0], Bishop, White, 0);
  init_piece(&board[3][0], King, White, 0);
  init_piece(&board[4][0], Queen, White, 0);
  init_piece(&board[5][0], Bishop, White, 0);
  init_piece(&board[6][0], Knight, White, 0);
  init_piece(&board[7][0], Rook, White, 0);
  init_piece(&board[0][1], Pawn, White, 0);
  init_piece(&board[1][1], Pawn, White, 0);
  init_piece(&board[2][1], Pawn, White, 0);
  init_piece(&board[3][1], Pawn, White, 0);
  init_piece(&board[4][1], Pawn, White, 0);
  init_piece(&board[5][1], Pawn, White, 0);
  init_piece(&board[6][1], Pawn, White, 0);
  init_piece(&board[7][1], Pawn, White, 0);
  init_piece(&board[0][6], Pawn, Black, 0);
  init_piece(&board[1][6], Pawn, Black, 0);
  init_piece(&board[2][6], Pawn, Black, 0);
  init_piece(&board[3][6], Pawn, Black, 0);
  init_piece(&board[4][6], Pawn, Black, 0);
  init_piece(&board[5][6], Pawn, Black, 0);
  init_piece(&board[6][6], Pawn, Black, 0);
  init_piece(&board[7][6], Pawn, Black, 0);
  init_piece(&board[0][7], Rook, Black, 0);
  init_piece(&board[1][7], Knight, Black, 0);
  init_piece(&board[2][7], Bishop, Black, 0);
  init_piece(&board[3][7], King, Black, 0);
  init_piece(&board[4][7], Queen, Black, 0);
  init_piece(&board[5][7], Bishop, Black, 0);
  init_piece(&board[6][7], Knight, Black, 0);
  init_piece(&board[7][7], Rook, Black, 0);
  return;
}

void fill_board(B board, Piece p) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j].type = p.type;
      board[i][j].side = p.side;
      board[i][j].promotion = p.promotion;
    }
  }
}

void blank_moves(M board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = 0;
    }
  }
}

void blank_board(B board) {
  Piece p;
  p.type = 0;
  p.side = 0;
  p.promotion = 0;
  fill_board(board, p);
}

void init_piece(Piece* p, char type, char side, char promotion) {
  p->type = type;
  p->side = side;
  p->promotion = promotion;
}

void print_board(B board) {
  char c;

  printf("   0  1  2  3  4  5  6  7\n");
  for (int j = 0; j < 8; j++) {
    printf("%d:", j);
    for (int i = 0; i < 8; i++) {
      if (board[i][j].side == 1) {
        c = board[i][j].type;
      }
      else if (board[i][j].side == 2) {
        c = board[i][j].type + 32;
      }
      else {
        c = '-';
      }
      printf(" %c ", c);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void print_moves(B board, M moves) {
  char c;

  printf("   0  1  2  3  4  5  6  7\n");
  for (int j = 0; j < 8; j++) {
    printf("%d:", j);
    for (int i = 0; i < 8; i++) {
      switch(moves[i][j]) {
        case -1:
          c = board[i][j].type;
          break;
        case 1:
          c = 'O';
          break;
        case 2:
        case 3:
          c = board[i][j].type + 32;
          break;
        default:
          c = '-';
          break;
      }
      printf(" %c ", c);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void move_piece(B board, int row1, int col1, int row2, int col2) {
  board[col2][row2].type = board[col1][row1].type;
  board[col2][row2].side = board[col1][row1].side;
  board[col2][row2].promotion = board[col1][row1].promotion;

  board[col1][row1].type = 0;
  board[col1][row1].side = 0;
  board[col1][row1].promotion = 0;
}

void possible_moves(B board, M moves, int row, int col) {
  blank_moves(moves);
  Piece* p;
  int new_col;
  int new_row;


  if ((row > 7) || (row < 0)) {
    printf("Error: Row out of bounds.");
    return;
  }
  if ((col > 7) || (col < 0)) {
    printf("Error: Col out of bounds.");
    return;
  }

  moves[col][row] = -1;
  p = &p;

  switch(p->type) {
    case 'P':
      // Set pawn direction
      if (p->side == 1) new_row = row + 1;
      else new_row = row - 1;

      if ((new_row < 8) && ((new_row) >= 0)) {
        // Forward
        if (board[col][new_row].side == 0) {
          moves[col][new_row] = 1;
        }

        // Left
        new_col = col - 1;
        if ((new_col < 8) && ((new_col) >= 0)) {
          if ((board[new_col][new_row].side != 0) && (board[new_col][new_row].side != p->side)) {
            moves[new_col][new_row] = 1;
          }
        }

        // Right
        new_col = col + 1;
        if ((new_col < 8) && ((new_col) >= 0)) {
          if ((board[new_col][new_row].side != 0) && (board[new_col][new_row].side != p->side)) {
            moves[new_col][new_row] = 1;
          }
        }
      }
      break;

    default:
      blank_moves(moves);
      break;
  }

  return;
}

int check_status(B board){
  int check = 0;
  B moves;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      check = 0; // DELETE THIS
    }
  }

  return check;
}
