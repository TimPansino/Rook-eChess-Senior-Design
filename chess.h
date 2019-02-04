// Function Declarations
void init_piece(Piece* p, char type, char side, char promotion);
void blank_board(B board);
void default_board(B board);
void blank_moves(M board);
void move_piece(B board, int row1, int col1, int row2, int col2);
int check_status(B board, char side);
void possible_moves(B board, M moves, int row, int col);
void valid_moves(B board, M moves, int row, int col);
