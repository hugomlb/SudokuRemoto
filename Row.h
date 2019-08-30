#ifndef _ROW_H_
#define  _ROW_H_

typedef struct {
  cell_t *rowStart;
} row_t;

void row_init(row_t *self, board_t *pBoard, int rowNumber);

int row_checkRules(row_t *self);

#endif
