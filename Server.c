#define _POSIX_C_SOURCE 200112L
#include "Server.h"
#include "Socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdio.h>
#define ADD_TO_HINT -1
#define NO 1
#define YES 0

void server_init(server_t *self, const char *service) {
  sudoku_init(& self -> sudoku);
  socket_init(& self -> socket, service, 's');
  socket_bindAndListen(& self -> socket);
}

void server_run(server_t *self) {
  socket_acceptClient(& self -> socket);
  int socketclosed = 1;
  while (socketclosed != 0) {
    char buf [1];
    socketclosed = server_receive(self, 1, buf);
    server_communicationProtocol(self, buf);
  }
}

void server_communicationProtocol(server_t *self, char *buf) {
  switch (buf[0]) {
    case 'P':
      server_putNumberIn(self); //MANDAR TABLERO SI ES VALIDO LA AGREGACION
      break;
    case 'V':
      server_verifyRules(self);
      break;
    case 'R':
      server_resetSudoku(self); //AGREGAR EL SEND DEL MENSAJE A CLIENT
      break;
    case 'G':
      server_get(self); //MANDAR MENSAJE A CLIENT
      break;
  }
}

int server_receive(server_t *self, int bytesToReceive, char* buf) {
  buf[bytesToReceive - 1] = 0;
  return socket_receive(& self -> socket, buf, bytesToReceive);
}

void server_putNumberIn(server_t *self) {
  uint8_t buf[3];
  int errCheck;
  server_receive(self, 3, (char*) buf);
  errCheck = sudoku_putNumberIn(& self -> sudoku, *buf, *(buf + 1), *(buf + 2));
  if (errCheck == ADD_TO_HINT) {
    uint8_t x = 36;
    socket_send(& self -> socket, (char*) &x, 1);
    socket_send(& self -> socket, "La celda indicado no es modificable", 36);
  }
}

void server_verifyRules(server_t *self) {
  int errCheck;
  errCheck = sudoku_checkRules(& self -> sudoku);
  if (errCheck == 0) {
    uint8_t x = 3;
    socket_send(& self -> socket, (char*) &x, 1);
    socket_send(& self -> socket, "OK", 3);
  } else {
    uint8_t x = 6;
    socket_send(& self -> socket, (char*) &x, 1);
    socket_send(& self -> socket, "ERROR", 6);
  }
}

void server_resetSudoku(server_t *self) {
  sudoku_restart(& self -> sudoku);
}

void server_get(server_t *self){
  char buf[723];
  sudoku_get(& self -> sudoku, buf);
  socket_send(& self -> socket, buf, 723);
}

void server_release(server_t *self) {
  sudoku_release(& (self -> sudoku));
  socket_release(& (self -> socket));
}
