#include "Column.h"
#include "RuleVerifier.h"
#include "Cell.h"

#define ROWSIZE 9;

void column_init(column_t *self, board_t *pBoard, int columnNumber) {
  column_t -> columnStart = board_getCellIn(pBoard, 0, columnNumber);
}

int column_checkRules(column_t *self) {
  ruleVerifier ruleVerifier;
  ruleVerifier_init(& ruleVerifier);
  for (int i = 0; i < 9; i + ROWSIZE) {
    int numberToAdd = cell_getNumber(* (self -> columnStart + i));
    ruleVerifier_addNumber(& ruleVerifier, numberToAdd);
  }
  return ruleVerifier_verify(& ruleVerifier);
}
