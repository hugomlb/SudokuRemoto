#include "Client.h"
#include <stdio.h>

void client_init(client_t *self, const char *serviceName) {
  clientProtocol_init(self -> protocol, serviceName, self);
}

void client_run(client_t *self) {
  int keepRuning = 0;
  while (keepRuning == 0) {
    keepRuning = clientProtocol_executeCommand(self -> protocol);
  }
}

void client_putNumber(client_t *self, const char *buf) {
  clientProtocol_send(self -> protocol, "P", 1);
  uint8_t x[3];
  x[0] = 1;
  x[1] = 1;
  x[2] = 1;
  clientProtocol_send(self -> protocol, (char*) &x, 3);
  clientProtocol_getAnswer(self -> protocol);
}

void client_verify(client_t *self) {
  clientProtocol_send(self -> protocol, "V", 1);
  clientProtocol_getAnswer(self -> protocol);
}

void client_reset(client_t *self) {
  clientProtocol_send(self -> protocol, "R", 1);
  clientProtocol_getAnswer(self -> protocol);
}

void client_get(client_t *self) {
  clientProtocol_send(self -> protocol, "G", 1);
  clientProtocol_getAnswer(self -> protocol);
}

void client_release(client_t *self) {
  clientProtocol_release(self -> protocol);
}
