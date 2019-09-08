#define _POSIX_C_SOURCE 200112L
#include "Socket.h"
#include <stdbool.h>
#include <stdio.h>
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
  //CON CLIENT HAY QUE RECORRER UNA LISTA
  getaddrinfo(NULL, service, &hints, &ptr);

  int aFd = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);
  if (aFd < 0) {
    printf("%s\n", "error");
  }
  self -> fd = aFd;
  freeaddrinfo(ptr);
}

void socket_bindAndListen(socket_t *self, const char*service) {
  struct addrinfo hints;
  struct addrinfo *ptr;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, service, & hints, & ptr);
  bind(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
  freeaddrinfo(ptr);
  listen(self -> fd, 1);
}

int socket_acceptClient(socket_t *self) {
  return accept(self -> fd, NULL, NULL);
}

void socket_setFd(socket_t *self, int afd) {
  self -> fd = afd;
}

void socket_connect(socket_t *self, char* host, const char* service) {
  struct addrinfo hints;
  struct addrinfo *ptr;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  getaddrinfo(host, service, & hints, & ptr);
  connect(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
  freeaddrinfo(ptr);
}

void socket_send(socket_t *self, char *buf, int size) {
  int sent = 0;
  int s = 0;
  while (sent < size) {
    s = send(self -> fd, & buf[sent], size - sent, MSG_NOSIGNAL);
    sent += s;
  }
}

int socket_receive(socket_t *self, char *buf, int size) {
  int received = 0;
  int s = 0;
  bool socketValid = true;
  while (received < size && socketValid) {
    s = recv(self -> fd, & buf[received], size - received, 0);
    if (s == 0) {
      socketValid = false;
    }
    received += s;
  }
  return s;
}

void socket_release(socket_t *self) {
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
