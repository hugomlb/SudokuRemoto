#include <stdio.h>
#include "Server.h"

int main(int argc, char const *argv[]) {
  server_t server;
  server_init(& server, "7777");
  server_run(& server);
  return 0;
}
