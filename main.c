#include <stdio.h>
#include "Server.h"
#include "Sudoku.h"
int main(int argc, char const *argv[]) {

  server_t server;
  server_init(& server, "7777");
  server_run(& server);
  server_release(& server);

  return 0;
}
