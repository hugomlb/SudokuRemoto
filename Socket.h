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

void socket_init(socket_t *self, int domain, int type, int protocol);

//int socket_send(socket_t *self, const void *buffer, size_t lenght);

//***************VER PARAMETROS DE ESTA FUNCION****************
int socket_receive();

//**************VER PARAMETROS DE ESTA FUNCION*****************
void socket_release();

int socket_connect(socket_t *self, const char *host, const char *service);

int socket_bindAndListen(socket_t *self, const struct sockaddr *addr, socklen_t adderlen, int backlog);

#endif
