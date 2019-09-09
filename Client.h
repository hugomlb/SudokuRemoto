#ifndef _CLIENT_H
#define  _CLIENT_H

#include "ProtocolC.h"

typedef struct {
  protocolC_t protocol;
} client_t;

int client_init(client_t *self, const char *host, const char *service);

int client_run(client_t *self);

int client_decodeCommand(client_t *self, const char *input);

int client_executeCommand(client_t *self);

void client_putNumber(client_t *self, const char *buf);

void client_verify(client_t *self);

void client_reset(client_t *self);

void client_get(client_t *self);

void client_release(client_t *self);

#endif
