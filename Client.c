#define _POSIX_C_SOURCE  200809L
#include "Client.h"
#include "Socket.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void client_init(client_t *self, const char *serviceName) {
  socket_init(& (self -> socket), serviceName, 'c');
  socket_connect(& (self -> socket));
}

void client_run(client_t *self) {
  client_getCommand(self);
/*  while(strcmp(input, "exit") == 0){
    uint8_t x[3];
    x[0] = 1;
    x[1] = 1;
    x[2] = 1;
    socket_send(& self -> socket, (char*) &x, 3);
  }*/
//  int x = 5;
//  x = htonl(x);
//  char* y = (char*)&x;
//  printf("%d\n", *y);
//  printf("%d\n", *(y+3));
}

void client_getCommand(client_t *self) {
  char *input = NULL;
  size_t size = 0;
  getline(& input, & size, stdin); //SI FALLA TE DEVUELVE -1 IGUAL LIBERAR MEMORIA
  client_decodeCommand(self, input);
  free(input);
}

void client_decodeCommand(client_t *self, const char* input) {
  if(strncmp(input, "put", 3) == 0){
    printf("%s\n", "put");
  } else if(strncmp(input, "verify", 6) == 0) {
    socket_send(& self -> socket, "V", 1);
    printf("%s\n", "verify");
  } else if (strncmp(input, "reset", 5) == 0) {
    socket_send(& self -> socket, "R", 1);
    printf("%s\n", "reset");
  } else if (strncmp(input, "get", 3) == 0) {
    socket_send(& self -> socket, "G", 1);
    printf("%s\n", "get");
  } else if(strncmp(input, "exit", 4) == 0) {
    printf("%s\n", "exit");
  } else {
    printf("%s\n", "no un comando");
  }
}

void client_release(client_t *self) {
  socket_release(& (self -> socket));
}
