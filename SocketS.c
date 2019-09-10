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

int socketS_init(socketS_t *self, const char *service) {
  struct addrinfo hints;
  struct addrinfo *rst;
  int returnValue = OK;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int errCheck = getaddrinfo(NULL, service, &hints, &rst);
  if (errCheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errCheck));
    returnValue = ERROR;
  }
  int aFd = socket(rst -> ai_family, rst -> ai_socktype, rst -> ai_protocol);
  if (aFd == -1) {
    printf("Error: %s\n", strerror(errno));
    returnValue = ERROR;
  }
  int val = 1;
  errCheck = setsockopt(aFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  if (errCheck == -1) {
     printf("Error: %s\n", strerror(errno));
     close(aFd);
     returnValue = ERROR;
  }
  self -> fd = aFd;
  freeaddrinfo(rst);
  return returnValue;
}

int socketS_bindAndListen(socketS_t *self, const char *service) {
  struct addrinfo hints;
  struct addrinfo *ptr, *rst;
  int returnValue = OK;
  bool binded = false;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int errCheck = getaddrinfo(NULL, service, &hints, &rst);
  if (errCheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errCheck));
    returnValue = ERROR;
  }
  for (ptr = rst; ptr != NULL && binded == false; ptr = ptr -> ai_next) {
    errCheck = bind(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
    if (errCheck == -1) {
      printf("Error: %s\n", strerror(errno));
      close(errCheck);
    }
    binded = (errCheck != -1);
  }
  errCheck = listen(self -> fd, 1);
  if (errCheck == -1) {
    printf("Error: %s\n", strerror(errno));
  }
  freeaddrinfo(rst);
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
