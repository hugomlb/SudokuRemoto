#include "Socket.h"

#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void socket_init(socket_t *self, int domain, int type, int protocol) {
  self -> fd = socket(domain, type, protocol);
}

int socket_bindAndListen(socket_t *self, const struct sockaddr *addr, socklen_t adderlen, int backlog) {
  bind(self -> fd, addr, adderlen);
  listen(self -> fd, backlog);
  return 0;
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

void socket_release(socket_t *self) {
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
