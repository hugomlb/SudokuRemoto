#include "Sudoku.h"
#include <stdio.h>

#define C 9

int main(int argc, char const *argv[]) {
  sudoku_t sudoku;
  sudoku_init(& sudoku);
  sudoku_addNumberIn(& sudoku, 4, 1, 1);
  sudoku_addNumberIn(& sudoku, 9, 9, 9);
  sudoku_restart(& sudoku);
  return 0;
}
