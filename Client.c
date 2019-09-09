#define _POSIX_C_SOURCE  200809L
#include "Client.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define ERROR 1
#define OK 0
#define SOCKET_CLOSED 2
#define EXIT 3

int client_init(client_t *self, const char *host, const char *service) {
  return protocolC_init(&self -> protocol, host, service);
}

int client_run(client_t *self) {
  int keepRuning = OK;
  int returnValue = OK;
  while (keepRuning == OK) {
    keepRuning = client_executeCommand(self);
  }
  if (keepRuning != EXIT){
    returnValue = ERROR;
  }
  return returnValue;
}

int client_executeCommand(client_t *self) {
  char *input = NULL;
  size_t size = 0;
  int errCheck = getline(& input, & size, stdin);
  if (errCheck == -1) {
    printf("%s\n", "Error en getline");
  } else{
    errCheck = client_decodeCommand(self, input);
  }
  free(input);
  return errCheck;
}

int client_decodeCommand(client_t *self, const char *input) {
  if(strcmp(input, "put\n") == 0){
    client_putNumber(self, input);

  } else if(strcmp(input, "verify\n") == 0) {
    client_verify(self);

  } else if (strcmp(input, "reset\n") == 0) {
    client_reset(self);

  } else if (strcmp(input, "get\n") == 0) {
    client_get(self);

  } else if(strcmp(input, "exit\n") == 0) {
    return EXIT;
  }
  return 0;
}

void client_putNumber(client_t *self, const char *buf) {
  int socketState = protocolC_send(&self -> protocol, "P", 1);
  if (socketState == OK) {
    uint8_t x[3];
    x[0] = 1;
    x[1] = 1;
    x[2] = 1;
    socketState = protocolC_send(&self -> protocol, (char*) &x, 3);
    if (socketState == OK) {
      socketState = protocolC_getAnswer(&self -> protocol);
    }
  }//HACER return DEL SOCKET STATE en este y los otros
}

void client_verify(client_t *self) {
  int socketState = protocolC_send(&self -> protocol, "V", 1);
  if (socketState == OK) {
    socketState = protocolC_getAnswer(&self -> protocol);
  }
}

void client_reset(client_t *self) {
  int socketState = protocolC_send(&self -> protocol, "R", 1);
  if (socketState == OK) {
    socketState = protocolC_getAnswer(&self -> protocol);
  }
}

void client_get(client_t *self) {
  int socketState = protocolC_send(&self -> protocol, "G", 1);
  if (socketState == OK) {
    socketState = protocolC_getAnswer(&self -> protocol);
  }
}

void client_release(client_t *self) {
  protocolC_release(&self -> protocol);
}
