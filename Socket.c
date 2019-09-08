#define _POSIX_C_SOURCE 200112L
#include "Socket.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

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
  //CON CLIENT HAY QUE RECORRER UNA LISTA, PARA HACER EL BIND EN EL SERVER TAMB
  int errcheck = getaddrinfo(NULL, service, &hints, &ptr);
  if (errcheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errcheck));
  }
  int aFd = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);
  if (aFd == -1) {
    printf("Error: %s\n", strerror(errno));
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
  int errcheck = getaddrinfo(NULL, service, &hints, &ptr);
  if (errcheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errcheck));
  }
  errcheck = bind(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
  if (errcheck == -1) {
    printf("Error: %s\n", strerror(errno));
  }
  freeaddrinfo(ptr);
  errcheck = listen(self -> fd, 1);
  if (errcheck == -1) {
    printf("Error: %s\n", strerror(errno));
  }
}

int socket_acceptClient(socket_t *self) {
  int fd = accept(self -> fd, NULL, NULL);
  if (fd == -1) {
    printf("Error: %s\n", strerror(errno));
  }
  return fd;
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
  int errcheck = getaddrinfo(host, service, & hints, & ptr);
  if (errcheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errcheck));
  }
  errcheck = connect(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
  if (errcheck == -1) {
    printf("Error: %s\n", strerror(errno));
  }
  freeaddrinfo(ptr);
}

void socket_send(socket_t *self, char *buf, int size) {
  int sent = 0;
  int s = 0;
  while (sent < size) {
    s = send(self -> fd, & buf[sent], size - sent, MSG_NOSIGNAL);
    if (s == -1) {
      printf("Error: %s\n", strerror(errno));
    }
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
    } else if (s == -1) {
      printf("Error: %s\n", strerror(errno));
    }
    received += s;
  }
  return s;
}

void socket_release(socket_t *self) {
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
