#include "Row.h"
#include "RuleVerifier.h"
#include "Cell.h"

void row_init(row_t *self, board_t *pBoard, int rowNum) {
  self -> rowStart = board_getCellIn(pBoard, rowNum, 0);
}

int row_checkRules(row_t *self) {
  ruleVerifier_t ruleVerifier;
  ruleVerifier_init(& ruleVerifier);
  for (int i = 0; i < 9; i ++) {
    int numToAdd = cell_getNumber(self -> rowStart + i);
    ruleVerifier_addNumber(& ruleVerifier, numToAdd);
  }
  return ruleVerifier_verify(& ruleVerifier);
}
