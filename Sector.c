#include "Sector.h"

void sector_init(sector_t *self, board_t *pBoard, int rowNum, int columnNum) {
  self -> sectorStart = board_getCellIn(pBoard, rowNum, columnNum);
}

int sector_checkRules(sector_t *self) {
  ruleVerifier ruleVerifier;
  ruleVerifier_init(& ruleVerifier);
  for (int row = 0; row < 3; row ++){
    for (int column = 0; column < 3; column ++){
      
    }
  }
}
