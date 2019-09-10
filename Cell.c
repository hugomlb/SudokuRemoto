#include "Cell.h"
#include <stdio.h>
#include <string.h>
#define ASCII_CERO 48
#define ADD_TO_HINT -1
#define OK 0
void cell_init(cell_t *self, int cellNum) {
  self -> isClue = false;
  int myNumber = cellNum - ASCII_CERO;
  cell_add(self, myNumber);
  if (myNumber > 0) {
    self -> isClue = true;
  }
}

int cell_add(cell_t *self, int cellNum) {
  if (!(self -> isClue)) {
    self -> number = cellNum;
    return OK;
  } else {
    return ADD_TO_HINT;
  }
}

void cell_restart(cell_t *self) {
  if (!(self -> isClue)) {
    cell_add(self, 0);
  }
}

int cell_getNumber(cell_t *self) {
  return self -> number;
}

void cell_get(cell_t *self, char *buf) {
  char *espace = " ";
  char printableNum;
  char printableCell[4] = " ";
  if (self -> number == 0) {
    printableNum = *espace;
  } else {
    printableNum = (self -> number + ASCII_CERO);
  }
  strncpy(printableCell, espace, 1);
  strncat(printableCell, &printableNum, 1);
  strncat(printableCell, espace, 1);
  strncat(buf, printableCell, 3);
}

void cell_release(cell_t *self) {
  //Do Nothing
}
