#ifndef _SOCKETS_H_
#define _SOCKETS_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
typedef struct {
  int fd;
} socketS_t;

void socketS_init(socketS_t *self);

int socketS_bindAndListen(socketS_t *self, const char *service);

int socketS_acceptClient(socketS_t *self);

void socketS_release(socketS_t *self);

#endif
