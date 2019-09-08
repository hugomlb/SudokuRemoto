#include "Client.h"
#include <stdio.h>

void client_init(client_t *self, const char *serviceName) {
  protocolC_init(&self -> protocol, serviceName, self);
}

void client_run(client_t *self) {
  int keepRuning = 0;
  while (keepRuning == 0) {
    keepRuning = protocolC_executeCommand(&self -> protocol);
  }
}

void client_putNumber(client_t *self, const char *buf) {
  protocolC_send(&self -> protocol, "P", 1);
  uint8_t x[3];
  x[0] = 1;
  x[1] = 1;
  x[2] = 1;
  protocolC_send(&self -> protocol, (char*) &x, 3);
  protocolC_getAnswer(&self -> protocol);
}

void client_verify(client_t *self) {
  protocolC_send(&self -> protocol, "V", 1);
  protocolC_getAnswer(&self -> protocol);
}

void client_reset(client_t *self) {
  protocolC_send(&self -> protocol, "R", 1);
  protocolC_getAnswer(&self -> protocol);
}

void client_get(client_t *self) {
  protocolC_send(&self -> protocol, "G", 1);
  protocolC_getAnswer(&self -> protocol);
}

void client_release(client_t *self) {
  protocolC_release(&self -> protocol);
}
