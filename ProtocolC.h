#ifndef _PROTOCOLC_H_
#define  _PROTOCOLC_H_
#include "Socket.h"

typedef struct {
  socket_t socket;
  void *client;
} protocolC_t;

void protocolC_init(protocolC_t *self, const char *servName, void *aClient);

int protocolC_executeCommand(protocolC_t *self);

int protocolC_decodeCommand(protocolC_t *self, const char *input);

void protocolC_receive(protocolC_t *self, char *buf, int lenght);

void protocolC_send(protocolC_t *self, char *buf, int lenght);

void protocolC_getAnswer(protocolC_t *self);

void protocolC_release(protocolC_t *self);

#endif
