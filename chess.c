// Includes
#include <stdio.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"

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

  // Enpassante
  if ((board[col2][row2].type == 'G') && (board[col1][row1].type == 'P')) {
    board[col2][row1].side = 0;
  }

  // Move Piece
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

  // Remove old ghost
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (board[i][j].type == 'G') {
        board[i][j].type = 0;
      }
    }
  }

  // Add new ghost
  if ((board[col2][row2].type == 'P') && (board[col2][row2].promotion == 0)) {
    switch (row2 - row1) {
      case 2:
        board[col2][row1+1].type = 'G';
        break;

      case -2:
        board[col2][row1-1].type = 'G';
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
          else if (board[newCol][newRow].type == 'G') {
            moves[newCol][newRow] = 3;
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
          else if (board[newCol][newRow].type == 'G') {
            moves[newCol][newRow] = 3;
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
  B newBoard;

  // Retrieve possible moves
  possibleMoves(board, moves, row, col);

  // Determine if move is illegal based on check
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (moves[j][i] != 0) {
        copyBoard(newBoard, board);
        movePiece(newBoard, row, col, i, j);
        if (checkStatus(newBoard, side)) {
          moves[j][i] = 0;
        }
        else {
          ret += 1;
        }
      }
    }
  }
  return ret;
}

int checkStatus(B board, char side){
  M moves;
  Piece* p;

  // Scan board
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      p = &board[j][i];
      if (p->side != 0) {
        possibleMoves(board, moves, i, j);
        if (p->side != side) {
          for (int jj = 0; jj < 8; jj++) {
            for (int ii = 0; ii < 8; ii++) {
              if ((moves[jj][ii] == 2) && (board[jj][ii].type == 'K')){
                return 1;
              }
            }
          }
        }
      }
    }
  }

  return 0;
}

int gameStatus(B board, char side) {
  int stale;
  int check;

  check = checkStatus(board, side);
  stale = !canMove(board, side);

  printf("Check: %d\n", check);
  printf("Stale: %d\n", stale);

  return check | (stale << 1);
}

int canMove(B board, char side) {
  M moves;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (board[i][j].side == side) {
        printf("Checking Piece (%d, %d)\n", j, i);
        if (validMoves(board, moves, j, i)) {
          return 1;
        }
      }
    }
  }

  return 0;
}

int parseState(B newBoard, B oldBoard, int side, C colors, Move* move) {
    M diff;
    M moves;
    int diffCt;
    int state = 1;

    int destRow1 = -1;
    int destCol1 = -1;
    int destRow2 = -1;
    int destCol2 = -1;
    int sourceRow1 = -1;
    int sourceCol1 = -1;
    int sourceRow2 = -1;
    int sourceCol2 = -1;
    int missingRow = -1;
    int missingCol = -1;

    diffCt = diffBoards(newBoard, oldBoard, diff);
    initMove(move);
    blankColors(colors);

    if (diffCt == 0) {
      return 0;
    }
    else if ((diffCt > 4) || (diffCt < 0)) {
      state = -1;
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
              else if (destCol2 == -1){
                destRow2 = j;
                destCol2 = i;
              }
              else {
                state = -1;
              }
            }
            else if ((newBoard[i][j].side == 0) && (oldBoard[i][j].side == side)) {
              if (sourceCol1 == -1) {
                  sourceRow1 = j;
                  sourceCol1 = i;
              }
              else if (sourceCol2 == -1) {
                sourceRow2 = j;
                sourceCol2 = i;
              }
              else {
                state = -1;
              }
            }
            else if (newBoard[i][j].side == 0) {
              missingRow = j;
              missingCol = i;
            }
          }
        }
      }
    }

    // Catch errors
    if (state == -1) {
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (diff[i][j]) {
            colors[i][j] = COLOR_ERROR;
          }
        }
      }
      return -1;
    }

    // Debug
    printf("Ct: %d\nS: %d | %d\nD: %d | %d\nM: %d\n", diffCt, sourceRow1, sourceRow2, destRow1, destRow2, missingRow);

    // Set Colors
    if ((diffCt == 1) && (sourceRow1 != -1)) {
      validMoves(oldBoard, moves, sourceRow1, sourceCol1);
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          switch (moves[i][j]) {
            case -1:
              colors[i][j] = COLOR_ORIGIN;
              break;

            case 1:
              colors[i][j] = COLOR_POSSIBLE;
              break;

            case 2:
              colors[i][j] = COLOR_CAPTURE;
              break;

            case 3:
              colors[i][j] = COLOR_SPECIAL;
              break;

            default:
              break;
          }
        }
      }
    }
    else if ((diffCt == 2) && (destRow1 == -1) && (missingRow != -1)) {
      // Indicate Possible Capture
    }
    else if ((sourceRow2 == -1) && (destRow2 == -1)) {
      if (validMoves(oldBoard, moves, sourceRow1, sourceCol1)) {
        switch (moves[destCol1][destRow1]) {
          case -1:
            colors[destCol1][destRow1] = COLOR_ORIGIN;
            break;

          case 1:
            colors[destCol1][destRow1] = COLOR_POSSIBLE;
            break;

          case 2:
            colors[destCol1][destRow1] = COLOR_CAPTURE;
            break;

          case 3:
            colors[destCol1][destRow1] = COLOR_SPECIAL;
            break;

          default:
            break;
        }
      }
    }
    else if (sourceRow2 != -1) {
      //TODO: Enpassante
      printf("Enpassante detected.\n");
      if (newBoard[destCol1][destRow1].type == 'P') {
        return 1;
      }
      else if (newBoard[destCol2][destRow2].type == 'P') {
        return 1;
      }
      else {
        state = -1;
      }
    }
    else if ((sourceRow2 != -1) && (destRow2 != -1)) {
      //TODO: Castling
      printf("Castling detected.\n");
      state = -1;
    }
    else {
      state = -1;
    }

    // Catch errors
    if (state == -1) {
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (diff[i][j]) {
            colors[i][j] = COLOR_ERROR;
          }
        }
      }
      return -1;
    }

    return state;
}

void initMove(Move* move) {
  move->newRow = -1;
  move->newCol = -1;
  move->oldRow = -1;
  move->oldCol = -1;
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
