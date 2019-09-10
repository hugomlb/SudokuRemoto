#include "Sector.h"
#include "RuleVerifier.h"

#define ROWSIZE 9

void sector_init(sector_t *self, board_t *pBoard, int rowNum, int columnNum) {
  self -> sectorStart = board_getCellIn(pBoard, rowNum, columnNum);
}

int sector_checkRules(sector_t *self, ruleVerifier_t *ruleVerifier) {
  ruleVerifier_reset(ruleVerifier);
  for (int column = 0; column < 3; column ++) {
    for (int row = 0; row < 3; row ++){
      int displacement = row + ROWSIZE * column;
      int numToAdd = cell_getNumber(self -> sectorStart + displacement);
      ruleVerifier_addNumber(ruleVerifier, numToAdd);
    }
  }
  return ruleVerifier_verify(ruleVerifier);
}
