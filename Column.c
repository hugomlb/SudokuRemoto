#include "Column.h"
#include "RuleVerifier.h"
#include "Cell.h"

#define ROWSIZE 9;

void column_init(column_t *self, board_t *pBoard, int columnNum) {
  self -> columnStart = board_getCellIn(pBoard, 0, columnNum);
}

int column_checkRules(column_t *self) {
  ruleVerifier ruleVerifier;
  ruleVerifier_init(& ruleVerifier);
  for (int i = 0; i < 9; i + ROWSIZE) {
    int numToAdd = cell_getNumber(* (self -> columnStart + i));
    ruleVerifier_addNumber(& ruleVerifier, numToAdd);
  }
  return ruleVerifier_verify(& ruleVerifier);
}
