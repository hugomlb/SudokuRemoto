#include <stdio.h>
#include "Client.h"

int main(int argc, char const *argv[]) {
  client_t client;
  client_init(& client, "7777", 1);
  client_release(& client);
  return 0;
}
