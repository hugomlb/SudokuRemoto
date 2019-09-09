#define _POSIX_C_SOURCE 200112L
#include "SocketC.h"
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

int socketC_init(socketC_t *self, const char* host, const char* service) {
  struct addrinfo hints;
  struct addrinfo *result;
  int returnValue = OK;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  int errcheck = getaddrinfo(host, service, & hints, & result);
  if (errcheck != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(errcheck));
    returnValue = ERROR;
  }
  socketC_connect(self, result);
  freeaddrinfo(result);
  return returnValue;
}

void socketC_connect(socketC_t *self, struct addrinfo *result) {
  bool conected = false;
  struct addrinfo *ptr;
  for (ptr = result; ptr != NULL && conected == false; ptr = ptr -> ai_next) {
    self -> fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (self -> fd == -1) {
         printf("Error: %s\n", strerror(errno));
      } else{
        int errcheck = connect(self -> fd, ptr -> ai_addr, ptr -> ai_addrlen);
        if (errcheck == -1) {
          printf("Error: %s\n", strerror(errno));
          close(self -> fd);
        }
        conected = (self -> fd != -1);
      }
  }
}

int socketC_send(socketC_t *self, char *buf, int size) {
  int sent = 0;
  int s = 0;
  bool socketValid = true;
  int returnValue = OK;
  while (sent < size && socketValid) {
    s = send(self -> fd, & buf[sent], size - sent, MSG_NOSIGNAL);
    if (s == 0) {
      socketValid = false;
      returnValue = SOCKET_CLOSED;
    } else if (s == -1) {
      printf("Error: %s\n", strerror(errno));
      returnValue = ERROR;
      socketValid = false;
    }
    sent += s;
  }
  return returnValue;
}

int socketC_receive(socketC_t *self, char *buf, int size) {
  int received = 0;
  int s;
  bool socketValid = true;
  int returnValue = OK;
  while (received < size && socketValid) {
    s = recv(self -> fd, & buf[received], size - received, 0);
    if (s == 0) {
      socketValid = false;
      returnValue = SOCKET_CLOSED;
    } else if (s == -1) {
      printf("Error: %s\n", strerror(errno));
      returnValue = ERROR;
      received = size +1;
    }
    received += s;
  }
  return returnValue;
}

void socketC_release(socketC_t *self) {
  shutdown(self -> fd, SHUT_RDWR);
  close(self -> fd);
}
