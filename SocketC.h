#ifndef _SOCKETC_H_
#define  _SOCKETC_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
typedef struct {
  int fd;
} socketC_t;

int socketC_init(socketC_t *self, const char* host, const char* service);

void socketC_connect(socketC_t *self, struct addrinfo *ptr);

int socketC_send(socketC_t *self, char *buf, int size);

int socketC_receive(socketC_t *self, char *buf, int size);

void socketC_release(socketC_t *self);

#endif
