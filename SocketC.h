#ifndef _SOCKETC_H_
#define _SOCKETC_H_

typedef struct {
  int fd;
} socketC_t;

void socketC_init(socketC_t *self);

int socketC_connect(socketC_t *self, const char* host, const char* service);

int socketC_send(socketC_t *self, char *buf, int size);

void socketC_setFd(socketC_t *self, int aFd);

int socketC_receive(socketC_t *self, char *buf, int size);

void socketC_release(socketC_t *self);

#endif
