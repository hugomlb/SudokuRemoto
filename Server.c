#include "Server.h"
#include <stdio.h>
#define ADD_TO_HINT -1
#define NO 1
#define YES 0

void server_init(server_t *self, const char *service) {
  sudoku_init(&self -> sudoku);
  protocolS_init(&self -> protocol, service, self);
}

void server_run(server_t *self) {
  int socketclosed = 1;
  while (socketclosed != 0) {
    char buf [1];
    socketclosed = protocolS_receive(&self -> protocol, buf, 1);
    protocolS_decodeCommand(&self -> protocol, buf);
  }
}

void server_putNumberIn(server_t *self) {
  uint8_t buf[3];
  int errCheck;
  protocolS_receive(&self -> protocol,(char*) buf, 3);
  errCheck = sudoku_putNumberIn(&self -> sudoku, *buf, *(buf + 1), *(buf + 2));
  if (errCheck == ADD_TO_HINT) {
    protocolS_send(&self -> protocol, "La celda indicado no es modificable\n", 37);
  } else {
    server_get(self);
  }
}

void server_verifyRules(server_t *self) {
  int errCheck;
  errCheck = sudoku_checkRules(& self -> sudoku);
  if (errCheck == 0) {
    protocolS_send(&self -> protocol, "OK\n", 3);
  } else {
    protocolS_send(&self -> protocol, "ERROR\n", 6);
  }
}

void server_resetSudoku(server_t *self) {
  sudoku_restart(& self -> sudoku);
  server_get(self);
}

void server_get(server_t *self){
  char buf[723];
  sudoku_get(& self -> sudoku, buf);
  protocolS_send(&self -> protocol, buf, 723);
}

void server_release(server_t *self) {
  sudoku_release(&self -> sudoku);
  protocolS_release(&self -> protocol);
}
