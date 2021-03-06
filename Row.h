#ifndef _ROW_H_
#define  _ROW_H_

#include "Cell.h"
#include "RuleVerifier.h"
#include "Board.h"

typedef struct {
  cell_t *rowStart;
} row_t;

void row_init(row_t *self, board_t *pBoard, int rowNum);

int row_checkRules(row_t *self, ruleVerifier_t *ruleVerifier);

void row_get(row_t *self, char* buf);

void row_makePrintableRow(row_t *self, char *buf);

void row_addSector(row_t *self, char *buf, int sectorNum);

void row_release(row_t *self);

#endif
