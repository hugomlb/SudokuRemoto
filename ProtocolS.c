#define _POSIX_C_SOURCE  200809L
#include "ProtocolS.h"
#include "Server.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void protocolS_init(protocolS_t *self, const char *service, void *aServer) {
  char mode = 's';
  socket_init(&self -> s, service, mode);
  socket_bindAndListen(&self -> s, service);
  int fd = socket_acceptClient(& self -> s);
  socket_setFd(& self -> socket, fd);
  self -> server = aServer;
}

void protocolS_decodeCommand(protocolS_t *self, char *buf) {
  switch (buf[0]) {
    case 'P':
      server_putNumberIn(self -> server);
      break;
    case 'V':
      server_verifyRules(self -> server);
      break;
    case 'R':
      server_resetSudoku(self -> server);
      break;
    case 'G':
      server_get(self -> server);
      break;
    default:
      break;
  }
}

int protocolS_receive(protocolS_t *self, char *buf, int bytesToReceive) {
  buf[bytesToReceive - 1] = 0;
  return socket_receive(&self -> socket, buf, bytesToReceive);
}

void protocolS_send(protocolS_t *self, char *buf, int lenght) {
  int x = htonl(lenght);
  socket_send(&self -> socket, (char*) &x, 4);
  socket_send(&self -> socket, buf, lenght);
}

void protocolS_release(protocolS_t *self) {
  socket_release(&self -> socket);
  socket_release(&self -> s);
}
