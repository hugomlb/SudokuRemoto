#ifndef _SERVER_H_
#define _SERVER_H_

#include "Sudoku.h"
#include "Socket.h"

typedef struct {
  sudoku_t sudoku;
  int local_addr;
  socket_t socket;
} server_t;

void server_init(server_t *self);

#endif
