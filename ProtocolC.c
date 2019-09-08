#define _POSIX_C_SOURCE  200809L
#include "ProtocolC.h"
#include "Client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void protocolC_init(protocolC_t *self, const char *servName, void *aClient) {
  socket_init(& self -> socket, servName, 'c');
  socket_connect(& self -> socket, "localhost", servName);
  self -> client = aClient;
}

int protocolC_executeCommand(protocolC_t *self) {
  char *input = NULL;
  size_t size = 0;
  int errCheck = getline(& input, & size, stdin);
  if (errCheck == -1) {
    printf("%s\n", "Error en getline");
  } else{
    errCheck = protocolC_decodeCommand(self, input);
  }
  free(input);
  return errCheck;
}

int protocolC_decodeCommand(protocolC_t *self, const char *input) {
  if(strncmp(input, "put", 3) == 0){
    client_putNumber(self -> client, input);

  } else if(strncmp(input, "verify", 6) == 0) {
    client_verify(self -> client);

  } else if (strncmp(input, "reset", 5) == 0) {
    client_reset(self -> client);

  } else if (strncmp(input, "get", 3) == 0) {
    client_get(self -> client);

  } else if(strncmp(input, "exit", 4) == 0) {
    return 1;
  }
  return 0;
}

void protocolC_receive(protocolC_t *self, char *buf, int lenght) {
  buf [lenght - 1] = 0;
  socket_receive(& self -> socket, buf, lenght);
}

void protocolC_send(protocolC_t *self, char *buf, int lenght) {
  socket_send(& self -> socket, buf, lenght);
}

void protocolC_getAnswer(protocolC_t *self) {
  int answerlenght[1];
  protocolC_receive(self, (char*) &answerlenght, 4);
  int lenght = ntohl(answerlenght[0]);
  char answer[lenght];
  protocolC_receive(self, answer, lenght);
  printf("%s", answer);
}

void protocolC_release(protocolC_t *self) {
  socket_release(& (self -> socket));
}
