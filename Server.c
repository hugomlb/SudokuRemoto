#include "Server.h"
#define _POSIX_C_SOURCE 200112L
#include "Socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void server_init(server_t *self){
  sudoku_init(& (self -> sudoku));
  struct addrinfo hints;
  struct addrinfo *ptr;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  self -> local_addr = getaddrinfo(NULL, "http", & hints, & ptr);
  socket_init(& (self -> socket), AF_INET, SOCK_STREAM, ptr -> ai_protocol);
  socket_bindAndListen(& (self -> socket), ptr -> ai_addr, ptr -> ai_addrlen, 20);
  freeaddrinfo(ptr);
}
