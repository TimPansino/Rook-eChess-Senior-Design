#include "drivers.h"
#include "pieces.h"
#include "debug.h"

// Function Definitions
void blankColors(C board) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      board[i][j] = OFF;
    }
  }
}

void updateLeds(C curBoard, C prevBoard) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      if (curBoard[i][j] != prevBoard[i][j]) {
        printColor(curBoard, j, i);
        prevBoard[i][j] = curBoard[i][j];
        // Update LED with driver
      }
    }
  }
}
