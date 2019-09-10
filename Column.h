#ifndef _COLUMN_H_
#define  _COLUMN_H_

#include "Cell.h"
#include "RuleVerifier.h"
#include "Board.h"

typedef struct {
  cell_t *columnStart;
} column_t;

void column_init(column_t *self, board_t *pBoard, int columnNum);

int column_checkRules(column_t *self, ruleVerifier_t *ruleVerifier);

#endif
