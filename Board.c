#include "Board.h"
#include "Cell.h"
#include <stdio.h>

void board_init(board_t *self) {
  FILE* boardFile;
  boardFile = fopen("board.txt", "r");
  int numberOfCell = fgetc(boardFile);
  for (int row = 0; row < 9; row ++) {
    for (int column = 0; column < 9; column ++) {
      cell_t cell;
      cell_init(&cell, numberOfCell - 48);
      self -> sudokuBoard [row][column] = cell;
      fgetc(boardFile);
      numberOfCell = fgetc(boardFile);
    }
  }
  fclose(boardFile);
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

//**************** NO APTO PARA VERSION FINAL *************************
void board_print(board_t *self) {
  for (int row = 0; row < 9; row ++) {
    for (int column = 0; column < 9; column ++) {
      cell_print(& (self -> sudokuBoard[row][column]));
    }
    printf("\n");
  }
  printf("\n");
}
//********************************************************************

cell_t* board_getCellIn(board_t *self, int row, int column) {
  return &(self -> sudokuBoard [row][column]);
}

void board_release(board_t *self) {
  //Do Nothing
}
