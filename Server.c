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
  printf("%s\n", buf);
  //server_communicationProtocol(self, buf);
}

void server_communicationProtocol(server_t *self, char *buf) {
  switch (buf[0]) {
    case 'P':
      printf("%s\n", "Put"); //NO APTO PARA LA VERSION FINAL
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
  socket_receive(& self -> socket, buf, 1);
}

void server_putNumberIn(server_t *self, int number, int row, int column) {
  sudoku_putNumberIn(& self -> sudoku, number, row, column);
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
