#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>

typedef struct {
  int value;
  bool clue;
} cell_t;

void cell_init(cell_t *self, int cellValue);

void cell_add(cell_t *self, int cellValue);

void cell_restart(cell_t *self);

void cell_release(cell_t *self);

int cell_getNumber(cell_t *self);

#endif
