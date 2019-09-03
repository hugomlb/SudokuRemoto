#include "Server.h"
#define _POSIX_C_SOURCE 200112L
#include "Socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdio.h>

void server_init(server_t *self, const char *service) {
  sudoku_init(& self -> sudoku);
  socket_init(& self -> socket, service, 's');
  socket_bindAndListen(& self -> socket);
}

void server_run(server_t *self) {
  socket_acceptClient(& self -> socket);
  char buf [1];
  server_receive(self, 1, buf);
  server_communicationProtocol(self, buf);
}

void server_communicationProtocol(server_t *self, char *buf) {
  switch (buf[0]) {
    case 'P':
      server_putNumberIn(self); //AGEGAR EL SEND A CLIENT
      break;
    case 'V':
      server_verifyRules(self); //AGREGAR EL SEND DEL MENSAJE A CLIENT
      break;
    case 'R':
      server_resetSudoku(self); //AGREGAR EL SEND DEL MENSAJE A CLIENT
      break;
    case 'G':
      server_get(self); //MANDAR MENSAJE A CLIENT
      break;
  }
}

void server_receive(server_t *self, int bytesToReceive, char* buf) {
  buf[bytesToReceive - 1] = 0;
  socket_receive(& self -> socket, buf, bytesToReceive);
}

void server_putNumberIn(server_t *self) {
  uint8_t buf[3];
  server_receive(self, 3, (char*) buf);
  sudoku_putNumberIn(& self -> sudoku, *buf, *(buf + 1), *(buf + 2));
}

void server_verifyRules(server_t *self) {
  sudoku_checkRules(& self -> sudoku);
}

void server_resetSudoku(server_t *self) {
  sudoku_restart(& self -> sudoku);
}

void server_get(server_t *self){
  sudoku_printBoard(& self -> sudoku); //NO APTO PARA LA VERSION FINAL
}

void server_release(server_t *self) {
  sudoku_release(& (self -> sudoku));
  socket_release(& (self -> socket));
}
