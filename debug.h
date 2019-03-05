#define PRINT_TYPE 1
// 0: Print C Array Indexes
// 1: Print Chess Board Standard Indexes
#define DEBUG 1

// Terminal Colors
#define TRED   "\x1B[31m"
#define TGRN   "\x1B[32m"
#define TYEL   "\x1B[33m"
#define TBLU   "\x1B[34m"
#define TMAG   "\x1B[35m"
#define TCYN   "\x1B[36m"
#define TWHT   "\x1B[37m"
#define TRESET "\x1B[0m"

void printBoard(B board);
void printMoves(B board, M moves);
void printColors(C board);
void printColor(C c, int x, int y);
void printTurn(int side);
int charToCoord(char c);
