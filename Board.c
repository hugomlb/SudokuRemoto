#include "Board.h"
#include "Cell.h"
#include <stdio.h>
#include <string.h>
#define ASCII_CERO 48
#define ROW_SIZE 9
#define COLUMN_SIZE 9

void board_init(board_t *self) {
  FILE* boardFile;
  boardFile = fopen("board.txt", "r");
  int asciiNumber = fgetc(boardFile);
  for (int row = 0; row < ROW_SIZE; row ++) {
    for (int column = 0; column < COLUMN_SIZE; column ++) {
      cell_t cell;
      cell_init(&cell, asciiNumber - ASCII_CERO);
      self -> sudokuBoard [row][column] = cell;
      fgetc(boardFile);
      asciiNumber = fgetc(boardFile);
    }
  }
  fclose(boardFile);
}

int board_addNumberIn(board_t *self, int num, int row, int column) {
  cell_t *cellToChange = &(self -> sudokuBoard [row][column]);
  return cell_add(cellToChange, num);
}

void board_restart(board_t *self) {
  for (int row = 0; row < ROW_SIZE; row ++) {
    for (int column = 0; column < COLUMN_SIZE; column ++) {
      cell_t *cellToRestart = &(self -> sudokuBoard [row][column]);
      cell_restart(cellToRestart);
    }
  }
}

cell_t* board_getCellIn(board_t *self, int row, int column) {
  return &(self -> sudokuBoard [row][column]);
}

void board_release(board_t *self) {
  for (int row = 0; row < ROW_SIZE; row ++) {
    for (int column = 0; column < COLUMN_SIZE; column ++) {
      cell_release(& self -> sudokuBoard [row][column]);
    }
  }
}
