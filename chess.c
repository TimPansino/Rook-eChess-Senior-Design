// Includes
#include "pieces.h"
#include "chess.h"

// Function Definitions
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

void blank_moves(M board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = 0;
    }
  }
}

void blank_board(B board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j].type = 0;
      board[i][j].side = 0;
      board[i][j].promotion = 0;
    }
  }
}

void init_piece(Piece* p, char type, char side, char promotion) {
  p->type = type;
  p->side = side;
  p->promotion = promotion;
  p->unmoved = 1;
}

void move_piece(B board, int row1, int col1, int row2, int col2) {
  if ((row1 == row2) && (col1 == col2)) {
    return;
  }
  board[col2][row2].type = board[col1][row1].type;
  board[col2][row2].side = board[col1][row1].side;
  board[col2][row2].promotion = board[col1][row1].promotion;
  board[col2][row2].unmoved = 0;

  board[col1][row1].type = 0;
  board[col1][row1].side = 0;
  board[col1][row1].promotion = 0;
  board[col1][row1].unmoved = 0;

  return;
}

int possible_moves(B board, M moves, int row, int col) {
  int ret = 0;
  Piece* p;
  int new_col;
  int new_row;

  blank_moves(moves);

  if ((row > 7) || (row < 0)) {
    return 0;
  }
  if ((col > 7) || (col < 0)) {
    return 0;
  }

  moves[col][row] = -1;
  p = &board[col][row];

  switch(p->type) {
    case 'P':
      // TODO: Enpassante, double moves.
      // Set pawn direction
      if (p->side == White) new_row = row + 1;
      else new_row = row - 1;

      if ((new_row < 8) && ((new_row) >= 0)) {
        // Forward
        if (board[col][new_row].side == 0) {
          moves[col][new_row] = 1;
          ret += 1;
        }

        // Left
        new_col = col - 1;
        if ((new_col < 8) && ((new_col) >= 0)) {
          if ((board[new_col][new_row].side != 0) && (board[new_col][new_row].side != p->side)) {
            moves[new_col][new_row] = 2;
            ret += 1;
          }
        }

        // Right
        new_col = col + 1;
        if ((new_col < 8) && ((new_col) >= 0)) {
          if ((board[new_col][new_row].side != 0) && (board[new_col][new_row].side != p->side)) {
            moves[new_col][new_row] = 2;
            ret += 1;
          }
        }
      }
      break;

    case 'Q':
      // Flows through Bishop and Rook cases before exiting.

    case 'B':
      // Down Right
      new_row = row;
      new_col = col;
      while ((++new_col < 8) && (++new_row < 8)) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Up Right
      new_row = row;
      new_col = col;
      while ((++new_col < 8) && (--new_row >= 0)) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Down Left
      new_row = row;
      new_col = col;
      while ((--new_col >= 0) && (++new_row < 8)) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Up Left
      new_row = row;
      new_col = col;
      while ((--new_col >= 0) && (--new_row >= 0)) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Allow Queen to waterfall through to Rook.
      if (p->type != 'Q') {
        break;
      }

    case 'R':
      // Right
      new_row = row;
      new_col = col;
      while (++new_col < 8) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Left
      new_row = row;
      new_col = col;
      while (--new_col >= 0) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Down
      new_row = row;
      new_col = col;
      while (++new_row < 8) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Up
      new_row = row;
      new_col = col;
      while (--new_row >= 0) {
        if(board[new_col][new_row].side == 0) {
          moves[new_col][new_row] = 1;
          ret += 1;
        }
        else if(board[new_col][new_row].side != p->side) {
          moves[new_col][new_row] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }
      break;

    case 'K':
    // TODO: Add castling.
      // Down
      new_row = row + 1;
      if (new_row < 8) {
        for(int i = -1; i < 2; i++) {
          new_col = col + i;
          if ((new_col < 8) && (new_col >= 0)) {
            if(board[new_col][new_row].side == 0) {
              moves[new_col][new_row] = 1;
              ret += 1;
            }
            else if(board[new_col][new_row].side != p->side) {
              moves[new_col][new_row] = 2;
              ret += 1;
            }
          }
        }
      }

      // Up
      new_row = row - 1;
      if (new_row >= 8) {
        for(int i = -1; i < 2; i++) {
          new_col = col + i;
          if ((new_col < 8) && (new_col >= 0)) {
            if(board[new_col][new_row].side == 0) {
              moves[new_col][new_row] = 1;
              ret += 1;
            }
            else if(board[new_col][new_row].side != p->side) {
              moves[new_col][new_row] = 2;
              ret += 1;
            }
          }
        }
      }

      // Middle
      new_row = row;
      if (new_row < 8) {
        for(int i = -1; i < 2; i++) {
          new_col = col + i;
          if ((i != 0) && (new_col < 8) && (new_col >= 0)) {
            if(board[new_col][new_row].side == 0) {
              moves[new_col][new_row] = 1;
              ret += 1;
            }
            else if(board[new_col][new_row].side != p->side) {
              moves[new_col][new_row] = 2;
              ret += 1;
            }
          }
        }
      }


      break;

    case 'N':
      for (int i = -2; i <= 2; i++) {
        new_row = row + i;
        if ((new_row < 8) && (new_row >= 0)) {
          switch(i) {
            case 2:
            case -2:
              for (int j = -1; j <= 1; j += 2) {
                new_col = col + j;
                if ((new_col < 8) && (new_col >= 0)) {
                  if (board[new_col][new_row].side == 0) {
                    moves[new_col][new_row] = 1;
                    ret += 1;
                  }
                  else if (board[new_col][new_row].side != p->side) {
                    moves[new_col][new_row] = 2;
                    ret += 1;
                  }
                }
              }
              break;

            case 1:
            case -1:
              for (int j = -2; j <= 2; j += 4) {
                new_col = col + j;
                if ((new_col < 8) && (new_col >= 0)) {
                  if (board[new_col][new_row].side == 0) {
                    moves[new_col][new_row] = 1;
                    ret += 1;
                  }
                  else if (board[new_col][new_row].side != p->side) {
                    moves[new_col][new_row] = 2;
                    ret += 1;
                  }
                }
              }
              break;
            default: break;
          }
        }
      }
      break;

    default:
      blank_moves(moves);
      return 0;
  }

  return ret;
}

int valid_moves(B board, M moves, int row, int col) {
  char side = board[col][row].side;
  int ret = 0;

  // Retrieve possible moves
  possible_moves(board, moves, row, col);

  // Determine if move is illegal based on check
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (moves[j][i] != 0) {
        ret += 1;
        switch(check_status(board, side)) {
          case 1: // Check
          case 3: // Checkmate
            moves[j][i] = 0;
            ret -= 1;
            break;

          default: break;
        }
      }
    }
  }
  return ret;
}

