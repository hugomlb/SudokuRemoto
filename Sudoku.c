#include "Sudoku.h"

void sudoku_init(sudoku_t *self) {
  board_init(&(self -> board));

  for (int i = 0; i < 9; i++) {
    column_init(& (self -> columns[i]));
    row_init(& (self -> rows[i]));
  }

  for (int i = 0; i < 9; i + 3) {
    for(int j = 0; j < 9; j + 3) {
      sector_init(& (self -> sectors), & (self -> board), i, j);
    }
  }

}

void sudoku_addNumberIn(sudoku_t *self, int number, int row, int column) {
  board_addNumberIn(& (self -> board), number, row + 1, column + 1);
}

void sudoku_restart(sudoku_t *self) {
  board_restart(& (self -> board));
}

void sudoku_printBoard(sudoku_t *self) {
  board_print(& (self -> board));
}

void sudoku_checkRules(sudoku_t *self) {
  
}
