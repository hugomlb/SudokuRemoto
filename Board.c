#include "Board.h"
#include "Cell.h"
#include <stdio.h>

void board_init(board_t *self) {
  for (int row = 0; row < 9; row ++) {
    for (int column = 0; column < 9; column ++) {
      cell_t cell;
      cell_init(&cell, 0);
      self -> sudokuBoard [row][column] = cell;
    }
  }
}

void board_addNumberIn(board_t *self, int num, int row, int column) {
  cell_t *cellToChange = &(self -> sudokuBoard [row][column]);
  cell_add(cellToChange, num);
}

void board_restart(board_t *self) {
  for (int row = 0; row < 9; row ++) {
    for (int column = 0; column < 9; column ++) {
      cell_t *cellToRestart = &(self -> sudokuBoard [row][column]);
      cell_restart(cellToRestart);
    }
  }
}

void board_print(board_t *self){
  printf("%s\n", "U===========U===========U===========U\n");
  for (int i=0; i<3; i++) {
    printf("%s\n", "U X | X | X U X | X | X U X | X | X U\n");
    printf("%s\n", "U---+---+---U---+---+---U---+---+---U\n");
    printf("%s\n", "U X | X | X U X | X | X U X | X | X U\n");
    printf("%s\n", "U---+---+---U---+---+---U---+---+---U\n");
    printf("%s\n", "U X | X | X U X | X | X U X | X | X U\n");
    printf("%s\n", "U===========U===========U===========U\n");
  }
}

cell_t* board_getCellIn(board_t *self, int row, int column) {
  return &(self -> sudokuBoard [row][column]);
}

void board_release(board_t *self) {
  //Do Nothing
}
