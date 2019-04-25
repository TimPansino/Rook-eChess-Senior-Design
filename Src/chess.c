// Includes
#include <stdio.h>
#include <string.h>
#include "pieces.h"
#include "drivers.h"
#include "chess.h"
#include "debug.h"

// Function Definitions
int commandLine(void) {
  char s[100];
  C colors;
  B curBoard;
  B prevBoard;
  M moves;
  Move move;
  Piece tempPiece;
  char side = White;
  int check = 0;
  int status = 0;

  defaultBoard(curBoard);
  defaultBoard(prevBoard);
  blankColors(colors);

  Print("\nWelcome to my half-baked chess simulator.\nType \"help\" for options!\n");
  Print("\n");
  printBoard(curBoard);

  while (1) {
    printTurn(side);
    status = gameStatus(curBoard, side);
    Print("Game Status: %d\n", status);
    Print(">");
    Scan(s);
    if (strcmp(s, "exit") == 0) {
      Print("Exiting...\n");
      break;
    }
    else if (strcmp(s, "help") == 0) {
      Print("help: This menu.\n");
      Print("b2c2: Movement example.\n");
      Print("d4: Lift piece example (replaces in same spot afterwards).\n");
      Print("dela1: Delete piece example.\n");
      Print("pute5: Replace last deleted piece example.\n");
      Print("skip: Ends current turn.\n");
      Print("force: Ends current turn and accepts board state.\n");
      Print("reset: Put the board back to the last accepted state.\n");
      Print("newgame: Start a new game.\n");
      Print("exit: Leave the simulator.\n");
    }
    else if (strcmp(s, "reset") == 0) {
      Print("Reset board to last state.\n");
      copyBoard(curBoard, prevBoard);
    }
    else if (strcmp(s, "force") == 0) {
      Print("Forced the board to accept current state.\n");
      copyBoard(prevBoard, curBoard);
      check = 0;
      switch(side) {
        case White: {
          side = Black;
          break;
        }
        case Black: {
          side = White;
          break;
        }
      }

      if ((status = gameStatus(curBoard, side)) > 1) {
        break;
      }
    }
    else if (strcmp(s, "skip") == 0) {
      Print("Skipping current turn.\n");
      check = 0;
      switch(side) {
        case White: {
          side = Black;
          break;
        }
        case Black: {
          side = White;
          break;
        }
      }

      if ((status = gameStatus(curBoard, side)) > 1) {
        break;
      }
    }
    else if (strcmp(s, "newgame") == 0) {
      check = 0;
      status = 0;
      side = White;

      defaultBoard(curBoard);
      defaultBoard(prevBoard);
      blankColors(colors);

      Print("New Game Started.\n");
    }
    else if ((strlen(s) == 5) && (s[0] == 'd') && (s[1] == 'e') && (s[2] == 'l')) {
      // Delete a piece
      int x, y;
      int flag = 0;

      if ((x = charToCoord(s[3])) == -1) flag = 1;
      if ((y = charToCoord(s[4])) == -1) flag = 1;
      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else {
        tempPiece.type = curBoard[x][y].type;
        tempPiece.side = curBoard[x][y].side;
        tempPiece.promotion = curBoard[x][y].promotion;
        tempPiece.unmoved = 0;

        curBoard[x][y].type = 0;
        curBoard[x][y].side = 0;
        check = 1;
      }
    }
    else if ((strlen(s) == 5) && (s[0] == 'p') && (s[1] == 'u') && (s[2] == 't')) {
      // Delete a piece
      int x, y;
      int flag = 0;

      if ((x = charToCoord(s[3])) == -1) flag = 1;
      if ((y = charToCoord(s[4])) == -1) flag = 1;
      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else if (tempPiece.side == 0) {
        Print("Error: No piece to replace.\n");
      }
      else {
        curBoard[x][y].type = tempPiece.type;
        curBoard[x][y].side = tempPiece.side;
        curBoard[x][y].promotion = tempPiece.promotion;
        curBoard[x][y].unmoved = 0;
        tempPiece.side = 0;

        check = 1;
      }
    }
    else if (strlen(s) == 2) {
      // Lift a piece to view colors
      int x, y;
      int flag = 0;

      if ((x = charToCoord(s[0])) == -1) flag = 1;
      if ((y = charToCoord(s[1])) == -1) flag = 1;
      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else {
        // Lift Piece
        tempPiece.type = curBoard[x][y].type;
        tempPiece.side = curBoard[x][y].side;
        curBoard[x][y].type = 0;
        curBoard[x][y].side = 0;

        // Display Status
        check = parseState(curBoard, prevBoard, side, colors, &move);
        printColors(colors);

        // Replace Piece
        curBoard[x][y].type = tempPiece.type;
        curBoard[x][y].side = tempPiece.side;

        // Display Moves
        if (side == curBoard[x][y].side) {
          validMoves(curBoard, moves, y, x);
          //printMoves(curBoard, moves);
        }
        check = 0;
      }
    }
    else if (strlen(s) == 4) {
      // Move a piece
      int x, y, xx, yy;
      int flag = 0;
      if ((x = charToCoord(s[0])) == -1) flag = 1;
      if ((y = charToCoord(s[1])) == -1) flag = 1;
      if ((xx = charToCoord(s[2])) == -1) flag = 1;
      if ((yy = charToCoord(s[3])) == -1) flag = 1;

      if (flag) {
        Print("Error: Move could not be parsed.\n");
      }
      else {
        movePiece(curBoard, y, x, yy, xx);
        check = 1;
      }
    }
    else {
      Print("Error: Could not parse command.\n");
    }

    if (check) {
      check = parseState(curBoard, prevBoard, side, colors, &move);
      if (check == 1) {
        copyBoard(prevBoard, curBoard);
        switch(side) {
          case White:
            side = Black;
            break;
          case Black:
            side = White;
            break;
        }

        Print("Move Accepted.\n");
        Print("Move: %c%c-%c%c\n", move.sourceCol+'A', move.sourceRow+'1', move.destCol+'A', move.destRow+'1');
        printColors(colors);
        printBoard(curBoard);
        if ((status = gameStatus(curBoard, side)) > 1) {
          break;
        }
      }
      else {
        Print("Board State Invalid.\n");
        printColors(colors);
        printBoard(curBoard);
        Print("Use \"reset\" to go back.\n");
      }
      check = 0;
    }
    else {
      Print("\n");
      printBoard(curBoard);
    }
  }

  switch (status) {
    case 0:
      Print("Game Quit.\n");
      break;
    case 1:
      Print("Game Quit While in Check.\n");
      break;
    case 2:
      Print("Game Over: Stalemate.\n");
      break;
    case 3:
      if (side == White) {
        Print("Game Over: Black Wins!\n");
      }
      else {
        Print("Game Over: White Wins!\n");
      }
      break;
    default:
      Print("Error: Invalid game state.\n");
      break;
  }

  return 0;
}

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

  // En passante
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

