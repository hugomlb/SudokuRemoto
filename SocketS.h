#ifndef _SOCKETS_H_
#define _SOCKETS_H_

typedef struct {
  int fd;
} socketS_t;

int socketS_init(socketS_t *self, const char *service, char mode);

int socketS_bindAndListen(socketS_t *self, const char* service);

int socketS_acceptClient(socketS_t *self);

void socketS_release(socketS_t *self);

#endif
