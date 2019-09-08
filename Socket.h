#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
  int fd;
} socket_t;

void socket_init(socket_t *self, const char *service, char mode);

void socket_bindAndListen(socket_t *self, const char* service);

int socket_acceptClient(socket_t *self);

void socket_connect(socket_t *self, char* host, const char* service);

void socket_setFd(socket_t *self, int aFd);

void socket_send(socket_t *self, char *buf, int size);

int socket_receive(socket_t *self, char *buf, int size);

void socket_release(socket_t *self);

#endif