inline void makeMove(B board, Move m) {
  movePiece(board, m.sourceRow, m.sourceCol, m.destRow, m.destCol);
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

  moves[col][row] = 10;

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
      if (type != 'Q') {
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
      // Up
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
      if (newRow >= 0) {
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
                if ((!p->unmoved) || (board[0][row].type != 'R') || (!board[0][row].unmoved)) {
                  moves[newCol][newRow] = 0;
                }
                else {
                  moves[newCol][newRow] = 3;
                  ret += 1;
                }
                for (int j = 1; j < col; j++) {
                  if (board[j][row].side != 0) {
                    moves[newCol][newRow] = 0;
                  }
                }
                break;
              case 2:
                if ((!p->unmoved) || (board[7][row].type != 'R') || (!board[7][row].unmoved)) {
                  moves[newCol][newRow] = 0;
                }
                else {
                  moves[newCol][newRow] = 3;
                  ret += 1;
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
      if (moves[j][i] > 0) {
        copyBoard(newBoard, board);
        movePiece(newBoard, row, col, i, j);
        if (checkStatus(newBoard, side)) {
          if (moves[j][i] != 10) {
        	  moves[j][i] = 0;
          }
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

  return check | (stale << 1);
}

int canMove(B board, char side) {
  M moves;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (board[i][j].side == side) {
        if (validMoves(board, moves, j, i) > 0)  {
          return 1;
        }
      }
    }
  }

  return 0;
}

int parseState(B newBoard, B oldBoard, int side, C colors, Move* move) {
    B tempBoard;
    M diff;
    M dummyDiff;
    M moves;
    int diffCt;
    int state = 0;
    int missingRow = -1;
    int missingCol = -1;

    diffCt = diffBoards(newBoard, oldBoard, diff);
    initMove(move);
    blankColors(colors);

    if (diffCt == 0) {
      return 0;
    }
    else if ((diffCt > 4) || (diffCt < 0)) {
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (diff[i][j]) {
            colors[i][j] = COLOR_ERROR;
          }
        }
      }
      return -1;
    }
    else {
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (diff[i][j] == 1) {
            if (newBoard[i][j].side == side) {
              if (move->destCol == -1) {
                  move->destRow = j;
                  move->destCol = i;
              }
              else {
                if (newBoard[i][j].type == 'K') {
                  move->destRow = j;
                  move->destCol = i;
                }
              }
            }
            else if ((newBoard[i][j].side == 0) && (oldBoard[i][j].side == side)) {
              if (move->sourceCol == -1) {
                  move->sourceRow = j;
                  move->sourceCol = i;
              }
              else {
                if (oldBoard[i][j].type == 'K') {
                  move->sourceRow = j;
                  move->sourceCol = i;
                }
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

    // Set Colors
    if ((diffCt == 1) && (move->sourceRow != -1)) {
      // Indicate Possible Moves
      validMoves(oldBoard, moves, move->sourceRow, move->sourceCol);
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          switch (moves[i][j]) {
            case 10:
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
    else if ((diffCt == 2) && (move->sourceRow != -1) && (missingRow != -1)) {
      // Indicate Possible Capture
      validMoves(oldBoard, moves, move->sourceRow, move->sourceCol);
      if (moves[missingCol][missingRow]) {
        colors[missingCol][missingRow] = COLOR_CAPTURE;
        colors[move->sourceCol][move->sourceRow] = COLOR_ORIGIN;
      }
      else {
        state = -1;
      }
    }
    else if ((move->sourceRow != -1) && (move->destRow != -1)) {
      // Validate Movement
      copyBoard(tempBoard, oldBoard);
      validMoves(oldBoard, moves, move->sourceRow, move->sourceCol);
      if (moves[move->destCol][move->destRow] == 0) {
        state = -1;
      }
      else {
        movePiece(tempBoard, move->sourceRow, move->sourceCol, move->destRow, move->destCol);

        if (diffBoards(tempBoard, newBoard, dummyDiff) != 0) {
          state = -1;
        }
        else {
          state = 1;

          for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 8; i++) {
              if (diff[j][i]) {
                colors[j][i] = COLOR_ACCEPTED;
              }
            }
          }
        }
      }
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
  move->sourceRow = -1;
  move->sourceCol = -1;
  move->destRow = -1;
  move->destCol = -1;
}

int diffBoards(B newBoard, B oldBoard, M diff) {
  int ret = 0;
  char newtype = 0;
  char oldtype = 0;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if ((newBoard[i][j].side != 0) || (oldBoard[i][j].side != 0)) {
    	// New Type
    	if ((newBoard[i][j].type == 'P') && (newBoard[i][j].promotion != 0)) {
    		newtype = newBoard[i][j].promotion;
    		Print("USING PROMO: %c\n", newtype);
    	}
    	else {
    		newtype = newBoard[i][j].type;
    	}

    	// Old Type
    	if ((oldBoard[i][j].type == 'P') && (oldBoard[i][j].promotion != 0)) {
    		oldtype = oldBoard[i][j].promotion;
    		Print("USING PROMO: %c\n", oldtype);
    	}
    	else {
    		oldtype = oldBoard[i][j].type;
    	}

    	// Diff Types
    	if (newBoard[i][j].side != oldBoard[i][j].side) {
		  diff[i][j] = 1;
		  ret += 1;
    	}
    	else if ((newBoard[i][j].type != oldBoard[i][j].type) && (newBoard[i][j].type != oldtype) && (newBoard[i][j].type != oldtype) && (newtype != oldtype)) {
            diff[i][j] = 1;
            ret += 1;
        }
        else {
          diff[i][j] = 0;
        }
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

void blankColors(C board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j] = COLOR_OFF;
    }
  }
}

int charToCoord(char c) {
  if (c >= 'A' && c <= 'H') {
    return c - 'A';
  }
  else if (c >= 'a' && c <= 'h') {
    return c - 'a';
  }
  else if (c >= '1' && c <= '8') {
    return c - '1';
  }
  else {
    return -1;
  }
}

char strToMove(char* s, Move* move) {
  int size = strlen(s);
  if ((size != 4) && (size != 5)) {
    move->sourceCol = -1;
    move->sourceRow = -1;
    move->destCol = -1;
    move->destRow = -1;
    return -1;
  }
  else {
    move->sourceCol = charToCoord(s[0]);
    move->sourceRow = charToCoord(s[1]);
    move->destCol = charToCoord(s[2]);
    move->destRow = charToCoord(s[3]);

    if ((move->sourceCol < 0) || (move->sourceCol > 7)) return -1;
    if ((move->sourceRow < 0) || (move->sourceRow > 7)) return -1;
    if ((move->destCol < 0) || (move->destCol > 7)) return -1;
    if ((move->destRow < 0) || (move->destRow > 7)) return -1;
  }

  if ((s[4] >= 'a') && (s[4] <= 'z')) s[4] += ('A' - 'a');

  return s[4];
}

char switchSide(char curSide) {
	switch (curSide) {
		case White:
			curSide = Black;
			break;
		case Black:
			curSide = White;
			break;
	}

	return curSide;
}

char verifyMove(B curBoard, Move* move) {
	M moves;

	if ((move->destCol == -1) || (move->sourceCol == -1)) {
		return 0;
	}

	validMoves(curBoard, moves, move->sourceRow, move->sourceCol);
	printMoves(curBoard, moves);
	Print("Move Value: %d\n", moves[move->destCol][move->destRow]);
	if (moves[move->destCol][move->destRow]) {
		return 1;
	}

	return 0;
}

void moveToStr(Move* move, char *s, int promote) {
  s[5] = '\0';
  s[0] = move->sourceCol + 'a';
  s[1] = move->sourceRow + '1';
  s[2] = move->destCol + 'a';
  s[3] = move->destRow + '1';
  s[4] = promote;
  if ((s[4] >= 'A') && (s[4] <= 'Z')) s[4] -= 'A' - 'a';
}
