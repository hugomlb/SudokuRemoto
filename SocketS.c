#define _POSIX_C_SOURCE 200112L
#include "SocketS.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define ERROR 1
#define OK 0
#define SOCKET_CLOSED 2

int socketS_init(socketS_t *self, const char *service, char mode) {
  struct addrinfo hints;
  struct addrinfo *ptr;
  int returnValue = OK;
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
    returnValue = ERROR;
  }
  int aFd = socket(ptr -> ai_family, ptr -> ai_socktype, ptr -> ai_protocol);
  if (aFd == -1) {
    printf("Error: %s\n", strerror(errno));
    returnValue = ERROR;
  }
  self -> fd = aFd;
  freeaddrinfo(ptr);
  return returnValue;
}

int socketS_bindAndListen(socketS_t *self, const char*service) {
  struct addrinfo hints;
  struct addrinfo *ptr;
  int returnValue = OK;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int errcheck = getaddrinfo(NULL, service, &hints, &ptr);
  if (errcheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errcheck));
    returnValue = ERROR;
  }
  errcheck = bind(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
  if (errcheck == -1) {
    printf("Error: %s\n", strerror(errno));
    returnValue = ERROR;
  }
  freeaddrinfo(ptr);
  errcheck = listen(self -> fd, 1);
  if (errcheck == -1) {
    printf("Error: %s\n", strerror(errno));
    returnValue = ERROR;
  }
  return returnValue;
}

int socketS_acceptClient(socketS_t *self) {
  int fd = accept(self -> fd, NULL, NULL);
  if (fd == -1) {
    printf("Error: %s\n", strerror(errno)); //CHEQUEAR BIEN QUE HACER CON ERROR
  }
  return fd;
}

void socketS_release(socketS_t *self) {
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
