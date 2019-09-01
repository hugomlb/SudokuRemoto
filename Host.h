#ifndef _HOST_H_
#define _HOST_H_

#include "Sudoku.h"

typedef struct {
  sudoku_t sudoku;
  int local_addr;
} host_t;

void host_init(host_t *self);

#endif
