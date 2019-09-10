#define _POSIX_C_SOURCE  200809L
#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ERROR 1
#define OK 0
#define SOCKET_CLOSED 2
#define EXIT 3
#define NUM_OUT_OF_RANGE "Error en el valor ingresado. Rango soportado: [1,9]\n"

int client_init(client_t *self, const char *host, const char *service) {
  return protocolC_init(&self -> protocol, host, service);
}

int client_run(client_t *self) {
  int keepRuning = OK;
  int returnValue = OK;
  while (keepRuning == OK) {
    keepRuning = client_executeCommand(self);
  }
  if (keepRuning != EXIT){
    returnValue = ERROR;
  }
  return returnValue;
}

int client_executeCommand(client_t *self) {
  char *input = NULL;
  size_t size = 0;
  int errCheck = getline(& input, & size, stdin);
  if (feof(stdin)) {
    errCheck = EXIT;
  } else{
    errCheck = client_decodeCommand(self, input);
  }
  free(input);
  return errCheck;
}

int client_decodeCommand(client_t *self, char *input) {
  if (strncmp(input, "put", 3) == 0) {
    client_decodePut(self, input);

  } else if (strcmp(input, "verify\n") == 0) {
    client_verify(self);

  } else if (strcmp(input, "reset\n") == 0) {
    client_reset(self);

  } else if (strcmp(input, "get\n") == 0) {
    client_get(self);

  } else if (strcmp(input, "exit\n") == 0) {
    return EXIT;
  }
  return 0;
}

void client_decodePut(client_t *self, char *input) {
  char *put, *numberToAdd, *in, *rowAndColumn;
  char * saveptr;
  put = strtok_r(input, " ", &saveptr);
  numberToAdd = strtok_r(NULL, " ", &saveptr);
  in = strtok_r(NULL, " ", &saveptr);
  rowAndColumn = strtok_r(NULL, " ", &saveptr);
  if ((strcmp(put, "put") == 0) && strcmp(in, "in") == 0) {
    put = strtok_r(NULL, " ", &saveptr);
    if (put == NULL) {
      put = strtok_r(rowAndColumn, ",", &saveptr);
      put = strtok_r(NULL, "\n", &saveptr);
      client_putNumber(self, numberToAdd, rowAndColumn, put);
    }
  }
}

void client_putNumber(client_t *self, char *number, char *row, char *column) {
  int socketState = protocolC_send(&self -> protocol, "P", 1);
  int numbersInRange = OK;
  numbersInRange = client_checkRange(self, number, numbersInRange);
  if (numbersInRange == ERROR) {
    fprintf(stderr, "%s", NUM_OUT_OF_RANGE);
  } else {
    numbersInRange = client_checkRange(self, row, numbersInRange);
    numbersInRange = client_checkRange(self, column, numbersInRange);
    if (numbersInRange == ERROR) {
      fprintf(stderr, "%s", "Error en los índices. Rango soportado: [1,9]\n");
    }
  }
  if ((socketState == OK) && (numbersInRange == OK)) {
    uint8_t x[3];
    x[0] = atoi(number);
    x[1] = atoi(row);
    x[2] = atoi(column);
    socketState = protocolC_send(&self -> protocol, (char*) &x, 3);
    if (socketState == OK) {
      socketState = protocolC_getAnswer(&self -> protocol);
    }
  }//HACER return DEL SOCKET STATE en este y los otros
}

int client_checkRange(client_t *self, char *number, int prevNumbers) {
  int returnValue = ERROR;
  if (prevNumbers == OK) {
    int numberToCheck = atoi(number);
    if ((numberToCheck >= 1) && (numberToCheck <= 9)) {
      returnValue = OK;
    }

  }
  return returnValue;
}

void client_verify(client_t *self) {
  int socketState = protocolC_send(&self -> protocol, "V", 1);
  if (socketState == OK) {
    socketState = protocolC_getAnswer(&self -> protocol);
  }
}

void client_reset(client_t *self) {
  int socketState = protocolC_send(&self -> protocol, "R", 1);
  if (socketState == OK) {
    socketState = protocolC_getAnswer(&self -> protocol);
  }
}

void client_get(client_t *self) {
  int socketState = protocolC_send(&self -> protocol, "G", 1);
  if (socketState == OK) {
    socketState = protocolC_getAnswer(&self -> protocol);
  }
}

void client_release(client_t *self) {
  protocolC_release(&self -> protocol);
}
