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

void socketS_init(socketS_t *self) {

}

int socketS_bindAndListen(socketS_t *self, const char *service) {
  struct addrinfo hints;
  struct addrinfo *ptr, *result;
  int returnValue = OK;
  bool binded = false;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int errcheck = getaddrinfo(NULL, service, &hints, &result);
  if (errcheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errcheck));
    returnValue = ERROR;
  }
  int aFd = socket(result -> ai_family, result -> ai_socktype, result -> ai_protocol);
  if (aFd == -1) {
    printf("Error: %s\n", strerror(errno));
    returnValue = ERROR;
  }
  int val = 1;
  int errCheck = setsockopt(aFd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
   if (errCheck == -1) {
      printf("Error: %s\n", strerror(errno));
      close(aFd);
      returnValue = ERROR;
   }
  self -> fd = aFd;
  for (ptr = result; ptr != NULL && binded == false; ptr = ptr -> ai_next) {
    errcheck = bind(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
    if (errcheck == -1) {
      printf("Error: %s\n", strerror(errno));
    }
    binded = (errcheck != -1);
  }
  errcheck = listen(self -> fd, 1);
  if (errcheck == -1) {
    printf("Error: %s\n", strerror(errno));
  }
  freeaddrinfo(ptr);
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
