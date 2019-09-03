#ifndef _SERVER_H_
#define _SERVER_H_

#include "Sudoku.h"
#include "Socket.h"

typedef struct {
  sudoku_t sudoku;
  int localAddress;
  socket_t socket;
} server_t;

void server_init(server_t *self, const char *service);

void server_run(server_t *self);

void server_communicationProtocol(server_t *self, char *buf);

void server_receive(server_t *self, int bytesToReceive, char *buf);

void server_putNumberIn(server_t *self, int number, int row, int column);

void server_verifyRules(server_t *self);

void server_resetSudoku(server_t *self);

void server_get(server_t *self);

void server_release();

#endif
