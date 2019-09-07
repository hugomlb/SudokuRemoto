#include "Client.h"
#include <stdio.h>

void client_init(client_t *self, const char *serviceName) {
  clientProtocol_init(self -> protocol, serviceName, self);
}

void client_run(client_t *self) {
  int keepRuning = 0;
  while (keepRuning == 0) {
    keepRuning = clientProtocol_executeCommand(self -> protocol);
  }
//  int x = 5;
//  x = htonl(x);
//  char* y = (char*)&x;
//  printf("%d\n", *y);
//  printf("%d\n", *(y+3));
}

void client_putNumber(client_t *self, const char *buf) {
  clientProtocol_send(self -> protocol, "P", 1);
  uint8_t x[3];
  x[0] = 1;
  x[1] = 1;
  x[2] = 1;
  clientProtocol_send(self -> protocol, (char*) &x, 3);
  char answerlenght[1];
  clientProtocol_receive(self -> protocol, answerlenght, 1);
  char answer[answerlenght[0]];
  clientProtocol_receive(self -> protocol, answer, answerlenght[0]);
  printf("%s", answer);
}

void client_verify(client_t *self) {
  clientProtocol_send(self -> protocol, "V", 1);
  char answerlenght[1];
  clientProtocol_receive(self -> protocol, answerlenght, 1);
  char answer[answerlenght[0]];
  clientProtocol_receive(self -> protocol, answer, answerlenght[0]);
  printf("%s\n", answer);
}

void client_reset(client_t *self) {
  clientProtocol_send(self -> protocol, "R", 1);

}

void client_get(client_t *self) {
  clientProtocol_send(self -> protocol, "G", 1);
  char answer[723];
  clientProtocol_receive(self -> protocol, answer, 723);
  printf("%s", answer);
}

void client_release(client_t *self) {
  clientProtocol_release(self -> protocol);
}
