#include "drivers.h"

// UID Matches
UID EMPTY = {0};
UID W_PAWN_1 = {0xe9, 0x9f, 0xb1, 0x63};
UID W_QUEEN = {0xd9, 0x7b, 0x35, 0x63};

// Function Definitions
void blankColors(C board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j] = OFF;
    }
  }
}

int diffUID(UID uidA, UID uidB) {
	for (int i = 0; i < UID_SIZE; i++) {
		if (uidA[i] != uidB[i]) {
			return 1;
		}
	}

	return 0;
}

void updateSquare(Piece* P, UID id) {
	if (!diffUID(W_PAWN_1, id)) {
		P->side = White;
		P->type = 'P';
	}
	else if (!diffUID(W_QUEEN, id)) {
		P->side = White;
		P->type = 'Q';
	}
	else {
		P->side = 0;
		P->type = 0;
	}
}
