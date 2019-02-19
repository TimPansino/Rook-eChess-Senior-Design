// Includes
#include <stdio.h>
#include "pieces.h"
#include "chess.h"
#include "drivers.h"

// Function Definitions
void defaultBoard(B board) {
  blankBoard(board);

  initPiece(&board[0][0], Rook, White, 0);
  initPiece(&board[1][0], Knight, White, 0);
  initPiece(&board[2][0], Bishop, White, 0);
  initPiece(&board[3][0], Queen, White, 0);
  initPiece(&board[4][0], King, White, 0);
  initPiece(&board[5][0], Bishop, White, 0);
  initPiece(&board[6][0], Knight, White, 0);
  initPiece(&board[7][0], Rook, White, 0);
  initPiece(&board[0][1], Pawn, White, 0);
  initPiece(&board[1][1], Pawn, White, 0);
  initPiece(&board[2][1], Pawn, White, 0);
  initPiece(&board[3][1], Pawn, White, 0);
  initPiece(&board[4][1], Pawn, White, 0);
  initPiece(&board[5][1], Pawn, White, 0);
  initPiece(&board[6][1], Pawn, White, 0);
  initPiece(&board[7][1], Pawn, White, 0);
  initPiece(&board[0][6], Pawn, Black, 0);
  initPiece(&board[1][6], Pawn, Black, 0);
  initPiece(&board[2][6], Pawn, Black, 0);
  initPiece(&board[3][6], Pawn, Black, 0);
  initPiece(&board[4][6], Pawn, Black, 0);
  initPiece(&board[5][6], Pawn, Black, 0);
  initPiece(&board[6][6], Pawn, Black, 0);
  initPiece(&board[7][6], Pawn, Black, 0);
  initPiece(&board[0][7], Rook, Black, 0);
  initPiece(&board[1][7], Knight, Black, 0);
  initPiece(&board[2][7], Bishop, Black, 0);
  initPiece(&board[3][7], Queen, Black, 0);
  initPiece(&board[4][7], King, Black, 0);
  initPiece(&board[5][7], Bishop, Black, 0);
  initPiece(&board[6][7], Knight, Black, 0);
  initPiece(&board[7][7], Rook, Black, 0);
  return;
}

void blankMoves(M board) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = 0;
    }
  }
}

void blankBoard(B board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      initPiece(&board[i][j], 0, 0, 0);
    }
  }
}

void initPiece(Piece* p, char type, char side, char promotion) {
  p->type = type;
  p->side = side;
  p->promotion = promotion;
  p->unmoved = 1;
}

void movePiece(B board, int row1, int col1, int row2, int col2) {
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

  // Castling
  if (board[col2][row2].type == 'K') {
    switch (col2-col1) {
      case 2:
        movePiece(board, row1, 7, row2, col2-1);
        break;

      case -2:
        movePiece(board, row1, 0, row2, col2+1);
        break;

      default:
        break;
    }
  }

  return;
}

