#include "Cell.h"

void cell_init(cell_t *self, int cellValue) {
    self -> clue = false;
    cell_add(self, cellValue);
    if (cellValue > 0) {
      self -> clue = true;
    }
}

void cell_add(cell_t *self, int cellValue) {
  if (!(self -> clue)) {
    self -> value = cellValue;
  }
}

void cell_restart(cell_t *self) {
  if (!(self -> clue)) {
    cell_add(self, 0);
  }
}

void cell_release(cell_t *self){
  //Do Nothing
}
