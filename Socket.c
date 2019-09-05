#define _POSIX_C_SOURCE 200112L
#include "Socket.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdio.h>

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
  //CON CLIENT HAY QUE RECORRER UNA LISTA
  getaddrinfo(NULL, service, & hints, & ptr);
  self -> fd = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);
  self -> ptr = ptr;
}

void socket_bindAndListen(socket_t *self) {
  bind(self -> fd, self -> ptr -> ai_addr, self -> ptr -> ai_addrlen);
  listen(self -> fd, 1);
}

void socket_acceptClient(socket_t *self) {
  self -> fd = accept(self -> fd, NULL, NULL);
}

void socket_connect(socket_t *self) {
  connect(self -> fd, self -> ptr -> ai_addr, self -> ptr -> ai_addrlen);
}

void socket_send(socket_t *self, char *buf, int size) {
  int sent = 0;
  int s = 0;
  while (sent < size) {
    s = send(self -> fd, & buf[sent], size - sent, MSG_NOSIGNAL);
    sent += s;
  }
}

void socket_receive(socket_t *self, char *buf, int size) {
  int received = 0;
  int s;
  while (received < size) {
    s = recv(self -> fd, & buf[received], size - received, 0);
    received += s;
  }
}

void socket_release(socket_t *self) {
  freeaddrinfo(self -> ptr);
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
