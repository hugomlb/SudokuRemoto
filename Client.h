#ifndef _CLIENT_H
#define  _CLIENT_H

#include "Socket.h"
#include "ClientProtocol.h"

typedef struct {
  clientProtocol_t protocol;
} client_t;

void client_init(client_t *self, const char *serviceName);

void client_run(client_t *self);

void client_putNumber(client_t *self, const char *buf);

void client_verify(client_t *self);

void client_reset(client_t *self);

void client_get(client_t *self);

void client_release(client_t *self);

#endif
