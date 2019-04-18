#include "drivers.h"

// UID Matches
UID BAD_UID = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
UID EMPTY_UID = {0};
UID WHITE_KING = {0x26, 0x27, 0x31, 0x42};
UID WHITE_QUEEN = {0x86, 0x28, 0x31, 0x42};
UID WHITE_KNIGHT_1 = {0xE6, 0x28, 0x31, 0x42};
UID WHITE_KNIGHT_2 = {0x56, 0xB0, 0x2F, 0x42};
UID WHITE_BISHOP_1 = {0x16, 0xB1, 0x2F, 0x42};
UID WHITE_BISHOP_2 = {0x76, 0x26, 0x31, 0x42};
UID WHITE_ROOK_1 = {0x76, 0x1A, 0x39, 0x42};
UID WHITE_ROOK_2 = {0x26, 0x3B, 0x33, 0x42};
UID WHITE_PAWN_1 = {0x76, 0xCE, 0x31, 0x42};
UID WHITE_PAWN_2 = {0x96, 0xE0, 0x33, 0x42};
UID WHITE_PAWN_3 = {0xD6, 0xCE, 0x31, 0x42};
UID WHITE_PAWN_4 = {0x36, 0xCF, 0x31, 0x42};
UID WHITE_PAWN_5 = {0xC6, 0xD3, 0x31, 0x42};
UID WHITE_PAWN_6 = {0x96, 0x3C, 0x33, 0x42};
UID WHITE_PAWN_7 = {0x36, 0x3C, 0x33, 0x42};
UID WHITE_PAWN_8 = {0x06, 0x2A, 0x31, 0x42};
UID BLACK_KING = {0xB6, 0xB2, 0x2F, 0x42};
UID BLACK_QUEEN = {0x66, 0xD3, 0x31, 0x42};
UID BLACK_KNIGHT_1 = {0xD6, 0x13, 0x2F, 0x42};
UID BLACK_KNIGHT_2 = {0x86, 0x13, 0x2F, 0x42};
UID BLACK_BISHOP_1 = {0xB6, 0xB0, 0x2F, 0x42};
UID BLACK_BISHOP_2 = {0x66, 0x1A, 0x39, 0x42};
UID BLACK_ROOK_1 = {0xC6, 0xCD, 0x31, 0x42};
UID BLACK_ROOK_2 = {0x16, 0xCE, 0x31, 0x42};
UID BLACK_PAWN_1 = {0xD6, 0xB3, 0x2F, 0x42};
UID BLACK_PAWN_2 = {0x56, 0x2A, 0x31, 0x42};
UID BLACK_PAWN_3 = {0xF6, 0xB1, 0x2F, 0x42};
UID BLACK_PAWN_4 = {0xA6, 0x29, 0x31, 0x42};
UID BLACK_PAWN_5 = {0x16, 0xB3, 0x2F, 0x42};
UID BLACK_PAWN_6 = {0x26, 0x14, 0x2F, 0x42};
UID BLACK_PAWN_7 = {0x56, 0x28, 0x31, 0x42};
UID BLACK_PAWN_8 = {0xB6, 0x27, 0x31, 0x42};

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
  if (!diffUID(BAD_UID, id)) {
    Print("Bad UID detected. Collisions?\n");
    P->side = 1;
    P->type = '?';
  }
  else if (!diffUID(EMPTY_UID, id)) {
    P->side = 0;
    P->type = 0;
  }
  else if (!diffUID(WHITE_KING, id)) {
    P->side = White;
    P->type = 'K';
  }
  else if (!diffUID(WHITE_QUEEN, id)) {
    P->side = White;
    P->type = 'Q';
  }
  else if (!diffUID(WHITE_KNIGHT_1, id)) {
    P->side = White;
    P->type = 'N';
  }
  else if (!diffUID(WHITE_BISHOP_1, id)) {
    P->side = White;
    P->type = 'B';
  }
  else if (!diffUID(WHITE_ROOK_1, id)) {
    P->side = White;
    P->type = 'R';
  }
  else if (!diffUID(WHITE_KNIGHT_2, id)) {
    P->side = White;
    P->type = 'N';
  }
  else if (!diffUID(WHITE_BISHOP_2, id)) {
    P->side = White;
    P->type = 'B';
  }
  else if (!diffUID(WHITE_ROOK_2, id)) {
    P->side = White;
    P->type = 'R';
  }
  else if (!diffUID(WHITE_PAWN_1, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_2, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_3, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_4, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_5, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_6, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_7, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(WHITE_PAWN_8, id)) {
    P->side = White;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_KING, id)) {
    P->side = Black;
    P->type = 'K';
  }
  else if (!diffUID(BLACK_QUEEN, id)) {
    P->side = Black;
    P->type = 'Q';
  }
  else if (!diffUID(BLACK_KNIGHT_1, id)) {
    P->side = Black;
    P->type = 'N';
  }
  else if (!diffUID(BLACK_BISHOP_1, id)) {
    P->side = Black;
    P->type = 'B';
  }
  else if (!diffUID(BLACK_ROOK_1, id)) {
    P->side = Black;
    P->type = 'R';
  }
  else if (!diffUID(BLACK_KNIGHT_2, id)) {
    P->side = Black;
    P->type = 'N';
  }
  else if (!diffUID(BLACK_BISHOP_2, id)) {
    P->side = Black;
    P->type = 'B';
  }
  else if (!diffUID(BLACK_ROOK_2, id)) {
    P->side = Black;
    P->type = 'R';
  }
  else if (!diffUID(BLACK_PAWN_1, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_2, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_3, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_4, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_5, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_6, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_7, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else if (!diffUID(BLACK_PAWN_8, id)) {
    P->side = Black;
    P->type = 'P';
  }
  else {
    Print("Unknown UID: ");
    printUIDArray(id, 4);
    Print("\n\n");
    P->side = 1;
    P->type = '?';
  }
}

void updateBoard(B curBoard) {
	UID id = {0};

	for (int j = 0; j < 8; j++) {
	  for (int i = 0; i < 2; i++) {
		rfidReaderAddress = i;
		rfidAntennaAddress = j;
		mfrc630_MF_scan(id);
		updateSquare(&curBoard[i][j], id);
	  }
	}
}

void printUIDArray(UID id, int size) {
  Print("{");
  for (int i = 0; i < size; i++) {
    Print("0x");
    Print("%02X", id[i]);
    if (i != 3) Print(", ");
  }
  Print("};");
}