int check_status(B board, char side){
  M moves;
  Piece* p;
  int check = 0;
  int stale = 2;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      p = &board[j][i];
      if (p->side != 0) {
        possible_moves(board, moves, i, j);
        if (p->side != side) {
          for (int jj = 0; jj < 8; jj++) {
            for (int ii = 0; ii < 8; ii++) {
              if ((moves[jj][ii] == 2) && (board[jj][ii].type == 'K')){
                check = 1;
              }
            }
          }
        }
        else {
          for (int jj = 0; jj < 8; jj++) {
            for (int ii = 0; ii < 8; ii++) {
              // TODO: Check for stalemate
              stale = 0;
            }
          }
        }
      }
    }
  }

  return check + stale;
}

int is_possible(B new_board, B old_board, int side) {
  M diff;
  M moves;
  int diff_ct;

  int dest_row1 = -1;
  int dest_col1 = -1;
  int dest_row2 = -1;
  int dest_col2 = -1;

  int source_row1 = -1;
  int source_col1 = -1;
  int source_row2 = -1;
  int source_col2 = -1;

  diff_ct = diff_boards(new_board, old_board, diff);

  if (diff_ct == 0) {
    return 1;
  }
  else if ((diff_ct > 4) || (diff_ct < 0)) {
    return 0;
  }
  else {
    for (int j = 0; j < 8; j++) {
      for (int i = 0; i < 8; i++) {
        if (diff[i][j] == 1) {
          if (new_board[i][j].side == side) {
            if (dest_col1 == -1) {
                dest_row1 = j;
                dest_col1 = i;
            }
            else {
              dest_row2 = j;
              dest_col2 = i;
            }
          }
          else if (new_board[i][j].side == 0) {
            if (source_col1 == -1) {
                source_row1 = j;
                source_col1 = i;
            }
            else {
              source_row2 = j;
              source_col2 = i;
            }
          }
        }
      }
    }
  }

  if ((source_row2 == -1) && (dest_row2 == -1)) {
    if (valid_moves(old_board, moves, source_row1, source_col1)) {
      if (moves[dest_col1][dest_row1]) {
        return 1;
      }
    }
  }
  else if ((source_row2 != -1) && (dest_row2 != -1)){
    //TODO: Castling
    return 1;
  }
  else {
    //TODO: Enpassante
    return 0;
  }


  return 0;
}

int diff_boards(B new_board, B old_board, M diff) {
  int ret = 0;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if ((new_board[i][j].type != old_board[i][j].type) && (new_board[i][j].side != old_board[i][j].side)) {
        diff[i][j] = 1;
        ret += 1;
      }
      else {
        diff[i][j] = 0;
      }
    }
  }

  return ret;
}

void copy_board(B new_board, B old_board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      new_board[i][j].type = old_board[i][j].type;
      new_board[i][j].side = old_board[i][j].side;
      new_board[i][j].promotion = old_board[i][j].promotion;
      new_board[i][j].unmoved = old_board[i][j].unmoved;
    }
  }

  return;
}
