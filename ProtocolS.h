#ifndef _PROTOCOLS_H_
#define  _PROTOCOLS_H_

#include "SocketC.h"

typedef struct {
  socketC_t peerSocket;
  void *server;
} protocolS_t;

void protocolS_init(protocolS_t *self, int fd);

void protocolS_decodeCommand(protocolS_t *self, char *buf);

int protocolS_receive(protocolS_t *self, char *buf, int bytesToReceive);

int protocolS_send(protocolS_t *self, char *buf, unsigned int lenght);

void protocolS_release(protocolS_t *self);

#endif
