#ifndef _SERVER_H_
#define _SERVER_H_

#include "Sudoku.h"
#include "Socket.h"
#include "ProtocolS.h"

typedef struct {
  sudoku_t sudoku;
  protocolS_t *protocol;
} server_t;

void server_init(server_t *self, const char *service);

void server_run(server_t *self);

void server_putNumberIn(server_t *self);

void server_verifyRules(server_t *self);

void server_resetSudoku(server_t *self);

void server_get(server_t *self);

void server_release();

#endif
