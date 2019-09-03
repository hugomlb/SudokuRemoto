#include "Socket.h"

#define _POSIX_C_SOURCE 200112L
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void socket_init(socket_t *self, const char *service, char mode) {
  struct addrinfo hints;
  struct addrinfo *ptr;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if (mode == 'c') {
      hints.ai_flags = 0;
  } else if (mode == 's') {
      hints.ai_flags = AI_PASSIVE;
  }
  //CON CLIENT HAY QUE RECORRER UNA LISTA EH
  getaddrinfo(NULL, service, & hints, & ptr);
  self -> fd = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);
  self -> ptr = ptr;
}

void socket_bindAndListen(socket_t *self) {
  bind(self -> fd, self -> ptr -> ai_addr, self -> ptr -> ai_addrlen);
  listen(self -> fd, 1);
}

void socket_setFd(socket_t *self, int newFd) {
  self -> fd = newFd;
}

socket_t socket_acceptClient(socket_t *self) {
  int clientfd = accept(self -> fd, NULL, NULL);
  socket_t clientSocket;
  socket_setFd(& clientSocket, clientfd);
  return clientSocket;
}

int socket_connect(socket_t *self, const struct sockaddr *addr, socklen_t adderlen) {
  int i = connect(self -> fd, addr, adderlen);
  return i;
}

void socket_release(socket_t *self) {
  freeaddrinfo(self -> ptr);
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
