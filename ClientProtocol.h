#ifndef _CLIENTPROTOCOL_H_
#define  _CLIENTPROTOCOL_H_
#include "Socket.h"

typedef struct {
  socket_t socket;
  void *client;
} clientProtocol_t;

void clientProtocol_init(clientProtocol_t *self, const char *serviceName, void *client);

int clientProtocol_executeCommand(clientProtocol_t *self);

int clientProtocol_decodeCommand(clientProtocol_t *self, const char *input);

void clientProtocol_receive(clientProtocol_t *self, char *buf, int lenght);

void clientProtocol_send(clientProtocol_t *self, char *buf, int lenght);

void clientProtocol_release(clientProtocol_t *self);
#endif
