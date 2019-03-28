#include "drivers.h"
#include "pieces.h"

// UID Matches
UID W_PAWN_1 = {0xe9, 0x9f, 0xb1, 0x63};

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
