#include "Socket.h"

#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void socket_init(socket_t *self, int domain, int type, int protocol) {
  self -> fd = socket(domain, type, protocol);
}
