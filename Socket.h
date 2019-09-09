#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct {
  int fd;
} socket_t;

int socket_init(socket_t *self, const char *service, char mode);

int socket_bindAndListen(socket_t *self, const char* service);

int socket_acceptClient(socket_t *self);

int socket_connect(socket_t *self, const char* host, const char* service);

void socket_setFd(socket_t *self, int aFd);

int socket_send(socket_t *self, char *buf, int size);

int socket_receive(socket_t *self, char *buf, int size);

void socket_release(socket_t *self);

#endif
