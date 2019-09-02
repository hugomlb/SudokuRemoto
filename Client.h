#ifndef _CLIENT_H
#define  _CLIENT_H

#include "Socket.h"

typedef struct {
  socket_t socket;
  int port;
  int remoteAddress;
} client_t;

void client_init(client_t *self, const char *serviceName, int aPort);

void client_run(client_t *self);

void client_release(client_t *self);

#endif
