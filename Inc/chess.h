#include "drivers.h"

// Function Declarations
int commandLine(void);
void initPiece(Piece* p, char type, char side, char promotion);
void blankBoard(B board);
void defaultBoard(B board);
void blankMoves(M board);
void movePiece(B board, int row1, int col1, int row2, int col2, int ignorePromotion);
int checkStatus(B board, char side);
int possibleMoves(B board, M moves, int row, int col);
int validMoves(B board, M moves, int row, int col);
int isPossible(B newBoard, B oldBoard, int side);
int diffBoards(B newBoard, B oldBoard, M diff);
void copyBoard(B newBoard, B oldBoard);
int canMove(B board, char side);
int gameStatus(B board, char side);
void initMove(Move* move);
int parseState(B newBoard, B oldBoard, int side, C colors, Move* move);
int charToCoord(char c);
