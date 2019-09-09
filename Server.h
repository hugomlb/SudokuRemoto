#ifndef _SERVER_H_
#define _SERVER_H_

#include "Sudoku.h"
#include "Socket.h"
#include "ProtocolS.h"

typedef struct {
  sudoku_t sudoku;
  protocolS_t protocol;
  socket_t socket;
} server_t;

int server_init(server_t *self, const char *service);

int server_run(server_t *self);

void server_decodeCommand(server_t *self, char *buf);

int server_accept(server_t *self);

void server_put(server_t *self);

void server_verifyRules(server_t *self);

void server_resetSudoku(server_t *self);

void server_get(server_t *self);

void server_release();

#endif
