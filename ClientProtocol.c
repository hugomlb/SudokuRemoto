#define _POSIX_C_SOURCE  200809L
#include "ClientProtocol.h"
#include "Client.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void clientProtocol_init(clientProtocol_t *self, const char *servName, void *aClient) {
  socket_init(& self -> socket, servName, 'c');
  socket_connect(& self -> socket);
  self -> client = aClient;
}

int clientProtocol_executeCommand(clientProtocol_t *self) {
  char *input = NULL;
  size_t size = 0;
  getline(& input, & size, stdin); //SI FALLA TE DEVUELVE -1 IGUAL LIBERAR MEMORIA
  int x = clientProtocol_decodeCommand(self, input);
  free(input);
  return x;
}

int clientProtocol_decodeCommand(clientProtocol_t *self, const char *input) {
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

void clientProtocol_receive(clientProtocol_t *self, char *buf, int lenght) {
  buf [lenght - 1] = 0;
  socket_receive(& self -> socket, buf, lenght);
}

void clientProtocol_send(clientProtocol_t *self, char *buf, int lenght) {
  socket_send(& self -> socket, buf, lenght);
}

void clientProtocol_release(clientProtocol_t *self){
  socket_release(& (self -> socket));
}
