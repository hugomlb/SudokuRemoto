#ifndef _PROTOCOLS_H_
#define  _PROTOCOLS_H_

#include "Socket.h"

typedef struct {
  socket_t socket;
  void *server;
} protocolS_t;

void protocolS_init(protocolS_t *self, const char *service, void *aServer);

void protocolS_decodeCommand(protocolS_t *self, char *buf);

int protocolS_receive(protocolS_t *self, char *buf, int bytesToReceive);

void protocolS_send(protocolS_t *self, char *buf, int lenght);

void protocolS_release(protocolS_t *self);

#endif
