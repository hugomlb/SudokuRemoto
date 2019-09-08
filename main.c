#include <stdio.h>
#include "Server.h"
#include "Client.h"

int main(int argc, char const *argv[]) {
  server_t server;
  server_init(& server, "7777");
  server_run(& server);
  server_release(& server);
  /*
  if(strcmp(argv[1], "client") == 0) {
    client_t client;
    client_init(&client, "7777");
    printf("%s\n", "INIT");
    client_run(& client);
    client_release(& client);
  } else if(strcmp(argv[1], "server") == 0) {
    server_t server;
    server_init(& server, "7777");
    server_run(& server);
    server_release(& server);
  } else {
    printf("%s\n", "hola");
  }*/
  return 0;
}
