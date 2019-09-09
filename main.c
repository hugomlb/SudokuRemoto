#include <stdio.h>

#include "Server.h"
#include "Client.h"
#include <string.h>

#define ERROR 1
#define OK 0
#define SOCKET_CLOSED 2
#define CMDERR "Modo no soportado, el primer parámetro debe ser server o client"
#define PARAMETERS_SERVER 3
#define PARAMETERS_CLIENT 4

int main(int argc, char const *argv[]) {
  int returnValue = OK;
  if(argc == PARAMETERS_CLIENT && strcmp(argv[1], "client") == 0) {
    client_t client;
    returnValue = client_init(&client, argv[2], argv[3]);
    if(returnValue == OK) {
      returnValue = client_run(&client);
      client_release(&client);
    }
  } else if(argc == PARAMETERS_SERVER && strcmp(argv[1], "server") == 0) {
    server_t server;
    returnValue = server_init(&server, argv[2]);
    if (returnValue == OK) {
      returnValue = server_run(&server);
      server_release(&server);
    }
  } else {
    printf("%s\n", CMDERR);
  }
  return returnValue;
}
