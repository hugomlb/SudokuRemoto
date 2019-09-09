#define _POSIX_C_SOURCE  200809L
#include "ProtocolC.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#define OK 0
#define ERROR 1
#define SOCKET_CLOSED 2
#define EXIT 3

int protocolC_init(protocolC_t *self, const char *host, const char *service) {
  int returnValue = socket_init(&self -> socket, service, 'c');
  if  (returnValue == OK) {
    returnValue = socket_connect(&self -> socket, host, service);
  }
  return returnValue;
}

int protocolC_receive(protocolC_t *self, char *buf, int lenght) {
  buf [lenght - 1] = 0;
  return socket_receive(& self -> socket, buf, lenght);
}

int protocolC_send(protocolC_t *self, char *buf, int lenght) {
  return socket_send(& self -> socket, buf, lenght);
}

int protocolC_getAnswer(protocolC_t *self) {
  unsigned int answerlenght[1];
  int returnValue = protocolC_receive(self, (char*) &answerlenght, 4);
  if (returnValue == OK) {
    unsigned int lenght = ntohl(answerlenght[0]);
    returnValue = protocolC_receive(self, self -> answer, lenght);
    if (returnValue == OK) {
      printf("%.*s", lenght, self -> answer);
    }
  }
  return returnValue;
}

void protocolC_release(protocolC_t *self) {
  socket_release(& (self -> socket));
}
