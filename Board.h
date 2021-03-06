#ifndef _BOARD_H_
#define _BOARD_H_

#include "Cell.h"

typedef struct {
  cell_t sudokuBoard[9][9];
} board_t;

void board_init(board_t *self);

int board_addNumberIn(board_t *self, int num, int row, int column);

void board_restart(board_t *self);

void board_print(board_t *self);

void board_get(board_t *self, char* buf);

cell_t* board_getCellIn(board_t *self, int row, int column);

void board_release(board_t *self);

#endif
