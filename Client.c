#define _POSIX_C_SOURCE  200809L
#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define ERROR 1
#define OK 0
#define NOT_A_COMMAND 0
#define SOCKET_CLOSED 2
#define EXIT 3
#define TRUE 4
#define FALSE 5
#define NUM_OUT_OF_RANGE "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define INDEX_OUT_OF_RANGE "Error en los índices. Rango soportado: [1,9]\n"

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
  int returnValue = NOT_A_COMMAND;
  if (strcmp(input, "verify\n") == 0) {
    returnValue = protocolC_sendCmmd(&self -> protocol, "V", TRUE, 1);

  } else if (strcmp(input, "reset\n") == 0) {
    returnValue = protocolC_sendCmmd(&self -> protocol, "R", TRUE, 1);

  } else if (strcmp(input, "get\n") == 0) {
    returnValue = protocolC_sendCmmd(&self -> protocol, "G", TRUE, 1);

  } else if (strcmp(input, "exit\n") == 0) {
    returnValue = EXIT;
  } else {
    client_decodePut(self, input);
  }
  return returnValue;
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
  int numbersInRange = client_checkNumbers(self, number, row, column);
  if (numbersInRange == OK) {
    int socketState = protocolC_sendCmmd(&self -> protocol, "P", FALSE, 1);
    if (socketState == OK) {
      uint8_t snd[3];
      snd[0] = atoi(number);
      snd[1] = atoi(row);
      snd[2] = atoi(column);
      socketState = protocolC_sendCmmd(&self -> protocol, (char*) snd, TRUE, 3);
    }
  }
}

int client_checkNumbers(client_t *self, char *number, char *row, char *column) {
  int numbersInRange = OK;
  numbersInRange = client_checkNumberRange(self, number, numbersInRange);
  if (numbersInRange == ERROR) {
    fprintf(stderr, "%s", NUM_OUT_OF_RANGE);
  } else {
    numbersInRange = client_checkNumberRange(self, row, numbersInRange);
    numbersInRange = client_checkNumberRange(self, column, numbersInRange);
    if (numbersInRange == ERROR) {
      fprintf(stderr, "%s", INDEX_OUT_OF_RANGE);
    }
  }
  return numbersInRange;
}

int client_checkNumberRange(client_t *self, char *number, int prevNumbers) {
  int returnValue = ERROR;
  if (prevNumbers == OK) {
    int numberToCheck = atoi(number);
    if ((numberToCheck >= 1) && (numberToCheck <= 9)) {
      returnValue = OK;
    }
  }
  return returnValue;
}

void client_release(client_t *self) {
  protocolC_release(&self -> protocol);
}
