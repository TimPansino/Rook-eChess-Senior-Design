#include "drivers.h"
#include "mfrc630.h"

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

// Address Translation Tables
int LEDTranslationTable[8][8] = {{0, 1, 2, 3, 44, 40, 36, 32}, {4, 5, 6, 7, 45, 41, 37, 33}, {8, 9, 10, 11, 46, 42, 38, 34}, {12, 13, 14, 15, 47, 43, 39, 35}, {19, 23, 27, 31, 63, 62, 61, 60}, {18, 22, 26, 30, 59, 58, 57, 56}, {17, 21, 25, 29, 55, 54, 53, 52}, {16, 20, 24, 28, 51, 50, 49, 48}};
int RFIDTranslationTable[8][8] = {{41, 49, 54, 53, 14, 22, 9, 10}, {40, 48, 62, 61, 15, 23, 1, 2}, {43, 51, 38, 37, 12, 20, 25, 26}, {42, 50, 46, 45, 13, 21, 17, 18}, {33, 57, 55, 52, 6, 30, 8, 11}, {32, 56, 63, 60, 7, 31, 0, 3}, {35, 59, 39, 36, 4, 28, 24, 27}, {34, 58, 47, 44, 5, 29, 16, 19}};

// Function Definitions
void blankColors(C board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j] = COLOR_OFF;
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
  int addr;
  int a, b;

	for (int j = 0; j < 8; j++) { // Antennas
	  for (int i = 0; i < 8; i++) { // Readers
  		rfidReaderAddress = i;
  		rfidAntennaAddress = j;
  		mfrc630_MF_scan(id);

		addr = RFIDTranslationTable[j][i];
		a = addr >> 3;
		b = addr & 7;
  		updateSquare(&curBoard[b][a], id);

  		if (diffUID(EMPTY_UID, id)) {
  			Print("%c%d: %d\n", 'A' + i, 8 - j, addr);
  		}
	  }
	}

	return;
}

void updateColors(C color) {
  int addr;

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      addr = LEDTranslationTable[j][i];
      updateLED(addr, color[i][j]);
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
