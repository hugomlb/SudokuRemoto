#ifndef _COLUMN_H_
#define  _COLUMN_H_

typedef struct {
  cell_t *columnStart;
} column_t;

void column_init(column_t *self, board_t *pBoard, int columnNum);

int column_checkRules(column_t *self);

#endif
