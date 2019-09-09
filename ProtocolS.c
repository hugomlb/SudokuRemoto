#define _POSIX_C_SOURCE  200809L
#include "ProtocolS.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define ERROR 1
#define OK 0
#define SOCKET_CLOSED 2

void protocolS_init(protocolS_t *self, int fd) {
  socket_setFd(& self -> peerSocket, fd);
}

int protocolS_receive(protocolS_t *self, char *buf, int bytesToReceive) {
  buf[bytesToReceive - 1] = 0;
  return socket_receive(&self -> peerSocket, buf, bytesToReceive);
}

int protocolS_send(protocolS_t *self, char *buf, unsigned int lenght) {
  unsigned int x = htonl(lenght);
  int returnValue = socket_send(&self -> peerSocket, (char*) &x, 4);
  if (returnValue != ERROR && returnValue != SOCKET_CLOSED) {
    returnValue = socket_send(&self -> peerSocket, buf, lenght);
  }
  return returnValue;
}

void protocolS_release(protocolS_t *self) {
  socket_release(&self -> peerSocket);
}
