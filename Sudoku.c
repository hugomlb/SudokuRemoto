#include "Sudoku.h"
#include <stdio.h>
#include <string.h>
#define YES 0
#define ROW_LIMIT "U---+---+---U---+---+---U---+---+---U\n"
#define SECTOR_LIMIT "U===========U===========U===========U\n"
void sudoku_init(sudoku_t *self) {
  board_init(& (self -> board));

  for (int i = 0; i < 9; i++) {
    column_init(& (self -> columns[i]), &(self -> board), i);
    row_init(& (self -> rows[i]), &(self -> board), i);
  }
  int counter = 0;
  for (int i = 0; i < 9; i += 3) {
    for (int j = 0; j < 9; j += 3) {
      sector_init(& (self -> sectors[counter]), & (self -> board), i, j);
      counter ++;
    }
  }
}

int sudoku_putNumberIn(sudoku_t *self, int number, int row, int column) {
  return board_addNumberIn(& (self -> board), number, row - 1, column - 1);
}

void sudoku_restart(sudoku_t *self) {
  board_restart(& (self -> board));
}

int sudoku_checkRules(sudoku_t *self) {
  int onRule = YES;
  onRule = sudoku_checkRulesOnRows(self, onRule);
  onRule = sudoku_checkRulesOnColumns(self, onRule);
  onRule = sudoku_checkRulesOnSectors(self, onRule);
  return onRule;
}

int sudoku_checkRulesOnRows(sudoku_t *self, int onRule) {
  int counter = 0;
  while (onRule == YES && counter < 9) {
    onRule = row_checkRules(& (self -> rows[counter]));
    counter ++;
  }
  return onRule;
}

int sudoku_checkRulesOnColumns(sudoku_t *self, int onRule) {
  int counter = 0;
  while (onRule == YES && counter < 9) {
    onRule = column_checkRules(& (self -> columns[counter]));
    counter ++;
  }
  return onRule;
}

int sudoku_checkRulesOnSectors(sudoku_t *self, int onRule) {
  int counter = 0;
  while (onRule == YES && counter < 9) {
    onRule = sector_checkRules(& (self -> sectors[counter]));
    counter ++;
  }
  return onRule;
}

void sudoku_get(sudoku_t *self, char* buf) {
  strncpy(buf, SECTOR_LIMIT, 39);
  for (int i = 0; i < 9; i += 3) {
    sudoku_addSectors(self, buf, i);
    strncat(buf, SECTOR_LIMIT, 39);
  }
}

void sudoku_addSectors(sudoku_t *self, char *buf, int sectorStart) {
  for (int i = 0; i < 2; i++) {
    row_get(& self -> rows[i + sectorStart], buf);
    strncat(buf, ROW_LIMIT, 39);
  }
  row_get(& self -> rows[2 + sectorStart], buf);
}

void sudoku_release(sudoku_t *self) {
  //HACER LOS RELEASE DE TODOS LOS ATRIBUTOS
}
