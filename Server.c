#include "Server.h"
#define _POSIX_C_SOURCE 200112L
#include "Socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void server_init(server_t *self, const char *service) {
  sudoku_init(& (self -> sudoku));
  socket_init(& (self -> serverSocket), service, 's');
  socket_bindAndListen(& (self -> serverSocket));
}

void server_run(server_t *self) {
  self -> clientSocket = socket_acceptClient(& self -> serverSocket);
}
