#include "Host.h"
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void host_init(host_t *self){
  sudoku_init(& (self -> sudoku));
  struct addrinfo hints;
  struct addrinfo *ptr;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  self -> local_addr = getaddrinfo(NULL, "http", & hints, & ptr);
  freeaddrinfo(ptr);
}
