#include "Server.h"
#include <stdio.h>
#include <stdint.h>

#define ERROR 1
#define OK 0
#define SOCKET_CLOSED 2
#define ADD_TO_HINT -1

int server_init(server_t *self, const char *service) {
  sudoku_init(&self -> sudoku);
  socketS_init(&self -> socket);
  int returnValue = socketS_bindAndListen(&self -> socket, service);
  return returnValue;
}

int server_run(server_t *self) {
  int socketState = OK;
  socketState = server_accept(self);
  while (socketState == OK) {
    char buf [1];
    socketState = protocolS_receive(&self -> protocol, buf, 1);
    if (socketState == OK) {
      server_decodeCommand(self, buf);
    }
  }
  server_release(self);
  return socketState;
}

void server_decodeCommand(server_t *self, char *buf) {
  switch (buf[0]) {
    case 'P':
      server_put(self);
      break;
    case 'V':
      server_verifyRules(self);
      break;
    case 'R':
      server_resetSudoku(self);
      break;
    case 'G':
      server_get(self);
      break;
    default:
      break;
  }
}

int server_accept(server_t *self) {
  int returnValue = OK;
  int fd = socketS_acceptClient(&self -> socket);
  if (fd > 0) {
    protocolS_init(&self -> protocol, fd);
  } else {
    returnValue = ERROR;
  }
  return returnValue;
}

void server_put(server_t *self) {
  uint8_t buf[3];
  int answ;
  int returnValue = protocolS_receive(&self -> protocol,(char*) buf, 3);
  if ((returnValue != SOCKET_CLOSED) || (returnValue != ERROR)) {
    answ = sudoku_putNumberIn(&self -> sudoku, *buf, *(buf + 1), *(buf + 2));
    if (answ == ADD_TO_HINT) {
      protocolS_send(&self -> protocol, "La celda indicado no es modificable\n", 37);
    } else {
      server_get(self);
    }
  }//VER SI DEVOLVER ERROR
}

void server_verifyRules(server_t *self) {
  int errCheck;
  errCheck = sudoku_checkRules(& self -> sudoku);
  if (errCheck == 0) {
    protocolS_send(&self -> protocol, "OK\n", 3);
  } else {
    protocolS_send(&self -> protocol, "ERROR\n", 6);
  }
}  //ATRAPAR ERRORES DE SEND

void server_resetSudoku(server_t *self) {
  sudoku_restart(& self -> sudoku);
  server_get(self);
}

void server_get(server_t *self){
  char buf[723];
  sudoku_get(& self -> sudoku, buf);
  protocolS_send(&self -> protocol, buf, 723);
} //ATRAPAR ERROR DE SEND

void server_release(server_t *self) {
  sudoku_release(&self -> sudoku);
  protocolS_release(&self -> protocol);
  socketS_release(&self -> socket);
}
