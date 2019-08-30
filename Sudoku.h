#ifndef _SUDOKU_H_
#define  _SUDOKU_H_

#include "Board.h"

typedef struct {
  board_t board;
} sudoku_t;

void sudoku_init(sudoku_t *self);

void sudoku_addNumberIn(sudoku_t *self, int number, int row, int column);

void sudoku_restart(sudoku_t *self);

void sudoku_printBoard(sudoku_t *self);

void sudoku_checkRules(sudoku_t *self);

void sudoku_release(sudoku_t *self);

#endif
