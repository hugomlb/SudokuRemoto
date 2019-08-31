#include "Cell.h"
#include <stdio.h>

void cell_init(cell_t *self, int cellNum) {
    self -> clue = false;
    cell_add(self, cellNum);
    if (cellNum > 0) {
      self -> clue = true;
    }
}

void cell_add(cell_t *self, int cellNum) {
  if (!(self -> clue)) {
    self -> number = cellNum;
  }
}

void cell_restart(cell_t *self) {
  if (!(self -> clue)) {
    cell_add(self, 0);
  }
}

int cell_getNumber(cell_t *self) {
  return self -> number;
}

//****************NO APTO PARA VERSIO FINAL***************************
void cell_print(cell_t *self) {
  printf("%d", self -> number);
}
//********************************************************************

void cell_release(cell_t *self) {
  //Do Nothing
}
