#ifndef _SOCKET_H_
#define _SOCKET_H_

#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
  int fd;
} socket_t;

void socket_init(socket_t *self, const char *service, char mode);

//int socket_send(socket_t *self, const void *buffer, size_t lenght);

socket_t socket_acceptClient(socket_t *self);

//**************VER PARAMETROS DE ESTA FUNCION*****************
void socket_release(socket_t *self);

int socket_connect(socket_t *self, const struct sockaddr *addr, socklen_t adderlen);

//int socket_connect(socket_t *self, const char *host, const char *service);

int socket_bindAndListen(socket_t *self, const struct sockaddr *addr, socklen_t adderlen, int backlog);

void socket_setFd(socket_t *self, int newFd);

#endif
