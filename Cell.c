#include "Cell.h"
#include <stdio.h>
#include <string.h>
#define ASCII_CERO 48
#define ADD_TO_HINT -1
#define OK 0

void cell_init(cell_t *self, char cellNum) {
    self -> isClue = false;
    int myNumber = cellNum - ASCII_CERO;
    cell_add(self, myNumber);
    if (myNumber > 0) {
      self -> isClue = true;
    }
    cell_setPrintableCell(self, myNumber);
}

int cell_add(cell_t *self, int cellNum) {
  int returnValue = ADD_TO_HINT;
  if (!(self -> isClue)) {
    self -> number = cellNum;
    cell_setPrintableCell(self, cellNum);
    returnValue = OK;
  }
  cell_setPrintableCell(self, cellNum);
  return returnValue;
}

void cell_setPrintableCell(cell_t *self, int cellNum) {
  char newValue;
  if (cellNum > 0) {
    newValue = cellNum + ASCII_CERO;
    strncpy(self -> printableCell, &newValue, 1);
  } else {
    strncpy(self -> printableCell, " ", 1);
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
  strncat(buf, " ", 1);
  strncat(buf, self -> printableCell, 1);
  strncat(buf, " ", 1);
}

void cell_release(cell_t *self) {
  //Do Nothing
}
