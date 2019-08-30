#ifndef _ROW_H_
#define  _ROW_H_

#include "Cell.h"
#include "Board.h"

typedef struct {
  cell_t *rowStart;
} row_t;

void row_init(row_t *self, board_t *pBoard, int rowNum);

int row_checkRules(row_t *self);

#endif
