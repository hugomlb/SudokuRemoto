#include "Sudoku.h"
#include <stdio.h>

#define YES 0

void sudoku_init(sudoku_t *self) {
  board_init(&(self -> board));

  for (int i = 0; i < 9; i++) {
    column_init(& (self -> columns[i]), &(self -> board), i);
    row_init(& (self -> rows[i]), &(self -> board), i);
  }
  int counter = 0;
  for (int i = 0; i < 9; i += 3) {
    for(int j = 0; j < 9; j += 3) {
      sector_init(& (self -> sectors[counter]), & (self -> board), i, j);
      counter ++;
    }
  }

}

void sudoku_addNumberIn(sudoku_t *self, int number, int row, int column) {
  board_addNumberIn(& (self -> board), number, row - 1, column - 1);
}

void sudoku_restart(sudoku_t *self) {
  board_restart(& (self -> board));
}

void sudoku_printBoard(sudoku_t *self) {
  board_print(& (self -> board));
}

void sudoku_checkRules(sudoku_t *self) {
  int onRule = YES;
  int counter = 0;
  while (onRule == YES && counter < 9) {
    onRule = row_checkRules(& (self -> rows[counter]));
    counter ++;
  }
  counter = 0;
  while (onRule == YES && counter < 9) {
    onRule = column_checkRules(& (self -> columns[counter]));
    counter ++;
  }
  counter = 0;
  while (onRule == YES && counter < 9) {
    onRule = sector_checkRules(& (self -> sectors[counter]));
    counter ++;
  }
  printf("%d\n", onRule);
}
