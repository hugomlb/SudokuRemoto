#include "Row.h"
#include "RuleVerifier.h"
#include "Cell.h"

void row_init(row_t *self, board_t *pBoard, int rowNumber) {
  row_t -> rowStart = board_getCellIn(pBoard, rowNumber, 0);
}

int row_checkRules(row_t *self) {
  ruleVerifier_t ruleVerifier;
  ruleVerifier_init(& ruleVerifier);
  for (int i = 0; i < 9; i ++) {
    int numberToAdd = cell_getNumber(* (self -> rowStart + i);
    ruleVerifier_addNumber(& ruleVerifier, numberToAdd);
  }
  return ruleVerifier_verify(& ruleVerifier);
}
