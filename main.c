#include "Sudoku.h"
#include <stdio.h>

#define C 9

int main(int argc, char const *argv[]) {
  sudoku_t sudoku;
  sudoku_init(& sudoku);
  sudoku_addNumberIn(& sudoku, 4, 7, 7);
  sudoku_printBoard(& sudoku);
  sudoku_addNumberIn(& sudoku, 4, 9, 9);
  sudoku_checkRules(& sudoku);
  sudoku_printBoard(& sudoku);
  sudoku_restart(& sudoku);
  sudoku_checkRules(& sudoku);
  sudoku_printBoard(& sudoku);
  return 0;
}
