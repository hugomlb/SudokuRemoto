#include "Client.h"
#define _POSIX_C_SOURCE 200112L
#include "Socket.h"
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void client_init(client_t *self, const char *serviceName) {
  socket_init(& (self -> socket), serviceName, 'c');
  socket_connect(& (self -> socket));
}

void client_run(client_t *self) {
  socket_send(& self -> socket, "HOLA", 1);
}

void client_release(client_t *self) {
  socket_release(& (self -> socket));
}
