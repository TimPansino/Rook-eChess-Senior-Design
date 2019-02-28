#define PRINT_TYPE 1
// 0: Print C Array Indexes
// 1: Print Chess Board Standard Indexes

void printBoard(B board);
void printMoves(B board, M moves);
void printColors(C board);
void printColor(C c, int x, int y);
void printTurn(int side);
int charToCoord(char c);
char pawnPromote(void);
