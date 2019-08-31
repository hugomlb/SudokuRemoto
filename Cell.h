#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>

typedef struct {
  int number;
  bool clue;
} cell_t;

void cell_init(cell_t *self, int cellNum);

void cell_add(cell_t *self, int cellNum);

void cell_restart(cell_t *self);

void cell_release(cell_t *self);

int cell_getNumber(cell_t *self);

void cell_print(cell_t *self);

#endif
