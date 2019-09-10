#include "Row.h"
#include "RuleVerifier.h"
#include "Cell.h"
#include <string.h>

#define ROWSIZE 9

void row_init(row_t *self, board_t *pBoard, int rowNum) {
  self -> rowStart = board_getCellIn(pBoard, rowNum, 0);
}

int row_checkRules(row_t *self, ruleVerifier_t *ruleVerifier) {
  ruleVerifier_reset(ruleVerifier);
  for (int i = 0; i < ROWSIZE; i ++) {
    int numToAdd = cell_getNumber(self -> rowStart + i);
    ruleVerifier_addNumber(ruleVerifier, numToAdd);
  }
  return ruleVerifier_verify(ruleVerifier);
}

void row_get(row_t *self, char *buf) {
  char printbleRow[39] = " ";
  row_makePrintableRow(self, printbleRow);
  strncat(buf, printbleRow, 38);
}

void row_makePrintableRow(row_t *self, char *buf) {
  strncpy(buf, "U", 1);
  for (int i = 0; i < 9; i += 3) {
    row_addSector(self, buf, i);
    strncat(buf, "U", 1);
  }
  strncat(buf, "\n", 1);
}

void row_addSector(row_t *self, char *buf, int sectorNum) {
  for (int i = 0; i < 2; i ++) {
    cell_get(self -> rowStart + i + sectorNum, buf);
    strncat(buf, "|", 1);
  }
  cell_get(self -> rowStart + 2 + sectorNum, buf);
}

void row_release(row_t *self) {
  //DO NOTHING
}
