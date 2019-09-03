#ifndef _SUDOKU_H_
#define  _SUDOKU_H_

#include "Board.h"
#include "Row.h"
#include "Column.h"
#include "Sector.h"

typedef struct {
  board_t board;
  row_t rows[9];
  column_t columns[9];
  sector_t sectors[9];
} sudoku_t;

void sudoku_init(sudoku_t *self);

void sudoku_putNumberIn(sudoku_t *self, int number, int row, int column);

void sudoku_restart(sudoku_t *self);

void sudoku_printBoard(sudoku_t *self);

void sudoku_checkRules(sudoku_t *self);

int sudoku_checkRulesOnRows(sudoku_t *self, int onRule);

int sudoku_checkRulesOnColumns(sudoku_t *self, int onRule);

int sudoku_checkRulesOnSectors(sudoku_t *self, int onRule);

void sudoku_release(sudoku_t *self);

#endif