int possibleMoves(B board, M moves, int row, int col) {
  int ret = 0;
  Piece* p;
  int newCol;
  int newRow;
  int type;

  p = &board[col][row];

  if ((p->type == 'P') && (p->promotion != 0)) {
    type = p->promotion;
  }
  else {
    type = p->type;
  }

  blankMoves(moves);

  if ((row > 7) || (row < 0)) {
    return 0;
  }
  if ((col > 7) || (col < 0)) {
    return 0;
  }

  moves[col][row] = -1;

  switch(type) {
    case 'P':
      // TODO: Enpassante
      // Set pawn direction
      if (p->side == White) newRow = row + 1;
      else newRow = row - 1;

      if ((newRow < 8) && ((newRow) >= 0)) {
        // Forward
        if (board[col][newRow].side == 0) {
          moves[col][newRow] = 1;
          ret += 1;
          if (p->unmoved) {
            if (p->side == White) {
              if (board[col][newRow + 1].side == 0) {
                moves[col][newRow + 1] = 3;
                ret += 1;
              }
            }
            else {
              if (board[col][newRow - 1].side == 0) {
                moves[col][newRow - 1] = 3;
                ret += 1;
              }
            }

          }
        }

        // Left
        newCol = col - 1;
        if ((newCol < 8) && ((newCol) >= 0)) {
          if ((board[newCol][newRow].side != 0) && (board[newCol][newRow].side != p->side)) {
            moves[newCol][newRow] = 2;
            ret += 1;
          }
        }

        // Right
        newCol = col + 1;
        if ((newCol < 8) && ((newCol) >= 0)) {
          if ((board[newCol][newRow].side != 0) && (board[newCol][newRow].side != p->side)) {
            moves[newCol][newRow] = 2;
            ret += 1;
          }
        }
      }
      break;

    case 'Q':
      // Flows through Bishop and Rook cases before exiting.

    case 'B':
      // Down Right
      newRow = row;
      newCol = col;
      while ((++newCol < 8) && (++newRow < 8)) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Up Right
      newRow = row;
      newCol = col;
      while ((++newCol < 8) && (--newRow >= 0)) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Down Left
      newRow = row;
      newCol = col;
      while ((--newCol >= 0) && (++newRow < 8)) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Up Left
      newRow = row;
      newCol = col;
      while ((--newCol >= 0) && (--newRow >= 0)) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
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
      newRow = row;
      newCol = col;
      while (++newCol < 8) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Left
      newRow = row;
      newCol = col;
      while (--newCol >= 0) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Down
      newRow = row;
      newCol = col;
      while (++newRow < 8) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
          ret += 1;
          break;
        }
        else {
          break;
        }
      }

      // Up
      newRow = row;
      newCol = col;
      while (--newRow >= 0) {
        if(board[newCol][newRow].side == 0) {
          moves[newCol][newRow] = 1;
          ret += 1;
        }
        else if(board[newCol][newRow].side != p->side) {
          moves[newCol][newRow] = 2;
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
      newRow = row + 1;
      if (newRow < 8) {
        for(int i = -1; i < 2; i++) {
          newCol = col + i;
          if ((newCol < 8) && (newCol >= 0)) {
            if(board[newCol][newRow].side == 0) {
              moves[newCol][newRow] = 1;
              ret += 1;
            }
            else if(board[newCol][newRow].side != p->side) {
              moves[newCol][newRow] = 2;
              ret += 1;
            }
          }
        }
      }

      // Up
      newRow = row - 1;
      if (newRow >= 8) {
        for(int i = -1; i < 2; i++) {
          newCol = col + i;
          if ((newCol < 8) && (newCol >= 0)) {
            if(board[newCol][newRow].side == 0) {
              moves[newCol][newRow] = 1;
              ret += 1;
            }
            else if(board[newCol][newRow].side != p->side) {
              moves[newCol][newRow] = 2;
              ret += 1;
            }
          }
        }
      }

      // Middle
      newRow = row;
      if (newRow < 8) {
        for(int i = -2; i <= 2; i++) {
          newCol = col + i;
          if ((newCol < 8) && (newCol >= 0)) {
            switch (i) {
              case -1:
              case 1:
                if(board[newCol][newRow].side == 0) {
                  moves[newCol][newRow] = 1;
                  ret += 1;
                }
                else if(board[newCol][newRow].side != p->side) {
                  moves[newCol][newRow] = 2;
                  ret += 1;
                }
                break;
              case -2:
                moves[newCol][newRow] = 3;
                if ((!p->unmoved) || (board[0][row].type != 'R') || (!board[0][row].unmoved)) {
                  moves[newCol][newRow] = 0;
                }
                for (int j = 1; j < col; j++) {
                  if (board[j][row].side != 0) {
                    moves[newCol][newRow] = 0;
                  }
                }
                break;
              case 2:
                moves[newCol][newRow] = 3;
                if ((!p->unmoved) || (board[7][row].type != 'R') || (!board[7][row].unmoved)) {
                  moves[newCol][newRow] = 0;
                }
                for (int j = 6; j > col; j--) {
                  if (board[j][row].side != 0) {
                    moves[newCol][newRow] = 0;
                  }
                }
                break;
              default:
                break;
            }
          }
        }
      }


      break;

    case 'N':
      for (int i = -2; i <= 2; i++) {
        newRow = row + i;
        if ((newRow < 8) && (newRow >= 0)) {
          switch(i) {
            case 2:
            case -2:
              for (int j = -1; j <= 1; j += 2) {
                newCol = col + j;
                if ((newCol < 8) && (newCol >= 0)) {
                  if (board[newCol][newRow].side == 0) {
                    moves[newCol][newRow] = 1;
                    ret += 1;
                  }
                  else if (board[newCol][newRow].side != p->side) {
                    moves[newCol][newRow] = 2;
                    ret += 1;
                  }
                }
              }
              break;

            case 1:
            case -1:
              for (int j = -2; j <= 2; j += 4) {
                newCol = col + j;
                if ((newCol < 8) && (newCol >= 0)) {
                  if (board[newCol][newRow].side == 0) {
                    moves[newCol][newRow] = 1;
                    ret += 1;
                  }
                  else if (board[newCol][newRow].side != p->side) {
                    moves[newCol][newRow] = 2;
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
      return 0;
      break;
  }

  return ret;
}

int validMoves(B board, M moves, int row, int col) {
  char side = board[col][row].side;
  int ret = 0;

  // Retrieve possible moves
  possibleMoves(board, moves, row, col);

  // Determine if move is illegal based on check
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (moves[j][i] != 0) {
        ret += 1;
        switch(checkStatus(board, side)) {
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

int checkStatus(B board, char side){
  M moves;
  Piece* p;
  int check = 0;

  // Scan board
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      p = &board[j][i];
      if (p->side != 0) {
        possibleMoves(board, moves, i, j);
        if (p->side != side) {
          for (int jj = 0; jj < 8; jj++) {
            if (check) break;
            for (int ii = 0; ii < 8; ii++) {
              if ((moves[jj][ii] == 2) && (board[jj][ii].type == 'K')){
                check = 1;
                break;
              }
            }
          }
        }
      }
    }
  }

  return check;
}

int gameStatus(B board, char side) {
  int stale;
  int check;

  check = checkStatus(board, side);
  stale = !canMove(board, side);

  return check | (stale << 1);
}

int canMove(B board, char side) {
  M moves;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if ((board[i][j].side == side) && (validMoves(board, moves, j, i))) {
        //TODO: FIX THIS
        printf("ROW: %d | COL: %d\n", j, i);
        return 1;
      }
    }
  }

  return 0;
}

int isPossible(B newBoard, B oldBoard, int side) {
  M diff;
  M moves;
  int diffCt;

  int destRow1 = -1;
  int destCol1 = -1;
  int destRow2 = -1;
  int destCol2 = -1;

  int sourceRow1 = -1;
  int sourceCol1 = -1;
  int sourceRow2 = -1;
  int sourceCol2 = -1;

  diffCt = diffBoards(newBoard, oldBoard, diff);

  if (diffCt == 0) {
    return 0;
  }
  else if ((diffCt > 4) || (diffCt < 0)) {
    return 0;
  }
  else {
    for (int j = 0; j < 8; j++) {
      for (int i = 0; i < 8; i++) {
        if (diff[i][j] == 1) {
          if (newBoard[i][j].side == side) {
            if (destCol1 == -1) {
                destRow1 = j;
                destCol1 = i;
            }
            else {
              destRow2 = j;
              destCol2 = i;
            }
          }
          else if (newBoard[i][j].side == 0) {
            if (sourceCol1 == -1) {
                sourceRow1 = j;
                sourceCol1 = i;
            }
            else {
              sourceRow2 = j;
              sourceCol2 = i;
            }
          }
        }
      }
    }
  }

  if ((sourceRow2 == -1) && (destRow2 == -1)) {
    if (validMoves(oldBoard, moves, sourceRow1, sourceCol1)) {
      if (moves[destCol1][destRow1]) {
        return 1;
      }
    }
  }
  else if ((sourceRow2 != -1) && (destRow2 != -1)){
    //TODO: Castling
    return 1;
  }
  else {
    //TODO: Enpassante
    return 0;
  }


  return 0;
}

int diffBoards(B newBoard, B oldBoard, M diff) {
  int ret = 0;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if ((newBoard[i][j].type != oldBoard[i][j].type) && (newBoard[i][j].side != oldBoard[i][j].side)) {
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

void copyBoard(B newBoard, B oldBoard) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      newBoard[i][j].type = oldBoard[i][j].type;
      newBoard[i][j].side = oldBoard[i][j].side;
      newBoard[i][j].promotion = oldBoard[i][j].promotion;
      newBoard[i][j].unmoved = oldBoard[i][j].unmoved;
    }
  }

  return;
}
